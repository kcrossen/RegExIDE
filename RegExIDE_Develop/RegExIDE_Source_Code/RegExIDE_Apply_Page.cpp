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

#ifndef REGEXIDE_APPLY_PAGE_CPP
#define REGEXIDE_APPLY_PAGE_CPP

#include "RegularExpressionIDE.h"

QWidget*
RegularExpressionIDE::Initialize_Apply_Page_UI ( ) {
    QWidget* container = new QWidget();
    container->setContentsMargins(0, 0, 0, 0);
    container->setMinimumHeight(UI_Minimum_Height);

    QVBoxLayout *container_layout = new QVBoxLayout;
    container_layout->setContentsMargins(0, 0, 0, 0);
    container_layout->setSpacing(2);

    QHBoxLayout *series_command_layout = new QHBoxLayout;
    series_command_layout->setContentsMargins(0, 0, 0, 0);
    series_command_layout->addWidget(new QLabel(tr("<b>Series:<\b>")), 0);
    Series_ComboBox = new QComboBox();
    // Series_ComboBox->lineEdit()->setReadOnly(true);
    Series_ComboBox->setEditable(false);
    Series_ComboBox->setInsertPolicy(QComboBox::NoInsert);
    series_command_layout->addWidget(Series_ComboBox, 0);

    QToolButton *series_start_series = new QToolButton();
    series_start_series->setText(tr("Start Series"));
    connect(series_start_series, SIGNAL(clicked(bool)), this, SLOT(onSeriesStartSeriesClicked(bool)));
    series_command_layout->addWidget(series_start_series, 0);

    series_command_layout->addSpacing(8);

    QToolButton *series_replace = new QToolButton();
    series_replace->setText(tr("Replace"));
    connect(series_replace, SIGNAL(clicked(bool)), this, SLOT(onSeriesReplaceClicked(bool)));
    series_command_layout->addWidget(series_replace, 0);

    QToolButton *series_next_step = new QToolButton();
    series_next_step->setText(tr("Next Step"));
    connect(series_next_step, SIGNAL(clicked(bool)), this, SLOT(onSeriesNextStepClicked(bool)));
    series_command_layout->addWidget(series_next_step, 0);

    series_command_layout->addSpacing(8);

    QToolButton *series_replace_next_step = new QToolButton();
    series_replace_next_step->setText(tr("Replace, Next Step"));
    connect(series_replace_next_step, SIGNAL(clicked(bool)), this, SLOT(onSeriesReplaceNextStepClicked(bool)));
    series_command_layout->addWidget(series_replace_next_step, 0);

    series_command_layout->addStretch(100);
    container_layout->addLayout(series_command_layout, 0);

    Series_Help_Label = new QLabel("");
    // Series_Help_Label->setAlignment(Qt::AlignHCenter);
    container_layout->addWidget(Series_Help_Label, 0);

    QFrame *horizontal_separator = new QFrame;
    horizontal_separator->setFrameStyle(QFrame::HLine | QFrame::Raised);
    container_layout->addWidget(horizontal_separator, 0);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(15);

    QHBoxLayout *regex_label_command_layout = new QHBoxLayout;
    regex_label_command_layout->setContentsMargins(0, 0, 0, 0);
    regex_label_command_layout->addWidget(new QLabel(tr("<b>Find pattern<\b>")), 0);

    regex_label_command_layout->addSpacing(80);

    regex_label_command_layout->addStretch(50);

    QToolButton *copy_from_rx_tab = new QToolButton();
    copy_from_rx_tab->setText(tr("Copy from Regular Expression Tab"));
    copy_from_rx_tab->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    connect(copy_from_rx_tab, SIGNAL(clicked(bool)), this, SLOT(onCopyFromRegularExpressionTabClicked(bool)));
    regex_label_command_layout->addWidget(copy_from_rx_tab, 0);

    regex_label_command_layout->addStretch(50);

    regex_label_command_layout->addWidget(new QLabel(tr("<b>Replace pattern<\b>")), 0);
    regex_label_command_layout->addSpacing(4);
    Apply_Replace_Scripted = new QCheckBox("Scripted");
    regex_label_command_layout->addWidget(Apply_Replace_Scripted, 0);
    container_layout->addLayout(regex_label_command_layout, 0);

    QHBoxLayout *regex_layout = new QHBoxLayout;
    regex_layout->setContentsMargins(0, 0, 0, 0);

    Apply_Find_Pattern = new PlainTextEdit(this, RegEx_Matching);
    Apply_Find_Pattern->setFont(font);
    Apply_Find_Pattern->setReadOnly(false);
    regex_layout->addWidget(Apply_Find_Pattern, 50);

    Apply_Replace_Pattern = new PlainTextEdit(this, RegEx_Matching);
    Apply_Replace_Pattern->setFont(font);
    Apply_Replace_Pattern->setReadOnly(false);
    regex_layout->addWidget(Apply_Replace_Pattern, 50);

    container_layout->addLayout(regex_layout, 50);
    container_layout->addSpacing(4);

    QHBoxLayout *target_layout = new QHBoxLayout;
    target_layout->setContentsMargins(0, 0, 0, 0);
    target_layout->addWidget(new QLabel(tr("<b>Target</b>")), 0);

    #define target_layout_extra_space 4

    target_layout->addSpacing(target_layout_extra_space);

    QToolButton *from_file = new QToolButton();
    from_file->setText(tr("From File"));
    connect(from_file, SIGNAL(clicked(bool)), this, SLOT(onTargetFromFileClicked(bool)));
    target_layout->addWidget(from_file, 0);

    QToolButton *from_clipboard = new QToolButton();
    from_clipboard->setText(tr("From Clipboard"));
    connect(from_clipboard, SIGNAL(clicked(bool)), this, SLOT(onTargetFromClipboardClicked(bool)));
    target_layout->addWidget(from_clipboard, 0);

    QToolButton *from_memory = new QToolButton();
    from_memory->setText(tr("From Memory"));
    connect(from_memory, SIGNAL(clicked(bool)), this, SLOT(onTargetFromMemoryClicked(bool)));
    target_layout->addWidget(from_memory, 0);

    target_layout->addSpacing(8);

    target_layout->addStretch(50);

    QToolButton *find_next = new QToolButton();
    find_next->setText(tr("Find Next"));
    connect(find_next, SIGNAL(clicked(bool)), this, SLOT(onFindNextClicked(bool)));
    target_layout->addWidget(find_next, 0);

    QToolButton *replace_find_next = new QToolButton();
    replace_find_next->setText(tr("Replace && Find Next"));
    connect(replace_find_next, SIGNAL(clicked(bool)), this, SLOT(onReplaceFindNextClicked(bool)));
    target_layout->addWidget(replace_find_next, 0);

    target_layout->addSpacing(target_layout_extra_space);

    QToolButton *replace_all = new QToolButton();
    replace_all->setText(tr("Replace All"));
    connect(replace_all, SIGNAL(clicked(bool)), this, SLOT(onReplaceAllClicked(bool)));
    target_layout->addWidget(replace_all, 0);

    target_layout->addStretch(50);

    QToolButton *to_replace_pattern = new QToolButton();
    to_replace_pattern->setText(tr("To Replace"));
    connect(to_replace_pattern, SIGNAL(clicked(bool)), this, SLOT(onTargetToReplaceClicked(bool)));
    target_layout->addWidget(to_replace_pattern, 0);

    QToolButton *to_memory = new QToolButton();
    to_memory->setText(tr("To Memory"));
    connect(to_memory, SIGNAL(clicked(bool)), this, SLOT(onTargetToMemoryClicked(bool)));
    target_layout->addWidget(to_memory, 0);

    QToolButton *to_clipboard = new QToolButton();
    to_clipboard->setText(tr("To Clipboard"));
    connect(to_clipboard, SIGNAL(clicked(bool)), this, SLOT(onTargetToClipboardClicked(bool)));
    target_layout->addWidget(to_clipboard, 0);

    QToolButton *to_file = new QToolButton();
    to_file->setText(tr("To File"));
    connect(to_file, SIGNAL(clicked(bool)), this, SLOT(onTargetToFileClicked(bool)));
    target_layout->addWidget(to_file, 0);

    container_layout->addLayout(target_layout, 0);
    Apply_Target = new PlainTextEdit(this);
    Apply_Target->setFont(font);
    Apply_Target->setReadOnly(false);
    Apply_Target->setLineWrapMode(QPlainTextEdit::NoWrap);
    connect(Apply_Target, SIGNAL(cursorPositionChanged()), this, SLOT(onApplyTargetCursorPositionChanged()));
    container_layout->addWidget(Apply_Target, 150);

    container->setLayout(container_layout);
    return container;
}

