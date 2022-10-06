#include <xc.h>
#include "atconfig.h"
#include "fsm.h"
#include "lcd.h"
#include "tmr_tick.h"
#include "eusart.h"
#include "str.h"


#define ATCONFIG_BUF_SIZE   16
char atconfig_buf[ATCONFIG_BUF_SIZE] = {0};
FIFO atconfig_fifo = {atconfig_buf, 0,0,ATCONFIG_BUF_SIZE,0,0};


FIFO * atcfg_fifo( void )
{
    return( &atconfig_fifo );
}

char version[16] = "---------------";



void atconfig_init( void * p )
{
    lcd_print(0,0,"ATCONFIG init");
    tmr_tick_set(0,3000);
    NEXT_STATE = atconfig_init_espera;
}

void atconfig_init_espera( void * p )
{
    if( !tmr_tick(0) )
        NEXT_STATE = atconfig_msg_at;
}



void atconfig_msg_at( void * p )
{
    lcd_clr();
    eusart_print("AT\r\n");
    lcd_print(0,0,"AT");
    tmr_tick_set(0,5000);
    NEXT_STATE = atconfig_msg_at_resp;
}

void atconfig_msg_at_resp( void * p )
{
    char * str = str_search(&atconfig_fifo,"OK");
    lcd_print(1,0,  str );
    if( !tmr_tick(0) )
    {
        NEXT_STATE = atconfig_msg_ate0;
    }
}


void atconfig_msg_ate0( void * p )
{
    eusart_print("ATE0\r\n");
    lcd_print(0,0,"ATE0");
    tmr_tick_set(0,5000);
    NEXT_STATE = atconfig_msg_ate0_resp;
}

void atconfig_msg_ate0_resp( void * p )
{
    char * str = str_search(&atconfig_fifo,"OK");
    lcd_print(1,0,  str );
    if( !tmr_tick(0) )
    {
        NEXT_STATE = atconfig_msg_atgmr;
    }
}



void atconfig_msg_atgmr( void * p )
{
    eusart_print("AT+GMR\r\n");
    lcd_print(0,0,"AT+GMR");
    tmr_tick_set(0,50000);
    NEXT_STATE = atconfig_msg_atgmr_resp;
}

void atconfig_msg_atgmr_resp( void * p )
{
    str_between(&atconfig_fifo,"version:","(**", version );
    lcd_print(1,0, version );
    if( !tmr_tick(0) )
    {
        NEXT_STATE = atconfig_msg_atgmr;
    }
}

