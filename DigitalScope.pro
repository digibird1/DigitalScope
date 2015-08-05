TEMPLATE = app
CONFIG += console

#CONFIG -= app_bundle

CONFIG+=debug

QT = gui core
QT       += network
include(./qextserialport-1.2rc/src/qextserialport.pri)

SOURCES += main.cpp \
    serialmain.cpp \
    scopedatamanager.cpp \
    scopedisplay.cpp \
    trigger.cpp \
    controlpannel.cpp \
    fftwidget.cpp \
    plot.cpp \
    client.cpp \
    DataStructure.cpp \
    runoctavescript.cpp


HEADERS += \
    serialmain.h \
    scopedatamanager.h \
    DataStructure.h \
    scopedisplay.h \
    trigger.h \
    controlpannel.h \
    fftwidget.h \
    plot.h \
    client.h \
    runoctavescript.h

#INCLUDEPATH +=kiss_fft130
#SOURCES += kiss_fft130/kiss_fft.c
#LIBS += -L../DigitalScope/qrealfourier-0.2.0-source/code/build -Lqrealfourier-0.2.0-source/code/build -lqrealfourier


#LIBS += -lqwt

#INCLUDEPATH += /usr/include/qwt

INCLUDEPATH +=qwt-6.1/src
LIBS += -L./qwt-6.1/lib -L../DigitalScope/qwt-6.1/lib -lqwt

#FFTW library and C++ wrapper files
LIBS +=-L/usr/lib -lfft -l2Dfft -lfftw3

#Octave
INCLUDEPATH += /usr/include/octave-3.6.4
LIBS += -L/usr/lib/x86_64-linux-gnu -loctinterp -loctave #-lcruft


