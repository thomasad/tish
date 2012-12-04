#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int main ()
{
  puts ("\nTISH - Tom's Incomplete SHell\n2012 Thomas Deacon\n");
  char *inputString = malloc (1);
  char inputChar;
  while (1)
    {
      printf("TISH$ ");
      inputChar = getchar();
      /*Reads user-input*/
      char counter=0;
      while (inputChar!='\n')
	{
	  inputString[counter]=inputChar;
	  inputChar = getchar();
	  counter++;
	  
	  char *error = realloc (inputString, counter);
	  if (error == NULL)
	    {
	      /*Can't allocate memory, exiting*/
	      free (inputString);
	      perror("realloc");
	      inputChar = EOF;
	      return -1;
	    }
	  else
	    {
	      inputString = error;
	    }
	  if (counter==PATH_MAX)
	    {
	      inputChar='\n';
	    }
	}/*Finished fetching user-input*/
      char *command = strtok(inputString, " ");
      char *parameter = strtok(NULL, "\n");
      printf ("\n%s, %s\n", command, parameter);
    }/*End of infinite loop*/
  return 0;
}
