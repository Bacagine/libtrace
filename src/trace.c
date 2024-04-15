/**
 * trace.c: This file contains the implementation of traceger functions
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 *
 * Date: 2023-06-16
 */

#include "trace.h"

char gszTrace[256] = "";
int giDebugLevel = 1;

void vSetTraceFileName(const char *kszLogFileName) {
  snprintf(gszTrace, sizeof(gszTrace), "%s", kszLogFileName); 
}

void vSetDebugLevel(const int kiDebugLevel) {
  giDebugLevel = kiDebugLevel;
}

int iGetDebugLevel(void) {
  return giDebugLevel;
}

void _vTrace(const char *kpszModuleName,
             const int kiLine, 
             const char *kpszFmt, ...) {
  va_list args;
  FILE *fpLogFile = NULL;
  time_t tTime = time(NULL);
  struct timeval stTimeVal;
  struct tm *stTime = localtime(&tTime);
  char *pszDbg = NULL;
  pid_t iPID = getpid();
  int iReallocBuffer = 0;

  gettimeofday(&stTimeVal, NULL);
  stTime = localtime(&stTimeVal.tv_sec);

  if ( ( fpLogFile = fopen(gszTrace, "a") ) == NULL ) {
    fprintf(stderr, "E: Impossible create or open file %s!\n"
                    "%s\n", gszTrace, strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  va_start(args, kpszFmt);

  iReallocBuffer = snprintf(NULL, 0,
    "%02d/%02d/%04d %02d:%02d:%02d:%03ld %d %s:%d %s\n",
    stTime->tm_mday,
    stTime->tm_mon + 1,
    stTime->tm_year + 1900,
    stTime->tm_hour,
    stTime->tm_min,
    stTime->tm_sec,
    stTimeVal.tv_usec / 1000,
    iPID,
    kpszModuleName,
    kiLine,
    kpszFmt
  );

  pszDbg = (char *) malloc(sizeof(char) * (iReallocBuffer+1));

  if ( pszDbg == NULL ) {
    fprintf(stderr, "E: Out memory!\n");
    exit(EXIT_FAILURE);
  }

  memset(pszDbg , 0x00, iReallocBuffer+1);
  
  iReallocBuffer = snprintf(pszDbg, iReallocBuffer+1,
    "%02d/%02d/%04d %02d:%02d:%02d:%03ld %d %s:%d %s\n",
    stTime->tm_mday,
    stTime->tm_mon + 1,
    stTime->tm_year + 1900,
    stTime->tm_hour,
    stTime->tm_min,
    stTime->tm_sec,
    stTimeVal.tv_usec / 1000,
    iPID,
    kpszModuleName,
    kiLine,
    kpszFmt
  );

  vfprintf(fpLogFile, pszDbg, args);
  fflush(fpLogFile);

  free(pszDbg);
  pszDbg = NULL;

  fclose(fpLogFile);
  fpLogFile = NULL;

  va_end(args);
}

