#include <xc.h>
#include "fifo.h"

void fifo_enqueue( FIFO * fifo, unsigned char dado )
{
    if( fifo->count < fifo->size )
    {
        fifo->queue[fifo->head] = dado;
        ++fifo->head;
        fifo->head %= fifo->size;
        ++fifo->count;
    }
}


unsigned char fifo_dequeue( FIFO * fifo )
{
    unsigned char dado = 0;
    if( fifo->count )
    {
        dado = fifo->queue[fifo->tail];
        fifo->tail++;
        fifo->tail %= fifo->size;
        --fifo->count;
    }
    return( dado );
}

unsigned char fifo_queue_is_free( FIFO * fifo )
{
    return( fifo->size-fifo->count );
}

unsigned char fifo_queue_data_available( FIFO * fifo )
{
    return( fifo->count );
}
