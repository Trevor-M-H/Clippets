/*

  DISCLAIMER and Copyright

  Free to use!
  
  I accept not responsibility for the use or misuse of this software.
  
  Please credit the Author if you do want to use it.
  
  Trevor Heyl 2009

*/
/******************************************************************************
* Module : tnh_timer.C
*
* Description : 
*     General purpose timers, choose timer types (8,16 or 32 bit) and timer 
*     capabilities with tmh_timer.H.  choose number of timers, timer structures
*     are statically allocated.
*
*     1. Call Timer_Tick() from timer, ISR choose interval as desired
*     2. Declare a Timer handle of type TIMER
*     3. Get a free timer with this handle (Timer_Get())
*     4. Start the timer with Timer_Start() or Timer_Start_cb(), set the mode too
*     5. Optionally free the timer for later reuse, this does not free
*        The memory, only the usage.
*     6. Call back types may only be void fp(void) types
*     7. Oneshot mode can be used, test the expiration with  Timer_Timeout();
*
*
*******************************************************************************/
#include "tmh_timer.h"

#if ENABLE_8BIT_TIMERS
static A_8TIMER timers8[MAX_8BIT_TIMERS];
#endif
#if ENABLE_16BIT_TIMERS
static A_16TIMER timers16[MAX_16BIT_TIMERS];
#endif
#if ENABLE_32BIT_TIMERS
static A_32TIMER timers32[MAX_32BIT_TIMERS];
#endif


static BOOLEAN Timers_initial=FALSE;


/******************************************************************************
* Function : safe_func
* Description : Dummy func to call if user does not init callback
* Params :  None
* Returns :  None
*******************************************************************************/
void safe_func(void) {
}


/******************************************************************************
* Function : Timers_Init
* Description : Init all timers
* Params :  None
* Returns :  None
*******************************************************************************/
void Timers_Init(void) {
      TIMER c;
     
      DISABLE_INTS();
#if ENABLE_8BIT_TIMERS    
        for(c=0;c<MAX_8BIT_TIMERS;c++) {
             timers8[c].t_bits.in_use = FALSE;
             timers8[c].t_bits.tmod = TIM_ONESHOT;
#if CALLBACKS
             timers8[c].cb = safe_func;
#endif            
        }                                      
#endif
#if ENABLE_16BIT_TIMERS   
        for(c=0;c<MAX_16BIT_TIMERS;c++) {
             timers16[c].t_bits.in_use = FALSE; 
             timers16[c].t_bits.tmod = TIM_ONESHOT; 
#if CALLBACKS
             timers16[c].cb = safe_func;
#endif            
        }                                      
#endif
#if ENABLE_32BIT_TIMERS   
        for(c=0;c<MAX_32BIT_TIMERS;c++) {
             timers32[c].t_bits.in_use = FALSE;
             timers32[c].t_bits.tmod = TIM_ONESHOT; 
#if CALLBACKS
             timers32[c].cb = safe_func;
#endif            
        }                                      
#endif

      Timers_initial = TRUE;
      
      ENABLE_INTS();

}


/******************************************************************************
* Function : Timer_Get
* Description : Get a free timer
* Params :  Timer base, 8,16 or 32 bit i.e. TIM_8BIT TIM_16BIT  TIM_32BIT
* Returns :  0 - Fail, 1to 255 timer ref/ instance
*******************************************************************************/
TIMER Timer_Get(TIMER_BASES tbase) {

      uint8_t c;
      TIMER retval=0;
      
      if(!Timers_initial) Timers_Init();
      
      DISABLE_INTS();
#if ENABLE_8BIT_TIMERS    
      if(tbase == TIM_8BIT) {
        for(c=0;c<MAX_8BIT_TIMERS;c++) {
            if(!timers8[c].t_bits.in_use) {
             /* found a timer */
             timers8[c].t_bits.in_use = TRUE;
             timers8[c].t_bits.to = FALSE;
             retval = c+1;
             break;
            }                                      
        }          
      }
#endif
#if ENABLE_16BIT_TIMERS   
      if(tbase == TIM_16BIT) {
        for(c=0;c<MAX_16BIT_TIMERS;c++) {
            if(!timers16[c].t_bits.in_use) {
             /* found a timer */
             timers16[c].t_bits.in_use = TRUE;
             timers16[c].t_bits.to = FALSE;
             retval = (c+64+1);
             break;
            }                                      
        }          
      }
#endif
#if ENABLE_32BIT_TIMERS   
      if(tbase == TIM_32BIT) {
        for(c=0;c<MAX_32BIT_TIMERS;c++) {
            if(!timers32[c].t_bits.in_use) {
             /* found a timer */
             timers32[c].t_bits.in_use = TRUE;
             timers32[c].t_bits.to = FALSE;
             retval = (c+128+1);
             break;
            }                                      
        }          
      }
#endif
      ENABLE_INTS();
      
      return retval;

}

