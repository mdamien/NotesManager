QT       += core gui phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NotesManager
TEMPLATE = app

FORMS = \
    mainwindow.ui \
    settingsdialog.ui

SOURCES += \
    main.cpp \
    article.cpp \
    note.cpp \
    document.cpp \
    binary.cpp \
    notesmanager.cpp \
    exportstrategy.cpp \
    textexport.cpp \
    htmlexport.cpp \
    savetextexport.cpp \
    tag.cpp \
    tagmanager.cpp \
    notesparser.cpp \
    latexexport.cpp \
    mainwindow.cpp \
    notewidget.cpp \
    articlewidget.cpp \
    documentwidget.cpp \
    imagewidget.cpp \
    audiowidget.cpp \
    videowidget.cpp \
    settingsdialog.cpp \
    historymanager.cpp \
    trash.cpp

HEADERS += \
    article.h \
    note.h \
    document.h \
    binary.h \
    notesmanager.h \
    exportstrategy.h \
    textexport.h \
    htmlexport.h \
    savetextexport.h \
    tag.h \
    tagmanager.h \
    notesparser.h \
    latexexport.h \
    mainwindow.h \
    notewidget.h \
    articlewidget.h \
    documentwidget.h \
    imagewidget.h \
    audiowidget.h \
    videowidget.h \
    settingsdialog.h \
    historymanager.h \
    trash.h

OTHER_FILES += \
    TODO.txt

RESOURCES +=
