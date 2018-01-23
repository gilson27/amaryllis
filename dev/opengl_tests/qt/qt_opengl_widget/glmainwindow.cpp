#include "glmainwindow.h"
#include "ui_glmainwindow.h"

GLMainWindow::GLMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GLMainWindow)
{
    ui->setupUi(this);
}

GLMainWindow::~GLMainWindow()
{
    delete ui;
}

void GLMainWindow::on_openGLWidget_resized()
{

}
