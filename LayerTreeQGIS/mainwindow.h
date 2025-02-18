#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "qgsmapcanvas.h"
#include "qgsvectorlayer.h"
#include "qgsrasterlayer.h"
#include "qgslayertree.h"
#include "qgslayertreeview.h"
#include "qgslayertreemodel.h"
#include "qgscheckablecombobox.h"
#include "qgslayertreeviewitemdelegate.h"
#include "qgslayertreeviewindicator.h"
#include <QToolTip>
#include <QPoint>

#include <QBrush>
#include <QHelpEvent>
#include <QMenu>
#include <QPen>
#include <QToolTip>
#include "datamanager.h"
#include "qgscustomlayerorderwidget.h"
#include "qgslayertreemapcanvasbridge.h"
#include "qgsmapoverviewcanvas.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QgsMapCanvas *canvas;
    QgsLayerTreeView *layertreeview;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};


#include <QStandardItemModel>
#include <QStandardItem>
#include <QCheckBox>
#include <QItemDelegate>
#include <QAbstractItemDelegate>
#include <QStyledItemDelegate>

#include <QAbstractItemDelegate>
#include <QPainter>
#include <QCheckBox>
#include <QStyleOptionButton>

#include <QApplication>

#include <QObject>



class CheckBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CheckBoxItemDelegate()
    {
        mLayerTreeView = DataManager::instance()->layertreeview;
        connect( mLayerTreeView, &QgsLayerTreeView::clicked, this, &CheckBoxItemDelegate::onClicked );
    }

    void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const override
    {

        QStyleOptionViewItem newopt = option;
        newopt.rect.setX(option.rect.x()+20);
        QStyledItemDelegate::paint( painter, newopt, index );

        QgsLayerTreeNode *node = mLayerTreeView->index2node( index );
        if ( !node )
            return;
        QStyleOptionViewItem opt = option;
        initStyleOption( &opt, index );

        const QColor baseColor = opt.palette.base().color();
        QRect tRect = mLayerTreeView->style()->subElementRect( QStyle::SE_ItemViewItemText, &opt, mLayerTreeView );

        bool checked = node->itemVisibilityChecked();
        QRect cbRect = option.rect;
        // tRect.setX(tRect.x()+20);
        QStyleOptionButton checkBoxStyleOption;
        checkBoxStyleOption.state = checked ? QStyle::State_On : QStyle::State_Off;
        checkBoxStyleOption.rect = QRect(cbRect.x() , cbRect.y(), 20, cbRect.height());
        checkBoxStyleOption.styleObject = QApplication::style();

        // painter->fillRect(option.rect,QBrush(Qt::blue));

        // Set the palette for the checkbox (to change the border color)
        QPalette palette = checkBoxStyleOption.palette;
        palette.setColor(QPalette::Button, Qt::red); // Set the button color (which affects the border)
        checkBoxStyleOption.palette = palette;
        QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkBoxStyleOption, painter);

        const bool shouldShowLayerMark = tRect.left() < 0; // Layer/group node icon not visible anymore?
        if ( shouldShowLayerMark )
        {
            const int tPadding = tRect.height() / 10;
            const QRect mRect( mLayerTreeView->viewport()->rect().right() - mLayerTreeView->layerMarkWidth(), tRect.top() + tPadding, mLayerTreeView->layerMarkWidth(), tRect.height() - tPadding * 2 );
            const QBrush pb = painter->brush();
            const QPen pp = painter->pen();
            painter->setPen( QPen( Qt::NoPen ) );
            QBrush b = QBrush( opt.palette.mid() );
            QColor bc = b.color();
            // mix mid color with base color for a less dominant, yet still opaque, version of the color
            bc.setRed( static_cast<int>( bc.red() * 0.3 + baseColor.red() * 0.7 ) );
            bc.setGreen( static_cast<int>( bc.green() * 0.3 + baseColor.green() * 0.7 ) );
            bc.setBlue( static_cast<int>( bc.blue() * 0.3 + baseColor.blue() * 0.7 ) );
            b.setColor( bc );
            painter->setBrush( b );
            painter->drawRect( mRect );
            painter->setBrush( pb );
            painter->setPen( pp );
        }

        const QList<QgsLayerTreeViewIndicator *> indicators = mLayerTreeView->indicators( node );
        if ( indicators.isEmpty() )
            return;

        const QRect indRect = mLayerTreeView->style()->subElementRect( static_cast<QStyle::SubElement>( QgsLayerTreeViewProxyStyle::SE_LayerTreeItemIndicator ), &opt, mLayerTreeView );
        const int spacing = indRect.height() / 10;
        const int h = indRect.height();
        int x = indRect.left();


        for ( QgsLayerTreeViewIndicator *indicator : indicators )
        {
            const QRect rect( x + spacing, indRect.top() + spacing, h - spacing * 2, h - spacing * 2 );
            // Add a little more padding so the icon does not look misaligned to background
            const QRect iconRect( x + spacing * 2, indRect.top() + spacing * 2, h - spacing * 4, h - spacing * 4 );
            x += h;

            QIcon::Mode mode = QIcon::Normal;
            if ( !( opt.state & QStyle::State_Enabled ) )
                mode = QIcon::Disabled;
            else if ( opt.state & QStyle::State_Selected )
                mode = QIcon::Selected;

            // Draw indicator background, for when floating over text content
            const qreal bradius = spacing;
            const QBrush pb = painter->brush();
            const QPen pp = painter->pen();
            QBrush b = QBrush( opt.palette.midlight() );
            QColor bc = b.color();
            bc.setRed( static_cast<int>( bc.red() * 0.3 + baseColor.red() * 0.7 ) );
            bc.setGreen( static_cast<int>( bc.green() * 0.3 + baseColor.green() * 0.7 ) );
            bc.setBlue( static_cast<int>( bc.blue() * 0.3 + baseColor.blue() * 0.7 ) );
            b.setColor( bc );
            painter->setBrush( b );
            painter->setPen( QPen( QBrush( opt.palette.mid() ), 0.25 ) );
            painter->drawRoundedRect( rect, bradius, bradius );
            painter->setBrush( pb );
            painter->setPen( pp );

            indicator->icon().paint( painter, iconRect, Qt::AlignCenter, mode );
        }
    }

    static void _fixStyleOption( QStyleOptionViewItem &opt )
    {
       opt.showDecorationSelected = true;
    }
    bool helpEvent( QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index ) override
    {
        if ( event && event->type() == QEvent::ToolTip )
        {
            QgsLayerTreeNode *node = mLayerTreeView->index2node( index );
            if ( node )
            {
                const QList<QgsLayerTreeViewIndicator *> indicators = mLayerTreeView->indicators( node );
                if ( !indicators.isEmpty() )
                {
                    QStyleOptionViewItem opt = option;
                    initStyleOption( &opt, index );
                    _fixStyleOption( opt );

                    const QRect indRect = mLayerTreeView->style()->subElementRect( static_cast<QStyle::SubElement>( QgsLayerTreeViewProxyStyle::SE_LayerTreeItemIndicator ), &opt, mLayerTreeView );

                    if ( indRect.contains( event->pos() ) )
                    {
                        const int indicatorIndex = ( event->pos().x() - indRect.left() ) / indRect.height();
                        if ( indicatorIndex >= 0 && indicatorIndex < indicators.count() )
                        {
                            const QString tooltip = indicators[indicatorIndex]->toolTip();
                            if ( !tooltip.isEmpty() )
                            {
                                QToolTip::showText( event->globalPos(), tooltip, view );
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return QStyledItemDelegate::helpEvent( event, view, option, index );
    }

private slots:
    void onClicked( const QModelIndex &index )
    {
        qDebug()<<"clicked";
        QgsLayerTreeNode *node = mLayerTreeView->index2node( index );
        if ( !node )
            return;

        // qDebug()<<node->name()<<node->isVisible()<<node->itemVisibilityChecked();
        // node->setItemVisibilityCheckedRecursive(!node->isItemVisibilityCheckedRecursive());
        node->setItemVisibilityChecked(!node->itemVisibilityChecked());

        // qDebug()<<node->name()<<node->isVisible()<<node->itemVisibilityChecked();

        // qDebug()<<"-----------------";
        QList<QgsMapLayer *> layerlist;
        for(QgsMapLayer *mplayer :  QgsProject::instance()->layerTreeRoot()->checkedLayers()){
            layerlist.append(mplayer);
        }
        DataManager::instance()->mCanvas->setLayers(layerlist);


    }

private:
    QgsLayerTreeView *mLayerTreeView;
};


/*
class CheckBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CheckBoxItemDelegate(QObject *parent = nullptr)
    {

    }

    // Override paint method to render the checkbox
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        bool checked = index.data(Qt::CheckStateRole).toBool();
        qDebug()<<index.data(Qt::CheckStateRole)<<"painter";
        // Define the checkbox style option
        QStyleOptionButton checkBoxStyleOption;
        checkBoxStyleOption.state = checked ? QStyle::State_On : QStyle::State_Off;
        checkBoxStyleOption.rect = option.rect;

        // Draw the checkbox
        QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkBoxStyleOption, painter);

    }

    // Create the checkbox editor when item is clicked
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QCheckBox *editor = new QCheckBox(parent);
        return editor;
    }

    // Set data when the checkbox is clicked
    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        bool checked = index.data(Qt::CheckStateRole).toBool();
        QCheckBox *checkBoxEditor = static_cast<QCheckBox *>(editor);
        checkBoxEditor->setChecked(checked);
    }

    // Update the model when the checkbox state changes
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
    {
        QCheckBox *checkBoxEditor = static_cast<QCheckBox *>(editor);
        bool checked = checkBoxEditor->isChecked();
        model->setData(index, checked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);

    }

    // Handle the event when the checkbox is clicked
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        editor->setGeometry(option.rect);
    }

};


*/
// class MyDelegate : public QAbstractItemDelegate
// {
// public :
//     MyDelegate(QObject *parent =0);
//     QWidget *createEditor(QWidget *parent,
//                                   const QStyleOptionViewItem &option,
//                                   const QModelIndex &index) const
//     {
//         QCheckBox *checkbox = new QCheckBox(parent);
//         return checkbox;
//     }


//     void setEditorData(QWidget *editor, const QModelIndex &index) const
//     {
//         int value  = index.model()->data(index,Qt::EditRole).toInt();
//         QCheckBox *checkbox  = static_cast<QCheckBox *>(editor);
//         checkbox->setChecked(value);
//     }
//     void setModelData(QWidget *editor,
//                               QAbstractItemModel *model,
//                               const QModelIndex &index) const
//     {
//         QCheckBox *checkbox  = static_cast<QCheckBox *>(editor);
//         model->setData(index,checkbox->isChecked(),Qt::EditRole);
//     }
//     virtual void updateEditorGeometry(QWidget *editor,
//                                       const QStyleOptionViewItem &option,
//                                       const QModelIndex &index) const
//     {
//         editor->setGeometry(option.rect);
//     }

// };

#endif // MAINWINDOW_H
