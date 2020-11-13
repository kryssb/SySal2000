// GrainFinder.cpp: implementation of the CGrainFinder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "FindGrainsThreadDlg.h"
#include "GrainFinder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//typedef unsigned char GrainRaw[25];


CString LogFilePath("C:\\SySal2000\\Fog2000\\Data\\GrainFinderLog.txt");
extern CString DebugFilePath;

static float GlobalGFfloat;
static int GlobalGFint1;
static int GlobalGFint2;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGrainFinder::CGrainFinder(SGFContext *Context)
{
	int i;
	CAPoints = NULL;
	CSFPointers = NULL;
//	mpZetas = (int *)calloc(sizeof(int),601);
//	mpGoodOne = (int *)calloc(sizeof(int),601);
	m_pMinGrains = (SGrain *)malloc(sizeof(SGrain)*1024);
	m_NumMin = 1024;
	m_depths = (float *)malloc(sizeof(float)*256);
	for(i=0;i<256;i++)*(m_depths + i) = NOT_USED_DEPTH;
	m_pImageData = NULL;//(BYTE *)malloc(1048576*5);
	m_Session = 0;
	if(Context != NULL)GFC = *Context;
	SSheet temp = {0,0,0,0,0,0,0,0,0,0};
	m_Sheet = temp;
	m_pOffsets = (int *)calloc(sizeof(int),MAX_NUMBER_OF_IMAGES);
	m_MicData.pDepths = m_depths;
	m_MicData.pSpaceUp = &m_EmSpaceUp;
	m_MicData.pSpaceDw = &m_EmSpaceDw;
	m_MicData.LevelsUp = 0;
	m_MicData.LevelsDw = 0;
	m_MicData.Level = 0;
	m_MicData.HasImages = false;
	m_MicData.pOperaData = &m_PredData.D;
}

CGrainFinder::~CGrainFinder()
{
	if(m_pMinGrains != NULL)free(m_pMinGrains);
	if(m_depths != NULL)free(m_depths);
	if(m_pOffsets != NULL)free(m_pOffsets);
	if(CSFPointers != NULL)free(CSFPointers);
	if(CAPoints != NULL)free(CAPoints);
}


int CGrainFinder::ComputeData(int frame,SGrain ** ppMinGrains,int * pNumMin,SEmulsionSpace * space,float * depths,UINT Options)
{
	if(m_pImageData == NULL)return 4;
	if(ppMinGrains == NULL)ppMinGrains = &m_pMinGrains;
	if(pNumMin == NULL)pNumMin = &m_NumMin;
	if(space == NULL)space = &m_EmSpaceUp;
	if(depths == NULL)depths = m_depths;
	if(Options == 0)Options = GFC.pGFTParam->Options;
	SEmulsionSpace & Space = *space;
	int l,m,i,j,k,ImageDivision,leftmargin,rightmargin,sommap,beta,Cursor,Margin,SommaTot = 0;
	int divisionx,divisiony;
	//                        External Parameters
	int Threshold,Delta,IsDifferential,ParentParameters = Options & FOG_OPT_PARENTPARAM;
	int Statistics = Options & FOG_OPT_STATISTICS;
	bool InvertXY = GFC.pGfPa->InvertXY;
	//						Function Body
	BYTE * pointer,* pAlfa,alfa;
	BYTE maxb = 0,minb = 255;
	int NumGrains = Space.NumGrains,LastNumGrains = NumGrains;
	if(ParentParameters && GFC.pGetComputingParameters)
		GFC.pGetComputingParameters(GFC.pContext,Threshold,ImageDivision,Delta);
	else{	Threshold = GFC.pGfPa->Threshold;
		ImageDivision = GFC.pGfPa->CellSize;
		Delta = GFC.pGfPa->Delta;	}
	if(GFC.pLastNumGrains != NULL)*(GFC.pLastNumGrains) = LastNumGrains;
	Margin = GFC.pGfPa->MaxImagesOffset;
	IsDifferential = Options & 1;
	if(ParentParameters && GFC.pIsDifferential)IsDifferential = GFC.pIsDifferential(GFC.pContext);
	int ImageSize = mImageSize;
	divisionx = (mXWidth-2*Margin)/ImageDivision;
	divisiony = (mYWidth-2*Margin)/ImageDivision;
	leftmargin = Margin + (int)(((float)((mXWidth-2*Margin)%ImageDivision))/2 + 0.51);
	rightmargin = Margin + (int)(((float)((mXWidth-2*Margin)%ImageDivision))/2);
//	int ImageOffSet = FindOffset(ImageDataP[2],ImageDataP[3],128);
	int kmin = 1,kmax = 2;//kmin = 0,kmax = 3;
//	int x;
	k = 1;
//	int & Level = m_MicData.Level;
	BYTE * pData = m_pImageData + ImageSize*frame;
//	if(!(Level == frame))MessageBox(NULL,"MicData Error","Check This",MB_OK);
	for(l=0; l < divisionx; l++)
	{	for(m=0; m<divisiony; m++)
		{
			Cursor = l*ImageDivision + m*ImageDivision*mXWidth + leftmargin*(1 + mXWidth);
			beta = 255;
			sommap = 0;
//			pointer = ImageDataP[2] + Cursor;
			pointer = pData + Cursor;
//			for(k = kmin; k < kmax; k++)			// L'insieme di tre immagini viene diviso in settori dei quali si 
			{
				for(i=0; i < ImageDivision; i++)	// cerca il minimo. Se questo è minore di un valore fissato dall'esterno
				{
					for(j=0; j < ImageDivision; j++)// si registrano le coordinate locali su un array.
					{
						pAlfa = m_pImageData + ImageSize*(frame - 2 + k) + Cursor + i + j*mXWidth;
						pAlfa = m_pImageData + ImageSize*frame + Cursor + i + j*mXWidth;
						alfa = *pAlfa;
						if(Statistics)
						{
							sommap += alfa;
							SommaTot += alfa;
							if(alfa > maxb)maxb = alfa;//(maxb > alfa ? maxb :maxb =  alfa);
							(minb < alfa ? minb :minb =  alfa);
						}
						if(alfa <= beta)(beta = alfa,pointer = pAlfa);// <= _> Minimum will be the one in the last frame.
/*							z = frame - 1 + k;// Attenzione zeta indica il frame a partire da uno.
							y = leftmargin + m*ImageDivision + j + 1;
							x = leftmargin + l*ImageDivision + i + 1;*/
					}
				}
			}
			if(GrainTest(*ppMinGrains + NumGrains,frame,pointer,Delta,Threshold,Options))
				NumGrains++;
			if(NumGrains==*pNumMin)
			{
				SGrain * pMinGrains = (SGrain *)realloc(*ppMinGrains,(*pNumMin+=4096)*sizeof(SGrain));
				if(pMinGrains == NULL)return 2;
				*ppMinGrains = pMinGrains;
			}	
		}
	}
	int TempNumGrains = LastNumGrains;
	float PixLength = GFC.pMicPar->PixLen;
	if(Space.pGrains == NULL)Space.GetSpace();
	SDistortion * pDistortion = &Space.Distortion;
	if(Options & FOG_OPT_MANUALCOMPUTE)pDistortion = NULL;
	for(i=LastNumGrains;i<NumGrains;i++)
	{
		SIntGrain &gr = *(Space.pGrains + TempNumGrains++);
		(*(*ppMinGrains + TempNumGrains - 1)).ToIntGrain(&gr,depths,GFC.pMicPar,InvertXY,pDistortion);
		if(TempNumGrains==Space.Allocated)
		{
			SIntGrain * WorkPointer;
			WorkPointer = (SIntGrain *)realloc(Space.pGrains,(Space.Allocated+=2048)*sizeof(SIntGrain));
			if(WorkPointer == NULL)return 3;
			Space.pGrains = WorkPointer;
		}
	}
	if(Statistics && GFC.pSetInteger)
	{
		GFC.pSetInteger(GFC.pContext,GFC.pIdc->Minimo,minb);
		GFC.pSetInteger(GFC.pContext,GFC.pIdc->Massimo,maxb);
		int NumBytes = divisionx*divisiony*ImageDivision*ImageDivision;
		int result;
		GFC.pSetInteger(GFC.pContext,GFC.pIdc->Medio,SommaTot/NumBytes);
	}
	Space.NumGrains = NumGrains;
	return 0;
}


WORD * CGrainFinder::ComputeArea(BYTE * pImage,int PosX,int PosY,int HalfSizeX,int HalfSizeY)
{
	// PosX e PosY partono da 0;
	UINT Options = GFC.pGFTParam->Options;
	Options |= FOG_OPT_BLUEGRAINS | FOG_OPT_PARENTPARAM;

	WORD * pPoints = CAPoints;
	if(pPoints == NULL)
	{
		CAPoints = (WORD *)calloc(sizeof(WORD)*2,1024);
		if(CAPoints)pPoints = CAPoints;
	}
	memset(pPoints,0,2048);
	WORD * ppoints = pPoints; 
	int l,m,i,j,ImageDivision,sommap,beta,Cursor0,Cursor,Margin,SommaTot = 0;
	
	int divisionx,divisiony;
	//                        External Parameters
	int Threshold,Delta,IsDifferential,ParentParameters = Options & FOG_OPT_PARENTPARAM;
	//						Function Body
	BYTE * pointer,* pAlfa,alfa;
	BYTE maxb = 0,minb = 255;
	int NumGrains = 0;
	bool DoTest;
	if(ParentParameters && GFC.pGetComputingParameters)
	{	GFC.pGetComputingParameters(GFC.pContext,Threshold,ImageDivision,Delta);
		if(ImageDivision < 1)ImageDivision = 1;	}
	else{	Threshold = GFC.pGfPa->Threshold;
		ImageDivision = GFC.pGfPa->CellSize;
		Delta = GFC.pGfPa->Delta;	}
	Margin = GFC.pGfPa->MaxImagesOffset;
	IsDifferential = Options & 1;
	if(ParentParameters && GFC.pIsDifferential)IsDifferential = GFC.pIsDifferential(GFC.pContext);
	int Radius = 6;
	divisionx = (2*HalfSizeX + 1 + Radius)/ImageDivision;
	divisiony = (2*HalfSizeY + 1 + Radius)/ImageDivision;
	SGrain Fake;
//	WORD GoodI,GoodJ,GoodK;
	Cursor0 =  PosX - HalfSizeX - Radius + (PosY - HalfSizeY - Radius)*mXWidth;
	for(l=0;l<divisionx;l++)
	{	for(m=0;m<divisiony;m++)
		{	beta = 255;
			sommap = 0;
			DoTest = false;
			for(i=0;i<ImageDivision;i++)	
			{	for(j=0;j<ImageDivision;j++)
				{	Cursor = Cursor0 + i + j*mXWidth + m*ImageDivision*mXWidth + l*ImageDivision;
					if((Cursor < Margin*mXWidth + Margin) || (Cursor > (1024 - Margin)*mXWidth) || (Cursor % mXWidth) < Margin || (Cursor % mXWidth) > (mXWidth - Margin))
						continue;
					pAlfa = pImage + Cursor;
					alfa = *pAlfa;
					if(alfa <= beta)
					{	DoTest = true;
						beta = alfa;	pointer = pAlfa;	} }	}
			if(DoTest && GrainTest(&Fake,m_MicData.Level,pointer,Delta,Threshold,Options))
			{
				*(pPoints + 2*NumGrains) = (pointer - pImage) % mXWidth + 1;
				*(pPoints + 2*NumGrains + 1) = (pointer - pImage)/mXWidth + 1;
				NumGrains++;
			}
			if(NumGrains==1023)return pPoints;	}	}
	return pPoints;
}


BYTE ** CGrainFinder::ComputeSingleFrame(BYTE * pBytes,int XWidth,int YWidth,int Delta,int Margin)
{
	int l,m,i,j,ImageDivision = 4,leftmargin,rightmargin,sommap,beta,Cursor,SommaTot = 0;
	int divisionx,divisiony;
	int Statistics = GFC.pGFTParam->Options & 16384;
	BYTE * pointer,* pAlfa,alfa;
	BYTE maxb = 0,minb = 255;
	int NumMin = 512;
	if(CSFPointers == NULL)
	{
		CSFPointers = (BYTE **)calloc(sizeof(BYTE *),1024);
	}
	if(CSFPointers == NULL)return 0;
	for(i = 0; i < 1024; i++)*(CSFPointers + i) = NULL;
	int NumGrains = 0;
	SGrain OneGrain;
	int ImageSize = XWidth*YWidth;
	divisionx = (XWidth-2*Margin)/ImageDivision;
	divisiony = (YWidth-2*Margin)/ImageDivision;
	leftmargin = Margin + (int)(((float)((XWidth-2*Margin)%ImageDivision))/2 + 0.51);
	rightmargin = Margin + (int)(((float)((XWidth-2*Margin)%ImageDivision))/2);
	for(l=0;l<divisionx;l++)
	{	if(NumGrains == 1023)break;
		for(m=0;m<divisiony;m++)
		{	Cursor = l*ImageDivision + m*ImageDivision*XWidth + leftmargin*(1 + XWidth);
			beta = 255;	sommap = 0;
			pointer = pBytes + Cursor;
			for(i=0;i<ImageDivision;i++)
			{	for(j=0;j<ImageDivision;j++)
				{	pAlfa = (pBytes + Cursor + i + j*XWidth);
					alfa = *pAlfa;
					if(Statistics)
					{	sommap += alfa;
						SommaTot += alfa;
						if(alfa > maxb)maxb = alfa; if(alfa < minb)minb = alfa;	}
					if(alfa <= beta)(beta = alfa,pointer = pAlfa);}	}
			if(GrainTest(&OneGrain,NULL,pointer,Delta,NULL,FOG_OPT_SINGLEFRAME))*(CSFPointers + NumGrains++) = pointer;
			if(NumGrains == 1023)break;	}	}
/*	if(Statistics && GFC.pSetInteger)
	{	GFC.pSetInteger(GFC.pContext,GFC.pIdc->Minimo,minb);
		GFC.pSetInteger(GFC.pContext,GFC.pIdc->Massimo,maxb);
		int NumBytes = divisionx*divisiony*ImageDivision*ImageDivision;
		int result = NumBytes;
		GFC.pSetInteger(GFC.pContext,GFC.pIdc->Medio,SommaTot/result);	}*/
	return CSFPointers;
}

