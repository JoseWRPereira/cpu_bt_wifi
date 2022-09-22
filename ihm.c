#include <xc.h>
#include "lcd.h"
#include "keyboard.h"
#include "tmr_tick.h"
#include "ihm.h"
#include "atcmd.h"

extern ATCMD atcmd;

void fsm_ihm_init( IHM * ptr )
{
    ptr->estado = IHM_INIT_STATE;
    ptr->tecla = 0;
    lcd_init();
    keyboard_init();
}

void fsm_ihm( IHM * ptr )
{
    ptr->tecla = keyboard_scan();

    switch( ptr->estado )
    {
        case 0:
                tmr_tick_set(IHM_TMR,1000);
                ptr->estado = 1;
                break;
        case 1:
                if( !tmr_tick(IHM_TMR) )
                    ptr->estado = 2;
                break;
        case 2:
                lcd_print(0,0,"SENAI Jandira");
                tmr_tick_set(IHM_TMR,3000);
                ptr->estado = 3;
                break;
        case 3:
                if( !tmr_tick(IHM_TMR) )
                    ptr->estado = 10;
                break;
        case 10:
                lcd_print(0,0,"Comandos AT     ");
                lcd_print(1,0,"                ");
                tmr_tick_set(IHM_TMR,3000);
                ptr->estado = 11;
                break;
        case 11:
                if( !tmr_tick(IHM_TMR) )
                    ptr->estado = 12;
                break;
        case 12:
                fsm_atcmd_com( &atcmd, "AT\r\n", "OK" );
                tmr_tick_set(IHM_TMR,3000);
                ptr->estado = 13;
                break;
        case 13:
                if( atcmd.estado == ATCMD_EOT )
                {
                    lcd_print(1,0,"OK");
                    ptr->estado = 13;
                }
                if( !tmr_tick(IHM_TMR) )
                    ptr->estado = IHM_ERROR_TIMEOUT;
                break;
        case IHM_ERROR_TIMEOUT:
                lcd_print(1,0," Timeout ATCMD  ");
                break;
        default:
                ptr->estado = IHM_ERROR;
                break;
    }
}



