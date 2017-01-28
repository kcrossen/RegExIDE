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

#ifndef REGEXIDE_HELP_H
#define REGEXIDE_HELP_H

#include <QString>

QString RegExIDE_Help_Text =
    "<center><h2>RegExIDE Application</h2></center>"

    "<center><p>"
    "This software tool is based on PCRE version 8.39 (http://www.pcre.org/) "
    "with a few limitations and extensions due to the Qt 5.6 QRegularExpression 'wrapper'. "
    "</p></center>"

    "<h2>Menus</h2>"

    "<h3>RegExIDE Menu</h3>"
        "<blockquote><b>Preferences</b> "
        "Still to be done. This may take some time. "
        "</blockquote>"

    "<h3>Catalog Menu</h3>"
        "<blockquote><b>Clear</b> "
        "Clear text entries on one of three tabs <b>Regular Expression Tab</b>, <b>Apply Tab</b>, "
        "or <b>Catalog Tab</b>. "
        "</blockquote>"

        "<blockquote><b>categories</b> "
        "These are stored RegEx 'formulas', organized by category. Click on a RegEx 'formula' to transfer 'formula' "
        "to the text entries one of three tabs <b>Regular Expression Tab</b>, <b>Apply Tab</b>, "
        "or <b>Catalog Tab</b>. In the case of the <b>Catalog Tab</b>, the transferred 'formula' "
        "would probably be modified to create a new 'formula'. "
        "</blockquote>"

    "<h2>Regular Expression Tab</h2>"

    "<h3>Find pattern</h3>"
    "<p><b>Entering and editing regular expression pattern</b> "
    "The regular expression to test may be entered here. This text entry area responds to undo/redo and "
    "also highlights matching left/right parentheses. "
    "When the items in <b>RegEx capturing groups</b> or <b>RegEx pattern elements</b> are selected, "
    "the corresponding regular expression pattern elements are highlighted here. </p>"

        "<blockquote><b>Copy escaped</b> "
        "Copies <b>RegEx pattern</b> to the clipboard as it would have to be rendered in C or C++ source code. "
        "For example, <i>(?&lt;number&gt;\\d+)</i> would be rendered as <i>\"(?&lt;number&gt;\\\\d+)\"</i>. </blockquote>"

        "<blockquote><b>Status:</b> "
        "Will be 'Valid' unless there is an error in the <b>RegEx pattern</b>, in which case the "
        "<b>RegEx pattern</b> text will be rendered in red and an error message will be displayed here. </blockquote>"

    "<h3>Target text</h3>"
    "<p>"
    "The text that in whole or in part, the <b>RegEx pattern</b> is supposed to match. </p>"

    "<h3>Replace pattern, Replace pattern result</h3>"
    "<p>"
    "A replacement pattern may also be specified in which matched groups from <b>Target text</b> may be rearranged or "
    "interspersed with other text. For example, the regular expression pattern "
    "<i>(?:(?&lt;numbers&gt;[0-9]+)|(?&lt;letters&gt;[a-z]+)|(?&lt;symbols&gt;[@#$%&]+))+</i> would match "
    "<nobr>'<i>123abc$%&</i>'</nobr> and the replacement pattern <nobr>'<i>~\\1\\3\\2~</i>'</nobr> would yield "
    "<nobr>'<i>~123$%&abc~</i>'</nobr> as the <b>Replace pattern result</b>. </p>"

        "<blockquote><b>Copy escaped</b> "
        "Copies <b>Replace pattern</b> to the clipboard as it would have to be rendered in C or C++ source code. "
        "For example, <i>~\\1\\3\\2~</i> would be rendered as <i>\"~\\\\1\\\\3\\\\2~\"</i>. </blockquote>"

    "<h3>RegEx capturing groups</h3>"
    "<p>"
    "The capturing groups in the <b>RegEx pattern</b>. "
    "Click on a listed group in <b>RegEx capturing groups</b> to highlight in green "
    "the text representing the group in <b>RegEx pattern</b>. "
    "Note that these are the only elements that may be used in <b>Replace pattern</b>. </p>"

    "<h3>RegEx pattern elements</h3>"
    "<p>"
    "An analysis of <b>RegEx pattern</b>, identifying the pattern's component regular expression elements. "
    "Click on an element in <b>RegEx pattern elements</b> to highlight in green "
    "the text representing the element in <b>RegEx pattern</b>. </p>"

    "<h3>RegEx matches</h3>"
    "<p>"
    "The <b>RegEx pattern</b> matches in <b>Target text</b> are analyzed in detail and each detail is highlighted "
    "in <b>Target text</b> using the corresponding color. </p>"

    "<h2>Options and Reference Tab</h2>"

    "<h3>Pattern options</h3>"

    "<p><b>CaseInsensitiveOption</b> "
    "The pattern should match against the subject string in a case insensitive way. "
    "This option corresponds to the /i modifier in Perl regular expressions. </p>"
    "<p><b>DotMatchesEverythingOption</b> "
    "The dot metacharacter (.) in the pattern string is allowed to match any character in the subject string, "
    "including newlines (normally, the dot does not match newlines). "
    "This option corresponds to the /s modifier in Perl regular expressions. </p>"
    "<p><b>MultilineOption</b> "
    "The caret (^) and the dollar ($) metacharacters in the pattern string are allowed to match, respectively, "
    "immediately after and immediately before any newline in the subject string, "
    "as well as at the very beginning and at the very end of the subject string. "
    "This option corresponds to the /m modifier in Perl regular expressions. </p>"
    "<p><b>ExtendedPatternSyntaxOption</b> "
    "Any whitespace in the pattern string which is not escaped and outside a character class is ignored. "
    "Moreover, an unescaped sharp (#) outside a character class causes all the following characters, "
    "until the first newline (included), to be ignored. "
    "This can be used to increase the readability of a pattern string as well as put comments inside regular expressions; "
    "this is particulary useful if the pattern string is loaded from a file or written by the user, "
    "because in C++ code it is always possible to use the rules for string literals to put comments outside the pattern string. "
    "This option corresponds to the /x modifier in Perl regular expressions. </p>"
    "<p><b>InvertedGreedinessOption</b> "
    "The greediness of the quantifiers is inverted: *, +, ?, {m,n}, etc. become lazy, "
    "while their lazy versions (*?, +?, ??, {m,n}?, etc.) become greedy. "
    "There is no equivalent for this option in Perl regular expressions. </p>"
    "<p><b>DontCaptureOption</b> "
    "The non-named capturing groups do not capture substrings; named capturing groups still work as intended, "
    "as well as the implicit capturing group number 0 corresponding to the entire match. "
    "There is no equivalent for this option in Perl regular expressions. </p>"
    "<p><b>UseUnicodePropertiesOption</b> "
    "The meaning of the \\w, \\d, etc., character classes, as well as the meaning of their counterparts (\\W, \\D, etc.), "
    "is changed from matching ASCII characters only to matching any character with the corresponding Unicode property. "
    "For instance, \\d is changed to match any character with the Unicode Nd (decimal digit) property; "
    "\\w to match any character with either the Unicode L (letter) or N (digit) property, plus underscore, and so on. "
    "This option corresponds to the /u modifier in Perl regular expressions. </p>"
    "<p><b>OptimizeOnFirstUsageOption</b> "
    "The regular expression will be optimized (and possibly JIT-compiled) on its first usage, "
    "instead of after a certain (undefined) number of usages. See also optimize(). </p>"
    "<p><b>DontAutomaticallyOptimizeOption</b> "
    "Regular expressions are automatically optimized after a certain number of usages; "
    "setting this option prevents such optimizations, therefore avoiding possible unpredictable spikes in CPU and memory usage. "
    "If both this option and the OptimizeOnFirstUsageOption option are set, then this option takes precedence. "
    "Note: this option will still let the regular expression to be optimized by manually calling optimize(). </p>"

    "<h3>Match options</h3>"

    "<p><b>Offset:</b> "
    "Start match attempt at the position <i>offset</i> inside <b>Target text</b>. "
    "In effect, the first <i>offset</i> characters of <b>Target text</b> are ignored. </p>"
    "<p><b>AnchoredMatchOption</b> "
    "The match is constrained to start exactly at the offset passed to match() in order to be successful, "
    "even if the pattern string does not contain any metacharacter that anchors the match at that point. </p>"

    "<p><b>Match Type</b></p>"
        "<blockquote><b>NormalMatch</b> "
        "A normal match is done. </blockquote>"
        "<blockquote><b>PartialPreferCompleteMatch</b> "
        "The pattern string is matched partially against the subject string. If a partial match is found, "
        "then it is recorded, and other matching alternatives are tried as usual. "
        "If a complete match is then found, then it's preferred to the partial match; "
        "in this case only the complete match is reported. "
        "If instead no complete match is found (but only the partial one), "
        "then the partial one is reported. </blockquote>"
        "<blockquote><b>PartialPreferFirstMatch</b> "
        "The pattern string is matched partially against the subject string. If a partial match is found, "
        "then matching stops and the partial match is reported. In this case, other matching alternatives "
        "(potentially leading to a complete match) are not tried. "
        "Moreover, this match type assumes that the subject string only a substring of a larger text, "
        "and that (in this text) there are other characters beyond the end of the subject string. </blockquote>"
        "<blockquote><b>NoMatch</b> "
        "No matching is done. Using this match type is not very useful for the user, as no matching ever happens. </blockquote>"

    "<p><b>DontCheckSubjectStringMatchOption</b> "
    "The subject string is not checked for UTF-16 validity before attempting a match. Use this option with extreme caution, "
    "as attempting to match an invalid string may crash the program and/or constitute a security issue. </p>"

    "<h3>RegEx reference</h3>"
    "<p>Note: In the following, <i>ellipsis</i> refers to the single character '…'.</p>"
    "<p><b>Copy (Click)</b> "
    "The text of the regular expression element will be copied to the clipboard, including any <i>ellipsis</i>. "
    "Subsequent pastes from clipboard will paste the <i>ellipsis</i>, leaving it to be replaced manually."
    "</p>"
    "<p><b>Paste (⌘-Click)</b> "
    "The text of the regular expression element will be pasted into the current RegEx Pattern at the cursor position. "
    "If any text in the current RegEx Pattern is selected, and the regular expression element contains an <i>ellipsis</i>, "
    "the <i>ellipsis</i> will be replaced by the selected text, "
    "and the result will replace the selected text in the current RegEx Pattern. "
    "</p>"
    "<p>"
    "For example, the regular expression element representing a named capture group is <i>(?&lt;name&gt;…)</i>, "
    "where <i>name</i> is the name given by the programmer to identify that capture group. "
    "The <i>ellipsis</i> in <i>(?&lt;name&gt;…)</i> would be replaced by whatever regular expression elements would "
    "capture the desired text, e.g. <i>(?&lt;number&gt;/b[0-9]+/b)</i> would capture a decimal integer. "
    "</p>"

    "<h2>Trace Tab</h2>"
    "<p>"
    "Trace is a visual representation of the steps being taken by RegEx to match the target with the pattern. "
    "Each pair if color coded lines of text represent a single step in the matching process. "
    "For each step, the upper, blue highlighted, line in each pair highlights the current matching element. "
    "The lower, green highlighted, line in each pair highlights the currently matched target text, and in brighter green, "
    "the next target text character to be matched (or not)."
    "</p>"
    "<p>"
    "Trace is available as a step-by-step 'animated' sequence (above) or as a static listing of all of the steps (below). "
    "The key parts of the pattern (currently active pattern element in blue) and the target (currently matched text plus "
    "the next character to process in green) are aligned so that both can be seen together in context. "
    "The 'animated' sequence is driven by the slider above the 'animated' display, and when that slider has focus, "
    "by the keyboard left arrow and right arrow keys. "
    "</p>"
        "<blockquote><b>Trace All Matches</b> "
        "Normally, tracing stops after the first match is found. If there are more match instances to be found "
        "or there is a matching error after the first match, "
        "this will force trace to take as many trace steps as <b>Target text</b> makes possible. "
        "</blockquote>"

    "<h2>Catalog Tab</h2>"
    "<p>"
    "Once a regular expression and replace pattern have been tested on the <b>Regular Expression Tab</b>, they "
    "may be stored for repeated recall using the <b>Catalog Tab</b>. The <b>Catalog</b> becomes "
    "a library of frequently used find/replace patterns or series of find/replace patterns. "
    "</p>"
        "<blockquote><b>Save</b> "
        "Save the catalog as part of the initialization file. "
        "</blockquote>"

        "<blockquote><b>Open...</b> "
        "Retrieve the catalog from an initialization file that you have previously specified in a <b>Save As...</b>. "
        "</blockquote>"

        "<blockquote><b>Save As...</b> "
        "Save the catalog as part of an initialization file that you specify. "
        "</blockquote>"

        "<blockquote><b>Delete</b> "
        "Delete the selected item. "
        "</blockquote>"

        "<blockquote><b>Move Up</b> "
        "Move the selected item up in the order of its siblings, i.e before the item immediately above. "
        "</blockquote>"

        "<blockquote><b>Move Down</b> "
        "Move the selected item down in the order of its siblings, i.e after the item immediately below. "
        "</blockquote>"

    "<h3>Catalog Entry Editor</h3>"
    "<p>"
    "Edit existing or create new catalog entries. "
    "</p>"

        "<blockquote><b>Series</b> "
        "If this catalog entry is part of a series of steps, enter that series name here. "
        "</blockquote>"

        "<blockquote><b>Series Index</b> "
        "If this catalog entry is part of a series as a step, enter the order of this entry step here. "
        "The indexes do not have to be sequential (so 10, 20, 30, etc. is acceptable), but the series entries "
        " in this <b>Series</b> will be applied in the numerical order of <b>Series Index</b> values. "
        "</blockquote>"

        "<blockquote><b>Series Help</b> "
        "Text that will be displayed as help or explaination for this series step. "
        "</blockquote>"

        "<blockquote><b>Before Replace</b>, <b>After Replace</b> "
        "Before the replace operation or after the replace operation, one of the following actions will be automatically"
        "taken, <i>Target_From_Clipboard, Target_From_Memory, Target_Swap_Memory, Target_To_Replace, Target_To_Memory, "
        "Target_To_Clipboard</i>. <i>Memory</i> refers to an internal buffer where the <b>Target</b> text may be "
        "temporarily stored until needed. "
        "</blockquote>"

        "<blockquote><b>Category</b> "
        "Categories collect catalog entries into related groups, making individual entries easier to find. "
        "</blockquote>"

        "<blockquote><b>RegEx Name</b> "
        "The name assigned to this find/replace pattern pair. "
        "</blockquote>"

        "<blockquote><b>Find pattern</b> "
        "The regular expression pattern used to locate specific instances of text in <b>Target</b>. "
        "</blockquote>"

        "<blockquote><b>Replace pattern</b> "
        "A replacement pattern may also be specified in which matched instances from <b>Target</b> may be rearranged or "
        "interspersed with other text. "
        "</blockquote>"

        "<blockquote><b>Scripted (replace pattern)</b> "
        "This tells the catalog that the displayed <b>Replace pattern</b> is a script, see <b>Script Tab</b> below. "
        "</blockquote>"

        "<blockquote><b>Replace pattern specified</b> "
        "If the <b>Replace pattern</b> is empty, this tells the catalog that the empty <b>Replace pattern</b> should "
        "be stored anyway. For example, you want to remove instances found by the <b>Find pattern</b> from "
        "the <b>Target</b> completely, in other words, replace them with nothing. "
        "</blockquote>"

        "<blockquote><b>Target</b> "
        "Normally this would be empty, but as a demonstration for example, you may wish to store an example target text. "
        "</blockquote>"

        "<blockquote><b>Target specified</b> "
        "If the <b>Target</b> is empty, this tells the catalog that the empty <b>Target</b> should "
        "be stored anyway. Normally this would be true, but as a demonstration for example, you may wish to "
        "store an example target text. "
        "</blockquote>"

        "<blockquote><b>Add New RegEx</b> "
        "The editing changes applied in the <b>Catalog Entry Editor</b> will be saved as a new catalog entry. "
        "</blockquote>"

        "<blockquote><b>Update RegEx</b> "
        "The editing changes applied in the <b>Catalog Entry Editor</b> will be used to update the current "
        "catalog entry. "
        "</blockquote>"

        "<blockquote><b>Copy from Regular Expression Tab</b> "
        "Copy entries for <b>RegEx Pattern</b>, <b>Replace Pattern</b>, and <b>Target</b> from <b>Regular Expression Tab</b>. "
        "</blockquote>"

    "<h2>Script Tab</h2>"
    "<p>"
    "Test scripts for use in the <b>Catalog</b>. To the right of the <b>Script</b> page there is a splitter "
    "which, when double-clicked, will display a JavaScript reference cheat-sheet. Double-clicking the reference area "
    "again will hide the reference. When the reference is displayed, clicking an item will copy that item "
    "to the clipboard and ⌘-clicking an item will paste that item into the <b>Script Editor</b>. "
    "</p>"
    "<p>"
    "Scripts cover situations in which regular expression are incapable of transforming the original text into "
    "the desired final form. For an example from SQL, transforming "
        "<blockquote><i>INSERT INTO `photo`<br>"
        "         (`id`, `width`, `height`, `bytes`, `url`, `server`, `web_path`, <br>"
        "          `creation_date`, `is_orphan`, `is_local`, `local_date`, `type`) <br>"
        "VALUES</i></blockquote>"
    "into "
        "<blockquote><i>UPDATE `photo`<br>"
        "SET `width` = \\2,<br>"
        " `height` = \\3,<br>"
        " `bytes` = \\4,<br>"
        " `url` = \\5,<br>"
        " `server` = \\6,<br>"
        " `web_path` = \\7,<br>"
        " `creation_date` = \\8,<br>"
        " `is_orphan` = \\9,<br>"
        " `is_local` = \\10,<br>"
        " `local_date` = \\11,<br>"
        " `type` = \\12<br>"
        "WHERE (`id` = \\1);</i></blockquote>"
    "is impossible with regular expressions alone without knowing the length of the SQL table "
    "(<i>photo</i> in this case) column list. "
    "Moreover a separate find/replace pattern would have to be constructed for every such column list length."
    "</p>"
    "<p>"
    "With a single series of steps consisting of find/replace patterns and one script, "
    "this situation can be solved for all column list lengths. To see how this works, select the series "
    "<i>INSERT to UPDATE</i> on the <b>Apply Tab</b> and click the <b>Start Series</b> button. "
    "Then click the button <b>Replace, Next Step</b> repeatedly. "
    "</p>"

    "<h3>Find pattern</h3>"
    "<p>"
    "Optional but if specified, enter the text in which <b>Find pattern</b> will search for a match in "
    "<b>Target or Matched text</b>. This simulates the conditions under which your script will operate "
    "when used on the <b>Apply Tab</b>. "
    "</p>"

    "<h3>Target or Matched text</h3>"
    "<p>"
    "Enter text which will be returned by a RegEx match, or if a <b>Find pattern</b> is specified, enter "
    "the text in which <b>Find pattern</b> will search for a match. "
    "</p>"

    "<h3>Script Editor</h3>"
    "<p>"
    "Create or edit and test a JavaScript script to transform <b>Match Text</b> into <b>Replace Text</b>. "
    "Your script must begin with <b>function replace_function(match) {</b> and end with <b>}</b>. "
    "Argument 'match' has at least one property, match_obj.group_0 or match_obj['0'], which captures the entire string "
    "found by <b>Find pattern</b>. If there are any captures in <b>Find pattern</b>, for example "
    "'\\$(?&lt;initial&gt;\\d+)', these captures, if any, will be in properties match_obj.group_1 or match_obj['1'] "
    "and match_obj.group_initial or match_obj.initial. "
    "Your script must also <b>return</b> return_value<b>;</b>, where return_value is the <b>Replace Text</b> "
    "corresponding to the argument 'match'. Run the examples supplied by the <b>Script Tab</b> to see how "
    "this works, using the print() statements to show what's happening in your script. "
    "</p>"

        "<blockquote><b>Keyboard Tab</b> "
        "Shift selected text block left 4 spaces. "
        "</blockquote>"

        "<blockquote><b>Keyboard ⌘[</b> "
        "Shift selected text block left 2 spaces. "
        "</blockquote>"

        "<blockquote><b>Keyboard ⌘⇧[</b> "
        "Shift selected text block left 1 space. "
        "</blockquote>"

        "<blockquote><b>Keyboard ⌘]</b> "
        "Shift selected text block right 2 spaces. "
        "</blockquote>"

        "<blockquote><b>Keyboard ⌘⇧]</b> "
        "Shift selected text block right 1 space. "
        "</blockquote>"

        "<blockquote><b>Keyboard ⌘=</b> "
        "Reformat selected text block. "
        "</blockquote>"

        "<blockquote><b>Keyboard {, [, (, \", \' with selected text</b> "
        "The selected text will be enclosed by {}, [], (), \"\", or \'\', respectively. "
        "</blockquote>"

        "<blockquote><b>Example Script</b> "
        "Example scripts to demonstrate scripting techniques and JavaScript features. "
        "</blockquote>"

        "<blockquote><b>Reset Script</b> "
        "Reinitialize the script. "
        "</blockquote>"

        "<blockquote><b>Run Script</b> "
        "Run the script to generate <b>Replace Text</b> from <b>Match Text</b>. "
        "</blockquote>"

    "<h3>Replace Text</h3>"
    "<p>"
    "The text computed by your script corresponding to <b>Match Text</b>. "
    "</p>"

    "<h3>Script Debug and Error Messages</h3>"
    "<p>"
    "Any text from <b>print</b> statements or JavaScript error messages. "
    "</p>"

    "<h2>Apply Tab</h2>"
    "<p>"
    "Once a regular expression and replace pattern have been tested on the <b>Regular Expression Tab</b>, "
    "and perhaps stored for repeated recall using the <b>Catalog Tab</b>, "
    "use the <b>Apply Tab</b> to run large-scale find/replace operations. "
    "</p>"

    "<h3>Series</h3>"
    "<p>"
    "A series is an ordered collection of individual find/replace steps that transforms the original <b>Target</b> text "
    "into the desired end form. Series would typically be applied to situations in which it's difficult or impossible "
    "to transform the original text into the desired form with a single find/replace step. In the event that a single "
    "find/replace step will work, choose that find/replace pattern from the <b>RegExCatalog</b> menu. "
    "</p>"

        "<blockquote><b>Start Series</b> "
        "After choosing a series from the list to the left, click this button to load the first step of the chosen series. "
        "</blockquote>"

        "<blockquote><b>Replace</b> "
        "Replace all instances of <b>Find pattern</b> in <b>Target</b> according to <b>Replace pattern</b>. "
        "</blockquote>"

        "<blockquote><b>Next Step</b> "
        "Go to next step in this series. "
        "</blockquote>"

        "<blockquote><b>Replace, Next Step</b> "
        "Replace all instances of <b>Find pattern</b> in <b>Target</b> according to <b>Replace pattern</b>, "
        "then go to next step in this series. "
        "</blockquote>"

    "<h3>Find pattern, Replace pattern, and Target</h3>"
    "<p>"
    "In the event that a single find/replace step will transform your original text into final form, "
    "choose that find/replace pattern from the <b>RegExCatalog</b> menu to initialize "
    "<b>Find pattern</b> and <b>Replace pattern</b>. <b>Target</b> would then typically be initialized with "
    "the original text to be transformed either from the clipboard or from a file. "
    "</p>"

        "<blockquote><b>Copy from Regular Expression Tab</b> "
        "Copy entries for <b>Find pattern</b> and <b>Replace pattern</b> from <b>Regular Expression Tab</b>. "
        "</blockquote>"

        "<blockquote><b>Scripted (Replace pattern)</b> "
        "This indicates that the displayed <b>Replace pattern</b> is a script, see <b>Script Tab</b> above. "
        "</blockquote>"

        "<blockquote><b>From File</b> "
        "Load file into <b>Target</b>. "
        "</blockquote>"

        "<blockquote><b>From Clipboard</b> "
        "Copy contents of clipboard into <b>Target</b>. "
        "</blockquote>"

        "<blockquote><b>From Memory</b> "
        "Copy contents of RegExIDE memory buffer into <b>Target</b>. "
        "</blockquote>"

        "<blockquote><b>Find Next</b> "
        "Find next instance of <b>Find pattern</b> in <b>Target</b>. "
        "</blockquote>"

        "<blockquote><b>Replace & Find Next</b> "
        "Replace current instance of <b>Find pattern</b> in <b>Target</b> according to <b>Replace pattern</b>, "
        "then find next instance of <b>Find pattern</b> in <b>Target</b>. "
        "</blockquote>"

        "<blockquote><b>Replace All</b> "
        "Replace all instances of <b>Find pattern</b> in <b>Target</b> according to <b>Replace pattern</b>. "
        "</blockquote>"

        "<blockquote><b>To Replace</b> "
        "Copy contents of <b>Target</b> to <b>Replace pattern</b>. This feature can be used after a <b>Replace pattern</b> "
        "has been built using RegExIDE. "
        "</blockquote>"

        "<blockquote><b>To Memory</b> "
        "Copy contents of <b>Target</b> to RegExIDE memory buffer. "
        "</blockquote>"

        "<blockquote><b>To Clipboard</b> "
        "Copy contents of <b>Target</b> to clipboard. "
        "</blockquote>"

        "<blockquote><b>To File</b> "
        "Save contents of <b>Target</b> to file. "
        "</blockquote>"
    ;

#endif // REGEXIDE_HELP_H