void CGrainFinder::SaveGrains(CString Path,int version /*=0*/)
{
	if(m_EmSpaceUp.NumGrains == 0)return;
	if(version == 3 || version == 4 || version == 5 || version == 6 || version == 7)version = 0;
	FILE * txtSavingFile,* grsSavingFile;
	CString txtfile(Path),grsfile;
	CString GrsFile(Path);
	CString Extension = GrsFile.Right(4);
	if(Extension.CompareNoCase(".grs"))GrsFile += ".grs";
	char identifier[8] = "Grains ";
	if(version == -1)
	{
		Extension = txtfile.Right(4);
		if(Extension.CompareNoCase(".txt"))txtfile += ".txt";
	}
//	txtfile = txtfile + "_Grains.txt";
	int i,j,count;
	if(version == -1)
	{
		SMip * pMip = GFC.pT->m_pTrackUp;
		SIntGrain * pGrains;
		txtSavingFile = fopen(txtfile,"w");
		if(txtSavingFile == NULL){if(GFC.pMessage)GFC.pMessage("Error Opening File!","Grain Finder - Save File 1",MB_OK);}
		if(txtSavingFile != NULL)
		{	for(i = 0; i < m_EmSpaceUp.NumGrains; i++)
			{	SIntGrain & Grain = *(m_EmSpaceUp.pGrains + i);
				fprintf(txtSavingFile,"%g\t%g\t%g\n",Grain.x,Grain.y,Grain.z);	}
			count = 0;//GFC.pT->CountTracks(pMip);
			if(count > 0)fprintf(txtSavingFile,"%d\t%d\t%d\n",0,0,0);
			for(i = 0; i < count; i++)
			{
				pGrains = pMip->pGrains;
				fprintf(txtSavingFile,"%g\t%g\t%g\n",pMip->mx,pMip->nx,pMip->sigmax);
				fprintf(txtSavingFile,"%g\t%g\t%g\n",pMip->mz,pMip->nz,pMip->sigmaz);
				fprintf(txtSavingFile,"%g\t%d\t%g\n",pMip->md,pMip->NGrains,pMip->GiC);
				for(j = 0; j < pMip->NGrains; j++)
				{
					fprintf(txtSavingFile,"%g\t%g\t%g\n",(pGrains + j)->xx,(pGrains + j)->yy,(pGrains + j)->zz);
				}
				pMip = pMip->pNext;
			}
			fclose(txtSavingFile);	}
		return;	}
	switch(version)
	{	case 1:
		{	grsfile = Path + ".grs2";
			grsSavingFile = fopen(grsfile,"wb");
			int Zeri[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
			if(grsSavingFile != NULL)
			{	int versionNumber = 2;
				fwrite(identifier,8,1,grsSavingFile);
				fwrite(&versionNumber,sizeof(int),1,grsSavingFile);
				fwrite(&m_EmSpaceUp.Distortion,sizeof(SDistortion),1,grsSavingFile);
				fwrite(&m_EmSpaceUp.NumGrains,sizeof(int),1,grsSavingFile);
				fwrite(Zeri,sizeof(int),16,grsSavingFile);
				fwrite(m_EmSpaceUp.pGrains,sizeof(SIntGrain),m_EmSpaceUp.NumGrains,grsSavingFile);
				fclose(grsSavingFile);	}
				else if(GFC.pMessage)GFC.pMessage("Error Opening File!","Grain Finder - Save File 2",MB_OK);	}
			break;
		case 0:
		{	grsfile = GrsFile;//Path + ".grs";
			grsSavingFile = fopen(grsfile,"wb");
			int Zeri[9]= {0,0,0,0,0,0,0,0,0};
			if(grsSavingFile != NULL)
			{	int versionNumber,i;
				int SaveImages = (GFC.pGFTParam->Options & FOG_OPT_SAVEIMAGES)/FOG_OPT_SAVEIMAGES;
				int NumberOfImages = GFC.pScanner->m_NumberOfImages;
				if(!SaveImages)NumberOfImages = 0;
				versionNumber = m_GrainsVersion;
				if(versionNumber == 6 && !SaveImages)versionNumber = 5;
				fwrite(identifier,8,1,grsSavingFile);
				fwrite(&versionNumber,sizeof(int),1,grsSavingFile);
				fwrite(&m_EmSpaceUp.Distortion,sizeof(SDistortion),1,grsSavingFile);
				fwrite(&m_UsedMin,sizeof(int),1,grsSavingFile);
				byte first = 0,last = 0;
				for(i = 0; i <= 255; i++){if(*(m_depths + i)==NOT_USED_DEPTH)first++;else break;}
				for(i = (last = first); i <= 255; i++){if(*(m_depths + i) != NOT_USED_DEPTH)last++;}
				fwrite(GFC.pMicPar,sizeof(SMicroParameters),1,grsSavingFile);
				fwrite(&m_Sheet,sizeof(SSheet),1,grsSavingFile);
				int count = GFC.pT->CountTracks(GFC.pT->m_pTrackUp);
				fwrite(&count,sizeof(int),1,grsSavingFile);
				fwrite(&m_EmSpaceUp.ZetaRange,sizeof(float),4,grsSavingFile);
				fwrite(&m_EmSpaceUp.AdjustedDensity,sizeof(float),1,grsSavingFile);
				fwrite(&NumberOfImages,sizeof(int),1,grsSavingFile);
				fwrite(Zeri,sizeof(Zeri),1,grsSavingFile);
				fwrite(&first,sizeof(byte),1,grsSavingFile);
				fwrite(&last,sizeof(byte),1,grsSavingFile);
				fwrite(m_depths + first,sizeof(float),last - first,grsSavingFile);
				fwrite(m_pMinGrains,sizeof(SGrain),m_UsedMin,grsSavingFile);
				fwrite(&GFC.pT->m_Distortion,sizeof(SDistortion),1,grsSavingFile);
				if(count > 0)
				{	SMip * pNext = GFC.pT->m_pTrackUp;
					for(i = 0; i < count; i++)
					{	pNext->Save(grsSavingFile,7);
						pNext = pNext->pNext;	}	}
				if(SaveImages)
				{
					for(i = 0; i < NumberOfImages; i++)
					{
						fwrite(m_pImageData + i*1024*1280,1024,1280,grsSavingFile);
					}
				}
				fclose(grsSavingFile);	}
				else if(GFC.pMessage)GFC.pMessage("Error Opening File!","Grain Finder - Save File 3",MB_OK);	}
			break;	}
}
void CGrainFinder::SaveTables(CString PostFix)
{
	if(PostFix.IsEmpty())PostFix = "scn";
	CString FullPath = m_GrainsFilePath;
	FromFullPathDirectory(FullPath,true);
	SaveTables(FullPath,PostFix);
}


void CGrainFinder::SaveTables(CString Path,CString PostFix,int Side)
{
	static CString oldPath;
	static int index = 0;
	SEmulsionSpace * pSpace;
	if(Side == 0)pSpace = &m_EmSpaceUp;
	else pSpace = &m_EmSpaceDw;
	int i,j,count,NumGrains = pSpace->NumGrains;
	UINT bSaveGrainsTable = GFC.pGFTParam->Options & FOG_OPT_SAVEGRAINSTABLE;
	UINT bSaveTracksTable = GFC.pGFTParam->Options & FOG_OPT_SAVETRACKTABLE;
	if(!oldPath.CompareNoCase(Path)){oldPath = Path; index = 0;}
	index++;
	if(pSpace->NumGrains == 0)return;
	CString TrackSaveFile,GrainSaveFile,TracksGrainFile,FileInfoFile;
	TrackSaveFile.Format("%sTracksTable_%s.txt",Path,PostFix);
	GrainSaveFile.Format("%sGrainsTable_%s.txt",Path,PostFix);
	TracksGrainFile.Format("%sTracksGrainTable_%s.txt",Path,PostFix);
	FileInfoFile.Format("%sFileInfoTable_%s.txt",Path,PostFix);
	FILE * pTrackSavFile = NULL,* pGrainSavFile = NULL,* pTrackGrainSavFile = NULL,* pFileInfoFile = NULL;
	CString txtfile(Path),grsfile;
	txtfile = txtfile + "_Grains.txt";
	SMip * p;
	if(Side == 0)p = GFC.pT->m_pTrackUp;
	else p = GFC.pT->m_pTrackDw;
	SIntGrain * pG;
	if(bSaveTracksTable || true)
	{
		pTrackSavFile = fopen(TrackSaveFile,"a");
		pTrackGrainSavFile = fopen(TracksGrainFile,"a");
	}
	pGrainSavFile = fopen(GrainSaveFile,"a");
	pFileInfoFile = fopen(FileInfoFile,"a");
	count = GFC.pT->CountTracks(p);
	if(pTrackSavFile == NULL || pGrainSavFile == NULL || pTrackGrainSavFile == NULL || pFileInfoFile == NULL)
	{if(GFC.pMessage)GFC.pMessage("Error Opening File!","Fog",MB_OK);}
	if(pGrainSavFile != NULL && bSaveGrainsTable)
	{	for(i = 0; i < NumGrains; i++)
		{
			SIntGrain & Grain = *(pSpace->pGrains + i);
			fprintf(pGrainSavFile,"%d\t%g\t%g\t%g\t%g\t%g\t%g\t%g\n",index,Grain.x,Grain.y,Grain.z,Grain.xx,Grain.yy,Grain.zz,Grain.zzz);
		}	
	}
	if(pTrackSavFile != NULL && bSaveTracksTable)
	{
		for(i = 0; i < count; i++)
		{
			fprintf(pTrackSavFile,"%d\t%d\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t",index,i + 1,p->mx,p->nx,p->sigmax,p->my,p->ny,p->sigmay,p->mz,p->nz,p->sigmaz);
			fprintf(pTrackSavFile,"%g\t%g\t%g\t%g\t%g\t%g\t%g\t%d\n",p->GiC,p->md,p->MaxDist,p->MeanGap,p->MaxGap,p->Length,p->Alfa,p->NGrains);
			if(pTrackGrainSavFile != NULL)
			{
				pG = p->pGrains;
				for(j = 0; j < p->NGrains; j++)
				{
					fprintf(pTrackGrainSavFile,"%d\t%d\t%g\t%g\t%g\t%g\t%g\t%g\t%g\n",index,i + 1,pG->x,pG->y,pG->z,pG->xx,pG->yy,pG->zz,pG->zzz);
					pG++;
				}
				p = p->pNext;
			}
		}
	}
	if(pFileInfoFile != NULL)
	{
		SEmulsionSpace & ER = *pSpace;
		SDistortion * pD;
		float Spessore = ER.ZetaRange.UpperZ - ER.ZetaRange.BottomZ;
		fprintf(pFileInfoFile,"%d\t%d\t%d\t%g\t%g\t%g\t",index,NumGrains,count,ER.AdjustedDensity,ER.Density,Spessore);
		fprintf(pFileInfoFile,"%g\t%g\t%g\t%g\t%g\t%g\t",GFC.pMicPar->XStageCoordinate,GFC.pMicPar->YStageCoordinate,ER.ZetaRange.BottomZ,ER.ZetaRange.DeadZoneDw,ER.ZetaRange.DeadZoneUp,ER.ZetaRange.UpperZ);
		pD = &ER.Distortion;
		fprintf(pFileInfoFile,"%g\t%g\t%g\t%g\t%g\t",pD->A,pD->B,pD->xzero,pD->yzero,pD->R);
		pD = &GFC.pT->m_Distortion;
		fprintf(pFileInfoFile,"%g\t%g\t%g\t%g\t%g\t",pD->A,pD->B,pD->xzero,pD->yzero,pD->R);
		fprintf(pFileInfoFile,"%d\t%d\t",m_Sheet.Brick,m_Sheet.Sheet);
		fprintf(pFileInfoFile,"%g\t%g\t%g\t%g\t",m_Sheet.Mark1X,m_Sheet.Mark1Y,m_Sheet.Mark2X,m_Sheet.Mark2Y);
		fprintf(pFileInfoFile,"%g\t%g\t%g\t%g\t",m_Sheet.Mark3X,m_Sheet.Mark3Y,m_Sheet.Mark4X,m_Sheet.Mark4Y);
		CString FileName = m_GrainsFilePath;
		FromFullPathFileName(FileName);

		fprintf(pFileInfoFile,"\"%s\"\n",FileName);
	}
	if(pTrackSavFile != NULL)fclose(pTrackSavFile);
	if(pGrainSavFile != NULL)fclose(pGrainSavFile);
	if(pTrackGrainSavFile != NULL)fclose(pTrackGrainSavFile);
	if(pFileInfoFile != NULL)fclose(pFileInfoFile);
	return;
}

int CGrainFinder::LoadGrains(const char *Path,int Delta /*=0*/,int Threshold /*=0*/)
{
	if(Delta == 0)Delta = GFC.pGfPa->Delta;
	if(Threshold == 0)Threshold = GFC.pGfPa->Threshold;
	CString temp;
	FILE * grsSavedFile;
	m_GrainsFilePath = Path;
	int versionNumber;
	int i;
	SMip * pMip,* pNext;
	CString identifier("       ");
	grsSavedFile = fopen(Path,"rb");
	if(grsSavedFile == NULL)
	{	if(GFC.pMessage)GFC.pMessage((temp.Format("Error Opening file \n%s",Path),temp),"Grain Finder - LoadGrains 1",MB_OK);
		return 0;	}
	// Individua il puntatore dell' array di char di identifier.
	// L' efficacia potrebbe dipendere dalla versione del compilatore.
	fread((void *)*(int *)(&identifier),8,1,grsSavedFile);
	if(identifier != "Grains ")
	{	if(GFC.pMessage)GFC.pMessage("Not Grains file!","Grain Finder - LoadGrains 2",MB_OK);
		fclose(grsSavedFile);
		return 0;	}
	fread(&versionNumber,sizeof(int),1,grsSavedFile);
	if(versionNumber == 3 || versionNumber == 5 || versionNumber == 6 || versionNumber == 7)//Standard grain format
	{	m_GrainsVersion = 3;
		int NumGrains = 0,NumMin,index = 0,count = 0,&NumberOfImages = GFC.pScanner->m_NumberOfImages;
		float Fiducials[8];
		int Zeri[9];
		GFC.pT->DeleteMips(GFC.pT->m_pTrackUp);
		GFC.pT->DeleteMips(GFC.pT->m_pTrackDw);
		if(GFC.pUpdateShow)GFC.pUpdateShow(GFC.pContext,FOG_UPDATE_TRACKS);
		SEmulsionSpace &S = m_EmSpaceUp;
		SIntGrain * pGrains = S.pGrains;
		fread(&(S.Distortion),sizeof(SDistortion),1,grsSavedFile);
		fread(&NumMin,sizeof(int),1,grsSavedFile);
		if(pGrains != NULL){free(pGrains);}
		byte first,last;
		for(i = 0; i < 256; i++)*(m_depths + i) = NOT_USED_DEPTH;
		fread(GFC.pMicPar,sizeof(SMicroParameters),1,grsSavedFile);
		fread(&m_Sheet,sizeof(SSheet),1,grsSavedFile);
		fread(&count,sizeof(int),1,grsSavedFile);
		fread(Fiducials,sizeof(float),5,grsSavedFile);
		fread(&NumberOfImages,sizeof(int),1,grsSavedFile);
		fread(Zeri,sizeof(Zeri),1,grsSavedFile);
		fread(&first,sizeof(byte),1,grsSavedFile);
		fread(&last,sizeof(byte),1,grsSavedFile);
		fread(m_depths + first,sizeof(float),last - first,grsSavedFile);
		m_MicData.HasImages = NumberOfImages == last;
		ASSERT(first == 0);
		m_MicData.LevelsUp = last;
		m_MicData.LevelsDw = 0;
		SGrain * pMinGrains = (SGrain *)realloc(m_pMinGrains,sizeof(SGrain)*NumMin);
		if(pMinGrains != NULL){m_pMinGrains = pMinGrains;	m_NumMin = NumMin;}
		else
		{	if(GFC.pMessage)GFC.pMessage("No Memory Available","Grain Finder - LoadGrains 5",MB_OK);
			return 0;	}
		fread(m_pMinGrains,sizeof(SGrain),NumMin,grsSavedFile);
		m_UsedMin = NumMin;
		fread(&GFC.pT->m_Distortion,sizeof(SDistortion),1,grsSavedFile);
		if(count > 0)
		{	pNext = GFC.pT->m_pTrackUp;
			for(i = 0; i < count; i++)
			{	pNext->Load(grsSavedFile,versionNumber);				;
				if(i < count - 1 && pNext->AddNext() != NULL)pNext = pNext->pNext;	}	}
		int MaxNumberOfImages = GFC.pScanner->MaxNumberOfImages;
		if(NumberOfImages > GFC.pScanner->MaxNumberOfImages)
		{//	MessageBox(((CWnd *)GFC.pContext)->m_hWnd,"Cannot load all ImageData","GrainFinder",MB_OK);
			NumberOfImages = MaxNumberOfImages;	}
		if(NumberOfImages > 0 && m_pImageData)
		{
			for(i = 0; i < NumberOfImages; i++)
			{
				fread(m_pImageData + 1024*1280*i,1280,1024,grsSavedFile);
			}
			GFC.pScanner->m_NumberOfImages = NumberOfImages;
			GFC.pScanner->m_bGlobalBytesLoaded = true;
		}
		fclose(grsSavedFile);
		if(GFC.pSetInteger)GFC.pSetInteger(GFC.pContext,GFC.pIdc->Mips,count);
		for(i = 0; i < NumMin; i++)
		{	SGrain &G = *(pMinGrains + i);
			if(G.Max + 128 - G.Min >= (unsigned int)Delta &&
				(G.DeltaNextMax + G.Max + 128 - G.Min - G.DeltaNextMin >= (unsigned int)Threshold || 
				G.DeltaPrevMax + G.Max + 128 - G.Min - G.DeltaPrevMin >= (unsigned int)Threshold))NumGrains++;}
		pGrains = (SIntGrain *)malloc(NumGrains * sizeof(SIntGrain));
		if(pGrains == NULL){if(GFC.pMessage)GFC.pMessage("No Memory Available!","Grain Finder - LoadGrains 6",MB_OK);}
		S.pGrains = pGrains;
		S.Allocated = NumGrains;
		bool InvertXY = GFC.pGfPa->InvertXY;
		for(i = 0; i < NumMin; i++)
		{	SGrain &G = *(pMinGrains + i);
			if(G.Max + 128 - G.Min >= (unsigned int)Delta &&
				(G.DeltaNextMax + G.Max + 128 - G.Min - G.DeltaNextMin >= (unsigned int)Threshold || 
				G.DeltaPrevMax + G.Max + 128 - G.Min - G.DeltaPrevMin >= (unsigned int)Threshold))
				G.ToIntGrain(pGrains + index++,m_depths,GFC.pMicPar,InvertXY,&S.Distortion);}
		S.NumGrains = NumGrains;
		*GFC.pLastNumGrains = NumGrains;}
	m_GrainsVersion = versionNumber;
	if(m_GrainsVersion == 5 || m_GrainsVersion == 6)m_GrainsVersion = 7;
	GFC.pSetInteger(GFC.pContext,GFC.pIdc->TotalGrains, m_EmSpaceUp.NumGrains);
	m_FileLoaded = true;
//	if(GFC.pGFTParam->Options & FOG_OPT_CORRECTDIST)FindOperaDistortion(m_EmulsionRegion);
	CheckDensity(m_EmSpaceUp);
	pMip = GFC.pT->m_pTrackUp;
	while(pMip->pNext != NULL)
	{
		GFC.pT->GetNominalLength(&m_EmSpaceUp,pMip);
		pMip = pMip->pNext;
	}
	if(GFC.pUpdateShow)GFC.pUpdateShow(GFC.pContext,255);
	return m_EmSpaceUp.NumGrains;
}

SDistortion CGrainFinder::FindOperaDistortion(SEmulsionSpace &Space)
{
	STrackingInfo Par = GFC.pT->Parameters;
	SIntGrain *pGrains = Space.pGrains;
	int NumGrains = Space.NumGrains;
	int i;
	CString text;
	double x0,y0,A = -0.00004,B = 0.0,r;
	float Bestx0 = 0,Besty0 = 0,BestA = 0,BestB = 0;
	double x0min = -100,x0max = 100,dx0 = 20;
	double y0min = -100,y0max = 100, dy0 = 20,div = 5;
	float x,y,z,maxz = -NOT_USED_DEPTH,minz = NOT_USED_DEPTH;
	int MinTriCounts = 20000;
	int mean,index = 0,MinMiddleBin = 1000,MMBIndex,TriCounts;
	int rangemin,rangemax;
	float spessore;
	for(i = 0; i < NumGrains; i++)
	{
		SIntGrain &gr = *(pGrains + i);
		z = gr.zz;
		if(maxz < z)maxz = z;
		if(minz > z)minz = z;
		if(maxz >= NOT_USED_DEPTH)
		{
			text.Format("Abnormal z value found in grain %d file %s",i+1,m_GrainsFilePath);
			GFC.pWriteLog(LogFilePath,text);
			(*(m_pMinGrains + i)).ToIntGrain(pGrains + i,m_depths,GFC.pMicPar,false);
		}
	//	if(gr.xx > 210)ASSERT(FALSE);
	}
	spessore = maxz - minz;
	int MaxNumBin = (8*((int)(maxz - minz)));
	if(NumGrains == 0)return SDistortion();
	if(GFC.pSetDlgItemText)GFC.pSetDlgItemText(GFC.pContext, GFC.pIdc->StaticLocalGrains,"Searching");
	int *pBins = (int *)malloc(sizeof(int)*MaxNumBin);
	SDistortion Best0;
	if(pBins)
	{
	for(i = 1; i < 4; i++)
	{	for(x0 = x0min; x0 < x0max; x0 += dx0)
		{	for(y0 = y0min; y0 < y0max; y0 += dy0)
			{	int i;
				memset(pBins,0,sizeof(int)*MaxNumBin);
				maxz = -NOT_USED_DEPTH;minz = NOT_USED_DEPTH;
				for(i = 0; i < NumGrains; i++)
				{	SIntGrain &gr = *(pGrains + i);
					x = (gr.xx - (float)x0);
					y = (gr.yy - (float)y0);
					r = x*x + y*y;
					z = (float)(gr.zz - A*r);
					if(maxz < z)maxz = z;
					if(minz > z)minz = z;
					gr.z = z;	}
				minz = minz - .01f;
				maxz = maxz + .01f;
				int NumBins = (int)(1 + 5*(maxz - minz));
				if(NumBins > MaxNumBin)continue;
				int NotUnoBins = 0;
				for(i = 0; i < NumGrains; i++)
				{	(*(pBins + (int)(5*((pGrains + i)->z - minz))))++;	}
				for(i = 0; i < NumBins; i++){if(*(pBins + i) > 1)NotUnoBins++;}
				index = 0;
				MinMiddleBin = 5*MaxNumBin;
				float minbin = 0, maxbin = 0;
				if(NotUnoBins < 100)
					continue;
				mean = NumGrains/NotUnoBins;
				if(mean < 6)mean = 6;
				for(i = 0; i < NumBins; i++)
				{	if(*(pBins + i) < mean/2)minbin += 0.2f;
					else break;	}
				for(i = NumBins - 1; i >= 0; i--)
				{	if(*(pBins + i) < mean/2)maxbin += 0.2f;
					else break;	}
				if((maxz - maxbin) - (minz + minbin) > spessore)continue;
				float midZ = ((maxz - maxbin) + (minz + minbin))/2.f;
				rangemin = 5*(int)(midZ - minz - 5);
				rangemax = 5*(int)(midZ - minz + 5);
				if(rangemin < 1)rangemin = 1;
				if(rangemax > NumBins)rangemax = NumBins;
				for(i = rangemin; i < rangemax + 1; i++)
				{	if(MinMiddleBin > *(pBins + i))
					{	MinMiddleBin = *(pBins + i);
						MMBIndex = i;	}	}
				for(i = -1; i < 2; i++)
				{
					TriCounts = *(pBins + MMBIndex - 1 + i) + *(pBins + MMBIndex + i) + *(pBins + MMBIndex + 1 + i);
					TriCounts = *(pBins + MMBIndex - 2 + i) + TriCounts + *(pBins + MMBIndex + 2 + i);
					TriCounts = *(pBins + MMBIndex - 3 + i) + TriCounts + *(pBins + MMBIndex + 3 + i);
					TriCounts = *(pBins + MMBIndex - 4 + i) + TriCounts + *(pBins + MMBIndex + 4 + i);
					if(TriCounts < MinTriCounts)
					{
						MinTriCounts = TriCounts;
						Bestx0 = (float)x0;
						Besty0 = (float)y0;
					}
				}
			}
		}
		x0min = Bestx0 - dx0; x0max = Bestx0 + dx0; dx0 /= div;
		y0min = Besty0 - dy0; y0max = Besty0 + dy0; dy0 /= div;
		div = 4.;
	}
	double AMin = -0.00007,AMax = 0.,dA = 0.00001;
//	double BMin = -0.0000000015,BMax = 0.0000000015,dB = 0.0000000003;
	double BMin = 0.00000000012,BMax = 0.000000000151,dB = 0.00000000003;
	div = 5;
	MinTriCounts = 20000;
	for(i = 1; i < 4; i++)
	{
		for(A = AMin; A < AMax; A += dA)
		{
			for(B = BMin; B < BMax; B += dB)
			{	int i;
				memset(pBins,0,sizeof(int)*MaxNumBin);
				maxz = -NOT_USED_DEPTH;minz = NOT_USED_DEPTH;
				for(i = 0; i < NumGrains; i++)
				{	SIntGrain &gr = *(pGrains + i);
					x = (gr.xx - Bestx0);
					y = (gr.yy - Besty0);
					r = x*x + y*y;
					z = (float)(gr.zz - A*r - B*r*r);
					if(maxz < z)maxz = z;
					if(minz > z)minz = z;
					gr.z = z;	}
				minz = minz - .01f;
				maxz = maxz + .01f;
				int NumBins = (int)(1 + 5*(maxz - minz));
				if(NumBins > MaxNumBin)continue;
				int NotUnoBins = 0;
				for(i = 0; i < NumBins; i++){*(pBins + i) = 0;}
				for(i = 0; i < NumGrains; i++)
				{	(*(pBins + (int)(5*((pGrains + i)->z - minz))))++;	}
				for(i = 0; i < NumBins; i++){if(*(pBins + i) > 1)NotUnoBins++;}
				index = 0;
				MinMiddleBin = 5*MaxNumBin;
				float minbin = 0, maxbin = 0;
				if(NotUnoBins < 100)
					continue;
				mean = NumGrains/NotUnoBins;
				if(mean < 6)mean = 6;
				for(i = 0; i < NumBins; i++)
				{	if(*(pBins + i) < mean/2)minbin += 0.2f;
					else break;	}
				for(i = NumBins - 1; i >= 0; i--)
				{	if(*(pBins + i) < mean/2)maxbin += 0.2f;
					else break;	}
				if((maxz - maxbin) - (minz + minbin) > spessore)continue;
				float midZ = ((maxz - maxbin) + (minz + minbin))/2.f;
				rangemin = 5*(int)(midZ - minz - 5);
				rangemax = 5*(int)(midZ - minz + 5);
				if(rangemin < 1)rangemin = 1;
				if(rangemax > NumBins)rangemax = NumBins;
				for(i = rangemin; i < rangemax + 1; i++)
				{	if(MinMiddleBin > *(pBins + i))
					{	MinMiddleBin = *(pBins + i);
						MMBIndex = i;	}	}
				for(i = -1; i < 2; i++)
				{
					TriCounts = *(pBins + MMBIndex - 1 + i) + *(pBins + MMBIndex + i) + *(pBins + MMBIndex + 1 + i);
					TriCounts = *(pBins + MMBIndex - 2 + i) + TriCounts + *(pBins + MMBIndex + 2 + i);
					TriCounts = *(pBins + MMBIndex - 3 + i) + TriCounts + *(pBins + MMBIndex + 3 + i);
					TriCounts = *(pBins + MMBIndex - 4 + i) + TriCounts + *(pBins + MMBIndex + 4 + i);
					if(TriCounts < MinTriCounts)
					{
						MinTriCounts = TriCounts;
						BestA = (float)A;
						BestB = (float)B;
					}
				}
			}
		}
		AMin = BestA - dA; AMax = BestA + dA; dA /= div;
		BMin = BestB - dB; BMax = BestB + dB; dB /= div;
		div = 4.;

	}
	SDistortion Best(Bestx0,Besty0,BestA,BestB,-0.0000001);
	ApplyCorrection(m_EmSpaceUp,Best);
	Best0 = Best;
	}
	free(pBins);
	return Best0;
}

void CGrainFinder::CheckDensity(SEmulsionSpace & Space)
{
	int i;
	float minx=1000,maxx=-1000,miny=1000,maxy=-1000;
	float sizex,sizey,sizez,minz=NOT_USED_DEPTH,maxz=-NOT_USED_DEPTH;
	int MinZPos = 0,NumGrains = Space.NumGrains;
	if(Space.NumGrains == 0)return;
	const float NominalWidth = 40.f;
//	float Product,Depth;
//	int Width;
	for(i=0;i<NumGrains;i++)
	{	SIntGrain &grain = *(Space.pGrains + i);
		if(minx > grain.x)minx = grain.x;
		if(maxx < grain.x)maxx = grain.x;
		if(miny > grain.y)miny = grain.y;
		if(maxy < grain.y)maxy = grain.y;
		if(minz > grain.z)minz = grain.z;
		if(maxz < grain.z)maxz = grain.z;	}
	minx = minx - 2.f;maxx = maxx + 2.f;
	miny = miny - 2.f; maxy = maxy + 2.f;
	minz = minz - 2.f; maxz = maxz + 2.f;
	Space.Diagonal.x = sizex = maxx-minx;
	Space.Diagonal.y =  miny-maxy;
	sizey = maxy-miny;
	Space.Diagonal.z = sizez = maxz-minz;
	Space.LowerCorner.x = minx;
	Space.LowerCorner.y = maxy;
	Space.LowerCorner.z = minz;
	Space.UpperCorner.x = maxx;
	Space.UpperCorner.y = miny;
	Space.UpperCorner.z = maxz;
	Space.Volume = sizex*sizey*sizez;
//	Space.Density = NumGrains*1000.f/Space.Volume;
	CString Text;
	int NumBins = (int)(1 + 5*(maxz - minz));
	int mean,index = 0,MinMiddleBin = 2*NumBins,MMBIndex,NotTwoBins;
	float minbin = 0, maxbin = 0,DeadZoneMaxZ,DeadZoneMinZ,midZ,surfaceArea;
	int rangemin,rangemax,UnoBins = 0;
	SIntGrain * pGrains = Space.pGrains;
	int *pBins = (int *)calloc(NumBins,sizeof(int));
//	if(NumBins > 600){
//		Text.Format("Number of Bin Exeeded in %s\n",m_GrainsFilePath);
//		GFC.pWriteLog(LogFilePath,Text);
//		return;}
	NotTwoBins = 0;
	for(i = 0; i < NumGrains; i++)(*(pBins + (int)(5*((pGrains + i)->z - minz))))++;
	for(i = 0; i < NumBins; i++){if(*(pBins + i) > 1)NotTwoBins++;} 
	for(i = 0; i < NumBins; i++){if(*(pBins + i) == 1)UnoBins++;} 
	if(NotTwoBins > 0) mean = (int)NumGrains/NotTwoBins;
	else mean =0;
	if(mean < 6)mean = 6;
	for(i = 0; i < NumBins; i++)if(*(pBins + i) < mean/2)minbin += 0.2f;else break;
	for(i = NumBins - 1; i >= 0; i--)if(*(pBins + i) < mean/2)maxbin += 0.2f;else break;
	midZ = ((maxz - maxbin) + (minz + minbin))/2.f;
	rangemin = 5*(int)(midZ - minz - 5);
	rangemax = 5*(int)(midZ - minz + 5);
	rangemin = rangemin < 1 ? 1 : rangemin;
	rangemax = rangemax > NumBins ? NumBins : rangemax;
	for(i = rangemin; i < rangemax + 1; i++)
	{	if(MinMiddleBin > *(pBins + i))
		{	MinMiddleBin = *(pBins + i);
			MMBIndex = i;	}	}
	DeadZoneMaxZ = minz + 0.2f * MMBIndex;
	DeadZoneMinZ = DeadZoneMaxZ;
	if(MMBIndex > 10)
	{	
		for(i = MMBIndex; i > MMBIndex - 10; i--)
            if(*(pBins + i) < mean/2)DeadZoneMinZ -= 0.2f;
			else break;		}
	else
	{
		Text.Format("Abnormal Density distribution 1 in %s\n",m_GrainsFilePath);
		GFC.pWriteLog(LogFilePath,Text);
	}
	if(MMBIndex < 590)
	{   for(i = MMBIndex; i < MMBIndex + 10; i++)
			if(*(pBins + i) < mean/2)DeadZoneMaxZ += 0.2f;
			else break;	}
	else
	{
			Text.Format("Abnormal Density distribution 2 in %s\n",m_GrainsFilePath);
			GFC.pWriteLog(LogFilePath,Text);
	}
	free(pBins);
	Space.ZetaRange.BottomZ = minz + minbin;
	Space.ZetaRange.DeadZoneDw = DeadZoneMinZ;
	Space.ZetaRange.DeadZoneUp = DeadZoneMaxZ;
	Space.ZetaRange.MaxZ = maxz - 1.0f;
	Space.ZetaRange.MinZ = minz + 1.0f;
	Space.ZetaRange.UpperZ = maxz - maxbin;
	Space.ZetaRange.MaxX = maxx; Space.ZetaRange.MinX = minx;
	Space.ZetaRange.MaxY = maxy; Space.ZetaRange.MinY = miny;
	surfaceArea = GFC.pMicPar->PixLen*(GFC.pMicPar->HalfCCDLength - GFC.pGfPa->MaxImagesOffset)*2;
	surfaceArea *= GFC.pMicPar->PixLen*(GFC.pMicPar->HalfCCDWidth - GFC.pGfPa->MaxImagesOffset)*2;
	surfaceArea = (maxx - minx)*(maxy - miny);
	Space.Density = Space.NumGrains/(((maxz - maxbin) - (minz + minbin) - (DeadZoneMaxZ - DeadZoneMinZ))*surfaceArea/1000.f);
	Space.AdjustedDensity = ((float)NumGrains)/(surfaceArea * NominalWidth * 0.001f);
}

__forceinline float CGrainFinder::Depth(double b1, double f1, double b2, double f2, double b3, double f3)
{
	float result = (float)( ((b2 - b3)*f1*f1 - (b1 - b3)*f2*f2 + (b1 - b2)*f3*f3)/
		  (2*((b2 - b3)*f1 - (b1 - b3)*f2 + (b1 - b2)*f3)));
	if(result < -10000.f||result > 10000.f)return (float)f3;
	return result;
}

__forceinline BYTE CGrainFinder::IsAMinimum(BYTE * pointer)
{
	int XWidth = mXWidth;
	int XWMeno = XWidth - 1, XWPiu = XWidth + 1;
	register BYTE worker;
	BYTE beta = *pointer,max,max1,max2,min,min1,min2;
	max1 = *(pointer - XWPiu);
	min1 = worker = *(pointer - XWidth);
	if(max1 < worker)(min1 = max1,max1 = worker);	//110
													//1 0
	max2 = *(pointer - 1);							//100
	min2 = worker = *(pointer + XWMeno);
	if(max2 < worker)(min2 = max2,max2 = worker);

	max = max1 > max2 ? max1 : max2;
	min = min1 < min2 ? min1 : min2;
	if(beta > min)return 0;

	max1 = *(pointer + XWPiu);
	min1 = worker = *(pointer + 1);
	if(max1 < worker)(min1 = max1,max1 = worker);

	max2 = *(pointer - XWMeno);
	min2 = worker = *(pointer + XWidth);
	if(max2 < worker)(min2 = max2,max2 = worker);

	worker = max1 > max2 ? max1 : max2;
	max = max > worker ? max : worker;
	worker = min1 < min2 ? min1 : min2;
//	min = min < worker ? min : worker;
	if(beta >= worker)return 0;
// If Arrived here IsLocalMinimum is true
	max1 = *(pointer - XWidth - XWidth - 2);
	worker = *(pointer - - XWidth - XWidth - 1);
	if(max1 > worker)worker = max1;

	max1 = *(pointer - XWidth - XWidth);
	max2 = *(pointer - XWidth - XWidth + 1);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer - XWidth - XWidth + 2);
	max2 = *(pointer - XWidth - 2);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer - XWidth + 2);
	max2 = *(pointer - 2);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer + 2);
	max2 = *(pointer + XWidth - 2);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer + XWidth + 2);
	max2 = *(pointer + XWidth + XWidth - 2);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer + XWidth + XWidth - 1);
	max2 = *(pointer + XWidth + XWidth);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer + XWidth + XWidth + 1);
	max2 = *(pointer + XWidth + XWidth + 2);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;

	max = max > worker ? max : worker;

