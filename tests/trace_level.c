/**
 * trace_level.c: Test to trace library with TRACE_DETAILS
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-06-16
 */

#include <stdio.h>
#include "trace.h"

#define UNUSED(X) (void) X

int main(int argc, char **argv, char **envp) {
  int ii;
  
  UNUSED(gszTrace);

  vSetDebugLevel(TRACE_LEVEL);

  if ( giDebugLevel < 1 ) {
    fprintf(stderr, "Error, giDebugLevel return value: %d!\n", giDebugLevel);
    exit(EXIT_FAILURE);
  }
  
  vSetTraceFileName("trace_level.log");

  if ( INFO_DETAILS ) {
    vTrace("begin %s function", __func__);
    vTrace("INFO Message"      );
  }

  if ( WARNING_DETAILS ) vTrace("WARNING Message");
  if ( ERROR_DETAILS   ) vTrace("ERROR Message"    );
  if ( FATAL_DETAILS   ) vTrace("FATAL Message"    );
  
  if ( DEBUG_DETAILS ) {
    vTrace("argc = %d", argc);
    for ( ii = 0; ii < argc; ii++ ) {
      vTrace("argv[%d] = %s", ii, argv[ii]);
    }

    for ( ii = 0; envp[ii] != NULL; ii++ ) {
      vTrace("envp[%d] = %s", ii, envp[ii]);
    }
  }
  
  if ( TRACE_DETAILS ) {
    vTrace("TRACE Message");
    vTrace("%s(argc=%p, argv=%p, envp=%p)", __func__, &argc, &argv, &envp);
  }

  if ( INFO_DETAILS ) {
    vTrace("end %s function", __func__);
  }

  return 0;
}

