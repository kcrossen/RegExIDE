# RegExIDE
### Regular Expression development environment, regex create, regex test ###
Although it only supports PCRE (8.39), it is otherwise a superset of all the RegexBuddy features I ever used before leaving Windows. For example, RegExIDE has a trace feature that allows you to watch your RegEx in action as it parses your target text. RegexBuddy (https://www.regexbuddy.com/) is Windows only.

RegExIDE goes further by supporting ordered sequences of find/replace patterns that will solve problems impossible or extremely difficult with a single find/replace pattern set. It also implements scriptable callbacks in which each found instance of the pattern is passed to your script, such that your script can compute the replacement. Scripts can solve problems that are impossible to solve with any number of regular expressions. For example, suppose that you wanted to replace some given string in your text with an increasing series of decimal numbers, i.e. transform <b>array[$0], array[$0], array[$0], ... array[$0]</b> into <b>array[0], array[1], array[2], ... array[max_n]</b>, where <b>max_n</b> is arbitrary. It works similarly to Python's <i>re.sub(pattern, repl, string)</i> where repl can be a function <i>called for every non-overlapping occurrence of pattern. The function takes a single match object argument, and returns the replacement string</i>.

Simple directions for using the application are given on the <b>Help Tab</b>, and many practical demonstration examples are built into the application itself.

![Alt text](/RegExIDE_Develop/Screenshots/RegExIDE_main_a.jpg?raw=true "Regular Expression Tab")

![Alt text](/RegExIDE_Develop/Screenshots/RegExIDE_options_a.jpg?raw=true "Options & Reference Tab")

![Alt text](/RegExIDE_Develop/Screenshots/RegExIDE_trace_a.jpg?raw=true "Trace Tab")

![Alt text](/RegExIDE_Develop/Screenshots/RegExIDE_catalog_a.jpg?raw=true "Catalog Tab")

![Alt text](/RegExIDE_Develop/Screenshots/RegExIDE_script_a.jpg?raw=true "Script Tab")

![Alt text](/RegExIDE_Develop/Screenshots/RegExIDE_apply_a.jpg?raw=true "Apply Tab")

![Alt text](/RegExIDE_Develop/Screenshots/RegExIDE_help_a.jpg?raw=true "Help Tab")

This application is built with QT Creator 4.0.1 and based on Qt 5.6.1, and provided as compiled dmg for OS-X 10.11 (probably works on earlier OS-X) and source code.

The project /RegExIDE/RegExIDE.pro will build the application over OS-X 10.11.6 (assuming Qt 5.6.1 or better SDK has been installed), but given the lack of any significant OS dependencies other than "Home" and application private settings directories, it should be easily buildable over Windows or Linux as well.

Aside from Qt, other significant contributions of open source code are: PCRE (Philip Hazel, University of Cambridge) and Duktape (Sami Vaarala, et al.).
