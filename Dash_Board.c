#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"
#include "eeprom.h"
#include "i2c_1.h"
#include <xc.h>
#include "ds1307.h"

int pre_index=10;
int store_flag;
unsigned char address = 0x00;
int count_event=0;
unsigned int count_event_flag;

void static  get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
        store_time[0] = time[0];
        store_time[1] = time[1];
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        
        store_time[0] = time[0];
		
        time[1] = '0' + (clock_reg[0] & 0x0F);
        store_time[1] = time[1];
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
    
    store_time[2] = time[3];
    store_time[3] = time[4];
    store_time[4] = time[6];
    store_time[5] = time[7];
    store_time[6] = '\0';
}



void display_dashboard(void) 
{
    get_time();
    clcd_print(time,LINE2(0));
    clcd_print("TIME", LINE1(2));
    clcd_print("GEAR", LINE1(9));
    clcd_print("SP", LINE1(14));

}

void display_gear(void) 
{
    
    if ((key == MK_SW1 && gear_index < 7) && (flag==0))
    {
        
        gear_index++;
        
        store_data();
        
    } 
    else if ((key == MK_SW2 && gear_index > 1) && (flag==0))
    {
       
        gear_index--;
        store_data();
        
    } 
    else if (key == MK_SW3) 
    {
        gear_index = 8;
        flag=1;
        store_data();
        
    }
    else if(flag==1 && key==MK_SW1)
    {
        gear_index=1;
        flag=0;
        store_data();
        
    }
    else if(flag==1 && key==MK_SW2)
    {
        gear_index=1;
        flag=0;
        store_data();
        
    }
    
    clcd_print(gear[gear_index], LINE2(10));
    
    speed = read_adc(CHANNEL4) / 10.24;
    clcd_putch((speed / 10) % 10 + 48, LINE2(14));
    clcd_putch(speed % 10 + 48, LINE2(15));
    

}












