/*
In questo esempio viene modificato il comportamento di default
del segnale SIGINT (CTRL-C) e il programma non verrà terminato
successivamente viene ripristinato il comportamento di default
 
*/

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <signal.h>

void handler_signal_ctrlc(int signum) {
  printf("\n\nHandler_signal_ctrlc - gestione dell'eccezione CTRL-C \n\n");
  printf("Ripristino del comportamento di default\n\n");
  signal(SIGINT, SIG_DFL); /*USR1 torna a default */
  return;
}

int main() {
  signal(SIGINT, handler_signal_ctrlc);
  
  printf("\n[INIZIO]\n");
  //Ciclo infinito
  for(;;)
  {
    printf("Ciclo infinito ...\n");
    sleep(1);
  }

  // Codice mai eseguito
  printf("\n[FINE]\n");
  exit(0);
}
