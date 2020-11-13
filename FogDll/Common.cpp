
#include "stdafx.h"
#include "common.h"

int GetFloat(CWnd * pContext,UINT IDC,float &ToGet)
{
	CString myString;
	int Value = 0;
	pContext->GetDlgItem(IDC)->GetWindowText(myString);
	Value = sscanf(myString,"%f",&ToGet);
	if(Value != 1){ ToGet = 0; pContext->GetDlgItem(IDC)->SetWindowText("0.0");}
	return Value;
};

//int CGrainFinder::compare(const void *elem1, const void *elem2)
int CompareIntGrainXD(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*(((SIntGrain *)elem2)->x - ((SIntGrain *)elem1)->x));
};
int CompareIntGrainXA(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*(((SIntGrain *)elem1)->x - ((SIntGrain *)elem2)->x));
};
int CompareIntGrainYD(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*(((SIntGrain *)elem2)->y - ((SIntGrain *)elem1)->y));
};
int CompareIntGrainYA(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*(((SIntGrain *)elem1)->y - ((SIntGrain *)elem2)->y));
};
int CompareIntGrainZD(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*(((SIntGrain *)elem2)->z - ((SIntGrain *)elem1)->z));
};
int CompareIntGrainZA(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*(((SIntGrain *)elem1)->z - ((SIntGrain *)elem2)->z));
};

int CompareIntGrainPointerXD(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*((*((SIntGrain **)elem2))->x - (*((SIntGrain **)elem1))->x));
};
int CompareIntGrainPointerXA(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*((*((SIntGrain **)elem1))->x - (*((SIntGrain **)elem2))->x));
};
int CompareIntGrainPointerYD(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*((*((SIntGrain **)elem2))->y - (*((SIntGrain **)elem1))->y));
};
int CompareIntGrainPointerYA(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*((*((SIntGrain **)elem1))->y - (*((SIntGrain **)elem2))->y));
};
int CompareIntGrainPointerZD(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*((*((SIntGrain **)elem2))->z - (*((SIntGrain **)elem1))->z));
};
int CompareIntGrainPointerZA(const void * elem1,const void * elem2)
{
	return (int)(1000000.f*((*((SIntGrain **)elem1))->z - (*((SIntGrain **)elem2))->z));
};

void SetFloat(CWnd * pContext,UINT IDC,float ToSet,const char * pFormat)
{
	CString myString;
	if(pFormat == NULL)myString.Format("%.3f",ToSet);
	else myString.Format(pFormat,ToSet);
	pContext->SetDlgItemText(IDC,myString);
};

int GetInteger(void * pContext,UINT IDC,int &ToGet)
{
	CString text;
	((CWnd *)pContext)->GetDlgItemText(IDC,text);
	return sscanf(text,"%d",&ToGet);
}

int SetInteger(void * pContext,UINT IDC,int ToSet)
{
	CString text;
	text.Format("%d",ToSet);
	((CWnd *)pContext)->SetDlgItemText(IDC,text);
	return 0;
}

