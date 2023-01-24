#include <QApplication>
#include "choice.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    choice diag;
    diag.show();
    return a.exec();
}
