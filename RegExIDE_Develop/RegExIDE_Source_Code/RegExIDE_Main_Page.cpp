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

#ifndef REGEXIDE_MAIN_PAGE_CPP
#define REGEXIDE_MAIN_PAGE_CPP

#include "RegularExpressionIDE.h"

QWidget*
RegularExpressionIDE::Initialize_Main_Page_UI ( ) {
    QWidget *left_container = Initialize_Main_Page_Left_UI();

    QFrame *verticalSeparator = new QFrame;
    verticalSeparator->setFrameStyle(QFrame::VLine | QFrame::Sunken);

    QWidget *right_container = Initialize_Main_Page_Right_UI();

    QHBoxLayout *main_page_layout = new QHBoxLayout;
    main_page_layout->setContentsMargins(0, 0, 0, 0);
    main_page_layout->setSpacing(2);

    main_page_layout->addWidget(left_container, 100);
    main_page_layout->addWidget(verticalSeparator, 0);
    main_page_layout->addWidget(right_container, 75);

    QFrame* main_page_frame = new QFrame();
    main_page_frame->setFrameStyle(QFrame::NoFrame);
    main_page_frame->setContentsMargins(0, 0, 0, 0);
    main_page_frame->setLayout(main_page_layout);

    return main_page_frame;
}

