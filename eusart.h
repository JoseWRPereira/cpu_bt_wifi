#ifndef EUSART_H
#define EUSART_H

///////////////////////////////////////// Restrições
// Cristal: 20MHz
// baud_rate: 9600, 19200, 38400, 57600 ou 115200 
/////////////////////////////////////////
void eusart_init( unsigned long baud_rate );


void eusart_read( unsigned char * rx_ptr, unsigned char rx_limit );
void eusart_reading( unsigned char rx );
void eusart_put( unsigned char c );
void eusart_printing( void );
void eusart_print( const char * str );


#endif
