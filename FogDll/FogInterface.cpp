#include "stdafx.h"
#include "FogInterface.h"
#include "FogDlg.h"

CFogDlg * pFogInterfaceDlg = NULL;


void FogShouldStop(bool stop)
{
	pFogInterfaceDlg->m_Scanner.m_bShouldStop = stop;
}
#ifndef FOG_HOME

int FogGetQuantities(IStage2 * iST, ISySalObject *iStOb, IFrameGrabber * iFG, float & TopFog, float & TopMaxZ, float & TopMinZ, float & TopQuality, int & TopLight, float & BtmFog, float & BtmMaxZ, float & BtmMinZ, float & BtmQuality, int & BtmLight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SFogInit F;//= {false,true,iStOb,iST,NULL,iFG};
	F.IsEmbedded = true;
	F.iOdyOb = NULL;
	F.iSt2 = iST;
	F.iStOb = iStOb;
	F.ScanningAvailable = true;
	F.iFG = iFG;
	CFogDlg dlg(&F);
	pFogInterfaceDlg = &dlg;
	SOperaAsked &O = dlg.m_Scanner.Opera;
	O.SideDw = 0;
	O.SideDwFogDensity = 0;
	O.SideDwLight = 0;
	O.SideDwMaxZ = 0;
	O.SideDwMinZ = 0;
	O.SideUp = 0;
	O.SideUpFogDensity = 0;
	O.SideUpLight = 0;
	O.SideUpMaxZ = 0;
	O.SideUpMinZ = 0;
	O.XStage = 0;
	O.YStage = 0;
	O.ToReturn = 0;
	int Result = 0;
	O.SideUpMaxZ = TopMaxZ;

	dlg.m_Scanner.Scan();

	TopMaxZ = O.SideUpMaxZ;
	TopMinZ = O.SideUpMinZ;
	TopFog = O.SideUpFogDensity;
	TopQuality = O.SideUp;
	TopLight = O.SideUpLight;
	BtmMaxZ = O.SideDwMaxZ;
	BtmMinZ = O.SideDwMinZ;
	BtmFog = O.SideDwFogDensity;
	BtmQuality = O.SideDw;
	BtmLight = O.SideDwLight;
	if(O.SideUp < 0.8)Result |= 1;
	if(O.SideDw < 0.8)Result |= 2;

	pFogInterfaceDlg = NULL;
	return O.ToReturn;
}


int FogTakeImages(IStage2 *iST, ISySalObject *iStOb, IFrameGrabber *iFG, 
				  const char *outputpath, float mappedx, float mappedy, float topmaxz, 
				  float bottommaxz, double imxx, double imxy, double imyx, double imyy,
				  float sbsx, float sbsy,Identifier id)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SFogInit F;//= {false,true,iStOb,iST,NULL,iFG};
	F.IsEmbedded = true;
	F.iOdyOb = NULL;
	F.iSt2 = iST;
	F.iStOb = iStOb;
	F.iFG = iFG;
	F.ScanningAvailable = (F.iSt2 != NULL && F.iStOb != NULL && F.iFG != NULL);;
	CFogDlg dlg(&F);
	pFogInterfaceDlg = &dlg;
	int result;
	SPredictionTakeImages & Pred = dlg.m_CGrainFinder.m_PredData;
	Pred.OutputPath = outputpath;
	Pred.D.ImageCountDw = 0;
	Pred.D.sx = sbsx;		Pred.D.sy = sbsy;
	Pred.D.MappedX = mappedx;		Pred.D.MappedY = mappedy;
	Pred.D.Imxx = imxx;		Pred.D.Imxy = imxy;		Pred.D.Imyx = imyx;		Pred.D.Imyy = imyy;
	dlg.GFTParam.Options |= FOG_OPT_SAVETABLES;
	dlg.GFTParam.Options |= FOG_OPT_SAVETRACKTABLE;
//Temp 
	//int i,WaitTime;
	//float x,y,z;
	//dlg.m_Scanner.m_Mover.GetPos(x,y,z);
	//for(i = 0; i < 50; i++)
	//{
	//	Pred.OutputPath.Format("F:\\DatiMic\\DatiMic %02d.mic", i + 1);
	//	WaitTime = dlg.m_Scanner.m_Mover.MoveTo(x + 500*i,y);
	//	if(i > 0)
	//		z = dlg.m_Scanner.Opera.SideUpMaxZ;
	//	dlg.m_Scanner.m_Mover.MoveZTo(z + 50,0,FOG_WAITTIME_AUTOMATIC,WaitTime);
//End Temp
	result = dlg.m_Scanner.Scan(true);
//Temp
//	}
//EndTemp
	//dlg.m_Scanner.SetLight(0,false);
	pFogInterfaceDlg = NULL;
	return result;
}

#endif



int FogShow(
#ifndef FOG_HOME
			IStage2 * iST, ISySalObject *iStOb, IFrameGrabber * iFG
#endif
			)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SFogInit F;//= {false,true,iStOb,iST,NULL,iFG};
	F.IsEmbedded = false;
#ifndef FOG_HOME
	F.iOdyOb = NULL;
	F.iSt2 = iST;
	F.iStOb = iStOb;
	F.iFG = iFG;
	F.ScanningAvailable = (F.iSt2 != NULL && F.iStOb != NULL && F.iFG != NULL);
#else
	F.ScanningAvailable = false;
#endif
	CFogDlg dlg(&F);
	pFogInterfaceDlg = &dlg;
	SOperaAsked &O = dlg.m_Scanner.Opera;
	int Result = 0;
	int nResponse;
	nResponse = dlg.DoModal();

	if(nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	pFogInterfaceDlg = NULL;
	return Result;	
}