void
RegularExpressionIDE::Series_Step_Initialize ( ) {
    OrderedVariantMap regex_descr = toOrderedMap(Series_RegEx_Descriptors[Series_Step]);
    QString series_help_text =
              "<b>Step " + QString::number(Series_Step + 1) + " of " +
              QString::number(Series_RegEx_Descriptors.count());
    if (regex_descr.contains("Series_Help")) {
        series_help_text += ":  </b>" + regex_descr.value("Series_Help").toString();
    }
    else series_help_text += "</b>";
    Series_Help_Label->setText(series_help_text);

    Series_Before_Replace.clear();
    if (regex_descr.contains("Series_Before_Replace"))
        Series_Before_Replace = regex_descr.value("Series_Before_Replace").toString();
    Series_After_Replace.clear();
    if (regex_descr.contains("Series_After_Replace"))
        Series_After_Replace = regex_descr.value("Series_After_Replace").toString();

    if (regex_descr.contains("RegEx_Pattern")) {
        // Don't defeat Undo/Redo
        Apply_Find_Pattern->Set_PlainText(regex_descr.value("RegEx_Pattern").toString());
    }

    if (regex_descr.contains("Replace_Pattern")) {
        // Don't defeat Undo/Redo
        Apply_Replace_Pattern->Set_PlainText(regex_descr.value("Replace_Pattern").toString());
        Apply_Replace_Pattern->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        Apply_Replace_Scripted->setChecked(false);
    }

    if (regex_descr.contains("Replace_Script")) {
        // Don't defeat Undo/Redo
        Apply_Replace_Pattern->Set_PlainText(regex_descr.value("Replace_Script").toString());
        Apply_Replace_Pattern->setLineWrapMode(QPlainTextEdit::NoWrap);
        Apply_Replace_Scripted->setChecked(true);
    }


    if (regex_descr.contains("Target")) {
        // Don't defeat Undo/Redo
        Apply_Target->Set_PlainText(regex_descr.value("Target").toString());
    }
    Apply_Target_Offset = -1;
}

