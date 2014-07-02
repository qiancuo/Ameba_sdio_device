#ifndef __BASIC_TYPES_H__
#define __BASIC_TYPES_H__
#include <linux/types.h>

#define _func_enter_ do{}while(0)
#define _func_exit_ do{}while(0)

#define SUCCESS	1
#define FAIL	0
#define _SUCCESS SUCCESS
#define _FAIL FAIL

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef TRUE
	#define _TRUE	1
#else
	#define _TRUE	TRUE	
#endif
		
#ifndef FALSE		
	#define _FALSE	0
#else
	#define _FALSE	FALSE	
#endif

#define IN
#define OUT
#define VOID void
typedef	signed int sint;

#ifndef	PVOID
typedef void * PVOID;
//#define PVOID	(void *)
#endif

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
#define u1Byte u8
#define u2Byte u16
#define u4Byte u32
#define UCHAR u8
#define USHORT u16
#define UINT u32
#define ULONG u32
#define s8 signed char
#define s16 signed short
#define s32 signed int

#define _RND(sz, r) ((((sz)+((r)-1))/(r))*(r))
#define RND4(x)	(((x >> 2) + (((x & 3) == 0) ?  0: 1)) << 2)
__inline static u32 _RND4(u32 sz)
{

	u32	val;

	val = ((sz >> 2) + ((sz & 3) ? 1: 0)) << 2;
	
	return val;

}

typedef void (*proc_t)(void*);

typedef 	__kernel_size_t	SIZE_T;	
typedef	__kernel_ssize_t	SSIZE_T;
#define FIELD_OFFSET(s,field)	((SSIZE_T)&((s*)(0))->field)
	

#define MEM_ALIGNMENT_OFFSET	(sizeof (SIZE_T))
#define MEM_ALIGNMENT_PADDING	(sizeof(SIZE_T) - 1)

#define SIZE_PTR SIZE_T
#define SSIZE_PTR SSIZE_T

//port from fw by thomas
// TODO: Belows are Sync from SD7-Driver. It is necessary to check correctness

/*
 *	Call endian free function when
 *		1. Read/write packet content.
 *		2. Before write integer to IO.
 *		3. After read integer from IO.
*/

//
// Byte Swapping routine.
//
#define EF1Byte	(u8)
#define EF2Byte 	le16_to_cpu
#define EF4Byte	le32_to_cpu

//
// Read LE format data from memory
//
#define ReadEF1Byte(_ptr)		EF1Byte(*((u8 *)(_ptr)))
#define ReadEF2Byte(_ptr)		EF2Byte(*((u16 *)(_ptr)))
#define ReadEF4Byte(_ptr)		EF4Byte(*((u32 *)(_ptr)))

//
// Write LE data to memory
//
#define WriteEF1Byte(_ptr, _val)	(*((u8 *)(_ptr)))=EF1Byte(_val)
#define WriteEF2Byte(_ptr, _val)	(*((u16 *)(_ptr)))=EF2Byte(_val)
#define WriteEF4Byte(_ptr, _val)	(*((u32 *)(_ptr)))=EF4Byte(_val)									

//
//	Example:
//		BIT_LEN_MASK_32(0) => 0x00000000
//		BIT_LEN_MASK_32(1) => 0x00000001
//		BIT_LEN_MASK_32(2) => 0x00000003
//		BIT_LEN_MASK_32(32) => 0xFFFFFFFF
//
#define BIT_LEN_MASK_32(__BitLen) \
	(0xFFFFFFFF >> (32 - (__BitLen)))
//
//	Example:
//		BIT_OFFSET_LEN_MASK_32(0, 2) => 0x00000003
//		BIT_OFFSET_LEN_MASK_32(16, 2) => 0x00030000
//
#define BIT_OFFSET_LEN_MASK_32(__BitOffset, __BitLen) \
	(BIT_LEN_MASK_32(__BitLen) << (__BitOffset)) 

//
//	Description:
//		Return 4-byte value in host byte ordering from
//		4-byte pointer in litten-endian system.
//
#define LE_P4BYTE_TO_HOST_4BYTE(__pStart) \
	(EF4Byte(*((u32 *)(__pStart))))

//
//	Description:
//		Translate subfield (continuous bits in little-endian) of 4-byte value in litten byte to
//		4-byte value in host byte ordering.
//
#define LE_BITS_TO_4BYTE(__pStart, __BitOffset, __BitLen) \
	( \
		( LE_P4BYTE_TO_HOST_4BYTE(__pStart) >> (__BitOffset) ) \
		& \
		BIT_LEN_MASK_32(__BitLen) \
	)

//
//	Description:
//		Mask subfield (continuous bits in little-endian) of 4-byte value in litten byte oredering  
//		and return the result in 4-byte value in host byte ordering.
//
#define LE_BITS_CLEARED_TO_4BYTE(__pStart, __BitOffset, __BitLen) \
	( \
		LE_P4BYTE_TO_HOST_4BYTE(__pStart) \
		& \
		( ~BIT_OFFSET_LEN_MASK_32(__BitOffset, __BitLen) ) \
	)

