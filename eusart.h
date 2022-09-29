#ifndef EUSART_H
#define EUSART_H

#include "fifo.h"

/// @brief Aponta o endereço da estrutura de recepção de dados via serial
/// @param  None
/// @return Ponteiro para estrutura da FIFO EUSART
FIFO * eusart_fifo( void );

///////////////////////////////////////// Restrições
// Cristal: 20MHz
// baud_rate: 9600, 19200, 38400, 57600 ou 115200 
/////////////////////////////////////////
void eusart_init( unsigned long baud_rate );
void eusart_reading( unsigned char rx );
void eusart_put( unsigned char c );
void eusart_printing( void );
void eusart_print( const char * str );

#endif
