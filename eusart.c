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


// #include "config.h"
#include <xc.h>
#include "fifo.h"
#include "eusart.h"
#include "error.h"
#include "delay.h"



/////////////////////////////////////////
///////////////////////////////////////// FIFO Queue
/////////////////////////////////////////

#define EUSART_RCV_SIZE 16

char eusart_rcv_buf[EUSART_RCV_SIZE] = {0};
FIFO eusart_rcv = { eusart_rcv_buf, 0, 0, EUSART_RCV_SIZE, 0, 0};


FIFO * eusart_fifo( void )
{
    return( &eusart_rcv );
}



/////////////////////////////////////////
///////////////////////////////////////// Inicialização
/////////////////////////////////////////
void eusart_init( unsigned long baud_rate )
{                           //  baud_rate: 9600, 19200, 38400, 57600, 115200 @20MHz
    INTCONbits.GIE = 0;
                            // Calcula valor para registradores que produzem
                            // a taxa de transmissão (Baud rate) de dados desejada.
    SPBRG = (unsigned char)(((_XTAL_FREQ>>4)/(baud_rate/10))-5)/10;
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



/////////////////////////////////////////
///////////////////////////////////////// Recepção de dados
/////////////////////////////////////////
void eusart_reading( unsigned char rx )
{
    if( ((rx >= ' ') && (rx <= 127)) )//|| (rx=='\r') || (rx=='\n') )
    {
        fifo_enqueue( &eusart_rcv, rx );
    }
}



/////////////////////////////////////////
///////////////////////////////////////// Transmissão de dados
/////////////////////////////////////////
const char * eusart_tx_ptr;

void eusart_put( unsigned char c )
{
    TXREG = c;
    while( !TXSTAbits.TRMT )
        ;
}
void eusart_printing( void )
{
    TXREG = *eusart_tx_ptr;
    ++eusart_tx_ptr;
    PIE1bits.TXIE = ((*eusart_tx_ptr) != 0);
}
void eusart_print( const char * str )
{
    if( *str )
    {
        eusart_tx_ptr = str;
        eusart_printing();
    }
}
