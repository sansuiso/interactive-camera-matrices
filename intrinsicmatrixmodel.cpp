#include <Eigen/Core>

#include "camera.h"
#include "intrinsicmatrixmodel.h"

IntrinsicMatrixModel::IntrinsicMatrixModel(Camera *camera, QObject *parent)
    : QAbstractTableModel(parent), _camera(camera)
{

}

int IntrinsicMatrixModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

int IntrinsicMatrixModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant IntrinsicMatrixModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole && _camera)
    {
        Eigen::Matrix3f source = _camera->intrinsic();
        return QString::number(source(row, col));
    }

    return QVariant();
}

QVariant IntrinsicMatrixModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);

    return QVariant();
}
