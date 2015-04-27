#ifndef INTRINSICMATRIXMODEL_H
#define INTRINSICMATRIXMODEL_H

#include <QAbstractTableModel>

QT_FORWARD_DECLARE_CLASS(Camera)

class IntrinsicMatrixModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit IntrinsicMatrixModel(Camera* camera, QObject *parent = 0);

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

#endif // INTRINSICMATRIXMODEL_H
