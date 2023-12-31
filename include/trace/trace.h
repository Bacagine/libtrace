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

#define INFO_LEVEL    1 /* Normal messages                                      */
#define WARNING_LEVEL 2 /* Warning alert messages                               */
#define ERROR_LEVEL   3 /* Error messages                                       */
#define FATAL_LEVEL   4 /* Fatal error messages                                 */
#define DEBUG_LEVEL   5 /* Messages with more information about the source code */
#define TRACE_LEVEL   6 /* Show all messages in trace                           */

/**
 * Example of use:
 *
 * if(INFO_DETAILS)
 * {
 *   vTraceInfo("INFO Message");
 * }
 *
 * if(DEBUG_DETAILS)
 * {
 *   vTraceDebug("DEBUG Message");
 * }
 */
#define INFO_DETAILS    giDebugLevel >= INFO_LEVEL   
#define WARNING_DETAILS giDebugLevel >= WARNING_LEVEL
#define ERROR_DETAILS   giDebugLevel >= ERROR_LEVEL
#define FATAL_DETAILS   giDebugLevel >= FATAL_LEVEL
#define DEBUG_DETAILS   giDebugLevel >= DEBUG_LEVEL
#define TRACE_DETAILS   giDebugLevel >= TRACE_LEVEL

/* White color */
#define INFO_INIT_COLOR "\033[1;37m"
#define INFO_END_COLOR  "\033[0m"

/* Cyan color */
#define WARNING_INIT_COLOR "\033[1;35m"
#define WARNING_END_COLOR  "\033[0m"

/* Red color */
#define ERROR_INIT_COLOR "\033[1;31m"
#define ERROR_END_COLOR  "\033[0m"

#define FATAL_INIT_COLOR "\033[1;31m"
#define FATAL_END_COLOR  "\033[0m"

/* Blue color */
#define DEBUG_INIT_COLOR "\033[1;34m"
#define DEBUG_END_COLOR  "\033[0m"

/* Yellow color */
#define TRACE_INIT_COLOR "\033[1;33m"
#define TRACE_END_COLOR  "\033[0m"

#define vTraceInfo(FORMAT, ...)    _vTrace(INFO_LEVEL,    __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)
#define vTraceWarning(FORMAT, ...) _vTrace(WARNING_LEVEL, __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)
#define vTraceError(FORMAT, ...)   _vTrace(ERROR_LEVEL,   __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)
#define vTraceFatal(FORMAT, ...)   _vTrace(FATAL_LEVEL,   __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)
#define vTraceDebug(FORMAT, ...)   _vTrace(DEBUG_LEVEL,   __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)
#define vTraceAll(FORMAT, ...)     _vTrace(TRACE_LEVEL,   __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)

#define vTrace(LOG_LEVEL, FORMAT, ...) if(giDebugLevel >= LOG_LEVEL) _vTrace(LOG_LEVEL, __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)

#define vTraceBegin() if(INFO_DETAILS) _vTrace(INFO_LEVEL, __FILE__, __LINE__, "%s - begin", __func__)
#define vTraceEnd()   if(INFO_DETAILS) _vTrace(INFO_LEVEL, __FILE__, __LINE__, "%s - end", __func__)

static const char *kszLogLevel[] = {
  "INFO", "WARNING", "ERROR", "FATAL", "DEBUG", "TRACE"
};

static const char *kszLogLevelColorInit[] = {
  INFO_INIT_COLOR, WARNING_INIT_COLOR, 
  ERROR_INIT_COLOR, FATAL_INIT_COLOR, 
  DEBUG_INIT_COLOR, TRACE_INIT_COLOR
};

static const char *kszLogLevelColorEnd[] = {
  INFO_END_COLOR, WARNING_END_COLOR, 
  ERROR_END_COLOR, FATAL_END_COLOR, 
  DEBUG_END_COLOR, TRACE_END_COLOR
};

/**
 * Receive the name of .conf file
 */
extern char gszConfFileName[256];

/**
 * Receive the name of .trace file
 */
extern char gszLogFileName[256]; 

/**
 * Receive the level of debug from .conf 
 * file, the default is 1 (INFO_LEVEL)
 */
extern int giDebugLevel;

/**
 * Receive if the trace level tag is colored 
 * or not, the default is without color
 */
extern bool gbColoredLogLevel;

/**
 * Set the name of configure file of 
 * the software
 */
void vSetConfFileName(const char *kszConfFile);

/**
 * Set the name of trace file
 */
void vSetLogFileName(const char *kszLogFileName);

/** 
 * Enable or disable trace level with 
 * colored and bold
 */
void vSetColoredLogLevel(bool bColored);

/**
 * Set the value of giDebugLevel
 */
void vSetLogLevel(const int kiDebugLevel);

/**
 * Get the trace level from file.
 * 
 * return values:
 * 1 - 6 = Log Level
 * -1 if can't open the file.
 * -2 if LOG_LEVEL is empty in file
 * -3 if don't found LOG_LEVEL variable in file
 * -4 if value of LOG_LEVEL is invalid
 */
int iGetLogLevel(void);

/**
 * Get the colored trace level from file.
 * 
 * return values:
 *  0 is fals, no color in trace level
 *  1 is true, colored in trace level
 * -1 if can't open the file.
 * -2 if COLORED_LOG_LEVEL is empty in file
 * -3 if don't found COLORED_LOG_LEVEL variable in file
 * -4 if value of COLORED_LOG_LEVEL is invalid
 */
int iGetColoredLogLevel(void);

/**
 * Print a trace message with the trace level between [].
 */
void _vTrace(const int kiDebugLevel,
             const char *kpszModuleName,
             const int kiLine,
             const char *kpszFmt, ...);

#endif /* _TRACE_H_ */

