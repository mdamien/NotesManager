QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NotesManager
TEMPLATE = app

SOURCES += \
    main.cpp \
    articlewidget.cpp \
    article.cpp \
    note.cpp \
    document.cpp \
    binary.cpp \
    mainwindow.cpp \
    notesmanager.cpp \
    exportstrategy.cpp \
    textexport.cpp \
    notesfactory.cpp \
    articlefactory.cpp \
    documentfactory.cpp \
    htmlexport.cpp \
    videofactory.cpp \
    audiofactory.cpp \
    imagefactory.cpp \
    savetextexport.cpp

HEADERS += \
    articlewidget.h \
    article.h \
    note.h \
    document.h \
    binary.h \
    mainwindow.h \
    notesmanager.h \
    exportstrategy.h \
    textexport.h \
    notesfactory.h \
    articlefactory.h \
    documentfactory.h \
    htmlexport.h \
    videofactory.h \
    audiofactory.h \
    imagefactory.h \
    savetextexport.h
