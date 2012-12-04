#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

/* void pwd
 * version 1 build 1
 * Author:        Thomas Deacon
 * Date:          14/10/12
 * Purpose:       Displays current directory
 * Modifications: None 
 * Parameters:    None */
char *pwd ()
{
  char *currentDir;
  currentDir = getcwd(0,0);
  /*Basic error checking*/
  if (currentDir == NULL)
    {
      perror("getcwd");
    }
  else
    {
      return currentDir;
    }
  return NULL;
}

/* void cd
 * Author:        Thomas Deacon
 * Date:          01/11/12
 * Purpose:       Changes current working direcotry
 * Modifications: None
 * Paramenters:   Directory to change to */
void cd (char *directory)
{
  char result;
  if (directory == NULL)
    {
      
    }
  else
    {
      result = chdir (directory);
    }
  if (result<0)
    { 
      perror("chdir");
    } 
  return;
}

char ls ()
{
  DIR *dirPointer=opendir(pwd());
  struct dirent *dirp;
  if (dirPointer==NULL)
    {
      perror("opendir");
      return -1;
    }
  while ((dirp=readdir(dirPointer))!=NULL)
    {
      printf ("%s\n", dirp->d_name);
    }
  closedir(dirPointer);
  return 0;
}

/************************************************
 *                void kill
 *        Author: Thomas Deacon
 *          Date: 16/11/12
 *       Purpose: Kills a process using given ID
 * Modifications: None
 *    Parameters: Process ID to kill
 *************************************************/
void kill (short id)
{

}
