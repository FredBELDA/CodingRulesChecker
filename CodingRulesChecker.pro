#-------------------------------------------------
#
# Project created by QtCreator 2020-01-31T13:29:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodingRulesChecker
TEMPLATE = app

SOURCES += main.cpp\
    aboutdialog.cpp \
    abstractverifconfigfiles.cpp \
    abstractveriffiles.cpp \
    abstractveriffilerules.cpp \
    abstractcfamilyveriffiles.cpp \
    cveriffile.cpp \
    cppveriffile.cpp \
    hveriffile.cpp \
    iniveriffile.cpp \
    javaveriffile.cpp \
    mainwindow.cpp \
    report.cpp \
    rulechoicedialog.cpp \
    ruledialog.cpp \
    utils.cpp \
    verifyaccolade.cpp \
    verifycamelcase.cpp \
    verifyconditions.cpp \
    verifyhfile.cpp \
    verifymagicnumber.cpp \
    verifyorphanfunctions.cpp \
    verifypointer.cpp \
    verifytodo.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    abstractverifconfigfiles.h \
    abstractveriffiles.h \
    abstractveriffilerules.h \
    abstractcfamilyveriffiles.h \
    commonelements.h \
    cveriffile.h \
    cppveriffile.h \
    hveriffile.h \
    iniveriffile.h \
    javaveriffile.h \
    report.h \
    rulechoicedialog.h \
    ruledialog.h \
    utils.h \
    verifyaccolade.h \
    verifycamelcase.h \
    verifyconditions.h \
    verifyhfile.h \
    verifymagicnumber.h \
    verifyorphanfunctions.h \
    verifypointer.h \
    verifytodo.h

FORMS    += mainwindow.ui \
    ruledialog.ui \
    aboutdialog.ui \
    rulechoicedialog.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
