#ifndef REGEXIDE_JAVASCRIPT_REFERENCE_H
#define REGEXIDE_JAVASCRIPT_REFERENCE_H

// Reference primitives to populate reference tree
QList <QStringList>
JavaScript_Reference ( ) {
    QList <QStringList> javascript_reference;

    javascript_reference << QStringList({"Arrays", "array.length", "Returns length of the array"});
    javascript_reference << QStringList({"Arrays", "array.toString()", "Converts an array to a string of (comma separated) array values"});
    javascript_reference << QStringList({"Arrays", "array.join(sep)", "Joins array elements into a string can specify the separator string"});
    javascript_reference << QStringList({"Arrays", "array.pop()", "Removes the last element from an array"});
    javascript_reference << QStringList({"Arrays", "array.push()", "Adds a new element to an array (at the end)"});
    javascript_reference << QStringList({"Arrays", "array.shift()", "Removes the first array element"});
    javascript_reference << QStringList({"Arrays", "array.unshift()", "Adds a new element to an array (at the beginning)"});
    javascript_reference << QStringList({"Arrays", "array.slice(from[,to])", "Extracts a part of an array and returns a new array"});
    javascript_reference << QStringList({"Arrays", "array.concat(a2[,a3...])", "Creates a new array by concatenating arrays"});
    javascript_reference << QStringList({"Arrays", "array.indexOf(value)", "Returns the position of the first found occurrence of a specified value in an array"});
    javascript_reference << QStringList({"Arrays", "array.lastIndexOf(value)", "Returns the position of the last found occurrence of a specified value in an array"});

    javascript_reference << QStringList({"Global", "eval(str)", "eval(\"2+2\") "});
    javascript_reference << QStringList({"Global", "Infinity", "if (x == NaN) "});
    javascript_reference << QStringList({"Global", "NaN", "if (x == NaN) "});
    javascript_reference << QStringList({"Global", "null", "if (x === null) "});
    javascript_reference << QStringList({"Global", "parseInt(str)", "Parses a string argument and returns an integer."});
    javascript_reference << QStringList({"Global", "parseFloat(str)", "Parses a string argument and returns a float."});
    javascript_reference << QStringList({"Global", "undefined", "if (x == undefined) "});

    javascript_reference << QStringList({"Math", "abs(x)", "Returns the absolute value of x"});
    javascript_reference << QStringList({"Math", "acos(x)", "Returns the arccosine of x, in radians"});
    javascript_reference << QStringList({"Math", "asin(x)", "Returns the arcsine of x, in radians"});
    javascript_reference << QStringList({"Math", "atan(x)", "Returns the arctangent of x as a numeric value between -PI/2 and PI/2 radians"});
    javascript_reference << QStringList({"Math", "atan2(y, x)", "Returns the arctangent of the quotient of its arguments"});
    javascript_reference << QStringList({"Math", "ceil(x)", "Returns x, rounded upwards to the nearest integer"});
    javascript_reference << QStringList({"Math", "cos(x)", "Returns the cosine of x (x is in radians)"});
    javascript_reference << QStringList({"Math", "exp(x)", "Returns the value of Ex"});
    javascript_reference << QStringList({"Math", "floor(x)", "Returns x, rounded downwards to the nearest integer"});
    javascript_reference << QStringList({"Math", "log(x)", "Returns the natural logarithm (base E) of x"});
    javascript_reference << QStringList({"Math", "max(x, y, z, ..., n)", "Returns the number with the highest value"});
    javascript_reference << QStringList({"Math", "min(x, y, z, ..., n)", "Returns the number with the lowest value"});
    javascript_reference << QStringList({"Math", "pow(x, y)", "Returns the value of x to the power of y"});
    javascript_reference << QStringList({"Math", "random()", "Returns a random number between 0 and 1"});
    javascript_reference << QStringList({"Math", "round(x)", "Rounds x to the nearest integer"});
    javascript_reference << QStringList({"Math", "sin(x)", "Returns the sine of x (x is in radians)"});
    javascript_reference << QStringList({"Math", "sqrt(x)", "Returns the square root of x"});
    javascript_reference << QStringList({"Math", "tan(x)", "Returns the tangent of an angle"});

    javascript_reference << QStringList({"Numbers", "isFinite(x)", "eturns true if its argument is a number other than NaN, Infinity, or -Infinity"});
    javascript_reference << QStringList({"Numbers", "isNaN(x)", "Returns true if its argument is NaN (not a number)"});
    javascript_reference << QStringList({"Numbers", "Number.isInteger(x)", "Returns true if its argument is an integer"});
    javascript_reference << QStringList({"Numbers", "Number.isSafeInteger(x)", "Returns true if its argument is a safe integer from -(253 - 1) inclusive to 253 - 1 inclusive"});

    javascript_reference << QStringList({"Objects", "obj.propertyName", "Access object property, get or set"});
    javascript_reference << QStringList({"Objects", "obj[\"propertyName\"]", "Access object property, get or set"});
    javascript_reference << QStringList({"Objects", "obj.methodName()", "Access object method"});
    javascript_reference << QStringList({"Objects", "obj.hasOwnProperty(propertyName)", "Returns a boolean indicating whether the object has the specified property"});
    javascript_reference << QStringList({"Objects", "Object.keys(obj)", "Returns an array containing the names of all of the given object's own enumerable properties"});
    javascript_reference << QStringList({"Objects", "Object.getOwnPropertyNames(obj)", "Returns an array of all properties (enumerable or not) found directly upon a given object"});
    javascript_reference << QStringList({"Objects", "Object.getOwnPropertyNames(obj)", "Returns an array of all properties (enumerable or not) found directly upon a given object"});

    javascript_reference << QStringList({"Operators Arithmetic", "+", "Addition: x = y + 2;"});
    javascript_reference << QStringList({"Operators Arithmetic", "-", "Subtraction: x = y - 2;"});
    javascript_reference << QStringList({"Operators Arithmetic", "*", "Multiplication: x = y * 2;"});
    javascript_reference << QStringList({"Operators Arithmetic", "/", "Division: x = y / 2;"});
    javascript_reference << QStringList({"Operators Arithmetic", "%", "Modulus (division remainder): x = y % 2;"});
    javascript_reference << QStringList({"Operators Arithmetic", "++", "Increment: x = ++y; x = y++;"});
    javascript_reference << QStringList({"Operators Arithmetic", "--", "Decrement: x = --y; x = y--;"});

    javascript_reference << QStringList({"Operators Assignment", "=", "x = y;"});
    javascript_reference << QStringList({"Operators Assignment", "+=", "x += y; same as: x = x + y;"});
    javascript_reference << QStringList({"Operators Assignment", "-=", "x -= y; same as: x = x - y;"});
    javascript_reference << QStringList({"Operators Assignment", "*=", "x *= y; same as: x = x * y;"});
    javascript_reference << QStringList({"Operators Assignment", "/=", "x /= y; same as: x = x / y;"});
    javascript_reference << QStringList({"Operators Assignment", "%=", "x %= y; same as: x = x % y;"});

    javascript_reference << QStringList({"Operators Bitwise", "&", "AND: x = 5 & 1	0101 & 0001	0001  1"});
    javascript_reference << QStringList({"Operators Bitwise", "|", "OR: x = 5 | 1	0101 | 0001	0101  5"});
    javascript_reference << QStringList({"Operators Bitwise", "~", "NOT: x = ~ 5  ~0101	1010  10"});
    javascript_reference << QStringList({"Operators Bitwise", "^", "XOR: x = 5 ^ 1	0101 ^ 0001	0100  4"});
    javascript_reference << QStringList({"Operators Bitwise", "<<", "Left shift: x = 5 << 1	0101 << 1	1010  10"});
    javascript_reference << QStringList({"Operators Bitwise", ">>", "Right shift: x = 5 >> 1	0101 >> 1	0010   2"});

    javascript_reference << QStringList({"Operators Comparison", "==", "equal to: (7 == 8) == false"});
    javascript_reference << QStringList({"Operators Comparison", "===", "equal value and equal type: (7 === \"5\") == false"});
    javascript_reference << QStringList({"Operators Comparison", "!=", "not equal: (7 != 8) == true"});
    javascript_reference << QStringList({"Operators Comparison", "!==", "not equal value or not equal type: (7 !== \"5\") == true"});
    javascript_reference << QStringList({"Operators Comparison", ">", "greater than: (7 > 8) == false"});
    javascript_reference << QStringList({"Operators Comparison", "<", "less than: (7 < 8) == true"});
    javascript_reference << QStringList({"Operators Comparison", ">=", "greater than or equal to: (7 >= 8) == false"});
    javascript_reference << QStringList({"Operators Comparison", "<=", "less than or equal to: (7 <= 8) == true"});

    javascript_reference << QStringList({"Operators Logical", "&&", "and: (x < 10 && y > 1) == true"});
    javascript_reference << QStringList({"Operators Logical", "||", "or: (x === 5 || y === 5) == false"});
    javascript_reference << QStringList({"Operators Logical", "!", "not: !(x === y) == true"});

    javascript_reference << QStringList({"Operators Miscellaneous", "typeof", "The typeof operator returns the type of a variable, object, function or expression: if (typeof x == \"number\") "});
    javascript_reference << QStringList({"Operators Miscellaneous", "(condition) ? value1:value2;", "Conditional (Ternary): (age < 18) ? \"Too young\":\"Old enough\";"});

    javascript_reference << QStringList({"Statements", "do statement while (expression)", "do {text += \"number: \" + i; i++;} while (i < 5);"});
    javascript_reference << QStringList({"Statements", "for ([init]; [test]; [next])", "for (var i = 0; i < 9; i++)"});
    javascript_reference << QStringList({"Statements", "if (expression) statement1 [else statement2]", "if (i == 0) { i += 1 } else { i += 2 }"});
    javascript_reference << QStringList({"Statements", "switch(expression) { case m: statements; break; case n: statements; break; default: statements; }", "switch (new Date().getDay()) { case 0: day = 'Sunday'; break; case 1: day = 'Monday'; break; … case 6: day = 'Saturday'; }"});
    javascript_reference << QStringList({"Statements", "var", "Declares a variable: var text = \"string\";"});
    javascript_reference << QStringList({"Statements", "while (expression) statement", "while (i < 5) {text += \"number:\" + i; i++;}"});

    javascript_reference << QStringList({"Strings", "str.length", "Returns length of the string"});
    javascript_reference << QStringList({"Strings", "str.charAt(idx)", "Returns character at the index"});
    javascript_reference << QStringList({"Strings", "str.charCodeAt(idx)", "Returns the Unicode of the character at the index"});
    javascript_reference << QStringList({"Strings", "str.concat(str1,str2,...)", "Joins two or more strings, and returns a new joined strings"});
    javascript_reference << QStringList({"Strings", "str.endsWith(str)", "Checks whether a string ends with specified string/characters"});
    javascript_reference << QStringList({"Strings", "str.fromCharCode(u1, u2,...)", "Converts Unicode values to characters"});
    javascript_reference << QStringList({"Strings", "str.includes(str)", "Checks whether a string contains the specified string/characters"});
    javascript_reference << QStringList({"Strings", "str.indexOf(str,[start])", "Returns the position of the first found occurrence of a specified value in a string"});
    javascript_reference << QStringList({"Strings", "str.lastIndexOf(str,[start])", "Returns the position of the last found occurrence of a specified value in a string"});
    javascript_reference << QStringList({"Strings", "str.localeCompare(str)", "Compares two strings in the current locale"});
    javascript_reference << QStringList({"Strings", "str.match(regexp)", "Searches a string for a match against a regular expression, and returns the matches"});
    javascript_reference << QStringList({"Strings", "parseInt(str)", "Parses a string argument and returns an integer."});
    javascript_reference << QStringList({"Strings", "parseFloat(str)", "Parses a string argument and returns a float."});
    javascript_reference << QStringList({"Strings", "str.replace(str,str)", "Searches a string for a specified value, or a regular expression, and returns a new string where the specified values are replaced"});
    javascript_reference << QStringList({"Strings", "str.replace(regexp,str)", "Searches a string for a specified value, or a regular expression, and returns a new string where the specified values are replaced"});
    javascript_reference << QStringList({"Strings", "str.replace(str,funct)", "Searches a string for a specified value, or a regular expression, and returns a new string where the specified values are replaced"});
    javascript_reference << QStringList({"Strings", "str.replace(regexp,funct)", "Searches a string for a specified value, or a regular expression, and returns a new string where the specified values are replaced"});
    javascript_reference << QStringList({"Strings", "str.search(regexp)", "Searches a string for a specified value, or regular expression, and returns the position of the match"});
    javascript_reference << QStringList({"Strings", "str.slice(from,[to])", "Extracts a part of a string and returns a new string"});
    javascript_reference << QStringList({"Strings", "str.split(str)", "Splits a string into an array of substrings"});
    javascript_reference << QStringList({"Strings", "str.split(regexp)", "Splits a string into an array of substrings"});
    javascript_reference << QStringList({"Strings", "str.startsWith(str)", "Checks whether a string begins with specified characters"});
    javascript_reference << QStringList({"Strings", "str.substr(start,[length])", "Extracts the characters from a string, beginning at a specified start position, and through the specified number of character"});
    javascript_reference << QStringList({"Strings", "str.substring(from,[to])", "Extracts the characters from a string, between two specified indices"});
    javascript_reference << QStringList({"Strings", "str.toLocaleLowerCase()", "Converts a string to lowercase letters, according to the host's locale"});
    javascript_reference << QStringList({"Strings", "str.toLocaleUpperCase()", "Converts a string to uppercase letters, according to the host's locale"});
    javascript_reference << QStringList({"Strings", "str.toLowerCase()", "Converts a string to lowercase letters"});
    javascript_reference << QStringList({"Strings", "obj.toString()", "Returns the value of a String object"});
    javascript_reference << QStringList({"Strings", "str.toUpperCase()", "Converts a string to uppercase letters"});
    javascript_reference << QStringList({"Strings", "str.trim()", "Removes whitespace from both ends of a string"});
    javascript_reference << QStringList({"Strings", "str1 + str2", "Concatenates two strings"});
    javascript_reference << QStringList({"Strings", "str1 += str2", "Concatenates two strings, same as: str1 = str1 + str2;"});

    return javascript_reference;
}

#endif // REGEXIDE_JAVASCRIPT_REFERENCE_H
