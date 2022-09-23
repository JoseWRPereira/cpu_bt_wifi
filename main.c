#include "config.h"
#include <xc.h>
#include "tmr_tick.h"
#include "ihm.h"
#include "atcmd.h"
#include "lcd.h"


/////////////////// Teste
#include "fifo.h" 
#define RCV_SIZE 8
unsigned char rcv_buf[RCV_SIZE] = "        ";
FIFO rcv;
///////////////////


IHM ihm;
ATCMD atcmd;

void main( void )
{
    tmr_tick_init();
    fsm_ihm_init( &ihm );
    fsm_atcmd_init( &atcmd );

    fifo_init(&rcv, rcv_buf, RCV_SIZE);
    tmr_tick_set(3, 5000);

    while( 1 )
    {
        lcd_num(0,0, rcv.head,2);
        lcd_num(0,3, rcv.tail,2);
        lcd_num(0,6, rcv.size,2);
        lcd_num(0,9, fifo_queue_is_free(&rcv),2);

        lcd_lincol(1,0);
        for( char i=0; i<RCV_SIZE; i++ )
            lcd_put( rcv_buf[i] );

        if( !tmr_tick(3) )
        {
            tmr_tick_set(3, 5000);
            lcd_lincol(0,15);
            lcd_put(fifo_dequeue(&rcv));
        }
    }

    while( 1 )
    {
        fsm_ihm( &ihm );
        fsm_atcmd( &atcmd );
        lcd_num(0, 9, ihm.estado, 3 );
        lcd_num(0,13, atcmd.estado, 3 );
    }
}


// void main( void )
// {
//     lcd_init();
//     eusart_init(115200);
//     keyboard_init();

//     while( 1 )
//     {
//         switch( estado )
//         {
//             case 0: 
//                     tx_ptr = "ATE0\r\n";
//                     eusart_print(tx_ptr);
//                     estado = 1;
//                     break;
//             case 1: 
//                     delay(1000);
//                     estado = 2;
//                     break;
//             case 2: 
//                     tx_ptr = "AT+CWMODE=1\r\n";
//                     eusart_print(tx_ptr);
//                     estado = 3;
//                     break;
//             case 3: 
//                     delay(1000);
//                     estado = 4;
//                     break;
//             case 4: 
//                     tx_ptr = "AT+CWJAP=\"arduino\",\"12345678\"\r\n";
//                     eusart_print(tx_ptr);
//                     estado = 5;
//                     break;
//             case 5: 
//                     delay(15000);
//                     estado = 6;
//                     break;
//             case 6: 
//                     tx_ptr = "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n";
//                     eusart_print(tx_ptr);
//                     estado = 7;
//                     break;
//             case 7: 
//                     delay(10000);
//                     estado = 8;
//                     break;
//             case 8: 
//                     tx_ptr = "AT+CIPSEND=83\r\n";
//                     eusart_print(tx_ptr);
//                     estado = 9;
//                     break;
//             case 9: 
//                     delay(1000);
//                     estado = 10;
//                     break;
//             case 10: 
//                     tx_ptr = "GET http://api.thingspeak.com/update?api_key=6WFOK02JI7PJRJRA&field1=35&field2=40\r\n";
//                     eusart_print(tx_ptr);
//                     estado = 11;
//                     break;
//             case 11: 
//                     delay(10000);
//                     estado = 6;
//                     break;
//         }
//         lcd_print(0,2, tx_ptr );
//         lcd_num(0,0, (int)estado, 2 );

//         lcd_print(1,0, rx_buf );
//         eusart_read( rx_buf, 49 );


//     }
// }


// #define RX_BUF_SIZE                     65
// unsigned char rx_buf[RX_BUF_SIZE];
// unsigned char rx_indice = 0;

// const unsigned char * tx_ptr;
// unsigned char tx_indice = 0;

// void main( void )
// {
//     unsigned char tecla = 0;
//     unsigned char estado = 0;
    
//     lcd_init();
//     keyboard_init();
//     eusart_init(115200);

//     while( 1 )
//     {
//         tecla = keyboard_scan();

//         switch( estado )
//         {
//             case 0:
//                     tx_indice = 0;
//                     rx_indice = 0;
//                     for( char i=0; i<RX_BUF_SIZE; i++ )
//                         rx_buf[i] = 0;
//                     ++estado;
//                     break;
//             case 1:
//                     tx_ptr = "ATE0\r\n";
//                     eusart_print(tx_ptr);
//                     ++estado;
//                     break;

//             case 3:
//                     tx_ptr = "AT+CWMODE=2\r\n";
//                     eusart_print(tx_ptr);
//                     ++estado;
//                     break;

//             case 5:
//                     tx_ptr = "AT+CWSAP=\"jwrp\",\"12345678\",1,3,4,0\r\n";
//                     eusart_print(tx_ptr);
//                     ++estado;
//                     break;

//             case 7:
//                     tx_ptr = "AT+CIPAP=\"192.168.4.80\"\r\n";
//                     eusart_print(tx_ptr);
//                     ++estado;
//                     break;
//             case 9:
//                     tx_ptr = "AT+CIPMUX=1\r\n";
//                     eusart_print(tx_ptr);
//                     ++estado;
//                     break;
//             case 11:
//                     tx_ptr = "AT+CIPSERVER=1,333\r\n";
//                     eusart_print(tx_ptr);
//                     ++estado;
//                     break;
//             default:
//                     estado += (tecla=='<');
//                     break;
//         }

//         if( tecla == '>' )
//         {
//             rx_indice += (rx_indice < (RX_BUF_SIZE-15));
//             // lcd_clr();
//         }
       

//         if( estado % 2 )
//         {
//             rx_indice = 0;
//             for( char i=0; i<(RX_BUF_SIZE-1); i++ )
//                 rx_buf[i] = ' ';
//             rx_buf[16] = 0;
//             eusart_read( rx_buf, RX_BUF_SIZE-1 );
//         }

//         lcd_print(0,0, tx_ptr+rx_indice );
//         lcd_print(1,0, rx_buf+rx_indice );
//     }
// }




// AT+CIPSTART="TCP","52.87.105.151",80

// AT+CIPSEND=74

// GET / HTTP/1.1
// Host: httpbin.org
// Accept: */*
// Connection: keep-alive





// AT+CIPSTART="TCP","23.22.144.165",443

// AT+CIPSEND=96

// GET /api/users HTTP/1.1
// Host: integrado.herokuapp.com
// Accept: */*
// Connection: keep-alive



// AT
// AT+CWMODE=1
// AT+CWLAP
// AT+CWJAP="arduino","12345678"
// AT+CWJAP="IoT_AP","12345678"
// AT+CIPSTART="TCP","api.thingspeak.com",80
// AT+CIPSEND=84
// GET https://api.thingspeak.com/update?api_key=6WFOK02JI7PJRJRA&field1=25&field2=45

