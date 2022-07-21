#ifndef POLYGONEMODEL_HPP
#define POLYGONEMODEL_HPP

#include <QAbstractListModel>
#include <QGeoCoordinate>

class PolygoneModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariantList coordinates READ coordinates NOTIFY coordinatesChanged)
    Q_PROPERTY(bool hasCatchedCoordinate READ hasCatchedCoordinate NOTIFY hasCatchedCoordinateChanged)

public:
    explicit PolygoneModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVariantList coordinates() const;
    Q_INVOKABLE void addCoordinate(const QGeoCoordinate &coord);

    Q_INVOKABLE void catchCloseCoordinate(const QGeoCoordinate &coord);
    Q_INVOKABLE void moveCatchedCoordinate(const QGeoCoordinate &coord);

    bool hasCatchedCoordinate();
    bool hasTrue(){return true;};
    Q_INVOKABLE void resetCatchedCoordinate();

signals:
    void coordinatesChanged();
    void hasCatchedCoordinateChanged();

private:
    QVector<QGeoCoordinate> _coordinates;
    int _catchedCoordId{-1};
    int closeLine(const QGeoCoordinate &point);
};

#endif // POLYGONEMODEL_HPP
