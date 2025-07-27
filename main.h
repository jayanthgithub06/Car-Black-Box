
#ifndef MAIN_H
#define	MAIN_H

#define EVENT_PAGE_SIZE 10
#define MAX_LOG_SIZE    100
#define EVENT_SIZE 10


unsigned char gear[9][3] = {"ON", "GN", "GR", "G1", "G2", "G3", "G4", "G5","C "};

unsigned short speed;
int flag=0;
unsigned char menu[15][50] = {"View Log              ","Clear Log          ","Download Log            ","Set Time             "};
int star=0;
unsigned char time[10];
//unsigned char event[50];
unsigned int n_event;
unsigned char ptr[10][16];
unsigned char uart_display[10][16];

int content=0;
int gear_index;
int mm_index=0;
unsigned int write_address=0;
int event_count=0;

int store_event_flag=0;
int log_flag=0;

//unsigned char time[][]={};
int menu_flag;

//int store_flag;
//int index=0;
//int start=0;
//int end=0;

//int scroll_view=0;

//int storage_flag=0;
//unsigned int address=0x00;


unsigned char clock_reg[10];
//unsigned char time[10];
unsigned char store_time[10];
unsigned char date[20];


unsigned int time_event_flag=1;
unsigned int first_time = 0;


//unsigned char event[100];


unsigned char key;


void display_dashboard(void);

void display_gear(void);

void collision(void);
void main_menu(void);
void display(void);
void store_data(void);
void view_log(void);
void read_event(unsigned int scroll_add);
void view_log(void);
void display_event(void);
void view_data(void);
void address_overwrite(void);
void download_log(void);
void save_time_to_rtc(void); 
void clear_log(void);
void set_time_log(void);
void static get_time(void);

//void debug_read_data(void); 

#endif	/* MAIN_H */

