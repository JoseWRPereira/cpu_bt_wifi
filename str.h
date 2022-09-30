#ifndef STR_H
#define STR_H

unsigned char str_size( const char * ptr );
unsigned char str_cmp( char * str1, const char * str2, unsigned char size );
const char * str_search( FIFO * fifo, const char * str );

#endif
