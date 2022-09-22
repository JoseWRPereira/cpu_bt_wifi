#ifndef ATCMD_H
#define ATCMD_H

#define ATCMD_MATCH     100
#define ATCMD_NO_MATCH  200


typedef struct atcmd_t
{
    const char * send;
    const char * recv;
    unsigned char recv_size;
    unsigned char estado;
} ATCMD;

void fsm_atcmd_init( ATCMD * ptr );
void fsm_atcmd_com( ATCMD * ptr, 
                const char * str_send, 
                const char * str_recv );
void fsm_atcmd( ATCMD * ptr );

#endif
