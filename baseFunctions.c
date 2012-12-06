#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "ps.h"

char execute (char *input);
void cd (char *directory);
char *pwd ();
char *kill (int signal, int PID);

char execute(char *input)
{
  char *instruction, *data;

  instruction = strtok(input, " ");
  data = strtok(NULL, "\"");
  if (!data) data = strtok(NULL, " ");
    
  if (!(strcmp(instruction, "cd"))) cd(data);
  else  if (!(strcmp(instruction, "ps"))) 
    {
      char token='0';
      if (data!=NULL)
	{
	  if (!(strcmp(data, "-A")))token = 'A';
	}
      ps(token);
    }

   if (!strcmp(instruction, "pwd"))
    {
      printf("%s\n",pwd());
    }
  else if (!(strcmp(instruction, "exit")))return -1;
  return 1;
}

void cd (char *directory)
{
  if (!directory)
    {
      directory = getenv("HOME");
    }
  else if (directory[0]!='/')
    {
      char *addition = strcpy (pwd(), directory);
      directory = addition;
    }
  char result = chdir(directory);
  if (result<0)
    {
      perror("chdir");
    }
  return;
}

char *pwd ()
{
  char *currentDir = getcwd(0, PATH_MAX);
  if (!currentDir) perror("getcwd");
  else return currentDir;
  return 0;
}


char *kill (int signal, int PID)
{

  return 0;
}