void
RegularExpressionIDE::Series_Replace ( ) {
    if (Series_Before_Replace.length() > 0) {
        if (Series_Before_Replace == "Target_From_Clipboard") {
            onTargetFromClipboardClicked();
        }
        else if (Series_Before_Replace == "Target_From_Memory") {
            onTargetFromMemoryClicked();
        }
        else if (Series_Before_Replace == "Target_Swap_Memory") {
            QString target_text = Apply_Target->toPlainText();
            Apply_Target->Set_PlainText(Apply_Memory);
            Apply_Memory = target_text;
        }
        else if (Series_Before_Replace == "Target_To_Replace") {
            onTargetToReplaceClicked();
        }
        else if (Series_Before_Replace == "Target_To_Memory") {
            onTargetToMemoryClicked();
        }
        else if (Series_Before_Replace == "Target_To_Clipboard") {
            onTargetToClipboardClicked();
        }
    }

    if (not Apply_Replace_Scripted->isChecked())
        Replace_All();
    else
        Replace_All_Scripted();

    if (Series_After_Replace.length() > 0) {
        if (Series_After_Replace == "Target_From_Clipboard") {
            onTargetFromClipboardClicked();
        }
        else if (Series_After_Replace == "Target_From_Memory") {
            onTargetFromMemoryClicked();
        }
        else if (Series_After_Replace == "Target_Swap_Memory") {
            QString target_text = Apply_Target->toPlainText();
            Apply_Target->Set_PlainText(Apply_Memory);
            Apply_Memory = target_text;
        }
        else if (Series_After_Replace == "Target_To_Replace") {
            onTargetToReplaceClicked();
        }
        else if (Series_After_Replace == "Target_To_Memory") {
            onTargetToMemoryClicked();
        }
        else if (Series_After_Replace == "Target_To_Clipboard") {
            onTargetToClipboardClicked();
        }
    }
}

