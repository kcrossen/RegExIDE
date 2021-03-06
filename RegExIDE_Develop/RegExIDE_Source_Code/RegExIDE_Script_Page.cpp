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

#ifndef REGEXIDE_SCRIPT_PAGE_UI_CPP
#define REGEXIDE_SCRIPT_PAGE_UI_CPP

#include "RegularExpressionIDE.h"

QWidget*
RegularExpressionIDE::Initialize_Script_Page_UI ( ) {
    DetailSplitter *container_splitter = new DetailSplitter(Qt::Horizontal);
    container_splitter->setContentsMargins(0, 0, 0, 0);

    QWidget *left_container = new QWidget(this);
    left_container->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *left_layout = new QVBoxLayout;
    left_layout->setContentsMargins(0, 0, 0, 0);
    left_layout->setSpacing(2);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(15);

    QHBoxLayout *find_target_layout = new QHBoxLayout;
    find_target_layout->setContentsMargins(0, 0, 0, 0);
    find_target_layout->setSpacing(2);

    QVBoxLayout *find_target_left_layout = new QVBoxLayout;
    find_target_left_layout->setContentsMargins(0, 0, 0, 0);
    find_target_left_layout->setSpacing(2);

    find_target_left_layout->addWidget(new QLabel(tr("<b>Find pattern<\b>")), 0);
    Script_Find_Pattern = new PlainTextEdit(this);
    Script_Find_Pattern->setFont(font);
    Script_Find_Pattern->setReadOnly(false);
    Script_Find_Pattern->setMinimumHeight(100);
    find_target_left_layout->addWidget(Script_Find_Pattern, 50);
    find_target_layout->addLayout(find_target_left_layout);

    QVBoxLayout *find_target_right_layout = new QVBoxLayout;
    find_target_right_layout->setContentsMargins(0, 0, 0, 0);
    find_target_right_layout->setSpacing(2);

    find_target_right_layout->addWidget(new QLabel(tr("<b>Target or Matched text<\b>")), 0);
    Script_Target = new PlainTextEdit(this);
    Script_Target->setFont(font);
    Script_Target->setReadOnly(false);
    Script_Target->setMinimumHeight(100);
    find_target_right_layout->addWidget(Script_Target, 50);
    find_target_layout->addLayout(find_target_right_layout);

    left_layout->addLayout(find_target_layout, 100);

    QHBoxLayout *script_editor_layout = new QHBoxLayout;
    script_editor_layout->setContentsMargins(0, 0, 0, 0);
    script_editor_layout->addWidget(new QLabel(tr("<b>Script Editor<\b>")), 0);

    QToolButton *example_script_a = new QToolButton();
    example_script_a->setText(tr("Series Example"));
    example_script_a->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    connect(example_script_a, SIGNAL(clicked(bool)), this, SLOT(onSeriesExampleClicked(bool)));
    script_editor_layout->addWidget(example_script_a, 0);

    QToolButton *example_script_b = new QToolButton();
    example_script_b->setText(tr("Demo+ Example"));
    example_script_b->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    connect(example_script_b, SIGNAL(clicked(bool)), this, SLOT(onDemoExampleClicked(bool)));
    script_editor_layout->addWidget(example_script_b, 0);

    QToolButton *example_script_c = new QToolButton();
    example_script_c->setText(tr("Extreme Example"));
    example_script_c->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    connect(example_script_c, SIGNAL(clicked(bool)), this, SLOT(onExtremeExampleClicked(bool)));
    script_editor_layout->addWidget(example_script_c, 0);

    QToolButton *starter_script = new QToolButton();
    starter_script->setText(tr("Starter Script"));
    starter_script->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    connect(starter_script, SIGNAL(clicked(bool)), this, SLOT(onStarterScriptClicked(bool)));
    script_editor_layout->addWidget(starter_script, 0);

    script_editor_layout->addStretch(50);

    QToolButton *reset_script = new QToolButton();
    reset_script->setText(tr("Reset Script"));
    reset_script->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    connect(reset_script, SIGNAL(clicked(bool)), this, SLOT(onResetScriptClicked(bool)));
    script_editor_layout->addWidget(reset_script, 0);

    QToolButton *run_script = new QToolButton();
    run_script->setText(tr("Run Script"));
    run_script->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    connect(run_script, SIGNAL(clicked(bool)), this, SLOT(onRunScriptClicked(bool)));
    script_editor_layout->addWidget(run_script, 0);

    left_layout->addLayout(script_editor_layout, 0);

    Script_JavaScript_Editor = new JSEdit(this);
    connect(Script_JavaScript_Editor, SIGNAL(textChanged()), this, SLOT(onScript_Editor_TextChanged()));
    Script_JavaScript_Editor->setWordWrapMode(QTextOption::NoWrap);
    // JavaScript_Editor->setTabStopWidth(4);
    left_layout->addWidget(Script_JavaScript_Editor, 800);

    left_layout->addSpacing(2);

    QFrame *horizontal_separator = new QFrame;
    horizontal_separator->setFrameStyle(QFrame::HLine | QFrame::Raised);
    left_layout->addWidget(horizontal_separator, 0);

    QPalette result_palette;

    QHBoxLayout *replace_message_layout = new QHBoxLayout;
    replace_message_layout->setContentsMargins(0, 0, 0, 0);
    replace_message_layout->setSpacing(2);

    QVBoxLayout *replace_message_left_layout = new QVBoxLayout;
    replace_message_left_layout->setContentsMargins(0, 0, 0, 0);
    replace_message_left_layout->setSpacing(2);

    replace_message_left_layout->addWidget(new QLabel(tr("<b>Replace Text<\b>")), 0);
    Script_Replace_Text = new PlainTextEdit(this);
    Script_Replace_Text->setFont(font);
    Script_Replace_Text->setReadOnly(true);
    result_palette = Script_Replace_Text->palette();
    result_palette.setBrush(QPalette::Base, result_palette.brush(QPalette::Disabled, QPalette::Base));
    Script_Replace_Text->setPalette(result_palette);
    Script_Replace_Text->setMinimumHeight(100);
    replace_message_left_layout->addWidget(Script_Replace_Text, 50);
    replace_message_layout->addLayout(replace_message_left_layout);

    QVBoxLayout *replace_message_right_layout = new QVBoxLayout;
    replace_message_right_layout->setContentsMargins(0, 0, 0, 0);
    replace_message_right_layout->setSpacing(2);

    replace_message_right_layout->addWidget(new QLabel(tr("<b>Script Debug and Error Messages<\b>")), 0);
    Script_Message_Text = new PlainTextEdit(this);
    Script_Message_Text->setFont(font);
    Script_Message_Text->setReadOnly(true);
    result_palette = Script_Message_Text->palette();
    result_palette.setBrush(QPalette::Base, result_palette.brush(QPalette::Disabled, QPalette::Base));
    Script_Message_Text->setPalette(result_palette);
    Script_Message_Text->setMinimumHeight(100);
    replace_message_right_layout->addWidget(Script_Message_Text, 50);
    replace_message_layout->addLayout(replace_message_right_layout);

    left_layout->addLayout(replace_message_layout, 100);

    Script_JS_Context = NULL;
    Script_Modified = false;

    left_container->setLayout(left_layout);
    container_splitter->addWidget(left_container);
    container_splitter->setStretchFactor(0, 50);

    QWidget *right_container = new QWidget(this);
    right_container->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *right_layout = new QVBoxLayout;
    right_layout->setContentsMargins(0, 0, 0, 0);
    right_layout->setSpacing(2);

    QLabel *reference_tree_label = new QLabel(tr("Click to copy, ⌘-Click to paste"));
    reference_tree_label->setAlignment(Qt::AlignHCenter);
    reference_tree_label->setToolTip(tr("Click to copy, ⌘-Click to paste"));
    right_layout->addWidget(reference_tree_label);

    JavaScript_Referennce_Tree = new TreeWidget(this);
    JavaScript_Referennce_Tree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    JavaScript_Referennce_Tree->setColumnCount(1);
    JavaScript_Referennce_Tree->header()->setHidden(true);
    JavaScript_Referennce_Tree->setRootIsDecorated(true);
    JavaScript_Referennce_Tree->setFont(font);

    QPalette tree_palette = JavaScript_Referennce_Tree->palette();
    tree_palette.setColor(QPalette::AlternateBase, QColor(224, 240, 255));
    JavaScript_Referennce_Tree->setPalette(tree_palette);
    JavaScript_Referennce_Tree->setAlternatingRowColors(true);

    JavaScript_Referennce_Tree->clear();

    int category_root_count = 0;
    QTreeWidgetItem *category_root;
    QTreeWidgetItem *item_root;
    QList <QTreeWidgetItem*> expand_category_root_list;
    QStringList expand_category_list = QStringList({"Statements", "Strings"});

    QList <QStringList> javascript_reference = JavaScript_Reference();

    QString current_category_name = "";
    for (int reference_idx = 0; reference_idx < javascript_reference.count(); reference_idx += 1) {
        QStringList js_item = javascript_reference[reference_idx];
        QString category_name = js_item[0];
        QString item_name = js_item[1];
        QString item_explain = js_item[2];

        if (not (category_name == current_category_name)) {
            category_root_count += 1;
            QStringList category_root_list;
            category_root_list << category_name << "";
            category_root = new QTreeWidgetItem(JavaScript_Referennce_Tree, category_root_list);
            current_category_name = category_name;
            if (expand_category_list.contains(category_name)) expand_category_root_list.append(category_root);
        }

        QStringList item_root_list;
        item_root_list << item_name << item_explain;
        item_root = new QTreeWidgetItem(category_root, item_root_list);
        item_root->setData(0, Qt::UserRole, item_name);
        item_root->setData(0, Qt::ToolTipRole, item_explain);
    }

    // JavaScript_Referennce_Tree->expandToDepth(0);
    for (int list_idx = 0; list_idx < expand_category_root_list.count(); list_idx += 1) {
        QTreeWidgetItem *expand_category_root = expand_category_root_list.at(list_idx);
        expand_category_root->setExpanded(true);
    }

    connect(JavaScript_Referennce_Tree, SIGNAL(clicked(QModelIndex)),
            this, SLOT(onJavaScriptReferenceTreeClicked(QModelIndex)));

    JavaScript_Referennce_Tree->Detail_Splitter = container_splitter;
    right_layout->addWidget(JavaScript_Referennce_Tree);

    right_container->setLayout(right_layout);
    container_splitter->addWidget(right_container);
    container_splitter->setStretchFactor(1, 50);

    container_splitter->setOpenSizes(QList<int> () << 700 << 300);
    container_splitter->setClosedSizes(QList<int> () << 1000 << 0);
    container_splitter->setSizes(QList<int> () << 1000 << 0);
    return container_splitter;
}

