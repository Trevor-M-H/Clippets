#include "tmh_buffer.h"


/*****************************************************************************
 * tmh_buff_init
 *  Init a circular buffer type. Nulls data
 *  bt  = buffer type ie.  BUFF_SMALL_U8, BUFF_SMALL_U16 etc
 *  buffer = the  data memory that is the buffer
 *  size = max size of the supplied data buffer
 *
 *  Returns
 *    false for any null pointer,size violation
 */
uint8_t tmh_buff_init( TMH_BUFF_TYPE bt,  void  *buffstruct,  void  *buffer, uint32_t size) {

	uint32_t cnt;

	if ( buffer == (void *)0)
		return false;

	switch (bt) {
#ifdef USE_U8_DATA
	case BUFF_SMALL_U8 :
		if ( size > 0x100  )
			return false;
		((CIRC_BUFFER_SMALL_U8t *)buffstruct)->type = (uint8_t)bt ;
		((CIRC_BUFFER_SMALL_U8t *)buffstruct)->sidx = 0;
		((CIRC_BUFFER_SMALL_U8t *)buffstruct)->eidx = 0;
		((CIRC_BUFFER_SMALL_U8t *)buffstruct)->count = 0;
		((CIRC_BUFFER_SMALL_U8t *)buffstruct)->ovf = 0;
		((CIRC_BUFFER_SMALL_U8t *)buffstruct)->size = (uint8_t)size;
		((CIRC_BUFFER_SMALL_U8t *)buffstruct)->buff = (uint8_t*)buffer;

		for(cnt = 0; cnt < size ; cnt++) {
			((CIRC_BUFFER_SMALL_U8t *)buffstruct)->buff[cnt] = 0;
		}

		return true;

	case BUFF_LARGE_U8 :
		if ( size > 0x10000 )
			return false;
		((CIRC_BUFFER_LARGE_U8t *)buffstruct)->type = (uint8_t)bt ;
		((CIRC_BUFFER_LARGE_U8t *)buffstruct)->sidx = 0;
		((CIRC_BUFFER_LARGE_U8t *)buffstruct)->eidx = 0;
		((CIRC_BUFFER_LARGE_U8t *)buffstruct)->count = 0;
		((CIRC_BUFFER_LARGE_U8t *)buffstruct)->ovf = 0;
		((CIRC_BUFFER_LARGE_U8t *)buffstruct)->size = (uint16_t)size;
		((CIRC_BUFFER_LARGE_U8t *)buffstruct)->buff = (uint8_t*)buffer;

		for(cnt = 0; cnt < size ; cnt++) {
			((CIRC_BUFFER_LARGE_U8t *)buffstruct)->buff[cnt] = 0;
		}

		return true;
#endif
#ifdef USE_U16_DATA
	case BUFF_SMALL_U16 :
		if ( size > 0x100 )
			return false;
		((CIRC_BUFFER_SMALL_U16t *)buffstruct)->type = (uint8_t)bt ;
		((CIRC_BUFFER_SMALL_U16t *)buffstruct)->sidx = 0;
		((CIRC_BUFFER_SMALL_U16t *)buffstruct)->eidx = 0;
		((CIRC_BUFFER_SMALL_U16t *)buffstruct)->count = 0;
		((CIRC_BUFFER_SMALL_U16t *)buffstruct)->ovf = 0;
		((CIRC_BUFFER_SMALL_U16t *)buffstruct)->size = (uint8_t)size;
		((CIRC_BUFFER_SMALL_U16t *)buffstruct)->buff = (uint16_t*)buffer;

		for(cnt = 0; cnt < size ; cnt++) {
			((CIRC_BUFFER_SMALL_U16t *)buffstruct)->buff[cnt] = 0;
		}

		return true;

	case BUFF_LARGE_U16 :
		if ( size > 0x10000 )
			return false;
		((CIRC_BUFFER_LARGE_U16t *)buffstruct)->type = (uint8_t)bt ;
		((CIRC_BUFFER_LARGE_U16t *)buffstruct)->sidx = 0;
		((CIRC_BUFFER_LARGE_U16t *)buffstruct)->eidx = 0;
		((CIRC_BUFFER_LARGE_U16t *)buffstruct)->count = 0;
		((CIRC_BUFFER_LARGE_U16t *)buffstruct)->ovf = 0;
		((CIRC_BUFFER_LARGE_U16t *)buffstruct)->size = (uint16_t)size;
		((CIRC_BUFFER_LARGE_U16t *)buffstruct)->buff = (uint16_t*)buffer;

		for(cnt = 0; cnt < size ; cnt++) {
			((CIRC_BUFFER_LARGE_U16t *)buffstruct)->buff[cnt] = 0;
		}

		return true;
#endif
	}
	return false;
}



