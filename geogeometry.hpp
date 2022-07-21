#ifndef GEOGEOMETRY_HPP
#define GEOGEOMETRY_HPP

#include <QGeoCoordinate>

constexpr int EARTH_R = 6371;

class GeoGeometry
{
public:
    GeoGeometry();

    /**
     * @brief minDistance - минимальная дистанция между отрезком и точкой в километрах
     * @param start - начало отрезка
     * @param end - конец отрезка
     * @param point - точка, до которой считаем расстояние
     * @return расстояние в километрах
     */
    static double minDistance(const QGeoCoordinate &start, const QGeoCoordinate &end,
                       const QGeoCoordinate &point);
};

#endif // GEOGEOMETRY_HPP
