#ifndef _FRAME_GRABBER_DEFS_
#define _FRAME_GRABBER_DEFS_

#define VC_BLACK 		0x0
#define VC_DKBLUE 		0x1
#define VC_DKGREEN 		0x2
#define VC_DKCYAN 		0x3
#define VC_DKRED 		0x4
#define VC_DKMAGENTA	0x5
#define VC_DKYELLOW 	0x6
#define VC_DKGRAY 		0x7
#define VC_LTGRAY 		0x8
#define VC_LTBLUE 		0x9
#define VC_LTGREEN 		0xA
#define VC_LTCYAN 		0xB
#define VC_LTRED 		0xC
#define VC_LTMAGENTA	0xD
#define VC_LTYELLOW 	0xE
#define VC_WHITE 		0xF
#define VC_TRANSPARENT	-1

#define VC_NO_COLORCODE -1

// Stock Cursors

#define VC_STOCKCURSORS_CROSS		1
#define VC_STOCKCURSORS_AREA5		0x21
#define VC_STOCKCURSORS_AREA9		0x22
#define VC_STOCKCURSORS_AREA16		0x23
#define VC_STOCKCURSORS_AREA25		0x24

//	VIDEOINFOSTRUCT - Structure containing data about the video display config.

typedef struct 
{
	WORD Width;        				// Width of display allocated
	WORD Height;					// Height of display allocated
	DWORD PageSize;					// Size of display buffer
	DWORD ColorsNumber;				// Number of colors supported
	DWORD DefaultColorsNumber;		// Number of default colors
	DWORD WhereDefault;				// First default color
	DWORD ReservedColor;			// Color reserved for overlay function
	BYTE DataSize;					//	Size of color pixel data
	BYTE Planes;					// Number of planes
	} VIDEOINFOSTRUCT;


//	GRABBERINFOSTRUCT - Structure containing data about the grabber config.

typedef struct 
{
	WORD Width;						// Width of grabber buffer
	WORD Height;					// Height of grabber buffer
	DWORD ColorsNumber;				// Number of colors supported
	BYTE DataSize;					// Size of color pixel data
	BYTE Planes;					// Number of planes
	BYTE Synchronization;			// Type of synchronization
	BYTE LiveMode;					// Live grabbing available flag
	BYTE PagesNumber;				// Number of pages internally allocated
	DWORD PageSize;					// Size of one page buffer
	} GRABBERINFOSTRUCT;

#define VC_GRAB_SYNC 0
#define VC_GRAB_ASYNC 1
#define VC_GRAB_LIVE_NO 0
#define VC_GRAB_LIVE_YES 1

#define VC_NO_GRAB 0
#define VC_GRAB_LIVE 1
#define VC_GRAB_SINGLE_FRAME 2

// PALETTESTRUCT - Structure containing color palette information

typedef struct 
{
	DWORD ColorsNumber;				// Number of colors supported
	BYTE ColorSize;					// Size of color information
	BYTE IsByPlane;					// Planes interleave device flag
	BYTE *PaletteData;				//	User - defined area for palette data
	} PALETTESTRUCT;

#endif