#include <bcm2835.h>
#include <stdio.h>
#include <time.h>
#include "lcd.h"
#include "puls.h"

//------------------------------------------------------------------------------------------
void lcd_write_byte(uint8_t data, uint8_t mode) 
{
// Versione:        1.0.0
// Prima versione:  29.12.12
// Ultima modifica: 29.12.12
//
    bcm2835_gpio_write(LCD_RS, mode);
    lcd_write_nibble(data >> 4);
    lcd_write_nibble(data & 0x0F); 
}
//------------------------------------------------------------------------------------------
void lcd_write_nibble(uint8_t data) 
{
// Versione:        1.0.0
// Prima versione:  29.12.12
// Ultima modifica: 29.12.12
//  
//      _    ______________________________
//  RS  _>--<______________________________
//      _____
//  RW       \_____________________________
//                   __________________
//  E   ____________/                  \___
//      _____________                ______
//  DB  _____________>--------------<______
//
    bcm2835_gpio_write(LCD_RW,  LOW); 
    bcm2835_gpio_write(LCD_E,   LOW);
    bcm2835_gpio_write(LCD_DB7, (data>>3)&1);
    bcm2835_gpio_write(LCD_DB6, (data>>2)&1);
    bcm2835_gpio_write(LCD_DB5, (data>>1)&1);
    bcm2835_gpio_write(LCD_DB4,  data    &1); 
    bcm2835_gpio_write(LCD_E,   HIGH); 
    delay_us(1);
    bcm2835_gpio_write(LCD_E,   LOW);
    
    // Pin condivisi con i led
    bcm2835_gpio_write(LCD_DB7, 0);
    bcm2835_gpio_write(LCD_DB6, 0);
    bcm2835_gpio_write(LCD_DB5, 0);
    bcm2835_gpio_write(LCD_DB4, 0); 

    delay_us(200); // wait 160 usecs for instruction to complete 
}
//------------------------------------------------------------------------------------------
void lcd_hw_init(void) 
{
// Versione:        1.0.0
// Prima versione:  29.12.12
// Ultima modifica: 29.12.12
//
    lcd_init();
    
    delay_ms(50);     // Wait more than 15 msecs after power is applied. 
    lcd_write_nibble(0x3); delay_ms(15);     // wait 5 msecs for the instruction to complete 
    lcd_write_nibble(0x3);
    lcd_write_nibble(0x3);
    lcd_write_nibble(0x2);
    lcd_write_byte(0x28, LCD_CMD); // 0x28 = HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT
    lcd_write_byte(0x0C, LCD_CMD); // 0x0C = HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK
    lcd_write_byte(0x01, LCD_CMD); // 0x01 = HD44780_CLEAR
    lcd_write_byte(0x06, LCD_CMD); // 0x06 = HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT
}
//------------------------------------------------------------------------------------------
void lcd_init(void) 
{
// Versione:        1.0.0
// Prima versione:  29.12.12
// Ultima modifica: 29.12.12
//
    // Set the pin to be an output
    bcm2835_gpio_fsel(LCD_DB4, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LCD_DB5, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LCD_DB6, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LCD_DB7, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LCD_E,   BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LCD_RS,  BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LCD_RW,  BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_write(LCD_RS,  LOW);
    bcm2835_gpio_write(LCD_RW,  LOW);
    bcm2835_gpio_write(LCD_E,   LOW);
}
//------------------------------------------------------------------------------------------
void lcd_set_cursor(uint8_t row, uint8_t col) 
{
// Versione:        1.0.0
// Prima versione:  29.12.12
// Ultima modifica: 29.12.12
//
// row=1-2, col=1-16
// 0x40 = LCD RAM address for the second line
//  
    uint8_t address;

    if(row!=1) address=0x40; else address=0;
    address += col-1;
    lcd_write_byte(HD44780_DDRAM_SET|address, LCD_CMD);
}
//------------------------------------------------------------------------------------------
void lcd_putc(char c) 
{
// Versione:        1.0.0
// Prima versione:  19.11.07
// Ultima modifica: 29.12.12
//  
    switch (c) 
    {
        case '\0': break;
        case '\r': lcd_set_cursor(1,1); break;
        case '\n': lcd_set_cursor(2,1); break;
        case '\f': lcd_write_byte(HD44780_CLEAR, LCD_CMD); delay_ms(3); break;
        case '\b': lcd_write_byte(HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_CURSOR | HD44780_SHIFT_LEFT, LCD_CMD); break;
        default  : lcd_write_byte(c, LCD_CHR); break;
    }
}
//------------------------------------------------------------------------------------------
void lcd_puts(char *string)
{
// Versione:        1.0.0
// Prima versione:  29.12.12
// Ultima modifica: 29.12.12
//  
    while (*string) lcd_putc(*string++);
}
//------------------------------------------------------------------------------------------
int lcd_test(void)
{
    char buf[17];
    char msg[40];
    time_t curtime;
    struct tm *timeinfo;
    
    printf("Test lcd started...\n") ;
    lcd_hw_init();
    lcd_puts("\fTest LCD\nP1 - CTRL-C exit");
    delay_ms(2000);
    
    while(1)
    {
        time(&curtime);
        timeinfo = localtime(&curtime);
        strftime(buf, 17, "%b %d  %H:%M:%S\n", timeinfo);
        sprintf(msg, "\fFB RaspBoard A10\n%s",buf);
        lcd_puts(msg);
        PulsInit();
        delay_ms(330);
        if(P1Click()) break;
        delay_ms(330);
        if(P1Click()) break;
        delay_ms(330);
        if(P1Click()) break;
        lcd_init();
    }
    
    lcd_init();
    printf("... test lcd end.\n");
}
