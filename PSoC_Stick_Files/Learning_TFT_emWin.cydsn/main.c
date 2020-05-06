/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include "GUI.h"
#include "tft.h"

void MainTask(void);
inline void counter(int* i, int max, int digits);
// Screen size for TFT 35628MP from MPJA, 240x320
int SCREEN_X; // 240
int SCREEN_Y; // 320
char print[100];

int main()
{
    CyGlobalIntEnable;                      // Enable global interrupts
    SPIM_1_Start();                         // initialize SPIM component 
    MainTask();                             // all of the emWin exmples use MainTask() as the entry point
    for(;;) {}                              // loop
}

void MainTask()
{
    GUI_Init();                             // initilize graphics library
    GUI_Clear();
    SCREEN_X = GUI_GetScreenSizeX();
    SCREEN_Y = GUI_GetScreenSizeY();
    int i = 0;
    int *iptr = &i;
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispString("Hello world!");
    while(1) {
         counter(iptr, 9999, 4);
     }
}

inline void counter(int* iptr, int max, int digits) {
    GUI_DispDecAt( (*iptr)++, 20,20,digits);
            if (*iptr > max) {
            *iptr = 0;
         }
}
/* [] END OF FILE */
