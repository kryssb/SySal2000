


int CTracker::Track2(SEmulsionSpace & Space)
{
	int count = 0;
	m_IsTrackingInProgress = true;
	DeleteMips(m_pTrackUp);
	SMip * pMip ;
	CString temp;
	m_Distortion = Space.Distortion;
	float MaxDev = TP.pTrackInfo->ErrorXY;
	if(Space.NumGrains == 0)return 0;
	int i,j;
	qsort(Space.pGrains,Space.NumGrains,sizeof(SIntGrain),CompareIntGrainYA);
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Tracked Grains");
	pMip = m_pTrackUp;
	STracker * pT = &TP;
	SEmulsionSections Sections(pT);
//	int miii = 0;
//	SEmulsionSections Sections(pT,1.57,1.57,1,miii);
	float MinY = TP.pMicPar->HalfCCDWidth*TP.pMicPar->PixLen - TP.pTrackInfo->MaxGap;
	int NumSections = Sections.NumVerSections*Sections.NumHorSections;
	SSection ** ppSections,*pSections = Sections.pSections;
	for(i = 0; i < NumSections; i++)
	{	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->LocalGrains,(temp.Format("%d/%d",i+1,NumSections),temp));
		SSection &section = *(pSections + i);
		for(j = 0; j < section.NGrains; j++)
		{	SIntGrain * pgrain = *(section.ppGrains + j);
			if(pgrain->y < MinY)break;
			ppSections = SelectTrackGrains(pgrain,Sections);
			/*for(j = 1000; j < Sections.NumHostSections;j++)
			{	SSection * pSec = Sections.GetNextSection(pgrain + i);
				if(*(ppSections + j) != pSec)ASSERT(FALSE);	}*/
			TrackGrains(pgrain,&Sections,pMip,MaxDev);	}	}
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Local Grains");
	count = DefineMips(MaxDev);
	if(TP.pSetInteger)TP.pSetInteger(TP.pContext, TP.pIdc->Mips,count);
	if(count > 1)
	{	pMip = m_pTrackUp;
		FindRadialDistortion(m_Distortion,pMip);
		FindDepthDistortion(m_Distortion,pMip);
		FindLinearCorrection(m_Distortion,Space);
		ApplyDistortionCorrection(m_Distortion,m_pTrackUp);
		ApplyDistortionCorrection(TP.pEmSpaceUp->Distortion,*TP.pEmSpaceUp);
		DefineMips(MaxDev);	}
	count = DefineMips(MaxDev);
	if(TP.pSetInteger)TP.pSetInteger(TP.pContext, TP.pIdc->Mips,count);
	m_IsTrackingInProgress = false;

	return count;
}
