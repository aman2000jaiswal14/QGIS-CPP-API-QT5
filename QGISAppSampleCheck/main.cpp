
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
