#-------------------------------------------------
#
# Project created by QtCreator 2012-10-21T11:20:19
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtcv-balls
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    matwidget.cpp \
    matqimage.cpp \
    cv_balls.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    matwidget.h \
    matqimage.h \
    cv_balls.h \
    glwidget.h

FORMS    += mainwindow.ui

# OpenCV things:
unix:LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
win32 {
    INCLUDEPATH += F:/NoSpace/opencv/build/include
    LIBS += -LF:/NoSpace/opencv/build/x86/mingw/lib -lopencv_core242 -lopencv_highgui242 -lopencv_imgproc242
}

# OpenGL things:
unix:LIBS += -lGL -lGLU
win32 {
    INCLUDEPATH += F:\NoSpace\glut-3.7\include
    LIBS += -LF:\NoSpace\glut-3.7\glutdlls37beta -lglut
}