void
RegularExpressionIDE::Replace_All ( ) {
    if (Apply_Target_Offset < 0) Apply_Target_Offset = 0;

    const QString regex_pattern = Apply_Find_Pattern->toPlainText();

    QRegularExpression regex = QRegularExpression(regex_pattern);
    if (regex.isValid() and
        (regex_pattern.length() > 0)) {
        QString target_text = Apply_Target->toPlainText();
        QRegularExpressionMatchIterator regex_iterator =
                                          regex.globalMatch(target_text, Apply_Target_Offset);
        if (regex_iterator.hasNext()) {
            // At least one found
            const QString replace_pattern = Apply_Replace_Pattern->toPlainText();
            if (Replace_With_Empty_Replace_Pattern or
                (replace_pattern.length() > 0)) {
                if (regex.isValid() and
                    (regex_pattern.length() > 0)) {
                    QString replace_result = target_text.replace(regex, replace_pattern);
                    // Don't defeat Undo/Redo
                    Apply_Target->Set_PlainText(replace_result);
                }
            }
        }
    }
}

QString Apply_Fatal_Error_Messages;

static void apply_fatal_error_handler ( void *udata,
                                         const char *msg ) {
    (void) udata;  /* ignored in this case, silence warning */

    /* Note that 'msg' may be NULL. */
    Apply_Fatal_Error_Messages += QString("*** FATAL ERROR: ") + QString((msg ? msg : "No message"));
    abort();
}

QString Apply_Print_Messages;

static duk_ret_t script_dummy_native_print ( duk_context *js_context ) {
    duk_push_string(js_context, " ");
    duk_insert(js_context, 0);
    duk_join(js_context, duk_get_top(js_context) - 1);
    Apply_Print_Messages += QString(duk_safe_to_string(js_context, -1)) + QString("\n");
    return 0;
}

