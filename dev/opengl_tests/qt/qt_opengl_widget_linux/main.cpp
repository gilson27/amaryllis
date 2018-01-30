#include "amaryllismainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AmaryllisMainWindow w;
    w.show();

    return a.exec();
}
