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

#include <QtGui>

#include "PlainTextEdit.h"

#define regex_parentheses_pattern "(?:\\\\\\\\|\\\\\\(|\\\\\\)|\\\\\\[)|(?:\\[(?:(?:\\^?\\][^]]*)|[^]]+)\\])|(\\(|\\))"
// #define bracket_pattern "(?:\\\\\\\\|\\\\\\(|\\\\\\)|\\\\\\[|\\\\\\]|\\\\\\{|\\\\\\})|(?:\\[(?:(?:\\^?\\][^]]*)|[^]]+)\\])|(\\(|\\)|\\[|\\]|\\{|\\})"
#define regex_bracket_pattern "(?:\\\\\\\\|\\\\\\(|\\\\\\)|\\\\\\[|\\\\\\]|\\\\\\{|\\\\\\})|(?<=\\[)(?:(?:(?:\\^?\\][^]]*)|[^]]+))(?=\\])|(\\(|\\)|\\[|\\]|\\{|\\})"
#define regex_bracket_list "()[]{}"

PlainTextEdit::PlainTextEdit ( QWidget* parent,
                               Bracket_Matching_Mode Matching_Mode ) : QPlainTextEdit ( parent ) {
    Current_Bracket_Matching_Mode = Matching_Mode;

    Post_Select_Bracket_Enclosed_Text = true;

    connect(this, SIGNAL(textChanged()),
            this, SLOT(onTextChanged()));
    connect(this, SIGNAL(cursorPositionChanged()),
            this, SLOT(matchParentheses()));
}

void
PlainTextEdit::Set_PlainText ( QString Set_Plain_Text ) {
    // Don't defeat Undo/Redo
    QPlainTextEdit::selectAll();
    QPlainTextEdit::insertPlainText(Set_Plain_Text);
    QTextCursor txt_cursor = QPlainTextEdit::textCursor();
    txt_cursor.movePosition(QTextCursor::Start);
    QPlainTextEdit::setTextCursor(txt_cursor);
}

void
PlainTextEdit::onTextChanged ( ) {
    if (Current_Bracket_Matching_Mode == No_Matching) return;

    QString bracket_pattern;
    if (Current_Bracket_Matching_Mode == RegEx_Matching) bracket_pattern = regex_bracket_pattern;
    QString bracket_list;
    if (Current_Bracket_Matching_Mode == RegEx_Matching) bracket_list = regex_bracket_list;

    Bracket_Source_Text = this->toPlainText();
    Bracket_Text = QString(" ").repeated(Bracket_Source_Text.length());
    QRegularExpression paren_regex = QRegularExpression(bracket_pattern);
    if (paren_regex.isValid()) {
        QRegularExpressionMatchIterator regex_iterator =
                                          paren_regex.globalMatch(Bracket_Source_Text);
        if (regex_iterator.hasNext()) {
            // At least one found
            while (regex_iterator.hasNext()) {
                QRegularExpressionMatch match = regex_iterator.next();
                if ((match.capturedLength() == 1) and
                    bracket_list.contains(match.captured())) {
                    Bracket_Text[match.capturedStart()] = match.captured().at(0);
                }
            }
        }
    }
}

