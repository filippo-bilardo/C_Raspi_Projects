/****************************************************************************************
 Libreria:        lcd.h
 Versione:        1.0.0
 Autore:          Filippo Bilardo

 After installing bcm2835, you can build this with something like:
 gcc -o lcd -l rt lcd.c -l bcm2835
 sudo ./led

 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 
  Ver     Date        Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  1.0.0   27.12.12    First relase
****************************************************************************************/
#include <bcm2835.h>

#ifndef _LCD
#define _LCD

// LCD pins
#define LCD_DB4 RPI_V2_GPIO_P1_13
#define LCD_DB5 RPI_V2_GPIO_P1_12
#define LCD_DB6 RPI_V2_GPIO_P1_11
#define LCD_DB7 RPI_V2_GPIO_P1_07
#define LCD_E   RPI_V2_GPIO_P1_16
#define LCD_RS  RPI_V2_GPIO_P1_18
#define LCD_RW  RPI_V2_GPIO_P1_15

// COMMANDS
// Execution time for all command is 37us
//
// Clear display writes space code 20H (character pattern for character code 20H must be a blank pattern) into
// all DDRAM addresses. It then sets DDRAM address 0 into the address counter, and returns the display to
// its original status if it was shifted. In other words, the display disappears and the cursor or blinking goes to
// the left edge of the display (in the first line if 2 lines are displayed). It also sets I/D to 1 (increment mode)
// in entry mode. S of entry mode does not change.
// 0b0001 = HD44780_CLEAR
// Execution time 1.52ms
#define HD44780_CLEAR                   0x01
// Sets DDRAM address 0 in address counter. Also returns display from 
// being shifted to original position. DDRAM contents remain unchanged.
// Execution time 1.52ms
#define HD44780_HOME                    0x02
// I/D: Increments (I/D = 1) or decrements (I/D = 0) the DDRAM address by 1 when a character code is
// written into or read from DDRAM.
// The cursor or blinking moves to the right when incremented by 1 and to the left when decremented by 1.
// The same applies to writing and reading of CGRAM.
// S: Shifts the entire display either to the right (I/D = 0) or to the left (I/D = 1) when S is 1. The display does
// not shift if S is 0.
// If S is 1, it will seem as if the cursor does not move but the display does. The display does not shift when
// reading from DDRAM. Also, writing into or reading out from CGRAM does not shift the display.
// 0b0110 = HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT
#define HD44780_ENTRY_MODE              0x04
    #define HD44780_EM_SHIFT_CURSOR     0
    #define HD44780_EM_SHIFT_DISPLAY    1
    #define HD44780_EM_DECREMENT        0
    #define HD44780_EM_INCREMENT        2
// D: The display is on when D is 1 and off when D is 0. When off, the display data remains in DDRAM, but
// can be displayed instantly by setting D to 1.
// C: The cursor is displayed when C is 1 and not displayed when C is 0. Even if the cursor disappears, the
// function of I/D or other specifications will not change during display data write. The cursor is displayed
// using 5 dots in the 8th line for 5 ´ 8 dot character font selection and in the 11th line for the 5 ´ 10 dot
// character font selection.
// B: The character indicated by the cursor blinks when B is 1 (Figure 13). The blinking is displayed as
// switching between all blank dots and displayed characters at a speed of 409.6-ms intervals when fcp or fOSC
// is 250 kHz. 
// 0b1100 = HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK
#define HD44780_DISPLAY_ONOFF           0x08
    #define HD44780_DISPLAY_OFF         0
    #define HD44780_DISPLAY_ON          4
    #define HD44780_CURSOR_OFF          0
    #define HD44780_CURSOR_ON           2
    #define HD44780_CURSOR_NOBLINK      0
    #define HD44780_CURSOR_BLINK        1
// Cursor or display shift shifts the cursor position or display to the right or left without writing or reading
// display data. This function is used to correct or search the display. In a 2-line display, the cursor
// moves to the second line when it passes the 40th digit of the first line. Note that the first and second line
// displays will shift at the same time.
// When the displayed data is shifted repeatedly each line moves only horizontally. The second line display
// does not shift into the first line position.
// The address counter (AC) contents will not change if the only action performed is a display shift.
// 0b10000 = HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_CURSOR | HD44780_SHIFT_LEFT
#define HD44780_DISPLAY_CURSOR_SHIFT    0x10
    #define HD44780_SHIFT_CURSOR        0
    #define HD44780_SHIFT_DISPLAY       8
    #define HD44780_SHIFT_LEFT          0
    #define HD44780_SHIFT_RIGHT         4
// DL: Sets the interface data length. Data is sent or received in 8-bit lengths (DB7 to DB0) when DL is 1,
// and in 4-bit lengths (DB7 to DB4) when DL is 0.When 4-bit length is selected, data must be sent or
// received twice.
// N: Sets the number of display lines.
// F: Sets the character font.
// Note: Perform the function at the head of the program before executing any instructions (except for the
// read busy flag and address instruction). From this point, the function set instruction cannot be
// executed unless the interface data length is changed.
// 0x28 = HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT
#define HD44780_FUNCTION_SET            0x20
    #define HD44780_FONT5x7             0
    #define HD44780_FONT5x10            4
    #define HD44780_ONE_LINE            0
    #define HD44780_TWO_LINE            8
    #define HD44780_4_BIT               0
    #define HD44780_8_BIT               16
// Set CGRAM address sets the CGRAM address binary AAAAAA into the address counter.
// Data is then written to or read from the MPU for CGRAM.
#define HD44780_CGRAM_SET               0x40
// Set DDRAM address sets the DDRAM address binary AAAAAAA into the address counter.
// Data is then written to or read from the MPU for DDRAM.
// However, when N is 0 (1-line display), AAAAAAA can be 00H to 4FH. When N is 1 (2-line display),
// AAAAAAA can be 00H to 27H for the first line, and 40H to 67H for the second line.
#define HD44780_DDRAM_SET               0x80

// Command or Data
#define LCD_CHR     1
#define LCD_CMD     0

#define delay_ms(x) bcm2835_delay(x)
#define delay_us(x) bcm2835_delayMicroseconds(x)

void lcd_write_byte(uint8_t data, uint8_t mode);
void lcd_write_nibble(uint8_t data);
void lcd_init(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_putc(char c);
void lcd_puts(char *string);
void lcd_signal_callback_handler(int signum);
int lcd_test(void);

#endif //_LCD
