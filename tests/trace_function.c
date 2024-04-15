/**
 * trace_function.c
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

void vMyFunc(void) {
  if ( INFO_DETAILS ) vTraceBegin();
  
  if ( INFO_DETAILS ) vTrace("INFO MESSAGE");
  if ( WARNING_DETAILS ) vTrace("WARNING MESSAGE");
  if ( ERROR_DETAILS ) vTrace("ERROR MESSAGE");
  if ( FATAL_DETAILS ) vTrace("FATAL MESSAGE");
  if ( DEBUG_DETAILS ) vTrace("DEBUG MESSAGE");
  if ( TRACE_DETAILS ) vTrace("TRACE MESSAGE");

  if ( INFO_DETAILS ) vTraceEnd();
}

int main(int argc, char **argv) {
  UNUSED(argc);
  UNUSED(argv);
  UNUSED(gszTrace);

  vSetDebugLevel(TRACE_LEVEL);

  vSetTraceFileName("trace.log");

  if ( INFO_DETAILS ) {
    vTraceBegin();
    vTrace("Main Info Message :)");
  }

  vMyFunc();

  if ( INFO_DETAILS ) vTraceEnd();

  return 0;
}

