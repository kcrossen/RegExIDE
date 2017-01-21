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

#ifndef REGEXIDE_OPTIONS_REFERENCE_PAGE_CPP
#define REGEXIDE_OPTIONS_REFERENCE_PAGE_CPP

#include "RegularExpressionIDE.h"

QWidget*
RegularExpressionIDE::Initialize_Options_Reference_Page_UI ( ) {
    QWidget* container = new QWidget();
    container->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);

    QWidget *left_container = Initialize_Options_Reference_Page_Left_UI();
    left_container->setMinimumHeight(UI_Minimum_Height);

    QFrame *verticalSeparator = new QFrame;
    verticalSeparator->setFrameStyle(QFrame::VLine | QFrame::Sunken);

    QWidget *right_container = Initialize_Options_Reference_Page_Right_UI();
    right_container->setMinimumHeight(UI_Minimum_Height);

    layout->addWidget(left_container, 0);
    layout->addWidget(verticalSeparator, 0);
    layout->addWidget(right_container, 100);

    container->setLayout(layout);
    return container;
}

QWidget*
RegularExpressionIDE::Initialize_Options_Reference_Page_Left_UI ( ) {
    QWidget *container = new QWidget;
    container->setContentsMargins(0, 0, 0, 0);
    container->setMinimumHeight(UI_Minimum_Height);
    container->setMinimumWidth(420);

    QFormLayout *layout = new QFormLayout(container);
    layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    layout->setMargin(0);
    layout->setVerticalSpacing(4);

    caseInsensitiveOptionCheckBox = new QCheckBox(tr("Case insensitive (/i)"));
    dotMatchesEverythingOptionCheckBox = new QCheckBox(tr("Dot matches everything (/s)"));
    multilineOptionCheckBox = new QCheckBox(tr("Multiline (/m)"));
    extendedPatternSyntaxOptionCheckBox = new QCheckBox(tr("Extended pattern (/x)"));
    invertedGreedinessOptionCheckBox = new QCheckBox(tr("Inverted greediness"));
    dontCaptureOptionCheckBox = new QCheckBox(tr("Don't capture"));
    useUnicodePropertiesOptionCheckBox = new QCheckBox(tr("Use unicode properties (/u)"));
    optimizeOnFirstUsageOptionCheckBox = new QCheckBox(tr("Optimize on first usage"));
    dontAutomaticallyOptimizeOptionCheckBox = new QCheckBox(tr("Don't automatically optimize"));

    QGridLayout *patternOptionsLayout = new QGridLayout;
    patternOptionsLayout->setContentsMargins(0, 0, 0, 0);
    patternOptionsLayout->setVerticalSpacing(4);
    int gridRow = 0;
    patternOptionsLayout->addWidget(caseInsensitiveOptionCheckBox, gridRow, 1);
    patternOptionsLayout->addWidget(dotMatchesEverythingOptionCheckBox, gridRow, 2);
    ++gridRow;
    patternOptionsLayout->addWidget(multilineOptionCheckBox, gridRow, 1);
    patternOptionsLayout->addWidget(extendedPatternSyntaxOptionCheckBox, gridRow, 2);
    ++gridRow;
    patternOptionsLayout->addWidget(invertedGreedinessOptionCheckBox, gridRow, 1);
    patternOptionsLayout->addWidget(dontCaptureOptionCheckBox, gridRow, 2);
    ++gridRow;
    patternOptionsLayout->addWidget(useUnicodePropertiesOptionCheckBox, gridRow, 1);
    patternOptionsLayout->addWidget(optimizeOnFirstUsageOptionCheckBox, gridRow, 2);
    ++gridRow;
    patternOptionsLayout->addWidget(dontAutomaticallyOptimizeOptionCheckBox, gridRow, 1);

    QFrame *horizontalSeparator_d = new QFrame;
    horizontalSeparator_d->setFrameStyle(QFrame::HLine | QFrame::Raised);
    layout->addRow(horizontalSeparator_d);

    layout->addRow(new QLabel(tr("<h3>Pattern options</h3>")));
    layout->addRow(patternOptionsLayout);

    QGridLayout *matchOptionsLayout = new QGridLayout;
    matchOptionsLayout->setContentsMargins(0, 0, 0, 0);
    matchOptionsLayout->setVerticalSpacing(4);

    offsetSpinBox = new QSpinBox;
    offsetSpinBox->setMinimumHeight(24);
    offsetSpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    anchoredMatchOptionCheckBox = new QCheckBox(tr("Anchored match"));
    anchoredMatchOptionCheckBox->setMinimumHeight(24);

    QGridLayout *matchOffsetLayout = new QGridLayout;
    matchOffsetLayout->setContentsMargins(0, 0, 0, 0);

    matchOffsetLayout->addWidget(new QLabel(tr("Offset:")), 0, 1, Qt::AlignVCenter);
    matchOffsetLayout->addWidget(offsetSpinBox, 0, 2, Qt::AlignVCenter);
    matchOffsetLayout->addWidget(anchoredMatchOptionCheckBox, 0, 3, Qt::AlignVCenter);
    matchOptionsLayout->addLayout(matchOffsetLayout, 0, 1);

    // layout->addRow(tr("Match\n &offset"), matchOffsetLayout);

    QGridLayout *matchTypeLayout = new QGridLayout;
    matchTypeLayout->setContentsMargins(0, 0, 0, 0);

    matchTypeComboBox = new QComboBox;
    matchTypeComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    matchTypeComboBox->addItem(tr("Normal"), QVariant::fromValue(QRegularExpression::NormalMatch));
    matchTypeComboBox->addItem(tr("Partial prefer complete"), QVariant::fromValue(QRegularExpression::PartialPreferCompleteMatch));
    matchTypeComboBox->addItem(tr("Partial prefer first"), QVariant::fromValue(QRegularExpression::PartialPreferFirstMatch));
    matchTypeComboBox->addItem(tr("No match"), QVariant::fromValue(QRegularExpression::NoMatch));

    matchTypeLayout->addWidget(new QLabel(tr("Type:")), 0, 1, Qt::AlignVCenter);
    matchTypeLayout->addWidget(matchTypeComboBox, 0, 2, Qt::AlignVCenter);
    matchOptionsLayout->addLayout(matchTypeLayout, 1, 1);

    // layout->addRow(tr("Match\n &type"), matchTypeComboBox);

    dontCheckSubjectStringMatchOptionCheckBox = new QCheckBox(tr("Don't check subject string (may crash the program)"));
    matchOptionsLayout->addWidget(dontCheckSubjectStringMatchOptionCheckBox, 2, 1);

    // QGridLayout *matchOptionsCheckBoxLayout = new QGridLayout;
    // matchOptionsCheckBoxLayout->addWidget(dontCheckSubjectStringMatchOptionCheckBox, 0, 0);
    // layout->addRow(tr("Match\n options"), matchOptionsCheckBoxLayout);

    QFrame *horizontalSeparator_e = new QFrame;
    horizontalSeparator_e->setFrameStyle(QFrame::HLine | QFrame::Raised);
    layout->addRow(horizontalSeparator_e);

    layout->addRow(new QLabel(tr("<h3>Match options</h3>")));
    layout->addRow(matchOptionsLayout);

    return container;
}

