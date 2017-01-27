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

#include "RegularExpressionIDE.h"

#include <QDebug>
#include "PCRE_Trace.h"
#include "RegExIDE_Help.h"
#include "RegExIDE_Copyright.h"

// Enhancements:
//   Apply
//   Store/Retrieve rx/replace patterns

// Finished:
//   Replace (done)
//   Reference w/ insertion (done)
//   Highlight groups (done)
//   Help (done)

// $ cd ~/Documents/RegExIDE_Develop/build-regularexpression-Desktop_Qt_5_6_1_clang_64bit-Release
// $ /Developer/5.6/clang_64/bin/macdeployqt RegExIDE.app

Q_DECLARE_METATYPE(QRegularExpression::MatchType)

QString RegExIDE_Preferences_Initialization_Text =
R"~~~(
{
  "Preferences": {
    "Home_Directory": "~/Downloads",
    "Import_Directory": "~/Documents",
    "Export_Directory": "~/Documents"
  },
  "RegEx_Catalog": [
    {
      "Category": "Demo",
      "RegEx_Name": "Simple find && replace",
      "RegEx_Pattern": "(?:(?<numbers>[0-9]+)|(?<letters>[a-z]+)|(?<symbols>[@#$%&]+))+",
      "Replace_Pattern": "\\1\\3\\2",
      "Target": "123abc$%& 456def@#$ 789ghi#$% 123$%&abc 456@#$def 789#$%ghi 123abc$%& 456def@#$ 789ghi#$%"
    },
    {
      "Series": "INSERT to UPDATE",
      "Series_Index": 0,
      "Category": "INSERT to UPDATE",
      "RegEx_Name": "INSERT to UPDATE Step 1",
      "RegEx_Pattern": "INSERT\\s+(?:INTO)?\\s+(`[^`]+`)\\s*\\((\\s*`[^`]+`),\\s*((?:\\s*`[^`]+`,)+\\s*`[^`]+`\\))\\s*VALUES",
      "Replace_Pattern": "UPDATE \\1\nSET \\3WHERE (\\2 = $1);\n",
      "Target": "INSERT INTO `photo` (`id`, `width`, `height`, `bytes`, `url`, `server`, `web_path`, `creation_date`, `is_orphan`, `is_local`, `local_date`, `type`)\nVALUES"
    },
    {
      "Series": "INSERT to UPDATE",
      "Series_Index": 1,
      "Category": "INSERT to UPDATE",
      "RegEx_Name": "INSERT to UPDATE Step 2",
      "RegEx_Pattern": "(?:(`[^`]+`)(?:(,)|(?:\\))))",
      "Replace_Pattern": "\\1 = $2\\2\n"
    },
    {
      "Series": "INSERT to UPDATE",
      "Series_Index": 2,
      "Category": "INSERT to UPDATE",
      "RegEx_Name": "INSERT to UPDATE Step 3",
      "RegEx_Pattern": "\\$2",
      "Replace_Script": "function replace_function(match_obj) {\n    if (typeof inc_val == \"undefined\") {\n        inc_val = parseInt(match_obj.group_0.replace(\"$\", \"\"));\n    }\n    var ret_val = \"\\\\\" + inc_val.toString();\n    inc_val++;\n    return ret_val;\n}\n"
    },
    {
      "Series": "INSERT to UPDATE",
      "Series_Index": 3,
      "Series_Help": "After replace, transfer <b>Target</b> to <b>Replace pattern</b> using the <b>To Replace pattern</b> button below.",
      "Series_After_Replace": "Target_To_Replace",
      "Category": "INSERT to UPDATE",
      "RegEx_Name": "INSERT to UPDATE Step 4",
      "RegEx_Pattern": "\\$",
      "Replace_Pattern": "\\"
    },
    {
      "Series": "INSERT to UPDATE",
      "Series_Index": 4,
      "Category": "INSERT to UPDATE",
      "RegEx_Name": "INSERT to UPDATE Step 5",
      "RegEx_Pattern": "\\s*\\((\\d+),\\s*(\\d+),\\s*(\\d+),\\s*(\\d+),\\s*('[^']+'),\\s*(\\d+),\\s*('[^']+'),\\s*('[^']+'),\\s*(\\d+),\\s*(\\d+),\\s*('[^']+'),\\s*(\\d+)\\)[,;]\\n",
      "Target": "\t(352444, 600, 450, 4554052, 'http://cdn.internet.com/photos/RsEiUEvNvsgX.jpg', 1, '/photos/RsEiUEvNvsgX.jpg', '2007-09-28 11:16:17', 0, 1, '0000-00-00 00:00:00', 4),\n\t(355163, 600, 450, 1475720, 'http://cdn.internet.com/photos/2Z5YacCG7Bnb.jpg', 1, '/photos/2Z5YacCG7Bnb.jpg', '2007-09-28 17:27:35', 0, 1, '0000-00-00 00:00:00', 4),\n\t(2347669, 320, 240, 2795046, 'http://cdn.internet.com/photos/lc97ZfR6QHzH.jpg', 1, '/photos/lc97ZfR6QHzH.jpg', '2008-03-06 15:12:33', 0, 1, '0000-00-00 00:00:00', 4),\n\t(2348780, 320, 240, 2463312, 'http://cdn.internet.com/photos/TcB8R8jR2dIF.jpg', 1, '/photos/TcB8R8jR2dIF.jpg', '2008-03-06 16:27:21', 0, 1, '0000-00-00 00:00:00', 4),\n"
    },
    {
      "Series": "Log Extracts to UPDATE",
      "Series_Index": 0,
      "Category": "Log Extracts to UPDATE",
      "RegEx_Name": "Unescape forwardslash",
      "RegEx_Pattern": "\\\\/",
      "Replace_Pattern": "/",
      "Target": "id=264143214 query=INSERT INTO `photo` (`type`, `width`, `height`, `is_local`, `server`, `web_path`, `url`, `creation_date`, `bytes`) VALUES (4, 640, 480, 38.85, '3', '\\/rfHxXrxHpe8C.jpg', 'https:\\/\\/cdn.internet.com\\/photos\\/rfHxXrxHpe8C.jpg', 1483345463, 3880897)\nid=264144355 query=INSERT INTO `photo` (`type`, `width`, `height`, `is_local`, `server`, `web_path`, `url`, `creation_date`, `bytes`) VALUES (4, 1024, 576, 789.16, '3', '\\/lAT1wvpw0jof.jpg', 'https:\\/\\/cdn.internet.com\\/photos\\/lAT1wvpw0jof.jpg', 1483358321, 95935426)\nid=264144356 query=INSERT INTO `photo` (`type`, `width`, `height`, `is_local`, `server`, `web_path`, `url`, `creation_date`, `bytes`) VALUES (4, 640, 360, 789.16, '3', '\\/beH57MgFU2tM.jpg', 'https:\\/\\/cdn.internet.com\\/photos\\/beH57MgFU2tM.jpg', 1483358323, 60806597)\nid=264144728 query=INSERT INTO `photo` (`type`, `width`, `height`, `is_local`, `server`, `web_path`, `url`, `creation_date`, `bytes`) VALUES (4, 1024, 576, 142.09, '3', '\\/ITntLAHfvndO.jpg', 'https:\\/\\/cdn.internet.com\\/photos\\/ITntLAHfvndO.jpg', 1483359524, 19818680)\n"
    },
    {
      "Series": "Log Extracts to UPDATE",
      "Series_Index": 1,
      "Category": "Log Extracts to UPDATE",
      "RegEx_Name": "Extract to UPDATE",
      "RegEx_Pattern": "id=(\\d+)\\s+query=INSERT INTO `photo` \\([^)]+\\)\\s*VALUES\\s*\\((\\d+),\\s*(\\d+),\\s*(\\d+),\\s*([0-9.]+),\\s*('\\d+'),\\s*('[^']+'),\\s*('[^']+'),\\s*(\\d+),\\s*(\\d+)\\)\\n",
      "Replace_Pattern": "UPDATE photo\nSET `type`=\\2,\n    `width`=\\3,\n    `height`=\\4,\n    `is_local`=\\5,\n    `server`=\\6,\n    `web_path`=\\7,\n    `url`=\\8,\n    `creation_date`=\\9,\n    `bytes`=\\10\nWHERE (id = \\1);\n"
    }
  ]
}
)~~~";

