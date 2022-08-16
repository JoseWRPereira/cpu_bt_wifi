#include <xc.h>
#include "delay.h"

void delay( unsigned int t )
{
    while( t )
    {
        __delay_ms( 1 );
        --t;
    }
}
