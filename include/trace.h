/**
 * trace.h
 * 
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com> in February 2025
 * 
 * Description: Debug module
 * 
 * Date: 20/02/2025
 */

#ifndef _TRACE_H_
#define _TRACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

#define MAX_DEBUG_LEVEL_LENGHT 10

#define DEBUG_INFO_LEVEL    '1'
#define DEBUG_WARNING_LEVEL '2'
#define DEBUG_ERROR_LEVEL   '3'
#define DEBUG_FATAL_LEVEL   '4'
#define DEBUG_LEVEL         '5'
#define DEBUG_TRACE_LEVEL   '6'
#define DEBUG_VERBOSE_LEVEL '7'
#define DEBUG_MORE_LEVEL    '8'
#define DEBUG_ALL_LEVEL     '9'

// Global Debug Level
#define DEBUG_INFO_DETAILS    gstTracePrm.szDebugLevel[0] >= DEBUG_INFO_LEVEL
#define DEBUG_WARNING_DETAILS gstTracePrm.szDebugLevel[0] >= DEBUG_WARNING_LEVEL
#define DEBUG_ERROR_DETAILS   gstTracePrm.szDebugLevel[0] >= DEBUG_ERROR_LEVEL
#define DEBUG_FATAL_DETAILS   gstTracePrm.szDebugLevel[0] >= DEBUG_FATAL_LEVEL
#define DEBUG_DETAILS         gstTracePrm.szDebugLevel[0] >= DEBUG_LEVEL
#define DEBUG_TRACE_DETAILS   gstTracePrm.szDebugLevel[0] >= DEBUG_TRACE_LEVEL
#define DEBUG_VERBOSE_DETAILS gstTracePrm.szDebugLevel[0] >= DEBUG_VERBOSE_LEVEL
#define DEBUG_MORE_DETAILS    gstTracePrm.szDebugLevel[0] >= DEBUG_MORE_LEVEL
#define DEBUG_ALL_DETAILS     gstTracePrm.szDebugLevel[0] >= DEBUG_ALL_LEVEL

#define vInitTrace(kpszTrace, kpszDebugLevel) _vInitTrace(kpszTrace, kpszDebugLevel, false, false, 0)

#define vTrace(...) do { _vTrace(__FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); } while ( 0 )
#define vTraceNoNL(...) do { _vTraceNoNL(__FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); } while ( 0 )
  
#define vTraceBegin() vTrace("begin")

#define vTraceInfo(szMsg) do { vTrace("[INFO] %s", szMsg); } while ( 0 )
#define vTraceWarning(szMsg) do { vTrace("[WARNING] %s", szMsg); } while ( 0 )
#define vTraceErro(szMsg) do { vTrace("[ERROR] %s", szMsg); } while ( 0 )
#define vTraceFatal(szMsg) do { vTrace("[FATAL] %s", szMsg); } while ( 0 )
#define vTraceDetails(szMsg) do { vTrace("[DETAILS] %s", szMsg); } while ( 0 )
#define vTraceTraceDetails(szMsg) do { vTrace("[TRACE] %s", szMsg); } while ( 0 )
#define vTraceVerbose(szMsg) do { vTrace("[VERBOSE] %s", szMsg); } while ( 0 )
#define vTraceMoreDetails(szMsg) do { vTrace("[MORE DETAILS]"); } while ( 0 )
#define vTraceAll(szMsg) do { vTrace("[ALL] %s", szMsg); } while ( 0 )

#define vTraceEnd() vTrace("end")

typedef struct STRUCT_TRACE_PRM {
  char szTrace[256];
  char szDebugLevel[MAX_DEBUG_LEVEL_LENGHT];
  bool bLogInTerminal;
  bool bRotateLog;
  long long llMaxLogSize;
} STRUCT_TRACE_PRM, *PSTRUCT_TRACE_PRM;

extern STRUCT_TRACE_PRM gstTracePrm;

/**
 * @brief set the path of trace file
 * 
 * @param kpszTrace is the path of the trace file
 */
void vSetTraceFile(const char *kpszTrace);

/**
 * @brief set the debug level
 * 
 * @param kpszDebugLevel is the debug level
 */
void vSetDebugLevel(const char *kpszDebugLevel);

/**
 * @brief enable log in terminal
 * 
 * @param kbLogOnTerminal enable log in terminal
 */
void vSetLogOnTerminal(const bool kbLogOnTerminal);

/**
 * @brief ...
 * 
 * @param kbLogOnTerminal p_kbLogOnTerminal:...
 */
void vSetRotateLog(const bool kbRotateLog);

/**
 * @brief ...
 * 
 * @param kllMaxLogSize p_kllMaxLogSize:...
 */
void vSetMaxLogSize(const long long kllMaxLogSize);

/**
 * @brief init trace module
 * 
 * @param kpszTrace is the path of the trace file
 * @param kpszDebugLevel is the debug level
 * @param kbLogOnTerminal enable log in terminal
 * @param kbRotateLog enable the rotate log
 * @param kllMaxLogSize is the max size of log file
 */
void _vInitTrace(const char *kpszTrace, const char *kpszDebugLevel, const bool kbLogOnTerminal, const bool kbRotateLog, const long long kllMaxLogSize);

/// @brief Rotate log
void vRotateLog(void);

/**
 * @brief Function used to write trace messages in a .log file
 * 
 * @param kspzModule is the name of module (__FILE__ define)
 * @param kiLine is the number of source code line (__LINE__ define)
 * @param kpszFunction is the name of function (__FUNCTION__ or __func__ defines)
 * @param kpszFmt is the formated trace message
 */
void _vTrace(const char *kpszModule, const int kiLine, const char *kpszFunction, const char *kpszFmt, ...);

/**
 * @brief Function used to write trace messages in a .log file without '\n' character in the end of string
 * 
 * @param kspzModule is the name of module (__FILE__ define)
 * @param kiLine is the number of source code line (__LINE__ define)
 * @param kpszFunction is the name of function (__FUNCTION__ or __func__ defines)
 * @param kpszFmt is the formated trace message
 */
void _vTraceNoNL(const char *kpszModule, const int kiLine, const char *kpszFunction, const char *kpszFmt, ...);

/**
 * @brief trace commando line arguments
 * 
 * @param argc argument counter
 * @param argv argument vector
 */
void vTraceCmdLine(int argc, char **argv);

/**
 * @brief trace envrionment system variables
 * 
 * @param envp is the envrionment system variables
 */
void vTraceEnvp(char **envp);

/// @brief Trace the data types size in bytes
void vTraceDataTypesSize(void);

#ifdef __cplusplus
}
#endif

#endif