QFont Application_Font;

QString Application_Title;

QString Application_Home_Directory = "~/Documents";
QString Application_Import_Directory = "~/Documents";
QString Application_Export_Directory = "~/Documents";

int main ( int argc, char *argv[] ) {
    QApplication app(argc, argv);
    // qDebug() << qVersion();

    RegularExpressionIDE main_window;
    main_window.show();
    return app.exec();
    QString copyright;
    copyright += Obligatory_Copyright_krc;
    copyright += "\n";
    copyright += Obligatory_Qt_Copyright;
    copyright += Obligatory_PCRE_Copyright;
    copyright += Obligatory_DukTape_Copyright;
    copyright += Obligatory_X2_Copyright;
}

RegularExpressionIDE::RegularExpressionIDE ( QWidget *parent ) : QMainWindow ( parent )
{
    QString window_title = (char*) "Regular Expression IDE (version: ";
    QString now_date = QString(__DATE__).trimmed().replace("  ", " ");
    QDate compile_date = QDate::fromString(now_date, "MMM d yyyy");
    QTime compile_time = QTime::fromString(QString(__TIME__).trimmed(), "hh:mm:ss");
    window_title.append(compile_date.toString("yyyyMMdd"));
    window_title.append("-");
    window_title.append(compile_time.toString("hhmmss"));
    window_title.append(")");

    Application_Title = window_title;

    Trace_First_Match_Only = true;
    Trace_Dirty = false;
    Trace_in_Process = false;

    Defer_UI_Refresh = true;

    Apply_Target_Offset = -1;
    Apply_Target_FindNext_Offset = -1;

    UI_Initialize();
    setWindowTitle(window_title);

    bool initialization_success = Open_Application_Initialization();

    // Save_Application_Initialization();

    if (initialization_success) Preferences_Menu_Initialize();

    UI_Connect();

    Application_Font = this->font();

#ifdef QT_DEBUG
    Demo_Initialize(3);
#endif

    Defer_UI_Refresh = false;
    UI_Refresh();
}