void
RegularExpressionIDE::onScript_Editor_TextChanged ( ) {
    Script_Modified = true;
}

void
RegularExpressionIDE::onSeriesExampleClicked ( bool ) {
    Script_Find_Pattern->Set_PlainText("\\$(?<initial>\\d+)");
    Script_Target->Set_PlainText("$2");
    QString script_text =
R"~~~(
// This script replaces, on successive calls, "$2" with "\2", "\3", "\4", etc.
// It would replace, on successive calls, "$3" with "\3", "\4", "\5", etc.
// It can be used whenever an unknown number of matches to a single group ...
// ... must be captured. First replace that single group w/ "$2", then ...
// ... Use this script to replace "$2"s with a series as above.
// Scripts must all begin with "function replace_function(match_obj) {
function replace_function(match_obj) {
    // Argument "match_obj" has at least one property, match_obj.group_0, which captures ...
    // ... entire string found by your regex, ...
    // ... also accessible as match_obj["group_0"] or match_obj['0'].
    // Property match_obj.group_1 and match_obj.group_initial or match_obj.initial are ...
    // ... both the first capture group's capture in this case.
    // The part you write starts below here ...

    // print(Object.keys(match_obj));
    // print(match_obj.group_0, match_obj.group_1, match_obj.group_initial);

    // Uncomment commented lines below to demo debug messages
    // print(typeof inc_val);
    if (typeof inc_val == "undefined") {
        inc_val = parseInt(match_obj.group_0.replace("$", ""));
        // Or, it could be done a second way as below
        // var pattern = /\d+/g;
        // inc_val = parseInt(pattern.exec(match_obj.group_0));
        // Or, it could be done a third way as below
        // inc_val = parseInt(match_obj.group_initial);
        // Or, it could be done a fourth way as below
        // inc_val = parseInt(match_obj.group_1);
    }
    // print(inc_val);
    var ret_val = "\\" + inc_val.toString();
    inc_val++;
    // print(ret_val, inc_val);
    return ret_val;

    // ... and ends above here.
    // You must return a replacement string.
}
// Scripts must all end with "}".
)~~~";
    Script_JavaScript_Editor->Set_PlainText(script_text.trimmed() + "\n");
    Script_Replace_Text->clear();
    Script_Message_Text->clear();
    Script_Modified = true;
}

