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
#include "trace.h"

#define UNUSED(X) (void) X

typedef struct STRUCT_PERSON {
  char szName[64];
  uint8_t uAge;
} STRUCT_PERSON, *PSTRUCT_PERSON;

static void vInitSTRUCT_PERSON(PSTRUCT_PERSON *ppstPerson) {
  if ( INFO_DETAILS ) {
    vTrace("begin %s function", __func__);
    vTrace("Setting the default values in members of struct STRUCT_PERSON");
  }
  
  memset((*ppstPerson), 0x00, sizeof(PSTRUCT_PERSON *));
  
  if ( DEBUG_DETAILS ) {
    vTrace("memset((*ppstPerson), 0x00, sizeof(PSTRUCT_PERSON *))");
  }

  if ( INFO_DETAILS ) {
    vTrace("end %s function", __func__);
  }
}
  
static void vCreateSTRUCT_PERSON(PSTRUCT_PERSON *ppstPerson, const char *szName, const uint8_t uAge) {
  if ( INFO_DETAILS ) {
    vTrace("begin %s function", __func__);
    vTrace("create a new person");
  }

  strcpy((*ppstPerson)->szName, szName);
  (*ppstPerson)->uAge = uAge;

  if ( DEBUG_DETAILS ) {
    vTrace("Values of the member STRUCT_PERSON");
    vTrace("(*ppstPerson)->szName = %s", (*ppstPerson)->szName);
    vTrace("(*ppstPerson)->uAge = %d", (*ppstPerson)->uAge);
  }

  if ( INFO_DETAILS ) {
    vTrace("STRUCT_PERSON created with succes");
    vTrace("end %s function", __func__);
  }
}

static void vShowSTRUCT_PERSON(PSTRUCT_PERSON pstPerson) {
  if ( INFO_DETAILS ) {
    vTrace("begin %s function", __func__);
    vTrace("Show STRUCT_PERSON");
    vTrace("Name: %s\n"
           "Age.: %d\n", pstPerson->szName,
                         pstPerson->uAge);
  }

  printf("Name: %s\n"
         "Age.: %d\n", pstPerson->szName,
                       pstPerson->uAge);

  if ( INFO_DETAILS ) vTraceEnd();
}

static void vDestroyPerson(PSTRUCT_PERSON *ppstPerson) {
  if ( INFO_DETAILS ) vTraceBegin();
  
  memset((*ppstPerson), 0x00, sizeof(PSTRUCT_PERSON *));
  
  if ( DEBUG_DETAILS ) {
    vTrace("memset((*ppstPerson), 0x00, sizeof(PSTRUCT_PERSON *))");
    vTrace("Freeing STRUCT_PERSON structure pointer");
  }

  free((*ppstPerson));
  (*ppstPerson) = NULL;

  if ( DEBUG_DETAILS ) {
    vTrace("free((*ppstPerson))");
    vTrace("(*ppstPerson) = NULL");
    vTrace("STRUCT_PERSON structure pointer free");
  }

  if ( INFO_DETAILS ) vTraceEnd();
}

int main(int argc, char **argv) {
  PSTRUCT_PERSON pstPerson = (PSTRUCT_PERSON) malloc(sizeof(STRUCT_PERSON));

  UNUSED(argc);
  UNUSED(argv);
  
  vSetTraceFileName("debug.log");
  vSetDebugLevel(DEBUG_LEVEL);
  
  // Initial trace messages
  if ( INFO_DETAILS ) {
    vTrace("begin of function %s", __func__);
  }
  
  if ( pstPerson == NULL ) {
    if ( DEBUG_DETAILS ) {
      vTrace("E: out memory in allocation of pstPerson!");
    }
  }

  vInitSTRUCT_PERSON(&pstPerson);
  
  vCreateSTRUCT_PERSON(&pstPerson, "Gustavo Bacagine", 23);
  
  vShowSTRUCT_PERSON(pstPerson);

  vDestroyPerson(&pstPerson);
  
  // End trace messages
  if ( INFO_DETAILS ) {
    vTrace("end of function %s", __func__);
  }

  return 0;
}

