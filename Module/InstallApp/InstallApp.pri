#InstallApp.pri
QT += core gui widgets

SOURCES += \
    $$PWD/InstallApp.cpp\
    $$PWD/InstallMongo.cpp \
    $$PWD/InstallNotepad.cpp \
    $$PWD/InstallODBC.cpp \
    $$PWD/InstallSQL.cpp\
    $$PWD/InstallSSMS.cpp \
    $$PWD/InstallVcredist.cpp

HEADERS += $$PWD/InstallApp.h \
    $$PWD/InstallMongo.h \
    $$PWD/InstallNotepad.h \
    $$PWD/InstallODBC.h \
    $$PWD/InstallSQL.h\
    $$PWD/InstallSSMS.h \
    $$PWD/InstallVcredist.h



INCLUDEPATH += $$PWD

FORMS += \
    $$PWD/InstallApp.ui

