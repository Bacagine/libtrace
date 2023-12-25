/**
 * trace.c: This file contains the implementation of traceger functions
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 *
 * Date: 2023-06-16
 */

#include "trace.h"

char gszConfFileName[256];
char gszLogFileName[256];
int giDebugLevel = 1;
bool gbColoredLogLevel = false;

void vSetConfFileName(const char *kszConfFileName)
{
  if(sizeof(kszConfFileName) > sizeof(gszConfFileName))
  {
    fprintf(stderr, "E: The name of configuraation file is bigger than %d", 256);

    exit(EXIT_FAILURE);
  }
  
  snprintf(gszConfFileName, sizeof(gszConfFileName), "%s", kszConfFileName); 
}

void vSetLogFileName(const char *kszLogFileName)
{
  if(sizeof(kszLogFileName) > sizeof(gszLogFileName))
  {
    fprintf(stderr, "E: The name of trace file is bigger than %d", 256);

    exit(EXIT_FAILURE);
  }
  
  snprintf(gszLogFileName, sizeof(gszLogFileName), "%s", kszLogFileName); 
}

void vSetColoredLogLevel(bool bColored)
{
  gbColoredLogLevel = bColored;
}

void vSetLogLevel(const int kiDebugLevel)
{
  giDebugLevel = kiDebugLevel;
}

