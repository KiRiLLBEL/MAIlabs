QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choice.cpp \
    directedge.cpp \
    directmatrix.cpp \
    directpaint.cpp \
    directpaintscene.cpp \
    directtable.cpp \
    directvertex.cpp \
    edge.cpp \
    item.cpp \
    main.cpp \
    matrix.cpp \
    myview.cpp \
    paint.cpp \
    paintscene.cpp \
    table.cpp \
    vertex.cpp \
    zoom.cpp

HEADERS += \
    choice.h \
    directedge.h \
    directmatrix.h \
    directpaint.h \
    directpaintscene.h \
    directtable.h \
    directvertex.h \
    edge.h \
    item.h \
    matrix.h \
    myview.h \
    paint.h \
    paintscene.h \
    table.h \
    vertex.h \
    zoom.h

FORMS += \
    choice.ui \
    directpaint.ui \
    directtable.ui \
    paint.ui \
    table.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