QWidget*
RegularExpressionIDE::Initialize_Main_Page_Left_UI ( ) {
    QWidget *container = new QWidget;
    container->setContentsMargins(0, 0, 0, 0);
    container->setMinimumHeight(UI_Minimum_Height);
    container->setMinimumWidth(540);

    QVBoxLayout *container_layout = new QVBoxLayout;
    container_layout->setContentsMargins(0, 0, 0, 0);
    container_layout->setSpacing(4);

    // container_layout->addWidget(new QLabel(tr("<h3>RegEx pattern, target, replace pattern</h3>")), 0);

    // QFrame *horizontalSeparator_a = new QFrame;
    // horizontalSeparator_a->setFrameStyle(QFrame::HLine | QFrame::Raised);
    // container_layout->addWidget(horizontalSeparator_a, 0);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(15);

    RegEx_Pattern_Edit = new PlainTextEdit(this, RegEx_Matching);
    RegEx_Pattern_Edit->setFont(font);

    QHBoxLayout *pattern_layout = new QHBoxLayout;
    pattern_layout->setContentsMargins(0, 0, 0, 0);
    pattern_layout->addWidget(new QLabel(tr("<h3>Find pattern</h3>")), 0);
    pattern_layout->addStretch(100);

    QToolButton *rx_pattern_selected_escaped = new QToolButton();
    rx_pattern_selected_escaped->setText("Escape selected text");
    rx_pattern_selected_escaped->setToolTip("Selected text should be rendered as literal characters w/o special meanings.");
    connect(rx_pattern_selected_escaped, SIGNAL(clicked(bool)), this, SLOT(onEscapeSelectedText(bool)));
    pattern_layout->addWidget(rx_pattern_selected_escaped, 0);

    pattern_layout->addSpacing(4);

    QToolButton *rx_pattern_copy_to_apply = new QToolButton();
    rx_pattern_copy_to_apply->setText("Copy to Apply");
    connect(rx_pattern_copy_to_apply, SIGNAL(clicked(bool)), this, SLOT(onRegexPatternCopyToApplyClicked(bool)));
    pattern_layout->addWidget(rx_pattern_copy_to_apply, 0);

    pattern_layout->addSpacing(4);

    QToolButton *rx_pattern_copy = new QToolButton();
    rx_pattern_copy->setText("Copy");
    connect(rx_pattern_copy, SIGNAL(clicked(bool)), this, SLOT(onRegexPatternCopyClicked(bool)));
    pattern_layout->addWidget(rx_pattern_copy, 0);

    QToolButton *rx_pattern_copy_escaped = new QToolButton();
    rx_pattern_copy_escaped->setText("Copy escaped");
    rx_pattern_copy_escaped->setToolTip("Copy <b>RegEx pattern</b> rendered as a C/C++ literal to be pasted into source code.");
    connect(rx_pattern_copy_escaped, SIGNAL(clicked(bool)), this, SLOT(onRegexPatternCopyEscapedClicked(bool)));
    pattern_layout->addWidget(rx_pattern_copy_escaped, 0);

    container_layout->addLayout(pattern_layout, 0);
    // container_layout->addWidget(new QLabel(tr("<h4>RegEx pattern (⌘-Click to copy escaped):</h4>")), 0);
    container_layout->addWidget(RegEx_Pattern_Edit, 100);

    QHBoxLayout *status_layout = new QHBoxLayout;
    status_layout->setContentsMargins(0, 0, 0, 0);

    status_layout->addWidget(new QLabel(tr("<b>Status:</b>")), 0);
    regexpStatusLabel = new QLabel(tr("Valid"));
    regexpStatusLabel->setWordWrap(true);
    // regexpStatusLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    regexpStatusLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    status_layout->addWidget(regexpStatusLabel, 0);

    container_layout->addLayout(status_layout, 0);

    QFrame *horizontalSeparator_c = new QFrame;
    horizontalSeparator_c->setFrameStyle(QFrame::HLine | QFrame::Raised);
    container_layout->addWidget(horizontalSeparator_c, 0);

    Target_Text_Edit = new PlainTextEdit(this);
    Target_Text_Edit->setFont(font);
    container_layout->addWidget(new QLabel(tr("<h3>Target text</h3>")), 0);
    container_layout->addWidget(Target_Text_Edit, 100);

    QFrame *horizontalSeparator_d = new QFrame;
    horizontalSeparator_d->setFrameStyle(QFrame::HLine | QFrame::Raised);
    container_layout->addWidget(horizontalSeparator_d, 0);

    Replace_Pattern_Edit = new PlainTextEdit(this, RegEx_Matching);
    Replace_Pattern_Edit->setFont(font);
    // connect(Replace_Pattern_Edit, SIGNAL(clicked()), this, SLOT(onReplacePatternCopyEscapedClicked()));

    QHBoxLayout *replace_layout = new QHBoxLayout;
    replace_layout->setContentsMargins(0, 0, 0, 0);
    replace_layout->addWidget(new QLabel(tr("<h3>Replace pattern</h3>")), 0);

    replace_layout->addStretch(100);

    QToolButton *replace_pattern_copy_to_apply = new QToolButton();
    replace_pattern_copy_to_apply->setText("Copy to Apply");
    connect(replace_pattern_copy_to_apply, SIGNAL(clicked(bool)), this, SLOT(onReplacePatternCopyToApplyClicked(bool)));
    replace_layout->addWidget(replace_pattern_copy_to_apply, 0);

    replace_layout->addSpacing(4);

    QToolButton *replace_pattern_copy = new QToolButton();
    replace_pattern_copy->setText("Copy");
    connect(replace_pattern_copy, SIGNAL(clicked(bool)), this, SLOT(onReplacePatternCopyClicked(bool)));
    replace_layout->addWidget(replace_pattern_copy, 0);

    QToolButton *replace_pattern_copy_escaped = new QToolButton();
    replace_pattern_copy_escaped->setText("Copy escaped");
    replace_pattern_copy_escaped->setToolTip("Copy <b>Replace pattern</b> rendered as a C/C++ literal to be pasted into source code.");
    connect(replace_pattern_copy_escaped, SIGNAL(clicked(bool)), this, SLOT(onReplacePatternCopyEscapedClicked(bool)));
    replace_layout->addWidget(replace_pattern_copy_escaped, 0);

    container_layout->addLayout(replace_layout, 0);
    // container_layout->addWidget(new QLabel(tr("<h4>Replace pattern (⌘-Click to copy escaped):</h4>")), 0);
    container_layout->addWidget(Replace_Pattern_Edit, 100);

    QFrame *horizontalSeparator_e = new QFrame;
    horizontalSeparator_e->setFrameStyle(QFrame::HLine | QFrame::Raised);
    container_layout->addWidget(horizontalSeparator_e, 0);

    container_layout->addWidget(new QLabel(tr("<h3>Replace pattern result</h3>")), 0);
    Replace_Pattern_Result = new PlainTextEdit(this);
    Replace_Pattern_Result->setReadOnly(true);
    QPalette result_palette = Replace_Pattern_Result->palette();
    result_palette.setBrush(QPalette::Base, result_palette.brush(QPalette::Disabled, QPalette::Base));
    Replace_Pattern_Result->setPalette(result_palette);
    container_layout->addWidget(Replace_Pattern_Result, 100);

    container->setLayout(container_layout);
    return container;
}

