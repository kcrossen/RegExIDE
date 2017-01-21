#ifndef REGEXIDE_REGULAR_EXPRESSION_REFERENCE_H
#define REGEXIDE_REGULAR_EXPRESSION_REFERENCE_H

// Reference primitives to populate reference tree
QList <QStringList>
Regular_Expression_Reference ( ) {
    QList <QStringList> regex_reference;

    regex_reference << QStringList({"Character Class", "Digit Character", "\\d"});
    regex_reference << QStringList({"Character Class", "Word Character", "\\w"});
    regex_reference << QStringList({"Character Class", "Whitespace Character", "\\s"});
    regex_reference << QStringList({"Character Class", "Not Digit Character", "\\D"});
    regex_reference << QStringList({"Character Class", "Not Word Character", "\\W"});
    regex_reference << QStringList({"Character Class", "Not Whitespace Character", "\\S"});
    regex_reference << QStringList({"Character Class", "Custom Character Class", "[…]"});
    regex_reference << QStringList({"Character Class", "Negated Custom Character Class", "[^…]"});

    regex_reference << QStringList({"Quantifiers", "Zero or One", "?"});
    regex_reference << QStringList({"Quantifiers", "Zero or More", "*"});
    regex_reference << QStringList({"Quantifiers", "One or More", "+"});
    regex_reference << QStringList({"Quantifiers", "nnn Times", "{nnn}"});
    regex_reference << QStringList({"Quantifiers", "nnn or More", "{nnn,}"});
    regex_reference << QStringList({"Quantifiers", "nnn to mmm Times", "{nnn,mmm}"});

    regex_reference << QStringList({"Groups & Captures", "Capturing Group", "(…)"});
    regex_reference << QStringList({"Groups & Captures", "Non-capturing Group", "(?:…)"});
    regex_reference << QStringList({"Groups & Captures", "Named Capturing Group", "(?<name>…)"});

    regex_reference << QStringList({"Lookarounds", "Positive Lookahead", "(?=…)"});
    regex_reference << QStringList({"Lookarounds", "Negative Lookahead", "(?!…)"});
    regex_reference << QStringList({"Lookarounds", "Positive Lookbehind", "(?<=…)"});
    regex_reference << QStringList({"Lookarounds", "Negative Lookbehind", "(?<!…)"});

    regex_reference << QStringList({"Zero Width Assertions", "Start of String/Line", "^"});
    regex_reference << QStringList({"Zero Width Assertions", "End of String/Line", "$"});
    regex_reference << QStringList({"Zero Width Assertions", "Start of String", "\\A"});
    regex_reference << QStringList({"Zero Width Assertions", "End of String", "\\Z"});
    regex_reference << QStringList({"Zero Width Assertions", "Word Boundary", "\\b"});
    regex_reference << QStringList({"Zero Width Assertions", "Not Word Boundary", "\\B"});

    regex_reference << QStringList({"Replacement", "Group Reference", "\\nnn"});

    regex_reference << QStringList({"Common", "Digits Group", "(\\d+)"});
    regex_reference << QStringList({"Common", "Potential Whitespace", "\\s*"});
    regex_reference << QStringList({"Common", "Quoted String (w/o quotes) Group", "((?:'[^']+')|(?:\"[^\"]+\"))"});

    return regex_reference;
}

#endif // REGEXIDE_REGULAR_EXPRESSION_REFERENCE_H
