#include <xc.h>
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"
#include "eeprom.h"
#include "ds1307.h"
#include "external_eeprom.h"

extern unsigned int count_event_flag;
extern int count_event;
unsigned char new_flag=1,view_flag=1;
unsigned char read_addr=0x00;
unsigned int read_count=0;
extern int store_flag;



unsigned int set_back_flag=0;

unsigned static start,end;

//unsigned static int delay=0;
//unsigned static int one_time_flag=1;
//unsigned static int hour=0,min=0,sec=0;
//unsigned static int exit_flag = 1;
//unsigned char time_data_hour,time_data_min,time_data_sec,set_time[20];



unsigned char time_data_hour,time_data_min,time_data_sec;

unsigned int Hour_key,Min_key,Sec_key;



void store_data(void) 
{
    
    store_event_flag = 1;
    
    if(event_count++>=10)
    {
        event_count=10;
        address_overwrite();
    }
    
    for (int i = 0; i < 10; i++) 
    {

        if (i < 6) 
        {
            write_external_eeprom(write_address,store_time[i]);

        } 
        else if (i < 8) 
        {
            if (i == 6) 
            {
                write_external_eeprom(write_address, gear[gear_index][0]);

            } 
            else 
            {
                write_external_eeprom(write_address, gear[gear_index][1]);
            }
        }
        else 
        {
            if (i == 8) 
            {
                write_external_eeprom(write_address, (speed / 10) + 48);
            } 
            else 
            {
                write_external_eeprom(write_address, (speed % 10) + 48);
            }
        }
        write_address++;
        
    }
    if(write_address > 99)
        write_address = 90;
}

void address_overwrite(void)
{
    unsigned char ch;
    int k=10;
    for(int i=0;i<90;i++)
    {
        ch=read_external_eeprom(k);
        write_external_eeprom(i,ch);
        k++;
    }
}

void view_log(void)
{
    unsigned static int once = 1;
    if(store_event_flag == 0)
    {
        CLEAR_DISP_SCREEN;
        clcd_print("NO LOGS TO ",LINE1(2));
        clcd_print("DISPLAY",LINE2(6));
        
        for(unsigned long int wait=500000; wait--;);
        log_flag=0;
        menu_flag=1;
        CLEAR_DISP_SCREEN;
        
    }
    else
    {
        unsigned char event[100];
        unsigned static start,end;
        if(store_event_flag && once)
        {
            once=0;
            start=0;
            end=10;
        }
        int k=0;
        for(int i=start;i<end;i++)
        {
            if((i%10) == 2 || (i%10) == 4)
            {
                event[k++] = ':';
                event[k++]=read_external_eeprom(i);
                
            }
            else if((i%10) == 6 || (i%10) == 8)
            {
                event[k++] = ' ';
                event[k++]=read_external_eeprom(i);
            }
            else
                event[k++]=read_external_eeprom(i);
        }
        event[k]='\0';
       
        static int count=0;
        
        if(key==MK_SW1)
        {
            if(start>0)
            {
                start-=10;
                end-=10;
                if(count>0)
                    count--;
            }
        }
        else if(key==MK_SW2)
        {
            if(start < ((event_count -1) * 10))
            {
                start+=10;
                end+=10;
                if(count<9)
                    count++;
            }
        }
        
        clcd_print("# View log :",LINE1(0));
        clcd_putch(count+48,LINE2(0));
        clcd_print(event,LINE2(2));
    }
}



void download_log(void)
{
    

    if(store_event_flag == 0)
    {
        clcd_print("DOWNLOAD LOG",LINE1(0));
        clcd_print("NO LOGS",LINE2(0));
        
        for(unsigned int block=10000000;block--;);
        log_flag=0;
        menu_flag=1;
        CLEAR_DISP_SCREEN;
        
    }
    else
    {
        
        clcd_print("DOWNLODING LOGS",LINE1(0));
        for(int wait=50000;wait--;);
        clcd_print("DOWNLOAD LOGS COMPLETED",LINE1(0));
        CLEAR_DISP_SCREEN;
        
        unsigned int start=0,end=10;
        for(int j=0;j<event_count;j++)
        {
            int k=0;
            for(int i=start;i<end;i++)
            {
                if((i%10)==2 || (i%10)==4)
                {
                    uart_display[j][k++]=':';
                    uart_display[j][k++]=read_external_eeprom(i);
                    
                }
                else if((i%10)==6 || (i%10)==8)
                {
                    uart_display[j][k++]=' ';
                    uart_display[j][k++]=read_external_eeprom(i);
                }
                else
                {
                    uart_display[j][k++]=read_external_eeprom(i);
                }
                
            }
            uart_display[j][k]='\0';
                start+=10;
                end+=10;
        }
             
            for(int i=0;i<event_count;i++)
            {
                puts(uart_display[i]);
                puts("\n\r");
            }
            log_flag=0;
            menu_flag=1;

    }
    

    
}



