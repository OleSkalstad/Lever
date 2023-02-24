QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    ball.cpp \
    camera.cpp \
    disc.cpp \
    funksjon.cpp \
    interactiveobject.cpp \
    inversefunksjon.cpp \
    logger.cpp \
    mainwindow.cpp \
    renderwindow.cpp \
    s_xyz.cpp \
    shader.cpp \
    trianglesurface.cpp \
    vertex.cpp \
    visualobject.cpp

HEADERS += \
    ball.h \
    camera.h \
    disc.h \
    funksjon.h \
    interactiveobject.h \
    inversefunksjon.h \
    logger.h \
    mainwindow.h \
    renderwindow.h \
    s_xyz.h \
    shader.h \
    trianglesurface.h \
    vertex.h \
    visualobject.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    plainshader.frag \
    plainshader.vert
