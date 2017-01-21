TEMPLATE = lib
TARGET = pcre_rx
CONFIG += staticlib

DEFINES += PCRE_STATIC
DEFINES += PCRE_DISABLE_JIT

#CONFIG += \
#     static \
#     hide_symbols \
#     exceptions_off rtti_off warn_off

## load(qt_helper_lib)

DEFINES += HAVE_CONFIG_H

SOURCES += \
    pcre16_byte_order.c \
    pcre16_chartables.c \
    pcre16_compile.c \
    pcre16_config.c \
    pcre16_dfa_exec.c \
    pcre16_exec.c \
    pcre16_fullinfo.c \
    pcre16_get.c \
    pcre16_globals.c \
    pcre16_jit_compile.c \
    pcre16_maketables.c \
    pcre16_newline.c \
    pcre16_ord2utf16.c \
    pcre16_refcount.c \
    pcre16_string_utils.c \
    pcre16_study.c \
    pcre16_tables.c \
    pcre16_ucd.c \
    pcre16_utf16_utils.c \
    pcre16_valid_utf16.c \
    pcre16_version.c \
    pcre16_xclass.c

HEADERS += \
    config.h \
    pcre.h \
    pcre_internal.h \
    ucp.h