void
RegularExpressionIDE::Replace_All_Scripted ( ) {
    if (Apply_Target_Offset < 0) Apply_Target_Offset = 0;

    Apply_Fatal_Error_Messages.clear();
    QString script_error_message;
    bool Script_Error = false;

    const QString regex_pattern = Apply_Find_Pattern->toPlainText();

    QRegularExpression regex = QRegularExpression(regex_pattern);
    if (regex.isValid() and
        (regex_pattern.length() > 0)) {
        QStringList capture_groups = regex.namedCaptureGroups();
        const int capture_groups_count = regex.captureCount() + 1;

        QString target_text = Apply_Target->toPlainText();
        QRegularExpressionMatchIterator regex_iterator =
                                          regex.globalMatch(target_text, Apply_Target_Offset);
        if (regex_iterator.hasNext()) {
            // At least one found
            // QJSEngine js_Engine;
            // QJSValue function = js_Engine.evaluate(Apply_Replace_Pattern->toPlainText());

            duk_context *js_context = duk_create_heap(NULL, NULL, NULL, NULL, apply_fatal_error_handler);

            duk_push_global_object(js_context);
            duk_push_c_function(js_context, script_dummy_native_print, DUK_VARARGS);
            duk_put_prop_string(js_context, -2, "print");

            QString replace_script = Apply_Replace_Pattern->toPlainText();
            duk_push_string(js_context, replace_script.toLatin1().data());
            if (duk_peval(js_context) != 0) {
                // Compile error
                script_error_message += QString("Error: ") +
                                        QString(duk_safe_to_string(js_context, -1)) +
                                        QString("\n");
                // Set up Script page for debugging
                Script_Find_Pattern->clear();
                Script_Target->clear();
                Script_JavaScript_Editor->Set_PlainText(replace_script);
                Script_Message_Text->Set_PlainText(script_error_message +
                                                   Apply_Print_Messages +
                                                   Apply_Fatal_Error_Messages);
                Script_Error = true;
            }
            duk_pop(js_context);  /* ignore result */

            QList <QRegularExpressionMatch> regex_matches;
            QStringList regex_replaces;

            if (not Script_Error) {
                duk_push_global_object(js_context);

                while (regex_iterator.hasNext()) {
                    Apply_Print_Messages.clear();
                    QRegularExpressionMatch match = regex_iterator.next();
                    regex_matches.append(match);
                    // regex_replaces.append(function.call(QJSValueList() << match.captured()).toString());
                    QString match_text = match.captured();
                    QString replace_text = "";
                    duk_get_prop_string(js_context, -1 /*index*/, "replace_function");

                    // Push matched text onto stack as match.group_0 argument property ...
                    // ... (whether it's needed or not)
                    // duk_push_string(js_context, match_text.toLatin1().data());
                    duk_idx_t obj_idx = duk_push_object(js_context);
                    for (int idx = 0; idx < capture_groups_count; idx += 1) {
                        QString match_capture = match.captured(idx);
                        QString match_name = QString("group_") + QString::number(idx);
                        duk_push_string(js_context, match_capture.toLatin1().data());
                        duk_put_prop_string(js_context, obj_idx, match_name.toLatin1().data());
                        match_name = QString::number(idx);
                        duk_push_string(js_context, match_capture.toLatin1().data());
                        duk_put_prop_string(js_context, obj_idx, match_name.toLatin1().data());
                        if (not capture_groups.at(idx).isNull()) {
                            match_capture = match.captured(capture_groups.at(idx));
                            match_name = QString("group_") + capture_groups.at(idx);
                            duk_push_string(js_context, match_capture.toLatin1().data());
                            duk_put_prop_string(js_context, obj_idx, match_name.toLatin1().data());
                            match_name = capture_groups.at(idx);
                            duk_push_string(js_context, match_capture.toLatin1().data());
                            duk_put_prop_string(js_context, obj_idx, match_name.toLatin1().data());
                        }
                    }

                    if (duk_pcall(js_context, 1 /*nargs*/) != 0) {
                        // Runtime error
                        script_error_message += QString("Error: ") +
                                                QString(duk_safe_to_string(js_context, -1)) +
                                                QString("\n");
                        // Set up Script page for debugging
                        Script_Find_Pattern->Set_PlainText(regex_pattern);
                        Script_Target->Set_PlainText(match.captured());
                        Script_JavaScript_Editor->Set_PlainText(replace_script);
                        Script_Message_Text->Set_PlainText(script_error_message +
                                                           Apply_Print_Messages +
                                                           Apply_Fatal_Error_Messages);
                        Script_Error = true;
                        break;
                    } else {
                        replace_text = QString(duk_safe_to_string(js_context, -1));
                    }
                    duk_pop(js_context);  /* pop result/error */

                    regex_replaces.append(replace_text);
                }
            }

            duk_destroy_heap(js_context);

            // if (script_error_message.length() > 0) qDebug() << script_error_message;
            // if (Apply_Fatal_Error_Messages.length() > 0) qDebug() << Apply_Fatal_Error_Messages;

            if (not Script_Error) {
                QString replace_result = target_text;
                for (int replace_idx = regex_matches.count() - 1; replace_idx >= 0; replace_idx -= 1) {
                    QRegularExpressionMatch match = regex_matches.takeLast();
                    QString replace = regex_replaces.takeLast();
                    replace_result.replace(match.capturedStart(), match.capturedLength(), replace);
                    // Don't defeat Undo/Redo
                    Apply_Target->Set_PlainText(replace_result);
                }
            }
        }
    }

    // If error, Script page has been set up for debugging, go to Script page now ...
    if (Script_Error) RegExIDE_Pages->setCurrentIndex(Script_Tab_Index);
}

void
RegularExpressionIDE::onApplyTargetCursorPositionChanged ( ) {
    QTextCursor target_cursor = Apply_Target->textCursor();
    Apply_Target_Offset = target_cursor.position();
}

void
RegularExpressionIDE::onSeriesStartSeriesClicked ( bool ) {
    Series_RegEx_Descriptors = Series_ComboBox->currentData().toList();
    Series_Step = 0;
    Series_Step_Initialize();
}

void
RegularExpressionIDE::onSeriesReplaceClicked ( bool ) {
    Series_Replace();
}

void
RegularExpressionIDE::onSeriesNextStepClicked ( bool ) {
    if (Series_Step < (Series_RegEx_Descriptors.count() - 1)) {
        Series_Step += 1;
        Series_Step_Initialize();
    }
}

