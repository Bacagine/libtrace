/**
 * main.c
 * 
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com> in February 2025
 * 
 * Description: A test for libtrace
 * 
 * Date: 21/02/2025
 */

#include "trace.h"

int main(int argc, char **argv, char **envp) {
  int iRsl = 0;
  
  vInitTrace("test.log", "9");
  
  if ( DEBUG_INFO_DETAILS ) {
    vTraceBegin();
    vTrace("%s [%s %s]",
      argv[0],
      __DATE__,
      __TIME__
    );
    
    vTraceCmdLine(argc, argv);
  }
  if ( DEBUG_TRACE_DETAILS ) vTraceEnvp(envp);
  
  printf("Hello World!!!\n");
  
  if ( DEBUG_INFO_DETAILS ) vTrace("end - iRsl [%d]", iRsl);
  
  return iRsl;
}