QWidget*
RegularExpressionIDE::Initialize_Main_Page_Right_UI ( ) {
    QWidget *container = new QWidget;
    container->setContentsMargins(0, 0, 0, 0);
    container->setMinimumHeight(UI_Minimum_Height);
    container->setMinimumWidth(420);

    QVBoxLayout* container_layout = new QVBoxLayout;
    container_layout->setContentsMargins(0, 0, 0, 0);
    container_layout->setSpacing(4);

    // QLabel *named_groups_label = new QLabel(tr("<h3>RegEx capturing groups</h3>"));
    container_layout->addWidget(new QLabel(tr("<h3>RegEx capturing groups</h3>")), 0);

    Groups_Tree = new QTreeWidget;
    Groups_Tree->setHeaderLabels(QStringList() << tr("Index") << tr("Named group"));
    // Groups_Tree->setSizeAdjustPolicy(QTreeWidget::AdjustToContents);
    Groups_Tree->setRootIsDecorated(false);
    Groups_Tree->setAlternatingRowColors(true);
    connect(Groups_Tree, SIGNAL(clicked(QModelIndex)),
            this, SLOT(onGroupsTreeClicked(QModelIndex)));
    container_layout->addWidget(Groups_Tree, 15);

    Pattern_Elements_Tree = new QTreeWidget;
    Pattern_Elements_Tree->setHeaderLabels(QStringList() << tr("Type") << tr("Text")); // << ""
    Pattern_Elements_Tree->setRootIsDecorated(true);
    Pattern_Elements_Tree->setColumnWidth(0, 220);
    Pattern_Elements_Tree->setColumnWidth(1, 180);
    Pattern_Elements_Tree->setAlternatingRowColors(true);
    connect(Pattern_Elements_Tree, SIGNAL(clicked(QModelIndex)),
            this, SLOT(onPatternElementsTreeClicked(QModelIndex)));
    container_layout->addWidget(new QLabel(tr("<h3>RegEx pattern elements</h3>")), 0);
    container_layout->addWidget(Pattern_Elements_Tree, 100);

    QFrame *horizontal_separator = new QFrame;
    horizontal_separator->setFrameStyle(QFrame::HLine | QFrame::Raised);
    container_layout->addWidget(horizontal_separator, 0);

    // QLabel *rx_match_details_label = new QLabel(tr("<h3>RegEx matches</h3>"));
    container_layout->addWidget(new QLabel(tr("<h3>RegEx matches</h3>")), 0);

    Matches_Tree = new QTreeWidget;
    Matches_Tree->setHeaderLabels(QStringList() << tr("Match idx") << tr("Group") << tr("Captured") << tr("Captured idx"));
    // Matches_Tree->setSizeAdjustPolicy(QTreeWidget::AdjustToContents);
    Matches_Tree->setRootIsDecorated(true);
    container_layout->addWidget(Matches_Tree, 100);

    container->setLayout(container_layout);
    return container;
}