/*****************************************************************************
 * tmh_flush
 *  Flush a circular buffer type. Resets data and pointers
 *  buffstruct  = buffer type ie.  BUFF_SMALL_U8, BUFF_SMALL_U16 etc
 *  *
 *  Returns
 *    false for any null pointer
 */
uint8_t tmh_flush( void  * buffstruct ) {

	uint32_t cnt;
	TMH_BUFF_TYPE bt = (TMH_BUFF_TYPE)*(uint8_t*)buffstruct;

	if ( buffstruct == (void *)0)
		return false;

	switch (bt) {
#ifdef USE_U8_DATA
	case BUFF_SMALL_U8 :
		((CIRC_BUFFER_SMALL_U8t *)buffstruct)->sidx = 0;
		((CIRC_BUFFER_SMALL_U8t *)buffstruct)->eidx = 0;
		((CIRC_BUFFER_SMALL_U8t *)buffstruct)->count = 0;
		((CIRC_BUFFER_SMALL_U8t *)buffstruct)->ovf = 0;

		for(cnt = 0; cnt < ((CIRC_BUFFER_SMALL_U8t *)buffstruct)->size ; cnt++) {
			((CIRC_BUFFER_SMALL_U8t *)buffstruct)->buff[cnt] = 0;
		}
		return true;

	case BUFF_LARGE_U8 :
		((CIRC_BUFFER_LARGE_U8t *)buffstruct)->sidx = 0;
		((CIRC_BUFFER_LARGE_U8t *)buffstruct)->eidx = 0;
		((CIRC_BUFFER_LARGE_U8t *)buffstruct)->count = 0;
		((CIRC_BUFFER_LARGE_U8t *)buffstruct)->ovf = 0;

		for(cnt = 0; cnt < ((CIRC_BUFFER_LARGE_U8t *)buffstruct)->size ; cnt++) {
			((CIRC_BUFFER_LARGE_U8t *)buffstruct)->buff[cnt] = 0;
		}

		return true;
#endif
#ifdef USE_U16_DATA
	case BUFF_SMALL_U16 :
		((CIRC_BUFFER_SMALL_U16t *)buffstruct)->sidx = 0;
		((CIRC_BUFFER_SMALL_U16t *)buffstruct)->eidx = 0;
		((CIRC_BUFFER_SMALL_U16t *)buffstruct)->count = 0;
		((CIRC_BUFFER_SMALL_U16t *)buffstruct)->ovf = 0;

		for(cnt = 0; cnt < ((CIRC_BUFFER_SMALL_U16t *)buffstruct)->size ; cnt++) {
			((CIRC_BUFFER_SMALL_U16t *)buffstruct)->buff[cnt] = 0;
		}
		return true;

	case BUFF_LARGE_U16 :
		((CIRC_BUFFER_LARGE_U16t *)buffstruct)->sidx = 0;
		((CIRC_BUFFER_LARGE_U16t *)buffstruct)->eidx = 0;
		((CIRC_BUFFER_LARGE_U16t *)buffstruct)->count = 0;
		((CIRC_BUFFER_LARGE_U16t *)buffstruct)->ovf = 0;

		for(cnt = 0; cnt < ((CIRC_BUFFER_LARGE_U16t *)buffstruct)->size ; cnt++) {
			((CIRC_BUFFER_LARGE_U16t *)buffstruct)->buff[cnt] = 0;
		}
		return true;
#endif
	}
	return false;
}


/*************************************************************************
 * tmh_pop
 *   Pops data from a circular buffer.
 *   bs = the circular buffer structure, we auto determine the type of
 *   circular buffer.
 *   data = place to put data, we determine the correct type but
 *     caller must supply correct type
 *
 *   Returns
 *    false if no data to pop, or invalid circular buffer type
 */