void _vTrace(const int kiDebugLevel,
             const char *kpszModuleName,
             const int kiLine, 
             const char *kpszFmt, ...)
{
  va_list args;
  FILE *fpLogFile = NULL;
  time_t tTime = time(NULL);
  struct tm *stTime = localtime(&tTime);
  char szDbg[2048];

  memset(szDbg , 0, sizeof(szDbg));

  if((fpLogFile = fopen(gszLogFileName, "a")) == NULL)
  {
    fprintf(stderr, "E: Impossible create or open file %s!\n"
                    "%s\n", gszLogFileName, strerror(errno));

    exit(EXIT_FAILURE);
  }
  
  va_start(args, kpszFmt);
  
  snprintf(szDbg, sizeof(szDbg), "%04d/%02d/%02d %02d:%02d:%02d %s:%d", stTime->tm_year + 1900, 
                                                                        stTime->tm_mon + 1, 
                                                                        stTime->tm_mday,
                                                                        stTime->tm_hour,
                                                                        stTime->tm_min,
                                                                        stTime->tm_sec,
                                                                        kpszModuleName,
                                                                        kiLine
  );

  switch(kiDebugLevel)
  {
    case INFO_LEVEL:
      if(gbColoredLogLevel)
      {
        char szLogLevel[22];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[INFO_LEVEL-1]);
        strcat(szLogLevel, kszLogLevel[INFO_LEVEL-1]);
        strcat(szLogLevel, kszLogLevelColorEnd[INFO_LEVEL-1]);
      
        strcat(szDbg, " [");
        strcat(szDbg, szLogLevel);
        strcat(szDbg, "] ");

        strcat(szDbg, kpszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }
      
      strcat(szDbg, " [");
      strcat(szDbg, kszLogLevel[INFO_LEVEL-1]);
      strcat(szDbg, "] ");

      strcat(szDbg, kpszFmt);
      strcat(szDbg, "\n");

      vfprintf(fpLogFile, szDbg, args);
      break;
    case WARNING_LEVEL:
      if(gbColoredLogLevel)
      {
        char szLogLevel[25];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[WARNING_LEVEL-1]);
        strcat(szLogLevel, kszLogLevel[WARNING_LEVEL-1]);
        strcat(szLogLevel, kszLogLevelColorEnd[WARNING_LEVEL-1]);
   
        strcat(szDbg, " [");     
        strcat(szDbg, szLogLevel);
        strcat(szDbg, "] ");

        strcat(szDbg, kpszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }

      strcat(szDbg, " [");
      strcat(szDbg, kszLogLevel[WARNING_LEVEL-1]);
      strcat(szDbg, "] ");

      strcat(szDbg, kpszFmt);
      strcat(szDbg, "\n");

      vfprintf(fpLogFile, szDbg, args);
      break;
    case ERROR_LEVEL:
      if(gbColoredLogLevel)
      {
        char szLogLevel[23];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[ERROR_LEVEL-1]);
        strcat(szLogLevel, kszLogLevel[ERROR_LEVEL-1]);
        strcat(szLogLevel, kszLogLevelColorEnd[ERROR_LEVEL-1]);

        strcat(szDbg, " [");
        strcat(szDbg, szLogLevel);
        strcat(szDbg, "] ");

        strcat(szDbg, kpszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }

      strcat(szDbg, " [");
      strcat(szDbg, kszLogLevel[ERROR_LEVEL-1]);
      strcat(szDbg, "] ");

      strcat(szDbg, kpszFmt);
      strcat(szDbg, "\n");

      vfprintf(fpLogFile, szDbg, args);
      break;
    case FATAL_LEVEL:
      if(gbColoredLogLevel)
      {
        char szLogLevel[23];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[FATAL_LEVEL-1]);
        strcat(szLogLevel, kszLogLevel[FATAL_LEVEL-1]);
        strcat(szLogLevel, kszLogLevelColorEnd[FATAL_LEVEL-1]);

        strcat(szDbg, " [");
        strcat(szDbg, szLogLevel);
        strcat(szDbg, "] ");

        strcat(szDbg, kpszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }

      strcat(szDbg, " [");
      strcat(szDbg, kszLogLevel[FATAL_LEVEL-1]);
      strcat(szDbg, "] ");

      strcat(szDbg, kpszFmt);
      strcat(szDbg, "\n");

      vfprintf(fpLogFile, szDbg, args);
      break;
    case DEBUG_LEVEL:
      if(gbColoredLogLevel)
      {
        char szLogLevel[23];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[DEBUG_LEVEL-1]);
        strcat(szLogLevel, kszLogLevel[DEBUG_LEVEL-1]);
        strcat(szLogLevel, kszLogLevelColorEnd[DEBUG_LEVEL-1]);

        strcat(szDbg, " [");
        strcat(szDbg, szLogLevel);
        strcat(szDbg, "] ");

        strcat(szDbg, kpszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }

      strcat(szDbg, " [");
      strcat(szDbg, kszLogLevel[DEBUG_LEVEL-1]);
      strcat(szDbg, "] ");

      strcat(szDbg, kpszFmt);
      strcat(szDbg, "\n");

      vfprintf(fpLogFile, szDbg, args);
      break;
    case TRACE_LEVEL:
      if(gbColoredLogLevel)
      {
        char szLogLevel[23];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[TRACE_LEVEL-1]);
        strcat(szLogLevel, kszLogLevel[TRACE_LEVEL-1]);
        strcat(szLogLevel, kszLogLevelColorEnd[TRACE_LEVEL-1]);

        strcat(szDbg, " [");
        strcat(szDbg, szLogLevel);
        strcat(szDbg, "] ");

        strcat(szDbg, kpszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }

      strcat(szDbg, " [");
      strcat(szDbg, kszLogLevel[TRACE_LEVEL-1]);
      strcat(szDbg, "] ");
      
      strcat(szDbg, kpszFmt);
      strcat(szDbg, "\n");

      vfprintf(fpLogFile, szDbg, args);
      break;
    default:
      break;
  }

  va_end(args);

  fclose(fpLogFile);
  fpLogFile = NULL;
}

