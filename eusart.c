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
unsigned char * eusart_rx_ptr;


void eusart_read( unsigned char * rx_ptr, unsigned char rx_limit )
{
    eusart_rx_ptr0 = rx_ptr;
    eusart_rx_ptr1 = (eusart_rx_ptr0 + rx_limit);
    eusart_rx_ptr = rx_ptr;
}

void eusart_reading( unsigned char rx )
{
    if( (rx >= ' ') && (rx <= 127) )
    {
        if( eusart_rx_ptr0 < eusart_rx_ptr1 )
        {
            *eusart_rx_ptr0 = rx;
            ++eusart_rx_ptr0;
        }
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

const char * eusart_tx_ptr;
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









// void eusart_reading( unsigned char rx )
// {

//     // if( (rx >= ' ') && (rx <= 127) )
//     {
//         // if( eusart_rx_ptr0 < eusart_rx_ptr1 )
//         // {
//         //     *eusart_rx_ptr0 = rx;
//         //     ++eusart_rx_ptr0;
//         // }

//         switch( padrao_estado )
//         {
//             case 0:
//                     if( rx == *(padrao_inicial+padrao_indice) )
//                     {
//                         padrao_indice++;
//                     }
//                     else
//                     {
//                         padrao_indice = 0;
//                         if( rx == *(padrao_inicial+padrao_indice) )
//                             padrao_indice++;
//                     }
//                     if( *(padrao_inicial+padrao_indice) == '\0' )
//                     {
//                         padrao_estado = 1;
//                         padrao_indice = 0;
//                         eusart_rx_ptr = eusart_rx_ptr0;
//                     }
//                     break;

//             case 1: 
//                     if( (rx >= ' ') && (rx <= 127) )
//                     {
//                         if( eusart_rx_ptr < eusart_rx_ptr1 )
//                         {
//                             *eusart_rx_ptr = rx;
//                             ++eusart_rx_ptr;
//                         }
//                     }

//                     if( rx == *(padrao_final+padrao_indice) )
//                     {
//                         padrao_indice++;
//                     }
//                     else
//                     {
//                         padrao_indice = 0;
//                         if( rx == *(padrao_final+padrao_indice) )
//                             padrao_indice++;
//                     }
//                     if( *(padrao_final+padrao_indice) == '\0' )
//                     {
//                         padrao_estado = 2;
//                         padrao_indice = 0;
//                     }
//                     break;
//             case 2:
//                     while( eusart_rx_ptr < eusart_rx_ptr1 )
//                     {
//                         *eusart_rx_ptr = ' ';
//                         ++eusart_rx_ptr;
//                     }
//                     padrao_estado = 3;
//                     break;

//             default:
//                     break;
//         }

//         // *eusart_rx_ptr = rx;
//         // ++eusart_rx_ptr;
//         // if( eusart_rx_ptr >= eusart_rx_ptr1 )
//         //     eusart_rx_ptr = eusart_rx_ptr0;
//     }
// }


// void eusart_read( unsigned char * rx_ptr, unsigned char rx_limit, const unsigned char * padrao_ini, const unsigned char * padrao_fim )
// {
//     eusart_rx_ptr0 = rx_ptr;
//     eusart_rx_ptr1 = (eusart_rx_ptr0 + rx_limit);
//     eusart_rx_ptr = rx_ptr;

//     padrao_inicial = padrao_ini;
//     padrao_final = padrao_fim;
//     padrao_indice = 0;
//     padrao_estado = 0;

  
// }
// unsigned char * eusart_rx_ptr0;
// unsigned char * eusart_rx_ptr1;
// unsigned char * eusart_rx_ptr;

// const unsigned char * padrao_inicial;
// const unsigned char * padrao_final;
// unsigned char padrao_indice = 0;
// unsigned char padrao_estado = 0;

