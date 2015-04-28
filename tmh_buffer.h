#ifndef _TMH_BUFFER_H_
#define _TMH_BUFFER_H_

#include <stdint.h> //std types uint_8  etc
#define USE_U8_DATA  // Include 8-bit type data buffers
#define USE_U16_DATA // Include 16-bit type data buffers
//#define OVERFLOW_OVERWRITE // TODO if defined we overwrite upon overflow,else we stop and return error

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

typedef enum BUFF_TYPE {
#ifdef USE_U8_DATA
	BUFF_SMALL_U8=123,
	BUFF_LARGE_U8=124,
#endif
#ifdef USE_U16_DATA
	BUFF_SMALL_U16=125,
	BUFF_LARGE_U16=126,
#endif
}TMH_BUFF_TYPE;


#ifdef USE_U8_DATA
//***8bit  data buffer types ***//
typedef struct CIRC_BUFF_8S {
	uint8_t   type;   //circular buffer type
	uint8_t   ovf;    // overflow/full flag
	uint8_t * buff;   // pointer to buffer memory
	uint8_t   sidx;   // start index
	uint8_t   eidx;   // end index
	uint8_t   size;   // maxbuffer size
	uint8_t   count;  //  current buffer size
} CIRC_BUFFER_SMALL_U8t;

typedef struct CIRC_BUFF_8L {
	uint8_t   type;   //circular buffer type
	uint8_t   ovf;    // overflow flag
	uint8_t * buff;   // pointer to buffer memory
	uint16_t   sidx;   // start index
	uint16_t   eidx;   // end index
	uint16_t   size;   // maxbuffer size
	uint16_t   count;  //  current buffer size
} CIRC_BUFFER_LARGE_U8t;

#endif

#ifdef USE_U16_DATA
//***16bit  data buffer types ***//
typedef struct CIRC_BUFF_16S {
	uint8_t   type;   //circular buffer type
	uint8_t   ovf;    // overflow flag
	uint16_t * buff;   // pointer to buffer memory
	uint8_t   sidx;   // start index
	uint8_t   eidx;   // end index
	uint8_t   size;   // maxbuffer size
	uint8_t   count;  //  current buffer size
} CIRC_BUFFER_SMALL_U16t;

typedef struct CIRC_BUFF_16L {
	uint8_t   type;   //circular buffer type
	uint8_t   ovf;    // overflow flag
	uint16_t * buff;   // pointer to buffer memory
	uint16_t   sidx;   // start index
	uint16_t   eidx;   // end index
	uint16_t   size;   // maxbuffer size
	uint16_t   count;  //  current buffer size
} CIRC_BUFFER_LARGE_U16t;

#endif


extern uint8_t tmh_buff_init( TMH_BUFF_TYPE bt,  void *buffstruct,  void *buffer, uint32_t size);
extern uint8_t tmh_pop(void * bs, void * data );
extern uint8_t tmh_push(void * bs, uint32_t data );
extern uint8_t tmh_flush(void * bs );
extern uint8_t tmh_isfull(void * bs );


#endif

