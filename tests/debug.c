/**
 * debug.c: Exemple of the DEBUG_DETAILS
 * 
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-06-17
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "log.h"

#define UNUSED(X) (void) X

/**
 * Structure that 
 * represents a person
 */
typedef struct Person
{
  char szName[64];
  uint8_t uAge;
} Person, *PPerson;

static void vInitPerson(PPerson *ppstPerson)
{
  if(INFO_DETAILS)
  {
    vTraceInfo("start %s function", __func__);
    vTraceInfo("Setting the default values in members of struct Person");
  }
  
  memset((*ppstPerson)->szName, 0, sizeof((*ppstPerson)->uAge));
  (*ppstPerson)->uAge = 0;
  
  if(DEBUG_DETAILS)
  {
    vTraceDebug("memset((*ppstPerson)->szName, 0, sizeof((*ppstPerson)->uAge))");
    vTraceDebug("(*ppstPerson)->uAge = 0");
  }

  if(INFO_DETAILS)
  {
    vTraceInfo("end %s function", __func__);
  }
}
  
static void vCreatePerson(PPerson *ppstPerson, const char *szName, const uint8_t uAge)
{
  if(INFO_DETAILS)
  {
    vTraceInfo("start %s function", __func__);
    vTraceInfo("create a new person");
  }

  strcpy((*ppstPerson)->szName, szName);
  (*ppstPerson)->uAge = uAge;

  if(DEBUG_DETAILS)
  {
    vTraceDebug("Values of the member Person");
    vTraceDebug("(*ppstPerson)->szName = %s", (*ppstPerson)->szName);
    vTraceDebug("(*ppstPerson)->uAge = %d", (*ppstPerson)->uAge);
  }

  if(INFO_DETAILS)
  {
    vTraceInfo("Person created with succes");
    vTraceInfo("end %s function", __func__);
  }
}

static void vShowPerson(PPerson pstPerson)
{
  if(INFO_DETAILS)
  {
    vTraceInfo("start %s function", __func__);
    vTraceInfo("Show Person");
    vTraceInfo("Name: %s\n"
             "Age.: %d\n", pstPerson->szName,
                           pstPerson->uAge);
  }

  printf("Name: %s\n"
         "Age.: %d\n", pstPerson->szName,
                       pstPerson->uAge);

  if(INFO_DETAILS)
  {
    vTraceInfo("end %s function", __func__);
  }
}

static void vDestroyPerson(PPerson *ppstPerson)
{
  if(INFO_DETAILS)
  {
    vTraceInfo("start %s function", __func__);
  }
  
  memset((*ppstPerson)->szName, 0, sizeof((*ppstPerson)->uAge));
  (*ppstPerson)->uAge = 0;
  
  if(DEBUG_DETAILS)
  {
    vTraceDebug("memset((*ppstPerson)->szName, 0, sizeof((*ppstPerson)->uAge))");
    vTraceDebug("(*ppstPerson)->uAge = 0");
    vTraceDebug("Freeing Person structure pointer");
  }

  free((*ppstPerson));
  (*ppstPerson) = NULL;

  if(DEBUG_DETAILS)
  {
    vTraceDebug("free((*ppstPerson))");
    vTraceDebug("(*ppstPerson) = NULL");
    vTraceDebug("Person structure pointer free");
  }

  if(INFO_DETAILS)
  {
    vTraceInfo("end %s function", __func__);
  }
}

int main(int argc, char **argv)
{
  PPerson pstPerson = (PPerson) malloc(sizeof(Person));
  
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
  
  vSetLogFileName("debug.log");
  
  /* Initial log messages */
  if(INFO_DETAILS)
  {
    vTraceInfo("Start of function %s", __func__);
  }
  
  if(pstPerson == NULL)
  {
    if(DEBUG_DETAILS)
    {
      vTraceDebug("E: out memory in allocation of pstPerson!");
    }
  }

  vInitPerson(&pstPerson);
  
  vCreatePerson(&pstPerson, "Gustavo Bacagine", 23);
  
  vShowPerson(pstPerson);

  vDestroyPerson(&pstPerson);
  
  /* End log messages */
  if(INFO_DETAILS)
  {
    vTraceInfo("End of function %s", __func__);
  }

  return 0;
}

