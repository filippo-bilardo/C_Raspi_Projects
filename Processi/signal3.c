/*
In questo esempio viene modificato il comportamento di default
del segnale SIGINT (CTRL-C) e il programma non verrà mai terminato
 
$// eseguire il processo in background
$./a.out &
$// per terminare il processo 
$kill -9 <pid processo>
$// oppure 
$kill <pid processo>
$// per inviare il segnale CTRL-C al processo
$kill -SIGINT <pid processo>
*/

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <signal.h>

void handler_signal_ctrlc(int signum) {
  printf("\n\n handler_signal_ctrlc - gestione dell'eccezione CTRL-C \n\n");
  return;
}

int main() {
  signal(SIGINT, handler_signal_ctrlc);
  
  printf("\n\n[INIZIO]");
  //Ciclo infinito
  for(;;)
  {
    printf("\nCiclo infinito ...");
    sleep(5);
  }

  // Codice mai eseguito
  printf("\n\n[FINE]");
  exit(0);
}
