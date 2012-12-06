#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

void printPID(int pid, char token)
{
  struct proc
  {
    int ppid;
    char filename[256];
    int tty_nr;
    int owner;
    unsigned long cuptime;
    unsigned long cstime;
  }p;
  
  FILE *stat;
  char command[256];
  sprintf(command, "/proc/%d/stat", pid);
  
  stat = fopen(command, "r");
  
  if (!stat) 
    {
      perror("fopen");
      return;
    }
  
  fscanf(stat,"%d %s %*c %*d %*d %d %d %*ld %*ld %*ld %*ld %*ld %*ld %lu %lu ", &p.ppid, &p.filename, &p.owner,&p.tty_nr, &p.cuptime, &p.cstime);
  if (token!='A')
    {
      int myID =(int)getpid();
      if (p.owner != myID)
	{
	  fclose(stat);
	  return;
	}
    }
  
  unsigned long time = (p.cuptime + p.cstime)/sysconf(_SC_CLK_TCK);
  unsigned char minutes = time;
  unsigned char hours = 0;
  unsigned char days = 0;
  unsigned int terminal = p.tty_nr;
  unsigned int terminalNo = terminal & 0xFF;
  terminal = terminal >> 8;
  char tty[6];
  if (terminal == 4)
    {
      sprintf(tty, "tty%d ", terminalNo);
    }
  else if (terminal == 136)
    {
      sprintf(tty, "pts/%d", terminalNo);
    }
  else
    {
      sprintf(tty, "?");
    }
  
  while (minutes>60)
    {
      minutes-=60;
      hours ++;
      if (hours==24)
	{
	  days++;
	  hours = 0;
	}
    }
  unsigned char loop;
  p.filename[0]=' ';
  for (loop=0;loop<255;loop++)
    {
      if (p.filename[loop]==')')p.filename[loop]=' ';
    }    
  
  printf("\n %d\t%s\t%02d:%02d:%02d%s",p.ppid, tty, days, hours, minutes, p.filename);
  fclose(stat);
  
  return;
}


void ps (char token)
{
  printf(" PID\tTTY\tTIME CMD");
  DIR *directory;
  struct dirent *dirp;

  if ((directory = opendir ("/proc"))==NULL) 
    {
      perror("opendir");
      return;
    }
  
  while ((dirp = readdir(directory))!=NULL)
    {
     
      if (isdigit(dirp->d_name[0]))
	{
	  printPID(atoi(dirp->d_name), token);
	}
    }
  

  closedir(directory);
  printf("\n");
  return;
}