void clear_log(void) 
{
    clcd_print("CLEAR LOG:", LINE1(0));
    clcd_print("LOGS CLEARING...", LINE2(0));
    store_event_flag = 0;
    event_count = 0;
    for (unsigned long int block = 1000000; block--;);
    log_flag = 0;
    menu_flag=1;
    CLEAR_DISP_SCREEN;
}





void save_time_to_rtc(void) 
{
    time_data_hour = time_data_hour | ((Hour_key / 10) << 4);
    time_data_hour = time_data_hour | (Hour_key % 10);
    write_ds1307(HOUR_ADDR, time_data_hour);
    time_data_min = time_data_min | ((Min_key / 10) << 4);
    time_data_min = time_data_min | (Min_key % 10);
    write_ds1307(MIN_ADDR, time_data_min);
    time_data_sec = time_data_sec | ((Sec_key / 10) << 4);
    time_data_sec = time_data_sec | (Sec_key % 10);
    write_ds1307(SEC_ADDR, time_data_sec);
}

void set_time_log(void)
{
    static int time_delay = 3000;
    static int time_flag = 2;
    static int initialized = 0;
    
    if(key==MK_SW12)
    {
        flag=1;
        initialized=0;
        menu_flag=0;
    }
    if(key==MK_SW10)
    {
     
        write_ds1307(HOUR_ADDR, ((Hour_key / 10) << 4) | (Hour_key % 10));
        write_ds1307(MIN_ADDR, ((Min_key / 10) << 4) | (Min_key % 10));
        write_ds1307(SEC_ADDR, ((Sec_key / 10) << 4) | (Sec_key % 10));
        
        CLEAR_DISP_SCREEN;

  
    
        initialized=0;

        menu_flag=0;
        return;
    }
    
    if(!initialized)
    {
        Hour_key=((store_time[0] - '0')*10) + (store_time[1] - '0');
        Min_key = ((store_time[2] - '0') * 10) + (store_time[3] - '0');
        Sec_key = ((store_time[4] - '0') * 10) + (store_time[5] - '0');
        initialized = 1;
    }
    
    clcd_print("HH:MM:SS", LINE1(0));
    clcd_putch('0' + Hour_key / 10, LINE2(0));
    clcd_putch('0' + Hour_key % 10, LINE2(1));
    clcd_putch(':', LINE2(2));
    clcd_putch('0' + Min_key / 10, LINE2(3));
    clcd_putch('0' + Min_key % 10, LINE2(4));
    clcd_putch(':', LINE2(5));
    clcd_putch('0' + Sec_key / 10, LINE2(6));
    clcd_putch('0' + Sec_key % 10, LINE2(7));
    
    if (time_flag == 0 && (time_delay > 1000)) 
    {
        clcd_putch(' ', LINE2(0));
        clcd_putch(' ', LINE2(1));
    } 
    else if (time_flag == 1 && (time_delay > 1000)) 
    {
        clcd_putch(' ', LINE2(3));
        clcd_putch(' ', LINE2(4));
    } 
    else if (time_flag == 2 && (time_delay > 1000)) 
    {
        clcd_putch(' ', LINE2(6));
        clcd_putch(' ', LINE2(7));
    }
    
     if (key == MK_SW1) 
    {
        if (time_flag == 0) {
            Hour_key = (Hour_key+1)%24;
        } else if (time_flag == 1) {
            Min_key = (Min_key + 1) % 60;
        } else if (time_flag == 2) {
            Sec_key = (Sec_key + 1) % 60;
        }
    }

    if (key == MK_SW2) 
    {
        time_flag = (time_flag + 1) % 3;
        //time_delay = 3000;
    }

    time_delay -= 10;
    if (time_delay <= 0) 
    {
        time_delay = 3000;
    }
}





    
