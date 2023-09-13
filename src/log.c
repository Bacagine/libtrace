/* log.c: This file contains the implementation of logger functions
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 *
 * Date: 2023-06-16
 */

#include "log.h"

void vSetConfFileName(const char *kszConfFileName)
{
  if(sizeof(kszConfFileName) > sizeof(gszConfFileName))
  {
    fprintf(stderr, "E: The name of configuraation file is bigger than %d", CONF_FILE_NAME_LENGTH);
    exit(EXIT_FAILURE);
  }
  
  sprintf(gszConfFileName, "%s", kszConfFileName); 
}

void vSetLogFileName(const char *kszLogFileName)
{
  if(sizeof(kszLogFileName) > sizeof(gszLogFileName))
  {
    fprintf(stderr, "E: The name of log file is bigger than %d", LOG_FILE_NAME_LENGTH);
    exit(EXIT_FAILURE);
  }
  
  sprintf(gszLogFileName, "%s", kszLogFileName); 
}

void vSetColoredLogLevel(bool bColored)
{
  gbColoredLogLevel = bColored;
}

void vLogMessage(DebugLevel usiDebugLevel,
                 const char *kszModuleName,
                 const int kiLine, 
                 const char *kszFmt, ...)
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
  
  va_start(args, kszFmt);

  switch(usiDebugLevel)
  {
    case INFO:
      if(gbColoredLogLevel)
      {
        char szLogLevel[22];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[INFO]);
        strcat(szLogLevel, kszLogLevel[INFO]);
        strcat(szLogLevel, kszLogLevelColorEnd[INFO]);

        sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                    stTime->tm_mon + 1, 
                                                                    stTime->tm_mday,
                                                                    stTime->tm_hour,
                                                                    stTime->tm_min,
                                                                    stTime->tm_sec,
                                                                    kszModuleName,
                                                                    kiLine,
                                                                    szLogLevel);
        strcat(szDbg, kszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }

      sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                  stTime->tm_mon + 1, 
                                                                  stTime->tm_mday,
                                                                  stTime->tm_hour,
                                                                  stTime->tm_min,
                                                                  stTime->tm_sec,
                                                                  kszModuleName,
                                                                  kiLine,
                                                                  kszLogLevel[INFO]);
      strcat(szDbg, kszFmt);
      strcat(szDbg, "\n");

      vfprintf(fpLogFile, szDbg, args);
      break;
    case WARNING:
      if(gbColoredLogLevel)
      {
        char szLogLevel[25];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[WARNING]);
        strcat(szLogLevel, kszLogLevel[WARNING]);
        strcat(szLogLevel, kszLogLevelColorEnd[WARNING]);

        sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                    stTime->tm_mon + 1, 
                                                                    stTime->tm_mday,
                                                                    stTime->tm_hour,
                                                                    stTime->tm_min,
                                                                    stTime->tm_sec,
                                                                    kszModuleName,
                                                                    kiLine,
                                                                    szLogLevel);
        strcat(szDbg, kszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }
      sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                  stTime->tm_mon + 1, 
                                                                  stTime->tm_mday,
                                                                  stTime->tm_hour,
                                                                  stTime->tm_min,
                                                                  stTime->tm_sec,
                                                                  kszModuleName,
                                                                  kiLine,
                                                                  kszLogLevel[WARNING]);
      strcat(szDbg, kszFmt);
      strcat(szDbg, "\n");

      vfprintf(fpLogFile, szDbg, args);
      break;
    case ERROR:
      if(gbColoredLogLevel)
      {
        char szLogLevel[23];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[ERROR]);
        strcat(szLogLevel, kszLogLevel[ERROR]);
        strcat(szLogLevel, kszLogLevelColorEnd[ERROR]);

        sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                    stTime->tm_mon + 1, 
                                                                    stTime->tm_mday,
                                                                    stTime->tm_hour,
                                                                    stTime->tm_min,
                                                                    stTime->tm_sec,
                                                                    kszModuleName,
                                                                    kiLine,
                                                                    szLogLevel);
        strcat(szDbg, kszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }

      sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                  stTime->tm_mon + 1, 
                                                                  stTime->tm_mday,
                                                                  stTime->tm_hour,
                                                                  stTime->tm_min,
                                                                  stTime->tm_sec,
                                                                  kszModuleName,
                                                                  kiLine,
                                                                  kszLogLevel[ERROR]);
      strcat(szDbg, kszFmt);
      strcat(szDbg, "\n");

      vfprintf(fpLogFile, szDbg, args);
      break;
    case FATAL:
      if(gbColoredLogLevel)
      {
        char szLogLevel[23];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[FATAL]);
        strcat(szLogLevel, kszLogLevel[FATAL]);
        strcat(szLogLevel, kszLogLevelColorEnd[FATAL]);

        sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                    stTime->tm_mon + 1, 
                                                                    stTime->tm_mday,
                                                                    stTime->tm_hour,
                                                                    stTime->tm_min,
                                                                    stTime->tm_sec,
                                                                    kszModuleName,
                                                                    kiLine,
                                                                    szLogLevel);
        strcat(szDbg, kszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }

      sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                  stTime->tm_mon + 1, 
                                                                  stTime->tm_mday,
                                                                  stTime->tm_hour,
                                                                  stTime->tm_min,
                                                                  stTime->tm_sec,
                                                                  kszModuleName,
                                                                  kiLine,
                                                                  kszLogLevel[FATAL]);
      strcat(szDbg, kszFmt);
      strcat(szDbg, "\n");

      vfprintf(fpLogFile, szDbg, args);
      break;
    case DEBUG:
      if(gbColoredLogLevel)
      {
        char szLogLevel[23];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[DEBUG]);
        strcat(szLogLevel, kszLogLevel[DEBUG]);
        strcat(szLogLevel, kszLogLevelColorEnd[DEBUG]);

        sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                    stTime->tm_mon + 1, 
                                                                    stTime->tm_mday,
                                                                    stTime->tm_hour,
                                                                    stTime->tm_min,
                                                                    stTime->tm_sec,
                                                                    kszModuleName,
                                                                    kiLine,
                                                                    szLogLevel);
        strcat(szDbg, kszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }

      sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                  stTime->tm_mon + 1, 
                                                                  stTime->tm_mday,
                                                                  stTime->tm_hour,
                                                                  stTime->tm_min,
                                                                  stTime->tm_sec,
                                                                  kszModuleName,
                                                                  kiLine,
                                                                  kszLogLevel[DEBUG]);
      strcat(szDbg, kszFmt);
      strcat(szDbg, "\n");

      vfprintf(fpLogFile, szDbg, args);
      break;
    case TRACE:
      if(gbColoredLogLevel)
      {
        char szLogLevel[23];
        
        memset(szLogLevel, 0, sizeof(szLogLevel));
        
        strcat(szLogLevel, kszLogLevelColorInit[TRACE]);
        strcat(szLogLevel, kszLogLevel[TRACE]);
        strcat(szLogLevel, kszLogLevelColorEnd[TRACE]);

        sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                    stTime->tm_mon + 1, 
                                                                    stTime->tm_mday,
                                                                    stTime->tm_hour,
                                                                    stTime->tm_min,
                                                                    stTime->tm_sec,
                                                                    kszModuleName,
                                                                    kiLine,
                                                                    szLogLevel);
        strcat(szDbg, kszFmt);
        strcat(szDbg, "\n");

        vfprintf(fpLogFile, szDbg, args);
        break;
      }

      sprintf(szDbg, "%04d/%02d/%02d %02d:%02d:%02d %s:%d [%s] ", stTime->tm_year + 1900, 
                                                                  stTime->tm_mon + 1, 
                                                                  stTime->tm_mday,
                                                                  stTime->tm_hour,
                                                                  stTime->tm_min,
                                                                  stTime->tm_sec,
                                                                  kszModuleName,
                                                                  kiLine,
                                                                  kszLogLevel[TRACE]);
      strcat(szDbg, kszFmt);
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

          sprintf(szLevel, "%s", pToken);
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
    fprintf(stderr, "E: Invalid value of log level in file %s!\n", gszConfFileName);
        
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

          sprintf(szBool, "%s", pToken);
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
    fprintf(stderr, "E: Invalid value of colored log level in file %s!\n", gszConfFileName);

    iReturnValue = -4;
  }

  fclose(fpLogConfFile);
  fpLogConfFile = NULL;

  return iReturnValue;
}

