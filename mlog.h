//
// Created by Sanhu Li on 06/14/18.
//

#ifndef ACCSEQ_LOGGER_H
#define ACCSEQ_LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#define NUM_LOG_LEVELS 2
#define AS_LOG_VERBOSE  0
#define AS_LOG_ERROR    1

typedef struct timespec ts_t;
typedef struct mlog mlog;

typedef ts_t (*ml_mp_ptr)(mlog *, int, const char *, ...);
typedef ts_t (*ml_mv_ptr)(mlog *, const char *, ...);
typedef ts_t (*ml_me_ptr)(mlog *, const char *, ...);

typedef struct banner {
    char const *texts[NUM_LOG_LEVELS];
} banner;

typedef struct mlog {
    ts_t start;
    FILE *stream;
    ml_mp_ptr mprint;
    ml_mv_ptr mvlog;
    ml_me_ptr melog;
    banner b;
} mlog;

static banner new_banner();
static mlog new_mlogger(ts_t *start);

static ts_t vmprint(mlog *tthis, int l, const char *fmt, va_list args);
static ts_t mvlog(mlog *tthis, const char *fmt, ...);
static ts_t melog(mlog *tthis, const char *fmt, ...);
static ts_t mprint(mlog *tthis, int l, const char *fmt, ...);
static double time_elapse(struct timespec start);

#ifdef __cplusplus
};
#endif

mlog new_mlogger(ts_t *start) {
    mlog logger;
    logger.stream = stderr;
    if (start == NULL) {
        clock_gettime(CLOCK_MONOTONIC, &logger.start);
    } else {
        logger.start = *start;
    }
    logger.mprint = mprint;
    logger.mvlog = mvlog;
    logger.melog = melog;
    logger.b = new_banner();
    return logger;
}


ts_t mvlog(mlog *tthis, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ts_t tp = vmprint(tthis, AS_LOG_VERBOSE, fmt, args);
    va_end(args);
    return tp;
}

ts_t mprint(mlog *tthis, int l, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ts_t tp = vmprint(tthis, l, fmt, args);
    va_end(args);
    return tp;
}

ts_t vmprint(mlog *tthis, int l, const char *fmt, va_list args) {
    const char *ltext;
    const int LOG_BUF_SZ = 1024;
    switch (l) {
        case AS_LOG_VERBOSE:
            ltext = tthis->b.texts[l];
            break;
        case AS_LOG_ERROR:
            ltext = tthis->b.texts[l];
            break;
        default:
            ltext = "UNKNOWN";
            break;
    }

    ts_t tp;
    char text[LOG_BUF_SZ];
    clock_gettime(CLOCK_MONOTONIC, &tp);
    double elapsed = time_elapse(tthis->start);

    vsprintf(text, fmt, args);

    fprintf(tthis->stream, "%-7s | %11.2lf | %s\n", ltext, elapsed, text);
    return tp;
}

ts_t melog(mlog *tthis, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ts_t tp = vmprint(tthis, AS_LOG_ERROR, fmt, args);
    va_end(args);
    return tp;
}

double time_elapse(struct timespec start) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    // return now.tv_sec - start.tv_sec +
        //    (now.tv_nsec - start.tv_nsec) / 1000000000.;
    return (now.tv_sec - start.tv_sec) * 1000 + 
            (now.tv_nsec - start.tv_nsec) / 1000000.;
}

banner new_banner() {
    banner b;
    b.texts[0] = "Verbose";
    b.texts[1] = "Error";
    return b;
}

#endif //ACCSEQ_LOGGER_H