void
RegularExpressionIDE::UI_Refresh ( ) {
    if (Defer_UI_Refresh) return;

    RegEx_Valid = false;

    // QString pattern = "\\btoto(\\w+)\\b";
    // QString target = "slkj tototata lkj";
    // QString pattern = "(?:(?<numbers>[0-9]+)|(?<letters>[a-z]+)|(?<symbols>[@#$%&]+))+";
    // QString target = "123abc$%& 456def@#$ 789ghi#$% 123$%&abc 456@#$def 789#$%ghi 123abc$%& 456def@#$ 789ghi#$%";
    // RegEx_Trace(pattern, target);

    setUpdatesEnabled(false);

    const QString regex_pattern = RegEx_Pattern_Edit->toPlainText();
    const QString target_text = Target_Text_Edit->toPlainText();

    offsetSpinBox->setMaximum(qMax(0, target_text.length() - 1));

    QRegularExpression regex(regex_pattern);
    QRegularExpression::MatchType matchType = matchTypeComboBox->currentData().value<QRegularExpression::MatchType>();
    QRegularExpression::PatternOptions patternOptions = QRegularExpression::NoPatternOption;
    QRegularExpression::MatchOptions matchOptions = QRegularExpression::NoMatchOption;

    if (anchoredMatchOptionCheckBox->isChecked())
        matchOptions |= QRegularExpression::AnchoredMatchOption;
    if (dontCheckSubjectStringMatchOptionCheckBox->isChecked())
        matchOptions |= QRegularExpression::DontCheckSubjectStringMatchOption;

    if (caseInsensitiveOptionCheckBox->isChecked())
        patternOptions |= QRegularExpression::CaseInsensitiveOption;
    if (dotMatchesEverythingOptionCheckBox->isChecked())
        patternOptions |= QRegularExpression::DotMatchesEverythingOption;
    if (multilineOptionCheckBox->isChecked())
        patternOptions |= QRegularExpression::MultilineOption;
    if (extendedPatternSyntaxOptionCheckBox->isChecked())
        patternOptions |= QRegularExpression::ExtendedPatternSyntaxOption;
    if (invertedGreedinessOptionCheckBox->isChecked())
        patternOptions |= QRegularExpression::InvertedGreedinessOption;
    if (dontCaptureOptionCheckBox->isChecked())
        patternOptions |= QRegularExpression::DontCaptureOption;
    if (useUnicodePropertiesOptionCheckBox->isChecked())
        patternOptions |= QRegularExpression::UseUnicodePropertiesOption;
    if (optimizeOnFirstUsageOptionCheckBox->isChecked())
        patternOptions |= QRegularExpression::OptimizeOnFirstUsageOption;
    if (dontAutomaticallyOptimizeOptionCheckBox->isChecked())
        patternOptions |= QRegularExpression::DontAutomaticallyOptimizeOption;

    regex.setPatternOptions(patternOptions);

    QPalette palette = RegEx_Pattern_Edit->palette();
    if (regex.isValid())
        palette.setColor(QPalette::Text, Target_Text_Edit->palette().color(QPalette::Text));
    else
        palette.setColor(QPalette::Text, Qt::red);
    RegEx_Pattern_Edit->setPalette(palette);

    Matches_Tree->clear();
    Matches_Tree->setEnabled(regex.isValid());

    QList<QTextEdit::ExtraSelection> selections = Target_Text_Edit->extraSelections();
    selections.clear();
    Target_Text_Edit->setExtraSelections(selections);

    if (regex.isValid() and
        (regex_pattern.length() > 0)) {
        RegEx_Valid = true;

        QStringList capture_groups = regex.namedCaptureGroups();
        for (int idx = 0; idx < capture_groups.size(); ++idx) {
            if (capture_groups.at(idx).isNull()) {
                if (idx == 0)
                    capture_groups[idx] = "Entire";
                else
                    capture_groups[idx] = "Group " + QString::number(idx);
            }
        }

        const int capturingGroupsCount = regex.captureCount() + 1;

        RegEx_Captures_Highlight(regex, Target_Text_Edit);

        QRegularExpressionMatchIterator regex_iterator =
                                          regex.globalMatch(target_text, offsetSpinBox->value(), matchType, matchOptions);

        QTextEdit::ExtraSelection selection_green;
        QTextCharFormat format_green = selection_green.format;
        format_green.setBackground(Green_Match_Color);
        selection_green.format = format_green;

        QTextEdit::ExtraSelection selection_light_green;
        QTextCharFormat format_light_green = selection_light_green.format;
        format_light_green.setBackground(Light_Green_Match_Color);
        selection_light_green.format = format_light_green;

        QTextEdit::ExtraSelection selection_blue;
        QTextCharFormat format_blue = selection_blue.format;
        format_blue.setBackground(Blue_Match_Color);
        selection_blue.format = format_blue;

        QTextEdit::ExtraSelection selection_light_blue;
        QTextCharFormat format_light_blue = selection_light_blue.format;
        format_light_blue.setBackground(Light_Blue_Match_Color);
        selection_light_blue.format = format_light_blue;

        bool selection_switch = false;
        int match_idx = 0;
        while (regex_iterator.hasNext()) {
            QRegularExpressionMatch match = regex_iterator.next();
            selection_switch = not selection_switch;

            QTreeWidgetItem *matchDetailTopItem = new QTreeWidgetItem(Matches_Tree);
            if (selection_switch)
                matchDetailTopItem->setBackgroundColor(0, Green_Match_Color);
            else
                matchDetailTopItem->setBackgroundColor(0, Blue_Match_Color);
            matchDetailTopItem->setText(0, QString::number(match_idx));

            for (int captureGroupIndex = 0; captureGroupIndex < capturingGroupsCount; ++captureGroupIndex) {
                QTreeWidgetItem *matchDetailItem = new QTreeWidgetItem(matchDetailTopItem);

                if (selection_switch) {
                    if (captureGroupIndex == 0) {
                        matchDetailItem->setBackgroundColor(1, Green_Match_Color);
                        matchDetailItem->setBackgroundColor(2, Green_Match_Color);
                    }
                    else if ((captureGroupIndex % 2) > 0) {
                        matchDetailItem->setBackgroundColor(1, Light_Green_Match_Color);
                        matchDetailItem->setBackgroundColor(2, Light_Green_Match_Color);
                    }
                    else {
                        matchDetailItem->setBackgroundColor(1, Green_Match_Color);
                        matchDetailItem->setBackgroundColor(2, Green_Match_Color);
                    }
                }
                else {
                    if (captureGroupIndex == 0) {
                        matchDetailItem->setBackgroundColor(1, Blue_Match_Color);
                        matchDetailItem->setBackgroundColor(2, Blue_Match_Color);
                    }
                    else if ((captureGroupIndex % 2) > 0) {
                        matchDetailItem->setBackgroundColor(1, Light_Blue_Match_Color);
                        matchDetailItem->setBackgroundColor(2, Light_Blue_Match_Color);
                    }
                    else {
                        matchDetailItem->setBackgroundColor(1, Blue_Match_Color);
                        matchDetailItem->setBackgroundColor(2, Blue_Match_Color);
                    }
                }
                matchDetailItem->setText(1, capture_groups.at(captureGroupIndex));
                matchDetailItem->setText(2, match.captured(captureGroupIndex));
                if (match.capturedStart(captureGroupIndex) >= 0) {
                    matchDetailItem->setText(3, (QString::number(match.capturedStart(captureGroupIndex)) +
                                                 "-" +
                                                 QString::number(match.capturedEnd(captureGroupIndex) - 1) +
                                                 " (" +
                                                 QString::number(match.capturedLength(captureGroupIndex)) +
                                                 ")"));
                }
                else
                    matchDetailItem->setText(3, "");
            }

            match_idx += 1;
        }

        // Parse (and display elements of) the RegEx pattern itself
        QRegularExpression parse_regex(Parse_RegEx_Pattern);

        if (parse_regex.isValid()) {
            RegEx_Elements_Compute(parse_regex, regex_pattern);
        }
        // Parse (and display elements of) the RegEx pattern itself

        // Find the beginning and ending of all groups
        QRegularExpression regex_regex("(?:\\\\\\\\|\\\\\\(|\\\\\\)|\\\\\\[)|(?<class>\\[(?:(?:\\^?\\][^]]*)|[^]]+)\\])|(?<paren>[()])");
        QRegularExpressionMatchIterator regex_regex_iterator = regex_regex.globalMatch(regex_pattern);
        RegEx_Pattern_Group_Capture_Map.clear();
        RegEx_Pattern_Group_Capture_Map.push_back(QVector<int>{0, (regex_pattern.length() - 1)});
        while (regex_regex_iterator.hasNext()) {
            QRegularExpressionMatch match = regex_regex_iterator.next();
            int begin_capture = match.capturedStart();
            if (regex_pattern[begin_capture] == '(') {
                RegEx_Pattern_Group_Capture_Map.push_back(QVector<int>{begin_capture, -1});
            }
            else if (regex_pattern[begin_capture] == ')') {
                int cap_idx = RegEx_Pattern_Group_Capture_Map.count() - 1;
                while (cap_idx > -1) {
                    if (RegEx_Pattern_Group_Capture_Map[cap_idx][1] < 0) {
                        RegEx_Pattern_Group_Capture_Map[cap_idx][1] = begin_capture;
                        break;
                    }
                    cap_idx -= 1;
                }
            }
        }

        int cap_idx = 1;
        // Remove non-capturing groups, leave only capturing groups
        while (cap_idx < RegEx_Pattern_Group_Capture_Map.count()) {
            int begin_capture = RegEx_Pattern_Group_Capture_Map[cap_idx][0];
            if ((begin_capture + 2) < regex_pattern.length()) {
                if ((regex_pattern[begin_capture + 1] == '?') and
                    (regex_pattern[begin_capture + 2] == ':')) {
                    RegEx_Pattern_Group_Capture_Map.remove(cap_idx);
                    cap_idx -= 1;
                }
            }
            cap_idx += 1;
        }

        Trace_Dirty = true;

        if (Trace_Dirty and RegEx_Valid and
            (RegExIDE_Pages->currentIndex() == Trace_Tab_Index))
            RegEx_Trace(regex_pattern, target_text);
    }

    Matches_Tree->expandAll();

    Groups_Tree->clear();
    Groups_Tree->setEnabled(regex.isValid());

    regexpStatusLabel->setText(tr(""));
    if (regex_pattern.length() > 0) {
        if (regex.isValid()) {
            regexpStatusLabel->setText(tr("Valid"));

            const QStringList capture_groups = regex.namedCaptureGroups();
            for (int i = 0; i < capture_groups.size(); ++i) {
                const QString current_capture_group = capture_groups.at(i);

                QTreeWidgetItem *capture_group_item = new QTreeWidgetItem(Groups_Tree);
                capture_group_item->setText(0, QString::number(i));
                capture_group_item->setText(1, current_capture_group.isNull() ? tr("<no name>") : current_capture_group);
            }
        }
        else
            regexpStatusLabel->setText(tr("Invalid: syntax error at position %1 (%2)")
                                       .arg(regex.patternErrorOffset())
                                       .arg(regex.errorString()));
    }

    Replace_Pattern_Result->clear();

    QString replace_pattern = Replace_Pattern_Edit->toPlainText();
    if (Replace_With_Empty_Replace_Pattern or
        (replace_pattern.length() > 0)) {
        if (regex.isValid() and
            (regex_pattern.length() > 0)) {
            QString target_text = Target_Text_Edit->toPlainText();
            QString replace_result = target_text.replace(regex, replace_pattern);
            Replace_Pattern_Result->setPlainText(replace_result);
        }
    }

    setUpdatesEnabled(true);
}

