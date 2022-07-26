#ifndef GEOGEOMETRY_HPP
#define GEOGEOMETRY_HPP

#include <QGeoCoordinate>
#include <QGeoPath>

constexpr int EARTH_R = 6371; // Средний радиус земли в КМ

class GeoGeometry
{
public:
    GeoGeometry();

    /**
     * @brief minDistance - минимальная дистанция между прямой и точкой в километрах
     * @param start - начало прямой
     * @param end - конец прямой
     * @param point - точка, до которой считаем расстояние
     * @return расстояние в километрах
     */
    static double minDistance(const QGeoCoordinate &start, const QGeoCoordinate &end,
                       const QGeoCoordinate &point);

    /**
     * @brief belongRect - проверка на принадлежность точки к прямоугольнику, образованному другими точками
     * @param start - начало прямоугольника
     * @param end - конец прямоугольника
     * @param point - точка, для которой определяем принадлежность
     * @param eps - запас для случаев горизонтальных или вертикальных прямых (в грудусах)
     * @return принадлежит ли?
     */
    static bool belongRect(const QGeoCoordinate &start, const QGeoCoordinate &end,
                           const QGeoCoordinate &point, double eps = 0.001);

    /**
     * @brief closedPoint - вычисляет ближайшую точку из пути до точки
     * @param path - гео путь
     * @param point - точка
     * @param eps - мера близости (метры)
     * @return индекс ближней точки, расстояние до которой меньше eps
     */
    static int closedPointId(const QGeoPath &path, const QGeoCoordinate &point, double eps = 1);
};

#endif // GEOGEOMETRY_HPP
