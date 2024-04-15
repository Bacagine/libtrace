# libtrace

![Colored Logger](doc/img/trace.png)

My personal debug library for my C/C++ programs

To better understand my codes, read the README.md at [this link](https://github.com/Bacagine/Bacagine)


# How to use?

## Log Levels

- INFO_LEVEL    (1): Normal messages
- WARNING_LEVEL (2): Alert messages
- ERROR_LEVEL   (3): Errors that not cause the interruption of program
- FATAL_LEVEL   (4): Erros that cause the interruption of program
- DEBUG_LEVEL   (5): Detailed messages intended for the programmer
- TRACE_LEVEL   (6): Messages more detailed than DEBUG_LEVEL level. Show all trace level messages

## Configuration file

Your application needs a .conf file, in this file you add the follow contents:

```shell
# 1 to 6
LOG_LEVEL = 6

# true or false
COLORED_LOG_LEVEL = false
```

## Build and Install
```
# ./mkinstall
```

## Examples of usage

### Example 1 - debug.c

```c
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

```

### Example 2 - hello_trace.c
```c
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

```

### Example 3 - trace_function.c

```c
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

```

### Example 4 - trace_level.c
```c
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

```

### Example 5 - Modular programming

```c
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

```

```c
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

```

### Compile the codes

```
$ gcc -o debug debug.c -ltrace
$ gcc -o hello_trace hello_trace.c -ltrace
$ gcc -o trace trace.c -ltrace
$ gcc -o trace_level trace_level.c -ltrace
$ gcc -c module1.c -o module1.o -ltrace
$ gcc -c module2.c -o module2.o -ltrace
$ gcc -o module module1.o module2.o -ltrace
```

OBS: if you would like to test without installing, make sure to run the following command in your terminal:

```
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
```

### Uninstall

```
# ./mkuninstall
```

