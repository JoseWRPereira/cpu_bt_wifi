#include <xc.h>
#include "atcmd.h"
#include "eusart.h"

#include "lcd.h" // Teste

void fsm_atcmd_init( ATCMD * ptr )
{
    eusart_init( 115200 );
    ptr->estado = 0;
}

void fsm_atcmd_com( ATCMD * ptr, 
                const char * str_send, 
                const char * str_recv )
{
    ptr->estado = 1;
    ptr->send = str_send;
    ptr->recv = str_recv;
    ptr->recv_size = size_of_str(ptr->recv);
}

void fsm_atcmd( ATCMD * ptr )
{
    switch( ptr->estado )
    {
        case 1:
                eusart_print( ptr->send );
                lcd_lincol(1,0);
                ptr->estado = 10;
                break;
        case 10:
                if( eusart_size_of_rx() >= ptr->recv_size )
                {
                    if( eusart_cmp( ptr->recv, ptr->recv_size ) )
                    {
                        ptr->estado = 20;
                    }
                    else
                    {
                        lcd_put( eusart_rx_pop() );
                    }
                }
                break;
        case 20:
                lcd_lincol(1,15);
                lcd_put('*');
                ptr->estado = ATCMD_EOT;
                lcd_lincol(1,0);
                break;
        case ATCMD_EOT:
                {
                    char c = eusart_rx_pop();
                    if( c )
                        lcd_put( c );
                }
                break;
    }
}