//
//	Description:
//		Set subfield of little-endian 4-byte value to specified value.	
//
#define SET_BITS_TO_LE_4BYTE(__pStart, __BitOffset, __BitLen, __Value) \
	*((u32 *)(__pStart)) = \
		EF4Byte( \
			LE_BITS_CLEARED_TO_4BYTE(__pStart, __BitOffset, __BitLen) \
			| \
			( (((u32)__Value) & BIT_LEN_MASK_32(__BitLen)) << (__BitOffset) ) \
		);

		
#define BIT_LEN_MASK_16(__BitLen) \
		(0xFFFF >> (16 - (__BitLen)))
		
#define BIT_OFFSET_LEN_MASK_16(__BitOffset, __BitLen) \
	(BIT_LEN_MASK_16(__BitLen) << (__BitOffset))
	
#define LE_P2BYTE_TO_HOST_2BYTE(__pStart) \
	(EF2Byte(*((u16 *)(__pStart))))
	
#define LE_BITS_TO_2BYTE(__pStart, __BitOffset, __BitLen) \
	( \
		( LE_P2BYTE_TO_HOST_2BYTE(__pStart) >> (__BitOffset) ) \
		& \
		BIT_LEN_MASK_16(__BitLen) \
	)
	
#define LE_BITS_CLEARED_TO_2BYTE(__pStart, __BitOffset, __BitLen) \
	( \
		LE_P2BYTE_TO_HOST_2BYTE(__pStart) \
		& \
		( ~BIT_OFFSET_LEN_MASK_16(__BitOffset, __BitLen) ) \
	)

#define SET_BITS_TO_LE_2BYTE(__pStart, __BitOffset, __BitLen, __Value) \
	*((u16 *)(__pStart)) = \
		EF2Byte( \
			LE_BITS_CLEARED_TO_2BYTE(__pStart, __BitOffset, __BitLen) \
			| \
			( (((u16)__Value) & BIT_LEN_MASK_16(__BitLen)) << (__BitOffset) ) \
		);
			
#define BIT_LEN_MASK_8(__BitLen) \
		(0xFF >> (8 - (__BitLen)))

#define BIT_OFFSET_LEN_MASK_8(__BitOffset, __BitLen) \
	(BIT_LEN_MASK_8(__BitLen) << (__BitOffset))

#define LE_P1BYTE_TO_HOST_1BYTE(__pStart) \
	(EF1Byte(*((u8 *)(__pStart))))

#define LE_BITS_TO_1BYTE(__pStart, __BitOffset, __BitLen) \
	( \
		( LE_P1BYTE_TO_HOST_1BYTE(__pStart) >> (__BitOffset) ) \
		& \
		BIT_LEN_MASK_8(__BitLen) \
	)

#define LE_BITS_CLEARED_TO_1BYTE(__pStart, __BitOffset, __BitLen) \
	( \
		LE_P1BYTE_TO_HOST_1BYTE(__pStart) \
		& \
		( ~BIT_OFFSET_LEN_MASK_8(__BitOffset, __BitLen) ) \
	)

#define SET_BITS_TO_LE_1BYTE(__pStart, __BitOffset, __BitLen, __Value) \
	*((u8 *)(__pStart)) = \
		EF1Byte( \
			LE_BITS_CLEARED_TO_1BYTE(__pStart, __BitOffset, __BitLen) \
			| \
			( (((u8)__Value) & BIT_LEN_MASK_8(__BitLen)) << (__BitOffset) ) \
		);


#define LE_BITS_CLEARED_TO_2BYTE_16BIT(__pStart, __BitOffset, __BitLen) \
	( \
		LE_P2BYTE_TO_HOST_2BYTE(__pStart) \
	)

#define SET_BITS_TO_LE_2BYTE_16BIT(__pStart, __BitOffset, __BitLen, __Value) \
	*((u16 *)(__pStart)) = \
		EF2Byte( \
			LE_BITS_CLEARED_TO_2BYTE_16BIT(__pStart, __BitOffset, __BitLen) \
			| \
			( (u16)__Value) \
		);

#define LE_BITS_CLEARED_TO_1BYTE_8BIT(__pStart, __BitOffset, __BitLen) \
	( \
		LE_P1BYTE_TO_HOST_1BYTE(__pStart) \
	)

#define SET_BITS_TO_LE_1BYTE_8BIT(__pStart, __BitOffset, __BitLen, __Value) \
{ \
	*((u8 *)(__pStart)) = \
		EF1Byte( \
			LE_BITS_CLEARED_TO_1BYTE_8BIT(__pStart, __BitOffset, __BitLen) \
			| \
			((u8)__Value) \
		); \
}

// Get the N-bytes aligment offset from the current length
#define N_BYTE_ALIGMENT(__Value, __Aligment) ((__Aligment == 1) ? (__Value) : (((__Value + __Aligment - 1) / __Aligment) * __Aligment))

typedef unsigned char	BOOLEAN,*PBOOLEAN;

#define TEST_FLAG(__Flag,__testFlag)		(((__Flag) & (__testFlag)) != 0)
#define SET_FLAG(__Flag, __setFlag)			((__Flag) |= __setFlag)
#define CLEAR_FLAG(__Flag, __clearFlag)		((__Flag) &= ~(__clearFlag))
#define CLEAR_FLAGS(__Flag)					((__Flag) = 0)
#define TEST_FLAGS(__Flag, __testFlags)		(((__Flag) & (__testFlags)) == (__testFlags))

#endif //__BASIC_TYPES_H__


