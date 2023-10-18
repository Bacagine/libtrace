/**
 * trace_level.c: Test to log library with TRACE_LOG_LEVEL
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-06-16
 */

#include <stdio.h>
#include "log.h"

#define UNUSED(X) (void) X

int main(int argc, char **argv, char **envp)
{
  int ii;
  
  UNUSED(gbColoredLogLevel);
  UNUSED(gszLogFileName);
  UNUSED(gszConfFileName);
  UNUSED(kszLogLevelColorEnd);
  UNUSED(kszLogLevelColorInit);
  UNUSED(kszLogLevel);

  vSetConfFileName("log.conf");

  vSetLogLevel(iGetLogLevel());

  if(giDebugLevel < 0)
  {
    fprintf(stderr, "Error, giDebugLevel return value: %d!\n", giDebugLevel);

    exit(EXIT_FAILURE);
  }
  
  vSetLogFileName("trace_level.log");

  if(INFO_LOG_LEVEL)
  {
    vTraceInfo("start %s function", __func__);
    vTraceInfo("INFO Message"      );
  }

  if(WARNING_LOG_LEVEL) vTraceWarning("WARNING Message");
  if(ERROR_LOG_LEVEL  ) vTraceError("ERROR Message"    );
  if(FATAL_LOG_LEVEL  ) vTraceFatal("FATAL Message"    );
  
  if(DEBUG_LOG_LEVEL  )
  {
    vTraceDebug("argc = %d", argc);
    for(ii = 0; ii < argc; ii++)
    {
      vTraceDebug("argv[%d] = %s", ii, argv[ii]);
    }

    for(ii = 0; envp[ii] != NULL; ii++)
    {
      vTraceDebug("envp[%d] = %s", ii, envp[ii]);
    }
  }
  
  if(TRACE_LOG_LEVEL  )
  {
    vTraceAll("TRACE Message");
    vTraceAll("%s(argc=%p, argv=%p, envp=%p)", __func__, &argc, &argv, &envp);
  }

  if(INFO_LOG_LEVEL)
  {
    vTraceInfo("End %s function", __func__);
  }

  return 0;
}

