/****************************************************************************
**
** Copyright (C) 2016 Ken Crossen, example expanded into useful application
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

#ifndef REGEXIDE_REGEX_CATALOG_PAGE_CPP
#define REGEXIDE_REGEX_CATALOG_PAGE_CPP

#include "RegularExpressionIDE.h"

QWidget*
RegularExpressionIDE::Initialize_Catalog_Page_UI ( ) {
    QWidget* container = new QWidget();
    container->setContentsMargins(0, 0, 0, 0);
    container->setMinimumHeight(UI_Minimum_Height);

    QHBoxLayout *container_layout = new QHBoxLayout;
    container_layout->setContentsMargins(0, 0, 0, 0);
    container_layout->setSpacing(4);

    QVBoxLayout *catalog_tree_container_layout = new QVBoxLayout;
    catalog_tree_container_layout->setContentsMargins(0, 0, 0, 0);
    catalog_tree_container_layout->setSpacing(2);

    // Buttons to move (reorder) tree leaves
    QHBoxLayout *catalog_tree_button_layout = new QHBoxLayout;
    catalog_tree_button_layout->setContentsMargins(0, 0, 0, 0);

    catalog_tree_button_layout->addWidget(new QLabel(tr("<b>Catalog</b>")), 0);

    QToolButton *save_catalog_button = new QToolButton();
    save_catalog_button->setText(tr("Save"));
    connect(save_catalog_button, SIGNAL(clicked(bool)), this, SLOT(onSaveCatalogClicked(bool)));
    catalog_tree_button_layout->addWidget(save_catalog_button, 0);

    catalog_tree_button_layout->addSpacing(4);

    QToolButton *open_catalog_button = new QToolButton();
    open_catalog_button->setText(tr("Open..."));
    connect(open_catalog_button, SIGNAL(clicked(bool)), this, SLOT(onOpenCatalogClicked(bool)));
    catalog_tree_button_layout->addWidget(open_catalog_button, 0);

    QToolButton *save_catalog_as_button = new QToolButton();
    save_catalog_as_button->setText(tr("Save As..."));
    connect(save_catalog_as_button, SIGNAL(clicked(bool)), this, SLOT(onSaveCatalogAsClicked(bool)));
    catalog_tree_button_layout->addWidget(save_catalog_as_button, 0);

    catalog_tree_button_layout->addStretch(50);

    catalog_tree_button_layout->addWidget(new QLabel(tr("<b>Item</b>")), 0);

    QToolButton *delete_button = new QToolButton();
    delete_button->setText(tr("Delete"));
    connect(delete_button, SIGNAL(clicked(bool)), this, SLOT(onRegExCatalogDeleteItemClicked(bool)));
    catalog_tree_button_layout->addWidget(delete_button, 0);

    catalog_tree_button_layout->addSpacing(4);

    QToolButton *move_up_button = new QToolButton();
    move_up_button->setText(tr("Move Up"));
    connect(move_up_button, SIGNAL(clicked(bool)), this, SLOT(onRegExCatalogMoveUpClicked(bool)));
    catalog_tree_button_layout->addWidget(move_up_button, 0);

    QToolButton *move_down_button = new QToolButton();
    move_down_button->setText(tr("Move Down"));
    connect(move_down_button, SIGNAL(clicked(bool)), this, SLOT(onRegExCatalogMoveDownClicked(bool)));
    catalog_tree_button_layout->addWidget(move_down_button, 0);

    catalog_tree_container_layout->addLayout(catalog_tree_button_layout, 0);
    // Buttons to move (reorder) tree leaves

    RegEx_Catalog_Tree = new TreeWidget(this);
    RegEx_Catalog_Tree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    RegEx_Catalog_Tree->setColumnCount(1);
    RegEx_Catalog_Tree->header()->setHidden(true);
    RegEx_Catalog_Tree->setRootIsDecorated(true);
    RegEx_Catalog_Tree->setSelectionMode(QAbstractItemView::SingleSelection);

    QPalette tree_palette = RegEx_Catalog_Tree->palette();
    tree_palette.setColor(QPalette::AlternateBase, QColor(224, 240, 255));
    RegEx_Catalog_Tree->setPalette(tree_palette);
    RegEx_Catalog_Tree->setAlternatingRowColors(true);

    RegEx_Catalog_Tree->clear();

    connect(RegEx_Catalog_Tree, SIGNAL(clicked(QModelIndex)),
            this, SLOT(onRegExCatalogTreeClicked(QModelIndex)));
    RegEx_Catalog_Tree->Context_Menu = true;
    // connect(RegEx_Catalog_Tree, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
    //         this, SLOT(onPreferencesTreeItemClicked(QTreeWidgetItem*, int)));
    if (RegEx_Catalog_Tree->Context_Menu) {
        connect(RegEx_Catalog_Tree, SIGNAL(itemRightClicked(QTreeWidgetItem*, int)),
                this, SLOT(onRegExCatalogItemRightClicked(QTreeWidgetItem*, int)));
    }

    catalog_tree_container_layout->addWidget(RegEx_Catalog_Tree, 40);

    container_layout->addLayout(catalog_tree_container_layout, 50);

    QFrame *vertical_separator = new QFrame;
    vertical_separator->setFrameStyle(QFrame::VLine | QFrame::Sunken);
    container_layout->addWidget(vertical_separator, 0);

    // RegEx Catalog editor UI
    QVBoxLayout *editor_container_layout = new QVBoxLayout;
    editor_container_layout->setContentsMargins(0, 0, 0, 0);
    editor_container_layout->setSpacing(2);

    QHBoxLayout *editor_button_layout = new QHBoxLayout;
    editor_button_layout->setContentsMargins(0, 0, 0, 0);

    QToolButton *add_new_regex_button = new QToolButton();
    add_new_regex_button->setText(tr("Add New RegEx"));
    connect(add_new_regex_button, SIGNAL(clicked(bool)), this, SLOT(onAddNewRegExClicked(bool)));
    editor_button_layout->addWidget(add_new_regex_button, 0);

    QToolButton *update_regex_button = new QToolButton();
    update_regex_button->setText(tr("Update RegEx"));
    connect(update_regex_button, SIGNAL(clicked(bool)), this, SLOT(onUpdateRegExClicked(bool)));
    editor_button_layout->addWidget(update_regex_button, 0);

    editor_button_layout->addStretch(100);

    QToolButton *copy_from_rx_tab = new QToolButton();
    copy_from_rx_tab->setText(tr("Copy from Regular Expression Tab"));
    connect(copy_from_rx_tab, SIGNAL(clicked(bool)), this, SLOT(onCopyFromRegularExpressionTabClicked(bool)));
    editor_button_layout->addWidget(copy_from_rx_tab, 0);
    editor_container_layout->addLayout(editor_button_layout, 0);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(15);

    QHBoxLayout *series_layout = new QHBoxLayout;
    series_layout->setContentsMargins(0, 0, 0, 0);
    series_layout->addWidget(new QLabel(tr("<b>Series</b>")), 0);
    Catalog_Series = new QLineEdit();
    series_layout->addWidget(Catalog_Series, 100);
    editor_container_layout->addLayout(series_layout, 0);

    QHBoxLayout *series_index_layout = new QHBoxLayout;
    series_index_layout->setContentsMargins(0, 0, 0, 0);
    series_index_layout->addWidget(new QLabel(tr("<b>Series Index</b>")), 0);
    Catalog_Series_Index = new QLineEdit();
    series_index_layout->addWidget(Catalog_Series_Index, 100);
    editor_container_layout->addLayout(series_index_layout, 0);

    QHBoxLayout *series_help_layout = new QHBoxLayout;
    series_help_layout->setContentsMargins(0, 0, 0, 0);
    series_help_layout->addWidget(new QLabel(tr("<b>Series Help</b>")), 0);
    Catalog_Series_Help = new QLineEdit();
    series_help_layout->addWidget(Catalog_Series_Help, 100);
    editor_container_layout->addLayout(series_help_layout, 0);

    QStringList before_after_replace =
      QStringList({"",
                   "Target_From_Clipboard", "Target_From_Memory", "Target_Swap_Memory",
                   "Target_To_Replace", "Target_To_Memory", "Target_To_Clipboard"});

    QHBoxLayout *series_before_replace_layout = new QHBoxLayout;
    series_before_replace_layout->setContentsMargins(0, 0, 0, 0);
    series_before_replace_layout->addWidget(new QLabel(tr("<b>Before Replace</b>")), 0);
    Catalog_Series_Before_Replace_ComboBox = new QComboBox();
    Catalog_Series_Before_Replace_ComboBox->setEditable(false);
    Catalog_Series_Before_Replace_ComboBox->setInsertPolicy(QComboBox::NoInsert);
    Catalog_Series_Before_Replace_ComboBox->addItems(before_after_replace);
    series_before_replace_layout->addWidget(Catalog_Series_Before_Replace_ComboBox, 100);
    editor_container_layout->addLayout(series_before_replace_layout, 0);

    QHBoxLayout *series_after_replace_layout = new QHBoxLayout;
    series_after_replace_layout->setContentsMargins(0, 0, 0, 0);
    series_after_replace_layout->addWidget(new QLabel(tr("<b>After Replace</b>")), 0);
    Catalog_Series_After_Replace_ComboBox = new QComboBox();
    Catalog_Series_After_Replace_ComboBox->setEditable(false);
    Catalog_Series_After_Replace_ComboBox->setInsertPolicy(QComboBox::NoInsert);
    Catalog_Series_After_Replace_ComboBox->addItems(before_after_replace);
    series_after_replace_layout->addWidget(Catalog_Series_After_Replace_ComboBox, 100);
    editor_container_layout->addLayout(series_after_replace_layout, 0);

    QFrame *horizontal_separator_a = new QFrame;
    horizontal_separator_a->setFrameStyle(QFrame::HLine | QFrame::Raised);
    editor_container_layout->addWidget(horizontal_separator_a, 0);

    QHBoxLayout *category_layout = new QHBoxLayout;
    category_layout->setContentsMargins(0, 0, 0, 0);
    category_layout->addWidget(new QLabel(tr("<b>Category</b>")), 0);
    Catalog_Category = new QLineEdit();
    category_layout->addWidget(Catalog_Category, 100);
    editor_container_layout->addLayout(category_layout, 0);

    QHBoxLayout *regex_name_layout = new QHBoxLayout;
    regex_name_layout->setContentsMargins(0, 0, 0, 0);
    regex_name_layout->addWidget(new QLabel(tr("<b>RegEx Name</b>")), 0);
    Catalog_RegEx_Name = new QLineEdit();
    regex_name_layout->addWidget(Catalog_RegEx_Name, 100);
    editor_container_layout->addLayout(regex_name_layout, 0);

    QFrame *horizontal_separator_b = new QFrame;
    horizontal_separator_b->setFrameStyle(QFrame::HLine | QFrame::Raised);
    editor_container_layout->addWidget(horizontal_separator_b, 0);

    editor_container_layout->addWidget(new QLabel(tr("<b>Find pattern</b>")), 0);
    Catalog_RegEx_Pattern = new PlainTextEdit(this, RegEx_Matching);
    Catalog_RegEx_Pattern->setFont(font);
    Catalog_RegEx_Pattern->setReadOnly(false);
    editor_container_layout->addWidget(Catalog_RegEx_Pattern, 50);

    QHBoxLayout *replace_pattern_layout = new QHBoxLayout;
    replace_pattern_layout->setContentsMargins(0, 0, 0, 0);
    replace_pattern_layout->addWidget(new QLabel(tr("<b>Replace pattern</b>")), 0);
    replace_pattern_layout->addSpacing(4);
    Catalog_Replace_Scripted = new QCheckBox("Scripted");
    replace_pattern_layout->addWidget(Catalog_Replace_Scripted, 0);
    replace_pattern_layout->addStretch(50);
    Catalog_Replace_Pattern_Specified = new QCheckBox(tr("Replace pattern specified"));
    replace_pattern_layout->addWidget(Catalog_Replace_Pattern_Specified, 0);

    editor_container_layout->addLayout(replace_pattern_layout, 0);
    Catalog_Replace_Pattern = new PlainTextEdit(this, RegEx_Matching);
    Catalog_Replace_Pattern->setFont(font);
    Catalog_Replace_Pattern->setReadOnly(false);
    editor_container_layout->addWidget(Catalog_Replace_Pattern, 50);

    QHBoxLayout *target_layout = new QHBoxLayout;
    target_layout->setContentsMargins(0, 0, 0, 0);
    target_layout->addWidget(new QLabel(tr("<b>Target</b>")), 0);
    target_layout->addStretch(50);
    Catalog_Target_Specified = new QCheckBox(tr("Target specified"));
    target_layout->addWidget(Catalog_Target_Specified, 0);

    editor_container_layout->addLayout(target_layout, 0);
    Catalog_Target = new PlainTextEdit(this);
    Catalog_Target->setFont(font);
    Catalog_Target->setReadOnly(false);
    editor_container_layout->addWidget(Catalog_Target, 50);

    container_layout->addLayout(editor_container_layout, 50);

    container->setLayout(container_layout);
    return container;
}

void
RegularExpressionIDE::Populate_RegEx_Catalog_Tree ( QVariantList RegEx_Catalog_Descriptors ) {
    RegEx_Catalog_Tree->clear();

    QHash <QString, QTreeWidgetItem*> regex_catalog_roots;

    int category_root_count = 0;
    QTreeWidgetItem *item_root;

    for (int regex_idx = 0; regex_idx < RegEx_Catalog_Descriptors.count(); regex_idx += 1) {
        OrderedVariantMap regex_descr = toOrderedMap(RegEx_Catalog_Descriptors[regex_idx]);
        if (regex_descr.contains("Category") and regex_descr.contains("RegEx_Name") and
            regex_descr.contains("RegEx_Pattern")) {
            QString category_name = regex_descr.value("Category").toString();
            QString regex_name = regex_descr.value("RegEx_Name").toString();
            regex_name = regex_name.replace("&&", "&");

            if (not regex_catalog_roots.contains(category_name)) {
                // Add another root
                category_root_count += 1;
                regex_catalog_roots[category_name] =
                  new QTreeWidgetItem(RegEx_Catalog_Tree, QStringList({category_name, ""}));
            }

            item_root =
              new QTreeWidgetItem(regex_catalog_roots[category_name], QStringList({regex_name, ""}));
            item_root->setData(0, Qt::UserRole, fromOrderedMap(regex_descr));
        }
    }

    RegEx_Catalog_Tree->expandToDepth(0);
}

OrderedVariantMap
RegularExpressionIDE::RegEx_Descriptor_From_Edit ( ) {
    OrderedVariantMap regex_descr;
    if ((Catalog_Series->text().length() > 0) and
        (Catalog_Series_Index->text().length() > 0)) {
        regex_descr["Series"] = Catalog_Series->text();
        regex_descr["Series_Index"] = Catalog_Series_Index->text().toInt();
        regex_descr["Series_Help"] = Catalog_Series_Help->text();
        if (Catalog_Series_Before_Replace_ComboBox->currentText().length() > 0)
            regex_descr["Series_Before_Replace"] = Catalog_Series_Before_Replace_ComboBox->currentText().length();
        if (Catalog_Series_After_Replace_ComboBox->currentText().length() > 0)
            regex_descr["Series_After_Replace"] = Catalog_Series_After_Replace_ComboBox->currentText();
     }

    regex_descr["Category"] = Catalog_Category->text();
    regex_descr["RegEx_Name"] = Catalog_RegEx_Name->text();
    regex_descr["RegEx_Pattern"] = Catalog_RegEx_Pattern->toPlainText();

    if ((Catalog_Replace_Pattern->toPlainText().length() > 0) or
        Catalog_Replace_Pattern_Specified->isChecked()) {
        if (Catalog_Replace_Scripted->isChecked()) {
            regex_descr["Replace_Script"] = Catalog_Replace_Pattern->toPlainText();
        }
        else {
            regex_descr["Replace_Pattern"] = Catalog_Replace_Pattern->toPlainText();
        }
    }

    if ((Catalog_Target->toPlainText().length() > 0) or
        Catalog_Target_Specified->isChecked())
        regex_descr["Target"] = Catalog_Target->toPlainText();

    return regex_descr;
}

QVariantList
RegularExpressionIDE::RegEx_Catalog_From_Tree ( ) {
    QVariantList regex_descriptors;
    for (int category_item_idx = 0;
         category_item_idx < RegEx_Catalog_Tree->topLevelItemCount();
         category_item_idx += 1) {

        QTreeWidgetItem *category_item = RegEx_Catalog_Tree->topLevelItem(category_item_idx);
        for (int regex_item_idx = 0; regex_item_idx < category_item->childCount(); regex_item_idx += 1) {
            QTreeWidgetItem *regex_item = category_item->child(regex_item_idx);
            OrderedVariantMap regex_descr = toOrderedMap(regex_item->data(0, Qt::UserRole));
            regex_descriptors.append(fromOrderedMap(regex_descr));
        }
    }

    return regex_descriptors;
}

void
RegularExpressionIDE::RegEx_Catalog_Set_Selected_RegEx ( OrderedVariantMap Select_RegEx_Descr ) {
    RegEx_Catalog_Tree->clearSelection();

    bool found_regex = false;
    for (int category_item_idx = RegEx_Catalog_Tree->topLevelItemCount() - 1;
         category_item_idx >= 0;
         category_item_idx -= 1) {

        QTreeWidgetItem *category_item = RegEx_Catalog_Tree->topLevelItem(category_item_idx);
        for (int regex_item_idx = category_item->childCount() - 1; regex_item_idx >= 0; regex_item_idx -= 1) {
            QTreeWidgetItem *regex_item = category_item->child(regex_item_idx);
            OrderedVariantMap regex_descr = toOrderedMap(regex_item->data(0, Qt::UserRole));
            if ((regex_descr.value("Category").toString() ==
                 Select_RegEx_Descr.value("Category").toString()) and
                (regex_descr.value("RegEx_Name").toString() ==
                 Select_RegEx_Descr.value("RegEx_Name").toString())) {
                regex_item->setSelected(true);
                found_regex = true;
            }
        }
        if (found_regex) break;
    }
}

void
RegularExpressionIDE::onRegExCatalogTreeClicked ( QModelIndex model_index ) {
    if (model_index.isValid() and
        (model_index.column() == 0)) {
        TreeWidget *sender_reference_tree = dynamic_cast<TreeWidget*>(sender());

        QModelIndex parent_model_index = sender_reference_tree->model()->parent(model_index);
        Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
        if (parent_model_index.isValid() and
            ((modifiers & Qt::ControlModifier) == Qt::ControlModifier)) {
            RegEx_Catalog_Edit_Item = sender_reference_tree->Clicked_Tree_Widget_Item;

            OrderedVariantMap regex_descr =
                                toOrderedMap(sender_reference_tree->model()->data(model_index, Qt::UserRole));

            QString series_name;
            if (regex_descr.contains("Series")) series_name = regex_descr.value("Series").toString();
            QString series_index;
            if (regex_descr.contains("Series_Index")) series_index = regex_descr.value("Series_Index").toString();
            QString series_help;
            if (regex_descr.contains("Series_Help")) series_help = regex_descr.value("Series_Help").toString();

            if (regex_descr.contains("Series_Before_Replace"))
                Catalog_Series_Before_Replace_ComboBox->setCurrentText(regex_descr.value("Series_Before_Replace").toString());
            else Catalog_Series_Before_Replace_ComboBox->setCurrentText("");
            if (regex_descr.contains("Series_After_Replace"))
                Catalog_Series_After_Replace_ComboBox->setCurrentText(regex_descr.value("Series_After_Replace").toString());
            else Catalog_Series_After_Replace_ComboBox->setCurrentText("");

            QString category_name = regex_descr.value("Category").toString();
            QString regex_name = regex_descr.value("RegEx_Name").toString();

            QString regex_pattern = regex_descr.value("RegEx_Pattern").toString();
            QString replace_pattern;
            if (regex_descr.contains("Replace_Pattern"))
                replace_pattern = regex_descr.value("Replace_Pattern").toString();
            QString replace_script;
            if (regex_descr.contains("Replace_Script"))
                replace_script = regex_descr.value("Replace_Script").toString();
            QString target;
            if (regex_descr.contains("Target"))
                target = regex_descr.value("Target").toString();

            Catalog_Series->setText(series_name);
            Catalog_Series_Index->setText(series_index);
            Catalog_Series_Help->setText(series_help);

            Catalog_Category->setText(category_name);
            Catalog_RegEx_Name->setText(regex_name);

            // Don't defeat Undo/Redo
            Catalog_RegEx_Pattern->Set_PlainText(regex_pattern);

            Catalog_Replace_Scripted->setChecked(false);
            Catalog_Replace_Pattern_Specified->setChecked(regex_descr.contains("Replace_Pattern") or
                                                          regex_descr.contains("Replace_Script"));
            if (regex_descr.contains("Replace_Pattern")) {
                Catalog_Replace_Pattern->Set_PlainText(replace_pattern);
                Catalog_Replace_Scripted->setChecked(false);
            }
            else if (regex_descr.contains("Replace_Script")) {
                Catalog_Replace_Pattern->Set_PlainText(replace_script);
                Catalog_Replace_Scripted->setChecked(true);
            }

            Catalog_Target_Specified->setChecked(regex_descr.contains("Target"));
            Catalog_Target->Set_PlainText(target);
        }
    }
}

void
RegularExpressionIDE::onRegExCatalogItemRightClicked ( QTreeWidgetItem *item,
                                                           int column ) {
    if (column == 0) {
        QTreeWidgetItem *parent_item = item->parent();

        if (not (parent_item == NULL)) {
            // Array children: can duplicate, can delete if not only child, ...
            // ... can reorder if not first (no up) or last child (no down)
            RegEx_Catalog_Tree_Right_Clicked_Item = item;

            QMenu* contextMenu = new QMenu ( this );
            Q_CHECK_PTR ( contextMenu );

            contextMenu->addAction("Delete item", this, SLOT(onRegExCatalogDeleteItem()));

            // contextMenu->addSeparator();
            // Only JSON array children may be reordered
            if (parent_item->indexOfChild(item) > (2 - 1))
                contextMenu->addAction("Move item up two", this, [this]{ onRegExCatalogMoveItemUp(2); });
            if (parent_item->indexOfChild(item) > (1 - 1))
                contextMenu->addAction("Move item up one", this, [this]{ onRegExCatalogMoveItemUp(1); });
            if (parent_item->indexOfChild(item) < (parent_item->childCount() - 1))
                contextMenu->addAction("Move item down one", this, [this]{ onRegExCatalogMoveItemDown(1); });
            if (parent_item->indexOfChild(item) < (parent_item->childCount() - 2))
                contextMenu->addAction("Move item down two", this, [this]{ onRegExCatalogMoveItemDown(2); });

            contextMenu->exec ( QCursor::pos() );
            delete contextMenu;
            contextMenu = 0;
        }
    }
}

void
RegularExpressionIDE::onRegExCatalogDeleteItem ( ) {
    QTreeWidgetItem *parent_item = RegEx_Catalog_Tree_Right_Clicked_Item->parent();
    if (parent_item == NULL) return;
    // JSON array child ...
    delete RegEx_Catalog_Tree_Right_Clicked_Item;

    QVariantList regex_descriptors = RegEx_Catalog_From_Tree();
    Populate_RegEx_Catalog_Tree(regex_descriptors);
}

void
RegularExpressionIDE::onRegExCatalogMoveItemUp ( int move_up_places ) {
    QTreeWidgetItem *parent_item = RegEx_Catalog_Tree_Right_Clicked_Item->parent();
    if (parent_item == NULL) return;
    // JSON array child ...
    if (parent_item->indexOfChild(RegEx_Catalog_Tree_Right_Clicked_Item) > (move_up_places - 1)) {
        // ... and not first child
        int child_idx = parent_item->indexOfChild(RegEx_Catalog_Tree_Right_Clicked_Item);
        QTreeWidgetItem* child_item = parent_item->takeChild(child_idx);
        parent_item->insertChild((child_idx - move_up_places), child_item);
        RegEx_Catalog_Tree->clearSelection();
        child_item->setSelected(true);
    }
}

void
RegularExpressionIDE::onRegExCatalogMoveItemDown ( int move_down_places ) {
    QTreeWidgetItem *parent_item = RegEx_Catalog_Tree_Right_Clicked_Item->parent();
    if (parent_item == NULL) return;
    // JSON array child ...
    if (parent_item->indexOfChild(RegEx_Catalog_Tree_Right_Clicked_Item) < (parent_item->childCount() - move_down_places)) {
        // ... and not last child
        int child_idx = parent_item->indexOfChild(RegEx_Catalog_Tree_Right_Clicked_Item);
        QTreeWidgetItem* child_item = parent_item->takeChild(child_idx);
        parent_item->insertChild((child_idx + move_down_places), child_item);
        RegEx_Catalog_Tree->clearSelection();
        child_item->setSelected(true);
    }
}

void
RegularExpressionIDE::onRegExCatalogDeleteItemClicked ( bool ) {
    QList<QTreeWidgetItem *> sel_items = RegEx_Catalog_Tree->selectedItems();
    if (not (sel_items.count() == 1)) return;
    RegEx_Catalog_Tree_Right_Clicked_Item = sel_items[0];
    onRegExCatalogDeleteItem();
}

void
RegularExpressionIDE::onRegExCatalogMoveUpClicked ( bool ) {
    QList<QTreeWidgetItem *> sel_items = RegEx_Catalog_Tree->selectedItems();
    if (not (sel_items.count() == 1)) return;
    RegEx_Catalog_Tree_Right_Clicked_Item = sel_items[0];
    onRegExCatalogMoveItemUp(1);
}

void
RegularExpressionIDE::onRegExCatalogMoveDownClicked ( bool ) {
    QList<QTreeWidgetItem *> sel_items = RegEx_Catalog_Tree->selectedItems();
    if (not (sel_items.count() == 1)) return;
    RegEx_Catalog_Tree_Right_Clicked_Item = sel_items[0];
    onRegExCatalogMoveItemDown(1);
}

void
RegularExpressionIDE::onAddNewRegExClicked ( bool ) {
    QVariantList regex_descriptors = RegEx_Catalog_From_Tree();

    OrderedVariantMap regex_descr = RegEx_Descriptor_From_Edit();

    regex_descriptors.append(fromOrderedMap(regex_descr));

    Populate_RegEx_Catalog_Tree(regex_descriptors);

    RegEx_Catalog_Set_Selected_RegEx(regex_descr);
}

void
RegularExpressionIDE::onUpdateRegExClicked ( bool ) {
    OrderedVariantMap regex_descr = RegEx_Descriptor_From_Edit();
    RegEx_Catalog_Edit_Item->setData(0, Qt::UserRole, fromOrderedMap(regex_descr));
}

void
RegularExpressionIDE::onSaveCatalogClicked ( bool ) {
    QVariantList regex_descriptors = RegEx_Catalog_From_Tree();
    RegExIDE_Initialization["RegEx_Catalog"] = regex_descriptors;
    Save_Application_Initialization();
}

void
RegularExpressionIDE::onOpenCatalogClicked ( bool ) {
    QString app_data_path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString filename = QFileDialog::getOpenFileName(this, tr("Open RegEx Catalog from"),
                                                    QDir::toNativeSeparators(app_data_path),
                                                    "INI (*.ini)");
    if (filename.isEmpty()) return;

    QFile ini_file(filename);
    if (not ini_file.open(QIODevice::ReadOnly)) {
        // Error message here?
        return;
    }

    QString ini_json = ini_file.readAll();
    ini_file.close();

    using namespace QtOrderedJson;

    bool ini_success = false;
    OrderedVariantMap regexide_ini;
    if (ini_json.length() > 0) {
        ini_json = Upgrade_Application_Initialization(ini_json);
        regexide_ini = toOrderedMap(parseJson(ini_json, ini_success));
    }

    if (ini_success) {
        if (regexide_ini.contains("RegEx_Catalog")) {
            QVariantList regex_catalog_descriptors = regexide_ini.value("RegEx_Catalog").toList();
            Populate_RegEx_Catalog_Tree(regex_catalog_descriptors);
        }
    }
}

void
RegularExpressionIDE::onSaveCatalogAsClicked ( bool ) {
    QString app_data_path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString filename = QFileDialog::getSaveFileName(this, tr("Save RegEx Catalog to"),
                                                    QDir::toNativeSeparators(app_data_path),
                                                    "INI (*.ini)");
    if (filename.isEmpty()) return;

    // Preserve "official" RegEx_Catalog ...
    QVariantList regex_catalog_descriptors = RegExIDE_Initialization.value("RegEx_Catalog").toList();

    QVariantList temp_regex_descriptors = RegEx_Catalog_From_Tree();
    RegExIDE_Initialization["RegEx_Catalog"] = temp_regex_descriptors;
    Save_Application_Initialization(filename);

    // ... and finally restore "official" RegEx_Catalog
    RegExIDE_Initialization["RegEx_Catalog"] = regex_catalog_descriptors;
}

#endif // REGEXIDE_REGEX_CATALOG_PAGE_CPP