//	int tmp = max < 245 ? (245 - max)/8 : 0;

	return  max;// + tmp;
}

__forceinline BYTE CGrainFinder::FindMinimum(BYTE * pointer)
{
	register BYTE worker;
	int XWidth = mXWidth;
	int XWMeno = XWidth - 1,XWPiu = XWidth + 1;
	BYTE beta = *pointer,min,min1,min2;
	min1 = *(pointer - XWPiu);
	worker = *(pointer - XWidth);
	if(min1 > worker)min1 = worker;

	min2 = *(pointer - 1);
	worker = *(pointer + XWMeno);
	if(min2 > worker)min2 = worker;

	min = min1 < min2 ? min1 : min2;

	min1 = *(pointer - XWMeno);
	worker = *(pointer + 1);
	if(min1 > worker)min1 = worker;

	min2 = *(pointer + XWidth);
	worker = *(pointer + XWPiu);
	if(min2 > worker)min2 = worker;

	worker = min1 < min2 ? min1 : min2;
	min = min < worker ? min : worker;

	return  min < beta ? min : beta;
}

__forceinline BYTE CGrainFinder::FindMax(BYTE * pointer)
{
	register BYTE worker;
	int XWidth = mXWidth;
	int XWPiu = XWidth + 1, XWMeno = XWidth - 1,DueXWidth = XWidth << 1;
	BYTE beta = *pointer,max1,max2,max;
	max1 = *(pointer - XWPiu);
	worker = *(pointer - XWidth);
	if(max1 < worker)max1 = worker;

	max2 = *(pointer - 1);
	worker = *(pointer + XWMeno);
	if(max2 < worker)max2 = worker;

	max = max1 > max2 ? max1 : max2;

	max1 = *(pointer - XWMeno);
	worker = *(pointer + 1);
	if(max1 < worker)max1 = worker;

	max2 = *(pointer + XWidth);
	worker = *(pointer + XWPiu);
	if(max2 < worker)max2 = worker;

	worker = max1 > max2 ? max1 : max2;
	max = max > worker ? max : worker;

	max = max > beta ? max : beta;	// max is the maximum in the nine central pixel.

	max1 = *(pointer - DueXWidth - 2);
	worker = *(pointer - DueXWidth - 1);
	if(max1 > worker)worker = max1;

	max1 = *(pointer - DueXWidth);
	max2 = *(pointer - DueXWidth + 1);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer - DueXWidth + 2);
	max2 = *(pointer - XWidth - 2);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer - XWidth + 2);
	max2 = *(pointer - 2);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer + 2);
	max2 = *(pointer + XWidth - 2);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer + XWidth + 2);
	max2 = *(pointer + DueXWidth - 2);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer + DueXWidth - 1);
	max2 = *(pointer + DueXWidth);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;
	max1 = *(pointer + DueXWidth + 1);
	max2 = *(pointer + DueXWidth + 2);
	if(max1 > worker)worker = max1;
	if(max2 > worker)worker = max2;// worker is the maximum in the 16 external pixel

	max = (max > worker ? max : worker);