void
RegularExpressionIDE::onSeriesReplaceNextStepClicked ( bool ) {
    Series_Replace();

    if (Series_Step < (Series_RegEx_Descriptors.count() - 1)) {
        Series_Step += 1;
        Series_Step_Initialize();
    }
}

void
RegularExpressionIDE::onTargetFromFileClicked ( bool ) {
    QString data_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString filename =  QFileDialog::getOpenFileName(this, "Target text from file",
                                                     QDir::toNativeSeparators(data_path),
                                                     "TXT (*.txt)");
    if (filename.isEmpty()) return;

    QFile target_text_file (filename);
    target_text_file.open(QIODevice::ReadOnly);
    QString target_text = target_text_file.readAll();
    target_text_file.close();

    Apply_Target->Set_PlainText(target_text);
    Apply_Target_Offset = -1;
}

void
RegularExpressionIDE::onTargetFromClipboardClicked ( bool ) {
#ifndef QT_NO_CLIPBOARD
    QClipboard *clipboard = QGuiApplication::clipboard();
    if (clipboard) {
        QString target_text = clipboard->text();
        Apply_Target->Set_PlainText(target_text);
        Apply_Target_Offset = -1;
    }
#endif
}

void
RegularExpressionIDE::onTargetFromMemoryClicked ( bool ) {
    Apply_Target->Set_PlainText(Apply_Memory);
}

void
RegularExpressionIDE::onReplaceAllClicked ( bool ) {
    if (not Apply_Replace_Scripted->isChecked())
        Replace_All();
    else
        Replace_All_Scripted();
}

void
RegularExpressionIDE::onFindNextClicked ( bool ) {
    if (Apply_Target_Offset < 0) Apply_Target_Offset = 0;

    Apply_Target_FindNext_Offset = Apply_Target_Offset;

    const QString regex_pattern = Apply_Find_Pattern->toPlainText();
    const QString target_text = Apply_Target->toPlainText();

    QRegularExpression regex = QRegularExpression(regex_pattern);
    if (regex.isValid() and
        (regex_pattern.length() > 0)) {
        QRegularExpressionMatchIterator regex_iterator =
                                          regex.globalMatch(target_text, Apply_Target_Offset,
                                                            QRegularExpression::PartialPreferCompleteMatch);
        if (regex_iterator.hasNext()) {
            // At least one found
            QRegularExpressionMatch match = regex_iterator.next();
            if (match.hasMatch() and (not match.hasPartialMatch())) {
                // This is the first match, and it's complete
                QTextEdit::ExtraSelection selection_green;
                QTextCharFormat format_green = selection_green.format;
                format_green.setBackground(Green_Match_Color);
                selection_green.format = format_green;

                QList<QTextEdit::ExtraSelection> parsed_selections = Apply_Target->extraSelections();
                parsed_selections.clear();

                int match_begin = match.capturedStart();
                int match_end = match.capturedEnd();

                QTextCursor target_cursor = Apply_Target->textCursor();
                target_cursor.setPosition(match_begin);
                target_cursor.setPosition(match_end, QTextCursor::KeepAnchor);

                selection_green.cursor = target_cursor;
                parsed_selections.append(selection_green);

                target_cursor.setPosition(Apply_Target_Offset);
                Apply_Target->setTextCursor(target_cursor);

                Apply_Target->setExtraSelections(parsed_selections);

                Apply_Target_Offset = match_end;
            }
        }
    }
}

