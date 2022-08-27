#include <xc.h>
#include "lcd.h"

#define KEYB_B0         PORTDbits.RD6
#define KEYB_B1         PORTDbits.RD7

void keyboard_init( void )
{
    TRISDbits.TRISD7 = 1;   // Tecla
    TRISDbits.TRISD6 = 1;   // Tecla
}

unsigned char keyb = 0, keybAnt = 0;
unsigned char keyboard_scan( void )
{
    if( !KEYB_B0 )
        keyb = '<';
    else if( !KEYB_B1 )
        keyb = '>';
    else
        keyb = 0;
    
    if( keybAnt==0 && keyb )
    {
        return( keybAnt = keyb );
    }
    else
    {
        keybAnt = keyb;
        return( 0 );
    }
}
