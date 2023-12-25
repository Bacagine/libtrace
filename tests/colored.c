/**
 * colored.c: Test to trace library, using colored trace level
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-06-16
 */

#include <stdio.h>
#include "trace.h"

#define UNUSED(X) (void) X

int main(int argc, char **argv)
{
  int iColoredLogLevel;
  
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
  
  iColoredLogLevel = iGetColoredLogLevel();
  
  if(iColoredLogLevel == 0 || iColoredLogLevel == 1)
  {
    vSetColoredLogLevel(iColoredLogLevel);
  }
  
  vSetLogFileName("colored.log");
  
  if(INFO_DETAILS)
  {
    vTraceInfo("start %s function", __func__);
    vTraceInfo("INFO Message"      );
  }

  if(WARNING_DETAILS) vTraceWarning("WARNING Message");
  if(ERROR_DETAILS  ) vTraceError("ERROR Message"    );
  if(FATAL_DETAILS  ) vTraceFatal("FATAL Message"    );
  
  if(DEBUG_DETAILS  ) vTraceDebug("argc = %d", argc);

  if(TRACE_DETAILS  ) vTraceAll("%s(argc = %p, argv = %p)", __func__, &argc, &argv);
  
  if(INFO_DETAILS)
  {
    vTraceInfo("End %s function", __func__);
  }

  return 0;
}

