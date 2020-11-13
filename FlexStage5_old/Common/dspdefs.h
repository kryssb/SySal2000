#ifndef _SYSAL_DISPATCHER_DEFINES_
#define _SYSAL_DISPATCHER_DEFINES_

#pragma pack(push)
#pragma pack(1)

#include "id.h"

#define MSG_FULL_SECTION				0x1

#define MSG_DATA_BYTES					0x70
#define MSG_HEADER_BYTES				0x70

#define MSG_HEADER_TYPE_1				0x0001

typedef struct 
{
	IO_Header Hdr;
	UINT Length;
	int Reserved[4];
	BYTE Message[1];
	} IO_Message;

#pragma pack(pop)


#endif