void
RegularExpressionIDE::onDemoExampleClicked ( bool ) {
    Script_Find_Pattern->Set_PlainText("(?:(?<numbers>[0-9]+)|(?<letters>[a-z]+)|(?<symbols>[@#$%&]+))+");
    Script_Target->Set_PlainText("123abc$%&");
    QString script_text =
R"~~~(
// This script demonstrates another solution similar to the demo example.
// It is not intended for actual use w/ RegExIDE, but rather as a demonstration ...
// ... of JavaScript programming techniques.
// Scripts must all begin with "function replace_function(match_obj) { ...
function replace_function(match_obj) {
    // Argument "match_obj" has at least one property, match_obj.group_0, which captures ...
    // ... entire string found by your regex, ...
    // ... also accessible as match_obj["group_0"] or match_obj['0'].
    // The part you write starts below here ...

    return match_obj.group_symbols.split("").reverse().join("") +
           match_obj.group_letters.split("").reverse().join("") +
           match_obj.group_numbers.split("").reverse().join("");

    // Or, equivalently as below
    // return match_obj["group_symbols"].split("").reverse().join("") +
    //        match_obj["group_letters"].split("").reverse().join("") +
    //        match_obj["group_numbers"].split("").reverse().join("");

    // Or, equivalently as below
    // return match_obj.symbols.split("").reverse().join("") +
    //        match_obj.letters.split("").reverse().join("") +
    //        match_obj.numbers.split("").reverse().join("");

    // Or, the solution below would match the demo exactly
    // return match_obj.group_3 + match_obj.group_2 + match_obj.group_1;

    // Or, equivalently as below
    // return match_obj["group_3"] + match_obj["group_2"] + match_obj["group_1"];

    // ... and ends above here.
    // You must return a replacement string.
}
// Scripts must all end with "}".
)~~~";
    Script_JavaScript_Editor->Set_PlainText(script_text.trimmed() + "\n");
    Script_Replace_Text->clear();
    Script_Message_Text->clear();
    Script_Modified = true;
}

