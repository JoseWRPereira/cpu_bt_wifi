
#include <xc.h>
#include "eusart.h"
#include "error.h"
#include "tmr_tick.h"

void __interrupt() isr(void)
{
    if( PIR1bits.RCIF && PIE1bits.RCIE )
    {
        if( RCSTAbits.FERR )
        {
            error_set(RECEIVE_FRAMING_ERROR);
        } 
        else if( RCSTAbits.OERR )
        {
            error_set(RECEIVE_OVERRUN_ERROR);
        }
        else 
        {
            eusart_reading( RCREG );
        }
    }
    if( PIR1bits.TXIF && PIE1bits.TXIE )
    {
        eusart_printing();
    }

    if( PIR1bits.TMR1IF )
    {
        PIR1bits.TMR1IF = 0;
        tmr_tick_int();
    }
}