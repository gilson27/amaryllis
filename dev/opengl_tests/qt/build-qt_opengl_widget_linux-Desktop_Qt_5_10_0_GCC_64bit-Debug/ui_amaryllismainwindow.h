/********************************************************************************
** Form generated from reading UI file 'amaryllismainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AMARYLLISMAINWINDOW_H
#define UI_AMARYLLISMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AmaryllisMainWindow
{
public:
    QAction *actionExit;
    QAction *actionAmaryllis;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QOpenGLWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AmaryllisMainWindow)
    {
        if (AmaryllisMainWindow->objectName().isEmpty())
            AmaryllisMainWindow->setObjectName(QStringLiteral("AmaryllisMainWindow"));
        AmaryllisMainWindow->resize(640, 480);
        actionExit = new QAction(AmaryllisMainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon;
        icon.addFile(QStringLiteral("images/File-delete-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon);
        actionAmaryllis = new QAction(AmaryllisMainWindow);
        actionAmaryllis->setObjectName(QStringLiteral("actionAmaryllis"));
        centralWidget = new QWidget(AmaryllisMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        openGLWidget = new QOpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        gridLayout->addWidget(openGLWidget, 2, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        AmaryllisMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AmaryllisMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        AmaryllisMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AmaryllisMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AmaryllisMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AmaryllisMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AmaryllisMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuAbout->addAction(actionAmaryllis);

        retranslateUi(AmaryllisMainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), AmaryllisMainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(AmaryllisMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AmaryllisMainWindow)
    {
        AmaryllisMainWindow->setWindowTitle(QApplication::translate("AmaryllisMainWindow", "AmaryllisMainWindow", nullptr));
        actionExit->setText(QApplication::translate("AmaryllisMainWindow", "Exit", nullptr));
        actionAmaryllis->setText(QApplication::translate("AmaryllisMainWindow", "Amaryllis", nullptr));
        menuFile->setTitle(QApplication::translate("AmaryllisMainWindow", "File", nullptr));
        menuAbout->setTitle(QApplication::translate("AmaryllisMainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AmaryllisMainWindow: public Ui_AmaryllisMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AMARYLLISMAINWINDOW_H
