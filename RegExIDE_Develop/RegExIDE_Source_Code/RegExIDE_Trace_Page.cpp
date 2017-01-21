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

#ifndef REGEXIDE_TRACE_PAGE_CPP
#define REGEXIDE_TRACE_PAGE_CPP

#include "RegularExpressionIDE.h"

QWidget*
RegularExpressionIDE::Initialize_Trace_Page_UI ( ) {
    QWidget* container = new QWidget();
    container->setContentsMargins(0, 0, 0, 0);
    container->setMinimumHeight(UI_Minimum_Height);

    QVBoxLayout *container_layout = new QVBoxLayout;
    container_layout->setContentsMargins(0, 0, 0, 0);
    container_layout->setSpacing(4);

    Trace_All_Matches = new QToolButton();
    Trace_All_Matches->setText("Trace All Matches");
    connect(Trace_All_Matches, SIGNAL(clicked(bool)), this, SLOT(onTraceAllMatchesClicked(bool)));
    container_layout->addWidget(Trace_All_Matches, 0);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(15);
    QFontMetrics font_metrics(font) ;

    Trace_Animation_Slider = new QSlider(Qt::Horizontal);
    Trace_Animation_Slider->setMinimum(0);
    Trace_Animation_Slider->setMaximum(0);
    connect(Trace_Animation_Slider, SIGNAL(valueChanged(int)), this, SLOT(onTraceAnimationSliderValueChanged(int)));
    container_layout->addWidget(Trace_Animation_Slider, 0);

    Trace_Animation = new PlainTextEdit(this);
    Trace_Animation->setContentsMargins(2, 2, 2, 2);
    Trace_Animation->setReadOnly(true);
    Trace_Animation->setFont(font);
    Trace_Animation->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    Trace_Animation->setWordWrapMode(QTextOption::NoWrap);
    Trace_Animation->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    Trace_Animation->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Trace_Animation->setFixedHeight((2 * (font_metrics.lineSpacing() + 4)) + 8);
    container_layout->addWidget(Trace_Animation, 0);

    Trace_RegEx_Result = new PlainTextEdit(this);
    Trace_RegEx_Result->setFont(font);
    Trace_RegEx_Result->setReadOnly(true);
    Trace_RegEx_Result->setLineWrapMode(QPlainTextEdit::NoWrap);
    Trace_RegEx_Result_Initial_Format = Trace_RegEx_Result->currentCharFormat();
    container_layout->addWidget(Trace_RegEx_Result, 100);

    container->setLayout(container_layout);
    return container;
}

void
RegularExpressionIDE::RegEx_Trace_Step ( QString RegEx_Pattern,
                                         QString RegEx_Target,
                                         PlainTextEdit* Trace_Display,
                                         int Trace_Step_Index,
                                         bool Normalize_Trace_Display ) {

    QTextCharFormat green_format = Trace_RegEx_Result_Initial_Format;
    green_format.setBackground(QColor(128, 255, 128));
    QTextCharFormat light_green_format = Trace_RegEx_Result_Initial_Format;
    light_green_format.setBackground(QColor(160, 225, 128));
    QTextCharFormat blue_format = Trace_RegEx_Result_Initial_Format;
    blue_format.setBackground(QColor(192, 192, 255));

    int start_match = Trace_Result[Trace_Step_Index][trace_start_match];
    int current_position = Trace_Result[Trace_Step_Index][trace_current_position];
    int pattern_position = Trace_Result[Trace_Step_Index][trace_pattern_position];
    int next_item_length = Trace_Result[Trace_Step_Index][trace_next_item_length];
    if (next_item_length == 0) next_item_length = 1;

    int pattern_offset = 0;
    int target_offset = 0;

    int display_offset = 0;
    int display_center = 0;
    int display_width = 0;

    if (Normalize_Trace_Display) {
        // Display of pattern or target (not both) are offset such that the centers of the ...
        // ... next active pattern element (in blue above) and the currently captured target ...
        // ... plus next target character to process (in green below) are aligned.
        int pattern_center = pattern_position + int(next_item_length / 2);
        int match_center = start_match + int((current_position - start_match) / 2);
        if (pattern_center > match_center) {
            target_offset = pattern_center - match_center;
        }
        else if (match_center > pattern_center) {
            pattern_offset = match_center - pattern_center;
        }

        display_offset = qMin((pattern_offset + pattern_position),
                              (target_offset + start_match));

        display_center = qMin((pattern_offset + pattern_center),
                              (target_offset + match_center));

        display_width = qMax((pattern_offset + RegEx_Pattern.length()),
                             (target_offset + RegEx_Target.length()));
    }

    Trace_Display->setCurrentCharFormat(Trace_RegEx_Result_Initial_Format);
    if (pattern_offset > 0) Trace_Display->insertPlainText(QString(" ").repeated(pattern_offset));
    if (pattern_position > 0) Trace_Display->insertPlainText(RegEx_Pattern.mid(0, pattern_position));
    Trace_Display->setCurrentCharFormat(blue_format);
    Trace_Display->insertPlainText(RegEx_Pattern.mid(pattern_position, next_item_length));
    Trace_Display->setCurrentCharFormat(Trace_RegEx_Result_Initial_Format);
    if (RegEx_Pattern.length() > (pattern_position + next_item_length))
        Trace_Display->insertPlainText(RegEx_Pattern.mid((pattern_position + next_item_length)));
    Trace_Display->insertPlainText("\n");

    if (target_offset > 0) Trace_Display->insertPlainText(QString(" ").repeated(target_offset));
    if (start_match > 0) Trace_Display->insertPlainText(RegEx_Target.mid(0, start_match));
    if (current_position > start_match) {
        Trace_Display->setCurrentCharFormat(light_green_format);
        Trace_Display->insertPlainText(RegEx_Target.mid(start_match, (current_position - start_match)));
    }
    Trace_Display->setCurrentCharFormat(green_format);
    Trace_Display->insertPlainText(RegEx_Target.mid(current_position, 1));
    Trace_Display->setCurrentCharFormat(Trace_RegEx_Result_Initial_Format);
    if (RegEx_Target.length() > current_position)
        Trace_Display->insertPlainText(RegEx_Target.mid((current_position + 1)));

    if (Normalize_Trace_Display) {
        // Display is scrolled horizontally so that all of highlighted pattern (in blue above) ...
        // ... and all of highlighted target (in green below) are visible (if possible).
        QScrollBar* horz_scrollbar = Trace_Display->horizontalScrollBar();
        int max_value = horz_scrollbar->maximum();
        int display_value = qMin(display_offset, display_center);
        if (display_center > int(display_width / 2)) display_value = qMax(display_offset, display_center);
        int new_value = int((display_value * max_value) / display_width);
        horz_scrollbar->setValue(new_value);
    }
}

