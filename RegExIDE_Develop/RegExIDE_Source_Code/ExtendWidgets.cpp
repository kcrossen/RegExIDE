/****************************************************************************
**
** Copyright (C) 2016 Ken Crossen
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Redistributions in source code or binary form may not be sold.
**
****************************************************************************/

#include "ExtendWidgets.h"

// TreeWidget definition

TreeWidget::TreeWidget ( QWidget* parent ) : QTreeWidget ( parent ) {
    // Mechanism to make right clicks useful in same way as left clicks
    connect(this, SIGNAL(pressed(QModelIndex)), this, SLOT(onPressed(QModelIndex)));
    connect(this, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(onItemPressed(QTreeWidgetItem*, int)));
    Context_Menu = true;
    Detail_Splitter = 0;
}

void
TreeWidget::mouseDoubleClickEvent ( QMouseEvent* event ) {
    if (Detail_Splitter == 0) return;

    QList <int> split_sizes = Detail_Splitter->sizes();

    if (split_sizes.count() >= 2) {
        if (split_sizes[1] == 0)
            Detail_Splitter->setSizes(Detail_Splitter->Open_Sizes);
        else
            Detail_Splitter->setSizes(Detail_Splitter->Closed_Sizes);
    }

    event->accept();
    return;
}

QModelIndexList
TreeWidget::Selected_Indexes ( ) {
    return selectedIndexes();
}

void
TreeWidget::mouseReleaseEvent ( QMouseEvent *event ) {
    Mouse_Button_Clicked = event->button();

    // Pass on buttons to base class
    QTreeWidget::mouseReleaseEvent(event);

    // Mechanism to make right clicks useful in same way as left clicks
    if (Mouse_Button_Clicked == Qt::RightButton) {
        if (Context_Menu) {
            emit rightClicked(Clicked_Model_Index);
            emit itemRightClicked(Clicked_Tree_Widget_Item, Clicked_Tree_Widget_Column);
        }
        else emit clicked(Clicked_Model_Index);
    }
}

void
TreeWidget::onPressed ( const QModelIndex &model_index ) {
    // Mechanism to make right clicks useful in same way as left clicks
    Clicked_Model_Index = model_index;
}

void
TreeWidget::onItemPressed ( QTreeWidgetItem *item,
                            int column ) {
    // Mechanism to make right clicks useful in same way as left clicks
    Clicked_Tree_Widget_Item = item;
    Clicked_Tree_Widget_Column = column;
}


// TabWidget Definition

TabWidget::TabWidget ( QWidget* parent ) : QTabWidget ( parent ) {
    tabBar()->installEventFilter(this);
}

bool
TabWidget::eventFilter ( QObject* , QEvent* event ) {
    if (event->type() == QEvent::Wheel) {
        // qDebug() << "Wheel event blocked";
        // We don't want this event handled, default behavior is an annoyance
        return true;
    }

    // Handle the rest with default behavior
    return false;
}

// Label definition

Label::Label ( QWidget* parent ) : QLabel ( parent ) {
    QPalette lbl_palette = this->palette();
    lbl_palette.setColor(QPalette::Background, QColor(208, 240, 255));
    this->setAutoFillBackground(true);
    this->setPalette(lbl_palette);
}

// Frame definition

Frame::Frame ( QWidget *parent ) : QFrame ( parent ) {
    setFrameStyle(QFrame::NoFrame);
    setContentsMargins(0, 0, 0, 0);
}

// HBoxLayout definition

HBoxLayout::HBoxLayout ( QWidget *parent ) : QHBoxLayout ( parent ) {
    setMargin(0);
    setContentsMargins(0, 0, 0, 0);
    setSpacing(0);
}

// VBoxLayout definition

VBoxLayout::VBoxLayout ( QWidget *parent ) : QVBoxLayout ( parent ) {
    setMargin(0);
    setContentsMargins(0, 0, 0, 0);
    setSpacing(0);
}

// Splitter definition

Splitter::Splitter ( QWidget *parent ) : QSplitter ( parent ) {
    setContentsMargins(0, 0, 0, 0);
}

Splitter::Splitter ( Qt::Orientation orientation, QWidget *parent ) : QSplitter ( orientation, parent ) {
    setContentsMargins(0, 0, 0, 0);
}

// Splitter/SplitterHandle Object Definition
// Implements double click to open/close right (bottom) split.
// Left (top) remains partially or fully open.

DetailSplitterHandle::DetailSplitterHandle ( Qt::Orientation orientation, DetailSplitter* parent ) :
    QSplitterHandle ( orientation, parent ) {
}

void
DetailSplitterHandle::mouseDoubleClickEvent ( QMouseEvent* event ) {
    QList <int> split_sizes = splitter()->sizes();

    DetailSplitter* parent = dynamic_cast<DetailSplitter*>(this->parent());

    if (split_sizes.count() >= 2) {
        if (split_sizes[1] == 0) {
            splitter()->setSizes(parent->Open_Sizes);
        }
        else {
            splitter()->setSizes(parent->Closed_Sizes);
        }
    }

    event->accept();
    return;
}

DetailSplitter::DetailSplitter ( QWidget* parent ) : QSplitter ( parent ) {
    installEventFilter(this);
}

DetailSplitter::DetailSplitter ( Qt::Orientation orientation, QWidget* parent ) : QSplitter ( orientation, parent ) {
    installEventFilter(this);
}

void
DetailSplitter::setOpenSizes ( QList <int> set_sizes ) {
    Open_Sizes = set_sizes;
}

void
DetailSplitter::setClosedSizes ( QList <int> set_sizes ) {
    Closed_Sizes = set_sizes;
}


QSplitterHandle*
DetailSplitter::createHandle ( ) {
    return new DetailSplitterHandle(orientation(), this);
}
