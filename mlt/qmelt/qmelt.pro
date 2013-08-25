isEmpty(MLT_SOURCE) {
    error("qmelt can only be built when MLT_SOURCE is set to the MLT source code directory.")
}

include(../../common.pri)
TEMPLATE = app

SOURCES += qmelt.cpp
SOURCES += $$MLT_SOURCE/src/melt/melt.c
SOURCES += $$MLT_SOURCE/src/melt/io.c

DEFINES += main=melt_main
DEFINES += VERSION=\\\"qmelt\\\"

INCLUDEPATH += $$MLT_SOURCE

CONFIG -= app_bundle

macx {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6
    # QMake from Qt 5.1.0 on OSX is messing with the environment in which it runs
    # pkg-config such that the PKG_CONFIG_PATH env var is not set.
    isEmpty(MLT_PREFIX) {
        MLT_PREFIX = /opt/local
    }
    INCLUDEPATH += $$MLT_PREFIX/include/mlt
    LIBS += -L$$MLT_PREFIX/lib -lmlt
} else {
    CONFIG += link_pkgconfig
    PKGCONFIG += mlt-framework
}
win32 {
    CONFIG += console
    DEFINES += MELT_NOSDL
}

isEqual(QT_MAJOR_VERSION, 5) {
    QT += widgets
}

TARGET = qmelt
QMAKE_RPATHDIR += $$PREFIX/lib

target.path = $$PREFIX/bin
INSTALLS += target
