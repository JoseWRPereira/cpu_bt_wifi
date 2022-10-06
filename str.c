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

// char str_between_indice = 0;
char str_between( FIFO * fifo, const char * str1, const char * str2, char * destino )
{
    char size;
    if( fifo->between == 0 )
    {
        size = str_size(str1);
        if( fifo_queue_data_available(fifo) > size )
        {
            if( str_cmp( fifo, str1, size ) )
            {
                fifo->between = 1;
                fifo->tail = (fifo->tail+size) % fifo->size;
                fifo->count -= size;
            }
            else
            {
                fifo_dequeue(fifo);
            }
        }
    }
    else
    {
        size = str_size(str2);
        if( fifo_queue_data_available(fifo) > size )
        {
            if( str_cmp( fifo, str2, size ) )
            {
                fifo->between = 0;
                fifo->tail = (fifo->tail+size) % fifo->size;
                fifo->count -= size;
            }
            else
            {
                *(destino+fifo->between-1) = fifo_dequeue(fifo);
                *(destino+fifo->between) = '\0';
                fifo->between += 1;
            }
        }
    }
    return( fifo->between );
}
