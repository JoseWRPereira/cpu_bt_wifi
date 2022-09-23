#include <xc.h>
#include "fifo.h"


void fifo_init( FIFO * fifo, char * q, unsigned char s )
{
    fifo->queue = q;
    fifo->head = 0;
    fifo->tail = 0;
    fifo->size = s;
}

void fifo_enqueue( FIFO * fifo, unsigned char dado )
{
    unsigned char h;
    h = fifo->head;
    fifo->queue[h] = dado;
    ++h;
    h %= fifo->size;
    if( h != fifo->tail )
    {
        fifo->head = h;
    }
}


unsigned char fifo_dequeue( FIFO * fifo )
{
    unsigned char dado;
    if( fifo->head != fifo->tail )
    {
        dado = fifo->queue[fifo->tail];
        fifo->tail++;
        fifo->tail %= fifo->size;
    }
    return( dado );
}


