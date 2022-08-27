#include "config.h"
#include <xc.h>
#include "delay.h"
#include "lcd.h"
#include "eusart.h"
#include "error.h"
#include "keyboard.h"

#define RX_BUF_SIZE                     65
unsigned char rx_buf[RX_BUF_SIZE];
unsigned char rx_indice = 0;

const unsigned char * tx_ptr;
unsigned char tx_indice = 0;

void main( void )
{
    unsigned char tecla = 0;
    unsigned char estado = 0;
    
    lcd_init();
    keyboard_init();
    eusart_init(115200);

    while( 1 )
    {
        tecla = keyboard_scan();

        switch( estado )
        {
            case 0:
                    tx_indice = 0;
                    rx_indice = 0;
                    for( char i=0; i<RX_BUF_SIZE; i++ )
                        rx_buf[i] = 0;
                    ++estado;
                    break;
            case 1:
                    tx_ptr = "ATE0\r\n";
                    eusart_print(tx_ptr);
                    ++estado;
                    break;

            case 3:
                    tx_ptr = "AT+CWMODE=2\r\n";
                    eusart_print(tx_ptr);
                    ++estado;
                    break;

            case 5:
                    tx_ptr = "AT+CWSAP=\"jwrp\",\"12345678\",1,3,4,0\r\n";
                    eusart_print(tx_ptr);
                    ++estado;
                    break;

            case 7:
                    tx_ptr = "AT+CIPAP=\"192.168.4.80\"\r\n";
                    eusart_print(tx_ptr);
                    ++estado;
                    break;
            case 9:
                    tx_ptr = "AT+CIPMUX=1\r\n";
                    eusart_print(tx_ptr);
                    ++estado;
                    break;
            case 11:
                    tx_ptr = "AT+CIPSERVER=1,333\r\n";
                    eusart_print(tx_ptr);
                    ++estado;
                    break;
            default:
                    estado += (tecla=='<');
                    break;
        }

        if( tecla == '>' )
        {
            rx_indice += (rx_indice < (RX_BUF_SIZE-15));
            // lcd_clr();
        }
       

        if( estado % 2 )
        {
            rx_indice = 0;
            for( char i=0; i<(RX_BUF_SIZE-1); i++ )
                rx_buf[i] = ' ';
            rx_buf[16] = 0;
            eusart_read( rx_buf, RX_BUF_SIZE-1 );
        }

        lcd_print(0,0, tx_ptr+rx_indice );
        lcd_print(1,0, rx_buf+rx_indice );
    }
}




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