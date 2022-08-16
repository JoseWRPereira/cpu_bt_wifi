#include "config.h"
#include <xc.h>
#include "delay.h"
#include "lcd.h"
#include "eusart.h"
#include "error.h"

#define VETOR_SIZE  16
unsigned char vetor[VETOR_SIZE];
const unsigned char msg[] = "AT\r\n";

void main( void )
{
    lcd_init();
    eusart_init(115200);

    for( char i=0; i<VETOR_SIZE; i++ )
        vetor[i] = 0;

    lcd_print(0,0, msg );
    eusart_read( vetor, VETOR_SIZE-1 );
    eusart_print(msg);

    while( 1 )
    {
        lcd_print(1,0,vetor);

        if( error_status() )
        {
            if( error_test( RECEIVE_FRAMING_ERROR ) )
            {
                lcd_print(0,0,"Framing error");
                delay(2000);
            }

            if( error_test( RECEIVE_OVERRUN_ERROR ) )
            {
                lcd_print(0,0,"Overun error");
                delay(2000);
            }
        }
    }
}