/* debug.c: Exemple of the DEBUG_LEVEL
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

/* Structure that 
 * represents a person
 */
typedef struct Person
{
  char szName[64];
  uint8_t uAge;
} Person, *PPerson;

static void vInitPerson(PPerson *ppstPerson)
{
  if(INFO_LEVEL)
  {
    vLogInfo("start %s function", __func__);
    vLogInfo("Setting the default values in members of struct Person");
  }
  
  memset((*ppstPerson)->szName, 0, sizeof((*ppstPerson)->uAge));
  (*ppstPerson)->uAge = 0;
  
  if(DEBUG_LEVEL)
  {
    vLogDebug("memset((*ppstPerson)->szName, 0, sizeof((*ppstPerson)->uAge))");
    vLogDebug("(*ppstPerson)->uAge = 0");
  }

  if(INFO_LEVEL)
  {
    vLogInfo("end %s function", __func__);
  }
}
  
static void vCreatePerson(PPerson *ppstPerson, const char *szName, const uint8_t uAge)
{
  if(INFO_LEVEL)
  {
    vLogInfo("start %s function", __func__);
    vLogInfo("create a new person");
  }

  strcpy((*ppstPerson)->szName, szName);
  (*ppstPerson)->uAge = uAge;

  if(DEBUG_LEVEL)
  {
    vLogDebug("Values of the member Person");
    vLogDebug("(*ppstPerson)->szName = %s", (*ppstPerson)->szName);
    vLogDebug("(*ppstPerson)->uAge = %d", (*ppstPerson)->uAge);
  }

  if(INFO_LEVEL)
  {
    vLogInfo("Person created with succes");
    vLogInfo("end %s function", __func__);
  }
}

static void vShowPerson(PPerson pstPerson)
{
  if(INFO_LEVEL)
  {
    vLogInfo("start %s function", __func__);
    vLogInfo("Show Person");
    vLogInfo("Name: %s\n"
             "Age.: %d\n", pstPerson->szName,
                           pstPerson->uAge);
  }

  printf("Name: %s\n"
         "Age.: %d\n", pstPerson->szName,
                       pstPerson->uAge);

  if(INFO_LEVEL)
  {
    vLogInfo("end %s function", __func__);
  }
}

static void vDestroyPerson(PPerson *ppstPerson)
{
  if(INFO_LEVEL)
  {
    vLogInfo("start %s function", __func__);
  }
  
  memset((*ppstPerson)->szName, 0, sizeof((*ppstPerson)->uAge));
  (*ppstPerson)->uAge = 0;
  
  if(DEBUG_LEVEL)
  {
    vLogDebug("memset((*ppstPerson)->szName, 0, sizeof((*ppstPerson)->uAge))");
    vLogDebug("(*ppstPerson)->uAge = 0");
    vLogDebug("Freeing Person structure pointer");
  }

  free((*ppstPerson));
  (*ppstPerson) = NULL;

  if(DEBUG_LEVEL)
  {
    vLogDebug("free((*ppstPerson))");
    vLogDebug("(*ppstPerson) = NULL");
    vLogDebug("Person structure pointer free");
  }

  if(INFO_LEVEL)
  {
    vLogInfo("end %s function", __func__);
  }
}

int main(int argc, char **argv)
{
  PPerson pstPerson = (PPerson) malloc(sizeof(Person));
  
  vSetLogFileName("debug.log");
  giDebugLevel = iGetLogLevel("log.conf");

  if(giDebugLevel < 0)
  {
    fprintf(stderr, "Error, giDebugLevel return value: %d!\n", giDebugLevel);

    exit(EXIT_FAILURE);
  }

  /* Initial log messages */
  if(INFO_LEVEL)
  {
    vLogInfo("Start of function %s", __func__);
  }
  
  if(pstPerson == NULL)
  {
    if(DEBUG_LEVEL)
    {
      vLogDebug("E: out memory in allocation of pstPerson!");
    }
  }

  vInitPerson(&pstPerson);
  
  vCreatePerson(&pstPerson, "Gustavo Bacagine", 23);
  
  vShowPerson(pstPerson);

  vDestroyPerson(&pstPerson);
  
  /* End log messages */
  if(INFO_LEVEL)
  {
    vLogInfo("End of function %s", __func__);
  }

  return 0;
}

