/**
 * module1.c: Test to trace library, using modular programming
 *
 * This file is module 1 of 2
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-09-14
 */

#include <stdio.h>
#include "trace.h"

#define UNUSED(X) (void) X

void vShowDebugLevel(void);
void vShowTraceFileName(void);

int main(int argc, char **argv) {
  UNUSED(argc);
  UNUSED(argv);
 
  vSetDebugLevel(TRACE_LEVEL);

  if ( giDebugLevel < 1 ) {
    fprintf(stderr, "Error, giDebugLevel return value: %d!\n", giDebugLevel);
    exit(EXIT_FAILURE);
  }
  
  vSetTraceFileName("module.log"); 
  
  if ( INFO_DETAILS ) {
    vTrace("begin %s function", __func__);
    vTrace("Debug Level = %d", giDebugLevel);
    vTrace("Log file: %s", gszTrace);
  }

  vShowDebugLevel();
  vShowTraceFileName();
  
  if(INFO_DETAILS) vTrace("end %s funciton", __func__);

  return 0;
}

