#include <xc.h>
#include "atcmd.h"
#include "eusart.h"
#include "fsm.h"

const char cmd_AT[] = "AT\r\n"; 

void * atcmd_init( void * p )
{
    eusart_init( (unsigned long)(*(struct fsmT *)p).arg );

    return( atcmd_send );
}

void * atcmd_send( void * p )
{
    eusart_print( cmd_AT );
    return( atcmd_wait_ok );
}

void * atcmd_wait_ok( void * p )
{
    if( eusart_size_of_rx() >= size_of_str(cmd_AT) )
    {
        if( eusart_cmp( "OK" ) )
        {
            eusart_rx_pop();
            return( atcmd_send );
        }
    }
    return( atcmd_wait_ok );
}



// void atcmd( struct atcmd_t * ptr )
// {

// }


// void atcmd_finite_state_machine_scan( struct atcmd_t * ptr )
// {
//     switch( ptr->atcmd_state )
//     {
//         case ATCMD_WAITING:
//                 break;
//         case ATCMD_START:
//                 eusart_read( ptr.rx, ATCMD_RX_SIZE );

//                 eusart_print( ptr->ptr_send );

//                 break;
//     }
// }
