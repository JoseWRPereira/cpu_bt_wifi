#include <xc.h>
#include "atcmd.h"
#include "eusart.h"


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
                ptr->estado = 10;
                break;
        case 10:
                if( eusart_size_of_rx() >= ptr->recv_size )
                {
                    if( eusart_cmp( ptr->recv, ptr->recv_size ) )
                    {
                        ptr->estado = ATCMD_MATCH;
                    }
                    else
                    {
                        char c = eusart_rx_pop();
                        if( c == '\n' )
                            ptr->estado = ATCMD_NO_MATCH;
                    }
                }
                break;
        case ATCMD_MATCH:
                eusart_rx_pop();
                break;
        case ATCMD_NO_MATCH:
                eusart_rx_pop();
                break;
    }
}
