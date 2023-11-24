/**
 * hello_log.c
 *
 * Writeen by Gustavo Bacagine <gustavo.bacaigne@protonmail.com>
 *
 * Descritpion: Print a hello world in a log file.
 * 
 * Date: 23/09/2023
 */

#include <stdio.h>
#include "log.h"

#define UNUSED(X) (void) X

int main(int argc, char **argv)
{
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
  
  vSetLogFileName("hello_log.log");

  if(INFO_DETAILS)
  {
    vTraceInfo("%s - begin", __func__);
    vTraceInfo("Hello World!!!");
    vTraceInfo("%s - end", __func__);
  }

  return 0;
}