void
RegularExpressionIDE::onExtremeExampleClicked ( bool ) {
    Script_Find_Pattern->Set_PlainText("\\s*(?<x>\\d+)\\s*,\\s*(?<y>\\d+)\\s*");
    Script_Target->Set_PlainText("2,2");
    QString script_text =
R"~~~(
// This script 'draws' a tic-tac-toe board with an 'X' in the supplied position.
// The position is given as x,y where both x and y must be between 1 and 3.
// If no (or invalid) position given, the script moves first with an 'O', ...
// ... otherwise the script makes its countermove also with an 'O'. Then enter ...
// ... a valid 'X' countermove, to which the script 'O' countermoves, and repeat.
// It is not intended for actual use w/ RegExIDE, but as a demonstration ...
// ... of JavaScript programming techniques.

// Each of the three pairs of y,x, in other words [y0,x0, y1,x1, y2,x2], represent ...
// ... board[y,x] positions that if occupied by all 'X' or all 'O' consititute a win.
var winning_runs = [ [0,0,0,1,0,2], [1,0,1,1,1,2], [2,0,2,1,2,2],
                     [0,0,1,0,2,0], [0,1,1,1,2,1], [0,2,1,2,2,2],
                     [0,0,1,1,2,2], [0,2,1,1,2,0] ];

function run_open_move(current_board, run_index) {
    // When a winning run is either two of 'X' or two of 'O' and one ' ' (open)
    var open = winning_runs[run_index];
    if (current_board[open[0]][open[1]] == " ") return [ open[0], open[1] ];
    else if (current_board[open[2]][open[3]] == " ") return [ open[2], open[3] ];
    else if (current_board[open[4]][open[5]] == " ") return [ open[4], open[5] ];
    else return [-1,-1];
}

function make_valid_script_move(current_board, move) {
    // If this move is valid, make it and return whether move was made
    var valid_move = ((move[0] >= 0) && (move[0] < 3) &&
                      (move[1] >= 0) && (move[1] < 3)) &&
                     (current_board[move[0]][move[1]] == " ");
    if (valid_move) current_board[move[0]][move[1]] = "O";
    return valid_move;
}

var hash_lines = "--+-+--";
function draw_board(current_board) {
    // 'Draw' the current board into a string
    var board_as_string = "";
    for (var y = 0; y < 3; y++) {
        var row = " ";
        for (var x = 0; x < 3; x++) {
            row += current_board[y][x];
            if (x < 2) row += "|";
        }
        board_as_string += row + "\n";
        if (y < 2) board_as_string += hash_lines + "\n";
    }
    return board_as_string;
}

// Scripts must all begin with "function replace_function(match_obj) { ...
function replace_function(match_obj) {
    // Argument "match_obj" has at least one property, match_obj.group_0, which captures ...
    // ... entire string found by your regex, ...
    // ... also accessible as match_obj["group_0"] or match_obj['0'].
    // The part you write starts below here ...

    if (typeof board == "undefined") {
        // There's no board, set up a new one with no moves made yet ...
        board = [ [ ' ', ' ', ' '] ,
                  [ ' ', ' ', ' '] ,
                  [ ' ', ' ', ' '] ];
        // ... and initialize other game-level variables as well.
        winner = "   ";
        open_moves = 9;
    }

    // Determine whether any move can be made now
    if ((winner == "XXX") || (winner == "OOO")) print("Already have a winner.");
    else if (open_moves == 0) print("No moves left, must be a draw.");
    else {
        // If the user has entered a valid move, make it
        var move_x = parseInt(match_obj.x) - 1;
        var move_y = parseInt(match_obj.y) - 1;
        if (((move_x >= 0) && (move_x < 3)) &&
            ((move_y >= 0) && (move_y < 3))) {
            // The user plays 'X'
            if (board[move_y][move_x] == " ") {
                board[move_y][move_x] = "X";
                open_moves--;
            }
            else {
                print("Already taken, try again.");
                // Indicate invalid move
                winner = "___";
            }
        }
    }

    var runs = [];
    if (winner == "   ") {
        // Check whether user has already won.
        for (var win_idx = 0; win_idx < winning_runs.length; win_idx++) {
            var win = winning_runs[win_idx];
            var run = board[win[0]][win[1]] + board[win[2]][win[3]] + board[win[4]][win[5]];
            if (run == "XXX") {
                print("You win.");
                winner = run;
                break;
            }
            else if (run == "OOO") {
                print("Script alreay won.");
                winner = run;
                break;
            }
            else runs.push(run);
        }
    }

    if (winner == "   ") {
        // Is a one-move win by script currently possible?
        for (var run_idx = 0; run_idx < runs.length; run_idx++) {
            var win_run = runs[run_idx];
            if ((win_run == " OO") || (win_run == "O O") || (win_run == "OO ")) {
                var winning_move = run_open_move(board, run_idx);
                if (make_valid_script_move(board, winning_move)) {
                    open_moves--;
                    print("Script wins.");
                    winner = "OOO";
                    break;
                }
            }
        }
    }

    if (winner == "   ") {
        // Is there a threat of a user's one-move win that must be blocked?
        for (var run_idx = 0; run_idx < runs.length; run_idx++) {
            var threat_run = runs[run_idx];
            if ((threat_run == " XX") || (threat_run == "X X") || (threat_run == "XX ")) {
                var blocking_move = run_open_move(board, run_idx);
                if (make_valid_script_move(board, blocking_move)) {
                    open_moves--;
                    // Indicate script move already made
                    winner = "---";
                    break;
                }
            }
        }
    }

    if (winner == "   ") {
        // Always take center, because of all moves, ...
        // ... it participates in largest number of winning runs (four).
        // Accordingly, it also blocks the most user winning runs.
        if (make_valid_script_move(board, [1,1])) {
            open_moves--;
            // Indicate script move already made
            winner = "---";
        }
        else {
            // List all valid moves for script.
            // Prefer corner moves which participate in ...
            // ... second largest number of winning runs (three).
            // All side moves participate in only two winning runs each.
            var corner_moves = [];
            var valid_moves = [];
            for (var y = 0; y < 3; y++) {
                for (var x = 0; x < 3; x++) {
                    if (board[y][x] == " ") {
                        var move = [y, x];
                        if (((y == 0) || (y == 2)) && ((x == 0) || (x == 2))) {
                            corner_moves.push(move);
                            valid_moves.push(move);
                        }
                        else valid_moves.push(move);
                    }
                }
            }

            var fork_moves = [];
            // Test valid script moves looking for one that leaves script with two distinct winning ...
            // ... next moves. Since user can't block both next moves, script must be left with ...
            // ... at least one winning move.
            for (var move_idx = 0; move_idx < valid_moves.length; move_idx++) {
                // Make new deep copy of array
                var test_board = JSON.parse(JSON.stringify(board));
                var my_next_moves = [];
                test_board[valid_moves[move_idx][0]][valid_moves[move_idx][1]] = "O";
                for (var win_idx = 0; win_idx < winning_runs.length; win_idx++) {
                    var win = winning_runs[win_idx];
                    var run = test_board[win[0]][win[1]] + test_board[win[2]][win[3]] + test_board[win[4]][win[5]];
                    if ((run == " OO") || (run == "O O") || (run == "OO ")) {
                        var next_move;
                        if (test_board[win[0]][win[1]] == " ") next_move = [ win[0], win[1] ];
                        else if (test_board[win[2]][win[3]] == " ")  next_move = [ win[2], win[3] ];
                        else if (test_board[win[4]][win[5]] == " ")  next_move = [ win[4], win[5] ];
                        // If we haven't found this next move already, store it
                        var next_move_idx = 0;
                        while (next_move_idx < my_next_moves.length) {
                            if (next_move ==
                                my_next_moves[next_move_idx]) break; // Found this move already
                            else next_move_idx++;
                        }
                        if (next_move_idx >=
                            my_next_moves.length) my_next_moves.push(next_move);
                    }
                }
                if (my_next_moves.length >= 2) {
                    // Script has at least two next move winners due to this move, ...
                    // ... both can't be blocked.
                    fork_moves.push(valid_moves[move_idx]);
                }
            }

            var my_move = [-1,-1];
            // If there's a move that sets up two next mover winners, make it
            if (fork_moves.length > 0) my_move = fork_moves[Math.floor(Math.random() * fork_moves.length)];
            // If there's any good move, make it, otherwise pick a valid move at random and make it.
            else if (corner_moves.length > 0) my_move = corner_moves[Math.floor(Math.random() * corner_moves.length)];
            else if (valid_moves.length > 0) my_move = valid_moves[Math.floor(Math.random() * valid_moves.length)];
            if (make_valid_script_move(board, my_move)) {
                open_moves--;
                // Indicate script move already made
                winner = "---";
            }
        }
    }

    if ((winner == "   ") || (winner == "---")) {
        for (var win_idx = 0; win_idx < winning_runs.length; win_idx++) {
            var win = winning_runs[win_idx];
            var run = board[win[0]][win[1]] + board[win[2]][win[3]] + board[win[4]][win[5]];
            if (run == "OOO") {
                winner = run;
                print("Script wins.");
                break;
            }
        }
    }

    // Clean up temporary indicators for this move cycle
    if (! ((winner == "XXX") || (winner == "OOO"))) winner = "   ";
    if ((winner == "   ") && (open_moves == 0)) print("No moves left, must be a draw.");

    // Draw the board, always
    var ret_val = draw_board(board);

    // ... and ends above here.
    // You must return a replacement string.
    return ret_val;
}
// Scripts must all end with "}".
)~~~";
    Script_JavaScript_Editor->Set_PlainText(script_text.trimmed() + "\n");
    Script_Replace_Text->clear();
    Script_Message_Text->clear();
    Script_Modified = true;
}

