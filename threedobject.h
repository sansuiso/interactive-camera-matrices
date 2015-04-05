#ifndef THREEDOBJECT_H
#define THREEDOBJECT_H

#include <QObject>
#include <QVector>

#include <qopengl.h>

class ThreeDObject : public QObject
{
    Q_OBJECT
public:
    explicit ThreeDObject(QObject *parent = 0);
    ~ThreeDObject();

    GLfloat const* data() const {
        return _data.constData();
    }

    int vertexCount() const {
        return _data.size();
    }

    int triangleCount() const {
        return _data.size()/3;
    }

signals:

public slots:

private:
    QVector<GLfloat> _data;
};

#endif // THREEDOBJECT_H
