#ifndef CAMERAMATRIXMODEL_H
#define CAMERAMATRIXMODEL_H

#include <QAbstractTableModel>

#include "camera.h"

class CameraMatrixModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CameraMatrixModel(Camera* camera, QObject *parent = 0);

signals:

public slots:

    void handleCameraUpdate()
    {
        QAbstractTableModel::dataChanged(QModelIndex(), QModelIndex());
    }

protected:
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    Camera* _camera;
};

#endif // CAMERAMATRIXMODEL_H
