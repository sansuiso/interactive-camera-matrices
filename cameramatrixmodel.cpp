#include "cameramatrixmodel.h"

CameraMatrixModel::CameraMatrixModel(Camera* camera, QObject *parent)
    : QAbstractTableModel(parent), _camera(camera)
{

}

int CameraMatrixModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;
}

int CameraMatrixModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;
}

QVariant CameraMatrixModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    Q_UNUSED(role);

    return QVariant();
}

QVariant CameraMatrixModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);

    return QVariant();
}
