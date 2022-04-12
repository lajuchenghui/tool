#include "CLog.h"

int m_nOldDay;
FILE *m_pFile = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int LogOpen(const char *pFile)
{
    int nRet = 0;

    if (!m_pFile && pFile) {
        m_pFile = fopen(pFile, "a");
        if (!m_pFile) {
            nRet = -1;
        }
    }

    return nRet;
}

void LogClose()
{
    if (m_pFile) {
        fflush(m_pFile);
        fclose(m_pFile);
        m_pFile = NULL;
    }
}

int LogRichWrite(const char *pFmt, ...)
{
    char szTime[60];
    char res[256];
    time_t t;
    struct tm *tp;

    pthread_mutex_lock(&mutex);

    memset(szTime, 0, sizeof(szTime));
    memset(res, 0, sizeof(res));
    t = time(NULL);
    tp = localtime(&t);
    if (m_nOldDay != tp->tm_mday)
    {
        char logFileName[MAX_PATH + 1] = { 0 };

        LogGetPathDef(logFileName);
        LogClose();
        LogOpen(logFileName);
        m_nOldDay = tp->tm_mday;
    }

    sprintf(szTime, "%2.2d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d",
            tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday,
            tp->tm_hour, tp->tm_min, tp->tm_sec);

    va_list args, args1;
    va_start(args, pFmt);
    va_copy(args1, args);

    va_end(args1);
    vsnprintf(res, sizeof(res), pFmt, args);
    va_end(args);

    if (m_pFile) {
        fprintf(m_pFile, "%s: %s\n", szTime, res);
        fflush(m_pFile);
    }

    fprintf(stderr, "%s: %s\n", szTime, res);
    pthread_mutex_unlock(&mutex);

    return 0;
}

/*  获取log文件名 例如返回 D:\release\2022-04-08.log  */
void LogGetPathDef(char *path)
{
    char FilePath[MAX_PATH + 1] = { 0 };
    char dateCur[MAX_PATH + 1] = { 0 };

    LogGetDir(FilePath);
    LogGetDate(dateCur);

    sprintf(path, "%s\\%s.log", FilePath, dateCur);
}

/*  获得程序目录的绝对路径名  */
void LogGetDir(char *str)
{
    GetModuleFileNameA(NULL, str, MAX_PATH);//获得整个程序路径
    (strrchr(str, '\\'))[0] = 0;//获得当前目录 因为去除了程序名
}

/*  获得当前日期 格式如 2022-04-08  */
void LogGetDate(char *srt)
{
    time_t t = time(NULL);
    struct tm* tp = localtime(&t);
    m_nOldDay = tp->tm_mday;
    sprintf(srt, "%2.2d-%2.2d-%2.2d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);
}
