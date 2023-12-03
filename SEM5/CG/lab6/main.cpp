#include <QApplication>
#include <QSurfaceFormat>

#include "Mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
    Mainwindow w;
    w.show();
    return QApplication::exec();
}