RegularExpressionIDE::~RegularExpressionIDE ( ) {
}

void
RegularExpressionIDE::closeEvent ( QCloseEvent *event )
{
    if (not (Script_JS_Context == NULL)) {
        duk_destroy_heap(Script_JS_Context);
        Script_JS_Context = NULL;
     }
    event->accept();
    // event->ignore();
}

QString
RegularExpressionIDE::Upgrade_Application_Initialization ( QString Initialization_JSON ) {
    QString ini_json = Initialization_JSON;
    ini_json.replace("(match)", "(match_obj)");
    ini_json.replace("match.match_", "match_obj.group_");
    ini_json.replace("match.group_", "match_obj.group_");
    ini_json = ini_json.replace("match[\"match_", "match_obj[\"group_");
    ini_json = ini_json.replace("match[\"group_", "match_obj[\"group_");
    ini_json = ini_json.replace("match[", "match_obj[");
    return ini_json;
}

bool
RegularExpressionIDE::Open_Application_Initialization ( ) {
    QString app_data_path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QDir app_data_directory(app_data_path);
    bool app_data_path_exists = app_data_directory.exists();
    if (not app_data_path_exists) {
        app_data_path_exists = app_data_directory.mkpath(app_data_path);
        if (not app_data_path_exists) {
            int i = 0;
            i++;
        }
    }

    RegExIDE_Ini_Path = QDir::toNativeSeparators(app_data_path + QString("/") + "RegExIDE.ini");

    // Does this file exist?
    QFileInfo test_file(RegExIDE_Ini_Path);
    if (not (test_file.exists() and test_file.isFile())) {
        // It does not, create one such
        QFile ini_file (RegExIDE_Ini_Path);
        if (ini_file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&ini_file);
            stream << RegExIDE_Preferences_Initialization_Text;
            ini_file.close();
        }
    }

    QFile ini_file (RegExIDE_Ini_Path);
    ini_file.open(QIODevice::ReadOnly);
    QString Initialization_JSON = ini_file.readAll();
    ini_file.close();

    using namespace QtOrderedJson;

    bool initialization_success = false;
    if (Initialization_JSON.length() > 0) {
        Initialization_JSON = Upgrade_Application_Initialization(Initialization_JSON);
        RegExIDE_Initialization = toOrderedMap(parseJson(Initialization_JSON, initialization_success));
    }

    if (not initialization_success) RegExIDE_Initialization.clear();

    return initialization_success;
}

