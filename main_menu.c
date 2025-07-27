#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"
#include "eeprom.h"
#include <xc.h>

//extern int mm_index;

void main_menu(void)
{
    if((key==MK_SW2 && mm_index<2) && (star==1))
    {
        CLEAR_DISP_SCREEN;
        mm_index++;
        
    }
    
    if(key==MK_SW2 && content<3)
    {
        star=1;
        content++;
        
    }
    
    if((key==MK_SW1 && mm_index>0) && (star==0))
    {
        CLEAR_DISP_SCREEN;
        mm_index--;
        
    }
    
    if(key==MK_SW1 && content>0)
    {
        star=0;
        content--;
    }
    
    if(star==0)
    {
        clcd_putch('*',LINE1(0));
        clcd_putch(' ',LINE2(0));
    }
    else if(star==1)
    {
        clcd_putch(' ',LINE1(0));
        clcd_putch('*',LINE2(0));
    }
    
    clcd_print(menu[mm_index],LINE1(2));
    clcd_print(menu[mm_index+1],LINE2(2));   
    
}
//void main_menu(void) {
//    if (key == MK_SW2) {
//        if (mm_index < 2 && star == 1) {
//            CLEAR_DISP_SCREEN;
//            mm_index++;
//        }
//        if (content < 3) {
//            star = 1;
//            content++;
//        }
//    }
//    
//    if (key == MK_SW1) {
//        if (mm_index > 0 && star == 0) {
//            CLEAR_DISP_SCREEN;
//            mm_index--;
//        }
//        if (content > 0) {
//            star = 0;
//            content--;
//        }
//    }
//    
//    // Ensure star state is managed properly
//    if (star == 0) {
//        clcd_putch('*', LINE1(0));
//        clcd_putch(' ', LINE2(0));
//    } else if (star == 1) {
//        clcd_putch(' ', LINE1(0));
//        clcd_putch('*', LINE2(0));
//    }
//
//    // Ensure proper menu display based on mm_index
//    if (mm_index == 0 && content == 0) {
//        clcd_print("Dashboard Menu", LINE1(2));
//    } else if (mm_index == 1 && content == 1) {
//        clcd_print("View Logs", LINE1(2));
//    } else {
//        clcd_print(menu[mm_index], LINE1(2));
//        clcd_print(menu[mm_index + 1], LINE2(2));
//    }
//}

//void view_log(void)
//{
//    if(key == MK_SW1 && scroll_view > 0)
//    {
//        scroll_view--;
//    }
//    else if(key==MK_SW2 && scroll_view < 9)
//    {
//        scroll_view++;
//    }
//    
//    if(storage_flag==0)
//    {
//        clcd_print("# View Log...",LINE1(0));
//        clcd_print("Log empty",LINE2(0));
//    }
//    else
//    {
//        clcd_print("# View log :",LINE1(0));
//        if(scroll_view)
//        {
//            read_event(scroll_view*10);
//        }
//        else
//        {
//            read_event(scroll_view);
//        }
//        event[0]=scroll_view+48;
//        display_event();
//    }
//}




