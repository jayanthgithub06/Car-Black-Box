
#include <xc.h>
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"
#include "eeprom.h"
#include "uart.h"
#include "ds1307.h"
#include "i2c_1.h"
#include "ds1307.h"

unsigned char prev_key = 0;
extern unsigned int set_back_flag=0;




void init_config(void) 
{
    init_adc();
    init_clcd();
    init_matrix_keypad();
    init_i2c();
    init_ds1307();
    init_uart();


}

void main(void) {
    init_config();
    
  
    
    while (1) 
    {
       
        key = read_switches(STATE_CHANGE);
        //        clcd_print(time, LINE2(0));

        if (key == MK_SW11 && menu_flag < 2) 
        {
            CLEAR_DISP_SCREEN;
            menu_flag++;
            if (menu_flag == 1) {
                log_flag = 0;
            } else if (menu_flag == 2) {
                log_flag = 1;
            }
//            save_time_to_rtc();
            
//            save_time_to_rtc();
//            exit_flag=0;
//            set_back_flag=1;
        }


        if (key == MK_SW12 && prev_key != MK_SW12) 
        {
            if (menu_flag > 0) 
            {
                CLEAR_DISP_SCREEN;
                menu_flag--;
                if (menu_flag == 0) 
                {
                    log_flag = 0;
                }
            }
//            save_time_to_rtc();
        }
        prev_key = key;


        if (menu_flag == 1) {
            main_menu();
        } else if (menu_flag == 2 && log_flag) {

            if (content == 0) {
                view_log();
            } else if (content == 1) {
                //                clcd_print("hello messi        ", LINE1(0));
                //                clcd_print("hi messi           ", LINE2(0));
                clear_log();
            } else if (content == 2) {
                download_log();
            } else if (content == 3) {
                //                clcd_print("hello ibra         ", LINE1(0));
                //                clcd_print("hi ibra            ", LINE2(0));
                set_time_log();
            }
        } else if (menu_flag == 0) {

            display_dashboard();
            display_gear();
        }
    }
}