//	BYTE tmp = max < 245 ? (245 - max)/4 : 0;
	return max;
}

__forceinline BYTE * CGrainFinder::FindMinP(BYTE * pointer)
{
	BYTE beta = *pointer;
	BYTE * pMin, * pMin1, * pMin2;
	int XWidth = mXWidth;
	int XWPiu = XWidth + 1,XWMeno = XWidth - 1;

	register BYTE *pworker;

	pMin1 = (pointer - XWPiu);
	pworker = (pointer - XWidth);
	if(*pMin1 > *pworker)pMin1 = pworker;

	pMin2 = (pointer - 1);
	pworker = (pointer + XWMeno);
	if(*pMin2 > *pworker)pMin2 = pworker;

	pMin = *pMin1 < *pMin2 ? pMin1 : pMin2;

	pMin1 = (pointer - XWMeno);
	pworker = (pointer + 1);
	if(*pMin1 > *pworker)pMin1 = pworker;

	pMin2 = (pointer + XWPiu);
	pworker = (pointer + XWidth);
	if(*pMin2 > *pworker)pMin2 = pworker;

	pworker = *pMin1 < *pMin2 ? pMin1 : pMin2;
	pMin = *pMin < *pworker ? pMin : pworker;

	pMin = *pMin < beta ? pMin : pointer;
	return pMin;
}

