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

#define NUM_LOG_LEVELS 2

typedef struct timespec ts_t;
typedef struct mlog mlog;

typedef ts_t (*ml_mp_ptr)(mlog *, int, const char *, ...);
typedef ts_t (*ml_mv_ptr)(mlog *, const char *, ...);
typedef ts_t (*ml_me_ptr)(mlog *, const char *, ...);

typedef struct banner {
    char *texts[NUM_LOG_LEVELS];
} banner;

typedef struct mlog {
    ts_t start;
    FILE *stream;
    ml_mp_ptr mprint;
    ml_mv_ptr mvlog;
    ml_me_ptr melog;
    banner b;
} mlog;

banner new_banner();
mlog new_mlogger(ts_t *start);

#ifdef __cplusplus
};
#endif

#endif //ACCSEQ_LOGGER_H