void
RegularExpressionIDE::onStarterScriptClicked ( bool ) {
    Script_Find_Pattern->Set_PlainText("");
    Script_Target->Set_PlainText("");
    QString script_text =
R"~~~(
// Scripts must all begin with "function replace_function(match_obj) {
function replace_function(match_obj) {
    // Argument "match_obj" has at least one property, match_obj.group_0, which captures ...
    // ... entire string found by your regex, also accessible as match_obj["group_0"].
    // print(match_obj.group_0);
    // The part you write starts below here ...


    // ... and ends above here.
    // You must return a replacement string.
    return ret_val;
}
// Scripts must all end with "}".
)~~~";
    Script_JavaScript_Editor->Set_PlainText(script_text.trimmed() + "\n");
    Script_Replace_Text->clear();
    Script_Message_Text->clear();
    Script_Modified = true;
}

void
RegularExpressionIDE::onResetScriptClicked ( bool ) {
    Script_Replace_Text->clear();
    Script_Message_Text->clear();
    Script_Modified = true;
}

QString Script_Fatal_Error_Messages;

static void script_fatal_error_handler ( void *udata,
                                         const char *msg ) {
    (void) udata;  /* ignored in this case, silence warning */

    /* Note that 'msg' may be NULL. */
    Script_Fatal_Error_Messages += QString("*** FATAL ERROR: ") + QString((msg ? msg : "No message"));
    abort();
}

