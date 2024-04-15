/**
 * hello_trace.c
 *
 * Writeen by Gustavo Bacagine <gustavo.bacaigne@protonmail.com>
 *
 * Descritpion: Print a hello world in a trace file.
 * 
 * Date: 23/09/2023
 */

#include <stdio.h>
#include "trace.h"

#define UNUSED(X) (void) X

int main(int argc, char **argv) {
  UNUSED(argc);
  UNUSED(argv);
  
  vSetDebugLevel(INFO_DETAILS);

  if ( giDebugLevel < 1 ) {
    fprintf(stderr, "Error, giDebugLevel return value: %d!\n", giDebugLevel);
    exit(EXIT_FAILURE);
  }
  
  vSetTraceFileName("hello_trace.log");

  if ( INFO_DETAILS ) {
    vTrace("%s - begin", __func__);
    vTrace("Hello World!!!");
    vTrace("%s - end", __func__);
  }

  return 0;
}

