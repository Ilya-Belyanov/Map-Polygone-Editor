#include <QGeoPath>

#include "polygonecontroller.hpp"
#include "geogeometry.hpp"

PolygoneController::PolygoneController(QObject *parent) : QObject(parent)
{

}

void PolygoneController::setModel(PolygoneModel *model)
{
    _model = model;
    resetCatchedCoordinate();
}

void PolygoneController::addCoordinate(const QGeoCoordinate &coord)
{
    if(!_model)
        return;
    int close = closeLineId(coord);
    if (close == -1)
        close = _model->rowCount() - 1;
    _model->insertCoordinate(close + 1, coord);
}

void PolygoneController::removeCloseCoordinate(const QGeoCoordinate &coord)
{
    int closeId = closePointId(coord);
    if(closeId != -1)
        _model->removeCoordinate(closeId);
}

void PolygoneController::catchCloseCoordinate(const QGeoCoordinate &coord)
{
    setCatchedCoordinate(closePointId(coord));
}

void PolygoneController::moveCatchedCoordinate(const QGeoCoordinate &coord)
{
    if(!hasCatchedCoordinate())
        return;
    _model->replaceCoordinate(_catchedCoordId, coord);
}

bool PolygoneController::hasCatchedCoordinate()
{
    return _catchedCoordId != -1;
}

void PolygoneController::resetCatchedCoordinate()
{
    setCatchedCoordinate(-1);
}

void PolygoneController::setCatchedCoordinate(int catched)
{
    if(_catchedCoordId == catched)
        return;
    _catchedCoordId = catched;
    emit hasCatchedCoordinateChanged();
}

int PolygoneController::closeLineId(const QGeoCoordinate &point)
{
    double min = 10000;
    int position = -1;
    QList<QGeoCoordinate> coordinates = _model->geoCoordinates();
    for(int i = 0; i < coordinates.size(); i++)
    {
        int end_point = (i == coordinates.size() - 1) ? 0: i + 1;

        QGeoCoordinate start = coordinates.at(i);
        QGeoCoordinate end = coordinates.at(end_point);
        if(!GeoGeometry::belongRect(start, end, point))
            continue;

        double local_min = GeoGeometry::minDistance(start, end, point);
        if(local_min < min)
        {
            min = local_min;
            position = i;
        }
    }
    if(min < CLOSE_DISTANCE_TO_LINE)
        return position;
    return -1;
}

int PolygoneController::closePointId(const QGeoCoordinate &point)
{
    QList<QGeoCoordinate> coordinates = _model->geoCoordinates();
    return GeoGeometry::closedPointId(QGeoPath(_model->geoCoordinates()), point, CLOSE_DISTANCE_POINTS);
}