__forceinline  bool CGrainFinder::GrainTest(SGrain * pMin,int frame,BYTE *pointer, int Delta, int Threshold,UINT Options)
{
	static int counter = 0;
	static int counter2 = 0;
	BYTE max = IsAMinimum(pointer);
	if(max < 128)return false;
	int *pCounter = &counter;
	BYTE beta = *pointer,max1 = 0,max2 = 0,alfa,gamma, * pAlfa, * pGamma,* pAlfa0, * pGamma0;
	bool SingleFrame = (Options & FOG_OPT_SINGLEFRAME) == FOG_OPT_SINGLEFRAME;
	if(SingleFrame && (max - beta >= Delta))return true;
	int x,y,z,k;
	int OttoImagesSize = mImageSize << 3,ImageSize = mImageSize;
	int projection;// = (pointer - m_pImageData)%ImageSize;
	int IsDifferential = 1 & Options;
	int & Level = m_MicData.Level;
//	ASSERT(Level == frame);
	BYTE * pData = m_pImageData + ImageSize*frame;
	if(max - beta >= Delta)
	{
//		int Offset23 = *(m_pOffsets + frame - 1) - *(m_pOffsets + frame - 2);
//		int Offset34 = *(m_pOffsets + frame) - *(m_pOffsets + frame - 1);
//		k = ((pointer + OttoImagesSize - ImageDataP[2])/ImageSize)%5 - 3;
//		projection = (pointer + OttoImagesSize - *(ImageDataP + 2 + k))%ImageSize;
		projection = pointer - pData;
		ASSERT(projection < ImageSize);
//		pAlfa0 = (*(ImageDataP + 1 + k) + projection);
		pAlfa0 = pData - ImageSize + projection;
		pAlfa = FindMinP(pAlfa0);
		alfa = *pAlfa;
		if(IsDifferential && beta > alfa)return false;
//		pGamma0 = (*(ImageDataP + 3 + k) + projection);
		pGamma0 = pData + ImageSize + projection;
		pGamma = FindMinP(pGamma0);
		gamma = *pGamma;
		if(IsDifferential)
		{
			if(beta >= gamma)return false;
			max2 = FindMax(pGamma);
			max1 = FindMax(pAlfa);
			if(max1 - alfa < Threshold && max2 - gamma < Threshold)gamma = 0;
			{	
				if(beta<=alfa && beta < gamma)
				{
					counter++;
					x = (pointer - m_pImageData - *(m_pOffsets + frame - 1))%mXWidth + 1;// x (1,mXWidth)
					y = ((pointer - m_pImageData - *(m_pOffsets + frame - 1))%ImageSize)/mXWidth + 1;//y (1,mYWidth)
					z = (pointer - m_pImageData)/ImageSize + 1;
					SLongGrain LG(x,y,z - 1,beta,128,max,alfa,gamma,128,128,max1,
						max2,pAlfa0-pAlfa,pGamma0-pGamma);
					*pMin = SGrain(LG);
					if(false)
					{
						SLongGrain LG1;
						pMin->ToLongGrain(LG1);
						bool test1 = LG.Max == LG1.Max && LG.Mean == LG1.Mean && LG.Min == LG1.Min && LG.NextMax == LG1.NextMax;
						bool test2 = LG.NextMean == LG.NextMean && LG.NextMin == LG1.NextMin && LG.NextMinPos == LG1.NextMinPos;
						bool test3 = LG.PrevMax == LG1.PrevMax && LG.PrevMean == LG1.PrevMean && LG.PrevMin == LG1.PrevMin;
						bool test4 = LG.x == LG1.x && LG.y == LG1.y && LG.z == LG1.z;
						bool test5 = (LG.NextMin - LG.Min > 63 || LG.PrevMin - LG.Min > 63);
						if(!(test1 && test2 && test3 && test4))counter2++;
						if(test5)counter++;
					}	
					return true;
				}
				else return false;
		}	}
		else
		{
			z = (pointer - m_pImageData)/ImageSize + 1;
			if(z==frame)
			{	x = (pointer-m_pImageData - *(m_pOffsets + frame - 1))%mXWidth + 1;
				y = ((pointer-m_pImageData - *(m_pOffsets + frame - 1))%ImageSize)/mXWidth + 1;
				SLongGrain LG(x,y,z - 1,beta,0,max,alfa,gamma,0,0,max1,
					max2,pAlfa0-pAlfa,pGamma0-pGamma);
				*pMin = SGrain(LG);
				return true;	}	}	}
	return false;
}

float CGrainFinder::Depth(double b1, double f1, double b2, double f2, double b3, double f3, double b4, double f4, double b5, double f5)
{
	float result;
	if(f2==f3)
	{
		result = Depth(b2,f2+0.6,b3,f3,b4,f4);
	}
	else if(f3==f4)
	{
		result = Depth(b2,f2,b3,f3,b4,f4-0.6);
	}
	else if(b2==b3 && b3 == b4 && b1 > b2 && b5 > b2)
	{
		result = Depth(b1,f1,b3,f3,b5,f5);
	}
	else
	{
		result = Depth(b2,f2,b3,f3,b4,f4);
	}
	if(result < -10000.f||result > 10000.f)
	{
		return (float)f3;
	}
	return result;
}

void CGrainFinder::ApplyCorrection(SDistortion Dist,SIntGrain & grain)
{
	double A = Dist.A,B = Dist.B, R = Dist.R,x0 = Dist.xzero,y0 = Dist.yzero;
	float x = grain.xx,y = grain.yy, z = grain.zz;
	double deltax = x - x0, deltay = y - y0,r;
	r = deltax * deltax + deltay * deltay;
	grain.x = x + (float)(R * deltax * r);
	grain.y = y + (float)(R * deltay * r);
	grain.z = z + (float)(- A*r - B*r*r);
}

void CGrainFinder::ApplyCorrection(SEmulsionSpace &Space, SDistortion Dist)
{
	Space.Distortion = Dist;
	int NumGrains = Space.NumGrains;
	SIntGrain * pGrain = Space.pGrains;
	double A = Dist.A,B = Dist.B, R = Dist.R,x0 = Dist.xzero,y0 = Dist.yzero;
	double a = Dist.a, b = Dist.b;
	double deltax,deltay,r;
	float x, y, z;
	Space.Distortion = Dist;
	for(int i = 0; i < NumGrains; i++)
	{
		SIntGrain &grain = *(pGrain + i);
		x = grain.xx; y = grain.yy; z = grain.zz;
		deltax = x - x0; deltay = y - y0;
		r = deltax * deltax + deltay * deltay;
		grain.x = x + (float)(R * deltax * r);
		grain.y = y + (float)(R * deltay * r);
//		grain.z = z + (float)(- A*r - B*r*r);
		grain.z = (float)(- A*r - B*r*r + z + a*x + b*y);
	}
	CheckDensity(Space);
	if(GFC.pUpdateShow)GFC.pUpdateShow(GFC.pContext,255);
}


int CGrainFinder::ComputeFile(LPCSTR pFileName,SGFTParam * pGftP /*=NULL*/)
{
	if(pGftP == NULL)pGftP = GFC.pGFTParam;
	int i,TrackGrains,ShowTracks,bSaveGrains,bSaveTxt,bFindGrains;
	int ShowImage,ShowGrains,Color,HeaderSize = 79,bCorrectDistortion;
	UINT Options;
	int LastNumGrains = 0;
	CString WindowTitle("Fog - "),ErrorMessage;
	CString FileName = pFileName,Extension = FileName.Right(3),Text;
//	memset(m_pMinGrains,0,sizeof(SGrain)*m_NumMin);
	float * depths = m_depths;
	for(i=0;i<256;i++)
		*(depths + i) = NOT_USED_DEPTH;
	Options = pGftP->Options;
	TrackGrains = 512 & Options;
	ShowTracks = 1024 & Options;
	bSaveGrains = 64 & Options;
	ShowImage = 2 & Options;
	ShowGrains = 4 & Options;
	Color = (24 & Options)/8;
	bSaveTxt = 32768 & Options;
	bFindGrains = FOG_OPT_FINDGRAINS & Options;
	bCorrectDistortion = FOG_OPT_CORRECTDIST & Options;
	bool bNotPhsFile = false;
	WindowTitle = WindowTitle + pFileName;
	if(GFC.pSetDlgItemText)GFC.pSetDlgItemText(GFC.pContext,0,WindowTitle);
	bool bCopyFile = false;
	FILE * OutPutFile = NULL;
	CTracker & TT = * GFC.pT;
	bNotPhsFile = true;
	int LoadedGrains = 0;
	if(bNotPhsFile)
	{	if(!Extension.CompareNoCase("phs"))LoadedGrains = LoadGrains(FileName + ".grs",GFC.pGfPa->Delta,GFC.pGfPa->Threshold);
		else if(!Extension.CompareNoCase("grs"))LoadedGrains = LoadGrains(pFileName,GFC.pGfPa->Delta,GFC.pGfPa->Threshold);
//		else if(!Extension.CompareNoCase("dat")){LoadedGrains = LoadDatGrains(pFileName);}//m_LoadedDatGrains = true; }
		else 
		{	Text.Format("File %s not Recognized!",pFileName);
			GFC.pWriteLog(LogFilePath,Text);	return 2;	}
		if(bCorrectDistortion)FindOperaDistortion(m_EmSpaceUp);
	}
	else LoadedGrains = m_EmSpaceUp.NumGrains;
	bool bPurgeFile = true;
	if(bPurgeFile)PurgeFile();
	int count = 0;
	if(LoadedGrains > 0)
	{
		if(TrackGrains)
		{
			STrackingInfo::ETracker Tracker = TT.TP.pTrackInfo->Tracker;
			if(Tracker == STrackingInfo::Tre)count = TT.Track3(m_EmSpaceUp,TT.m_pTrackUp);
		}
	}
	else m_EmSpaceUp.GetSpace();
	if(GFC.pSetInteger){GFC.pSetInteger(GFC.pContext, GFC.pIdc->Mips,count);	}
	if(bSaveGrains | bSaveTxt)
	{	if(bSaveGrains)SaveGrains(FileName + GFC.ConName);
		if(bSaveTxt)SaveGrains(FileName + GFC.ConName,-1);	}
/*	{
		CString TempDir = "C:\\Fulvio\\Data\\";
		CString ShortFileName = FileName;
		int FileOffset = ShortFileName.ReverseFind('\\');
		ShortFileName = ShortFileName.Right(ShortFileName.GetLength() - FileOffset);
		if(bSaveGrains)SaveGrains(TempDir + ShortFileName);
		if(bSaveTxt)SaveGrains(TempDir + ShortFileName);
	}*/

	return 0;
}


