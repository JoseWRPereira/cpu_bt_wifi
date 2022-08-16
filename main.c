#include "config.h"
#include <xc.h>
#include "delay.h"
#include "lcd.h"
#include "eusart.h"
#include "error.h"

extern unsigned char * eusart_rx_ptr0;
extern unsigned char * eusart_rx_ptr1;

unsigned char vetor[16];
const unsigned char msg[] = "CPU BT WiFi t9  ";
void main( void )
{
    lcd_init();
    eusart_init(115200);

    for( char i=0; i<16; i++ )
        vetor[i] = 0;
    for( char i=0; i<10; i++ )
        vetor[i] = '.';

    lcd_print(0,0, msg );
    lcd_print(1,0,"?");
    lcd_put('$');

    delay(3000);

    eusart_read( vetor, 10 );
    eusart_put('S');
    eusart_put('E');
    eusart_put('N');
    eusart_put('A');
    eusart_put('I');
    eusart_print(msg);

    while( 1 )
    {
        lcd_num(0,0, (int)eusart_rx_ptr0, 5);
        lcd_num(0,5, (int)eusart_rx_ptr1, 5);
        lcd_num(0,10, (int)&vetor[0], 5);
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