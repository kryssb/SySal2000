


#include "stdafx.h"
#include "FogScanningStructs.h"





void SScanningPoint::AddPoint(SScanningPoint * pNewPoint)//AddNext()
{
	if(pNext)
	{
		pNext->pPrevious = pNewPoint;
		pNewPoint->pNext = pNext;
		pNext = pNewPoint;
	}
	else
	{
		pNewPoint->pNext = NULL;
		pNext = pNewPoint;
	}
	pNewPoint->pPrevious = this;
}

void SScanningPoint::Delete()
{
	if(pPrevious)
	{
		pPrevious->pNext = pNext;
		if(pNext)pNext->pPrevious = pPrevious;
	}
	else if(pNext)pNext->pPrevious = NULL;
	delete(this);
}


UINT SScanningPoint::Load(FILE * pFile)
{
	int StringSize;
	char * theString = NULL;
	fread(&StepX,sizeof(float),1,pFile);
	fread(&NumStepX,sizeof(float),1,pFile);
	fread(&StepY,sizeof(float),1,pFile);
	fread(&NumStepY,sizeof(float),1,pFile);
	fread(&X,sizeof(float),1,pFile);
	fread(&Y,sizeof(float),1,pFile);
	fread(&ResumedX,sizeof(int),1,pFile);
	fread(&ResumedY,sizeof(int),1,pFile);
	fread(&Options,sizeof(UINT),1,pFile);
	fread(&StringSize,sizeof(int),1,pFile);
	theString = Directory.GetBuffer(StringSize + 1);
	if(theString)fread(theString,StringSize,1,pFile);
	*(theString + StringSize) = 0;
	Directory.ReleaseBuffer();
	fread(&StringSize,sizeof(int),1,pFile);
	theString = FileNames.GetBuffer(StringSize + 1);
	*(theString + StringSize) = 0;
	if(theString)fread(theString,StringSize,1,pFile);
	FileNames.ReleaseBuffer();

	return 0;
}


UINT SScanningPoint::Save(FILE * pFile)
{
	int written,StringSize;
	written = fwrite(this,sizeof(float)*6 + sizeof(int)*2 + sizeof(UINT),1,pFile);
	StringSize = Directory.GetLength();
	written = fwrite(&StringSize,sizeof(int),1,pFile);
	written = fwrite(*((char **)(&Directory)),StringSize,1,pFile);
	StringSize = FileNames.GetLength();
	written = fwrite(&StringSize,sizeof(int),1,pFile);
	written = fwrite(*((char **)(&FileNames)),StringSize,1,pFile);

	return 0;
}