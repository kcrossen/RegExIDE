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

#ifndef PCRE_TRACE_H
#define PCRE_TRACE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "pcre/pcre.h"

#define max_trace_result_count 5000
#define trace_start_match 0
#define trace_current_position 1
#define trace_pattern_position 2
#define trace_next_item_length 3
#define trace_capture_top 4
#define trace_capture_last 5
#define trace_items 6
int Trace_Result[max_trace_result_count][trace_items];

bool Trace_First_Match_Only;

int
Trace_Execute ( PCRE_SPTR16 RegEx_Pattern,
                PCRE_SPTR16 RegEx_Target,
                int RegEx_Target_Length );

#ifdef	__cplusplus
}
#endif

#endif /* End of PCRE_Trace.h */
