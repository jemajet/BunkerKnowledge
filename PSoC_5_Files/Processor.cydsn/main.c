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
#include "GUI.h"
#include "tft.h"

void MainTask(void);
inline void counter(int* i, int max, int digits);
void create_rects();
void display_stats(int word_count);
void clear_words(int word_count);

// Screen size for TFT 35628MP from MPJA, 240x320
int SCREEN_X = 240; // 240
int SCREEN_Y = 320; // 320
int MARGIN = 10;
int Y_INC = 20; // go down by 20 pixels when y is incremented
char print[100];


#define WORD_SIZE 50
#define NUM_RECTS 28
char end_command[4] = "END";

char word[WORD_SIZE];
uint8 printindex = 0;
char delimiter = '\n';
int wordindex = 0;
GUI_WRAPMODE aWm[] = { GUI_WRAPMODE_NONE, GUI_WRAPMODE_CHAR, GUI_WRAPMODE_WORD};
GUI_RECT rects[NUM_RECTS];
char words[NUM_RECTS][WORD_SIZE];
CY_ISR(RX_INT)
{
    char sent = UART_ReadRxData();
    if (sent == delimiter) {
        // end of word, display in its specified box, and clear word
        // first sent is name, then date, then alternating key, value pairs
        if (strcmp(words[printindex], end_command) == 0) { 
            // END, so go to display, printindex is number of words +1
            display_stats(printindex);
            clear_words(printindex);
            printindex = 0;
        } else {
            // This word is done, move to next word
            printindex++;
        }

        wordindex = 0;
    } else {
        // add sent to the current word
        words[printindex][wordindex] = sent; // add word
        words[printindex][wordindex+1] = '\0'; // make it a properly terminated string
        wordindex++; // prepare for next character
    }
    //LCD_1_PutChar(sent);     // RX ISR
    UART_WriteTxData(sent);
}

void main()
{	
    
	LCD_1_Start();					    // initialize lcd
	LCD_1_ClearDisplay();
    
    CyGlobalIntEnable;
    rx_int_StartEx(RX_INT);             // start RX interrupt (look for CY_ISR with RX_INT address)
                                        // for code that writes received bytes to LCD_1.
    
    UART_Start();                       // initialize UART
    UART_ClearRxBuffer();
    SPIM_1_Start();                         // initialize SPIM component     

    /*
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    CapSense_ScanEnabledWidgets();
    */
    LED_1_Write(1);
    
    MainTask();                             // all of the emWin exmples use MainTask() as the entry point
    
    for(;;) {
    
    }
}

void MainTask()
{
    GUI_Init();                             // initilize graphics library
    GUI_Clear();
    GUI_SetFont(&GUI_Font8x16);
    create_rects();
}

void create_rects() {
    int x = 0;
    int y = 0;
    uint i;
    for (i = 0; i < NUM_RECTS; i++) {

        if (i < 2) {
            GUI_RECT new_rect = {MARGIN, MARGIN+(y*Y_INC), SCREEN_X-MARGIN, MARGIN+((y+1)*Y_INC)};

            rects[i] = new_rect;

            y++;
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
                y++;
            }
            x ^= 1; // toggle the side for the next one
        }
    }

}

void display_stats(int word_count) {
    // displays the first display_count things in words
    // expects rects and words to be filled
    GUI_Clear();
    int i;
    for (i = 0; i < word_count; i++) {
        GUI_DispStringInRectWrap(words[i], &rects[i], GUI_TA_CENTER, GUI_WRAPMODE_WORD);
    }
}

void clear_words(int word_count) {
    int i;
    for (i = 0; i < word_count; i++) {
        memset(words[i], 0, WORD_SIZE);   
    }
}
/* [] END OF FILE */