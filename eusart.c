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
#include "eusart.h"
#include "error.h"
#include "delay.h"

struct eusart_t eusart;

unsigned char size_of_str( const char * ptr )
{
    unsigned char i = 0;
    while( *(ptr+i) )
    {
        ++i;
    }
    return( i );
}

unsigned char eusart_size_of_rx( void )
{
    return( (eusart.rx_head-eusart.rx_tail)%EUSART_RX_SIZE );
}

unsigned char eusart_cmp( const char * ptr, unsigned char size )
{
    unsigned char i;
    unsigned char cmp = 1;

    for( i=0; i<size; i++ )
    {
        if( eusart.rx[(eusart.rx_tail+i)%EUSART_RX_SIZE] != ptr[i] )
        {
            if( ptr[i] != '*')
            {
                cmp = 0;
                break;
            }
        }
    }
    return( cmp );
}

unsigned char eusart_rx_pop( void )
{
    unsigned char aux = 0;
    if( eusart.rx_tail != eusart.rx_head )
    {
        aux = eusart.rx[eusart.rx_tail];
        ++eusart.rx_tail;
        eusart.rx_tail %= EUSART_RX_SIZE;
    }
    return( aux );
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
        eusart.rx[eusart.rx_head] = rx;
        ++eusart.rx_head;
        eusart.rx_head %= EUSART_RX_SIZE;
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
void eusart_printing( void )
{
    TXREG = *eusart.tx_ptr;
    ++eusart.tx_ptr;
    PIE1bits.TXIE = ((*eusart.tx_ptr) != 0);
}
void eusart_print( const char * str )
{
    if( *str )
    {
        eusart.tx_ptr = str;
        eusart_printing();
    }
}
