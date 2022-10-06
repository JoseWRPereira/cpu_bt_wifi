#ifndef ATCONFIG_H
#define ATCONFIG_H

#include "fsm.h"

void atconfig_init( void * p );
void atconfig_init_espera( void * p );
void atconfig_msg0_at( void * p );
void atconfig_msg0_at_delay( void * p );
void atconfig_msg1_at( void * p );
void atconfig_msg1_at_delay( void * p );

#endif
