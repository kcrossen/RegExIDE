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

#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <QTextDocumentFragment>

enum Bracket_Matching_Mode { No_Matching, RegEx_Matching, CPP_Matching };

class PlainTextEdit : public QPlainTextEdit {
    Q_OBJECT

public:
    PlainTextEdit ( QWidget* parent = 0,
                    Bracket_Matching_Mode Matching_Mode = No_Matching );

    void
    Set_PlainText ( QString Set_Plain_Text );

    bool Brace_Bracket_Character;
    bool Quote_Bracket_Character;
    bool Post_Select_Bracket_Enclosed_Text;

    Bracket_Matching_Mode Current_Bracket_Matching_Mode = No_Matching;

private:
    QString Bracket_Source_Text;
    QString Bracket_Text;

protected:
    void
    keyPressEvent ( QKeyEvent* event );

private:
    void
    mouseReleaseEvent ( QMouseEvent *event );

signals:
    void
    clicked ( );

private slots:
    void
    onTextChanged ( );

    void
    matchParentheses ( );

private:
    void
    createParenthesisSelection (int pos );
};

#endif

