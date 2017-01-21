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

#include "PCRE_Trace.h"

#define callout_fail_id -1
int trace_result_count;
int trace_last_current_position;

static int trace_callout ( pcre16_callout_block *trace_callout_block ) {
//    typedef struct pcre_callout_block {
//      int          version;           /* Identifies version of block */
//      /* ------------------------ Version 0 ------------------------------- */
//      int          callout_number;    /* Number compiled into pattern */
//      int         *offset_vector;     /* The offset vector */
//      PCRE_SPTR    subject;           /* The subject being matched */
//      int          subject_length;    /* The length of the subject */
//      int          start_match;       /* Offset to start of this match attempt */
//      int          current_position;  /* Where we currently are in the subject */
//      int          capture_top;       /* Max current capture */
//      int          capture_last;      /* Most recently closed capture */
//      void        *callout_data;      /* Data passed in with the call */
//      /* ------------------- Added for Version 1 -------------------------- */
//      int          pattern_position;  /* Offset to next item in the pattern */
//      int          next_item_length;  /* Length of next item in the pattern */
//      /* ------------------- Added for Version 2 -------------------------- */
//      const unsigned char *mark;      /* Pointer to current mark or NULL    */
//      /* ------------------------------------------------------------------ */
//    } pcre_callout_block;

    // Use this to check whether callout failed
    int callout_number = trace_callout_block->callout_number;

    Trace_Result[trace_result_count][trace_start_match] = trace_callout_block->start_match;
    Trace_Result[trace_result_count][trace_current_position] = trace_callout_block->current_position;
    Trace_Result[trace_result_count][trace_pattern_position] = trace_callout_block->pattern_position;
    Trace_Result[trace_result_count][trace_next_item_length] = trace_callout_block->next_item_length;
    Trace_Result[trace_result_count][trace_capture_top] = trace_callout_block->capture_top;
    Trace_Result[trace_result_count][trace_capture_last] = trace_callout_block->capture_last;
    trace_result_count += 1;
    trace_last_current_position = trace_callout_block->current_position;

    // Ensure no buffer overrun
    if ((callout_number != callout_fail_id) &&
        (trace_result_count < (max_trace_result_count - 2)))
        return 0;
    else return 1;
}

int
Trace_Execute ( PCRE_SPTR16 RegEx_Pattern,
                PCRE_SPTR16 RegEx_Target,
                int RegEx_Target_Length ) {
    pcre16_callout = trace_callout;
    trace_result_count = 0;

    pcre16 *re;
    const char *error;
    int erroffset;

    re = pcre16_compile(RegEx_Pattern, (PCRE_MULTILINE | PCRE_AUTO_CALLOUT), &error, &erroffset, NULL); // PCRE_AUTO_CALLOUT

    if (re != NULL) {
        int count = 0;
        int trace_start_offset = 0;
        trace_last_current_position = 0;
        int ovector[30];
        while (trace_last_current_position < RegEx_Target_Length) {
            count = pcre16_exec(re, NULL, RegEx_Target, RegEx_Target_Length, trace_start_offset, 0, ovector, 30);
            // Returns:
            // >  0 => success; value is the number of elements filled in
            // =  0 => success, but offsets is not big enough
            // = -1 => failed to match
            // < -1 => some kind of unexpected problem
            if (count < 0) break;
            if (Trace_First_Match_Only) break;
            trace_start_offset = trace_last_current_position;
        }

        if (count < 0) {
            // Failed somehow
        }

        pcre16_free(re);
    }

    return trace_result_count;
}
