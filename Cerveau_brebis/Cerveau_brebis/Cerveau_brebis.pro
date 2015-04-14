#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T14:45:32
#
#-------------------------------------------------

QT       += core gui
QT	+= sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cerveau_brebis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    childview.cpp \
    database.cpp \
    dialog.cpp \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS  += mainwindow.h \
    childview.h \
    database.h \
    dialog.h \
    mainwidget.h \
    geometryengine.h

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target



