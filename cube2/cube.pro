QT       += core gui widgets sql

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp


SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp\
    infoview.cpp
HEADERS += \
    mainwidget.h \
    geometryengine.h \
    infoview.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

FORMS +=
