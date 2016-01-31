#include <bcm2835.h>
#include <stdio.h>
#include "led.h"
#include "lcd.h"
#include "puls.h"

void PulsInit(void)
{
    // Set the pin to be an input
    //  with a pullup
	#ifdef PULS_D1
    bcm2835_gpio_fsel(PULS_D1, BCM2835_GPIO_FSEL_INPT);
    //bcm2835_gpio_set_pud(PULS_D1, BCM2835_GPIO_PUD_UP);
	#endif
	#ifdef PULS_D2
    bcm2835_gpio_fsel(PULS_D2, BCM2835_GPIO_FSEL_INPT);
    //bcm2835_gpio_set_pud(PULS_D2, BCM2835_GPIO_PUD_UP);
	#endif
	#ifdef PULS_D3
    bcm2835_gpio_fsel(PULS_D3, BCM2835_GPIO_FSEL_INPT);
    //bcm2835_gpio_set_pud(PULS_D3, BCM2835_GPIO_PUD_UP);
	#endif
	#ifdef PULS_D4
    bcm2835_gpio_fsel(PULS_D4, BCM2835_GPIO_FSEL_INPT);
    //bcm2835_gpio_set_pud(PULS_D4, BCM2835_GPIO_PUD_UP);
	#endif
}
uint8_t PulsGetClick(void) 
{
    #ifdef PULS_D1
    if(P1Click()) return PULS_P1;
    #endif
    #ifdef PULS_D2
    if(P2Click()) return PULS_P2;
    #endif
    #ifdef PULS_D3
    if(P3Click()) return PULS_P3;
    #endif
    #ifdef PULS_D4
    if(P4Click()) return PULS_P4;
    #endif
    return PULS_NONE;
}
uint8_t PulsGetPress(void) 
{
    #ifdef PULS_D1
    if(P1Press()) return PULS_P1;
    #endif
    #ifdef PULS_D2
    if(P2Press()) return PULS_P2;
    #endif
    #ifdef PULS_D3
    if(P3Press()) return PULS_P3;
    #endif
    #ifdef PULS_D4
    if(P4Press()) return PULS_P4;
    #endif
    return PULS_NONE;
}
uint8_t PulsGetLPress(void) 
{
    #ifdef PULS_D1
    if(P1LPress()) return PULS_P1;
    #endif
    #ifdef PULS_D2
    if(P2LPress()) return PULS_P2;
    #endif
    #ifdef PULS_D3
    if(P3LPress()) return PULS_P3;
    #endif
    #ifdef PULS_D4
    if(P4LPress()) return PULS_P4;
    #endif
    return PULS_NONE;
}

#ifdef PULS_D1
uint8_t P1Press(void) {return !bcm2835_gpio_lev(PULS_D1);}
uint8_t P1LPress(void) 
{
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P1Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_PRESS_TIME; ++cont) {
            bcm2835_delay(1);
            if(!P1Press()) return 0;
        }
        return 1;
    }
    return 0;
}
uint8_t P1LLPress(void)
{
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P1Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_LLPRESS_TIME; ++cont) {
            bcm2835_delay(1);
            if(!P1Press()) return 0;
        }
        return 1;
    }
    return 0;
}
uint8_t P1Click(void) 
{
// Timeout di 10 secondi
//
    int cont = 10000;

    // verifico che il pulsante sia stato premuto per un tempo minimo
    if(P1LPress()) {
        // aspetto che il pulsante venga rilasciato
        while(P1Press()) { 
			if(--cont == 0) break;
			bcm2835_delay(1);
		}
        return 1;
    }
    return 0;
}
#endif
#ifdef PULS_D2
uint8_t P2Press(void) {return !bcm2835_gpio_lev(PULS_D2);}
uint8_t P2LPress(void) 
{
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P2Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_PRESS_TIME; ++cont) {
            bcm2835_delay(1);
            if(!P2Press()) return 0;
        }
        return 1;
    }
    return 0;
}
uint8_t P2LLPress(void) 
{
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P2Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_LLPRESS_TIME; ++cont) {
            bcm2835_delay(1);
            if(!P2Press()) return 0;
        }
        return 1;
    }
    return 0;
}
uint8_t P2Click(void) 
{
// Timeout di 10 secondi
//
    int cont = 10000;

    // verifico che il pulsante sia stato premuto per un tempo minimo
    if(P2LPress()) {
        // aspetto che il pulsante venga rilasciato
        while(P2Press()) { 
			if(--cont == 0) break;
			bcm2835_delay(1);
		}
        return 1;
    }
    return 0;
}
#endif
#ifdef PULS_D3
uint8_t P3Press(void) {return !bcm2835_gpio_lev(PULS_D3);}
uint8_t P3LPress(void) 
{
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P3Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_PRESS_TIME; ++cont) {
            bcm2835_delay(1);
            if(!P3Press()) return 0;
        }
        return 1;
    }
    return 0;
}
uint8_t P3LLPress(void) 
{
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P3Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_LLPRESS_TIME; ++cont) {
            bcm2835_delay(1);
            if(!P3Press()) return 0;
        }
        return 1;
    }
    return 0;
}
uint8_t P3Click(void) 
{
// Timeout di 10 secondi
//
    int cont = 10000;

    // verifico che il pulsante sia stato premuto per un tempo minimo
    if(P3LPress()) {
        // aspetto che il pulsante venga rilasciato
        while(P3Press()) { 
			if(--cont == 0) break;
			bcm2835_delay(1);
		}
        return 1;
    }
    return 0;
}
#endif
#ifdef PULS_D4
uint8_t P4Press(void) {return !bcm2835_gpio_lev(PULS_D4);}
uint8_t P4LPress(void) 
{
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P4Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_PRESS_TIME; ++cont) {
            bcm2835_delay(1);
            if(!P4Press()) return 0;
        }
        return 1;
    }
    return 0;
}
uint8_t P4LLPress(void) 
{
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P4Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_LLPRESS_TIME; ++cont) {
            bcm2835_delay(1);
            if(!P4Press()) return 0;
        }
        return 1;
    }
    return 0;
}
uint8_t P4Click(void) 
{
// Timeout di 10 secondi
//
    int cont = 10000;

    // verifico che il pulsante sia stato premuto per un tempo minimo
    if(P4LPress()) {
        // aspetto che il pulsante venga rilasciato
        while(P4Press()) { 
			if(--cont == 0) break;
			bcm2835_delay(1);
		}
        return 1;
    }
    return 0;
}
#endif

