#include "geogeometry.hpp"
#include "math.h"

GeoGeometry::GeoGeometry()
{}

double GeoGeometry::minDistance(const QGeoCoordinate &start, const QGeoCoordinate &end, const QGeoCoordinate &point)
{
    double y = sin(point.longitude() - start.longitude()) * cos(point.latitude());
    double x = cos(start.latitude()) * sin(point.latitude())
            - sin(start.latitude()) * cos(point.latitude())
            * cos(point.latitude() - start.latitude());
    double bearing1 = atan2(y, x) * 180 / M_PI;
    bearing1 = 360 - (int(bearing1 + 360) % 360);

    double y2 = sin(end.longitude() - start.longitude())
            * cos(end.latitude());
    double x2 = cos(start.latitude()) * sin(end.latitude())
            - sin(start.latitude()) * cos(end.latitude())
            * cos(end.latitude() - start.latitude());
    double bearing2 = +atan2(y2, x2) * 180 / M_PI;
    bearing2 = 360 - (int(bearing2 + 360) % 360);

    double lat1Rads = start.latitude() * M_PI / 180;
    double lat3Rads = point.latitude() * M_PI / 180;
    double dLon = (point.longitude() - start.longitude()) * M_PI / 180;

    double distanceAC = acos(sin(lat1Rads)
                             * sin(lat3Rads)+cos(lat1Rads)*cos(lat3Rads)*cos(dLon)) * EARTH_R;
    return fabs(asin(sin(distanceAC/EARTH_R)
                     *sin((bearing1 * M_PI / 180)-(bearing2* M_PI / 180))) * EARTH_R);
}