void
RegularExpressionIDE::RegEx_Captures_Highlight ( QRegularExpression Capture_RegularExpression,
                                                 PlainTextEdit *Target_PlainTextEdit ) {
    QTextEdit::ExtraSelection selection_green;
    QTextCharFormat format_green = selection_green.format;
    format_green.setBackground(Green_Match_Color);
    selection_green.format = format_green;

    QTextEdit::ExtraSelection selection_blue;
    QTextCharFormat format_blue = selection_blue.format;
    format_blue.setBackground(Blue_Match_Color);
    selection_blue.format = format_blue;

    QList<QTextEdit::ExtraSelection> parsed_selections = Target_PlainTextEdit->extraSelections();

    QRegularExpressionMatchIterator parse_regex_iterator =
                                      Capture_RegularExpression.globalMatch(Target_PlainTextEdit->toPlainText());

    bool selection_switch = false;
    while (parse_regex_iterator.hasNext()) {
        QRegularExpressionMatch match = parse_regex_iterator.next();
        selection_switch = not selection_switch;

        QTextCursor cursor = Target_PlainTextEdit->textCursor();
        cursor.setPosition(match.capturedStart());
        cursor.setPosition(match.capturedEnd(), QTextCursor::KeepAnchor);

        if (selection_switch) {
            selection_green.cursor = cursor;
            parsed_selections.append(selection_green);
        }
        else {
            selection_blue.cursor = cursor;
            parsed_selections.append(selection_blue);
        }
    }

    Target_PlainTextEdit->setExtraSelections(parsed_selections);
}

