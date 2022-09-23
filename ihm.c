#include <xc.h>
#include "lcd.h"
#include "keyboard.h"
#include "tmr_tick.h"
#include "ihm.h"
#include "atcmd.h"

// s: "AT\r\n"
// r: "OK"


// "AT+RST"
// "OK"


// "AT+GMR"
// "<AT version info>
// <SDK version info>
// <compile time>
// <Bin version>
// 
// OK"

// "AT+GMR\r\n"
// "AT version:1.2.0.0(Jul  1 2016 20:04:45)
// SDK version:1.5.4.1(39cb9a32)
// Ai-Thinker Technology Co. Ltd.
// v1.5.4.1-a Nov 30 2017 15:54:29
// OK"


// "ATE0\r\n"
// OK"

typedef struct AT_CMDS_T
{
    const char * enviar;
    const char * receber;
} AT_MSG;

#define AT_MSG_SIZE 6

// const char ok[] = "OK";
AT_MSG at = {"AT\r\n", "OK"};
AT_MSG at_cwmode_1 = {"AT+CWMODE=1\r\n", "OK" };
AT_MSG at_cwjap = {"AT+CWJAP=\"arduino\",\"12345678\"\r\n", "OK"};

AT_MSG at_cipstart = {"AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n", "OK"};
AT_MSG at_cipsend = {"AT+CIPSEND=84\r\n","OK"};
AT_MSG at_cipsend_ok = {"GET https://api.thingspeak.com/update?api_key=6WFOK02JI7PJRJRA&field1=25&field2=45\r\n","OK"};


AT_MSG * at_msg[AT_MSG_SIZE] = {    &at, 
                                    &at_cwmode_1,
                                    &at_cwjap,
                                    &at_cipstart,
                                    &at_cipsend,
                                    &at_cipsend_ok };
unsigned char at_msg_indice = 0;



extern ATCMD atcmd;

void fsm_ihm_init( IHM * ptr )
{
    ptr->estado = IHM_INIT_STATE;
    ptr->tecla = 0;
    lcd_init();
    keyboard_init();
}

void fsm_ihm( IHM * ptr )
{
    ptr->tecla = keyboard_scan();

    switch( ptr->estado )
    {
        case 0:
                tmr_tick_set(IHM_TMR,1000);
                ptr->estado = 1;
                break;
        case 1:
                if( !tmr_tick(IHM_TMR) )
                    ptr->estado = 2;
                break;
        case 2:
                lcd_print(0,0,"SENAI Jandira");
                tmr_tick_set(IHM_TMR,1000);
                ptr->estado = 3;
                break;
        case 3:
                if( !tmr_tick(IHM_TMR) )
                    ptr->estado = 4;
                break;


        case 4:
                lcd_print(0,0,"Comandos AT     ");
                lcd_print(1,0,"                ");
                tmr_tick_set(IHM_TMR,3000);
                ptr->estado = 5;
                break;
        case 5:
                if( !tmr_tick(IHM_TMR) )
                {
                    ptr->estado = 100;
                    lcd_clr();
                }
                break;




        case 10:
                fsm_atcmd_com( &atcmd, "AT\r\n", "*JW*" );
                lcd_num(0,13, atcmd.recv_size, 3 );
                tmr_tick_set(IHM_TMR,30000);
                ptr->estado = 11;
                break;
        case 11:
                if( atcmd.estado == ATCMD_MATCH )
                {
                    lcd_print(1,0,"*JW*");
                    ptr->estado = 20;
                }
                else if( atcmd.estado == ATCMD_NO_MATCH )
                {
                    lcd_print(1,0,"error 10");
                }
                break;

        case 20:
                fsm_atcmd_com( &atcmd, "AT\r\n", "OK" );
                lcd_num(0,13, atcmd.recv_size, 3 );
                tmr_tick_set(IHM_TMR,30000);
                ptr->estado = 21;
                break;
        case 21:
                if( atcmd.estado == ATCMD_MATCH )
                {
                    lcd_print(1,0,"OK                ");
                    ptr->estado = 30;
                }
                else if( atcmd.estado == ATCMD_NO_MATCH )
                {
                    lcd_print(1,0,"error 20");
                }
                break;


        case 30:
                break;



        case 100:
                at_msg_indice = 0;
                ptr->estado = 101;
                break;
        case 101:
                fsm_atcmd_com( &atcmd, at_msg[at_msg_indice]->enviar, at_msg[at_msg_indice]->receber );
                lcd_clr();
                lcd_num(0,0, (int)at_msg_indice, 2 );
                lcd_num(0,3, atcmd.recv_size, 3 );
                lcd_print(1,0, at_msg[at_msg_indice]->enviar);
                ptr->estado = 102;
                break;

        case 102:
                if( atcmd.estado == ATCMD_MATCH )
                {
                    lcd_print(1,0,"                ");
                    lcd_print(1,0, at_msg[at_msg_indice]->receber );
                    ptr->estado = 103;
                }
                else if( atcmd.estado == ATCMD_NO_MATCH )
                {
                    ptr->estado = 105;
                }

                break;
        case 103:
                ++at_msg_indice;
                if( at_msg_indice < AT_MSG_SIZE )
                    ptr->estado = 101;
                else 
                    ptr->estado = 104;
                break;
        case 104:
                lcd_print(1,0,"  AT msg ended  ");
                break;
        case 105:
                lcd_print(1,0,"  AT msg error  ");
                break;


        case IHM_ERROR_TIMEOUT:
                lcd_print(1,0," Timeout ATCMD  ");
                break;
        default:
                ptr->estado = IHM_ERROR;
                break;
    }
}



