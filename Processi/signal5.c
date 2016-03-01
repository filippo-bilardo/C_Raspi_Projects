#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int);
void child1(void);
void child2(void);
void father(int childpid1,int childpid2);

int main()
{ 
  int pid1,pid2;
  pid1=fork();

  if(pid1>0)
  { 
    // Attività del padre
    pid2=fork();
    if(pid2>0)
    { 
      father(pid1,pid2);
    }
    else if(pid2==0) 
    {
      child2();
    }
    else // (pid2<0)
    {
      printf("Si e' verificato un'errore nella crazione del processo figlio2.\n");
    }
  }
  else if(pid1==0) 
  {
    child1();
  }
  else // (pid1<0)
  {
    printf("Si e' verificato un'errore nella crazione del processo figlio1.\n");
  }

}

void father(int childpid1,int childpid2)
{
    /* attività del padre..*/
    int i;
    signal(SIGCHLD,signal_handler);
    printf("\nProcesso padre=%d. Figio1=%d, Figlio2=%d - AVVIO\n\n",getpid(),childpid1,childpid2);
    for (i=0; i<10000000; i++); 
    printf("\n\nProcesso padre=%d - TERMINAZIONE\n\n",getpid());
    exit(0); 
}

void child1()
{
    /* attività del figlio1..*/
    int i;
    printf("Processo figlio1=%d - AVVIO\n",getpid());
    for (i=0; i<4000; i++);
    printf("Processo figlio1=%d - TERMINAZIONE\n",getpid());
    exit(1); 
}

void child2()
{
    /* attività del figlio2..*/
    int i;
    printf("Processo figlio2=%d - AVVIO\n",getpid());
    for (i=0; i<8000; i++); 
    printf("Processo figlio2=%d - TERMINAZIONE\n",getpid());
    exit(2); 
}

void signal_handler(int signum)
{ 
  int status;
  int pid=wait(&status);
  printf("Terminazione del processo figlio=%d stato=%d\n",pid,status>>8);
  //signal(SIGCHLD,handler);
}