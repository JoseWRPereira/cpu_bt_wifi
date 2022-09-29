#ifndef FIFO_H
#define FIFO_H

typedef struct fifoT
{
    char * queue;
    unsigned char head;
    unsigned char tail;
    unsigned char size;
    unsigned char count;
} FIFO;


// void fifo_init( FIFO * fifo, char * queue, unsigned char size );
void fifo_enqueue( FIFO * fifo, unsigned char dado );
unsigned char fifo_dequeue( FIFO * fifo );
unsigned char fifo_queue_is_free( FIFO * fifo );
unsigned char fifo_queue_data_available( FIFO * fifo );

#endif
