#ifndef ATCMD_H
#define ATCMD_H



void * atcmd_init( void * p );
void * atcmd_send( void * p );
void * atcmd_wait_ok( void * p );




// #define ATCMD_WAITING   0
// #define ATCMD_START     1
// #define ATCMD_END       0
// #define ATCMD_ERROR     255

// #define ATCMD_RX_SIZE   32

// struct atcmd_t
// {
//     const char * ptr_send;
//     const char * ptr_receive;
//     char atcmd_state;
//     char next_ok;
//     char next_error;
//     char rx[ATCMD_RX_SIZE];
//     char i;
// };

#endif
