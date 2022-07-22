#include "geogeometry.hpp"
#include "math.h"
#include <QDebug>

GeoGeometry::GeoGeometry()
{}

double GeoGeometry::minDistance(const QGeoCoordinate &start, const QGeoCoordinate &end, const QGeoCoordinate &point)
{
    double bearing1 = start.azimuthTo(point);
    double bearing2 = start.azimuthTo(end);

    double distanceAC = start.distanceTo(point) / 1000.0;
    double dXt = asin(sin(distanceAC/double(EARTH_R))
                     *sin((bearing1 * M_PI / 180.0)-(bearing2 * M_PI / 180.0))) * double(EARTH_R);
    return fabs(dXt);
}

bool GeoGeometry::belongRect(const QGeoCoordinate &start, const QGeoCoordinate &end, const QGeoCoordinate &point, double eps)
{
    double max_lat = fmax(start.latitude(), end.latitude()) + eps;
    double max_lon = fmax(start.longitude(), end.longitude()) + eps;
    double min_lat = fmin(start.latitude(), end.latitude()) - eps;
    double min_lon = fmin(start.longitude(), end.longitude()) - eps;
    if(point.latitude() > min_lat
    && point.latitude() < max_lat
    && point.longitude() > min_lon
    && point.longitude() < max_lon)
        return true;
    return false;
}

int GeoGeometry::closedPointId(const QGeoPath &path, const QGeoCoordinate &point, double eps)
{
    double minDist = eps + 100;
    int index = -1;
    for(int i = 0; i < path.size(); i++)
    {
        double dist = path.coordinateAt(i).distanceTo(point);
        if(dist <= eps && dist < minDist)
        {
            index = i;
            minDist = dist;
        }
    }
    return index;
}
