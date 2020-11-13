#ifndef _SYSAL_IMAGE_LIBRARY_
#define _SYSAL_IMAGE_LIBRARY_

#include <windows.h>
#include <afxwin.h>

class ImageLibrary
{
public:
	struct ImageDescriptor
	{
		int Width;
		int Height;
		BYTE *pStart;		
		};

	ImageLibrary();
	virtual ~ImageLibrary();

protected:
	int Count;
	ImageDescriptor *pDescriptors;
	BYTE *pImages;
	int ImgLibWidth;
	int ImgLibHeight;
	BITMAPINFO ImgBMInfo;
	RGBQUAD ImgBMColors[255];
public:
	int GetCount() { return Count; }
	ImageDescriptor GetImageDescriptor(int i) { return pDescriptors[i]; }
	RGBQUAD *GetPaletteEntries() { return ImgBMInfo.bmiColors; }
	virtual bool SetImage(int index, BYTE *pimg, int w, int h) = 0;
	virtual bool DelImage(int index) = 0;	
	virtual void ShowLibrary(CDC &dc) = 0;
	virtual bool SaveLibrary(LPCSTR filename) = 0;
	};

#endif