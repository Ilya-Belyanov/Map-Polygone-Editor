#ifndef POLYGONECONTROLLER_HPP
#define POLYGONECONTROLLER_HPP

#include <QObject>
#include <QGeoCoordinate>

#include "polygonemodel.hpp"

constexpr uint CLOSE_DISTANCE_TO_LINE = 1; // Близкое расстояние до точки (в КМ)
constexpr uint CLOSE_DISTANCE_POINTS = 100; // Близкое от точки до точки (в М)

class PolygoneController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool hasCatchedCoordinate READ hasCatchedCoordinate NOTIFY hasCatchedCoordinateChanged)

public:
    explicit PolygoneController(QObject *parent = nullptr);

    void setModel(PolygoneModel *model);
    Q_INVOKABLE void addCoordinate(const QGeoCoordinate &coord);
    Q_INVOKABLE void removeCloseCoordinate(const QGeoCoordinate &coord);

    Q_INVOKABLE void catchCloseCoordinate(const QGeoCoordinate &coord);
    Q_INVOKABLE void moveCatchedCoordinate(const QGeoCoordinate &coord);

    bool hasCatchedCoordinate();
    Q_INVOKABLE void resetCatchedCoordinate();

signals:
    void hasCatchedCoordinateChanged();

private:
    PolygoneModel *_model;
    int _catchedCoordId{-1};

    void setCatchedCoordinate(int catched);
    int closeLineId(const QGeoCoordinate &point);
    int closePointId(const QGeoCoordinate &point);
};

#endif // POLYGONECONTROLLER_HPP
