#include <xc.h>
#include "atconfig.h"
#include "fsm.h"
#include "lcd.h"
#include "tmr_tick.h"


void atconfig_init( void * p )
{
    lcd_print(0,0,"ATCONFIG init");
    tmr_tick_set(0,3000);
    ((FSM *)p)->func = atconfig_init_espera;
}

void atconfig_init_espera( void * p )
{
    if( !tmr_tick(0) )
        NEXT_STATE = atconfig_msg0_at;
}



void atconfig_msg0_at( void * p )
{
    lcd_print(0,0,"Mensagem 0 - AT");
    tmr_tick_set(0,5000);
    NEXT_STATE = atconfig_msg0_at_delay;
}

void atconfig_msg0_at_delay( void * p )
{
    if( !tmr_tick(0) )
        NEXT_STATE = atconfig_msg1_at;
}


void atconfig_msg1_at( void * p )
{
    lcd_print(0,0,"Mensagem 1 - AT");
    tmr_tick_set(0,2000);
    NEXT_STATE = atconfig_msg1_at_delay;
}

void atconfig_msg1_at_delay( void * p )
{
    if( !tmr_tick(0) )
        NEXT_STATE = atconfig_msg0_at;
}
