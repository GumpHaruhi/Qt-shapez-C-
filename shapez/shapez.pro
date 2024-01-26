QT       += core gui
QT       += multimedia
QT       += widgets
QT       += core multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basetool.cpp \
    belt.cpp \
    cack.cpp \
    chicken.cpp \
    creator.cpp \
    cutter.cpp \
    fruit.cpp \
    fruitcack.cpp \
    gamewindow.cpp \
    gold.cpp \
    kitchen.cpp \
    kunkun.cpp \
    main.cpp \
    mappoint.cpp \
    mixer.cpp \
    noodles.cpp \
    soundplayer.cpp \
    startwindow.cpp \
    trash.cpp \
    treasure.cpp \
    water.cpp \
    world.cpp

HEADERS += \
    DataZip.h \
    basetool.h \
    belt.h \
    cack.h \
    chicken.h \
    creator.h \
    cutter.h \
    fruit.h \
    fruitcack.h \
    gamewindow.h \
    gold.h \
    kitchen.h \
    kunkun.h \
    mappoint.h \
    mixer.h \
    noodles.h \
    soundplayer.h \
    startwindow.h \
    trash.h \
    treasure.h \
    water.h \
    world.h

FORMS += \
    gamewindow.ui \
    startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_ICONS  += logoexe.ico