void
RegularExpressionIDE::RegEx_Elements_Compute ( QRegularExpression Capture_RegularExpression,
                                               QString Target_Text ) {
    // struct RegEx_Element {
    //     int Element_Begin;
    //     int Element_End;
    //     QString Element_Type;
    //     QString Element_Text;
    // };

    Pattern_Elements_Tree->clear();
    QTreeWidgetItem *pattern_root = new QTreeWidgetItem(Pattern_Elements_Tree,
                                                        (QStringList()
                                                         << "Entire Pattern" << ""));
                                                         // << (QString::number(0) +
                                                         //     QString("-") +
                                                         //     QString::number(Target_Text.length()))));
    pattern_root->setData(0, Qt::UserRole, 0);
    pattern_root->setData(0, (Qt::UserRole + 1), Target_Text.length());

    QTreeWidgetItem *current_root = pattern_root;
    QTreeWidgetItem *item_root;

    QStringList capture_groups = Capture_RegularExpression.namedCaptureGroups();
    for (int idx = 0; idx < capture_groups.size(); ++idx) {
        if (capture_groups.at(idx).isNull()) {
            if (idx == 0)
                capture_groups[idx] = "?0";
            else
                capture_groups[idx] = QString("?") + QString::number(idx);
        }
    }

    QRegularExpressionMatchIterator parse_regex_iterator =
                                      Capture_RegularExpression.globalMatch(Target_Text);

    while (parse_regex_iterator.hasNext()) {
        QRegularExpressionMatch match = parse_regex_iterator.next();
        if (match.captured().startsWith(")")) {
            current_root = current_root->parent();
        }
        else {
            // Must have already encountered the open paren and ...
            // ... extracted close paren information
            QString element_type = capture_groups[match.lastCapturedIndex()];
            QString element_text = match.captured();
            int match_begin = match.capturedStart();
            int match_end = match.capturedEnd();

            bool indent = false;

            if (element_text.startsWith("(")) {
                indent = true;
                // Find matching close paren
                QRegularExpressionMatchIterator paren_close_iterator = QRegularExpressionMatchIterator(parse_regex_iterator);
                int paren_level = 0;
                while (paren_close_iterator.hasNext()) {
                    QRegularExpressionMatch match = paren_close_iterator.next();
                    if (match.captured().startsWith("("))
                        paren_level += 1;
                    else if (match.captured().startsWith(")")) {
                        if (paren_level == 0) {
                            match_end = match.capturedEnd();
                            break;
                        }
                        paren_level -= 1;
                    }
                }

                // Figure out which type of group
                if (element_text.startsWith("(?:"))
                    element_type = "Non-capturing group";
                else if (element_text.startsWith("(?<="))
                    element_type = "Positive lookbehind";
                else if (element_text.startsWith("(?<!"))
                    element_type = "Negative lookbehind";
                else if (element_text.startsWith("(?="))
                    element_type = "Positive lookahead";
                else if (element_text.startsWith("(?!"))
                    element_type = "Negative lookahead";
                else if (element_text.startsWith("(?<"))
                    element_type = "Named capturing group";
                else
                    element_type = "Capturing group";

                element_text += " …";

            }
            else if (element_text.startsWith("[")) {
                if (element_text.startsWith("[^"))
                    element_type = "Negated char class";
                else
                    element_type = "Character class";
            }
            else if (element_text.startsWith("|")) {
                element_type = "Alternation";
            }
            else if (element_text.startsWith(".")) {
                element_type = "Any character";
            }
            else if (element_type == "?0") element_type = "Literal";

            item_root = new QTreeWidgetItem(current_root,
                                            (QStringList()
                                             << element_type << element_text));
                                             // << (QString::number(match_begin) +
                                             //     QString("-") +
                                             //     QString::number(match_end))));
            item_root->setData(0, Qt::UserRole, match_begin);
            item_root->setData(0, (Qt::UserRole + 1), match_end);

            if (indent) {
                // Indent tree one level
                current_root = item_root;
            }
        }
    }

    Pattern_Elements_Tree->expandToDepth(1);
}

