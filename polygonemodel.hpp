#ifndef POLYGONEMODEL_HPP
#define POLYGONEMODEL_HPP

#include <QAbstractListModel>
#include <QGeoCoordinate>

class PolygoneModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariantList coordinates READ coordinates NOTIFY coordinatesChanged)

public:
    enum Roles {
            LatRole = Qt::UserRole + 1,
            LonRole
        };

    explicit PolygoneModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVariantList coordinates() const;
    QList<QGeoCoordinate> geoCoordinates() const;
    void insertCoordinate(int row, const QGeoCoordinate &coord);
    void replaceCoordinate(int row, const QGeoCoordinate &coord);
    void removeCoordinate(int row);

signals:
    void coordinatesChanged();

private:
    QList<QGeoCoordinate> _coordinates;
};

#endif // POLYGONEMODEL_HPP
