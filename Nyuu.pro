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
    QGraphicsAnimatedSprite.cpp \
    QJson/serializerrunnable.cpp \
    QJson/serializer.cpp \
    QJson/qobjecthelper.cpp \
    QJson/parserrunnable.cpp \
    QJson/parser.cpp \
    QJson/json_scanner.cpp \
    QJson/json_parser.cc

HEADERS  += mainwindow.h \
    CRenderWidget.h \
    aboutdialog.h \
    CEntity.h \
    CScene.h \
    Globals.h \
    CStaticGeometryEntity.h \
    Maths.h \
    QGraphicsAnimatedSprite.h \
    CAnimatedGeometryEntity.h \
    QJson/stack.hh \
    QJson/serializerrunnable.h \
    QJson/serializer.h \
    QJson/qobjecthelper.h \
    QJson/qjson_export.h \
    QJson/qjson_debug.h \
    QJson/position.hh \
    QJson/parserrunnable.h \
    QJson/parser_p.h \
    QJson/parser.h \
    QJson/location.hh \
    QJson/json_scanner.h \
    QJson/json_parser.hh

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    Resources.qrc

OTHER_FILES += \
    QJson/json_parser.yy
