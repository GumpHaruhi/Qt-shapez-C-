/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartWindow
{
public:
    QWidget *centralwidget;
    QPushButton *newGame;
    QPushButton *loadGame;
    QLabel *logo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StartWindow)
    {
        if (StartWindow->objectName().isEmpty())
            StartWindow->setObjectName("StartWindow");
        StartWindow->resize(1440, 900);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StartWindow->sizePolicy().hasHeightForWidth());
        StartWindow->setSizePolicy(sizePolicy);
        StartWindow->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        centralwidget = new QWidget(StartWindow);
        centralwidget->setObjectName("centralwidget");
        newGame = new QPushButton(centralwidget);
        newGame->setObjectName("newGame");
        newGame->setGeometry(QRect(400, 320, 200, 40));
        sizePolicy.setHeightForWidth(newGame->sizePolicy().hasHeightForWidth());
        newGame->setSizePolicy(sizePolicy);
        loadGame = new QPushButton(centralwidget);
        loadGame->setObjectName("loadGame");
        loadGame->setGeometry(QRect(400, 420, 200, 40));
        sizePolicy.setHeightForWidth(loadGame->sizePolicy().hasHeightForWidth());
        loadGame->setSizePolicy(sizePolicy);
        loadGame->setStyleSheet(QString::fromUtf8(""));
        logo = new QLabel(centralwidget);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(150, 60, 700, 180));
        sizePolicy.setHeightForWidth(logo->sizePolicy().hasHeightForWidth());
        logo->setSizePolicy(sizePolicy);
        StartWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StartWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1440, 17));
        StartWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(StartWindow);
        statusbar->setObjectName("statusbar");
        StartWindow->setStatusBar(statusbar);

        retranslateUi(StartWindow);

        QMetaObject::connectSlotsByName(StartWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StartWindow)
    {
        StartWindow->setWindowTitle(QCoreApplication::translate("StartWindow", "StartWindow", nullptr));
        newGame->setText(QCoreApplication::translate("StartWindow", "\346\226\260\346\270\270\346\210\217", nullptr));
        loadGame->setText(QCoreApplication::translate("StartWindow", "\350\257\273\345\217\226\345\255\230\346\241\243", nullptr));
        logo->setText(QCoreApplication::translate("StartWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartWindow: public Ui_StartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