void SGrain::ToLongGrain(SLongGrain &Lg)
{	
	int XWidth;
	if(NewType)XWidth = 1280; else XWidth = 1024;
	Lg.x = x;
	Lg.y = y;
	Lg.z = z;
	Lg.Min = Min;
	Lg.Mean = (short)(Mean + 128);
	Lg.Max = (short)(Max + 128);
	Lg.PrevMin = (short)(Min + DeltaPrevMin);
	Lg.NextMin = (short)(Min + DeltaNextMin);
	Lg.PrevMean = (short)(Mean + DeltaPrevMean + 128);
	Lg.NextMean = (short)(Mean + DeltaNextMean + 128);
	Lg.PrevMax = (short)(Max + DeltaPrevMax + 128);
	Lg.NextMax = (short)(Max + DeltaNextMax + 128);
	Lg.PrevMinPos = (short)((PrevMinPos/3)*XWidth + PrevMinPos%3 - XWidth - 1);
	Lg.NextMinPos = (short)((NextMinPos/3)*XWidth + NextMinPos%3 - XWidth - 1);
}

	SGrain::SGrain(SLongGrain &L)
{		
		int XWidth = 1280;
		x = L.x;
		y = L.y;
		z = L.z;
		Min = L.Min;
		Mean = L.Mean > 127 ? L.Mean - 128 : 0;
		Max = L.Max > 127 ? L.Max - 128 : 0;
		register short worker;
		worker = L.PrevMin - L.Min;
		DeltaPrevMin = (worker > 63 ? 63 : worker);
		worker = L.NextMin - L.Min;
		DeltaNextMin = (worker > 63 ? 63 : worker);
		worker = L.PrevMean - L.Mean;
		if(worker > 31)worker = 31; else if(worker < -31)worker = -31;
		DeltaPrevMean = worker;
		worker = L.NextMean - L.Mean;
		if(worker > 31)worker = 31; else if(worker < -31)worker = -31;
		DeltaNextMean = worker;
		worker = L.PrevMax - L.Max;
		if(worker > 63)worker = 63; else if(worker < -63)worker = -63;
		DeltaPrevMax = worker;
		worker = L.NextMax - L.Max;
		if(worker > 63)worker = 63; else if(worker < -63)worker = -63;
		DeltaNextMax = worker;
		PrevMinPos = (L.PrevMinPos + XWidth + 1)%XWidth + 3*((L.PrevMinPos + XWidth + 1)/XWidth);
		NextMinPos = (L.NextMinPos + XWidth + 1)%XWidth + 3*((L.NextMinPos + XWidth + 1)/XWidth);
}

float SEmulsionSpace::CheckDensity()
{
	float minx=1000,maxx=-1000,miny=1000,maxy=-1000;
	float sizex,sizey,sizez,minz=NOT_USED_DEPTH,maxz=-NOT_USED_DEPTH;
	int i,MinZPos = 0,MaxZPos = NumGrains;
	if(NumGrains == 0)return 0.0;
	for(i=MinZPos;i<MaxZPos;i++)
	{	SIntGrain &grain = *(pGrains + i);
		minx > grain.x ? minx = grain.x : minx;
		maxx < grain.x ? maxx = grain.x : maxx;
		miny > grain.y ? miny = grain.y : miny;
		maxy < grain.y ? maxy = grain.y : maxy;
		minz > grain.z ? minz = grain.z : minz;
		maxz < grain.z ? maxz = grain.z : maxz;	}
	minx = minx - 2.f;maxx = maxx + 2.f;
	miny = miny - 2.f; maxy = maxy + 2.f;
	minz = minz - 2.f; maxz = maxz + 2.f;
	Diagonal.x = sizex = maxx-minx;
	Diagonal.y =  miny-maxy;
	sizey = maxy-miny;
	Diagonal.z = sizez = maxz-minz;
	LowerCorner.x = minx;	LowerCorner.y = maxy;	LowerCorner.z = minz;
	UpperCorner.x = maxx;	UpperCorner.y = miny;	UpperCorner.z = maxz;	
	Volume = sizex*sizey*sizez;
	Density = (MaxZPos - MinZPos)*1000.f/Volume;
	CString Text;
	int mean,index = 0,MinMiddleBin = 1000,MMBIndex,NumBins,NotZeroBins;
	int rangemin,rangemax;
	float surfaceArea,minbin = 0, maxbin = 0,DeadZoneMaxZ,DeadZoneMinZ,midZ;
	NumBins = (int)(1 + 5*(maxz - minz));
	int *pBins = (int *)calloc(NumBins,sizeof(int));
	NotZeroBins = 0;
	for(i = 0; i < NumGrains; i++)(*(pBins + (int)(5*((pGrains + i)->z - minz))))++;
	for(i = 0; i < NumBins; i++){if(*(pBins + i) > 0)NotZeroBins++;}
	mean = (int)NumGrains/NotZeroBins;
	for(i = 0; i < NumBins; i++)if(*(pBins + i) < mean/2)minbin += 0.2f;else break;
	for(i = NumBins - 1; i >= 0; i--)if(*(pBins + i) < mean/2)maxbin += 0.2f;else break;
	midZ = ((maxz - maxbin) + (minz + minbin))/2.f;
	rangemin = 5*(int)(midZ - minz - 5);
	rangemax = 5*(int)(midZ - minz + 5);
	rangemin < 1 ? rangemin = 1 : rangemin;
	rangemax > NumBins ? rangemax = NumBins : rangemax;
	for(i = rangemin; i < rangemax + 1; i++)
	{	if(MinMiddleBin > *(pBins + i))
		{	MinMiddleBin = *(pBins + i);
			MMBIndex = i;	}	}
	DeadZoneMaxZ = minz + 0.2f * MMBIndex;
	DeadZoneMinZ = DeadZoneMaxZ;
	if(MMBIndex > 10)
	{	for(i = MMBIndex; i > MMBIndex - 10; i--)
            if(*(pBins + i) < mean/2)DeadZoneMinZ -= 0.2f;
			else break;		}
	else	MessageBox(NULL,"Abnormal Density distribution","Emulsion Space",MB_OK);
	if(MMBIndex < 590)
	{   for(i = MMBIndex; i < MMBIndex + 10; i++)
			if(*(pBins + i) < mean/2)DeadZoneMaxZ += 0.2f;
			else break;	}
	else 	MessageBox(NULL,"Abnormal Density distribution","Emulsion Space",MB_OK);
	free(pBins);
	ZetaRange.BottomZ = minz + minbin;
	ZetaRange.DeadZoneDw = DeadZoneMinZ;
	ZetaRange.DeadZoneUp = DeadZoneMaxZ;
	ZetaRange.MaxZ = maxz - 1.0f;
	ZetaRange.MinZ = minz + 1.0f;
	ZetaRange.UpperZ = maxz - maxbin;
	ZetaRange.MaxX = maxx;	ZetaRange.MinX = minx;
	ZetaRange.MaxY = maxy;	ZetaRange.MinY = miny;
	surfaceArea = (maxx - minx - 8.0f)*(maxy - miny - 8.0f);
	AdjustedDensity = NumGrains/(((maxz - maxbin) - (minz + minbin) - (DeadZoneMaxZ - DeadZoneMinZ))*surfaceArea/1000.f);
	return AdjustedDensity;
}

