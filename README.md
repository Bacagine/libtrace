# LOG

My personal debug library for my C/C++ programers

# How to use?

## Log Levels

- INFO    (0): Normal messages
- WARNING (1): Alert messages
- ERROR   (2): Errors that not cause the interruption of program
- FATAL   (3): Erros that cause the interruption of program
- DEBUG   (4): Detailed messages intended for the programmer
- TRACE   (5): Messages more detailed than DEBUG level. Show all log level messages

## Configuration file

Your application needs a .conf file, in this file you add the follow contents:

```shell
LOG_LEVEL = 5 # 0 to 5
COLORED_LOG_LEVEL = false # true or false
```

## Build and Install
```
$ make
# make install
```

## Examples of usage

### Example 1 - colored.c
```c
/* colored.c: Test to log library, using colored log level
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-06-16
 */

#include <stdio.h>
#include "log.h"

int main(int argc, char **argv)
{
  int iColoredLogLevel = iGetColorLogLevel("log.conf");

  if(iColoredLogLevel == 0 || iColoredLogLevel == 1)
  {
    vSetColoredLogLevel(iColoredLogLevel);
  }

  vSetLogFileName("colored.log");
  giDebugLevel = iGetLogLevel("log.conf");

  if(giDebugLevel < 0)
  {
    fprintf(stderr, "Error, giDebugLevel return value: %d!\n", giDebugLevel);

    exit(EXIT_FAILURE);
  }
  
  if(INFO_LEVEL)
  {
    vLogInfo("start %s function", __func__);
    vLogInfo("INFO Message"      );
  }

  if(WARNING_LEVEL) vLogWarning("WARNING Message");
  if(ERROR_LEVEL  ) vLogError("ERROR Message"    );
  if(FATAL_LEVEL  ) vLogFatal("FATAL Message"    );
  
  if(DEBUG_LEVEL  ) vLogDebug("%s(argc=%p, argv=%p)", __func__, &argc, &argv);
  
  if(TRACE_LEVEL  ) vLogTrace("TRACE Message");
  
  if(INFO_LEVEL)
  {
    vLogInfo("End %s function", __func__);
  }

  return 0;
}
```

### Example 2 debug.c

```c
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
```

### Example 3 - trace.c

```c
/* trace.c: Test to log library with TRACE_LEVEL
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Date: 2023-06-16
 */

#include <stdio.h>
#include "log.h"

int main(int argc, char **argv, char **envp)
{
  int ii;
  
  vSetLogFileName("trace.log");
  giDebugLevel = iGetLogLevel("log.conf");

  if(giDebugLevel < 0)
  {
    fprintf(stderr, "Error, giDebugLevel return value: %d!\n", giDebugLevel);

    exit(EXIT_FAILURE);
  }
  
  if(INFO_LEVEL)
  {
    vLogInfo("start %s function", __func__);
    vLogInfo("INFO Message"      );
  }

  if(WARNING_LEVEL) vLogWarning("WARNING Message");
  if(ERROR_LEVEL  ) vLogError("ERROR Message"    );
  if(FATAL_LEVEL  ) vLogFatal("FATAL Message"    );
  
  if(DEBUG_LEVEL  )
  {
    vLogDebug("argc = %d", argc);
    for(ii = 0; ii < argc; ii++)
    {
      vLogDebug("argv[%d] = %s", ii, argv[ii]);
    }

    for(ii = 0; envp[ii] != NULL; ii++)
    {
      vLogDebug("envp[%d] = %s", ii, envp[ii]);
    }
  }
  
  if(TRACE_LEVEL  )
  {
    vLogTrace("TRACE Message");
    vLogTrace("%s(argc=%p, argv=%p, envp=%p)", __func__, &argc, &argv, &envp);
  }

  if(INFO_LEVEL)
  {
    vLogInfo("End %s function", __func__);
  }

  return 0;
}

```

### Compile the codes

```
gcc -o colored colored.c -llog
gcc -o debug debug.c -llog
gcc -o trace trace.c -llog
```

### Uninstall

```
make uninstall
```