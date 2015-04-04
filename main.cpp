#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);

    MainWindow w;
    w.resize(w.sizeHint());
    w.show();

    return a.exec();
}
