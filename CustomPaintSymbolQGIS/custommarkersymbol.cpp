#include "custommarkersymbol.h"

CustomMarkerSymbol::CustomMarkerSymbol() {
    this->setShape(Qgis::MarkerShape::Triangle);
    this->setSize(5);
}

QgsSimpleMarkerSymbolLayer *CustomMarkerSymbol::clone() const {
    return new CustomMarkerSymbol(*this);
}

void CustomMarkerSymbol::renderPoint(QPointF point, QgsSymbolRenderContext& context)  {
    QPainter* painter = context.renderContext().painter();
    if (!painter) return;

    // Save the painter state
    painter->save();

    // Set the pen and brush for drawing
    QPen pen(Qt::black, 2);  // Black outline with 2px width
    QBrush brush(Qt::gray, Qt::SolidPattern);  // Drone body color (gray)
    painter->setPen(pen);
    painter->setBrush(brush);

    // Set the origin to the center of the drone
    painter->translate(point);  // Move origin to the center of the drone

    double rotationAngle = context.feature()->attribute("angle").toDouble();
    // qDebug()<<" : "<<context.feature()->id()<<": "<<rotationAngle;
    m_rotationAngle = rotationAngle;
    // Rotate the drone's body and propellers by the rotation angle
    painter->rotate(m_rotationAngle);  // Rotate by the current angle

    // Draw the body of the drone (a circle in this case)
    painter->drawEllipse(QPointF(0, 0), 10, 10);  // 10px radius for the drone body

    // Draw the four propellers (rotated along with the drone)
    QBrush propellerBrush(Qt::darkGray, Qt::SolidPattern); // Propeller color (dark gray)
    painter->setBrush(propellerBrush);

    // Top-left propeller
    painter->rotate(45);  // Rotate by 45 degrees for the top-left propeller
    painter->drawRect(-3, -15, 6, 3);  // Propeller as a small rectangle

    // Top-right propeller
    painter->rotate(90);  // Rotate by another 90 degrees for the top-right propeller
    painter->drawRect(-3, -15, 6, 3);

    // Bottom-right propeller
    painter->rotate(90);  // Rotate by another 90 degrees for the bottom-right propeller
    painter->drawRect(-3, -15, 6, 3);

    // Bottom-left propeller
    painter->rotate(90);  // Rotate by another 90 degrees for the bottom-left propeller
    painter->drawRect(-3, -15, 6, 3);

    // Draw the head sign (top of the drone)
    painter->resetTransform();  // Reset the transformation (to prevent rotation interference)
    painter->translate(point);  // Move origin back to the center of the drone

    // Rotate the head sign independently from the drone's body
    painter->rotate(m_rotationAngle);  // Apply the head rotation angle

    QBrush headSignBrush(Qt::blue, Qt::SolidPattern);  // Color of the head sign
    painter->setBrush(headSignBrush);
    painter->setPen(QPen(Qt::black));  // Black outline for the head sign

    // Draw a small circle on top of the drone's body to represent the head sign
    painter->drawEllipse(QPointF(0, -12), 4, 4);  // Position above the body

    // Optional: Draw a text label for the head sign (optional, if you prefer text)
    QFont font = painter->font();
    font.setPointSize(8);  // Set font size for the label
    painter->setFont(font);
    painter->setPen(Qt::black);  // Use black color for the text
    // painter->drawText(QPointF(-5, -15), "H");  // Draw the letter "H" as the head sign

    // Restore the painter state
    painter->restore();
}


void CustomMarkerSymbol::rotateDrone(double angle)
{
    m_rotationAngle = angle;


}

