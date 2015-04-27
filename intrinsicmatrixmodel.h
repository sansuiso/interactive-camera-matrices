#ifndef INTRINSICMATRIXMODEL_H
#define INTRINSICMATRIXMODEL_H

#include "cameramatrixmodel.h"

class IntrinsicMatrixModel : public CameraMatrixModel
{
    Q_OBJECT
public:
    explicit IntrinsicMatrixModel(Camera* camera, QObject *parent = 0);

protected:
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
};

#endif // INTRINSICMATRIXMODEL_H
