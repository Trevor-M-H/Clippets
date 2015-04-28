#ifndef _TMH_TIMER_H_
#define _TMH_TIMER_H_

#include<stdint.h>

/* enable timer types and features here */
#define ENABLE_8BIT_TIMERS 1
#define ENABLE_16BIT_TIMERS 1
#define ENABLE_32BIT_TIMERS 1

#define MAX_8BIT_TIMERS 2
#define MAX_16BIT_TIMERS 2 
#define MAX_32BIT_TIMERS 2


#define RELOADABLE 1
/* use Start_Timer_cb() to use feature */
#define CALLBACKS  1

/* Your implementation to enable timer interupts if required */
#define DISABLE_INTS() ;
#define ENABLE_INTS() ;


/* specific types, redfine  if required */
#ifdef vFP
#undef vFP
#else
typedef void (*vFP)(void);
#endif
#ifndef BOOLEAN
typedef unsigned char BOOLEAN;
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif


/* Timer reference , up to 64 timers, 1 to 64 */
typedef uint8_t TIMER; 

typedef enum TIMER_BASES {
     TIM_8BIT,
     TIM_16BIT,
     TIM_32BIT
}TIMER_BASES;

typedef enum TIMER_MODES {
#if RELOADABLE   
     TIM_ONESHOT,
     TIM_RELOAD
#else
     TIM_ONESHOT
#endif   
}TIMER_MODES;

#if ENABLE_8BIT_TIMERS
  #if !MAX_8BIT_TIMERS
    #error Define some 8 bit timers
  #endif
  #if MAX_8BIT_TIMERS > 64  
    #error Too many  8 bit timers, max 64 
  #endif
  #if MAX_8BIT_TIMERS == 0  
    #error Too few 8 bit timers 
  #endif

typedef struct A_8TIMER {
    uint8_t timer;
#if RELOADABLE  
    uint8_t reload;
#endif  
#if CALLBACKS
    vFP cb;
#endif
    struct {
           uint16_t to        : 1;
           uint16_t in_use    : 1;
           uint16_t tmod      : 1;
           uint16_t spare     : 13;
    }t_bits;       
}A_8TIMER;

#endif

#if ENABLE_16BIT_TIMERS
  #if !MAX_16BIT_TIMERS
    #error Define some 16 bit timers
  #endif
  #if MAX_16BIT_TIMERS > 64  
    #error Too many  16 bit timers, max 64 
  #endif
  #if MAX_16BIT_TIMERS == 0  
    #error Too few 16 bit timers 
  #endif

typedef struct A_16TIMER {
    uint16_t timer;
#if RELOADABLE  
    uint16_t reload;
#endif  
#if CALLBACKS
    vFP cb;
#endif

    struct {
           uint16_t to        : 1;
           uint16_t tmod      : 1;
           uint16_t in_use    : 1;
           uint16_t spare     : 13;
    }t_bits;       
}A_16TIMER;

#endif
#if ENABLE_32BIT_TIMERS
  #if !MAX_32BIT_TIMERS
    #error Define some 32 bit timers
  #endif
  #if MAX_32BIT_TIMERS > 64  
    #error Too many  32 bit timers, max 64 
  #endif
  #if MAX_32BIT_TIMERS == 0  
    #error Too few 32 bit timers 
  #endif

typedef struct A_32TIMER {
    uint32_t timer;
#if RELOADABLE  
    uint32_t reload;
#endif  
#if CALLBACKS
    vFP cb;
#endif

    struct {
           uint16_t to        : 1;
           uint16_t in_use    : 1;
           uint16_t tmod      : 1;
           uint16_t spare     : 13;
    }t_bits;       
}A_32TIMER;

#endif

/* External functions for TImer module */
TIMER   Timer_Get(TIMER_BASES tbase);
BOOLEAN Timer_Free(TIMER tim);
BOOLEAN Timer_Start(TIMER tim, uint32_t val,TIMER_MODES mode );
BOOLEAN Timer_Timeout(TIMER tim);
void    Timer_Tick(void);
#if CALLBACKS
BOOLEAN Timer_Start_cb(TIMER tim, uint32_t val, TIMER_MODES mode, vFP cb );
#endif



#endif

