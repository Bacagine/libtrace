/**
 * trace.c
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Description: File created to test the new macros:
 *  vTrace
 *  vTraceBegin
 *  vTraceEnd
 *
 * Date: 2023-10-17
 *
 */

#include <stdio.h>
#include "trace.h"

#define UNUSED(X) (void) X

void vMyFunc(void)
{
  vTraceBegin();
  
  vTrace(INFO_LEVEL, "INFO MESSAGE");
  vTrace(WARNING_LEVEL, "WARNING MESSAGE");
  vTrace(ERROR_LEVEL, "ERROR MESSAGE");
  vTrace(FATAL_LEVEL, "FATAL MESSAGE");
  vTrace(DEBUG_LEVEL, "DEBUG MESSAGE");
  vTrace(TRACE_LEVEL, "TRACE MESSAGE");

  vTraceEnd();
}

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);
  UNUSED(gbColoredLogLevel);
  UNUSED(gszLogFileName);
  UNUSED(gszConfFileName);
  UNUSED(kszLogLevelColorEnd);
  UNUSED(kszLogLevelColorInit);
  UNUSED(kszLogLevel);

  vSetConfFileName("trace.conf");

  vSetLogLevel(iGetLogLevel());

  if(giDebugLevel < 1)
  {
    fprintf(stderr, "Error, giDebugLevel return value: %d!\n", giDebugLevel);

    exit(EXIT_FAILURE);
  }
  
  vSetLogFileName("trace.log");

  vTraceBegin();
  
  vTrace(INFO_LEVEL, "Main Info Message :)");

  vMyFunc();

  vTraceEnd();

  return 0;
}