void
RegularExpressionIDE::Save_Application_Initialization ( QString Save_Initialization_FileName ) {
    QString save_ini_filename = RegExIDE_Ini_Path;
    bool rename_success;
    if (Save_Initialization_FileName.isEmpty() or
        (Save_Initialization_FileName == RegExIDE_Ini_Path)) {
        QFileInfo ini_file_path_info(RegExIDE_Ini_Path);
        // Rename current MyQueryIDE.ini to MyQueryIDE-yyyymmdd-hhmmss.ini ...
        QString rename_regexide_ini_path =
                  ini_file_path_info.absolutePath() + QString("/") +
                  ini_file_path_info.completeBaseName() +
                  QDate::currentDate().toString("-yyyyMMdd") +
                  QTime::currentTime().toString("-hhmmss") + QString(".") +
                  ini_file_path_info.suffix();
        rename_success = QFile::rename(RegExIDE_Ini_Path, QDir::toNativeSeparators(rename_regexide_ini_path));
    }
    else {
        save_ini_filename = Save_Initialization_FileName;
        rename_success = true;
    }

    using namespace QtOrderedJson;

    if (rename_success) {
        bool serialization_success = false;
        QString init_json = serializeJsonStr(fromOrderedMap(RegExIDE_Initialization), serialization_success);
        if (init_json.length() > 0) {
            QFile save_ini(save_ini_filename);
            if (not save_ini.open(QIODevice::WriteOnly))
                // Error message here?
                return;

            QTextStream stream(&save_ini);
            stream << init_json;
            stream.flush();
            save_ini.close();
        }
    }
}