QString Print_Messages;

static duk_ret_t script_native_print ( duk_context *js_context ) {
    duk_push_string(js_context, " ");
    duk_insert(js_context, 0);
    duk_join(js_context, duk_get_top(js_context) - 1);
    Print_Messages += QString(duk_safe_to_string(js_context, -1)) + QString("\n");
    return 0;
}

void
RegularExpressionIDE::onRunScriptClicked ( bool ) {
    Script_Fatal_Error_Messages.clear();
    Print_Messages.clear();
    Script_Replace_Text->clear();
    Script_Message_Text->clear();

    bool regex_functional = false;
    QRegularExpression regex;
    QRegularExpressionMatchIterator regex_iterator;

    if (Script_Find_Pattern->toPlainText().trimmed().length() > 0) {
        const QString regex_pattern = Script_Find_Pattern->toPlainText();
        regex = QRegularExpression(regex_pattern);
        if (regex.isValid() and (regex_pattern.length() > 0)) {
            regex_iterator = regex.globalMatch(Script_Target->toPlainText());
            if (regex_iterator.hasNext()) {
                // At least one found
                regex_functional = true;
            }
        }
    }

    if (Script_Modified) {        
        if (not (Script_JS_Context == NULL)) {
            duk_destroy_heap(Script_JS_Context);
            Script_JS_Context = NULL;
         }

        // Script_JS_Context = duk_create_heap_default();
        Script_JS_Context = duk_create_heap(NULL, NULL, NULL, NULL, script_fatal_error_handler);

        duk_push_global_object(Script_JS_Context);
        duk_push_c_function(Script_JS_Context, script_native_print, DUK_VARARGS);
        duk_put_prop_string(Script_JS_Context, -2, "print");

        QString replace_script = Script_JavaScript_Editor->toPlainText();

        duk_push_string(Script_JS_Context, replace_script.toLatin1().data());
        if (duk_peval(Script_JS_Context) != 0) {
            Script_Message_Text->insertPlainText(QString("Error: ") +
                                                 QString(duk_safe_to_string(Script_JS_Context, -1)) +
                                                 QString("\n"));
        }
        duk_pop(Script_JS_Context);  /* ignore result */

        duk_push_global_object(Script_JS_Context);

        Script_Modified = false;
    }

    QString replace_text = "";
    duk_get_prop_string(Script_JS_Context, -1 /*index*/, "replace_function");

    // Push matched text onto stack as match_obj.group_0 argument ...
    // ... (whether it's needed or not)
    // duk_push_string(Script_JS_Context, match_text.toLatin1().data());
    duk_idx_t obj_idx = duk_push_object(Script_JS_Context);
    if (Script_Find_Pattern->toPlainText().trimmed().length() == 0) {
        QString match_text = Script_Target->toPlainText();
        duk_push_string(Script_JS_Context, match_text.toLatin1().data());
        duk_put_prop_string(Script_JS_Context, obj_idx, "group_0");
    }
    else if (regex_functional) {
        QStringList capture_groups = regex.namedCaptureGroups();
        const int capture_groups_count = regex.captureCount() + 1;

        QRegularExpressionMatch match = regex_iterator.next();
        for (int idx = 0; idx < capture_groups_count; idx += 1) {
            QString match_capture = match.captured(idx);
            QString match_name = QString("group_") + QString::number(idx);
            duk_push_string(Script_JS_Context, match_capture.toLatin1().data());
            duk_put_prop_string(Script_JS_Context, obj_idx, match_name.toLatin1().data());
            match_name = QString::number(idx);
            duk_push_string(Script_JS_Context, match_capture.toLatin1().data());
            duk_put_prop_string(Script_JS_Context, obj_idx, match_name.toLatin1().data());
            if (not capture_groups.at(idx).isNull()) {
                match_capture = match.captured(capture_groups.at(idx));
                match_name = QString("group_") + capture_groups.at(idx);
                duk_push_string(Script_JS_Context, match_capture.toLatin1().data());
                duk_put_prop_string(Script_JS_Context, obj_idx, match_name.toLatin1().data());
                match_name = capture_groups.at(idx);
                duk_push_string(Script_JS_Context, match_capture.toLatin1().data());
                duk_put_prop_string(Script_JS_Context, obj_idx, match_name.toLatin1().data());
            }
        }
    }

    if (duk_pcall(Script_JS_Context, 1 /*nargs*/) != 0) {
        Script_Message_Text->insertPlainText(QString("Error: ") +
                                             QString(duk_safe_to_string(Script_JS_Context, -1)) +
                                             QString("\n"));
    } else {
        replace_text = QString(duk_safe_to_string(Script_JS_Context, -1));
    }
    duk_pop(Script_JS_Context);  /* pop result/error */

    Script_Replace_Text->Set_PlainText(replace_text);

    if (Script_Fatal_Error_Messages.length() > 0) Script_Message_Text->insertPlainText(Script_Fatal_Error_Messages + "\n");
    if (Print_Messages.length() > 0) Script_Message_Text->insertPlainText(Print_Messages + "\n");
}

