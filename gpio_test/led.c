#include <bcm2835.h>
#include <stdio.h>
#include "led.h"

void LedInit(void)
{
    // Set the pin to be an output
    #ifdef LED0
    bcm2835_gpio_fsel(LED0, BCM2835_GPIO_FSEL_OUTP);
    #endif
    #ifdef LED1
    bcm2835_gpio_fsel(LED1, BCM2835_GPIO_FSEL_OUTP);
    #endif
    #ifdef LED2
    bcm2835_gpio_fsel(LED2, BCM2835_GPIO_FSEL_OUTP);
    #endif
    #ifdef LED3
    bcm2835_gpio_fsel(LED3, BCM2835_GPIO_FSEL_OUTP);
    #endif
    #ifdef LED_EN
    bcm2835_gpio_fsel(LED_EN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(LED_EN, HIGH);
    #endif
}
void LedOn(void)
{
    #ifdef LED0
    Led0On();
    #endif
    #ifdef LED1
    Led1On();
    #endif
    #ifdef LED2
    Led2On();
    #endif
    #ifdef LED3
    Led3On();
    #endif
}
void LedOff(void)
{
    #ifdef LED0
    Led0Off();
    #endif
    #ifdef LED1
    Led1Off();
    #endif
    #ifdef LED2
    Led2Off();
    #endif
    #ifdef LED3
    Led3Off();
    #endif
}
void LedBlink(uint8_t val, uint16_t cont, uint16_t delay)
{
    uint8_t i;
    for(i=0;i<cont;++i) 
    {
        LedHex(val);
        bcm2835_delay(delay);
        LedOff();
        bcm2835_delay(delay);
    }
}
void LedTest(void)
{
    uint8_t i;
    LedBlink(0xFF,3,50);
    for(i=0; i<4; ++i) {LedHex(2 << i); bcm2835_delay(100);}
    for(i=1; i<4; ++i) {LedHex(8 >> i); bcm2835_delay(100);}
    LedOff();
}
void LedHex(uint8_t val)
{
    #ifdef LED0
    if((val&0x01) == 0x01) Led0On(); else Led0Off();
    #endif
    #ifdef LED1
    if((val&0x02) == 0x02) Led1On(); else Led1Off();
    #endif
    #ifdef LED2
    if((val&0x04) == 0x04) Led2On(); else Led2Off();
    #endif
    #ifdef LED3
    if((val&0x08) == 0x08) Led3On(); else Led3Off();
    #endif
    #ifdef LED4
    if((val&0x10) == 0x10) Led4On(); else Led4Off();
    #endif
    #ifdef LED5
    if((val&0x20) == 0x20) Led5On(); else Led5Off();
    #endif
    #ifdef LED6
    if((val&0x40) == 0x40) Led6On(); else Led6Off();
    #endif
    #ifdef LED7
    if((val&0x80) == 0x80) Led7On(); else Led7Off();
    #endif
}
#ifdef LED0
void Led0On(void) {bcm2835_gpio_write(LED0, HIGH);}
void Led0Off(void) {bcm2835_gpio_write(LED0, LOW);}
void Led0Toggle(void) {if (bcm2835_gpio_lev(LED0)==HIGH) Led0Off(); else Led0On();}
#endif
#ifdef LED1
void Led1On(void) {bcm2835_gpio_write(LED1, HIGH);}
void Led1Off(void) {bcm2835_gpio_write(LED1, LOW);}
void Led1Toggle(void) {if (bcm2835_gpio_lev(LED1)==HIGH) Led1Off(); else Led1On();}
#endif
#ifdef LED2
void Led2On(void) {bcm2835_gpio_write(LED2, HIGH);}
void Led2Off(void) {bcm2835_gpio_write(LED2, LOW);}
void Led2Toggle(void) {if (bcm2835_gpio_lev(LED2)==HIGH) Led2Off(); else Led2On();}
#endif
#ifdef LED3
void Led3On(void) {bcm2835_gpio_write(LED3, HIGH);}
void Led3Off(void) {bcm2835_gpio_write(LED3, LOW);}
void Led3Toggle(void) {if (bcm2835_gpio_lev(LED3)==HIGH) Led3Off(); else Led3On();}
#endif
void LedToggleTest(void) 
{
    #ifdef LED0
    Led0Toggle(); bcm2835_delay(100); 
    Led0Toggle(); bcm2835_delay(100); 
    Led0Toggle(); bcm2835_delay(100); 
    Led0Toggle(); bcm2835_delay(100); 
    #endif
    #ifdef LED1
    Led1Toggle(); bcm2835_delay(100);
    Led1Toggle(); bcm2835_delay(100);
    Led1Toggle(); bcm2835_delay(100);
    Led1Toggle(); bcm2835_delay(100);
    #endif
    #ifdef LED2
    Led2Toggle(); bcm2835_delay(100);
    Led2Toggle(); bcm2835_delay(100);
    Led2Toggle(); bcm2835_delay(100);
    Led2Toggle(); bcm2835_delay(100);
    #endif
    #ifdef LED3
    Led3Toggle(); bcm2835_delay(100);
    Led3Toggle(); bcm2835_delay(100);
    Led3Toggle(); bcm2835_delay(100);
    Led3Toggle(); bcm2835_delay(100);
    #endif
}

int LedTest2(void)
{
    fprintf(stdout, "Test led started...\n");

    LedToggleTest();
    LedInit();
    LedTest();
    LedBlink(0xFF,2,500);

    fprintf(stdout, "... test led end.\n");
}

