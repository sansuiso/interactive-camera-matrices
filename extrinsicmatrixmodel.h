#ifndef EXTRINSICMATRIXMODEL_H
#define EXTRINSICMATRIXMODEL_H

#include <QAbstractTableModel>

#include "camera.h"

class ExtrinsicMatrixModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ExtrinsicMatrixModel(Camera* camera, QObject *parent = 0);

signals:

public slots:
    void handleCameraUpdate() {
        QAbstractTableModel::dataChanged(QModelIndex(), QModelIndex());
    }

protected:
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

private:
    Camera* _camera;
};

#endif // EXTRINSICMATRIXMODEL_H
