#include "geogeometry.hpp"
#include "math.h"
#include <QDebug>

GeoGeometry::GeoGeometry()
{}

double GeoGeometry::minDistance(const QGeoCoordinate &start, const QGeoCoordinate &end, const QGeoCoordinate &point)
{
    double deltafi = point.latitude() * M_PI / 180.0 - start.latitude() * M_PI / 180.0;
    double deltal = point.longitude() * M_PI / 180.0 - start.longitude() * M_PI / 180.0;
    double theta_13 = start.azimuthTo(end) ;
    double theta_23 = theta_13 + 90;
    double d12 = 2 * asin(sqrt(pow(sin(deltafi / 2.0), 2.0) +
                               cos(start.latitude() * M_PI / 180.0) *  cos(point.latitude()  * M_PI / 180.0)
                               * pow(sin(deltafi / 2.0), 2.0)));

    double theta_a = acos((sin(point.latitude() * M_PI / 180.0) - sin(start.latitude() * M_PI / 180.0) * cos(d12)))
                        / (sin(d12) * cos(start.latitude() * M_PI / 180.0));
    double theta_b = acos((sin(start.latitude() * M_PI / 180.0) - sin(point.latitude() * M_PI / 180.0) * cos(d12)))
                        / (sin(d12) * cos(point.latitude() * M_PI / 180.0));

    double theta_12, theta_21;
    if(sin(deltal) > 0)
    {
        theta_12 = theta_a;
        theta_21 = 2 * M_PI - theta_b;
    }
    else{
        theta_12 = 2 * M_PI - theta_a;
        theta_21 = theta_b;
    }
    double a1 = theta_13 * M_PI / 180.0 - theta_12 * M_PI / 180.0;
    double a2 = theta_21 - theta_23 * M_PI / 180.0;
    double a3 = acos(-cos(a1) * cos(a2) + sin(a1) * sin(a2) * cos(d12));
    double d13 = atan2(sin(d12) * sin(a1) * sin(a2), cos(a2) + cos(a1) * cos(a3));
    double fi3 = asin(sin(start.latitude() * M_PI / 180.0) * cos(d13) + cos(start.latitude() * M_PI / 180.0) * sin(d13) * cos(theta_13 * M_PI / 180.0) );
    double l3 = start.longitude() * M_PI / 180.0 + atan2(sin(theta_13 * M_PI / 180.0) * sin(d13) * cos(start.latitude() * M_PI / 180.0),
                                          cos(d13) - sin(start.latitude() * M_PI / 180.0) * sin(fi3));
    QGeoCoordinate new_point(fi3 * 180.0 / M_PI, l3 * 180.0 / M_PI);
    double max_lat = fmax(start.latitude(), end.latitude());
    double max_lon = fmax(start.longitude(), end.longitude());
    double min_lat = fmin(start.latitude(), end.latitude());
    double min_lon = fmin(start.longitude(), end.longitude());
    qDebug() << new_point.latitude() << " // " << new_point.longitude();
    if(new_point.latitude() > min_lat
    && new_point.latitude() < max_lat
    && new_point.longitude() > min_lon
    && new_point.longitude() < max_lon)
        qDebug() << "MORE";
    else{
        qDebug() << "LESS";

    }
    return 1000;
    /*
    double bearing1 = start.azimuthTo(point);
    double bearing2 = start.azimuthTo(end);

    double distanceAC = start.distanceTo(point) / 1000.0;
    double dXt = asin(sin(distanceAC/double(EARTH_R))
                     *sin((bearing1 * M_PI / 180.0)-(bearing2 * M_PI / 180.0))) * double(EARTH_R);

    double dAt = acos(cos(distanceAC/double(EARTH_R))/cos(dXt/double(EARTH_R))) * double(EARTH_R);
    double distEnd = start.distanceTo(end) / 1000.0;
    if(dAt < 0 || dAt >= distEnd)
        return 10000;
    return fabs(dXt);
    */
}
