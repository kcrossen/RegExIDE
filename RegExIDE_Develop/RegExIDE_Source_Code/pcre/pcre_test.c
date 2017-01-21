#include <QMetaObject>
#include <QtCore>

#include <QDebug>

#include "pcre.h"

QList < QVector<int> > trace_result;
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

    QVector<int> trace;
    trace << trace_callout_block->subject_length << trace_callout_block->start_match;
    trace << trace_callout_block->current_position << trace_callout_block->capture_top;
    trace << trace_callout_block->capture_last << trace_callout_block->pattern_position;
    trace << trace_callout_block->next_item_length;
    trace_result.append(trace);

    qDebug() << "subject:" << QString::fromUtf16(trace_callout_block->subject);
    qDebug() << trace_callout_block->offset_vector[2] << trace_callout_block->offset_vector[3];

    qDebug() << "callout_number:" << trace_callout_block->callout_number
             << "subject_length:" << trace_callout_block->subject_length
             << "start_match:" << trace_callout_block->start_match
             << "current_position:" << trace_callout_block->current_position
             << "capture_top:" <<  trace_callout_block->capture_top
             << "capture_last:" << trace_callout_block->capture_last
             << "pattern_position:" << trace_callout_block->pattern_position
             << "next_item_length:" << trace_callout_block->next_item_length;


    return trace_result.count();
}

static void
Trace_Execute ( QString RegEx_Pattern,
                QString RegEx_Target ) {
    pcre16_callout = trace_callout;

    pcre16 *re;
    const char *error;
    int erroffset;

    re = pcre16_compile(RegEx_Pattern.utf16(), 0, &error, &erroffset, NULL); // PCRE_AUTO_CALLOUT

    if (not (re == NULL)) {
        int ovector[30];
        int count = pcre16_exec(re, NULL, RegEx_Target.utf16(), RegEx_Target.length(), 0, 0, ovector, 30);

        pcre16_free(re);
    }
}

int main ( int argc, char *argv[] ) {
    Trace_Execute("[abc][abc]($C1)[abc]", "abd");
}
