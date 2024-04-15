/**
 * module2.c: Test to trace library, using modular programming
 *
 * This file is module 2 of 2
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-09-14
 */

#include "trace.h"

#define UNUSED(X) (void) X

void vShowDebugLevel(void) {
  UNUSED(gszTrace);
  
  if ( INFO_DETAILS ) {
    vTrace("begin %s function", __func__);
    vTrace("Debug Level = %d", giDebugLevel);
  }

  printf("Debug Level = %d\n", giDebugLevel);

  if ( INFO_DETAILS ) vTrace("end %s funciton", __func__);
}

void vShowTraceFileName(void) {
  if ( INFO_DETAILS ) {
   vTrace("begin %s function", __func__);
   vTrace("Log file: %s", gszTrace);
  }

  printf("Log file: %s\n", gszTrace);

  if ( INFO_DETAILS ) vTrace("end %s funciton", __func__);
}

