#ifndef _SYSAL_CAMERA_SPECS_
#define _SYSAL_CAMERA_SPECS_

typedef struct 
{
	unsigned Width;
	unsigned Height;
	unsigned OffX;
	unsigned OffY;
	unsigned WinWidth;
	unsigned WinHeight;
	float PixelToMicronX;
	float PixelToMicronY;
	} CameraSpec;

#endif