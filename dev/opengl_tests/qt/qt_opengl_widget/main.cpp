#include "glmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLMainWindow w;
    w.show();

    return a.exec();
}
