/****************************************************************************************
 Libreria:        puls.h
 Versione:        1.0.0
 Autore:          Filippo Bilardo

 After installing bcm2835, you can build this with something like:
 gcc -o puls -l rt puls.c -l bcm2835
 sudo ./puls

 Or you can test it before installing with:
 gcc -o puls -l rt -I ../../src ../../src/bcm2835.c puls.c
 sudo ./puls

  Ver     Date        Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  1.0.0   27.12.12    First relase
****************************************************************************************/
#include <bcm2835.h>

#ifndef _PULS
#define _PULS

// Pin mapping
#define PULS_D1 RPI_V2_GPIO_P1_07
#define PULS_D2 RPI_V2_GPIO_P1_12
#define PULS_D3 RPI_V2_GPIO_P1_11
#define PULS_D4 RPI_V2_GPIO_P1_13

#define PULS_NONE           0
#define PULS_P1             1
#define PULS_P2             2
#define PULS_P3             3
#define PULS_P4             4
#define _PULS_PRESS_TIME    10      // circa 10 msec - durata minimima pressione pulsante
#define _PULS_LLPRESS_TIME  3000    // circa 3 sec - durata minimima pressione lunga pulsante

void PulsInit(void);
uint8_t PulsGetClick(void);
uint8_t PulsGetPress(void);
uint8_t PulsGetLPress(void);
int PulsTest(void);

#ifdef PULS_D1
uint8_t P1Press(void);
uint8_t P1LPress(void);
uint8_t P1LLPress(void);
uint8_t P1Click(void);
#endif
#ifdef PULS_D2
uint8_t P2Press(void);
uint8_t P2LPress(void);
uint8_t P2LLPress(void);
uint8_t P2Click(void);
#endif
#ifdef PULS_D3
uint8_t P3Press(void);
uint8_t P3LPress(void);
uint8_t P3LLPress(void);
uint8_t P3Click(void);
#endif
#ifdef PULS_D4
uint8_t P4Press(void);
uint8_t P4LPress(void);
uint8_t P4LLPress(void);
uint8_t P4Click(void);
#endif

#endif //_PULS

