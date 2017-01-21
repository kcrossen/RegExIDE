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

#ifndef MYWIDGETS_H
#define MYWIDGETS_H

#include <QtCore>
#include <QtGui>
#include <QTreeWidget>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSplitter>
#include <QVariantMap>
#include <QMap>

#define initOpenSizes QList<int> () << 500 << 500
#define initClosedSizes QList<int> () << 1000 << 0

#define ToolBar_Button_Style "QToolButton:hover { border: 2px solid #8f8f91; border-radius: 4px; background-color: #dadbde; }"

class DetailSplitter;

class TreeWidget : public QTreeWidget {
    Q_OBJECT

public:
    TreeWidget ( QWidget* parent = 0 );

    DetailSplitter* Detail_Splitter;

    // Mechanism to make right clicks useful in same way as left clicks
    Qt::MouseButton Mouse_Button_Clicked;

    QModelIndex Clicked_Model_Index;

    QTreeWidgetItem *Clicked_Tree_Widget_Item;
    int Clicked_Tree_Widget_Column;

    bool Context_Menu;

    QModelIndexList
    Selected_Indexes ( );

protected:
    void
    mouseReleaseEvent ( QMouseEvent *event );

    void
    mouseDoubleClickEvent ( QMouseEvent* event );

private slots:
    // Mechanism to make right clicks useful in same way as left clicks
    void
    onPressed ( const QModelIndex &model_index );

    void
    onItemPressed ( QTreeWidgetItem *item,
                    int column );

signals:
    void
    rightClicked ( const QModelIndex &model_index );

    void
    itemRightClicked ( QTreeWidgetItem *item,
                       int column );

};

class Frame : public QFrame {
    Q_OBJECT

public:
    Frame ( QWidget *parent = 0 );

};

class HBoxLayout : public QHBoxLayout {
    Q_OBJECT

public:
    HBoxLayout ( QWidget *parent = 0 );

};

class VBoxLayout : public QVBoxLayout {
    Q_OBJECT

public:
    VBoxLayout ( QWidget *parent = 0 );

};

class Splitter : public QSplitter {
    Q_OBJECT

public:
    Splitter ( QWidget *parent = 0 );
    Splitter ( Qt::Orientation orientation, QWidget* parent = 0 );

};


class Label : public QLabel {
    Q_OBJECT

public:
    Label ( QWidget *parent = 0 );

};


class TabWidget : public QTabWidget {
    Q_OBJECT

public:
    TabWidget ( QWidget* parent = 0 ) ;

protected:
    bool
    eventFilter ( QObject*, // obj
                  QEvent* event );
};

// Splitter/SplitterHandle Object Definition
// Implements double click to open/close right (bottom) split.
// Left (top) remains partially or fully open.
class DetailSplitterHandle;

class DetailSplitter : public QSplitter {
    Q_OBJECT

public:
    DetailSplitter ( QWidget* parent = 0 );
    DetailSplitter ( Qt::Orientation orientation, QWidget* parent = 0 );

    QList <int> Open_Sizes = initOpenSizes;
    QList <int> Closed_Sizes = initClosedSizes;

    void
    setOpenSizes ( QList <int> set_sizes );

    void
    setClosedSizes ( QList <int> set_sizes );

protected:
    QSplitterHandle* createHandle ( ) ;

};

class DetailSplitterHandle : public QSplitterHandle {
    Q_OBJECT

public:
    DetailSplitterHandle ( Qt::Orientation orientation, DetailSplitter* parent = 0 );

protected:
    void
    mouseDoubleClickEvent ( QMouseEvent* event );

};

#endif // MYWIDGETS_H
