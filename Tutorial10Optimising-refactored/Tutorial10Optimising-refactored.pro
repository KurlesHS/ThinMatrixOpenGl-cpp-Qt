#-------------------------------------------------
#
# Project created by QtCreator 2017-03-28T22:45:25
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += SRCDIR=\\\"$$PWD/\\\"

TARGET = Tutorial10Optimising-refactored

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    mainwindow.cpp \
    renderEngine/displaymanager.cpp \
    engineTester/maingameloop.cpp \
    renderEngine/display.cpp \
    renderEngine/loader.cpp \
    renderEngine/irenderer.cpp \
    renderEngine/shaderprogram.cpp \
    renderEngine/staticshader.cpp \
    textures/modeltexture.cpp \
    models/texturedmodel.cpp \
    models/rawmodel.cpp \
    toolbox/maths.cpp \
    entities/entity.cpp \
    entities/camera.cpp \
    toolbox/keyboard.cpp \
    renderEngine/objloader.cpp \
    entities/light.cpp \
    toolbox/misc.cpp \
    renderEngine/masterrenderer.cpp \
    renderEngine/entityrenderer.cpp

HEADERS  += mainwindow.h \
    renderEngine/displaymanager.h \
    engineTester/maingameloop.h \
    renderEngine/display.h \
    renderEngine/loader.h \
    renderEngine/irenderer.h \
    renderEngine/shaderprogram.h \
    renderEngine/staticshader.h \
    textures/modeltexture.h \
    models/texturedmodel.h \
    models/rawmodel.h \
    toolbox/maths.h \
    entities/entity.h \
    entities/camera.h \
    toolbox/keyboard.h \
    renderEngine/objloader.h \
    entities/light.h \
    toolbox/misc.h \
    renderEngine/masterrenderer.h \
    renderEngine/entityrenderer.h

FORMS    += mainwindow.ui

DISTFILES += \
    shaders/shader.vert \
    shaders/shader.frag

RESOURCES += \
    tut10.qrc
