#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "baseFunctions.h"

#define SHELL "TISH$ "

int main()
{
  char loop = 1;
  while (loop>0)
    {
      char *input = readline(SHELL);
      add_history(input);
 
      loop = execute(input);
      free(input);
    }
  return 0;
}
