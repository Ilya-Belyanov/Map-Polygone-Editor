#include "polygonemodel.hpp"
#include "geogeometry.hpp"
#include <QDebug>

PolygoneModel::PolygoneModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int PolygoneModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _coordinates.size();
}

QVariant PolygoneModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= rowCount())
        return QVariant();
    if(role == LatRole)
        return QVariant::fromValue(_coordinates.at(index.row()).latitude());
    else if(role == LonRole)
        return QVariant::fromValue(_coordinates.at(index.row()).longitude());
    else if(role == IsCathed)
        return _catchedCoordId == index.row();
    return QVariant();
}

QHash<int, QByteArray> PolygoneModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[LatRole] = "lat";
    roles[LonRole] = "lon";
    roles[IsCathed] = "is_catched";
    return roles;
}

QVariantList PolygoneModel::coordinates() const
{
    QVariantList coorvariant;
    foreach(auto &coordinate, _coordinates){
        coorvariant.append(QVariant::fromValue(coordinate));
    }
    return coorvariant;
}


void PolygoneModel::addCoordinate(const QGeoCoordinate &coord)
{
    int close = closeLine(coord);
    if (close == -1)
        close = rowCount() - 1;
    beginInsertRows(QModelIndex(), close + 1, close + 1);
    _coordinates.insert(close + 1, coord);
    endInsertRows();
    emit coordinatesChanged();
}

void PolygoneModel::catchCloseCoordinate(const QGeoCoordinate &coord)
{
    for(int i = 0; i < _coordinates.size(); i++)
    {
        if(_coordinates.at(i).distanceTo(coord) <= 50)
        {
            _catchedCoordId = i;
            QModelIndex index = this->index(_catchedCoordId, 0);
            emit dataChanged(index, index);
            emit hasCatchedCoordinateChanged();
        }
    }
}

void PolygoneModel::moveCatchedCoordinate(const QGeoCoordinate &coord)
{
    if(!hasCatchedCoordinate())
        return;
    _coordinates[_catchedCoordId] = coord;
    QModelIndex index = this->index(_catchedCoordId, 0);
    emit dataChanged(index, index);
    emit coordinatesChanged();

}

bool PolygoneModel::hasCatchedCoordinate()
{
    return _catchedCoordId != -1;
}

void PolygoneModel::resetCatchedCoordinate()
{
    if(_catchedCoordId == -1)
        return;
    QModelIndex index = this->index(_catchedCoordId, 0);
    _catchedCoordId = -1;
    emit dataChanged(index, index);
}

int PolygoneModel::closeLine(const QGeoCoordinate &point)
{
    double min = 10000;
    int position = -1;

    for(int i = 0; i < _coordinates.size(); i++)
    {
        int end_point = (i == _coordinates.size() - 1) ? 0: i + 1;
        double local_min = GeoGeometry::minDistance(_coordinates.at(i),
                                       _coordinates.at(end_point),
                                       point);
        qDebug() << local_min;
        if(local_min < min)
        {
            min = local_min;
            position = i;
        }
    }
    if(min < 10)
        return position;
    return -1;
}
