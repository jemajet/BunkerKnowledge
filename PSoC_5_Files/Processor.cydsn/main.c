/* ========================================
 *
 * Copyright MIT 6.115, 2013
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF MIT 6.115.
 *
 * This file is necessary for your project to build.
 * Please do not delete it.
 *
 * ========================================
*/

#include <device.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "GUI.h"
#include "tft.h"

// Function defintions
void MainTask(void); // Used to initialize the GUI
void create_rects(); // Creates and stores the rectangles for stat display on GUI
void display_stats(int word_count); // Displays sent stats on the GUI
void clear_data(int word_count); // Clears the word array
void color_change(char* word, char* check_word, GUI_COLOR color); // Changes the color for particular words


// Serial Port Data Processing Constants

#define MARGIN 10 // 10 from the age to look nice
#define Y_INC 20 // go down by 20 pixels when y is incremented
#define WORD_SIZE 50
#define NUM_RECTS 30 // US has 28 data points, can expand if needed

// Screen size for TFT 35628MP from MPJA, 240x320
#define SCREEN_X 240
#define SCREEN_Y 320

// New GUI Color Constants
#define WHITE   0xFFFFFF
#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF
#define CYAN    0x00FFFF
#define ORANGE  0xFF9933
#define MAGENTA 0xFF00FF
#define YELLOW  0xFFFF00

// Serial Port Data Processing variables

char end_command[4] = "END";
uint8 printindex = 0; // used to keep the index of which word we're on
char delimiter = '\n'; // this delimiter expected in the sent data
int wordindex = 0; // used to track which character of a word we're modifying
GUI_RECT rects[NUM_RECTS]; // predefined rectangles to store in
char data[NUM_RECTS][WORD_SIZE]; // stores the sent data to display

CY_ISR(RX_INT)
{
    char sent = UART_ReadRxData();
    if (sent == delimiter) {
        // end of word, store in array, print if end of sending
        // first sent is name, then date, then alternating key, value pairs
        if (strcmp(data[printindex], end_command) == 0) { 
            // END, so go to display, printindex is number of words +1
            display_stats(printindex);
            clear_data(printindex);
            printindex = 0;
        } else {
            // This word is done, move to next word
            printindex++;
        }
        wordindex = 0; // start at the beginning of next word
    } else {
        // add sent to the current word
        data[printindex][wordindex] = sent; // add to word
        data[printindex][wordindex+1] = '\0'; // make it a properly terminated string
        wordindex++; // prepare for next character
    }
    UART_WriteTxData(sent);
}

void main()
{	
    CyGlobalIntEnable;
    rx_int_StartEx(RX_INT);     // start RX interrupt (look for CY_ISR with RX_INT address)
                                // for code that writes received bytes to LCD_1.
    
    UART_Start();               // initialize UART
    UART_ClearRxBuffer();
    SPIM_1_Start();             // initialize SPIM component     

    LED_1_Write(1);
    
    MainTask();                 // all of the emWin exmples use MainTask() as the entry point
    
    for(;;) {
     // Unused for now, only interrupts
    }
}

void MainTask()
{
    GUI_Init();                             // initilize graphics library
    GUI_Clear();
    GUI_SetFont(&GUI_Font8x16);
    GUI_SetTextMode(GUI_TM_NORMAL);
    create_rects();
}

void create_rects() {
    // Creates the rectangles needed to display our data, creates two full width
    // rectangles then pairs the rest of the way down.
    int x = 0;
    int y = 0;
    uint i;
    for (i = 0; i < NUM_RECTS; i++) {
        if (i < 2) {
            // full width for name and date, aka first two rectangles
            GUI_RECT new_rect = {MARGIN, MARGIN+(y*Y_INC), SCREEN_X-MARGIN, MARGIN+((y+1)*Y_INC)};
            rects[i] = new_rect;
            y++; // go to next line
        } else {
            if (x == 0) {
                // left side
                GUI_RECT new_rect = {MARGIN, MARGIN+(y*Y_INC), (SCREEN_X-MARGIN) /2, MARGIN+((y+1)*Y_INC)};
                rects[i] = new_rect;
            } else {
                // right side
                GUI_RECT new_rect = {(SCREEN_X-MARGIN) /2, MARGIN+(y*Y_INC), SCREEN_X-MARGIN, MARGIN+((y+1)*Y_INC)};
                rects[i] = new_rect;
            }
            if (x == 1) {
                y++; // go to next line if end of this line
            }
            x ^= 1; // toggle the side for the next one
        }
    }

}

void display_stats(int word_count) {
    // displays the first display_count things in data
    // expects rects and data to be filled
    GUI_Clear();
    int i;
    for (i = 0; i < word_count; i++) {
        if (i > 1 && i % 2 == 1) {
            // check if last rectangle was a key word so the number changes color
            color_change(data[i-1], "Confirmed", RED);  
            color_change(data[i-1], "Infected", RED); 
            color_change(data[i-1], "ested", CYAN);  
            color_change(data[i-1], "Recovered", GREEN);
            color_change(data[i-1], "Active", YELLOW);

        } else {
            GUI_SetColor(WHITE);
        }
        GUI_DispStringInRectWrap(data[i], &rects[i], GUI_TA_CENTER, GUI_WRAPMODE_WORD);
    }
}
void color_change(char* word, char* check_word, GUI_COLOR color) {
    // changes color of the text if check_word is a substring of word
    if (strstr(word, check_word) != NULL) {
        GUI_SetColor(color);   
    }
}

void clear_data(int word_count) {
    // clears all the words we've used to prepare for next data send
    int i;
    for (i = 0; i < word_count; i++) {
        memset(data[i], 0, WORD_SIZE);   
    }
}




/* [] END OF FILE */