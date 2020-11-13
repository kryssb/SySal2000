#ifndef _SYSAL_CAMERA_SPECS2_
#define _SYSAL_CAMERA_SPECS2_

#ifdef USE_MIDL_INCOMPATIBLE_STRUCTS
struct CameraSpec2 : public CameraSpec
{
	float RefractiveShrinkage;
	};
#else
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
	float RefractiveShrinkage;
	} CameraSpec2;
#endif
#endif