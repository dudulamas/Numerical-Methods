#-------------------------------------------------
#
# Project created by QtCreator 2017-12-09T10:01:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Metodos_Part2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    ldp_solucao.cpp \
    lu_solucao.cpp \
    matriz.cpp \
    operacoes.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    methods.h \
    ldp_solucao.h \
    lu_solucao.h \
    matriz.h \
    operacoes.h

FORMS    += mainwindow.ui \
    dialog.ui
