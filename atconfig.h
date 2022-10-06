#ifndef ATCONFIG_H
#define ATCONFIG_H

#include "fsm.h"
#include "fifo.h"

FIFO * atcfg_fifo( void );

void atconfig_init( void * p );
void atconfig_init_espera( void * p );
void atconfig_msg_at( void * p );
void atconfig_msg_at_resp( void * p );
void atconfig_msg_ate0( void * p );
void atconfig_msg_ate0_resp( void * p );
void atconfig_msg_atgmr( void * p );
void atconfig_msg_atgmr_resp( void * p );

#endif
