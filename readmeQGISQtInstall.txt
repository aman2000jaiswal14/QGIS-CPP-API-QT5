PART A. STEPS INSTALL QT
1.
sudo apt install libxcb-cursor0 libxcb-cursor-dev
2.
./qt-online-installer-linux-x64-4.8.1.run --mirror http://www.nic.funet.fi/pub/mirrors/download.qt-project.org
3.
chose 5.15.1 version of qt from archive filter in online installer


PART B. QGIS setup

STEPS
1.
sudo apt install gnupg software-properties-common
sudo mkdir -m755 -p /etc/apt/keyrings  # not needed since apt version 2.4.0 like Debian 12 and Ubuntu 22 or newer
sudo wget -O /etc/apt/keyrings/qgis-archive-keyring.gpg https://download.qgis.org/downloads/qgis-archive-keyring.gpg

2. CREATE A FILE AT which is a repo: ->  qgis.sources  (NOTE: In content Suites codename found by typing in terminal ->1. lsb_release -cs   or
														       2.   . /etc/os-release; echo "$UBUNTU_CODENAME"

CONTENT:->
Types: deb deb-src
URIs: https://qgis.org/debian
Suites: your-distributions-codename
Architectures: amd64
Components: main
Signed-By: /etc/apt/keyrings/qgis-archive-keyring.gpg

3. 
sudo apt update
wget https://download.qgis.org/downloads/qgis-archive-keyring.gpg
gpg --no-default-keyring --keyring ./qgis-archive-keyring.gpg --list-keys

4.

sudo mkdir -m755 -p /etc/apt/keyrings  # not needed since apt version 2.4.0 like Debian 12 and Ubuntu 22 or newer
sudo cp qgis-archive-keyring.gpg /etc/apt/keyrings/qgis-archive-keyring.gpg

5.
sudo mkdir -m755 -p /etc/apt/keyrings  # not needed since apt version 2.4.0 like Debian 12 and Ubuntu 22 or newer
sudo wget -O /etc/apt/keyrings/qgis-archive-keyring.gpg https://download.qgis.org/downloads/qgis-archive-keyring.gpg


6.
sudo apt build-dep qgis

7.
   cd
   mkdir -p dev/cpp
   cd dev/cpp
   ls
   sudo apt install git
   sudo apt update
   clear
   git clone --depth 1 https://github.com/qgis/QGIS.git
   cd QGIS
   mkdir QGIS-BUILD
   cd QGIS-BUILD/
   
   sudo add-apt-repository ppa:ubuntugis/ubuntugis-unstable
   sudo apt-get update
   sudo apt-get install pdal
   
8.
   sudo apt-get install -y     apt-transport-https     ca-certificates     clazy     cmake     curl     dh-python     git     gdal-bin     gnupg     gpsbabel     graphviz     'libaio1|libaio1t64'     'libdraco4|libdraco8'     libexiv2-27     'libfcgi0ldbl|libfcgi0t64'     libgsl27     'libprotobuf-lite17|libprotobuf-lite23|libprotobuf-lite32t64'     libqca-qt5-2-plugins     libqt53dextras5     libqt53drender5     'libqt5concurrent5|libqt5concurrent5t64'     libqt5keychain1     libqt5positioning5     libqt5multimedia5     libqt5multimediawidgets5     libqt5qml5     libqt5quick5     libqt5quickcontrols2-5     libqt5quickwidgets5     libqt5serialport5     libqt5sql5-odbc     libqt5sql5-sqlite     'libqt5xml5|libqt5xml5t64'     libqt5webkit5     libqwt-qt5-6     libspatialindex6     libsqlite3-mod-spatialite     'libzip4|libzip5|libzip4t64'     lighttpd     locales     pdal     poppler-utils     python3-future     python3-gdal     python3-mock     python3-nose2     python3-numpy     python3-owslib     python3-pip     python3-psycopg2     python3-pyproj     python3-pyqt5     python3-pyqt5.qsci     python3-pyqt5.qtsql     python3-pyqt5.qtsvg     python3-pyqt5.qtwebkit     python3-pyqt5.qtpositioning     python3-pyqt5.qtmultimedia     python3-pyqt5.qtserialport     python3-sip     python3-termcolor     python3-yaml     qpdf     qt3d-assimpsceneimport-plugin     qt3d-defaultgeometryloader-plugin     qt3d-gltfsceneio-plugin     qt3d-scene2d-plugin     qt5-image-formats-plugins     saga     supervisor     unzip     xauth     xfonts-100dpi     xfonts-75dpi     xfonts-base     xfonts-scalable     xvfb     ocl-icd-libopencl1
   
   
9.
  AT QGIS-BUILD DIRECTORY. CLEAN IF ANY CMAKECACHE FILE IS THERE. AS THIS FOLDER MUST BE EMPTIED TO START BUILDING QGIS
  cmake ..
  make
  make install
 
 10.
 All the lib and include folder will be at path /usr/local (if not there during make install it will print the path of all include and lib folder)
 /usr/local/include/qgis
 /usr/local/lib
 
 
 PART C. QT and QGIS integration
 .pro file include these line below CONFIG += c17
 
 INCLUDEPATH += /usr/local/include/qgis

 LIBS += -L/usr/local/lib -lqgis_core -lqgis_gui -lqgis_app
 
 
 Sample application.
 
 .pro file ->
 
QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
INCLUDEPATH += /usr/local/include/qgis

LIBS += -L/usr/local/lib -lqgis_core -lqgis_gui -lqgis_app
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



main.cpp ->


#include <QApplication>
#include "qgsapplication.h"
#include "qgsmapcanvas.h"
#include "qgsproviderregistry.h"
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[]) {
    // 1. Create QApplication FIRST (Crucial!)
    QApplication a(argc, argv);  // This MUST be the very first Qt-related line

    // 2. QGIS Application Initialization
    QgsApplication* qgsApp = new QgsApplication(argc, argv, true);

    QString prefixPath = "/usr"; // Or your actual path
    qgsApp->setPrefixPath(prefixPath, true);

    qgsApp->init();

    // 3. Check Initialization (AFTER QApplication creation)
    if (QgsApplication::instance() == nullptr) {
        QMessageBox::critical(nullptr, "Error", "QGIS initialization failed!");
        return 1;
    }

    QStringList providers = QgsProviderRegistry::instance()->providerList();
    if (providers.isEmpty()) {
        QMessageBox::warning(nullptr, "Warning", "No QGIS providers found. Check prefix path.");
    } else {
        qDebug() << "Providers:" << providers;
    }

    QgsMapCanvas* mapCanvas = new QgsMapCanvas(); // Now safe to use QGIS/Qt classes
    if (mapCanvas == nullptr) {
        QMessageBox::critical(nullptr, "Error", "Failed to create map canvas.");
        delete qgsApp;
        return 1;
    }
    delete mapCanvas;

    // qDebug() << "QGIS Version:" << QGIS_VERSION; // Assuming you defined QGIS_VERSION in .pro

    QMessageBox::information(nullptr, "Success", "QGIS initialized successfully!");


    // 4. Your Application Logic Here...

    qgsApp->exit();

    return a.exec(); // Start the Qt event loop (important!)
}

  
   
   
   
   
   
