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
#include "GUI.h"
#include "tft.h"

void MainTask(void);
inline void counter(int* i, int max, int digits);
// Screen size for TFT 35628MP from MPJA, 240x320
int SCREEN_X; // 240
int SCREEN_Y; // 320
char print[100];

uint8 x = 0;
uint8 x0 = 0;
uint8 x1 = 0;
uint8 y = 0;

uint8 get_x();
void inc_x();
void dec_x();
void reset_x();
void lcd_backspace();
void send_backspace();

#define COMMAND_SIZE 20
char command[COMMAND_SIZE];
uint8 command_index = 0;



CY_ISR(RX_INT)
{
    x = get_x();
    char sent = UART_ReadRxData();
    if (sent == 0x08 || sent == 0x7F) {
        // backspace
        lcd_backspace();
    } else if (sent == 0x0C) {
        // If clearing in putty, clear the lcd
        LCD_1_ClearDisplay();
        reset_x();
    } 
    else {
        LCD_1_Position(y, x);
        LCD_1_PutChar(sent);     // RX ISR
        inc_x();
    } 
    
    
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

    CapSense_Start();
    CapSense_InitializeAllBaselines();
    CapSense_ScanEnabledWidgets();
    uint8 button0 = 0;
    uint8 oldbutton0 = 0;
    uint8 button1 = 0;
    uint8 oldbutton1 = 0;
    LED_1_Write(1);
    
    MainTask();                             // all of the emWin exmples use MainTask() as the entry point
    int i = 0;
    int *iptr = &i;
    
    for(;;)
    

        
        if (! CapSense_IsBusy() )
            counter(iptr, 9999, 4);
		    {
                button0 = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
                button1 = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);

                if (button0 && button1) 
                {
                    // pressing both buttons clears the display
                    LCD_1_ClearDisplay();
                    reset_x();
                    UART_WriteTxData(0x0C);
                }
			    else if (button0 && button0 != oldbutton0) 
                {
                    // button 0, (5_5) switches which row you're writing on
                    y ^= 1;
                    LED_2_Write(LED_1_Read());
                    LED_1_Write(!LED_1_Read());
                        
                }
                else if (button1 && button1 != oldbutton1)
                {
                    // button 1, (5_6) is a backspace
                    lcd_backspace();
                    send_backspace();
                }
                /* Update all baselines */
                CapSense_UpdateEnabledBaselines();
                
           		/* Start scanning all enabled sensors */
            	CapSense_ScanEnabledWidgets();
                oldbutton0 = button0;
                oldbutton1 = button1;
		    }
    
   
}


void MainTask()
{
    GUI_Init();                             // initilize graphics library
    GUI_Clear();
    SCREEN_X = GUI_GetScreenSizeX();
    SCREEN_Y = GUI_GetScreenSizeY();
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispString("Hello world!");
}

inline void counter(int* iptr, int max, int digits) {
    GUI_DispDecAt( (*iptr)++, 20,20,digits);
            if (*iptr > max) {
            *iptr = 0;
         }
}

uint8 get_x() {
    if (y == 0) {
        return x0;
    } else {
        return x1;
    }
}

void inc_x() {
    if (y == 0) {
        x0++;
        x0 %= 15; // keep within bounds
    } else {
        x1++;
        x1 %= 15;
    }
}

void dec_x() {
    if (y == 0 && x0 > 0) {
        x0--;
    } else if (y == 0 && x0 == 0) {
        x0 = 14;
    } else if (y == 1 && x1 > 0) {
        x1--;
    } else if (y == 1 && x1 == 0) {
        x1 = 14;   
    }
}

void reset_x() {
    x0 = 0;
    x1 = 0;
    x = 0;
}

void lcd_backspace() {
    // clears the prior space on the LCD_1
    dec_x();
    x = get_x();
    LCD_1_Position(y, x);
    LCD_1_PutChar(' ');
    LCD_1_Position(y, x);
}
void send_backspace() {
    // sends the ASCII backspace character, space to delete
    //   then another backspace
    UART_WriteTxData(0x08);
    UART_WriteTxData(0x20);
    UART_WriteTxData(0x08);   
}

/* [] END OF FILE */