#include <Eigen/Core>
#include <QString>

#include "extrinsicmatrixmodel.h"

ExtrinsicMatrixModel::ExtrinsicMatrixModel(Camera *camera, QObject *parent)
    : QAbstractTableModel(parent), _camera(camera)
{

}

int ExtrinsicMatrixModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

int ExtrinsicMatrixModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant ExtrinsicMatrixModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole && _camera)
    {
        Eigen::Matrix4f source = _camera->extrinsic();
        return QString::number(source(row, col));
    }

    return QVariant();
}

QVariant ExtrinsicMatrixModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);

    return QVariant();
}
