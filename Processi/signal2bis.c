/*
In questo esempio al segnale SIGNINT (CTRL-C) 
è associata un funzione (handler) che verrà eseguita alla ricezione del segnale
mentre verrà restituito un errore     
*/

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <signal.h>

void handler_signal(int signum) 
{
  if (signum == SIGINT) printf("Ricvuto il segnale SIGINT\n"); 
  exit(1);
}

int main() 
{
  if (signal(SIGINT, handler_signal) == SIG_ERR)
    perror("Non si riesce a catturare il segnale SIGINT");
  if (signal(SIGKILL, handler_signal) == SIG_ERR)
    perror("Non si riesce a catturare il segnale SIGKILL");
  if (signal(SIGSTOP, handler_signal) == SIG_ERR)
    perror("Non si riesce a catturare il segnale SIGSTOP");
  
  printf("\n\n[INIZIO]");
  //Ciclo infinito
  for(;;)
  {
    printf("\nCiclo infinito ...");
    sleep(1);
  }

  // Codice mai eseguito
  printf("\n\n[FINE]");
  exit(0);
}
