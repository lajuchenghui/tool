#ifndef __C_LOG_H__
#define __C_LOG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>
#include <Windows.h>
#include "ILog.h"

#define APP_VERSION "V0"

#ifndef LOG_TAG
#define LOG_TAG "null"
#endif
// option for debug level.
#define OPTION_LOG_LEVEL_CLOSE      0
#define OPTION_LOG_LEVEL_ERROR      1
#define OPTION_LOG_LEVEL_WARNING    2
#define OPTION_LOG_LEVEL_DEFAULT    3
#define OPTION_LOG_LEVEL_DETAIL     4

#define LOG_LEVEL_ERROR     "err"//error
#define LOG_LEVEL_WARNING   "war"//warning
#define LOG_LEVEL_INFO      "inf"//info
#define LOG_LEVEL_VERBOSE   "veb"//verbose
#define LOG_LEVEL_DEBUG     "dbg"//debug

#ifndef CONFIG_LOG_LEVEL
#define CONFIG_LOG_LEVEL    OPTION_LOG_LEVEL_DEFAULT
#endif

#define AWLOG(level, fmt, ...)  \
    LogRichWrite("%s: %s <%s:%u>:" fmt "\n", level, LOG_TAG, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#if CONFIG_LOG_LEVEL == OPTION_LOG_LEVEL_CLOSE

#define LOGE(fmt, ...)
#define LOGW(fmt, ...)
#define LOGI(fmt, ...)
#define LOGV(fmt, ...)

#elif CONFIG_LOG_LEVEL == OPTION_LOG_LEVEL_ERROR

#define LOGE(fmt, ...) AWLOG(LOG_LEVEL_ERROR, "\033[40;31m" fmt "\033[0m", ##__VA_ARGS__)
#define LOGW(fmt, ...)
#define LOGI(fmt, ...)
#define LOGV(fmt, ...)

#elif CONFIG_LOG_LEVEL == OPTION_LOG_LEVEL_WARNING

#define LOGE(fmt, ...) AWLOG(LOG_LEVEL_ERROR, "\033[40;31m" fmt "\033[0m", ##__VA_ARGS__)
#define LOGW(fmt, ...) AWLOG(LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...)
#define LOGV(fmt, ...)

#elif CONFIG_LOG_LEVEL == OPTION_LOG_LEVEL_DEFAULT

#define LOGE(fmt, ...) AWLOG(LOG_LEVEL_ERROR, "\033[40;31m" fmt "\033[0m", ##__VA_ARGS__)
#define LOGW(fmt, ...) AWLOG(LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) AWLOG(LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define LOGV(fmt, ...)

#elif CONFIG_LOG_LEVEL == OPTION_LOG_LEVEL_DETAIL

#define LOGE(fmt, ...) AWLOG(LOG_LEVEL_ERROR, "\033[40;31m" fmt "\033[0m", ##__VA_ARGS__)
#define LOGW(fmt, ...) AWLOG(LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) AWLOG(LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define LOGV(fmt, ...) AWLOG(LOG_LEVEL_VERBOSE, fmt, ##__VA_ARGS__)

#else
    //#error "invalid configuration of debug level."
#endif

#ifdef __cplusplus
extern "C" {
#endif

int LogOpen(const char *pFile);
void LogClose();
int LogRichWrite(const char *pFmt,...);
void LogGetPathDef(char *path);
void LogGetDir(char *str);
void LogGetDate(char* str);

#ifdef __cplusplus
}
#endif

#endif
