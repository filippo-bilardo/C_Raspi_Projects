/*
In questo esempio al segnale SIGNINT (CTRL-C) 
� associata un funzione (handler) che verr� eseguita alla ricezione del segnale
*/

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <signal.h>

void handler_signal(int signum) {
  printf("\n\n handler_signal - gestione dell'eccezione CTRL-C \n\n");
  if (signum == SIGINT) printf("Ricvuto il segnale SIGINT\n"); 
  exit(1);
}

int main() {
  signal(SIGINT, handler_signal);
  
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