UINT FindGrainsThread(LPVOID pParam)
{
	int A = 0,NumTracks = 0,SpaceResult = 0;
	CGrainFinder &GF = *((CGrainFinder *)pParam);
	CTracker &TT = *GF.GFC.pT;
	GF.GFC.pSetInteger(GF.GFC.pContext,GF.GFC.pIdc->TotalMips,0);
	GF.GFC.pSetInteger(GF.GFC.pContext,GF.GFC.pIdc->Mips,0);
	CFindGrainsThreadDlg dlg(&GF.GFC);
	CString OldLogFile = LogFilePath;
	char * pNextFile;
	CString File,Directory,TotalPath,WindowTitle("Fog - "),PostFix;
	int FileDirectory;
	if(dlg.DoModal()==IDOK)
	{	if(GF.m_pImageData == NULL && !dlg.m_Fog2000)SpaceResult = GF.ImageSpace();
		else if(!dlg.m_Fog2000){ *(GF.GFC.ppThread) = NULL; return 0;}
		else SpaceResult = 1;
		if(SpaceResult != 1){ *(GF.GFC.ppThread) = NULL; return 0;}
		*GF.m_pComputingInProgress = true;
		UINT Options = GF.GFC.pGFTParam->Options;
		int SaveTables = Options & FOG_OPT_SAVETABLES;
		FileDirectory = (128 & Options);
		Directory = FileDirectory == 128 ? dlg.m_pFiles : " ";
		bool test = Directory.GetAt(Directory.GetLength() - 1) == '\\';
		if(!test)Directory = Directory + "\\";
		if(test)pNextFile = (dlg.m_pFiles + Directory.GetLength() + 1);
		else pNextFile = (dlg.m_pFiles + Directory.GetLength());
		File = pNextFile;
		if(File.IsEmpty())FileDirectory = 0;
		if(!(FileDirectory == 128))
		{
			char * pChar = dlg.m_pFiles;//*((char **)(&dlg.m_FilePath));
			int count = 0;
			int LastSlashPos = 0;
			for(int i = 0; i < 4000; i++)
			{
				if(*(pChar + i) == 92)LastSlashPos = i + 1;
				if(*(pChar + i) == 0)break;
			}	
			CString temp = pChar;
			Directory = temp.Left(LastSlashPos);
		}
		File = FileDirectory == 128 ? pNextFile : dlg.m_FilePath;
		PostFix = dlg.m_TablesPostFix;
		LogFilePath = Directory + "LogFile.txt";
		while(FileDirectory == 128 ? File.GetLength() > 0 : A++ == 0)
		{
			TotalPath = FileDirectory == 128 ? Directory + File : File;
			int result = GF.ComputeFile(FileDirectory == 128 ? TotalPath : dlg.m_FilePath);
			NumTracks += GF.GFC.pT->CountTracks(GF.GFC.pT->m_pTrackUp);
			if(SaveTables)GF.SaveTables(Directory,PostFix);
			GF.GFC.pSetInteger(GF.GFC.pContext,GF.GFC.pIdc->TotalMips,NumTracks);
			pNextFile = (pNextFile + File.GetLength() + 1);
			File = FileDirectory == 128 ? pNextFile : " ";
			if(result == 0)
			{	if(FileDirectory == 128)continue;
				else
				{	GF.ImageSpace();
					*(GF.GFC.ppThread) = NULL;
					*GF.m_pComputingInProgress = false;
					return 1;	}	}
			GF.m_Session++;	}
		if(!dlg.m_Fog2000)GF.ImageSpace();
		//if(((CWnd *)GF.GFC.pContext)->IsWindow())GF.GFC.pContext->FlashWindow(true);
		if(GF.GFC.pMessage)GF.GFC.pMessage("Finished!","Grain Finder - Batch Manager",MB_OK | MB_ICONEXCLAMATION);
		LogFilePath = OldLogFile;
		*(GF.GFC.ppThread) = NULL;
		*GF.m_pComputingInProgress = false;
		return 2;	}
	else { *(GF.GFC.ppThread) = NULL; return 0;}
}

int CGrainFinder::LoadTextGrains(CString Path)
{
	FILE * loadingFile = fopen(Path,"r");
	m_GrainsFilePath = Path;
	int result,i;
	int Allocated;
	float x,y,z;
	bool InvertXY = GFC.pGfPa->InvertXY;
	if(loadingFile == NULL)
	{
		if(GFC.pMessage)GFC.pMessage("Error Opening File!","Grain Finder - LoadTextGrains 1",MB_OK);
		return 0;
	}
	GFC.pT->DeleteMips(GFC.pT->m_pTrackUp);
	m_EmSpaceUp.GetSpace();
	SIntGrain * pGrains = m_EmSpaceUp.pGrains;
	Allocated = m_EmSpaceUp.Allocated;
	for(i = 0; i < m_EmSpaceUp.Allocated; i++)
	{
		result = fscanf(loadingFile,"%f %f %f",&x,&y,&z);
		if(result != 3){break;}
		SIntGrain &gr = *(pGrains + i);
		if(InvertXY)gr = SIntGrain(y,x,z);
		else gr = SIntGrain(x,y,z);
		if(Allocated == i + 1)
		{
			pGrains = (SIntGrain *)realloc(pGrains,(Allocated + 1024)*sizeof(SIntGrain));
			if(pGrains == NULL)
			{
				if(GFC.pMessage)GFC.pMessage("Error Obtaining Memory!","Grain Finder - LoadTextGrains 2",MB_ICONASTERISK);
				break;
			}
			m_EmSpaceUp.pGrains = pGrains;
			Allocated += 1024;
			m_EmSpaceUp.Allocated = Allocated;
		}
	}
	fclose(loadingFile);
	m_EmSpaceUp.NumGrains = i;
	if(i > 0)
	{
//		*(GFC.pNumGrains) = m_EmulsionRegion.NumGrains;
		m_FileLoaded = true;
		m_GrainsVersion = 4;
		if(GFC.pSetInteger)GFC.pSetInteger(GFC.pContext, GFC.pIdc->TotalGrains,m_EmSpaceUp.NumGrains);
	//	SetWindowText(m_FogDlg.EditGrains,(temp.Format("%d",m_NumGrains),temp));
		if(GFC.pGFTParam->Options & FOG_OPT_CORRECTDIST)FindOperaDistortion(m_EmSpaceUp);
		CheckDensity(m_EmSpaceUp);
		if(GFC.pUpdateShow)GFC.pUpdateShow(GFC.pContext,255);
	}
	return m_EmSpaceUp.NumGrains;

}

int CGrainFinder::ImageSpace()
{
	if(m_pImageData == NULL)
	{	m_pImageData = (BYTE *)malloc(GFC.pMicPar->HalfCCDLength*GFC.pMicPar->HalfCCDWidth*4*5);
		if(m_pImageData == NULL)
		{	if(GFC.pMessage)GFC.pMessage("Unable to Continue! Memory Error.","Grain Finder - ImageSpace",MB_OK | MB_ICONEXCLAMATION);
			return 0;	}
		else 	return 1;	}
	else
	{	free(m_pImageData);
		m_pImageData = NULL;	}
	return 2;
}

int CGrainFinder::ChangeSet(int Delta, int Threshold,float Radius,float RingSize)
{
	if(m_GrainsVersion == 3 || m_GrainsVersion == 5 || m_GrainsVersion == 6 || m_GrainsVersion == 7)
	{	int NumGrains = 0,NumMin = m_UsedMin,index = 0,count = 0,i;
//		float Fiducials[8];
		SEmulsionSpace &S = m_EmSpaceUp;
		SIntGrain * pGrains = S.pGrains;
		bool DeltaTest,ThresholdTest,RingTest;
		if(pGrains != NULL){free(pGrains);}
		bool InvertXY = GFC.pGfPa->InvertXY;
		for(i = 0; i < NumMin; i++)
		{	SGrain &G = *(m_pMinGrains + i);
			DeltaTest = (int)(G.Max + 128 - G.Min) >= Delta;
//			ThresholdTest = (int)(G.DeltaNextMax + G.Max + 128 - G.Min - G.DeltaNextMin) >= Threshold || 
//				(int)(G.DeltaPrevMax + G.Max + 128 - G.Min - G.DeltaPrevMin) >= Threshold;
			ThresholdTest = !((int)(G.DeltaNextMax + G.Max + 128 - G.Min - G.DeltaNextMin) < Threshold && 
				(int)(G.DeltaPrevMax + G.Max + 128 - G.Min - G.DeltaPrevMin) < Threshold);
			if(Radius > 0.f && RingSize > 0.f)
			{
				SIntGrain Gr;
				G.ToIntGrain(&Gr,m_depths,GFC.pMicPar,InvertXY,&S.Distortion);
				float GrainRadiusQuad = (Gr.x * Gr.x + Gr.y * Gr.y);
				float Radius1Quad = (Radius - RingSize)*(Radius - RingSize);
				float Radius2Quad = (Radius + RingSize)*(Radius + RingSize);
				RingTest = GrainRadiusQuad > Radius1Quad && GrainRadiusQuad < Radius2Quad;
			}
			else RingTest = true;
			if(DeltaTest && ThresholdTest && RingTest)NumGrains++;	}
		pGrains = (SIntGrain *)malloc(NumGrains * sizeof(SIntGrain));
		if(pGrains == NULL){if(GFC.pMessage)GFC.pMessage("No Memory Available!","Grain Finder - ChangeSet 1",MB_OK);}
		S.pGrains = pGrains;
		S.Allocated = NumGrains;
		for(i = 0; i < NumMin; i++)
		{	SGrain &G = *(m_pMinGrains + i);
			DeltaTest = (int)(G.Max + 128 - G.Min) >= Delta;
//			ThresholdTest = (int)(G.DeltaNextMax + G.Max + 128 - G.Min - G.DeltaNextMin) >= Threshold || 
//				(int)(G.DeltaPrevMax + G.Max + 128 - G.Min - G.DeltaPrevMin) >= Threshold;
			ThresholdTest = !((int)(G.DeltaNextMax + G.Max + 128 - G.Min - G.DeltaNextMin) < Threshold && 
				(int)(G.DeltaPrevMax + G.Max + 128 - G.Min - G.DeltaPrevMin) < Threshold);
			if(Radius > 0.f && RingSize > 0.f)
			{
				SIntGrain Gr;
				G.ToIntGrain(&Gr,m_depths,GFC.pMicPar,InvertXY,&S.Distortion);
				float GrainRadiusQuad = (Gr.x * Gr.x + Gr.y * Gr.y);
				float Radius1Quad = (Radius - RingSize)*(Radius - RingSize);
				float Radius2Quad = (Radius + RingSize)*(Radius + RingSize);
				RingTest = GrainRadiusQuad > Radius1Quad && GrainRadiusQuad < Radius2Quad;
			}
			else RingTest = true;
			if(DeltaTest && ThresholdTest && RingTest)
				G.ToIntGrain(pGrains + index++,m_depths,GFC.pMicPar,InvertXY,&S.Distortion);}
		S.NumGrains = NumGrains;
		*GFC.pLastNumGrains = NumGrains;}
	return m_EmSpaceUp.NumGrains;
}

int CGrainFinder::ComputeSetOfImages(BYTE *pBytes,int NumberOfImages)
{
	int Herr,LastNumGrains,LocalGrains;
	int i,frame;
	int IsDifferential;
	CString ErrorMessage;
	UINT Options,TrackGrains,bSaveGrains,ShowImage,bSaveTxt;
	int bSaveTables;
	GFC.pT->DeleteMips(GFC.pT->m_pTrackUp);
	if(GFC.pUpdateShow)GFC.pUpdateShow(GFC.pContext,FOG_UPDATE_TRACKS);
	Options = GFC.pGFTParam->Options;
	TrackGrains = FOG_OPT_TRACK & Options;
//	ShowTracks = FOG_OPT_SHOWTRACKS & Options;
	bSaveGrains = FOG_OPT_SAVEGRAINS & Options;
	ShowImage = FOG_OPT_SHOWPICTURE & Options;
//	ShowGrains = FOG_OPT_SHOWGRAINS & Options;
//	Color = (24 & Options)/8;
	bSaveTxt = FOG_OPT_SAVETXT & Options;
	bSaveTables = FOG_OPT_SAVETABLES & Options;
	int bCorrectDistortion = GFC.pGFTParam->Options & FOG_OPT_CORRECTDIST;
	m_EmSpaceUp.GetSpace();
	m_GrainsVersion = 7;
	IsDifferential = GFC.pGFTParam->Options & 1;
//	for(frame = 2; frame < NumberOfImages - 2; frame++)
	for(frame = 1; frame < NumberOfImages - 1; frame++)
	{	LastNumGrains = m_EmSpaceUp.NumGrains;
		Herr = ComputeData(frame);
		LocalGrains = m_EmSpaceUp.NumGrains - LastNumGrains;
		if(Herr > 0){if(GFC.pMessage)GFC.pMessage((ErrorMessage.Format("Memory Error: %d",Herr),ErrorMessage),"Grain Finder - ComputeSetOfImages 1",MB_OK);break;}
		if(ShowImage && GFC.pShowPicture)
			GFC.pShowPicture(GFC.pContext,frame,Options,m_EmSpaceUp.pGrains + LastNumGrains,LocalGrains,GFC.pT->m_pTrackUp);
		if(GFC.pSetInteger)
		{	GFC.pSetInteger(GFC.pContext, GFC.pIdc->TotalGrains,m_EmSpaceUp.NumGrains);
			GFC.pSetInteger(GFC.pContext, GFC.pIdc->Frame,frame);
			GFC.pSetInteger(GFC.pContext, GFC.pIdc->LocalGrains,m_EmSpaceUp.NumGrains - LastNumGrains);	}
		if(GFC.pSetFloat)GFC.pSetFloat(GFC.pContext, GFC.pIdc->Depth,*(m_depths + frame - 1));
	}
	m_UsedMin = m_EmSpaceUp.NumGrains;
	if(bCorrectDistortion)FindOperaDistortion(m_EmSpaceUp);
	else CheckDensity(m_EmSpaceUp);
	GFC.pGFTParam->FilePath = m_GrainsFilePath;
	if(TrackGrains)
	{	int count;
		STrackingInfo::ETracker Tracker = GFC.pT->TP.pTrackInfo->Tracker;
		if(Tracker == STrackingInfo::Tre)count = GFC.pT->Track3(m_EmSpaceUp,GFC.pT->m_pTrackUp);
		if(GFC.pSetInteger)GFC.pSetInteger(GFC.pContext, GFC.pIdc->TotalMips,count);	}
	if(bSaveGrains | bSaveTxt)
	{	if(bSaveGrains)SaveGrains(m_GrainsFilePath);
		if(bSaveTxt)SaveGrains(m_GrainsFilePath,-1);	}
	if(GFC.pUpdateShow)GFC.pUpdateShow(GFC.pContext,255);
	return 0;
}
int CGrainFinder::ComputeFrame(int frame)
{
	int Herr,LastNumGrains,LocalGrains;
	CString ErrorMessage;
	UINT Options,ShowImage;
	Options = GFC.pGFTParam->Options;
	ShowImage = FOG_OPT_SHOWPICTURE & GFC.pGFTParam->Options;
	
	LastNumGrains = m_EmSpaceUp.NumGrains;
	Herr = ComputeData(frame);
	LocalGrains = m_EmSpaceUp.NumGrains - LastNumGrains;
	if(Herr > 0){if(GFC.pMessage)GFC.pMessage((ErrorMessage.Format("Memory Error: %d",Herr),ErrorMessage),"Grain Finder - ComputeFrame 1",MB_OK);}
	if(ShowImage && GFC.pShowPicture)
		GFC.pShowPicture(GFC.pContext,frame,GFC.pGFTParam->Options,m_EmSpaceUp.pGrains + LastNumGrains,LocalGrains,GFC.pT->m_pTrackUp);
	if(GFC.pSetInteger)
	{	GFC.pSetInteger(GFC.pContext, GFC.pIdc->TotalGrains,m_EmSpaceUp.NumGrains);
		GFC.pSetInteger(GFC.pContext, GFC.pIdc->Frame,frame);
		GFC.pSetInteger(GFC.pContext, GFC.pIdc->LocalGrains,m_EmSpaceUp.NumGrains - LastNumGrains);	}
	if(GFC.pSetFloat)GFC.pSetFloat(GFC.pContext, GFC.pIdc->Depth,*(m_depths + frame - 1));
	return LocalGrains;
}