void
RegularExpressionIDE::Preferences_Menu_Initialize ( ) {
    // Set preferences
    if (RegExIDE_Initialization.contains("Preferences")) {
        OrderedVariantMap preference_descr =
                            toOrderedMap(RegExIDE_Initialization.value("Preferences"));

        if (preference_descr.contains("Home_Directory"))
            Application_Home_Directory = preference_descr.value("Home_Directory").toString();
        if (preference_descr.contains("Import_Directory"))
            Application_Import_Directory = preference_descr.value("Import_Directory").toString();
        if (preference_descr.contains("Export_Directory"))
            Application_Export_Directory = preference_descr.value("Export_Directory").toString();
    }

    setMenuBar(new QMenuBar(this));
    QMenu *RegExIDE_Menu = new QMenu("RegExIDE", this);

    RegExIDE_Menu->addAction(tr("Preferences"), this, SLOT(onMenuPreferences()));

    menuBar()->addMenu(RegExIDE_Menu);

    // RegEx Catalog
    QMenu *regex_catalog_menu = menuBar()->addMenu("RegExCatalog");
    regex_catalog_menu->addAction(tr("Clear"), this, SLOT(onMenuClear()));
    regex_catalog_menu->addSeparator();

    if (RegExIDE_Initialization.contains("RegEx_Catalog")) {
        QHash <QString, QMenu*> regex_catalog_dictionary;

        QVariantList regex_catalog_descriptors = RegExIDE_Initialization.value("RegEx_Catalog").toList();
        for (int regex_idx = 0; regex_idx < regex_catalog_descriptors.count(); regex_idx += 1) {
            OrderedVariantMap regex_descr =
                                toOrderedMap(regex_catalog_descriptors[regex_idx]);
            if (regex_descr.contains("Category") and regex_descr.contains("RegEx_Name") and
                regex_descr.contains("RegEx_Pattern")) {
                QString category_name = regex_descr.value("Category").toString();
                QString regex_name = regex_descr.value("RegEx_Name").toString();

                if (not regex_catalog_dictionary.contains(category_name)) {
                    // Add another submenu
                    regex_catalog_dictionary[category_name] = regex_catalog_menu->addMenu(category_name);
                }

                // Now add item to submenu
                QAction *item =
                  regex_catalog_dictionary[category_name]->addAction(regex_name, this, SLOT(onMenuRegExCatalog()));

                QHash <QString, QVariant> setup_list;
                // if (regex_descr.contains("Series"))
                //     setup_list["Series"] = regex_descr.value("Series").toString();
                // if (regex_descr.contains("Series_Index"))
                //     setup_list["Series_Index"] = regex_descr.value("Series_Index").toString();
                if (regex_descr.contains("Series_Help"))
                    setup_list["Series_Help"] = regex_descr.value("Series_Help").toString();
                setup_list["RegEx_Pattern"] = regex_descr.value("RegEx_Pattern").toString();
                if (regex_descr.contains("Replace_Pattern"))
                    setup_list["Replace_Pattern"] = regex_descr.value("Replace_Pattern").toString();
                if (regex_descr.contains("Target"))
                    setup_list["Target"] = regex_descr.value("Target").toString();
                item->setData(setup_list);
            }
        }

        Populate_RegEx_Catalog_Tree(regex_catalog_descriptors);

        QHash <QString, QMap <int, QVariant>>  ordered_series_descriptors;
        QStringList series_name_list;
        for (int regex_idx = 0; regex_idx < regex_catalog_descriptors.count(); regex_idx += 1) {
            OrderedVariantMap regex_descr =
                                toOrderedMap(regex_catalog_descriptors[regex_idx]);
            if (regex_descr.contains("Series") and regex_descr.contains("Series_Index")) {
                QString series_name = regex_descr.value("Series").toString();
                int series_index = regex_descr.value("Series_Index").toInt();
                if (not ordered_series_descriptors.contains(series_name)) {
                    ordered_series_descriptors[series_name] = QMap <int, QVariant>();
                    series_name_list.append(series_name);
                }
                QMap <int, QVariant> this_series = ordered_series_descriptors[series_name];
                this_series[series_index] = fromOrderedMap(regex_descr);
                ordered_series_descriptors[series_name] = this_series;
            }
        }

        series_name_list.sort();
        Series_ComboBox->clear();
        for (int name_idx = 0; name_idx < series_name_list.count(); name_idx += 1) {
            QString series_name = series_name_list[name_idx];
            QMap <int, QVariant> this_series = ordered_series_descriptors[series_name];
            QVariantList this_series_list;
            QList<int> this_series_keys = this_series.keys();
            for (int key_idx = 0; key_idx < this_series_keys.count(); key_idx += 1) {
                int key = this_series_keys[key_idx];
                this_series_list.append(fromOrderedMap(toOrderedMap(this_series[key])));
            }
            Series_ComboBox->insertItem(name_idx, series_name, this_series_list);
        }
    }
}

void
RegularExpressionIDE::onMenuPreferences ( ) {

}

void
RegularExpressionIDE::onMenuRegExCatalog ( ) {
    QAction *sender_action = dynamic_cast<QAction*>(sender());
    QHash<QString, QVariant> setup_list = sender_action->data().toHash();

    Defer_UI_Refresh = true;

    if (RegExIDE_Pages->currentIndex() == Main_Tab_Index) {
        if (setup_list.contains("RegEx_Pattern")) {
            // Don't defeat Undo/Redo
            RegEx_Pattern_Edit->Set_PlainText(setup_list.value("RegEx_Pattern").toString());
        }

        if (setup_list.contains("Replace_Pattern")) {
            // Don't defeat Undo/Redo
            Replace_Pattern_Edit->Set_PlainText(setup_list.value("Replace_Pattern").toString());
        }

        if (setup_list.contains("Target")) {
            // Don't defeat Undo/Redo
            Target_Text_Edit->Set_PlainText(setup_list.value("Target").toString());
        }
    }
    else if (RegExIDE_Pages->currentIndex() == RegEx_Catalog_Tab_Index) {
        if (setup_list.contains("RegEx_Pattern")) {
            // Don't defeat Undo/Redo
            Catalog_RegEx_Pattern->Set_PlainText(setup_list.value("RegEx_Pattern").toString());
        }

        if (setup_list.contains("Replace_Pattern")) {
            // Don't defeat Undo/Redo
            Catalog_Replace_Pattern->Set_PlainText(setup_list.value("Replace_Pattern").toString());
        }

        if (setup_list.contains("Target")) {
            // Don't defeat Undo/Redo
            Catalog_Target->Set_PlainText(setup_list.value("Target").toString());
        }
    }
    else if (RegExIDE_Pages->currentIndex() == Apply_Tab_Index) {
        if (setup_list.contains("RegEx_Pattern")) {
            // Don't defeat Undo/Redo
            Apply_Find_Pattern->Set_PlainText(setup_list.value("RegEx_Pattern").toString());
        }

        if (setup_list.contains("Replace_Pattern")) {
            // Don't defeat Undo/Redo
            Apply_Replace_Pattern->Set_PlainText(setup_list.value("Replace_Pattern").toString());
        }

        if (setup_list.contains("Series_Help")) {
            Series_Help_Label->setText(setup_list.value("Series_Help").toString());
        }

        if (setup_list.contains("Target")) {
            // Don't defeat Undo/Redo
            Apply_Target->Set_PlainText(setup_list.value("Target").toString());
        }
        Apply_Target_Offset = -1;
    }

    Defer_UI_Refresh = false;
    UI_Refresh();
}

