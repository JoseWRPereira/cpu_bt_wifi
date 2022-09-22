#ifndef IHM_H
#define IHM_H

#define IHM_TMR         TMR_TICK_0
#define IHM_INIT_STATE      0
#define IHM_ERROR_TIMEOUT   254
#define IHM_ERROR           255


typedef struct fsmihm_t
{
    unsigned char tecla;
    unsigned char estado;
} IHM;


void fsm_ihm_init( IHM * ptr );
void fsm_ihm( IHM * ptr );

#endif
