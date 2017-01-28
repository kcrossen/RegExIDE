QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

QT += macextras

# QT += qml

TARGET = RegExIDE
TEMPLATE = app

HEADERS = \
    RegularExpressionIDE.h \
    PlainTextEdit.h \
    MyWidgets.h \
    OrderedVariantMap.h \
    orderedJson.h \
    RegExIDE_Regular_Expression_Reference.h \
    Preferences_JSON_Schema.h \
    RegExIDE_Help.h \
    PCRE_Trace.h \
    duk_config.h \
    duktape.h \
    RegExIDE_Copyright.h \
    RegExIDE_JavaScript_Reference.h \
    JavaScript_Editor.h

# Alternative two-step build
# HEADERS += pcre.h

SOURCES = \
    RegularExpressionIDE.cpp \
    PlainTextEdit.cpp \
    MyWidgets.cpp \
    PCRE_Trace.c \
    OrderedVariantMap.cpp \
    orderedJson.cpp \
    duktape.c \
    RegExIDE_Script_Page.cpp \
    RegExIDE_RegEx_Catalog_Page.cpp \
    RegExIDE_Trace_Page.cpp \
    RegExIDE_Options_Reference_Page.cpp \
    RegExIDE_Main_Page.cpp \
    RegExIDE_Apply_Page.cpp \
    JavaScript_Editor.cpp

# One-step build
DEFINES += PCRE_DISABLE_JIT
DEFINES += HAVE_CONFIG_H

# One-step build
SOURCES += \
    pcre/pcre16_byte_order.c \
    pcre/pcre16_chartables.c \
    pcre/pcre16_compile.c \
    pcre/pcre16_config.c \
    pcre/pcre16_dfa_exec.c \
    pcre/pcre16_exec.c \
    pcre/pcre16_fullinfo.c \
    pcre/pcre16_get.c \
    pcre/pcre16_globals.c \
    pcre/pcre16_jit_compile.c \
    pcre/pcre16_maketables.c \
    pcre/pcre16_newline.c \
    pcre/pcre16_ord2utf16.c \
    pcre/pcre16_refcount.c \
    pcre/pcre16_string_utils.c \
    pcre/pcre16_study.c \
    pcre/pcre16_tables.c \
    pcre/pcre16_ucd.c \
    pcre/pcre16_utf16_utils.c \
    pcre/pcre16_valid_utf16.c \
    pcre/pcre16_version.c \
    pcre/pcre16_xclass.c

# One-step build
HEADERS += \
    pcre/config.h \
    pcre/pcre.h \
    pcre/pcre_internal.h \
    pcre/ucp.h

# Alternative two-step build
# LIBS += libpcre_rx.a