uint8_t tmh_pop(void * bs, void * data ) {

	//get type of buffer,its the first byte of the struct
	TMH_BUFF_TYPE bt = (TMH_BUFF_TYPE)*(uint8_t*)bs;


	switch (bt) {
#ifdef USE_U8_DATA
	case BUFF_SMALL_U8 : {
		CIRC_BUFFER_SMALL_U8t *b = (CIRC_BUFFER_SMALL_U8t*)bs;
		// Do we have buffered  data
		if(  b->eidx != b->sidx ) {
				*(uint8_t *)data = b->buff[b->sidx];  //yes pop it
				// Advance pointer and check start pointer wrapped ?
				if(b->sidx >= (b->size-1) ) { //is it going to wrap?
					b->sidx = 0; // y
				} else
					b->sidx++; //n
				return true;
		} else
				return false;  //nothing to pop
		}
		break;
	case BUFF_LARGE_U8 : {
		CIRC_BUFFER_LARGE_U8t *b = (CIRC_BUFFER_LARGE_U8t*)bs;
		// Do we have buffered  data
		if(  b->eidx != b->sidx ) {
				*(uint8_t *)data = b->buff[b->sidx];  //yes pop it
				// Advance pointer and check start pointer wrapped ?
				if(b->sidx >= (b->size-1) ) { //is it going to wrap?
					b->sidx = 0; // y
				} else
					b->sidx++; //n
				return true;
		} else
				return false;  //nothing to pop
		}
		break;
#endif
#ifdef USE_U16_DATA
	case BUFF_SMALL_U16 : {
		CIRC_BUFFER_SMALL_U16t *b = (CIRC_BUFFER_SMALL_U16t*)bs;
		// Do we have buffered  data
		if(  b->eidx != b->sidx ) {
				*(uint16_t *)data = b->buff[b->sidx];  //yes pop it
				// Advance pointer and check start pointer wrapped ?
				if(b->sidx >= (b->size-1) ) { //is it going to wrap?
					b->sidx = 0; // y
				} else
					b->sidx++; //n
				return true;
		} else
				return false;  //nothing to pop
		}
		break;
	case BUFF_LARGE_U16 : {
		CIRC_BUFFER_LARGE_U16t *b = (CIRC_BUFFER_LARGE_U16t*)bs;
		// Do we have buffered  data
		if(  b->eidx != b->sidx ) {
				*(uint16_t *)data = b->buff[b->sidx];  //yes pop it
				// Advance pointer and check start pointer wrapped ?
				if(b->sidx >= (b->size-1) ) { //is it going to wrap?
					b->sidx = 0; // y
				} else
					b->sidx++; //n
				return true;
		} else
				return false;  //nothing to pop
		}
		break;
#endif
	default:
		return false;
	}


}


/*************************************************************************
 * tmh_push
 *   Push data to a circular buffer.Hanldes wrap, overwrites un-popped data
 *   bs = the circular buffer structure, we auto determine the type of
 *   circular buffer.
 *   data = data to push , we determine the correct type but
 *     caller must supply uint32_t
 *
 *   Returns
 *    false if invalid circular buffer type
 */
uint8_t tmh_push(void * bs, uint32_t data ) {

	//get type of buffer,its the first byte of the struct
	TMH_BUFF_TYPE bt = (TMH_BUFF_TYPE)*(uint8_t*)bs;

	switch (bt) {
#ifdef USE_U8_DATA
	case BUFF_SMALL_U8 : {
			CIRC_BUFFER_SMALL_U8t * b = (CIRC_BUFFER_SMALL_U8t*)bs;
			b->buff[ b->eidx] = (uint8_t)data;
			// Adjust  pointers
			if( b->eidx >= (b->size-1) ) {
				b->eidx = 0; //wrap
			} else
				b->eidx++;

			if (b->eidx == b->sidx) {  // overflow?
				b->ovf = true;
				b->sidx++; //yes discard
				if(b->sidx >= (b->size-1) ) { // wrap?
					b->sidx = 0;
				}
			}
			return true;  //always able to push
		}
		break;
	case BUFF_LARGE_U8 : {
		CIRC_BUFFER_LARGE_U8t * b = (CIRC_BUFFER_LARGE_U8t*)bs;
		b->buff[ b->eidx] = (uint8_t)data;
		// Adjust  pointers
		if( b->eidx >= (b->size-1) ) {
			b->eidx = 0; //wrap
		} else
			b->eidx++;

		if (b->eidx == b->sidx) {  // overflow?
			b->ovf = true;
			b->sidx++; //yes discard
			if(b->sidx >= (b->size-1) ) { // wrap?
				b->sidx = 0;
			}
		}
		return true;  //always able to push
	}
	break;
#endif
#ifdef USE_U16_DATA
	case BUFF_SMALL_U16 : {
		CIRC_BUFFER_SMALL_U16t * b = (CIRC_BUFFER_SMALL_U16t*)bs;
		b->buff[ b->eidx] = (uint16_t)data;
		// Adjust  pointers
		if( b->eidx >= (b->size-1) ) {
			b->eidx = 0; //wrap
		} else
			b->eidx++;

		if (b->eidx == b->sidx) {  // overflow?
			b->ovf = true;
			b->sidx++; //yes discard
			if(b->sidx >= (b->size-1) ) { // wrap?
				b->sidx = 0;
			}
		}
		return true;  //always able to push
	}
	break;
	case BUFF_LARGE_U16 : {
		CIRC_BUFFER_LARGE_U16t * b = (CIRC_BUFFER_LARGE_U16t*)bs;
		b->buff[ b->eidx] = (uint16_t)data;
		// Adjust  pointers
		if( b->eidx >= (b->size-1) ) {
			b->eidx = 0; //wrap
		} else
			b->eidx++;

		if (b->eidx == b->sidx) {  // overflow?
			b->ovf = true;
			b->sidx++; //yes discard
			if(b->sidx >= (b->size-1) ) { // wrap?
				b->sidx = 0;
			}
		}
		return true;  //always able to push
	}
	break;
#endif

	default:
		return false;
	}


}



