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

/****************************************************************************
**
** Copyright (C) 2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author Giuseppe D'Angelo <giuseppe.dangelo@kdab.com>
** Copyright (C) 2015 Samuel Gaist <samuel.gaist@edeltech.ch>
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef REGULAREXPRESSIONDIALOG_H
#define REGULAREXPRESSIONDIALOG_H

#include <QApplication>

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QDateTime>

#include <QStandardPaths>
#include <QDir>
#include <QFileDialog>

#include <QCheckBox>
#include <QComboBox>
#include <QToolButton>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QLineEdit>
#include <QSpinBox>
#include <QPlainTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QModelIndex>
#include <QTabWidget>
#include <QHeaderView>

#include <QAction>
#include <QClipboard>

#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QSplitter>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

#include <QtAlgorithms>

#include "MyWidgets.h"
#include "PlainTextEdit.h"

#include "JavaScriptEdit.h"

#include "OrderedVariantMap.h"
#include "orderedJson.h"

#include "duktape.h"

//# ⇧   Shift   QChar(0x21E7)
//# ⌃  Control  QChar(0x2303)
//# ⌥	Option (alt)    QChar(0x2325)
//# ⌘	Command     QChar(0x2318)
//# ⏎ ↩ Return
//# ⏏	Eject
//# …   Elipsis QChar(0x2026)
//# ⇒ QChar(0x21D2)

//⌘ – &#x2318; – &#8984; – the Command Key symbol
//⌥ – &#x2325; – &#8997; – the Option Key symbol
//⇧ – &#x21E7; – &#8679; – the Shift Key symbol
//⎋ – &#x238B; – &#9099; – the ESC Key symbol
//⇪ – &#x21ea; – &#8682; – the Capslock symbol
//⏎ – &#x23ce; – &#9166; – the Return symbol
//⌫ – &#x232b; – &#9003; – the Delete / Backspace symbol

// Parse_RegEx_Pattern (not escaped) (?:\\\\|\\[^AZBbDWSdws])|(?<assert>\^|\$|\\A|\\Z|\\B|\\b)|(?<class>\\[DWSdws]|\[(?:(?:\^?\][^]]*)|[^]]+)\])|(?<group>\(\?:|\(\?=|\(\?!|\(\?<=|\(\?<!|\(\?<[_A-Za-z][_A-Za-z0-9]*>|\(\?|\(|\))|(?<quantifier>[?*+]|\{\d+\}|\{\d+,\}|\{\d+,\d+\})|(?<alternation>\|)|(?<any>\.)
#define Parse_RegEx_Pattern "(?:\\\\\\\\|\\\\[^AZBbDWSdws])|(?<assert>\\^|\\$|\\\\A|\\\\Z|\\\\B|\\\\b)|(?<class>\\\\[DWSdws]|\\[(?:(?:\\^?\\][^]]*)|[^]]+)\\])|(?<group>\\(\\?:|\\(\\?=|\\(\\?!|\\(\\?<=|\\(\\?<!|\\(\\?<[_A-Za-z][_A-Za-z0-9]*>|\\(\\?|\\(|\\))|(?<quantifier>[?*+]|\\{\\d+\\}|\\{\\d+,\\}|\\{\\d+,\\d+\\})|(?<alternation>\\|)|(?<any>\\.)"

#define Green_Match_Color QColor(128, 255, 128)
#define Light_Green_Match_Color QColor(160, 225, 128)

#define Blue_Match_Color QColor(192, 192, 255)
#define Light_Blue_Match_Color QColor(224, 192, 255)

struct RegEx_Element {
    int Element_Begin;
    int Element_End;
    QString Element_Type;
    QString Element_Text;
};

class RegularExpressionIDE : public QMainWindow {
    Q_OBJECT

public:
    RegularExpressionIDE ( QWidget *parent = 0 );
    ~RegularExpressionIDE ( );

protected:
    void
    closeEvent ( QCloseEvent* event );

    // Application ...
private:
    QString RegExIDE_Ini_Path;
    OrderedVariantMap RegExIDE_Initialization;

    #define UI_Minimum_Height 640

    TabWidget* RegExIDE_Pages;

    bool Defer_UI_Refresh;

    bool RegEx_Valid;

    #define Replace_With_Empty_Replace_Pattern true

private:
    void
    Demo_Initialize ( int demo_idx );

    void
    UI_Initialize ( );

    void
    UI_Connect ( );

    bool
    Open_Application_Initialization ( );

    void
    Save_Application_Initialization ( QString Save_Initialization_FileName  = "" );

    void
    Preferences_Menu_Initialize ( );

private slots:
    void
    onMenuPreferences ( );

    void
    onMenuRegExCatalog ( );

    void
    onMenuClear ( );

    void
    onCopyFromRegularExpressionTabClicked ( bool = false );

    void
    onCurrentPageChanged ( int new_current_tab_index );

    // ... Application

    // Main Page ...
private:
    PlainTextEdit *RegEx_Pattern_Edit;
    QLabel *regexpStatusLabel;

    PlainTextEdit *Target_Text_Edit;

    PlainTextEdit *Replace_Pattern_Edit;

    PlainTextEdit *Replace_Pattern_Result;

    QTreeWidget* Groups_Tree;

    QTreeWidget* Pattern_Elements_Tree;

    QTreeWidget* Matches_Tree;

    QVector<QVector<int>> RegEx_Pattern_Group_Capture_Map;

    int Main_Tab_Index;

private:
    QWidget*
    Initialize_Main_Page_UI ( );
    QWidget*
    Initialize_Main_Page_Left_UI ( );
    QWidget*
    Initialize_Main_Page_Right_UI ( );

    void
    UI_Refresh ( );

    void
    RegEx_Captures_Highlight ( QRegularExpression Capture_QRegularExpression,
                               PlainTextEdit *Target_PlainTextEdit );

    void
    RegEx_Elements_Compute ( QRegularExpression Capture_RegularExpression,
                             QString Target_Text );

private slots:
    void
    onEscapeSelectedText ( bool = false );

    void
    onRegexPatternCopyToApplyClicked ( bool = false );

    void
    onRegexPatternCopyClicked ( bool = false );

    void
    onRegexPatternCopyEscapedClicked ( bool = false );

    void
    onReplacePatternCopyToApplyClicked ( bool = false );

    void
    onReplacePatternCopyClicked ( bool = false );

    void
    onReplacePatternCopyEscapedClicked ( bool = false );

    void
    onGroupsTreeClicked ( QModelIndex model_index );

    void
    onPatternElementsTreeClicked ( QModelIndex model_index );

    // ... Main Page

    // Options Reference Page ...
private:
    QCheckBox *caseInsensitiveOptionCheckBox;
    QCheckBox *dotMatchesEverythingOptionCheckBox;
    QCheckBox *multilineOptionCheckBox;
    QCheckBox *extendedPatternSyntaxOptionCheckBox;
    QCheckBox *invertedGreedinessOptionCheckBox;
    QCheckBox *dontCaptureOptionCheckBox;
    QCheckBox *useUnicodePropertiesOptionCheckBox;
    QCheckBox *optimizeOnFirstUsageOptionCheckBox;
    QCheckBox *dontAutomaticallyOptimizeOptionCheckBox;

    QSpinBox *offsetSpinBox;

    QComboBox *matchTypeComboBox;

    QCheckBox *anchoredMatchOptionCheckBox;
    QCheckBox *dontCheckSubjectStringMatchOptionCheckBox;

    QTreeWidget* Reference_Tree;

private:
    QWidget*
    Initialize_Options_Reference_Page_UI ( );
    QWidget*
    Initialize_Options_Reference_Page_Left_UI ( );
    QWidget*
    Initialize_Options_Reference_Page_Right_UI ( );

private slots:
    void
    onReferenceTreeClicked ( QModelIndex model_index );

    // ... Options Reference Page

    // Trace Page ...
private:
    QSlider* Trace_Animation_Slider;
    PlainTextEdit* Trace_Animation;
    PlainTextEdit *Trace_RegEx_Result;
    QTextCharFormat Trace_RegEx_Result_Initial_Format;
    int Trace_Tab_Index;
    bool Trace_Dirty;
    bool Trace_in_Process;
    QToolButton *Trace_All_Matches;

private:
    QWidget*
    Initialize_Trace_Page_UI ( );

    void
    RegEx_Trace_Step ( QString RegEx_Pattern,
                       QString RegEx_Target,
                       PlainTextEdit* Trace_Display,
                       int Trace_Step_Index,
                       bool Normalize_Trace_Display = false );

    void
    RegEx_Trace ( QString RegEx_Pattern,
                  QString RegEx_Target );

private slots:
    void
    onTraceAllMatchesClicked ( bool = false );

    void
    onTraceAnimationSliderValueChanged ( int slider_value );

    // ... Trace Page

    // RegEx Catalog Page ...
private:
    TreeWidget* RegEx_Catalog_Tree;
    QTreeWidgetItem *RegEx_Catalog_Tree_Right_Clicked_Item;

    QTreeWidgetItem *RegEx_Catalog_Edit_Item;

    QLineEdit *Catalog_Series;
    QLineEdit *Catalog_Series_Index;
    QLineEdit *Catalog_Series_Help;
    QComboBox *Catalog_Series_Before_Replace_ComboBox;
    QComboBox *Catalog_Series_After_Replace_ComboBox;

    QLineEdit *Catalog_Category;
    QLineEdit *Catalog_RegEx_Name;

    PlainTextEdit *Catalog_RegEx_Pattern;
    PlainTextEdit *Catalog_Replace_Pattern;
    QCheckBox *Catalog_Replace_Scripted;
    QCheckBox *Catalog_Replace_Pattern_Specified;
    PlainTextEdit *Catalog_Target;
    QCheckBox *Catalog_Target_Specified;

    int RegEx_Catalog_Tab_Index;

private:
    QWidget*
    Initialize_RegEx_Catalog_Page_UI ( );

    void
    Populate_RegEx_Catalog_Tree ( QVariantList RegEx_Catalog_Descriptors );

    OrderedVariantMap
    RegEx_Descriptor_From_Edit ( );

    QVariantList
    RegEx_Catalog_From_Tree ( );

    void
    RegEx_Catalog_Set_Selected_RegEx ( OrderedVariantMap Select_RegEx_Descr );

private slots:
    void
    onRegExCatalogTreeClicked ( QModelIndex model_index );

    void
    onRegExCatalogItemRightClicked ( QTreeWidgetItem *item,
                                         int column );

    void
    onRegExCatalogDeleteItem ( );

        void
    onRegExCatalogMoveItemUp ( int move_up_places = 1 );

    void
    onRegExCatalogMoveItemDown ( int move_down_places = 1 );

    void
    onRegExCatalogDeleteItemClicked ( bool = false );

    void
    onRegExCatalogMoveUpClicked ( bool = false );

    void
    onRegExCatalogMoveDownClicked ( bool = false );

    void
    onAddNewRegExClicked ( bool = false );

    void
    onUpdateRegExClicked ( bool = false );

    void
    onSaveCatalogClicked ( bool = false );

    void
    onOpenCatalogClicked ( bool = false );

    void
    onSaveCatalogAsClicked ( bool = false );

    // ... RegEx Catalog Page

    // Script Page ...
private:
    PlainTextEdit *Script_Find_Pattern;
    PlainTextEdit *Script_Target;

    JSEdit *Script_JavaScript_Editor;
    bool Script_Modified;
    duk_context *Script_JS_Context;

    PlainTextEdit *Script_Replace_Text;
    PlainTextEdit *Script_Message_Text;

    TreeWidget *JavaScript_Referennce_Tree;

    int Script_Tab_Index;

private:
    QWidget*
    Initialize_Script_Page_UI ( );

private slots:
    void
    onScript_Editor_TextChanged ( );

    void
    onExampleScriptClicked ( bool = false );

    void
    onAnotherExampleScriptClicked ( bool = false );

    void
    onStarterScriptClicked ( bool = false );

    void
    onResetScriptClicked ( bool = false );

    void
    onRunScriptClicked ( bool = false );

    void
    onJavaScriptReferenceTreeClicked ( QModelIndex model_index );

    // ... Script Page

    // Apply Page ...
private:
    QComboBox *Series_ComboBox;
    QVariantList  Series_RegEx_Descriptors;
    int Series_Step;
    QString Series_Before_Replace;
    QString Series_After_Replace;
    QString Apply_Memory;

    PlainTextEdit *Apply_Find_Pattern;
    QCheckBox *Apply_Replace_Scripted;
    PlainTextEdit *Apply_Replace_Pattern;
    QLabel *Series_Help_Label;
    PlainTextEdit *Apply_Target;
    int Apply_Target_Offset;
    int Apply_Target_FindNext_Offset;
    int Apply_Tab_Index;

private:
    QWidget*
    Initialize_Apply_Page_UI ( );

    void
    Series_Step_Initialize ( );

    void
    Series_Replace ( );

    void
    Replace_All ( );

    void
    Replace_All_Scripted ( );

private slots:
    void
    onSeriesStartSeriesClicked ( bool = false );

    void
    onSeriesReplaceClicked ( bool = false );

    void
    onSeriesNextStepClicked ( bool = false );

    void
    onSeriesReplaceNextStepClicked ( bool = false );

    void
    onTargetFromFileClicked ( bool = false );

    void
    onTargetFromClipboardClicked ( bool = false );

    void
    onTargetFromMemoryClicked ( bool = false );

    void
    onReplaceAllClicked ( bool = false );

    void
    onFindNextClicked ( bool = false );

    void
    onReplaceFindNextClicked ( bool = false );

    void
    onTargetToReplaceClicked ( bool = false );

    void
    onTargetToMemoryClicked ( bool = false );

    void
    onTargetToClipboardClicked ( bool = false );

    void
    onTargetToFileClicked ( bool = false );

    void
    onApplyTargetCursorPositionChanged ( );

    // ... Apply Page

    // Help Page ...
private:
    QLabel *RegExIDE_Help;

private:
    QWidget*
    Initialize_Help_Page_UI ( );

    // ... Help Page

private:
#include "RegExIDE_Regular_Expression_Reference.h"
#include "RegExIDE_JavaScript_Reference.h"

};

#endif
