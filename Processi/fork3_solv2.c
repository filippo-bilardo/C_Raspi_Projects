#include <stdio.h>
#include <stdlib.h>

// Definire i prototipi delle funzioni
void childProcess(void);
void fatherProcess(int childpid);

// Definizione delle variabili globali op1,op2 e ris
int op1,op2,ris=0;

int main()
{

  int pid_processo,pide_del_padre;
  //
  // Inizializzazione delle var globali con i seguenti valori: op1=10, op2=20, ris=0
  op1=10;
  op2=10;
  //ris=0;
  // Visualizza il seguenti messaggi:
  // Prima della fork - pid processo=<getpid()>, pid del padre=<getppid()>;
  printf("\n\n[INIZIO] - Prima della fork - pid processo=%d, pid del padre=%d\n",getpid(),getppid());

  // Creazione del processo figlio
  int pid;
  pid=fork();
  if (pid==0)
  {
    // Richiamare la funzione childProcess();
    childProcess();
  }
  else if (pid>0)
  {
    // Richiamare la funzione fatherProcess(pid);
    fatherProcess(pid);

  }
  else // pid<0
  {
    printf("\nCreazione fallita!\n");
  }

  //
  // Visualizza il seguenti messaggi:
  // Termine del processo con pid=<getpid> avente pid padre=<getppid()>
  // Il risultato dell'operaziore e' ris=<ris>
  int wait_status, wait_status_high, wait_status_low;
  int wait_retvalue=wait(&wait_status);
  wait_status_high = wait_status >> 8;
  wait_status_low = wait_status & 0xFF;
  printf("[FINE] - Esito wait_retvalue=%d, wait_status_high=%d, wait_status_low=%d\n", wait_retvalue, wait_status_high, wait_status_low);
  printf("[FINE] - Termine del processo con pid=%d avente pid padre=%d\n",getpid(),getppid());
  printf("[FINE] - Il risultato dell'operaziore e' ris=%d\n",ris);

  exit(127);
}


// Definire la funzione childProcess();
void childProcess(void)
{
  // calcolo della somma tra op1 e op2
  ris=op1+op2;
  // Visualizza il seguenti messaggi:
  // [Figlio] - Il risultato della somma di op1+op2=<ris>
  printf("[Figlio] - Il risultato della somma di op1+op2=%d\n",ris);
  // [Figlio] - pid=<getpid()>, pid del processo padre=<getppid()>
  printf("[Figlio] - pid=%d, pid del processo padre=%d\n",getpid(),getppid());
}

// Definire la funzione fatherProcess(int childpid)
void fatherProcess(int childpid)
{
  // calcolo della moltiplicazione tra op1 e op2
  ris=op1*op2;
  // Visualizza il seguenti messaggi:
  // [Padre] - pid=<getpid()>, pid del processo padre=<getppid()>, pid del processo figlio=<childpid>
  printf("[Padre] - pid=%d, pid del processo padre=%d, pid del processo figlio=%d\n",getpid(),getppid(),childpid);
  // [Padre] - Il risultato della somma di op1+op2=<ris>
  printf("[Padre] - Il risultato della moltiplicazione di op1*op2=%d\n",ris);
}