void
RegularExpressionIDE::onMenuClear ( ) {
    Defer_UI_Refresh = true;

    if (RegExIDE_Pages->currentIndex() == Main_Tab_Index) {
        // Don't defeat Undo/Redo
        RegEx_Pattern_Edit->Set_PlainText("");
        Replace_Pattern_Edit->Set_PlainText("");
        Target_Text_Edit->Set_PlainText("");
    }
    else if (RegExIDE_Pages->currentIndex() == RegEx_Catalog_Tab_Index) {
        // Don't defeat Undo/Redo
        Catalog_RegEx_Pattern->Set_PlainText("");
        Catalog_Replace_Pattern->Set_PlainText("");
        Catalog_Target->Set_PlainText("");
    }
    else if (RegExIDE_Pages->currentIndex() == Apply_Tab_Index) {
        // Don't defeat Undo/Redo
        Apply_Find_Pattern->Set_PlainText("");
        Apply_Replace_Pattern->Set_PlainText("");
        Apply_Target->Set_PlainText("");
    }

    Defer_UI_Refresh = false;
    UI_Refresh();
}

void
RegularExpressionIDE::onCopyFromRegularExpressionTabClicked ( bool ) {
    if (RegEx_Valid) {
        if (RegExIDE_Pages->currentIndex() == RegEx_Catalog_Tab_Index) {
            // Don't defeat Undo/Redo
            Catalog_RegEx_Pattern->Set_PlainText(RegEx_Pattern_Edit->toPlainText());
            Catalog_Replace_Pattern->Set_PlainText(Replace_Pattern_Edit->toPlainText());
            Catalog_Target->Set_PlainText(Target_Text_Edit->toPlainText());
        }
        else if (RegExIDE_Pages->currentIndex() == Apply_Tab_Index) {
            // Don't defeat Undo/Redo
            Apply_Find_Pattern->Set_PlainText(RegEx_Pattern_Edit->toPlainText());
            Apply_Replace_Pattern->Set_PlainText(Replace_Pattern_Edit->toPlainText());
            Apply_Target_Offset = -1;
        }
    }
    else {
        // Error message
    }
}

