/* main.c: Test to log library with TRACE_LEVEL
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-06-16
 */

#include <stdio.h>
#include "log.h"

int main(int argc, char **argv, char **envp)
{
  int ii;

  vSetLogFileName("trace.log");
  giDebugLevel = iGetLogLevel("log.conf");

  if(giDebugLevel < 0)
  {
    fprintf(stderr, "Error, giDebugLevel return value: %d!\n", giDebugLevel);

    exit(EXIT_FAILURE);
  }
  
  if(INFO_LEVEL)
  {
    vLogInfo("start %s function", __func__);
    vLogInfo("INFO Message"      );
  }

  if(WARNING_LEVEL) vLogWarning("WARNING Message");
  if(ERROR_LEVEL  ) vLogError("ERROR Message"    );
  if(FATAL_LEVEL  ) vLogFatal("FATAL Message"    );
  
  if(DEBUG_LEVEL  )
  {
    vLogDebug("argc = %d", argc);
    for(ii = 0; ii < argc; ii++)
    {
      vLogDebug("argv[%d] = %s", ii, argv[ii]);
    }

    for(ii = 0; envp[ii] != NULL; ii++)
    {
      vLogDebug("envp[%d] = %s", ii, envp[ii]);
    }
  }
  
  if(TRACE_LEVEL  )
  {
    vLogTrace("TRACE Message");
    vLogTrace("%s(argc=%p, argv=%p, envp=%p)", __func__, &argc, &argv, &envp);
  }

  if(INFO_LEVEL)
  {
    vLogInfo("End %s function", __func__);
  }

  return 0;
}

