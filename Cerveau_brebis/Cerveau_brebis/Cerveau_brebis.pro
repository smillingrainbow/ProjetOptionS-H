#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T14:45:32
#
#-------------------------------------------------

QT       += core gui
QT	+= sql
QT	+= widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cerveau_brebis
TEMPLATE = app


SOURCES += main.cpp\
    childview.cpp \
    database.cpp \
    dialog.cpp \
    mainwidget.cpp \
    geometryengine.cpp \
    windowdb.cpp

HEADERS  += \
    childview.h \
    database.h \
    dialog.h \
    mainwidget.h \
    geometryengine.h \
    windowdb.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target



