TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
    commandargs.cpp \
    databasecolumn.cpp \
    databasequerry.cpp \
    main.cpp \
    database.cpp

HEADERS += \
    commandargs.h \
    databasecolumn.h \
    database.h \
    databasename.h \
    databasequerry.h


QT += sql
QT -= gui

