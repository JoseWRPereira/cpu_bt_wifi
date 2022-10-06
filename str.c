#include <xc.h>
#include "fifo.h"

unsigned char str_size( const char * ptr )
{
    unsigned char i = 0;
    while( *(ptr+i) )
    {
        ++i;
    }
    return( i );
}


unsigned char str_cmp( FIFO * fifo, const char * str2, unsigned char size )
{
    unsigned char i = 0;
    unsigned char ans = 1;

    while( size )
    {
        if( fifo->queue[((fifo->tail)+i) % fifo->size] != *(str2+i) )
        {
            ans = 0;
            size = 0;
        }
        else
        {
            --size;
        }
        ++i;
    }
    return( ans );
}

const char * str_search( FIFO * fifo, const char * str )
{
    char size = str_size(str);
    const char * ret = "";
    if( fifo_queue_data_available(fifo) >= size )
    {
        if( str_cmp( fifo, str, size ) )
        {
            ret = str;
        }
        fifo_dequeue(fifo);
    }
    return( ret );
}
