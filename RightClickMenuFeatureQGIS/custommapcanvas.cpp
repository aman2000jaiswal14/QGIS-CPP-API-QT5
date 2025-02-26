#include "custommapcanvas.h"

#include <QMenu>
#include <QMouseEvent>
#include <qgsvectorlayer.h>
#include <qgsfeature.h>
#include "qgswkbtypes.h"

CustomMapCanvas::CustomMapCanvas(QWidget* parent)
    : QgsMapCanvas(parent) {
    // Constructor implementation
}

void CustomMapCanvas::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        qDebug() << "Right button clicked";

        // Get the map point under the cursor
        QgsPointXY mapPoint = getCoordinateTransform()->toMapCoordinates(event->pos());
        QgsVectorLayer* layer = (QgsVectorLayer*)this->layer(1);

        if (layer && layer->geometryType() == Qgis::GeometryType::Point) {
            qDebug() << "Point geometry detected";

            // Calculate the search rectangle size based on the current map scale
            double scale = this->scale(); // Get the current map scale
            double searchRectSize = scale / 30000000; // Adjust the size based on scale

            // Define the search rectangle around the clicked point
            QgsRectangle searchRect(
                mapPoint.x() - searchRectSize,
                mapPoint.y() - searchRectSize,
                mapPoint.x() + searchRectSize,
                mapPoint.y() + searchRectSize
                );

            qDebug() << "Search rect:" << searchRect.toString() << searchRectSize;

            // Collect all features within the search rectangle
            QList<QgsFeature> features;
            QgsFeatureRequest request;
            request.setFilterRect(searchRect);
            QgsFeatureIterator it = layer->getFeatures(request);

            QgsFeature feature;
            while (it.nextFeature(feature)) {
                features.append(feature);
                qDebug() << "Found feature ID:" << feature.id();
            }

            if (!features.isEmpty()) {
                // If only one feature is found, directly show the context menu
                if (features.size() == 1) {
                    QgsFeature selectedFeature = features[0];

                    // Create a context menu
                    QMenu contextMenu(this);
                    QAction* openAction = contextMenu.addAction("Open");
                    QAction* closeAction = contextMenu.addAction("Close");

                    // Connect actions to slots and pass the feature
                    connect(openAction, &QAction::triggered, this, [this, selectedFeature]() { onOpen(selectedFeature); });
                    connect(closeAction, &QAction::triggered, this, [this, selectedFeature]() { onClose(selectedFeature); });

                    // Show the context menu
                    contextMenu.exec(event->globalPos());
                } else {
                    // If multiple features are found, show a list to the user
                    QStringList featureNames;
                    for (const QgsFeature& feat : features) {
                        featureNames.append(QString("Feature ID: %1").arg(feat.id()));
                    }

                    bool ok;
                    QString selectedFeatureName = QInputDialog::getItem(
                        this, "Select Feature", "Multiple features found. Please select one:",
                        featureNames, 0, false, &ok
                        );

                    if (ok && !selectedFeatureName.isEmpty()) {
                        // Find the selected feature
                        int index = featureNames.indexOf(selectedFeatureName);
                        if (index >= 0) {
                            QgsFeature selectedFeature = features[index];

                            // Create a context menu
                            QMenu contextMenu(this);
                            QAction* openAction = contextMenu.addAction("Open");
                            QAction* closeAction = contextMenu.addAction("Close");

                            // Connect actions to slots and pass the feature
                            connect(openAction, &QAction::triggered, this, [this, selectedFeature]() { onOpen(selectedFeature); });
                            connect(closeAction, &QAction::triggered, this, [this, selectedFeature]() { onClose(selectedFeature); });

                            // Show the context menu
                            contextMenu.exec(event->globalPos());
                        }
                    }
                }
            } else {
                qDebug() << "No features found under cursor";
            }
        }
    }
    QgsMapCanvas::mousePressEvent(event);
}
void CustomMapCanvas::onOpen(const QgsFeature& feature) {
    qDebug() << "Open action triggered for feature ID:" << feature.id();
    // You can now access the feature's attributes or geometry here
    qDebug() << "Feature attributes:" << feature.id();
}

void CustomMapCanvas::onClose(const QgsFeature& feature) {
    qDebug() << "Close action triggered for feature ID:" << feature.id();
    // You can now access the feature's attributes or geometry here
    qDebug() << "Feature attributes:" << feature.id();
}