/******************************************************************************
* Function : Timer_Start
* Description : Start a timer, must be valid timer
* Params :  Timer, 1 to 255, already allocated, timer timeout, timer mode and
*           
* Returns :  0 - Fail, , val too big,1 Done, timer started
*******************************************************************************/
BOOLEAN Timer_Start(TIMER tim, uint32_t val, TIMER_MODES mode ) {

        BOOLEAN retval = FALSE;
    
        /* 8-bit timers */
#if ENABLE_8BIT_TIMERS  
        if(tim > 0 && tim < 65) {
           if(val < 0x100 ) {
              DISABLE_INTS();
              timers8[tim-1].t_bits.to = FALSE;
              timers8[tim-1].timer = val;
#if RELOADABLE            
              timers8[tim-1].t_bits.tmod = mode;
              timers8[tim-1].reload = val;
#endif            
              retval = TRUE;
              ENABLE_INTS();
           }
        } 
#endif
#if ENABLE_16BIT_TIMERS      
        /* 16-bit timers */
        if(tim > 64 && tim < 129) {
           tim -=64;
           if(val < 0x10000   ) {
              DISABLE_INTS();
              timers16[tim-1].t_bits.to = FALSE;
              timers16[tim-1].timer = val;
#if RELOADABLE            
              timers16[tim-1].t_bits.tmod = mode;
              timers16[tim-1].reload = val;
#endif            
              retval = TRUE;
              ENABLE_INTS();
           }
        }  
#endif  
#if ENABLE_32BIT_TIMERS 
        /* 32-bit timers */
        if(tim < 193) {
           tim -=128;
           if( 1 ) {
             DISABLE_INTS();
             timers32[tim-1].t_bits.to = FALSE;
             timers32[tim-1].timer = val;
#if RELOADABLE            
              timers32[tim-1].t_bits.tmod = mode;
              timers32[tim-1].reload = val;
#endif            
             retval = TRUE;
             ENABLE_INTS();
           } 
        }
#endif      
            return retval;
}



#if CALLBACKS
/******************************************************************************
* Function : Timer_Start_cb
* Description : Start a timer, must be valid timer with call back func
* Params :  Timer, 1 to 255, already allocated, timer timeout, timer mode and
*           optional callback 
* Returns :  0 - Fail, , val too big,1 Done, timer started
*******************************************************************************/
BOOLEAN Timer_Start_cb(TIMER tim, uint32_t val, TIMER_MODES mode, vFP cb ) {

        BOOLEAN retval = FALSE;

        if(cb) {
#if ENABLE_8BIT_TIMERS
          if(tim > 0 && tim < 65) {
            DISABLE_INTS();
            timers8[tim-1].cb = cb;
            ENABLE_INTS();
            retval = Timer_Start(tim,val,mode);
          }                     
#endif         
#if ENABLE_16BIT_TIMERS
          if(tim > 64 && tim < 129) {
            tim-=64;
            DISABLE_INTS();
            timers16[tim-1].cb = cb;
            ENABLE_INTS();
            retval = Timer_Start((tim+64),val,mode);
          }                     
#endif         
#if ENABLE_32BIT_TIMERS
          if(tim > 128 && tim < 193) {
            tim-=128;
            DISABLE_INTS();
            timers32[tim-1].cb = cb;
            ENABLE_INTS();
            retval = Timer_Start((tim+128),val,mode);
          }                     
#endif         
        } 
            return retval;
}

#endif


