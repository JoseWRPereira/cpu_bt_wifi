#ifndef FSM_H
#define FSM_H

#include "atconfig.h"

#define NEXT_STATE          ((FSM*)p)->func

typedef struct fsmT
{
    void (* func)(void * p);
} FSM;


#endif
