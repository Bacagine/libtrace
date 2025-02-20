/**
 * trace.c
 * 
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com> in February 2025
 * 
 * Description: Debug module
 * 
 * Date: 20/02/2025
 */

#include "trace.h"

STRUCT_TRACE_PRM gstTracePrm = { 0 };

void vSetTraceFile(const char *kpszTrace) {
  snprintf(gstTracePrm.szTrace, sizeof(gstTracePrm.szTrace), "%s", kpszTrace);
}

void vSetDebugLevel(const char *kpszDebugLevel) {
  snprintf(gstTracePrm.szDebugLevel, sizeof(gstTracePrm.szDebugLevel), "%s", kpszDebugLevel);
}

void vSetLogOnTerminal(const bool kbLogOnTerminal) {
  gstTracePrm.bLogInTerminal = kbLogOnTerminal;
}

void vSetRotateLog(const bool kbRotateLog) {
  gstTracePrm.bRotateLog = kbRotateLog;
}

void vSetMaxLogSize(const long long kllMaxLogSize) {
  gstTracePrm.llMaxLogSize = kllMaxLogSize;
}

void _vInitTrace(const char *kpszTrace, const char *kpszDebugLevel, const bool kbLogOnTerminal, const bool kbRotateLog, const long long kllMaxLogSize) {
  vSetTraceFile(kpszTrace);
  vSetDebugLevel(kpszDebugLevel);
  vSetLogOnTerminal(kbLogOnTerminal);
  vSetRotateLog(kbRotateLog);
  vSetMaxLogSize(kllMaxLogSize);
}

void vRotateLog(void) {
  FILE *fpFile = NULL;
  struct tm *pstToday = NULL;
  time_t lSeconds;
  long long llFileSize = 0;
  gzFile gzFile = NULL;
  char szGZipedLog[1024] = "";
  char szBaseName[512] = "";
  char *pDot = NULL;
  char szBuffer[4096];
  int iBytesRead = 0;
  bool bCompactError = false;
  
  memset(szGZipedLog, 0x00, sizeof(szGZipedLog));
  memset(szBaseName , 0x00, sizeof(szBaseName ));
  memset(szBuffer   , 0x00, sizeof(szBuffer   ));
  
  if ( gstTracePrm.llMaxLogSize < 1 ) return;
  
  time(&lSeconds);
  pstToday = localtime(&lSeconds);
  
  if ( (fpFile = fopen(gstTracePrm.szTrace, "rb")) == NULL )
    return;

  fseek(fpFile, 0, SEEK_END);
  llFileSize = ftell(fpFile);
  
  if ( llFileSize < gstTracePrm.llMaxLogSize ) {
    fclose(fpFile);
    fpFile = NULL;
    return;
  }
  
  if ( (pDot = strrchr(gstTracePrm.szTrace, '.')) == NULL ) {
    strncpy(szBaseName, gstTracePrm.szTrace, sizeof(szBaseName) - 1);
  }
  else {
    strncpy(szBaseName, gstTracePrm.szTrace, pDot - gstTracePrm.szTrace);
    szBaseName[pDot - gstTracePrm.szTrace] = '\0';
  }

  snprintf(
    szGZipedLog,
    sizeof(szGZipedLog),
    "%s-%02d%02d%04d%02d%02d%02d.log.gz",
    szBaseName,
    pstToday->tm_mday,
    pstToday->tm_mon + 1,
    pstToday->tm_year + 1900,
    pstToday->tm_hour,
    pstToday->tm_min,
    pstToday->tm_sec
  );
  
  if ( (gzFile = gzopen(szGZipedLog, "wb")) == NULL ) {
    fclose(fpFile);
    fpFile = NULL;
    return;
  }
  
  while ( (iBytesRead = fread(szBuffer, 1, sizeof(szBuffer), fpFile)) > 0 ) {
    if ( gzwrite(gzFile, szBuffer, iBytesRead) != iBytesRead ) {
      bCompactError = true;
      break;
    }
  }
  
  gzclose(gzFile);
  gzFile = NULL;
  
  fclose(fpFile);
  fpFile = NULL;
  
  if ( !bCompactError ) remove(gstTracePrm.szTrace);
}

