/**
 * module2.c: Test to log library, using modular programming
 *
 * This file is module 2 of 2
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-09-14
 */

#include "log.h"

#define UNUSED(X) (void) X

void vShowDebugLevel(void)
{
  UNUSED(gbColoredLogLevel);
  UNUSED(gszLogFileName);
  UNUSED(gszConfFileName);
  UNUSED(kszLogLevelColorEnd);
  UNUSED(kszLogLevelColorInit);
  UNUSED(kszLogLevel);
  
  if(INFO_LEVEL)
  {
    vLogInfo("Start %s function", __func__);
    vLogInfo("Debug Level = %d", giDebugLevel);
  }

  printf("Debug Level = %d\n", giDebugLevel);

  if(INFO_LEVEL) vLogInfo("End %s funciton", __func__);
}

void vShowColoredLogLevel(void)
{
  UNUSED(gszLogFileName);
  UNUSED(gszConfFileName);
  UNUSED(kszLogLevelColorEnd);
  UNUSED(kszLogLevelColorInit);
  UNUSED(kszLogLevel);
  
  if(INFO_LEVEL)
  {
    vLogInfo("Start %s function", __func__);
    vLogInfo("Colored Log Level = %s", 
      gbColoredLogLevel == true ? "true" : "false");
  } 

  printf("Colored Log Level = %s\n", 
      gbColoredLogLevel == true ? "true" : "false");

  if(INFO_LEVEL) vLogInfo("End %s funciton", __func__);
}

void vShowConfFileName(void)
{
  UNUSED(gbColoredLogLevel);
  UNUSED(gszLogFileName);
  UNUSED(kszLogLevelColorEnd);
  UNUSED(kszLogLevelColorInit);
  UNUSED(kszLogLevel);
  
  if(INFO_LEVEL)
  {
    vLogInfo("Start %s function", __func__);
    vLogInfo("Configure file: %s", gszConfFileName);
  }

  printf("Configure file: %s\n", gszConfFileName);

  if(INFO_LEVEL) vLogInfo("End %s funciton", __func__);
}

void vShowLogFileName(void)
{
  UNUSED(gbColoredLogLevel);
  UNUSED(gszConfFileName);
  UNUSED(kszLogLevelColorEnd);
  UNUSED(kszLogLevelColorInit);
  UNUSED(kszLogLevel);
  
 if(INFO_LEVEL)
  {
    vLogInfo("Start %s function", __func__);
    vLogInfo("Log file: %s", gszLogFileName);
  }

  printf("Log file: %s\n", gszLogFileName);

  if(INFO_LEVEL) vLogInfo("End %s funciton", __func__);
}

