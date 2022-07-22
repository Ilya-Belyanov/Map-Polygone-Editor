#ifndef POLYGONEMODEL_HPP
#define POLYGONEMODEL_HPP

#include <QAbstractListModel>
#include <QGeoCoordinate>

constexpr uint CLOSE_DISTANCE_TO_LINE = 1; // Близкое расстояние до точки (в КМ)
constexpr uint CLOSE_DISTANCE_POINTS = 50; // Близкое от точки до точки (в М)

class PolygoneModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariantList coordinates READ coordinates NOTIFY coordinatesChanged)
    Q_PROPERTY(bool hasCatchedCoordinate READ hasCatchedCoordinate NOTIFY hasCatchedCoordinateChanged)

public:
    enum Roles {
            LatRole = Qt::UserRole + 1,
            LonRole,
            IsCathed
        };

    explicit PolygoneModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVariantList coordinates() const;
    Q_INVOKABLE void addCoordinate(const QGeoCoordinate &coord);
    Q_INVOKABLE void removeCloseCoordinate(const QGeoCoordinate &coord);

    void removeRow(int row);

    Q_INVOKABLE void catchCloseCoordinate(const QGeoCoordinate &coord);
    Q_INVOKABLE void moveCatchedCoordinate(const QGeoCoordinate &coord);

    bool hasCatchedCoordinate();
    Q_INVOKABLE void resetCatchedCoordinate();

signals:
    void coordinatesChanged();
    void hasCatchedCoordinateChanged();

private:
    QVector<QGeoCoordinate> _coordinates;
    int _catchedCoordId{-1};

    int closeLine(const QGeoCoordinate &point);
    int closePointId(const QGeoCoordinate &point);
    void setCatchedCoordinate(int catched);
};

#endif // POLYGONEMODEL_HPP
