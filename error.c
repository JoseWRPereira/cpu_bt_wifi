#include "error.h"
#include "lcd.h"

unsigned char error = 0;

void error_set( unsigned char e )
{
    error |= e;
}
unsigned char error_test( unsigned char e )
{
    return( (error & e) != 0 );
}
unsigned char error_status( void )
{
    return( error );
}
