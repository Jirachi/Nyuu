#-------------------------------------------------
#
# Project created by QtCreator 2012-10-20T00:03:35
#
#-------------------------------------------------

QT       += core gui

TARGET = Nyuu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CRenderWidget.cpp \
    aboutdialog.cpp \
    CEntity.cpp \
    CScene.cpp \
    Globals.cpp \
    CStaticGeometryEntity.cpp \
    Maths.cpp \
    QGraphicsAnimatedSprite.cpp

HEADERS  += mainwindow.h \
    CRenderWidget.h \
    aboutdialog.h \
    CEntity.h \
    CScene.h \
    Globals.h \
    CStaticGeometryEntity.h \
    Maths.h \
    QGraphicsAnimatedSprite.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    Resources.qrc
