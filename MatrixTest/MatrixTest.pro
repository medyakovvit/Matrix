QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -L$$PWD/../dependencies/armadillo-9.800.3/lib \
        -larmadillo

INCLUDEPATH += $$PWD/../dependencies/armadillo-9.800.3/include

SOURCES +=  tst_matrix.cpp

HEADERS += \
    ../MatrixLib/Matrix.h
