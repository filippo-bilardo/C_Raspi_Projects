/*
Se non è definito nessun handler di segnale
quando il S.O. invia il segnale verrà
eseguita l'operazione di default

Provare a compilare ed eseguire il seguente 
codice.
Cosa succede se nella shell si preme CTRL-C ?
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
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