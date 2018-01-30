#ifndef AMARYLLISMAINWINDOW_H
#define AMARYLLISMAINWINDOW_H

#define STB_IMAGE_IMPLEMENTATION

#include <QMainWindow>

namespace Ui {
class AmaryllisMainWindow;
}

class AmaryllisMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AmaryllisMainWindow(QWidget *parent = 0);
    ~AmaryllisMainWindow();

private:
    Ui::AmaryllisMainWindow *ui;
};

#endif // AMARYLLISMAINWINDOW_H
