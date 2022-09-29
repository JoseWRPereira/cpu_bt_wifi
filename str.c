#include <xc.h>


unsigned char str_size( const char * ptr )
{
    unsigned char i = 0;
    while( *(ptr+i) )
    {
        ++i;
    }
    return( i );
}


unsigned char str_cmp( char * str1, const char * str2, unsigned char size )
{
    unsigned char i = 0;
    unsigned char ans = 1;

    while( size )
    {
        if( *(str1+i) != *(str2+i) )
        {
            ans = 0;
            size = 0;
        }
        else
        {
            --size;
        }
    }
    return( ans );
}

