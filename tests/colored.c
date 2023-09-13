/* colored.c: Test to log library, using colored log level
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-06-16
 */

#include <stdio.h>
#include "log.h"

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

  vSetConfFileName("log.conf");

  vSetLogLevel(iGetLogLevel());

  if(giDebugLevel < 0)
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
 
  if(INFO_LEVEL)
  {
    vLogInfo("start %s function", __func__);
    vLogInfo("INFO Message"      );
  }

  if(WARNING_LEVEL) vLogWarning("WARNING Message");
  if(ERROR_LEVEL  ) vLogError("ERROR Message"    );
  if(FATAL_LEVEL  ) vLogFatal("FATAL Message"    );
  
  if(DEBUG_LEVEL  ) vLogDebug("argc = %d", argc);

  if(TRACE_LEVEL  ) vLogTrace("%s(argc = %p, argv = %p)", __func__, &argc, &argv);
  
  if(INFO_LEVEL)
  {
    vLogInfo("End %s function", __func__);
  }

  return 0;
}