void _vTrace(const char *kpszModule, const int kiLine, const char *kpszFunction, const char *kpszFmt, ...) {
  va_list ap;
  FILE *fpFile = NULL;
  char *pszDbg = NULL;
  int iBufferSize = 0;
  time_t tSeconds = 0;
  struct tm *pstToday = NULL;
  
  if ( (fpFile = fopen(gstTracePrm.szTrace, "a")) == NULL ) {
    fprintf(stderr, "E: impossible open the file [%s] %s!", gstTracePrm.szTrace, strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  tSeconds = time(NULL);
  pstToday = localtime(&tSeconds);
  
  va_start(ap, kpszFmt);
  
  iBufferSize = snprintf(
    NULL,
    0,
    "%02d/%02d/%04d %02d:%02d:%02d [%s:%i] %s - %s\n",
    pstToday->tm_mday,
    pstToday->tm_mon + 1,
    pstToday->tm_year + 1900,
    pstToday->tm_hour,
    pstToday->tm_min,
    pstToday->tm_sec,
    kpszModule,
    kiLine,
    kpszFunction,
    kpszFmt
  )+1;
  pszDbg = (char *) malloc(sizeof(char) * iBufferSize);
  snprintf(
    pszDbg,
    iBufferSize,
    "%02d/%02d/%04d %02d:%02d:%02d [%s:%i] %s - %s\n",
    pstToday->tm_mday,
    pstToday->tm_mon + 1,
    pstToday->tm_year + 1900,
    pstToday->tm_hour,
    pstToday->tm_min,
    pstToday->tm_sec,
    kpszModule,
    kiLine,
    kpszFunction,
    kpszFmt
  );
  
  vfprintf(fpFile, pszDbg, ap);
  
  if ( gstTracePrm.bLogInTerminal ) printf("%s", pszDbg);
  
  free(pszDbg);
  
  va_end(ap);
  
  fclose(fpFile);
  fpFile  = NULL;
  
  if ( gstTracePrm.bRotateLog ) vRotateLog();
}

void _vTraceNoNL(const char *kpszModule, const int kiLine, const char *kpszFunction, const char *kpszFmt, ...) {
  va_list ap;
  FILE *fpFile = NULL;
  char *pszDbg = NULL;
  int iBufferSize = 0;
  time_t tSeconds = 0;
  struct tm *pstToday = NULL;
  
  if ( (fpFile = fopen(gstTracePrm.szTrace, "a")) == NULL ) {
    fprintf(stderr, "E: impossible open the file [%s] %s!", gstTracePrm.szTrace, strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  tSeconds = time(NULL);
  pstToday = localtime(&tSeconds);
  
  va_start(ap, kpszFmt);
  
  iBufferSize = snprintf(
    NULL,
    0,
    "%02d/%02d/%04d %02d:%02d:%02d [%s:%i] %s - %s",
    pstToday->tm_mday,
    pstToday->tm_mon + 1,
    pstToday->tm_year + 1900,
    pstToday->tm_hour,
    pstToday->tm_min,
    pstToday->tm_sec,
    kpszModule,
    kiLine,
    kpszFunction,
    kpszFmt
  )+1;
  pszDbg = (char *) malloc(sizeof(char) * iBufferSize);
  snprintf(
    pszDbg,
    iBufferSize,
    "%02d/%02d/%04d %02d:%02d:%02d [%s:%i] %s - %s",
    pstToday->tm_mday,
    pstToday->tm_mon + 1,
    pstToday->tm_year + 1900,
    pstToday->tm_hour,
    pstToday->tm_min,
    pstToday->tm_sec,
    kpszModule,
    kiLine,
    kpszFunction,
    kpszFmt
  );
  
  vfprintf(fpFile, pszDbg, ap);
  
  if ( gstTracePrm.bLogInTerminal ) printf("%s", pszDbg);
  
  free(pszDbg);
  
  va_end(ap);
  
  fclose(fpFile);
  fpFile  = NULL;
  
  if ( gstTracePrm.bRotateLog ) vRotateLog();
}

void vTraceCmdLine(int argc, char **argv) {
  int ii = 0;
  vTrace("argc [%d]", argc);
  for ( ii = 0; ii < argc; ii++ ) {
    vTrace("%d: [%s]", ii, argv[ii]);
  }
}

void vTraceEnvp(char **envp) {
  int ii = 0;
  for ( ii = 0; envp[ii]; ii++ ) {
    vTrace("%d: [%s]", ii, envp[ii]);
  }
}

void vTraceDataTypesSize(void) {
  vTrace("bool               [%ld]", sizeof(bool));
  vTrace("char               [%ld]", sizeof(char));
  vTrace("signed char        [%ld]", sizeof(signed char));
  vTrace("unsigned char      [%ld]", sizeof(unsigned char));
  vTrace("short              [%ld]", sizeof(short));
  vTrace("unsigned short     [%ld]", sizeof(unsigned short));
  vTrace("int                [%ld]", sizeof(int));
  vTrace("unsigned int       [%ld]", sizeof(unsigned int));
  vTrace("long               [%ld]", sizeof(long));
  vTrace("unsigned long      [%ld]", sizeof(unsigned long));
  vTrace("long long          [%ld]", sizeof(long long));
  vTrace("unsigned long long [%ld]", sizeof(unsigned long long));
  vTrace("float              [%ld]", sizeof(float));
  vTrace("double             [%ld]", sizeof(double));
  vTrace("long double        [%ld]", sizeof(long double));
  vTrace("int8_t             [%ld]", sizeof(int8_t));
  vTrace("uint8_t            [%ld]", sizeof(uint8_t));
  vTrace("int16_t            [%ld]", sizeof(int16_t));
  vTrace("uint16_t           [%ld]", sizeof(uint16_t));
  vTrace("int32_t            [%ld]", sizeof(int32_t));
  vTrace("uint32_t           [%ld]", sizeof(uint32_t));
#ifdef __x86_64__
  vTrace("int64_t            [%ld]", sizeof(int64_t));
  vTrace("uint64_t           [%ld]", sizeof(uint64_t));
#endif
  vTrace("size_t             [%ld]", sizeof(size_t));
  vTrace("ptrdiff_t          [%ld]", sizeof(ptrdiff_t));
  vTrace("void*              [%ld]", sizeof(void *));
}