void
RegularExpressionIDE::Demo_Initialize ( int demo_idx ) {
    Defer_UI_Refresh = true;

    // Trace fail/succeed test:
    // "(?:(?<numbers>[0-9]{3})|(?<letters>[a-z]{3})|(?<symbols>[@#$%&]{3})){3}"
    // "123abc$!%& " // (fails)
    // "123abc$%& " // (succeeds)

    if (demo_idx == 0) {
        // Don't defeat Undo/Redo
        RegEx_Pattern_Edit->selectAll();
        RegEx_Pattern_Edit->insertPlainText("(?<class>(?<!\\\\)\\[\\]?[^]]+\\])|(?<brace>(?<!\\\\)[{}])|(?<paren>(?<!\\\\)[()])");

        Target_Text_Edit->selectAll();
        Target_Text_Edit->insertPlainText("[]a] \[ [0-9] {1} (abc)");

        Replace_Pattern_Edit->selectAll();
        Replace_Pattern_Edit->insertPlainText("");
    }
    else if (demo_idx == 1) {
        // Don't defeat Undo/Redo
        RegEx_Pattern_Edit->selectAll();
        RegEx_Pattern_Edit->insertPlainText("(?:(?<numbers>[0-9]+)|(?<letters>[a-z]+)|(?<symbols>[@#$%&]+))+");

        Target_Text_Edit->selectAll();
        Target_Text_Edit->insertPlainText("123abc$%& 456def@#$ 789ghi#$% 123$%&abc 456@#$def 789#$%ghi 123abc$%& 456def@#$ 789ghi#$%");

        Replace_Pattern_Edit->selectAll();
        Replace_Pattern_Edit->insertPlainText("\\1\\3\\2");
    }
    else if (demo_idx == 2) {
        // Don't defeat Undo/Redo
        RegEx_Pattern_Edit->selectAll();
        RegEx_Pattern_Edit->insertPlainText("(?:(?<numbers>[0-9]+)|(?<letters>[a-z]+)|(?<symbols>[@#$%&]+))+");

        Target_Text_Edit->selectAll();
        Target_Text_Edit->insertPlainText("(?:(?<numbers>[0-9]+)|(?<letters>[a-z]+)|(?<symbols>[@#$%&]+))+");

        Replace_Pattern_Edit->selectAll();
        Replace_Pattern_Edit->insertPlainText("");
    }
    else if (demo_idx == 3) {
        // Don't defeat Undo/Redo
        RegEx_Pattern_Edit->selectAll();
        RegEx_Pattern_Edit->insertPlainText(Parse_RegEx_Pattern);

        Target_Text_Edit->selectAll();
        Target_Text_Edit->insertPlainText("(?:(?<numbers>[0-9]{3})|(?<letters>[a-z]{3,})|(?<symbols>[@#$%&]{3,5}))+");

        Replace_Pattern_Edit->selectAll();
        Replace_Pattern_Edit->insertPlainText("");
    }

    Defer_UI_Refresh = false;
    UI_Refresh();
}

void
RegularExpressionIDE::UI_Initialize ( ) {
    setContentsMargins(4, 0, 4, 4);

    RegExIDE_Pages = new TabWidget(this);
    RegExIDE_Pages->setContentsMargins(0, 0, 0, 0);

    QWidget* main_page = Initialize_Main_Page_UI();
    main_page->setMinimumHeight(UI_Minimum_Height);
    Main_Tab_Index = RegExIDE_Pages->addTab(main_page, tr("Regular Expression"));

    QWidget* options_reference_page = Initialize_Options_Reference_Page_UI();
    options_reference_page->setMinimumHeight(UI_Minimum_Height);
    RegExIDE_Pages->addTab(options_reference_page, tr("Options and Reference"));

    QWidget* trace_page = Initialize_Trace_Page_UI();
    trace_page->setMinimumHeight(UI_Minimum_Height);
    Trace_Tab_Index = RegExIDE_Pages->addTab(trace_page, tr("Trace"));

    QWidget* regex_catalog_page = Initialize_RegEx_Catalog_Page_UI();
    regex_catalog_page->setMinimumHeight(UI_Minimum_Height);
    RegEx_Catalog_Tab_Index = RegExIDE_Pages->addTab(regex_catalog_page, tr("RegEx Catalog"));

    QWidget* script_page = Initialize_Script_Page_UI();
    script_page->setMinimumHeight(UI_Minimum_Height);
    Script_Tab_Index = RegExIDE_Pages->addTab(script_page, tr("Script"));

    QWidget* apply_page = Initialize_Apply_Page_UI();
    apply_page->setMinimumHeight(UI_Minimum_Height);
    Apply_Tab_Index = RegExIDE_Pages->addTab(apply_page, tr("Apply"));

    QWidget* help_page = Initialize_Help_Page_UI();
    help_page->setMinimumHeight(UI_Minimum_Height);
    RegExIDE_Pages->addTab(help_page, tr("Help"));

    setCentralWidget(RegExIDE_Pages);

    connect(RegExIDE_Pages, SIGNAL(currentChanged(int)), this, SLOT(onCurrentPageChanged(int)));
}

