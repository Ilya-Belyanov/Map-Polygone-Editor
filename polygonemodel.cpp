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
    return QVariant();
}

QHash<int, QByteArray> PolygoneModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[LatRole] = "lat";
    roles[LonRole] = "lon";
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

QList<QGeoCoordinate> PolygoneModel::geoCoordinates() const
{
    return _coordinates;
}

void PolygoneModel::insertCoordinate(int row, const QGeoCoordinate &coord)
{
    beginInsertRows(QModelIndex(), row, row);
    _coordinates.insert(row, coord);
    endInsertRows();
    emit coordinatesChanged();
}

void PolygoneModel::replaceCoordinate(int row, const QGeoCoordinate &coord)
{
    _coordinates[row] = coord;
    QModelIndex index = this->index(row, 0);
    emit dataChanged(index, index);
    emit coordinatesChanged();
}

void PolygoneModel::removeCoordinate(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    _coordinates.removeAt(row);
    endRemoveRows();
    emit coordinatesChanged();
}
