#ifndef ERROR_H
#define ERROR_H

#define RECEIVE_FRAMING_ERROR   1
#define RECEIVE_OVERRUN_ERROR   2

void error_set( unsigned char e );
unsigned char error_test( unsigned char e );
unsigned char error_status( void );

#endif