void
PlainTextEdit::matchParentheses ( ) {
    // /* ??? */ bool match = false;
    QList<QTextEdit::ExtraSelection> selections;
    setExtraSelections(selections);

    if (Current_Bracket_Matching_Mode == No_Matching) return;

    QString target_text = this->toPlainText();

    if (not (target_text.length() == Bracket_Text.length())) onTextChanged();
    if (not (target_text == Bracket_Source_Text)) onTextChanged();

    QString bracket_list;
    if (Current_Bracket_Matching_Mode == RegEx_Matching) bracket_list = regex_bracket_list;

    int position = this->textCursor().position() - 1;
    if ((position < 0) or (position >= target_text.length()) or
        (position >= Bracket_Text.length())) return;
    if (not bracket_list.contains(target_text.at(position))) return;

    // For example, may have found bracket_list character in character set.
    if (not (Bracket_Text.at(position) == target_text.at(position))) return;

    int match_position = position;
    int paren_level = 0;
    if (Bracket_Text.at(match_position) == '(') {
        while (match_position < Bracket_Text.length()) {
            if (Bracket_Text.at(match_position) == '(') paren_level += 1;
            else if (Bracket_Text.at(match_position) == ')') paren_level -= 1;
            if (paren_level == 0) break;
            match_position += 1;
        }
    }
    else if (Bracket_Text.at(match_position) == ')') {
        while (match_position >= 0) {
            if (Bracket_Text.at(match_position) == ')') paren_level += 1;
            else if (Bracket_Text.at(match_position) == '(') paren_level -= 1;
            if (paren_level == 0) break;
            match_position -= 1;
        }
    }
    else if (Bracket_Text.at(match_position) == '[') {
        while (match_position < Bracket_Text.length()) {
            if (Bracket_Text.at(match_position) == '[') paren_level += 1;
            else if (Bracket_Text.at(match_position) == ']') paren_level -= 1;
            if (paren_level == 0) break;
            match_position += 1;
        }
    }
    else if (Bracket_Text.at(match_position) == ']') {
        while (match_position >= 0) {
            if (Bracket_Text.at(match_position) == ']') paren_level += 1;
            else if (Bracket_Text.at(match_position) == '[') paren_level -= 1;
            if (paren_level == 0) break;
            match_position -= 1;
        }
    }
    else if (Bracket_Text.at(match_position) == '{') {
        while (match_position < Bracket_Text.length()) {
            if (Bracket_Text.at(match_position) == '{') paren_level += 1;
            else if (Bracket_Text.at(match_position) == '}') paren_level -= 1;
            if (paren_level == 0) break;
            match_position += 1;
        }
    }
    else if (Bracket_Text.at(match_position) == '}') {
        while (match_position >= 0) {
            if (Bracket_Text.at(match_position) == '}') paren_level += 1;
            else if (Bracket_Text.at(match_position) == '{') paren_level -= 1;
            if (paren_level == 0) break;
            match_position -= 1;
        }
    }

    if ((not (match_position == position)) and
        ((match_position >= 0) and (match_position < Bracket_Text.length()))) {
        createParenthesisSelection(position);
        createParenthesisSelection(match_position);
    }
}

void
PlainTextEdit::createParenthesisSelection ( int pos ) {
    QList<QTextEdit::ExtraSelection> selections = extraSelections();

    QTextEdit::ExtraSelection selection;
    QTextCharFormat format = selection.format;
    format.setBackground(Qt::green);
    selection.format = format;
    
    QTextCursor cursor = textCursor();
    cursor.setPosition(pos);
    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    selection.cursor = cursor;

    selections.append(selection);

    setExtraSelections(selections);
}

void
PlainTextEdit::keyPressEvent ( QKeyEvent* event ) {
    // Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();

    if (((event->key() == Qt::Key_ParenLeft) or
         (event->key() == Qt::Key_BracketLeft) or
         ((event->key() == Qt::Key_BraceLeft) and Brace_Bracket_Character) or
         ((event->key() == Qt::Key_QuoteDbl) and Quote_Bracket_Character) or
         ((event->key() == Qt::Key_Apostrophe) and Quote_Bracket_Character)) and
        (this->textCursor().selectedText().count() > 0)) {
        event->accept();
        // For these "bracketing" characters, if the "opening" character is typed ...
        // ... when text is selected, the selected text will be enclosed by ...
        // ... "open" and "close" characters.
        QString left_encloser;
        QString right_encloser;
        if (event->key() == Qt::Key_ParenLeft) {
            left_encloser = "(";
            right_encloser = ")";
        }
        else if (event->key() == Qt::Key_BracketLeft) {
            left_encloser = "[";
            right_encloser = "]";
        }
        else if (event->key() == Qt::Key_BraceLeft) {
            left_encloser = "{";
            right_encloser = "}";
        }
        else if (event->key() == Qt::Key_QuoteDbl) {
            left_encloser = "\"";
            right_encloser = "\"";
        }
        else if (event->key() == Qt::Key_Apostrophe) {
            left_encloser = "'";
            right_encloser = "'";
        }

        QTextCursor txt_cursor = this->textCursor();
        int sel_begin_pos = txt_cursor.selectionStart();
        int sel_end_pos = txt_cursor.selectionEnd();
        txt_cursor.insertText(left_encloser + txt_cursor.selectedText() + right_encloser);

        if (Post_Select_Bracket_Enclosed_Text) {
            txt_cursor.setPosition((sel_begin_pos + 1));
            txt_cursor.setPosition((sel_end_pos + 1), QTextCursor::KeepAnchor);
            this->setTextCursor(txt_cursor);
        }

        return;
    }
    else {
        // Allow parent class (normal) handling of key
        QPlainTextEdit::keyPressEvent(event);
    }
}


void
PlainTextEdit::mouseReleaseEvent ( QMouseEvent *event )
{
    if (event->button() & Qt::LeftButton) {
        emit clicked();
    }

    QPlainTextEdit::mouseReleaseEvent(event);
}
