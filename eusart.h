#ifndef EUSART_H
#define EUSART_H

#define EUSART_RX_SIZE      32

struct eusart_t
{
    unsigned char rx[EUSART_RX_SIZE];
    unsigned char rx_head, rx_tail;
    const char * tx_ptr;
    unsigned char status;
};

///////////////////////////////////////// Restrições
// Cristal: 20MHz
// baud_rate: 9600, 19200, 38400, 57600 ou 115200 
/////////////////////////////////////////
void eusart_init( unsigned long baud_rate );

unsigned char size_of_str( const char * ptr );
unsigned char eusart_size_of_rx( void );
unsigned char eusart_cmp( const char * ptr, unsigned char size );
unsigned char eusart_rx_pop( void );
void eusart_reading( unsigned char rx );
void eusart_put( unsigned char c );
void eusart_printing( void );
void eusart_print( const char * str );

#endif
