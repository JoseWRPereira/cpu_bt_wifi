#ifndef FSM_H
#define FSM_H


#define FSM_U32(x)      ((unsigned long)(*(struct fsmT *)p).x)
#define FSM_S32(x)      ((  signed long)(*(struct fsmT *)p).x)
#define FSM_U16(x)      ((unsigned int )(*(struct fsmT *)p).x)
#define FSM_S16(x)      ((  signed int )(*(struct fsmT *)p).x)
#define FSM_U8(x)       ((unsigned char)(*(struct fsmT *)p).x)
#define FSM_S8(x)       ((  signed char)(*(struct fsmT *)p).x)

#define FSM_ARG_U32     ((unsigned long)(*(struct fsmT *)p).arg)
#define FSM_ARG_S32     ((  signed long)(*(struct fsmT *)p).arg)
#define FSM_ARG_U16     ((unsigned int )(*(struct fsmT *)p).arg)
#define FSM_ARG_S16     ((  signed int )(*(struct fsmT *)p).arg)
#define FSM_ARG_U8      ((unsigned char)(*(struct fsmT *)p).arg)
#define FSM_ARG_S8      ((  signed char)(*(struct fsmT *)p).arg)

struct fsmT
{
    void *(*func)(void* p);
    void * arg;
};


#endif
