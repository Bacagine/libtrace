/**
 * module1.c: Test to log library, using modular programming
 *
 * This file is module 1 of 2
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-09-14
 */

#include <stdio.h>
#include "log.h"

#define UNUSED(X) (void) X

void vShowDebugLevel(void);
void vShowColoredLogLevel(void);
void vShowConfFileName(void);
void vShowLogFileName(void);

int main(int argc, char **argv)
{
  int iColoredLogLevel;
 
  UNUSED(argc);
  UNUSED(argv);
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
  
  vSetLogFileName("module.log"); 
  
  if(INFO_LEVEL)
  {
    vLogInfo("Start %s function", __func__);
    vLogInfo("Debug Level = %d", giDebugLevel);
    vLogInfo("Colored Log Level = %s", 
      gbColoredLogLevel == true ? "true" : "false");
    vLogInfo("Configure file: %s", gszConfFileName);
    vLogInfo("Log file: %s", gszLogFileName);
  }

  vShowDebugLevel();
  vShowColoredLogLevel();
  vShowConfFileName();
  vShowLogFileName();
  
  if(INFO_LEVEL) vLogInfo("End %s funciton", __func__);

  return 0;
}
