#include "StdAfx.h"
#include "ImageLibrary.h"

// Image Library
ImageLibrary::ImageLibrary()
{
	pImages = 0;
	ImgLibWidth = 0;
	ImgLibHeight = 0;	
	ImgBMInfo.bmiHeader.biBitCount = 8;
	ImgBMInfo.bmiHeader.biClrImportant = 256;
	ImgBMInfo.bmiHeader.biClrUsed = 256;
	ImgBMInfo.bmiHeader.biCompression = BI_RGB;
	ImgBMInfo.bmiHeader.biHeight = 0;
	ImgBMInfo.bmiHeader.biPlanes = 1;
	ImgBMInfo.bmiHeader.biSize = sizeof(ImgBMInfo.bmiHeader);
	ImgBMInfo.bmiHeader.biSizeImage = 0;
	ImgBMInfo.bmiHeader.biWidth = 0;
	ImgBMInfo.bmiHeader.biXPelsPerMeter = 10000;
	ImgBMInfo.bmiHeader.biYPelsPerMeter = 10000;
	int i;
	for (i = 0; i < 256; i++)
	{
		ImgBMInfo.bmiColors[i].rgbBlue = i;
		ImgBMInfo.bmiColors[i].rgbGreen = i;
		ImgBMInfo.bmiColors[i].rgbRed = i;
		ImgBMInfo.bmiColors[i].rgbReserved = 0;
		}
	Count = 0;
	pDescriptors = 0;
	}

ImageLibrary::~ImageLibrary()
{
	if (pDescriptors) free(pDescriptors);
	if (pImages) GlobalFree(pImages);
	}

// End Image Library
