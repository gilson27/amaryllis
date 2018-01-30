#include "amaryllismainwindow.h"
#include "ui_amaryllismainwindow.h"

AmaryllisMainWindow::AmaryllisMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AmaryllisMainWindow)
{
    ui->setupUi(this);
}

AmaryllisMainWindow::~AmaryllisMainWindow()
{
    delete ui;
}
