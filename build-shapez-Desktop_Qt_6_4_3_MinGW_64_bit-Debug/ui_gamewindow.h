/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QWidget *centralwidget;
    QPushButton *creatorButton;
    QPushButton *cutterButton;
    QPushButton *beltButton;
    QPushButton *trashButton;
    QPushButton *kitchenButton;
    QPushButton *magicButton;
    QPushButton *shopButton;
    QPushButton *saveButton;
    QPushButton *minerButton;
    QPushButton *mixerButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName("GameWindow");
        GameWindow->resize(1440, 900);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GameWindow->sizePolicy().hasHeightForWidth());
        GameWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(GameWindow);
        centralwidget->setObjectName("centralwidget");
        creatorButton = new QPushButton(centralwidget);
        creatorButton->setObjectName("creatorButton");
        creatorButton->setGeometry(QRect(520, 760, 50, 50));
        cutterButton = new QPushButton(centralwidget);
        cutterButton->setObjectName("cutterButton");
        cutterButton->setGeometry(QRect(620, 760, 50, 50));
        beltButton = new QPushButton(centralwidget);
        beltButton->setObjectName("beltButton");
        beltButton->setGeometry(QRect(570, 760, 50, 50));
        trashButton = new QPushButton(centralwidget);
        trashButton->setObjectName("trashButton");
        trashButton->setGeometry(QRect(670, 760, 50, 50));
        kitchenButton = new QPushButton(centralwidget);
        kitchenButton->setObjectName("kitchenButton");
        kitchenButton->setGeometry(QRect(720, 760, 50, 50));
        magicButton = new QPushButton(centralwidget);
        magicButton->setObjectName("magicButton");
        magicButton->setGeometry(QRect(770, 760, 50, 50));
        shopButton = new QPushButton(centralwidget);
        shopButton->setObjectName("shopButton");
        shopButton->setGeometry(QRect(60, 800, 60, 60));
        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(1340, 20, 40, 40));
        minerButton = new QPushButton(centralwidget);
        minerButton->setObjectName("minerButton");
        minerButton->setGeometry(QRect(820, 760, 50, 50));
        mixerButton = new QPushButton(centralwidget);
        mixerButton->setObjectName("mixerButton");
        mixerButton->setGeometry(QRect(870, 760, 50, 50));
        GameWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GameWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1440, 17));
        GameWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(GameWindow);
        statusbar->setObjectName("statusbar");
        GameWindow->setStatusBar(statusbar);

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GameWindow)
    {
        GameWindow->setWindowTitle(QCoreApplication::translate("GameWindow", "MainWindow", nullptr));
        creatorButton->setText(QString());
        cutterButton->setText(QString());
        beltButton->setText(QString());
        trashButton->setText(QString());
        kitchenButton->setText(QString());
        magicButton->setText(QString());
        shopButton->setText(QString());
        saveButton->setText(QString());
        minerButton->setText(QString());
        mixerButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
