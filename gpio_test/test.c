//
// sudo gcc -o test -l rt test.c -l bcm2835 led.c puls.c lcd.c
// sudo ./test
// 
#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "led.h"
#include "lcd.h"
#include "puls.h"

char msg[40];

//------------------------------------------------------------------------------------------
void signal_callback_handler(int signum)
{
	//printf("Caught signal %d\n",signum);
	
	// Cleanup and close up stuff here
	//lcd_init();
	//sprintf(msg, "\fFB RaspBoard A10\n... Good bye ...\n");
	//lcd_puts(msg);
	printf("\n... test gpio end.\n");

	if (!bcm2835_close()) {
		fprintf(stderr, "Error! bcm2835_close() fails.\n");
		exit(1);
	}
    exit(0);
}
//------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
    // Use for testing
	//bcm2835_set_debug(1);
	// Register signal and signal handler
	signal(SIGINT, signal_callback_handler);
	

	fprintf(stdout, "Test gpio started...\n");

	if (!bcm2835_init()) {
		fprintf(stderr, "Error! bcm2835_init() fails.\n");
		exit(1);
	}
	
	//lcd_hw_init();
	//lcd_puts("\fFB RaspBoard A10\ntest gpio ...");
  LedTest2();
	//PulsTest();
	//lcd_test();

	sprintf(msg, "\fFB RaspBoard A10\n... Good bye ...\n");
	//lcd_puts(msg);
	fprintf(stdout, "... test gpio end.\n");

	if (!bcm2835_close()) {
		fprintf(stderr, "Error! bcm2835_close() fails.\n");
		exit(1);
	}
    exit(0);
}
