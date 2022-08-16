/*
 * File:   eusart.c
 * Author: josewrpereira
 *
 * Objetivo: 
 *      Camada de Abstração de Hardware:
 *          Interface de comunicação Serial EUSART
 *          EUSART = Enhanced Universal Synchronous Asynchronous Receiver Transmitter
 *                   Transmissor Receptor Assíncrono Síncrono Universal Aprimorado
 * 
 * Pinos    | PORT     | Função
 *  25      | RC6      | TX
 *  26      | RC7      | RX
 * 
 */


#include "config.h"
#include <xc.h>
#include "delay.h"
#include "error.h"



/////////////////////////////////////////
///////////////////////////////////////// Recepção de dados
/////////////////////////////////////////

unsigned char * eusart_rx_ptr0;
unsigned char * eusart_rx_ptr1;

void eusart_read( unsigned char * rx_ptr, unsigned char rx_limit )
{
    eusart_rx_ptr0 = rx_ptr;
    eusart_rx_ptr1 = (eusart_rx_ptr0 + rx_limit);
}

void eusart_reading( unsigned char rx )
{
    if( eusart_rx_ptr0 < eusart_rx_ptr1 )
    {
        *eusart_rx_ptr0 = rx;
        ++eusart_rx_ptr0;
    }
}



/////////////////////////////////////////
///////////////////////////////////////// Transmissão de dados
/////////////////////////////////////////

void eusart_put( unsigned char c )
{
    TXREG = c;
    while( !TXSTAbits.TRMT )
        ;
}

const char * eusart_ptr_tx;
void eusart_printing( void )
{
    TXREG = *eusart_ptr_tx;
    ++eusart_ptr_tx;
    PIE1bits.TXIE = ((*eusart_ptr_tx) != 0);
}
void eusart_print( const char * str )
{
    if( *str )
    {
        eusart_ptr_tx = str;
        eusart_printing();
    }
}




/////////////////////////////////////////
///////////////////////////////////////// Inicialização
/////////////////////////////////////////


void eusart_init( unsigned long baud_rate )
{                           //  baud_rate: 9600, 19200, 38400, 57600, 115200 @20MHz
    INTCONbits.GIE = 0;
                            // Calcula valor para registradores que produzem
                            // a taxa de transmissão (Baud rate) de dados desejada.
    SPBRG = (((_XTAL_FREQ>>4)/(baud_rate/10))-5)/10;
    TXSTAbits.SYNC = 0;     // Modo assíncrono.
    BAUDCTLbits.BRG16 = 0;  // Gerador de BaudRate de 16 bits.
    TXSTAbits.BRGH = 1;     // Seleção de alto BaudRate.
    
    RCSTAbits.SPEN = 1;     // Habilita pinos para TX e RX.
    TXSTAbits.TXEN = 1;     // Inicia transmissão.
    RCSTAbits.CREN = 1;     // Habilita recepção.

    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;   
    INTCONbits.GIE = 1;
}
