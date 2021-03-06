/***************************************************************************
         qgsvectorfieldsymbollayer.h
         -------------------------
  begin                : Octorer 25, 2011
  copyright            : (C) 2011 by Marco Hugentobler
  email                : marco dot hugentobler at sourcepole dot ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSVECTORFIELDSYMBOLLAYER_H
#define QGSVECTORFIELDSYMBOLLAYER_H

#include "qgssymbollayer.h"

/** \ingroup core
 * A symbol layer class for displaying displacement arrows based on point layer attributes*/
class CORE_EXPORT QgsVectorFieldSymbolLayer: public QgsMarkerSymbolLayer
{
  public:
    enum VectorFieldType
    {
      Cartesian = 0,
      Polar,
      Height
    };

    enum AngleOrientation
    {
      ClockwiseFromNorth = 0,
      CounterclockwiseFromEast
    };

    enum AngleUnits
    {
      Degrees = 0,
      Radians
    };

    QgsVectorFieldSymbolLayer();
    ~QgsVectorFieldSymbolLayer();

    static QgsSymbolLayer* create( const QgsStringMap& properties = QgsStringMap() );
    static QgsSymbolLayer* createFromSld( QDomElement &element );

    QString layerType() const override { return "VectorField"; }

    bool setSubSymbol( QgsSymbol* symbol ) override;
    QgsSymbol* subSymbol() override { return mLineSymbol; }

    void setColor( const QColor& color ) override;
    virtual QColor color() const override;

    void renderPoint( QPointF point, QgsSymbolRenderContext& context ) override;
    void startRender( QgsSymbolRenderContext& context ) override;
    void stopRender( QgsSymbolRenderContext& context ) override;

    QgsVectorFieldSymbolLayer* clone() const override;
    QgsStringMap properties() const override;

    void toSld( QDomDocument& doc, QDomElement &element, const QgsStringMap& props ) const override;

    void drawPreviewIcon( QgsSymbolRenderContext& context, QSize size ) override;

    QSet<QString> usedAttributes() const override;

    //setters and getters
    void setXAttribute( const QString& attribute ) { mXAttribute = attribute; }
    QString xAttribute() const { return mXAttribute; }
    void setYAttribute( const QString& attribute ) { mYAttribute = attribute; }
    QString yAttribute() const { return mYAttribute; }
    void setScale( double s ) { mScale = s; }
    double scale() const { return mScale; }
    void setVectorFieldType( VectorFieldType type ) { mVectorFieldType = type; }
    VectorFieldType vectorFieldType() const { return mVectorFieldType; }
    void setAngleOrientation( AngleOrientation orientation ) { mAngleOrientation = orientation; }
    AngleOrientation angleOrientation() const { return mAngleOrientation; }
    void setAngleUnits( AngleUnits units ) { mAngleUnits = units; }
    AngleUnits angleUnits() const { return mAngleUnits; }

    void setOutputUnit( QgsUnitTypes::RenderUnit unit ) override;
    QgsUnitTypes::RenderUnit outputUnit() const override;

    void setMapUnitScale( const QgsMapUnitScale& scale ) override;
    QgsMapUnitScale mapUnitScale() const override;

    /** Sets the units for the distance.
     * @param unit distance units
     * @see distanceUnit()
    */
    void setDistanceUnit( QgsUnitTypes::RenderUnit unit ) { mDistanceUnit = unit; }

    /** Returns the units for the distance.
     * @see setDistanceUnit()
    */
    QgsUnitTypes::RenderUnit distanceUnit() const { return mDistanceUnit; }

    void setDistanceMapUnitScale( const QgsMapUnitScale& scale ) { mDistanceMapUnitScale = scale; }
    const QgsMapUnitScale& distanceMapUnitScale() const { return mDistanceMapUnitScale; }

  private:
    QString mXAttribute;
    QString mYAttribute;
    QgsUnitTypes::RenderUnit mDistanceUnit;
    QgsMapUnitScale mDistanceMapUnitScale;
    double mScale;
    VectorFieldType mVectorFieldType;
    AngleOrientation mAngleOrientation;
    AngleUnits mAngleUnits;

    QgsLineSymbol* mLineSymbol;

    //Attribute indices are resolved in startRender method
    int mXIndex;
    int mYIndex;

    //Converts length/angle to cartesian x/y
    void convertPolarToCartesian( double length, double angle, double& x, double& y ) const;
};

#endif // QGSVECTORFIELDSYMBOLLAYER_H


