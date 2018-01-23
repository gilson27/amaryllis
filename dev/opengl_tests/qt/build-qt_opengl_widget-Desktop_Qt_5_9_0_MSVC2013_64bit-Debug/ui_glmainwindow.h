/********************************************************************************
** Form generated from reading UI file 'glmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLMAINWINDOW_H
#define UI_GLMAINWINDOW_H

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

class Ui_GLMainWindow
{
public:
    QAction *actionExit;
    QAction *actionAbout_Us;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QOpenGLWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GLMainWindow)
    {
        if (GLMainWindow->objectName().isEmpty())
            GLMainWindow->setObjectName(QStringLiteral("GLMainWindow"));
        GLMainWindow->resize(516, 392);
        actionExit = new QAction(GLMainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout_Us = new QAction(GLMainWindow);
        actionAbout_Us->setObjectName(QStringLiteral("actionAbout_Us"));
        centralWidget = new QWidget(GLMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        openGLWidget = new QOpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        gridLayout->addWidget(openGLWidget, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        GLMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GLMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 516, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        GLMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GLMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GLMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GLMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GLMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout_Us);

        retranslateUi(GLMainWindow);

        QMetaObject::connectSlotsByName(GLMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GLMainWindow)
    {
        GLMainWindow->setWindowTitle(QApplication::translate("GLMainWindow", "GLMainWindow", Q_NULLPTR));
        actionExit->setText(QApplication::translate("GLMainWindow", "Exit", Q_NULLPTR));
        actionAbout_Us->setText(QApplication::translate("GLMainWindow", "About Us", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("GLMainWindow", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("GLMainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GLMainWindow: public Ui_GLMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLMAINWINDOW_H