void
RegularExpressionIDE::onEscapeSelectedText ( bool ) {
    QString selected_text = RegEx_Pattern_Edit->textCursor().selectedText();
    if (selected_text.length() > 0) {
        Defer_UI_Refresh = true;
        QString escaped_selected_text = QRegularExpression::escape(selected_text);
        RegEx_Pattern_Edit->insertPlainText(escaped_selected_text);
        Defer_UI_Refresh = false;
        UI_Refresh();
    }
}

void
RegularExpressionIDE::onRegexPatternCopyToApplyClicked ( bool ) {
    if (RegEx_Valid) {
        // Don't defeat Undo/Redo
        Apply_Find_Pattern->selectAll();
        Apply_Find_Pattern->insertPlainText(RegEx_Pattern_Edit->toPlainText());

        Apply_Target_Offset = -1;
    }
    else {
        // Error message
    }
}

void
RegularExpressionIDE::onRegexPatternCopyClicked ( bool ) {
#ifndef QT_NO_CLIPBOARD
    QToolButton *sender_tool_button = dynamic_cast<QToolButton*>(sender());
    Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
    if ((not (sender_tool_button == NULL)) or
        ((modifiers & Qt::ControlModifier) == Qt::ControlModifier)) {
        QClipboard *clipboard = QGuiApplication::clipboard();
        if (clipboard) {
            QString pattern = RegEx_Pattern_Edit->toPlainText();
            if (pattern.length() > 0) {
                clipboard->setText(pattern);
            }
        }
    }
#endif
}

void
RegularExpressionIDE::onRegexPatternCopyEscapedClicked ( bool ) {
#ifndef QT_NO_CLIPBOARD
    QToolButton *sender_tool_button = dynamic_cast<QToolButton*>(sender());
    Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
    if ((not (sender_tool_button == NULL)) or
        ((modifiers & Qt::ControlModifier) == Qt::ControlModifier)) {
        QClipboard *clipboard = QGuiApplication::clipboard();
        if (clipboard) {
            QString pattern = RegEx_Pattern_Edit->toPlainText();
            if (pattern.length() > 0) {
                QString pattern_escaped = pattern;
                pattern_escaped.replace(QLatin1String("\\"), QLatin1String("\\\\"));
                pattern_escaped.replace(QLatin1String("\""), QLatin1String("\\\""));
                pattern_escaped.prepend(QLatin1Char('"'));
                pattern_escaped.append(QLatin1Char('"'));
                clipboard->setText(pattern_escaped);
            }
        }
    }
#endif
}