int CGrainFinder::PurgeFile(int Up,int Dw)
{
	int i;
	float MaxZ = -NOT_USED_DEPTH,MinZ = NOT_USED_DEPTH,workZ;
	const int BinsPerMicron = 2;
	const int ConfidenceInterval = 7;//Confidence interval is reduced by microns added to MaxZ and MinZ
	const int MinExpectedGrains = 12;// Density of 0.2g/1000µ³
	int BinsToSkip = BinsPerMicron*ConfidenceInterval;
	SIntGrain * pGrains = m_EmSpaceUp.pGrains;
	int NumGrains = m_EmSpaceUp.NumGrains,NotMin = 0,NumZetas,AverageNumGrains;
	int MaxNumberOfImages = GFC.pScanner->MaxNumberOfImages;
	for(i = 0; i < NumGrains; i++)
	{	workZ = (pGrains + i)->zz;
		MinZ = workZ > MinZ ? MinZ : workZ;
		MaxZ = workZ < MaxZ ? MaxZ : workZ;	}
	MaxZ = (float)(int)MaxZ + 3.f;
	MinZ = (float)(int)MinZ - 1.f;
	NumZetas = (int)(BinsPerMicron*(MaxZ - MinZ));//Half Micron Bins : 2g/1000µ³ * 390µ * 310µ * 0.5µ = 120.9g
	int * pBins = (int *)calloc(sizeof(int),NumZetas);
	bool InvertXY = GFC.pGfPa->InvertXY;
	if(pBins)
	{
		int StartI,EndI,Index = 0,MaxNumGrains = 0;
		float Start,End;
		int Delta = GFC.pGfPa->Delta,Threshold = GFC.pGfPa->Threshold;
		bool DeltaTest,ThresholdTest;
		for(i = 0; i < NumGrains;i++)
		{
			workZ = (pGrains + i)->zz;
			(*(pBins + (int)(BinsPerMicron*(workZ - MinZ))))++;
		}
		for(i = 0; i < NumZetas; i++)
		{
			if(*(pBins + i) > MinExpectedGrains)NotMin++;
		}
		AverageNumGrains = (NumGrains >> 2)/NotMin;
		for(i = 0; i < NumZetas; i++)if(*(pBins + i) > AverageNumGrains)break;
		StartI = i - BinsToSkip - Dw;
		if(StartI < 0)StartI = 0;
		for(i = 0; i < NumZetas; i++)if(*(pBins + NumZetas - 1 - i) > AverageNumGrains)break;
		EndI = NumZetas - 1 - i + BinsToSkip + Up;
		if(EndI > NumZetas)EndI = NumZetas;
		Start = MinZ + StartI/BinsPerMicron;
		End = MinZ + EndI/BinsPerMicron;
		for(i = 0; i < MaxNumberOfImages; i++)
			if(*(m_depths + i) > End)*(m_depths + i) = NOT_USED_DEPTH;
			else break;
		StartI = i;
		for(i = 0; i < MaxNumberOfImages; i++)
		{
			if(*(m_depths + MaxNumberOfImages - i - 1) < NOT_USED_DEPTH)
			{
				if(*(m_depths + MaxNumberOfImages - i - 1) < Start)*(m_depths + MaxNumberOfImages - i - 1) = NOT_USED_DEPTH;
				else break;
			}
		}
		EndI = MaxNumberOfImages - i - 1;
		for(i = 0; i < m_UsedMin; i++)
		{
			SGrain & Grain = *(m_pMinGrains + i);
			if((Grain.z - 1 < StartI) || (Grain.z + 1 > EndI))continue;
			DeltaTest = (int)(Grain.Max + 128 - Grain.Min) >= Delta;
			ThresholdTest = !((int)(Grain.DeltaNextMax + Grain.Max + 128 - Grain.Min - Grain.DeltaNextMin) < Threshold && 
				(int)(Grain.DeltaPrevMax + Grain.Max + 128 - Grain.Min - Grain.DeltaPrevMin) < Threshold);
			if(!(DeltaTest && ThresholdTest))continue;
			Grain.z -= StartI;
			*(m_pMinGrains + Index++) = Grain;
		}
		m_UsedMin = Index;
		memcpy(m_depths,m_depths + StartI,sizeof(float)*(EndI - StartI + 1));
		for(i = (EndI - StartI + 1); i < MaxNumberOfImages; i++)
			*(m_depths + i) = NOT_USED_DEPTH;
		if(GFC.pScanner->m_NumberOfImages)
		{
			if(StartI)memcpy(m_pImageData,m_pImageData + StartI*1280*1024,1280*1024*(EndI - StartI + 1));
			GFC.pScanner->m_NumberOfImages = (EndI - StartI + 1);
		}
	}
	free(pBins);
	for(i = 0; i < m_UsedMin; i++)
	{
		SGrain &G = *(m_pMinGrains + i);
		G.ToIntGrain(pGrains + i,m_depths,GFC.pMicPar,InvertXY,&m_EmSpaceUp.Distortion);
	}
	m_EmSpaceUp.NumGrains = m_UsedMin;
	CheckDensity(m_EmSpaceUp);
	if(GFC.pUpdateShow)GFC.pUpdateShow(GFC.pContext,255);
	*GFC.pLastNumGrains = NumGrains;
	return 0;
}

SGrainTest * CGrainFinder::ExtendedGrainTest(unsigned char *pByte,UINT Options)
{
	static SGrainTest GT;
	SGrainTest * pGT = &GT;
	SGrain Grain;
	memset(pGT,0,sizeof(SGrainTest));
	pGT->FromImage = true;
	int Delta,Threshold,ImageDivision,ImageSize = mImageSize;
	if(Options & FOG_OPT_PARENTPARAM && GFC.pGetComputingParameters)
	{	GFC.pGetComputingParameters(GFC.pContext,Threshold,ImageDivision,Delta); }
	else { Delta = GFC.pGfPa->Delta; Threshold = GFC.pGfPa->Threshold; }
	int Frame = 0,i = 0;
	if(GFC.pGetInteger && GFC.pIdc->Frame)GFC.pGetInteger(GFC.pContext,GFC.pIdc->Frame,Frame);
	int Frames[7] = {0,1,2,3,-1,-2,-3};
	while(!pGT->IsGrain && i < 1 && Frames[i] + Frame > 2)
	{
		if(pGT->IsGrain = GrainTest(&Grain,Frame + Frames[i],pByte + Frames[i]*ImageSize,Delta,Threshold,Options))
		{
			pGT->Frame = Frame + Frames[i];
		}
		i++;
	}
	BYTE Max = IsAMinimum(pByte);
	pGT->IsMinimum = (Max > 0);
	if(pGT->IsMinimum)pGT->Delta = Max - *pByte;
	else pGT->Delta = 0;
	Max = IsAMinimum(pByte + 1280*1024);
	pGT->IsNextMinimum = (Max > 0);
	if(pGT->IsNextMinimum)pGT->NextDelta = Max - *(pByte + 1280*1024);
	else pGT->NextDelta = 0;
	Max = IsAMinimum(pByte - 1280*1024);
	pGT->IsPreviousMinimum = (Max > 0);
	if(pGT->IsPreviousMinimum)pGT->PreviousDelta = Max - *(pByte - 1280*1024);
	else pGT->PreviousDelta = 0;
	if(pGT->IsGrain && pGT->Frame == Frame)
	{
		Grain.ToIntGrain(&pGT->Grano,m_depths,GFC.pMicPar,false,&m_EmSpaceUp.Distortion);
		pGT->Delta = Grain.Max + 128 - Grain.Min;
		pGT->PreviousDelta = pGT->Delta + Grain.DeltaPrevMax - Grain.DeltaPrevMin;
		pGT->NextDelta = pGT->Delta + Grain.DeltaNextMax - Grain.DeltaNextMin;
		int Count = GFC.pT->CountTracks();
		if(Count > 0)
		{
			int SeeMip = 0;
			if(GFC.pGetInteger && GFC.pIdc->SeeMip)GFC.pGetInteger(GFC.pContext,GFC.pIdc->SeeMip,SeeMip);
			SMip *pMip = NULL;
			if(SeeMip != 0 && SeeMip <= Count)
			{
				pMip = GFC.pT->m_pTrackUp;
				for(i = 1; i < SeeMip; i++)
				{
					pMip = pMip->pNext;
				}
				pGT->DistanceXY = GFC.pT->Distance(&pGT->Grano,pMip,FOG_DISTANCE_XY);
				pGT->DistanceZ = GFC.pT->Distance(&pGT->Grano,pMip,FOG_DISTANCE_Z);
				pGT->Distance = GFC.pT->Distance0(&pGT->Grano,pMip,false);
				pGT->IsoDistance = GFC.pT->Distance0(&pGT->Grano,pMip,true);
				pGT->Distance = GFC.pT->Distance(&pGT->Grano,pMip,FOG_DISTANCE_DEFAULT);
				pGT->IsoDistance = GFC.pT->Distance(&pGT->Grano,pMip,FOG_DISTANCE_ISOMETRIC);
			}
		}
		else pGT->Distance = 0.f;
	}

	return pGT;
}


