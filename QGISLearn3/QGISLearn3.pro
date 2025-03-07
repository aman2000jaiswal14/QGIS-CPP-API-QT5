QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
INCLUDEPATH += /usr/local/include/qgis
LIBS += -L/usr/local/lib -lqgis_core -lqgis_gui -lqgis_app -lqgis_analysis -lqgisgrass8 -lqgis_native
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    custommapcanvas.cpp \
    drawpointtool.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    custommapcanvas.h \
    drawpointtool.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
