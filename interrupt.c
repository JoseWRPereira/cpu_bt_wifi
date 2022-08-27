
#include <xc.h>
#include "eusart.h"
#include "error.h"

void __interrupt() isr(void)
{
    if( PIR1bits.RCIF && PIE1bits.RCIE )
    {
        // if( RCSTAbits.FERR )
        // {
        //     error_set(RECEIVE_FRAMING_ERROR);
        // } 
        // else if( RCSTAbits.OERR )
        // {
        //     error_set(RECEIVE_OVERRUN_ERROR);
        // }
        // else 
        {
            eusart_reading( RCREG );
        }
    }
    if( PIR1bits.TXIF && PIE1bits.TXIE )
    {
        eusart_printing();
    }
}