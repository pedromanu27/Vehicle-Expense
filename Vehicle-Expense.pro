#-------------------------------------------------
#
# Project created by QtCreator 2019-12-27T11:40:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Vehicle-Expense
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        vehiclesdialog.cpp

HEADERS += \
        mainwindow.h \
        database.h \
        vehiclesdialog.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/qcustomplot/lib/ -lqcustomplot2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/qcustomplot/lib/ -lqcustomplotd2
else:unix: LIBS += -L$$PWD/libs/qcustomplot/lib/ -lqcustomplot2

INCLUDEPATH += $$PWD/libs/qcustomplot/include
DEPENDPATH += $$PWD/libs/qcustomplot/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/qsint/lib/ -lqsint
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/qsint/lib/ -lqsintd
else:unix: LIBS += -L$$PWD/libs/qsint/lib/ -lqsint

INCLUDEPATH += $$PWD/libs/qsint/include
DEPENDPATH += $$PWD/libs/qsint/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/LimeReport/lib/ -llimereport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/LimeReport/lib/ -llimereportd
else:unix: LIBS += -L$$PWD/libs/LimeReport/lib/ -llimereport

INCLUDEPATH += $$PWD/libs/LimeReport/include
DEPENDPATH += $$PWD/libs/LimeReport/include

DISTFILES += \
    appicon.rc

RC_FILE = appicon.rc