/******************************************************************************
* Function : Timer_Timeout
* Description : Check for timer timeout
* Params :  Timer, 1 to 255, already allocated 
* Returns :  0 - No, 1 - Yes
*******************************************************************************/
BOOLEAN Timer_Timeout(TIMER tim) {
        BOOLEAN retval = FALSE;
#if ENABLE_8BIT_TIMERS
        if(tim > 0 && tim < 65) {
           if(timers8[tim-1].t_bits.in_use) {
              DISABLE_INTS();
              if(timers8[tim-1].t_bits.to) {
                 retval = TRUE;
#if RELOADABLE
                 if(timers8[tim-1].t_bits.tmod == TIM_RELOAD)
                  timers8[tim-1].t_bits.to = FALSE;
#endif            
              }
              ENABLE_INTS();
           }
        } 
#endif      
#if ENABLE_16BIT_TIMERS
        if(tim > 64 && tim < 129) {
           tim -= 64;
           if(timers16[tim-1].t_bits.in_use) {
              DISABLE_INTS();
              if(timers16[tim-1].t_bits.to) {
                 retval = TRUE;
#if RELOADABLE
                 if(timers16[tim-1].t_bits.tmod == TIM_RELOAD)
                    timers16[tim-1].t_bits.to = FALSE;
#endif            
              }
              ENABLE_INTS();
           }
        } 
#endif      
#if ENABLE_32BIT_TIMERS
        if(tim > 128 && tim < 193) {
           tim -= 128;
           if(timers32[tim-1].t_bits.in_use) {
              DISABLE_INTS();
              if(timers32[tim-1].t_bits.to) {
                 retval = TRUE;
#if RELOADABLE
                 if(timers32[tim-1].t_bits.tmod == TIM_RELOAD)
                  timers32[tim-1].t_bits.to = FALSE;
#endif            
              }
              ENABLE_INTS();
           }
        } 
#endif      
        return retval;
} 

/******************************************************************************
* Function : Timer_Free
* Description : Free up timer 
* Params :  Timer, 1 to 255, already allocated 
* Returns :  0 - Was not in use, 1 - Freed
*******************************************************************************/

BOOLEAN Timer_Free(TIMER tim) {
        BOOLEAN retval = FALSE;
#if ENABLE_8BIT_TIMERS
        if(tim > 0 && tim < 65) {
           if(timers8[tim-1].t_bits.in_use) {
              DISABLE_INTS();
              if(timers8[tim-1].t_bits.in_use = FALSE) retval = TRUE;
              ENABLE_INTS();
           }
        } 
#endif      
#if ENABLE_16BIT_TIMERS
        if(tim > 64 && tim < 129) {
           tim -= 64;
           if(timers16[tim-1].t_bits.in_use) {
              DISABLE_INTS();
              if(timers16[tim-1].t_bits.in_use = FALSE) retval = TRUE;
              ENABLE_INTS();
           }
        } 
#endif      
#if ENABLE_32BIT_TIMERS
        if(tim > 128 && tim < 193) {
           tim -= 128;
           if(timers32[tim-1].t_bits.in_use) {
              DISABLE_INTS();
              if(timers32[tim-1].t_bits.in_use = FALSE) retval = TRUE;
              ENABLE_INTS();
           }
        } 
#endif      
        return retval;  

}



/******************************************************************************
* Function : Timer_Tick
* Description : Increment timers etc. call from timer ISR
* Params :  None
* Returns :  None
*******************************************************************************/
void Timer_Tick(void) {
     uint8_t c;
#if ENABLE_8BIT_TIMERS
     for(c=0;c<MAX_8BIT_TIMERS;c++) {
           if(timers8[c].t_bits.in_use) {
              DISABLE_INTS();
              if(timers8[c].timer) timers8[c].timer--;
              else {
                 timers8[c].t_bits.to = TRUE;
#if RELOADABLE
                 if(timers8[c].t_bits.tmod == TIM_RELOAD) {
                    timers8[c].timer = timers8[c].reload;                                    
                 }
#endif          
#if CALLBACKS
                 if(timers8[c].cb) (timers8[c].cb)();
#endif
             }   
              ENABLE_INTS();
           }
     } 
#endif      
#if ENABLE_16BIT_TIMERS
     for(c=0;c<MAX_16BIT_TIMERS;c++) {
           if(timers16[c].t_bits.in_use) {
              DISABLE_INTS();
              if(timers16[c].timer) timers16[c].timer--;
              else {
                 timers16[c].t_bits.to = TRUE;
#if RELOADABLE
                 if(timers16[c].t_bits.tmod == TIM_RELOAD) {
                    timers16[c].timer = timers16[c].reload;                                  
                 }
#endif          
#if CALLBACKS
                 if(timers16[c].cb) (timers16[c].cb)();
#endif
     
              } 
              ENABLE_INTS();
           }
     } 
#endif      
#if ENABLE_32BIT_TIMERS
     for(c=0;c<MAX_32BIT_TIMERS;c++) {
           if(timers32[c].t_bits.in_use) {
              DISABLE_INTS();
              if(timers32[c].timer) timers32[c].timer--;
              else {
                 timers32[c].t_bits.to = TRUE;
#if RELOADABLE
                 if(timers32[c].t_bits.tmod == TIM_RELOAD) {
                    timers32[c].timer = timers32[c].reload;                                  
                 }
#endif      
#if CALLBACKS
                 if(timers32[c].cb) (timers32[c].cb)();
#endif

              }      
              ENABLE_INTS();
           }
     } 
#endif      
}