void
RegularExpressionIDE::UI_Connect ( ) {
    connect(RegEx_Pattern_Edit, &QPlainTextEdit::textChanged, this, &RegularExpressionIDE::UI_Refresh);
    connect(Target_Text_Edit, &QPlainTextEdit::textChanged, this, &RegularExpressionIDE::UI_Refresh);
    connect(Replace_Pattern_Edit, &QPlainTextEdit::textChanged, this, &RegularExpressionIDE::UI_Refresh);

    connect(caseInsensitiveOptionCheckBox, &QCheckBox::toggled, this, &RegularExpressionIDE::UI_Refresh);
    connect(dotMatchesEverythingOptionCheckBox, &QCheckBox::toggled, this, &RegularExpressionIDE::UI_Refresh);
    connect(multilineOptionCheckBox, &QCheckBox::toggled, this, &RegularExpressionIDE::UI_Refresh);
    connect(extendedPatternSyntaxOptionCheckBox, &QCheckBox::toggled, this, &RegularExpressionIDE::UI_Refresh);
    connect(invertedGreedinessOptionCheckBox, &QCheckBox::toggled, this, &RegularExpressionIDE::UI_Refresh);
    connect(dontCaptureOptionCheckBox, &QCheckBox::toggled, this, &RegularExpressionIDE::UI_Refresh);
    connect(useUnicodePropertiesOptionCheckBox, &QCheckBox::toggled, this, &RegularExpressionIDE::UI_Refresh);
    connect(optimizeOnFirstUsageOptionCheckBox, &QCheckBox::toggled, this, &RegularExpressionIDE::UI_Refresh);
    connect(dontAutomaticallyOptimizeOptionCheckBox, &QCheckBox::toggled, this, &RegularExpressionIDE::UI_Refresh);

    connect(offsetSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &RegularExpressionIDE::UI_Refresh);

    connect(matchTypeComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &RegularExpressionIDE::UI_Refresh);

    connect(anchoredMatchOptionCheckBox, &QCheckBox::toggled, this, &RegularExpressionIDE::UI_Refresh);
    connect(dontCheckSubjectStringMatchOptionCheckBox, &QCheckBox::toggled, this, &RegularExpressionIDE::UI_Refresh);
}

void
RegularExpressionIDE::onCurrentPageChanged ( int new_current_tab_index ) {
    if ((new_current_tab_index == Trace_Tab_Index) and Trace_Dirty and RegEx_Valid) {
        const QString regex_pattern = RegEx_Pattern_Edit->toPlainText();
        const QString target_text = Target_Text_Edit->toPlainText();
        if (target_text.length() > 0) RegEx_Trace(regex_pattern, target_text);
        Trace_RegEx_Result->setFocus();
        Trace_Animation_Slider->setFocus();
    }
}

#include "RegExIDE_Main_Page.cpp"

#include "RegExIDE_Options_Reference_Page.cpp"

#include "RegExIDE_Trace_Page.cpp"

#include "RegExIDE_RegEx_Catalog_Page.cpp"

#include "RegExIDE_Script_Page.cpp"

#include "RegExIDE_Apply_Page.cpp"

QWidget*
RegularExpressionIDE::Initialize_Help_Page_UI ( ) {
    QWidget* container = new QWidget();
    container->setContentsMargins(0, 0, 0, 0);
    container->setMinimumHeight(UI_Minimum_Height);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    QScrollArea *help_scroll_area = new QScrollArea(this);
    help_scroll_area->setBackgroundRole(QPalette::Light);
    help_scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    help_scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    help_scroll_area->setWidgetResizable(true);

    RegExIDE_Help = new QLabel(help_scroll_area);
    RegExIDE_Help->setContentsMargins(8, 2, 8, 2);
    RegExIDE_Help->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    RegExIDE_Help->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    RegExIDE_Help->setWordWrap(true);
    RegExIDE_Help->setText(RegExIDE_Help_Text);

    help_scroll_area->setWidget(RegExIDE_Help);
    layout->addWidget(help_scroll_area, 100);

    container->setLayout(layout);

    return container;
}