int iGetLogLevel(void)
{
  FILE *fpLogConfFile = NULL;
  int iDebugLevel = -1;
  char szLine[256];
  int iLineLen = sizeof(szLine);

  /* Used to verify if the LOG_LEVEL 
   * variable is found in .conf file */
  bool bFoundLogLevel = false;
  
  char *pToken = NULL;
  int ii = 0;
  char szLevel[2];
  
  memset(szLine, 0, iLineLen);
  memset(szLevel, 0, sizeof(szLevel));

  /* Try open .conf file */
  if((fpLogConfFile = fopen(gszConfFileName, "r")) == NULL)
  {
    fprintf(stderr, "E: %s %s\n", gszConfFileName, strerror(errno));

    return -1;
  }

  while(fgets(szLine, iLineLen, fpLogConfFile) != NULL)
  {
    /* Ignore commented szLines */
    if(strstr(szLine, "#")) continue;
    pToken = strtok(szLine, " = ");
    
    if(strstr(szLine, "LOG_LEVEL"))
    {
      bFoundLogLevel = true;
      
      while(pToken != NULL)
      {
        /* Getting the value after '=' 
         * symbol and converting form 
         * string to char
         */
        if(ii == 1)
        {
          /* Verify if have a value after '=' symbol */
          if(!strcmp(pToken, "") || !strcmp(pToken, " ") || !strcmp(pToken, "\n"))
          {
            fprintf(stderr, "E: LOG_LEVEL is empty in file %s!\n", gszConfFileName);
            
            fclose(fpLogConfFile);
            fpLogConfFile = NULL;
            
            return -2;
          }

          snprintf(szLevel, sizeof(szLevel), "%s", pToken);
          iDebugLevel = atoi(szLevel);
          
          break;
        }
        pToken = strtok(NULL, " = ");

        ii++;
      }

      break;
    }
    else
    {
      continue;
    }
  }

  /* If don't found the LOG_LEVEL 
   * variable in file print a error 
   * message to user */
  if(bFoundLogLevel == false)
  {
    fprintf(stderr, "E: Not found variable LOG_LEVEL in file %s!\n", gszConfFileName);
        
    fclose(fpLogConfFile);
    fpLogConfFile = NULL;

    return -3;
  }
  
  /* If LOG_LEVEL in file is incorret */
  if(iDebugLevel < 0 || iDebugLevel > 5)
  {
    fprintf(stderr, "E: Invalid value of trace level in file %s!\n", gszConfFileName);
        
    fclose(fpLogConfFile);
    fpLogConfFile = NULL;

    return -4;
  }

  fclose(fpLogConfFile);
  fpLogConfFile = NULL;

  return iDebugLevel;
}

int iGetColoredLogLevel(void)
{
  FILE *fpLogConfFile = NULL;
  char szLine[256];
  int iLineLen = sizeof(szLine);

  /* Used to verify if the COLORED_LOG_LEVEL 
   * variable is found in .conf file */
  bool bFoundColoredLogLevel = false;
  
  char *pToken = NULL;
  int ii = 0;
  char szBool[6]; /* Receive true or false */
  int iReturnValue = false;

  memset(szLine, 0, iLineLen);
  memset(szBool, 0, sizeof(szBool));

  /* Try open .conf file */
  if((fpLogConfFile = fopen(gszConfFileName, "r")) == NULL)
  {
    fprintf(stderr, "E: %s %s\n", gszConfFileName, strerror(errno));

    return -1;
  }

  while(fgets(szLine, iLineLen, fpLogConfFile) != NULL)
  {
    /* Ignore commented szLines */
    if(strstr(szLine, "#")) continue;
    pToken = strtok(szLine, " = ");
    
    if(strstr(szLine, "COLORED_LOG_LEVEL"))
    {
      bFoundColoredLogLevel = true;
      
      while(pToken != NULL)
      {
        /* Getting the value after '=' 
         * symbol and converting form 
         * string to char
         */
        if(ii == 1)
        {
          /* Verify if have a value after '=' symbol */
          if(!strcmp(pToken, "") || !strcmp(pToken, " ") || !strcmp(pToken, "\n"))
          {
            fprintf(stderr, "E: COLORED_LOG_LEVEL is empty in file %s!\n", gszConfFileName);
            
            fclose(fpLogConfFile);
            fpLogConfFile = NULL;
            
            return -2;
          }

          snprintf(szBool, sizeof(szBool), "%s", pToken);
          szBool[strcspn(szBool, "\n")] = 0;
          
          break;
        }
        pToken = strtok(NULL, " = ");

        ii++;
      }

      break;
    }
    else
    {
      continue;
    }
  }

  /* If don't found the LOG_LEVEL 
   * variable in file print a error 
   * message to user */
  if(bFoundColoredLogLevel == false)
  {
    fprintf(stderr, "E: Not found variable COLORED_LOG_LEVEL in file %s!\n", gszConfFileName);
        
    fclose(fpLogConfFile);
    fpLogConfFile = NULL;

    return -3;
  }
  
  /* If COLORED_LOG_LEVEL in file is incorret */
  if(!strcmp(szBool, "true") || !strcmp(szBool, "TRUE"))
  {
    iReturnValue = 1;
  }
  else if(!strcmp(szBool, "false") || !strcmp(szBool, "FALSE"))
  {
    iReturnValue = 0;
  }
  else
  {
    fprintf(stderr, "E: Invalid value of colored trace level in file %s!\n", gszConfFileName);

    iReturnValue = -4;
  }

  fclose(fpLogConfFile);
  fpLogConfFile = NULL;

  return iReturnValue;
}