void
RegularExpressionIDE::onReplaceFindNextClicked ( bool ) {
    if ((Apply_Target_Offset < 0) or
        ((Apply_Target_Offset > Apply_Target_FindNext_Offset) and
         (Apply_Target_FindNext_Offset >= 0))) {
        if (Apply_Target_Offset < 0) {
            Apply_Target_Offset = 0;
            onFindNextClicked();
        }
        else if (Apply_Target_Offset > Apply_Target_FindNext_Offset) {
            Apply_Target_Offset = Apply_Target_FindNext_Offset;
        }

        Apply_Target_FindNext_Offset = Apply_Target_Offset;

        const QString regex_pattern = Apply_Find_Pattern->toPlainText();
        QString target_text = Apply_Target->toPlainText();

        QRegularExpression regex = QRegularExpression(regex_pattern);
        if (regex.isValid() and
            (regex_pattern.length() > 0)) {
            QRegularExpressionMatchIterator regex_iterator =
                                              regex.globalMatch(target_text, Apply_Target_Offset,
                                                                QRegularExpression::PartialPreferCompleteMatch);
            if (regex_iterator.hasNext()) {
                // At least one found
                QRegularExpressionMatch match = regex_iterator.next();
                if (match.hasMatch() and (not match.hasPartialMatch())) {
                    // This is the first match, and it's complete
                    int match_begin = match.capturedStart();
                    int match_end = match.capturedEnd();
                    int match_length = match.capturedLength();

                    QStringList captured;
                    const int capture_groups_count = regex.captureCount() + 1;
                    for (int capture_group_idx = 0; capture_group_idx < capture_groups_count; ++capture_group_idx) {
                        captured.append(match.captured(capture_group_idx));
                    }

                    QString replace_pattern = Apply_Replace_Pattern->toPlainText();
                    QString replace_text = replace_pattern;
                    QList<QRegularExpressionMatch> replace_pattern_match_list;
                    QRegularExpression replace_pattern_regex = QRegularExpression("(?:\\\\\\\\)+|(?:\\\\(\\d+))");
                    if (replace_pattern_regex.isValid()) {
                        QRegularExpressionMatchIterator replace_pattern_regex_iterator =
                                                          replace_pattern_regex.globalMatch(replace_pattern);
                        while (replace_pattern_regex_iterator.hasNext()) {
                            QRegularExpressionMatch replace_pattern_match = replace_pattern_regex_iterator.next();
                            bool no_error;
                            replace_pattern_match.captured().right(1).toInt(&no_error);
                            // Only accept backreferences w/ numbers
                            if (no_error) replace_pattern_match_list.append(replace_pattern_match);
                        }

                        while (replace_pattern_match_list.count() > 0) {
                            QRegularExpressionMatch replace_pattern_match = replace_pattern_match_list.takeLast();
                            int cap_idx = replace_pattern_match.captured(1).toInt();
                            if (cap_idx < captured.count()) {
                                replace_text.replace(replace_pattern_match.capturedStart(),
                                                     (replace_pattern_match.capturedEnd() -
                                                      replace_pattern_match.capturedStart()),
                                                     captured[cap_idx]);
                            }
                        }

                        // Render '\' characters properly
                        replace_text.replace("\\\\", "\\");
                    }

                    target_text.replace(match_begin, (match_end - match_begin), replace_text);
                    // Don't defeat Undo/Redo
                    Apply_Target->selectAll();
                    Apply_Target->insertPlainText(target_text);
                    Apply_Target_Offset = match_end - match_length + replace_text.length();
                    onFindNextClicked();
                }
            }
        }
    }
}

void
RegularExpressionIDE::onTargetToReplaceClicked ( bool ) {
    QString target_text = Apply_Target->toPlainText();
    Apply_Replace_Pattern->Set_PlainText(target_text);
}

void
RegularExpressionIDE::onTargetToMemoryClicked ( bool ) {
    Apply_Memory = Apply_Target->toPlainText();
}

void
RegularExpressionIDE::onTargetToClipboardClicked ( bool ) {
#ifndef QT_NO_CLIPBOARD
    QClipboard *clipboard = QGuiApplication::clipboard();
    if (clipboard) {
        QString target_text = Apply_Target->toPlainText();
        if (target_text.length() > 0) clipboard->setText(target_text);
    }
#endif
}

void
RegularExpressionIDE::onTargetToFileClicked ( bool ) {
    QString app_data_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString filename =  QFileDialog::getSaveFileName(this, "Target text to file",
                                                     QDir::toNativeSeparators(app_data_path),
                                                     "TXT (*.txt)");
    if (filename.isEmpty()) return;

    QFile target_text_file(filename);
    if (not target_text_file.open(QIODevice::WriteOnly))
        // Error message here?
        return;

    QTextStream stream(&target_text_file);
    stream << Apply_Target->toPlainText();
    stream.flush();
    target_text_file.close();
}

#endif // REGEXIDE_APPLY_PAGE_CPP
