#include <stdio.h>
#include <stdlib.h>

// Definizione delle variabili globali op1,op2 e ris

// Definiamo i prototipi delle funzioni

int main()
{
  //
  // Inizializzazione delle var globali con i seguenti valori: op1=10, op2=20, ris=0
  // Visualizza il seguenti messaggi:
  // Prima della fork - pid processo=<getpid()>, pid del padre=<getppid()>;
  //

  // Creazione del processo figlio
  int pid;
  pid=fork();
  if (pid==0)
  {
    childProcess();
  }
  else if (pid>0)
  {
    fatherProcess(pid);
  }
  else // pid<0
  {
    printf("\nCreazione fallita!\n");
  }
  
  //
  // Visualizza il seguenti messaggi:
  // Termine del processo con pid=<getpid> avente pid padre=<getppid()>
  // Il risultato dell'operaziore � ris=<ris>
  //

  exit(0);
}


int childProcess()
{
  // Visualizza il seguenti messaggi:
  // [Figlio] - pid=<getpid()>, pid del processo padre=<getppid()>
  // calcolo della somma tra op1 e op2
  // [Figlio] - Il risultato della somma di op1+op2=<ris>
}

int fatherProcess(int childpid)
{
  // Visualizza il seguenti messaggi:
  // [Padre] - pid=<getpid()>, pid del processo padre=<getppid()>, pid del processo figlio=<childpid>
  // calcolo della moltiplicazione tra op1 e op2
  // [Padre] - Il risultato della moltiplicazione di op1+op2=<ris>
}