void
RegularExpressionIDE::RegEx_Trace ( QString RegEx_Pattern,
                                    QString RegEx_Target ) {
    Trace_in_Process = true;

    Trace_RegEx_Result->clear();
    Trace_RegEx_Result->setCurrentCharFormat(Trace_RegEx_Result_Initial_Format);

    Trace_Animation_Slider->setMaximum(0);
    Trace_Animation->clear();

    if (RegEx_Target.length() == 0) return;

    // Test
    // QString pattern = "\\btoto(\\w+)\\b";
    // QString target = "slkj tototata lkj";

    int trace_result_count =
          Trace_Execute(RegEx_Pattern.utf16(),
                        RegEx_Target.utf16(),
                        RegEx_Target.length());

    int target_ruler_length = (qMax(RegEx_Pattern.length(), RegEx_Target.length()) + 9) / 10;
    QString target_ruler = QString(":....·....").repeated(target_ruler_length) + ":";

    for (int trace_idx = 0; trace_idx < trace_result_count; trace_idx += 1) {
        RegEx_Trace_Step(RegEx_Pattern, RegEx_Target, Trace_RegEx_Result, trace_idx);
        Trace_RegEx_Result->insertPlainText("\n");
        Trace_RegEx_Result->insertPlainText(target_ruler + "\n\n");
    }

    Trace_Animation_Slider->setMaximum(trace_result_count - 1);
    Trace_Animation_Slider->setValue(0);

    Trace_Animation->clear();
    RegEx_Trace_Step(RegEx_Pattern, RegEx_Target, Trace_Animation, 0, true);  // Normalize_Trace_Display

    Trace_Animation_Slider->setFocus();

    Trace_Dirty = false;
    Trace_in_Process = false;
}

void
RegularExpressionIDE::onTraceAllMatchesClicked ( bool ) {
    const QString regex_pattern = RegEx_Pattern_Edit->toPlainText();
    const QString target_text = Target_Text_Edit->toPlainText();
    if (RegEx_Valid and (target_text.length() > 0)) {
        Trace_First_Match_Only = false;
        RegEx_Trace(regex_pattern, target_text);
        Trace_First_Match_Only = true;
    }
    Trace_RegEx_Result->setFocus();
    Trace_Animation_Slider->setFocus();
}

void
RegularExpressionIDE::onTraceAnimationSliderValueChanged ( int slider_value ) {
    if (Trace_in_Process) return;
    if (not RegEx_Valid) return;

    const QString regex_pattern = RegEx_Pattern_Edit->toPlainText();
    const QString target_text = Target_Text_Edit->toPlainText();

    if (target_text.length() == 0) return;

    Trace_Animation->clear();
    RegEx_Trace_Step(regex_pattern, target_text, Trace_Animation, slider_value, true); // Normalize_Trace_Display
}

#endif // REGEXIDE_TRACE_PAGE_CPP