int PulsTest(void)
{
	char msg[40];
 	fprintf(stdout, "Test pulsanti started...\n");
    PulsInit();

    #ifdef PULS_D1
    int p1=0;
    #endif
    #ifdef PULS_D2
    int p2=0;
    #endif
    #ifdef PULS_D3
    int p3=0;
    #endif
    #ifdef PULS_D4
    int p4=0;
    #endif
    
    #ifdef _LCD
	lcd_init();
    lcd_puts("\f Test pulsanti\nP1=5,P2=20-Fine");
    #endif
	fprintf(stdout, "	Test pulsanti, P1=5,P2=20 -> Fine\n");
    for(;;)
    {
        #ifdef PULS_D1
        if((p1==5) && (p2==20))
        {
			#ifdef _LED
			LedInit();
            LedOff();
            #endif
            #ifdef _LCD
			lcd_init();
            lcd_puts("\f      Fine      \n Test pulsanti");
            #endif
			fprintf(stdout, "	Fine test pulsanti \n");
            break;
        }
        #endif
		
        #ifdef PULS_D1
		PulsInit();
        if(P1Click())
        {
            p1++;
			fprintf(stdout, "	P1Click, p1=%d\n",p1);
            #ifdef _LCD
			lcd_init();
            sprintf(msg,"\fP1C P2P P3LP P4C\n%03u %03u  %03u %03u",p1,p2,p3,p4);
            lcd_puts(msg);
            #endif
            #ifdef LED0
			LedInit();
            LedBlink(1, 1, 50);
            #endif
        }
        #endif
		
        #ifdef PULS_D2
		PulsInit();
        if(P2LPress())
        {
            p2++;
			fprintf(stdout, "	P2LPress, p2=%d\n",p2);
            #ifdef _LCD
			lcd_init();
            sprintf(msg,"\fP1C P2P P3LP P4C\n%03u %03u  %03u %03u",p1,p2,p3,p4);
            lcd_puts(msg);
            #endif
            #ifdef LED1
			LedInit();
            LedBlink(2, 1, 50);
            #endif
        }
        #endif
		
        #ifdef PULS_D3
		PulsInit();
        if(P3LLPress()) 
        {
            p3++;
			fprintf(stdout, "	P3LLPress, p3=%d\n",p3);
            #ifdef _LCD
			lcd_init();
            sprintf(msg,"\fP1C P2P P3LP P4C\n%03u %03u  %03u %03u",p1,p2,p3,p4);
            lcd_puts(msg);
            #endif
            #ifdef LED2
			LedInit();
            LedBlink(4, 1, 50);
            #endif
		}
        #endif
		
        #ifdef PULS_D4
		PulsInit();
        if(P4Click()) {
            p4++;
			fprintf(stdout, "	P4Click p4=%d\n",p4);
            #ifdef _LCD
			lcd_init();
            sprintf(msg,"\fP1C P2P P3LP P4C\n%03u %03u  %03u %03u",p1,p2,p3,p4);
            lcd_puts(msg);
            #endif
            #ifdef LED3
			LedInit();
            LedBlink(8, 1, 50);
            #endif
        }
        #endif
    }

	fprintf(stdout, "... test pulsanti end.\n");
}
