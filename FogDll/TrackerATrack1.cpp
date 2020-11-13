

int CTracker::Track1(SEmulsionSpace & Space)
{
	int count = 0;
	m_IsTrackingInProgress = true;
	DeleteMips(m_pTrackUp);
	SMip * pMip ;
	SIntGrain * pgrain;
	CString temp;
	m_Distortion = Space.Distortion;
	float MaxDev = TP.pTrackInfo->ErrorXY;
	if(Space.NumGrains == 0)return 0;
	int i;
	qsort(Space.pGrains,Space.NumGrains,sizeof(SIntGrain),CompareIntGrainYA);
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Tracked Grains");
	pMip = m_pTrackUp;
	m_UpperEdgeSpace = SelectUpperEdgeGrains(Space);
	pgrain = m_UpperEdgeSpace.pGrains;
	STracker * pT = &TP;
	float MinY = TP.pMicPar->HalfCCDLength*TP.pMicPar->PixLen - TP.pTrackInfo->MaxGap;
	for(i = 0; i < m_UpperEdgeSpace.NumGrains; i++)
	{	if(pgrain->y < MinY)break;
		if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->LocalGrains,(temp.Format("%d/%d",i+1,m_UpperEdgeSpace.NumGrains),temp));
		m_TrackSpace = SelectTrackGrains(*(pgrain + i),Space);
		TrackGrains(*(pgrain + i),m_TrackSpace,pMip,MaxDev);
		free(m_TrackSpace.pGrains);
		}//	}
//	free(m_UpperEdgeSpace.pGrains);
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

