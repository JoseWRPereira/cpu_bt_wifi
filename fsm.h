#ifndef FSM_H
#define FSM_H

#define NEXT        (*(struct fsmT *)p)

struct fsmT
{
    void *(* func)(void * p);
    void * arg;
};


#endif
