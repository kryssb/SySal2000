#ifndef _MARK_MAP_DATA_STRUCTURES_
#define _MARK_MAP_DATA_STRUCTURES_

#pragma pack(push)
#pragma pack(1)

#include "id.h"
#include "MarkMap.h"
#include "MarkMap2.h"
#include "MarkMap3.h"

#define MAP_FULL_SECTION				0xA

#define MAP_DATA_BYTES					0x60
#define MAP_HEADER_BYTES				0x60

#define MAP_MARK_HEADER_TYPE			0x0001
#define MAP_MARKEXT_HEADER_TYPE			0x0002
#define MAP_MARKX_HEADER_TYPE			0x0003

typedef struct 
{
	IO_HeaderId Hdr;
	union
	{
		MarkMap Map;
		MarkMap2 Map2;
		MarkMap3 Map3;
		};
	} IO_MarkMap;

#pragma pack(pop)

#endif