/***************************************************************************
    qgsunitselectionwidget.h
    -------------------
    begin                : Mar 24, 2014
    copyright            : (C) 2014 Sandro Mani
    email                : smani@sourcepole.ch

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef QGSUNITSELECTIONWIDGET_H
#define QGSUNITSELECTIONWIDGET_H

#include <QWidget>
#include "qgssymbol.h"
#include "ui_qgsunitselectionwidget.h"
#include "ui_qgsmapunitscaledialog.h"

class QgsMapCanvas;

/** \ingroup gui
 * Dialog allowing the user to choose the minimum and maximum scale of an object in map units */
class GUI_EXPORT QgsMapUnitScaleDialog : public QDialog, private Ui::QgsMapUnitScaleDialog
{
    Q_OBJECT

  public:
    QgsMapUnitScaleDialog( QWidget* parent = nullptr );

    /** Returns the map unit scale */
    QgsMapUnitScale getMapUnitScale() const;
    /** Sets the map unit scale */
    void setMapUnitScale( const QgsMapUnitScale& scale );

    /** Sets the map canvas associated with the dialog. This allows the dialog to retrieve the current
     * map scale from the canvas.
     * @param canvas map canvas
     * @note added in QGIS 2.12
     */
    void setMapCanvas( QgsMapCanvas* canvas );

  private slots:
    void configureMinComboBox();
    void configureMaxComboBox();

};

/** \ingroup gui
 * Widget displaying a combobox allowing the user to choose between millimeter and map units
 *  If the user chooses map units,  a button appears allowing the specification of minimum and maximum scale */
class GUI_EXPORT QgsUnitSelectionWidget : public QWidget, private Ui::QgsUnitSelectionWidget
{
    Q_OBJECT

  private:
    QgsMapUnitScaleDialog* mUnitScaleDialog;
    int mMapUnitIdx;

  public:
    QgsUnitSelectionWidget( QWidget* parent = nullptr );

    /** Sets the units which the user can choose from in the combobox.
     * @param units list of strings for custom units to display in the widget
     * @param mapUnitIdx specifies which entry corresponds to the map units, or -1 if none
     */
    void setUnits( const QStringList& units, int mapUnitIdx );

    /** Sets the units which the user can choose from in the combobox. Clears any existing units.
     * @param units list of valid units
     * @note added in QGIS 2.9
     */
    void setUnits( const QgsUnitTypes::RenderUnitList& units );

    /** Get the selected unit index */
    int getUnit() const { return mUnitCombo->currentIndex(); }

    /** Returns the current predefined selected unit (if applicable).
     * @returns selected output unit, or QgsUnitTypes::RenderUnknownUnit if the widget was populated with custom unit types
     * @note added in QGIS 2.9
     */
    QgsUnitTypes::RenderUnit unit() const;

    /** Sets the selected unit index
     * @param unitIndex index of unit to set as current
     * @note available in Python bindings as setUnitIndex
     */
    void setUnit( int unitIndex );

    /** Sets the selected unit
     * @param unit predefined unit to set as current
     */
    void setUnit( QgsUnitTypes::RenderUnit unit );

    /** Returns the map unit scale */
    QgsMapUnitScale getMapUnitScale() const { return mUnitScaleDialog->getMapUnitScale(); }

    /** Sets the map unit scale */
    void setMapUnitScale( const QgsMapUnitScale& scale ) { mUnitScaleDialog->setMapUnitScale( scale ); }

    /** Sets the map canvas associated with the widget. This allows the widget to retrieve the current
     * map scale from the canvas.
     * @param canvas map canvas
     * @note added in QGIS 2.12
     */
    void setMapCanvas( QgsMapCanvas* canvas );

  signals:
    void changed();

  private slots:
    void showDialog();
    void toggleUnitRangeButton();

};

#endif // QGSUNITSELECTIONWIDGET_H