QWidget*
RegularExpressionIDE::Initialize_Options_Reference_Page_Right_UI ( ) {
    QWidget *container = new QWidget();
    container->setContentsMargins(0, 0, 0, 0);
    container->setMinimumHeight(UI_Minimum_Height);
    container->setMinimumWidth(540);

    QVBoxLayout* container_layout = new QVBoxLayout;
    container_layout->setContentsMargins(0, 0, 0, 0);

    container_layout->addWidget(new QLabel(tr("<h3>RegEx reference (Click to copy, ⌘-Click to paste)</h3>")), 0);

    Reference_Tree = new TreeWidget(this);
    Reference_Tree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    Reference_Tree->setColumnCount(1);
    Reference_Tree->header()->setHidden(true);
    Reference_Tree->setRootIsDecorated(true);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(15);
    Reference_Tree->setFont(font);

    QPalette tree_palette = Reference_Tree->palette();
    tree_palette.setColor(QPalette::AlternateBase, QColor(224, 240, 255));
    Reference_Tree->setPalette(tree_palette);
    Reference_Tree->setAlternatingRowColors(true);

    Reference_Tree->clear();

    int category_root_count = 0;
    QTreeWidgetItem *category_root;
    QTreeWidgetItem *item_root;

    QList <QStringList> regex_reference = Regular_Expression_Reference();

    QString current_category_name = "";
    for (int reference_idx = 0; reference_idx < regex_reference.count(); reference_idx += 1) {
        QStringList regex_item = regex_reference[reference_idx];
        QString category_name = regex_item[0];
        QString item_name = regex_item[1];
        QString item_syntax = regex_item[2];

        if (not (category_name == current_category_name)) {
            category_root_count += 1;
            QStringList category_root_list;
            category_root_list << category_name << "";
            category_root = new QTreeWidgetItem(Reference_Tree, category_root_list);
            current_category_name = category_name;
        }

        QStringList item_root_list;
        item_root_list << item_name + ": " + item_syntax << item_syntax;
        item_root = new QTreeWidgetItem(category_root, item_root_list);
        item_root->setData(0, Qt::UserRole, item_syntax);
        item_root->setData(0, Qt::ToolTipRole, item_name + ", " + item_syntax);
    }

    Reference_Tree->expandToDepth(0);

    connect(Reference_Tree, SIGNAL(clicked(QModelIndex)),
            this, SLOT(onReferenceTreeClicked(QModelIndex)));

    container_layout->addWidget(Reference_Tree, 100);

    container->setLayout(container_layout);
    return container;
}

void
RegularExpressionIDE::onReferenceTreeClicked ( QModelIndex model_index ) {
    if (model_index.isValid() and
        (model_index.column() == 0)) {
        QTreeWidget *sender_reference_tree = dynamic_cast<QTreeWidget*>(sender());

        QModelIndex parent_model_index = sender_reference_tree->model()->parent(model_index);
        Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
        if (parent_model_index.isValid()) {
            QString clicked_value =
                      sender_reference_tree->model()->data(model_index, Qt::UserRole).toString();
            if (modifiers == Qt::NoModifier) {
                QApplication::clipboard()->setText(clicked_value);
            }
            else if ((modifiers & Qt::ControlModifier) == Qt::ControlModifier) {
                if (clicked_value.contains("…")) {
                    QString selected_text = RegEx_Pattern_Edit->textCursor().selectedText();
                    if (selected_text.length() > 0) clicked_value.replace("…", selected_text);
                }
                RegEx_Pattern_Edit->insertPlainText(clicked_value);
                Defer_UI_Refresh = false;
                UI_Refresh();
            }
        }
    }
}

#endif // REGEXIDE_OPTIONS_REFERENCE_PAGE_CPP
