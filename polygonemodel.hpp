#ifndef POLYGONEMODEL_HPP
#define POLYGONEMODEL_HPP

#include <QAbstractListModel>
#include <QGeoCoordinate>

class PolygoneModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariantList coordinates READ coordinates NOTIFY coordinatesChanged)

public:
    explicit PolygoneModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVariantList coordinates() const;
    Q_INVOKABLE void addCoordinate(const QGeoCoordinate &coord);

signals:
    void coordinatesChanged();

private:
    QVector<QGeoCoordinate> _coordinates;

    int closeLine(const QGeoCoordinate &point);
};

#endif // POLYGONEMODEL_HPP
