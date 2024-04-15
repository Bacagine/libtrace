/**
 * trace.h: This file contains constants and functions to create 
 * .log files
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmai.com>
 *
 * Date: 2023-06-16
 */

#ifndef _TRACE_H_
#define _TRACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>

#ifdef LINUX
  #include <sys/time.h>
  #include <unistd.h>
#else
  #include <windows.h>
#endif

#define INFO_LEVEL    1 // Normal messages
#define WARNING_LEVEL 2 // Warning alert messages
#define ERROR_LEVEL   3 // Error messages
#define FATAL_LEVEL   4 // Fatal error messages
#define DEBUG_LEVEL   5 // Messages with more information about the source code
#define TRACE_LEVEL   6 // Show all messages in trace

/**
 * Example of use:
 *
 * if(INFO_DETAILS) {
 *   vTraceInfo("INFO Message");
 * }
 *
 * if(DEBUG_DETAILS) {
 *   vTraceDebug("DEBUG Message");
 * }
 */
#define INFO_DETAILS    giDebugLevel >= INFO_LEVEL   
#define WARNING_DETAILS giDebugLevel >= WARNING_LEVEL
#define ERROR_DETAILS   giDebugLevel >= ERROR_LEVEL
#define FATAL_DETAILS   giDebugLevel >= FATAL_LEVEL
#define DEBUG_DETAILS   giDebugLevel >= DEBUG_LEVEL
#define TRACE_DETAILS   giDebugLevel >= TRACE_LEVEL

#define vTrace(FORMAT, ...) _vTrace(__FILE__, __LINE__, FORMAT, ##__VA_ARGS__)

#define vTraceBegin() _vTrace(__FILE__, __LINE__, "%s - begin", __func__)
#define vTraceEnd()   _vTrace(__FILE__, __LINE__, "%s - end", __func__)

extern char gszTrace[256]; 
extern int giDebugLevel;

void vSetTraceFileName(const char *kszLogFileName);
void vSetDebugLevel(const int kiDebugLevel);
int iGetDebugLevel(void);

void _vTrace(const char *kpszModuleName,
             const int kiLine,
             const char *kpszFmt, ...);

#endif

