#ifndef FIFO_H
#define FIFO_H

typedef struct fifoT
{
    char * queue;
    unsigned char head;
    unsigned char tail;
    unsigned char size;
} FIFO;


void fifo_init( FIFO * fifo, char * q, unsigned char s );
void fifo_enqueue( FIFO * fifo, unsigned char dado );
unsigned char fifo_dequeue( FIFO * fifo );
unsigned char fifo_queue_is_free( FIFO * fifo );


#endif
