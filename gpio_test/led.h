/****************************************************************************************
 Libreria:        led.h
 Versione:        1.0.0
 Autore:          Filippo Bilardo

 After installing bcm2835, you can build this with something like:
 gcc -o led -l rt led.c -l bcm2835
 sudo ./led

 Or you can test it before installing with:
 gcc -o led -l rt -I ../../src ../../src/bcm2835.c led.c
 sudo ./led

  Ver     Date        Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  1.0.0   27.12.12    First relase
****************************************************************************************/
#include <bcm2835.h>

#ifndef _LED
#define _LED

// Pin mapping
//#define LED0 RPI_V2_GPIO_P1_13
//#define LED1 RPI_V2_GPIO_P1_11
//#define LED2 RPI_V2_GPIO_P1_12
#define LED3 RPI_V2_GPIO_P1_07
//#define LED_EN RPI_V2_GPIO_P1_15

#ifdef __cplusplus
extern "C" {
#endif

extern void LedInit(void);
extern void LedOn(void);
extern void LedOff(void);
extern void LedBlink(uint8_t val, uint16_t cont, uint16_t delay);
extern void LedTest(void);
extern void LedHex(uint8_t val);
#ifdef LED0
extern void Led0On(void);
extern void Led0Off(void);
extern void Led0Toggle(void);
#endif
#ifdef LED1
extern void Led1On(void);
extern void Led1Off(void);
extern void Led1Toggle(void);
#endif
#ifdef LED2
extern void Led2On(void);
extern void Led2Off(void);
extern void Led2Toggle(void);
#endif
#ifdef LED3
extern void Led3On(void);
extern void Led3Off(void);
extern void Led3Toggle(void);
#endif

extern void LedToggleTest(void);
extern int LedTest2(void);

#ifdef __cplusplus
}
#endif

#endif //_LED