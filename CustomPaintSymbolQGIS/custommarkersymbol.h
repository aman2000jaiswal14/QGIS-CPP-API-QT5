#ifndef CUSTOMMARKERSYMBOL_H
#define CUSTOMMARKERSYMBOL_H
#include "qgsmarkersymbollayer.h"
#include "qgsmarkersymbol.h"
class CustomMarkerSymbol : public QgsSimpleMarkerSymbolLayer
{
public:
    CustomMarkerSymbol();

    QgsSimpleMarkerSymbolLayer* clone() const override;

    void renderPoint(QPointF point, QgsSymbolRenderContext& context) override;
    void rotateDrone(double angle);
    double m_rotationAngle=0;
private :

};

#endif // CUSTOMMARKERSYMBOL_H