SGrainTest * CGrainFinder::ExtendedGrainTest(int Dx,int Dy,float z)
{
	static SGrainTest GT;
	SGrainTest * pGT = &GT;
	SGrain * pGrain;
	memset(pGT,0,sizeof(SGrainTest));
	bool DistanceEvaluated = false;
	int i,x,y;
	for(i = 0; i < m_UsedMin; i++)
	{
		pGrain = m_pMinGrains + i;
		x = (int)pGrain->x;
		if((x - Dx < -1) || (x - Dx > 1))continue;
		y = (int)pGrain->y;
		if((y - Dy < -1) || (y - Dy > 1))continue;
		pGrain->ToIntGrain(&pGT->Grano,m_depths,GFC.pMicPar,false,&m_EmSpaceUp.Distortion);
		if(fabs(pGT->Grano.z - z) > 2.f)continue;
		else break;
	}
	if(i == m_UsedMin)return pGT;
	pGT->Delta = pGrain->Max + 128 - pGrain->Min;
	pGT->PreviousDelta = pGT->Delta + pGrain->DeltaPrevMax - pGrain->DeltaPrevMin;
	pGT->NextDelta = pGT->Delta + pGrain->DeltaNextMax - pGrain->DeltaNextMin;
	pGT->IsGrain = true;
	int Count = GFC.pT->CountTracks();
	if(Count > 0)
	{
		int SeeMip = 0;
		if(GFC.pGetInteger && GFC.pIdc->SeeMip)GFC.pGetInteger(GFC.pContext,GFC.pIdc->SeeMip,SeeMip);
		SMip *pMip = NULL;
		if(SeeMip != 0 && SeeMip <= Count)
		{
			pMip = GFC.pT->m_pTrackUp;
			for(int i = 1; i < SeeMip; i++)
			{
				pMip = pMip->pNext;
			}
			pGT->Distance = GFC.pT->Distance(&pGT->Grano,pMip);
		}
	}

	return pGT;
}
void CGrainFinder::ClearMemory(void)
{
	m_EmSpaceUp.GetSpace();
	m_pMinGrains = (SGrain *)realloc(m_pMinGrains,sizeof(SGrain)*1024);
	m_NumMin = 1024;
	m_UsedMin = 0;
}
void CGrainFinder::SaveMicData(int Side,fpos_t & LastPos,const char * pPath)
{
	if(m_EmSpaceUp.NumGrains == 0)return;
	FILE * micSavingFile;
	CString GrsFile;
	if(pPath == NULL)GrsFile = m_PredData.OutputPath;
	else GrsFile = pPath;
	CString Extension = GrsFile.Right(4);
	if(Extension.CompareNoCase(".mic"))GrsFile += ".mic";
	m_GrainsFilePath = GrsFile;
	char identifier[16] = "Opera Mic View ";
	int i,count,versionNumber = 1;
	int Zeri[20]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	if(Side == 0)
	{
		micSavingFile = fopen(GrsFile,"wb");
		if(micSavingFile)
		{
			m_PredData.D.ImageCountUp = GFC.pScanner->m_NumberOfImages;
			m_PredData.D.StageX = GFC.pScanner->Opera.XStage;
			m_PredData.D.StageY = GFC.pScanner->Opera.YStage;
			fwrite(identifier,sizeof(identifier),1,micSavingFile);
			fwrite(&versionNumber,sizeof(int),1,micSavingFile);
			fwrite(&Side,sizeof(int),1,micSavingFile);
			fwrite(&m_PredData.D,sizeof(SOperaData),1,micSavingFile);
			fwrite(Zeri,sizeof(Zeri),1,micSavingFile);
			count = GFC.pT->CountTracks(GFC.pT->m_pTrackUp);
			fwrite(&m_UsedMin,sizeof(int),1,micSavingFile);
			fwrite(&count,sizeof(int),1,micSavingFile);
			fwrite(&m_EmSpaceUp.Distortion,sizeof(SDistortion),1,micSavingFile);
			fwrite(&m_Sheet,sizeof(SSheet),1,micSavingFile);
			fwrite(&m_EmSpaceUp.ZetaRange,sizeof(float),4,micSavingFile);
			fwrite(&m_EmSpaceUp.AdjustedDensity,sizeof(float),1,micSavingFile);
			byte first = 0,last = 0;
			for(i = 0; i <= 255; i++){if(*(m_depths + i)==NOT_USED_DEPTH)first++;else break;}
			for(i = (last = first); i <= 255; i++){if(*(m_depths + i) != NOT_USED_DEPTH)last++;}
			fwrite(&first,sizeof(byte),1,micSavingFile);
			fwrite(&last,sizeof(byte),1,micSavingFile);
			fwrite(m_depths + first,sizeof(float),last - first,micSavingFile);
			fwrite(m_pMinGrains,sizeof(SGrain),m_UsedMin,micSavingFile);
			if(count > 0)
			{
				SMip * pNext = GFC.pT->m_pTrackUp;
				for(i = 0; i < count; i++)
				{
					pNext->Save(micSavingFile,7);
					pNext = pNext->pNext;
				}
			}
			for(i = 0; i < m_PredData.D.ImageCountUp; i++)
			{
				fwrite(m_pImageData + i*1024*1280,1024,1280,micSavingFile);
			}
			int posSize = sizeof(fpos_t);
			fgetpos(micSavingFile,&LastPos);
			fclose(micSavingFile);
		}
		else if(GFC.pMessage)
			GFC.pMessage("Error Opening File!","Grain Finder - Save MicData 1",MB_OK);
	}
	else
	{
		micSavingFile = fopen(GrsFile,"rb+");
		if(micSavingFile)
		{
			m_PredData.D.ImageCountDw = GFC.pScanner->m_NumberOfImages;
			fseek(micSavingFile,sizeof(identifier) + sizeof(int),SEEK_SET);
			fwrite(&Side,sizeof(int),1,micSavingFile);
			fwrite(&m_PredData.D,sizeof(SOperaData),1,micSavingFile);
			fsetpos(micSavingFile,&LastPos);
			fwrite(Zeri,sizeof(Zeri),1,micSavingFile);
			count = GFC.pT->CountTracks(GFC.pT->m_pTrackUp);
			fwrite(&m_UsedMin,sizeof(int),1,micSavingFile);
			fwrite(&count,sizeof(int),1,micSavingFile);
			fwrite(&m_EmSpaceUp.Distortion,sizeof(SDistortion),1,micSavingFile);
			fwrite(&m_EmSpaceUp.ZetaRange,sizeof(float),4,micSavingFile);
			fwrite(&m_EmSpaceUp.AdjustedDensity,sizeof(float),1,micSavingFile);
			byte first = 0,last = 0;
			for(i = 0; i <= 255; i++){if(*(m_depths + i)==NOT_USED_DEPTH)first++;else break;}
			for(i = (last = first); i <= 255; i++){if(*(m_depths + i) != NOT_USED_DEPTH)last++;}
			fwrite(&first,sizeof(byte),1,micSavingFile);
			fwrite(&last,sizeof(byte),1,micSavingFile);
			fwrite(m_depths + first,sizeof(float),last - first,micSavingFile);
			fwrite(m_pMinGrains,sizeof(SGrain),m_UsedMin,micSavingFile);
			if(count > 0)
			{
				SMip * pNext = GFC.pT->m_pTrackUp;
				for(i = 0; i < count; i++)
				{
					pNext->Save(micSavingFile,7);
					pNext = pNext->pNext;
				}
			}
			for(i = 0; i < m_PredData.D.ImageCountDw; i++)
			{
				fwrite(m_pImageData + i*1024*1280,1024,1280,micSavingFile);
			}
			fgetpos(micSavingFile,&LastPos);
			fclose(micSavingFile);
		}
		else if(GFC.pMessage)
			GFC.pMessage("Error Opening File!","Grain Finder - Save MicData 2",MB_OK);
	}
}


int CGrainFinder::LoadMicData(const char * pFilePath)
{
	FILE * micFile;
	CString MicFile;
	if(pFilePath == NULL)
		return 1;
	MicFile = pFilePath;
	char identifier[16] = "Opera Mic View ";
	char id[16];
	int i,TrackCount,versionNumber,Side;
	micFile = fopen(MicFile,"rb");
	int Zeri[20];
	for(i = 0; i <= 255; i++)
		*(m_depths + i) = NOT_USED_DEPTH;
	int MaxNumberOfImages = GFC.pScanner->MaxNumberOfImages;
	BYTE first,last;
	SMip * pNext;
	SGrain * pGrain;
	if(micFile != NULL)
	{
		//Side UP
		fread(id,sizeof(id),1,micFile);
		if(memcmp(id,identifier,sizeof(id)))
		{
			fclose(micFile);
			return 3;
		}
		fread(&versionNumber,sizeof(int),1,micFile);
		fread(&Side,sizeof(int),1,micFile);
		fread(&m_PredData.D,sizeof(SOperaData),1,micFile);
		m_MicData.LevelsUp = m_PredData.D.ImageCountUp;
		m_MicData.LevelsDw = m_PredData.D.ImageCountDw;
		if(m_MicData.LevelsUp && m_MicData.LevelsDw)m_MicData.HasImages = true;
		fread(Zeri,sizeof(Zeri),1,micFile);
		fread(&m_UsedMin,sizeof(int),1,micFile);
		m_EmSpaceUp.NumGrains = m_UsedMin;
		if(m_pMinGrains)
			free(m_pMinGrains);
		m_pMinGrains = (SGrain *)calloc(m_UsedMin,sizeof(SGrain));
		if(m_pMinGrains)
			m_NumMin = m_UsedMin;
		else
		{
			GFC.pMessage("Error Opening File!","Grain Finder - Load Mic Data 4",MB_OK);
			return 4;
		}
		fread(&TrackCount,sizeof(int),1,micFile);
		fread(&m_EmSpaceUp.Distortion,sizeof(SDistortion),1,micFile);
		fread(&m_Sheet,sizeof(SSheet),1,micFile);
		fread(&m_EmSpaceUp.ZetaRange,sizeof(float),4,micFile);
		fread(&m_EmSpaceUp.AdjustedDensity,sizeof(float),1,micFile);
		fread(&first,sizeof(byte),1,micFile);
		fread(&last,sizeof(byte),1,micFile);
		fread(m_depths + first,sizeof(float),last - first,micFile);
		fread(m_pMinGrains,sizeof(SGrain),m_UsedMin,micFile);
		if(TrackCount > 0)
		{
			pNext = m_MicData.pMipsUp;
			for(i = 0; i < TrackCount; i++)
			{	pNext->Load(micFile,7);
				if(i < TrackCount - 1 && pNext->AddNext() != NULL)
					pNext = pNext->pNext;
			}
		}
		if(m_EmSpaceUp.pGrains)free(m_EmSpaceUp.pGrains);
		m_EmSpaceUp.pGrains = (SIntGrain *)calloc(m_UsedMin,sizeof(SIntGrain));
		if(m_EmSpaceUp.pGrains)
			m_EmSpaceUp.Allocated = m_UsedMin;
		else 
		{
			m_EmSpaceUp.Allocated = 0;
			GFC.pMessage("Error Opening File!","Grain Finder - Load Mic Data 5",MB_OK);
			return 5;
		}
		bool InvertXY = GFC.pGfPa->InvertXY;
		SIntGrain * pGrains = m_EmSpaceUp.pGrains;
		for(i = 0; i < m_UsedMin; i++)
		{
			pGrain = m_pMinGrains + i;
			pGrain->ToIntGrain(pGrains + i,m_depths,GFC.pMicPar,InvertXY,&m_EmSpaceUp.Distortion);
		}
		m_EmSpaceUp.CheckDensity();
		if(m_MicData.LevelsUp + m_MicData.LevelsDw > MaxNumberOfImages)
		{
			bool result = GFC.pScanner->ReallocGlobalBytes(m_MicData.LevelsUp + m_MicData.LevelsDw);
			if(!result)
			{
				GFC.pMessage("Error Opening File!","Grain Finder - Load Mic Data 6",MB_OK);
				return 6;
			}
			MaxNumberOfImages = m_MicData.LevelsUp + m_MicData.LevelsDw;
		}
		for(i = 0; i < m_MicData.LevelsUp; i++)
		{
			fread(m_pImageData + 1024*1280*i,1280,1024,micFile);
		}
		
		//Side DW
		int UsedMinDw,TotalUsedMin;
		fread(Zeri,sizeof(Zeri),1,micFile);
		fread(&UsedMinDw,sizeof(int),1,micFile);
		m_EmSpaceDw.NumGrains = UsedMinDw;
		fread(&TrackCount,sizeof(int),1,micFile);
		fread(&m_EmSpaceDw.Distortion,sizeof(SDistortion),1,micFile);
		fread(&m_EmSpaceDw.ZetaRange,sizeof(float),4,micFile);
		fread(&m_EmSpaceDw.AdjustedDensity,sizeof(float),1,micFile);
		fread(&first,sizeof(byte),1,micFile);
		fread(&last,sizeof(byte),1,micFile);
		fread(m_depths + first + m_MicData.LevelsUp,sizeof(float),last - first,micFile);
		TotalUsedMin = m_UsedMin + UsedMinDw;
		SGrain * pMinGrains = (SGrain *)realloc(m_pMinGrains,sizeof(SGrain)*(TotalUsedMin));
		if(pMinGrains)
		{
			m_pMinGrains = pMinGrains;
//			m_UsedMin += UsedMinDw;// Later! m_UsedMin needed;
		}
		else
		{
			GFC.pMessage("Error Opening File!","Grain Finder - Load Mic Data 7",MB_OK);
			return 7;
		}
		fread(m_pMinGrains + m_UsedMin,sizeof(SGrain),UsedMinDw,micFile);
		if(m_EmSpaceDw.pGrains)free(m_EmSpaceDw.pGrains);
		m_EmSpaceDw.pGrains = (SIntGrain *)malloc(sizeof(SIntGrain)*UsedMinDw);
		if(m_EmSpaceDw.pGrains)
		{
			m_EmSpaceDw.Allocated = UsedMinDw;
			pGrains = m_EmSpaceDw.pGrains;
		}
		else
		{
			GFC.pMessage("Memory Error","Grain Finder - Load Mic Data 8",MB_OK);
			return 8;
		}
		for(i = 0; i < UsedMinDw; i++)
		{
			pGrain = m_pMinGrains + i  + m_UsedMin;
			pGrain->z += m_MicData.LevelsUp;
			pGrain->ToIntGrain(pGrains + i,m_depths,GFC.pMicPar,InvertXY,&m_EmSpaceDw.Distortion);
		}
		m_EmSpaceDw.CheckDensity();
		m_UsedMin += UsedMinDw;
		if(TrackCount > 0)
		{
			pNext = m_MicData.pMipsDw;
			for(i = 0; i < TrackCount; i++)
			{	pNext->Load(micFile,7);
				if(i < TrackCount - 1 && pNext->AddNext() != NULL)
					pNext = pNext->pNext;
			}
		}
		for(i = 0; i < m_MicData.LevelsDw; i++)
		{
			fread(m_pImageData + 1024*1280*(i + m_MicData.LevelsUp),1280,1024,micFile);
		}
		int byte1,byte2,wI,j,m1,m2,Offset,Off2 = 0;
		BYTE * pB;
		Offset = m_MicData.LevelsUp - 2;
		Off2 = m_MicData.LevelsUp;
		for(i = 0; i < 3; i++)
		{
			m1 = 12 - 4*i;
			m2 = 4 + 4*i;
			if(i == 2)
			{
				Off2 = m_MicData.LevelsUp - 1;
				wI = m1;		m1 = m2;		m2 = wI;
			}
			for(j = 0; j < 1310720; j++)
			{
				pB = m_pImageData + 1310720 * (Offset + i) + j;
				byte1 = *pB;
				byte2 = *(m_pImageData + 1310720 * Off2 + j);
				wI = byte1*m1 + byte2*m2;
				*pB = (BYTE)(wI >> 4);
			}
		}
		GFC.pScanner->m_NumberOfImages = m_MicData.LevelsUp + m_MicData.LevelsDw;
		GFC.pScanner->m_bGlobalBytesLoaded = true;
		m_MicData.pGlobalBytes = m_pImageData;
		m_FileLoaded = true;
		fclose(micFile);
	}
	else if(GFC.pMessage)
	{
		GFC.pMessage("Error Opening File!","Grain Finder - Load Mic Data 1",MB_OK);
		return 2;
	}
	return 0;
}