int SEmulsionSpace::Purge()
{
	CheckDensity();
	int StartNum = NumGrains;
	float RefBottom = ZetaRange.BottomZ - 4,RefUp = ZetaRange.UpperZ + 4;
	SIntGrain Null;
	for(int i = 0; i < NumGrains; i++)
	{
		if((pGrains + i)->z > RefUp || (pGrains + i)->z < RefBottom)
		{
			*(pGrains + i) = *(pGrains + NumGrains - 1);
			*(pGrains + NumGrains - 1) = Null;
			NumGrains--;
			i--;
		}
	}
	return StartNum - NumGrains;
}

void SEmulsionSpace::GetSpace()
{
	if(pGrains!=NULL)free(pGrains);
	memset(this,0,sizeof(SEmulsionSpace));
	pGrains = (SIntGrain *)malloc(2048*sizeof(SIntGrain));
	Allocated = 2048;
}

void STrackingInfo::SetPhiInterval(float startPhi, float endPhi)
{
	if(startPhi > endPhi)
	{
		StartPhi = endPhi;
		EndPhi = startPhi;
	}
	else
	{
		StartPhi = startPhi;
		EndPhi = endPhi;
	}
}

void FromFullPathFileName(CString & FullPath)
{
	int LastSlashPos,len;
	len = FullPath.GetLength();
	LastSlashPos = FullPath.ReverseFind('\\');
	if(LastSlashPos != -1)FullPath = FullPath.Right(len - LastSlashPos - 1);
}

void FromFullPathDirectory(CString & FullPath,bool IncludeSlash)
{
	int SlashPos = FullPath.ReverseFind('\\');
	if(IncludeSlash)SlashPos++;
	FullPath = FullPath.Left(SlashPos);
}
void ErrorMessage(DWORD Err)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,NULL,Err,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)// Default language
  ,(LPTSTR) &lpMsgBuf,0,NULL);// Process any inserts in lpMsgBuf.	
	MessageBox(NULL,(LPCTSTR)lpMsgBuf,NULL,MB_OK | MB_ICONINFORMATION );// Display the string. 
}
