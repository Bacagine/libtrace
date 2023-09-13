/* log.h: This file contains constants and functions to create 
 * .log files
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmai.com>
 *
 * Date: 2023-06-16
 */

#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>

#define CONF_FILE_NAME_LENGTH 256
#define LOG_FILE_NAME_LENGTH  256

#define INFO    0 /* Normal messages                                      */
#define WARNING 1 /* Warning alert messages                               */
#define ERROR   2 /* Error messages                                       */
#define FATAL   3 /* Fatal error messages                                 */
#define DEBUG   4 /* Messages with more information about the source code */
#define TRACE   5 /* Show all messages in log                             */

/**
 * Example of use:
 *
 * if(INFO_LEVEL)
 * {
 *   vLogInfo("INFO Message");
 * }
 *
 * if(DEBUG_LEVEL)
 * {
 *   vLogDebug("DEBUG Message");
 * }
 */
#define INFO_LEVEL    giDebugLevel >= INFO   
#define WARNING_LEVEL giDebugLevel >= WARNING
#define ERROR_LEVEL   giDebugLevel >= ERROR
#define FATAL_LEVEL   giDebugLevel >= FATAL
#define DEBUG_LEVEL   giDebugLevel >= DEBUG
#define TRACE_LEVEL   giDebugLevel >= TRACE

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

#define vLogInfo(FORMAT, ...)    vLogMessage(INFO,    __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)
#define vLogWarning(FORMAT, ...) vLogMessage(WARNING, __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)
#define vLogError(FORMAT, ...)   vLogMessage(ERROR,   __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)
#define vLogFatal(FORMAT, ...)   vLogMessage(FATAL,   __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)
#define vLogDebug(FORMAT, ...)   vLogMessage(DEBUG,   __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)
#define vLogTrace(FORMAT, ...)   vLogMessage(TRACE,   __FILE__, __LINE__, FORMAT, ##__VA_ARGS__)

typedef int DebugLevel;

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
static char gszConfFileName[LOG_FILE_NAME_LENGTH];

/**
 * Receive the name of .log file
 */
static char gszLogFileName[LOG_FILE_NAME_LENGTH]; 

/**
 * Receive the level of debug from .conf 
 * file, the default is 0 (INFO)
 */
static DebugLevel giDebugLevel = 0;

/**
 * Receive if the log level tag is colored 
 * or not, the default is without color
 */
static bool gbColoredLogLevel = false;

/**
 * Set the name of configure file of 
 * the software
 */
void vSetConfFileName(const char *kszConfFile);

/**
 * Set the name of log file
 */
void vSetLogFileName(const char *kszLogFileName);

/** 
 * Enable or disable log level with 
 * colored and bold
 */
void vSetColoredLogLevel(bool bColored);

/**
 * Get the log level from file.
 * 
 * return values:
 * 0 - 6 = Log Level
 * -1 if can't open the file.
 * -2 if LOG_LEVEL is empty in file
 * -3 if don't found LOG_LEVEL variable in file
 * -4 if value of LOG_LEVEL is invalid
 */
int iGetLogLevel(void);

/**
 * Get the colored log level from file.
 * 
 * return values:
 *  0 is fals, no color in log level
 *  1 is true, colored in log level
 * -1 if can't open the file.
 * -2 if COLORED_LOG_LEVEL is empty in file
 * -3 if don't found COLORED_LOG_LEVEL variable in file
 * -4 if value of COLORED_LOG_LEVEL is invalid
 */
int iGetColoredLogLevel(void);

/**
 * Print a log message
 */
void vLogMessage(const DebugLevel usiDebugLevel,
                 const char *kszModuleName,
                 const int kiLine,
                 const char *kszFmt, ...);

#endif /* _LOG_H_ */

