#-------------------------------------------------
#
# Project created by QtCreator 2015-02-26T13:23:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sommet.cpp \
    arc.cpp \
    graphe.cpp \
    mygraphicsview.cpp

HEADERS  += mainwindow.h \
    sommet.h \
    arc.h \
    graphe.h \
    mygraphicsview.h \
    constantes.h

FORMS    += mainwindow.ui