void
RegularExpressionIDE::onReplacePatternCopyToApplyClicked ( bool ) {
    if (RegEx_Valid) {
        // Don't defeat Undo/Redo
        Apply_Replace_Pattern->selectAll();
        Apply_Replace_Pattern->insertPlainText(Replace_Pattern_Edit->toPlainText());

        Apply_Target_Offset = -1;
    }
    else {
        // Error message
    }
}

void
RegularExpressionIDE::onReplacePatternCopyClicked ( bool ) {
#ifndef QT_NO_CLIPBOARD
    QToolButton *sender_tool_button = dynamic_cast<QToolButton*>(sender());
    Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
    if ((not (sender_tool_button == NULL)) or
        ((modifiers & Qt::ControlModifier) == Qt::ControlModifier)) {
        QClipboard *clipboard = QGuiApplication::clipboard();
        if (clipboard) {
            QString pattern = Replace_Pattern_Edit->toPlainText();
            if (pattern.length() > 0) {
                clipboard->setText(pattern);
            }
        }
    }
#endif
}

void
RegularExpressionIDE::onReplacePatternCopyEscapedClicked ( bool ) {
#ifndef QT_NO_CLIPBOARD
    QToolButton *sender_tool_button = dynamic_cast<QToolButton*>(sender());
    Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
    if ((not (sender_tool_button == NULL)) or
        ((modifiers & Qt::ControlModifier) == Qt::ControlModifier)) {
        QClipboard *clipboard = QGuiApplication::clipboard();
        if (clipboard) {
            QString pattern = Replace_Pattern_Edit->toPlainText();
            if (pattern.length() > 0) {
                QString pattern_escaped = pattern;
                pattern_escaped.replace(QLatin1String("\\"), QLatin1String("\\\\"));
                pattern_escaped.replace(QLatin1String("\""), QLatin1String("\\\""));
                pattern_escaped.prepend(QLatin1Char('"'));
                pattern_escaped.append(QLatin1Char('"'));
                clipboard->setText(pattern_escaped);
            }
        }
    }
#endif
}

void
RegularExpressionIDE::onGroupsTreeClicked ( QModelIndex model_index ) {
    if (model_index.isValid()) {
        QTreeWidget *sender_groups_tree = dynamic_cast<QTreeWidget*>(sender());
        QModelIndex clicked_index = sender_groups_tree->model()->index(model_index.row(), 0);

        int clicked_group_idx = sender_groups_tree->model()->data(clicked_index).toInt();

        if (clicked_group_idx < RegEx_Pattern_Group_Capture_Map.count()) {
            int begin_capture = RegEx_Pattern_Group_Capture_Map[clicked_group_idx][0];
            int end_capture = RegEx_Pattern_Group_Capture_Map[clicked_group_idx][1];

            QTextEdit::ExtraSelection selection;
            QTextCharFormat format = selection.format;
            format.setBackground(Qt::green);
            selection.format = format;

            QTextCursor cursor = RegEx_Pattern_Edit->textCursor();
            cursor.setPosition(begin_capture);
            cursor.setPosition((end_capture + 1), QTextCursor::KeepAnchor);
            selection.cursor = cursor;

            QList<QTextEdit::ExtraSelection> selections;
            selections.append(selection);

            RegEx_Pattern_Edit->setExtraSelections(selections);
        }
    }
}

void
RegularExpressionIDE::onPatternElementsTreeClicked ( QModelIndex model_index ) {
    if (model_index.isValid()) {
        // item_root->setData(0, Qt::UserRole, match_begin);
        // item_root->setData(0, (Qt::UserRole + 1), match_end);

        QModelIndex parent_index = model_index.parent();
        const QAbstractItemModel *tree_model = model_index.model();
        QModelIndex clicked_index = tree_model->index(model_index.row(), 0, parent_index);
        int begin_capture = tree_model->data(clicked_index, Qt::UserRole).toInt();
        int end_capture = tree_model->data(clicked_index, (Qt::UserRole + 1)).toInt() - 1;

        QTextEdit::ExtraSelection selection;
        QTextCharFormat format = selection.format;
        format.setBackground(Qt::green);
        selection.format = format;

        QTextCursor cursor = RegEx_Pattern_Edit->textCursor();
        cursor.setPosition(begin_capture);
        cursor.setPosition((end_capture + 1), QTextCursor::KeepAnchor);
        selection.cursor = cursor;

        QList<QTextEdit::ExtraSelection> selections;
        selections.append(selection);

        RegEx_Pattern_Edit->setExtraSelections(selections);
    }
}

#endif // REGEXIDE_MAIN_PAGE_CPP
