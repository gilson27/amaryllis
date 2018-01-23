#ifndef GLMAINWINDOW_H
#define GLMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class GLMainWindow;
}

class GLMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GLMainWindow(QWidget *parent = 0);
    ~GLMainWindow();

private slots:
    void on_openGLWidget_resized();

private:
    Ui::GLMainWindow *ui;
};

#endif // GLMAINWINDOW_H