void
RegularExpressionIDE::onJavaScriptReferenceTreeClicked ( QModelIndex model_index ) {
    if (model_index.isValid() and
        (model_index.column() == 0)) {
        QTreeWidget *sender_reference_tree = dynamic_cast<QTreeWidget*>(sender());

        QModelIndex parent_model_index = sender_reference_tree->model()->parent(model_index);
        Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
        if (parent_model_index.isValid()) {
            QString clicked_value =
                      sender_reference_tree->model()->data(model_index, Qt::UserRole).toString();
            if (clicked_value.startsWith("str.")) clicked_value = clicked_value.replace("str.", ".");
            else if (clicked_value.startsWith("obj.")) clicked_value = clicked_value.replace("obj.", ".");
            else if (clicked_value.startsWith("obj[")) clicked_value = clicked_value.replace("obj[", "[");
            else if (clicked_value.startsWith("array.")) clicked_value = clicked_value.replace("array.", ".");
            if (modifiers == Qt::NoModifier) {
                QApplication::clipboard()->setText(clicked_value);
            }
            else if ((modifiers & Qt::ControlModifier) == Qt::ControlModifier) {
                if (clicked_value.contains("…")) {
                    QString selected_text = Script_JavaScript_Editor->textCursor().selectedText();
                    if (selected_text.length() > 0) clicked_value.replace("…", selected_text);
                }
                Script_JavaScript_Editor->insertPlainText(clicked_value);
            }
        }
    }
}

//    JavaScript_Reserved_Words =
//        QStringList({"abstract", "arguments", "await", "boolean", "break", "byte", "case", "catch",
//                     "char", "class", "const", "continue", "debugger", "default", "delete", "do",
//                     "double", "else", "enum", "eval", "export", "extends", "false", "final",
//                     "finally", "float", "for", "function", "goto", "if", "implements", "import",
//                     "in", "instanceof", "int", "interface", "let", "long", "native", "new",
//                     "null", "package", "private", "protected", "public", "return", "short", "static",
//                     "super", "switch", "synchronized", "this", "throw", "throws", "transient", "true",
//                     "try", "typeof", "var", "void", "volatile", "while", "with", "yield"});


#endif // REGEXIDE_SCRIPT_PAGE_UI_CPP
