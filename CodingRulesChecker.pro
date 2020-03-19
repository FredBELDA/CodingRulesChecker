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
    abstractverifconfigfiles.cpp \
    hveriffile.cpp \
    mainwindow.cpp \
    abstractveriffiles.cpp \
    abstractveriffilerules.cpp \
    abstractcfamilyveriffiles.cpp \
    cveriffile.cpp \
    cppveriffile.cpp \
    javaveriffile.cpp \
    report.cpp \
    iniveriffile.cpp \
    ruledialog.cpp \
    verifyaccolade.cpp \
    verifycamelcase.cpp \
    verifyconditions.cpp \
    verifyhfile.cpp \
    verifymagicnumber.cpp \
    verifyorphanfunctions.cpp \
    verifypointer.cpp \
    verifytodo.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
    abstractverifconfigfiles.h \
    abstractveriffiles.h \
    abstractveriffilerules.h \
    abstractcfamilyveriffiles.h \
    commonelements.h \
    cveriffile.h \
    cppveriffile.h \
    hveriffile.h \
    javaveriffile.h \
    report.h \
    iniveriffile.h \
    ruledialog.h \
    verifyaccolade.h \
    verifycamelcase.h \
    verifyconditions.h \
    verifyhfile.h \
    verifymagicnumber.h \
    verifyorphanfunctions.h \
    verifypointer.h \
    verifytodo.h \
    utils.h

FORMS    += mainwindow.ui \
 ruledialog.ui

DISTFILES +=

RESOURCES += \
 resources.qrc
