
__int64 Counter1 = 0,Counter2 = 0,Counter3 = 0;

float SquareDistance(float mx,float my,float mz,float nxMenox0,float nyMenoy0,float nzMenoz0,float alfaQuadro)
{
	// distanza del punto {p1,p2,p3} dalla retta specificata dai primi quattro parametri
	// assegnando alla coponente z della distanza un peso alfa.
	float Add,wf1;
	//	((my*(nx-x0)+mx*(-ny+y0))²+alfa²*((mz*(nx-x0)+mx*(-nz+z0))²+(mz*(ny-y0)+my*(-nz+z0))²))/(mx²+my²+alfa²*mz²)
	wf1 = mz*nxMenox0;
	wf1 = wf1 - mx*nzMenoz0;
	Add = wf1*wf1;
	wf1 = mz*nyMenoy0;
	wf1 = wf1 - my*nzMenoz0;
	Add = Add + wf1*wf1;
	Add = alfaQuadro*Add;
	wf1 = my*nxMenox0;
	wf1 = wf1 - mx*nyMenoy0;
	Add = Add + wf1*wf1;
	return Add/(mx*mx + my*my + alfaQuadro*mz*mz);
}

double SquareDistanceDouble(double mx,double my,double mz,double nxMenox0,double nyMenoy0,double nzMenoz0,double alfaQuadro)
{
	// distanza del punto {p1,p2,p3} dalla retta specificata dai primi quattro parametri
	// assegnando alla coponente z della distanza un peso alfa.
	double Add,wf1;
	//	((my*(nx-x0)+mx*(-ny+y0))²+alfa²*((mz*(nx-x0)+mx*(-nz+z0))²+(mz*(ny-y0)+my*(-nz+z0))²))/(mx²+my²+alfa²*mz²)
	wf1 = mz*nxMenox0;
	wf1 = wf1 - mx*nzMenoz0;
	Add = wf1*wf1;
	wf1 = mz*nyMenoy0;
	wf1 = wf1 - my*nzMenoz0;
	Add = Add + wf1*wf1;
	Add = alfaQuadro*Add;
	wf1 = my*nxMenox0;
	wf1 = wf1 - mx*nyMenoy0;
	Add = Add + wf1*wf1;
	return Add/(mx*mx + my*my + alfaQuadro*mz*mz);
}

#include "TrackerATrack31.cpp"

bool SGrainChain::PushGrain(SIntGrain * pGrain)
{
	if(NGrains == Allocated)
	{
		SIntGrain ** ppNew = (SIntGrain **)calloc(sizeof(SIntGrain *),Block + Allocated);
		if(ppNew)
		{
			memcpy(ppNew,ppGrains,sizeof(SIntGrain *)*Allocated);
			free(ppGrains);
			ppGrains = ppNew;
			Allocated += Block;
		}
	}
	if(!(NGrains == Allocated))
	{
		for(int i = 0; i < NGrains; i++)
			if(*(ppGrains + i) == pGrain)return false;
		*(ppGrains + NGrains++) = pGrain;
		Counter1++;
		return true;
	}
	MessageBox(NULL,"Memory Error","Grain Chain",MB_OK);
	return false;
}

bool SGrainChain::PopGrain(int Pos)//Pos from 0 to NGrains - 1
{
	if(Pos >= NGrains || Pos < 0)return false;
	*(ppGrains + Pos) = *(ppGrains + NGrains - 1);
	*(ppGrains + --NGrains) = NULL;
	return true;
}

void SGrainChain::Join(SGrainChain * pChain,bool Delete)
{
	float ChainGrains = (float)pChain->NGrains;
	float nGrains = (float)NGrains;
	float TotalGrains = (nGrains + ChainGrains);
	float count = 0;
	for(int i = 0; i < ChainGrains; i++)
		if(PushGrain(*(pChain->ppGrains + i)))count++;
	if(Delete)delete pChain;
	nGrains += (ChainGrains - count);
}

int SGrainChain::FromSections(SSection ** ppSec,int totGrains)
{
	NGrains = 0;
	int i,j,ngrains,TotalGrains = 100;
	SSection * pSec;
//	for(i = 0; i < 9; i++)TotalGrains += (pSection + i)->NGrains;
	if(Allocated < totGrains)
	{
		free(ppGrains);
		ppGrains = (SIntGrain **)calloc(sizeof(SIntGrain *),totGrains);
		Allocated = totGrains;
	}
	for(i = 0; i < 9; i++)
	{
		pSec = *(ppSec + i);
		ngrains = pSec->NGrains;
		for(j = 0; j < ngrains; j++)
		{
			*(ppGrains + NGrains++) = *(pSec->ppGrains + j);
		}
	}
	return 0;
}

void SGrainChain::Join(SSection * pSection)
{
	for(int i = 0; i < pSection->NGrains; i++)
		PushGrain(*(pSection->ppGrains + i));
}
SGrainChain::SGrainChain(SMip * pMip)
{
	int i;
	NGrains = pMip->NGrains;
	ppGrains = (SIntGrain **)calloc(sizeof(SIntGrain * ),NGrains);
	if(ppGrains)
	{
		Allocated = NGrains;
		for(i = 0; i < NGrains; i++)
		{
			*(ppGrains + i) = pMip->pGrains + i;
		}
		Alpha = pMip->Alfa;
		axe = pMip->Axe;
		Block = 10;
		GiC = pMip->GiC;
		Length = pMip->Length;
		MaxDist = pMip->MaxDist;
		MaxGap = pMip->MaxGap;
		mdxy = pMip->md;
		MeanGap = pMip->MeanGap;
		mx = pMip->mx;
		my = pMip->my;
		mz = pMip->mz;
		NomLength = pMip->NomLength;
		nx = pMip->nx;
		ny = pMip->ny;
		nz = pMip->nz;
		sigmax = pMip->sigmax;
		sigmay = pMip->sigmay;
		sigmaz = pMip->sigmaz;
	}
	else
	{
	}
}
SChains::~SChains()
{
//	for(int i = 0; i < NChains; i++){ delete *(ppChains + i);}
	free(ppChains);
}

bool SChains::PushChain(SGrainChain * pChain)// Only stores the pointer;
{
	if(NChains == Allocated)
	{
		SGrainChain ** ppNew = (SGrainChain **)calloc(sizeof(SGrainChain *),10 + Allocated);
		if(ppNew)
		{
			memcpy(ppNew,ppChains,sizeof(SGrainChain *)*Allocated);
			free(ppChains);
			ppChains = ppNew;
			Allocated += 10;
		}
	}
	if(!(NChains == Allocated)){ *(ppChains + NChains++) = pChain; return true;}
	MessageBox(NULL,"Memory Error","struct SChains",MB_OK);
	return false;
}

bool SChains::PopChain(int Pos,bool Delete)//Pos from 0 to NGrains - 1
{
	if(Pos >= NChains || Pos < 0)return false;
	if(Delete)delete *(ppChains + Pos);
	*(ppChains + Pos) = *(ppChains + --NChains);
	*(ppChains + NChains) = NULL;
	return true;
}

void SChains::Join(SChains * pChains)// pChains' Chains will be destroyed;
{
	int &ChainChains = pChains->NChains;
	while(ChainChains > 0)
	{
		PushChain(*(pChains->ppChains + --ChainChains));
		pChains->PopChain(ChainChains,false);
	}
//	delete pChains;

}

void SChains::DeleteChains()// Only deletes Chains
{
	while(NChains > 0)
	{
		delete *(ppChains + --NChains);
		*(ppChains + NChains) = NULL;
	}
}

void SaveSections(const char * filePath,SEmulsionSections * pESections)
{
	FILE * pSectionsFile = fopen(filePath,"w");
	SIntGrain * pGr;
	SSection * pSection;
	int i,j,k;
	for(i = 0; i < pESections->NumHorSections; i++)
	{
		for(k = 0; k < pESections->NumVerSections;k++)
		{
			pSection = (pESections->pSections + i + pESections->NumHorSections*k);
			for(j = 0; j < pSection->NGrains; j++)
			{
				pGr = *(pSection->ppGrains + j);
				fprintf(pSectionsFile,"%d\t%d\t%.3f\t%.3f\t%.3f\n",i + 1,k + 1,pGr->x,pGr->y,pGr->z);
			}
		}
	}
	fclose(pSectionsFile);
}

void SaveSections2(const char * filePath,SEmulsionSections * pESections)
{
	FILE * pSectionsFile = fopen(filePath,"w");
	SSection * pSection;
	int i,k;
	int NumVerSections = pESections->NumVerSections,NumHorSections = pESections->NumHorSections;
	for(k = 0; k < NumVerSections;k++)
	{
		for(i = 0; i < NumHorSections; i++)
		{
			pSection = (pESections->pSections + i + NumHorSections*k);
			if(i < NumHorSections - 1)fprintf(pSectionsFile,"%d\t%.3f\t",pSection->NGrains,pSection->Length);
			else fprintf(pSectionsFile,"%d\t%.3f\n",pSection->NGrains,pSection->Length);
		}
	}
	fclose(pSectionsFile);
}

void SaveChains(const char * filePath,SChains * pChains)
{
	FILE * pChainsFile = fopen(filePath,"w");
	int i,j;
	SGrainChain * pGC;
	SIntGrain * pGr;
	for(i = 0; i < pChains->NChains; i++)
	{
		pGC = *(pChains->ppChains + i);
		fprintf(pChainsFile,"%d\t%d\t%f\t%f\t%f\n",i + 1,0,pGC->mx,pGC->my,pGC->mz);
		fprintf(pChainsFile,"%d\t%d\t%f\t%f\t%f\n",i + 1,0,pGC->nx,pGC->ny,pGC->nz);
		fprintf(pChainsFile,"%d\t%d\t%f\t%f\t%f\n",i + 1,0,pGC->sigmax,pGC->sigmay,pGC->sigmaz);
		fprintf(pChainsFile,"%d\t%d\t%f\t%f\t%d\n",i + 1,0,pGC->GiC,pGC->mdxy,pGC->NGrains);
		for(j = 0; j < pGC->NGrains; j++)
		{
			pGr = *(pGC->ppGrains + j);
			fprintf(pChainsFile,"%d\t%d\t%f\t%f\t%f\n",i + 1,j + 1,pGr->x,pGr->y,pGr->z);
		}
	}
	fclose(pChainsFile);
}

int CTracker::Track3(SEmulsionSpace & Space,SMip * pMips)
{
	m_IsTrackingInProgress = true;
	DeleteMips(pMips);
	if(TP.pUpdateShow)TP.pUpdateShow(TP.pContext,FOG_UPDATE_TRACKS);
	CString temp;
	if(Space.NumGrains == 0)return 0;
	const float Degree = PI_FOG/180.f;
//	qsort(Space.pGrains,Space.NumGrains,sizeof(SIntGrain),comparey);
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Tracked Sections");
	float StartTheta = TP.pTrackInfo->StartTheta,EndTheta = TP.pTrackInfo->EndTheta;
	float StartPhi = TP.pTrackInfo->StartPhi,EndPhi = TP.pTrackInfo->EndPhi;
	float CellXY = TP.pTrackInfo->CellXY,CellZ = TP.pTrackInfo->CellZ;
	float Theta,Phi,deltaTheta,Length,effCell = 1.5f*CellXY;
	float RefAngle = 1*Degree;//(float)((int)(Degree*(float)atan2(155.f,CellXY)) + 1);
	float DeltaPhi = TP.pTrackInfo->DeltaPhi,DeltaTheta = TP.pTrackInfo->DeltaTheta,deltaPhi;
	SEmulsionSections * pESections = new SEmulsionSections(&TP,&Space,StartTheta,StartPhi,CellXY,CellZ);
	bool btemp = false;
	int i = 0,j = 0,Center;
	for(Theta = StartTheta; Theta < EndTheta; Theta += deltaTheta)
	{	i++;	j = 0;
		if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->LocalGrains,(temp.Format("%d", (int)(Theta/Degree)),temp));
		if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->Mips,(temp.Format("%d", m_Chains.NChains),temp));
		for(Phi = StartPhi; Phi < EndPhi; Phi += deltaPhi)
		{	j++;
			pESections->Create(Theta,Phi,CellXY,CellZ);
			Track31(pESections);
			if(btemp)
			{
				temp.Format("C:\\Sysal2000\\Fog2000\\SectionsNumGrains %02d %02d.txt",i,j);
				SaveSections2(temp,pESections);
			}
			Center = (pESections->NumVerSections/2)*(pESections->NumHorSections) + pESections->NumHorSections/2;
			Length = (pESections->pSections + Center)->Length;
			DeltaPhi = 2*effCell/((float)fabs(Length));
			deltaPhi = DeltaPhi/pESections->Sphericals.sinTheta;
		}
		deltaTheta = DeltaPhi;
		PurgeChain(&Space,&m_TrackerChains);
		m_Chains.Join(&m_TrackerChains);
	}
	delete pESections;
//	SaveSections("C:\\Fulvio\\Sections.txt",pESections);
//	Track31(pESections);
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Chain found");
	PurgeChain(&Space,&m_Chains);
	SortChains(&m_Chains);
//	SaveChains("C://Fulvio\\Chains.txt",&m_Chains);
	ChainToMips(&m_Chains,pMips);
	
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Local Grains");
	if(TP.pSetInteger)TP.pSetInteger(TP.pContext, TP.pIdc->Mips,m_Chains.NChains);
	m_Chains.DeleteChains();
	m_IsTrackingInProgress = false;
	if(TP.pUpdateShow)TP.pUpdateShow(TP.pContext,FOG_UPDATE_TRACKS);
	return 0;
}

int CTracker::Track4(SEmulsionSpace & Space)
{
	m_IsTrackingInProgress = true;
	DeleteMips(m_pTrackUp);
	if(TP.pUpdateShow)TP.pUpdateShow(TP.pContext,FOG_UPDATE_TRACKS);
	CString temp;
	if(Space.NumGrains == 0)return 0;
	const float Degree = PI_FOG/180.f;
	const float Zero = 0.f;
//	qsort(Space.pGrains,Space.NumGrains,sizeof(SIntGrain),comparey);
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Tracked Sections");
	float StartTheta = TP.pTrackInfo->StartTheta,EndTheta = TP.pTrackInfo->EndTheta;
	float StartPhi = TP.pTrackInfo->StartPhi,EndPhi = TP.pTrackInfo->EndPhi;
	float CellXY = TP.pTrackInfo->CellXY,CellZ = TP.pTrackInfo->CellZ;
	float Theta,Phi,Length,effCell = 1.5f*CellXY;
	float RefAngle = 1*Degree;//(float)((int)(Degree*(float)atan2(155.f,CellXY)) + 1);
	float DeltaPhi = TP.pTrackInfo->DeltaPhi,DeltaTheta = TP.pTrackInfo->DeltaTheta;
	DeltaPhi = DeltaTheta = Degree;
	float deltaTheta = 2*DeltaTheta,deltaPhi = 2*DeltaPhi,cosdPhi = (float)cos(DeltaPhi),ThreeDegree = 3.f*Degree;
	SEmulsionSections * pESections = new SEmulsionSections(&TP,&Space,StartTheta,StartPhi,CellXY,CellZ);
	bool btemp = false;
	int i = 0,j = 0,Center;
	if(StartTheta < ThreeDegree)
	{
		StartTheta = ThreeDegree;
		for(i = 0; i < 2; i++)
		{
			pESections->Create2(Zero,Zero,0.01745f,CellZ);
			Track41(pESections);
			for(j = 0; j < 6; j++)
			{
				pESections->Create2(2.f*Degree,Degree*(j*60),0.01745f,CellZ);
				Track41(pESections);
				if(btemp)
				{
					temp.Format("C:\\Sysal2000\\Fog2000\\SectionsNumGrains %02d %02d.txt",i,j);
					SaveSections2(temp,pESections);
				}
				Center = (pESections->NumVerSections/2)*(pESections->NumHorSections) + pESections->NumHorSections/2;
				Length = (pESections->pSections + Center)->Length;
			}
			PurgeChain(&Space,&m_TrackerChains);
			m_Chains.Join(&m_TrackerChains);
		}
	}
	for(Theta = StartTheta; Theta < EndTheta; Theta += deltaTheta)
	{
		i++;	j = 0;
		if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->LocalGrains,(temp.Format("%d", (int)(Theta/Degree)),temp));
		if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->Mips,(temp.Format("%d", m_Chains.NChains),temp));
		pESections->Sphericals.Update(Theta,StartPhi);
		DeltaPhi = (float)acos((cosdPhi - pESections->Sphericals.cosTheta*pESections->Sphericals.cosTheta)/(pESections->Sphericals.sinTheta*pESections->Sphericals.sinTheta));
		deltaPhi = 2.f*DeltaPhi;
		for(Phi = StartPhi; Phi < EndPhi; Phi += deltaPhi)
		{	j++;
			pESections->Create2(Theta,Phi,0.01745f,CellZ);
			Track41(pESections);
			if(btemp)
			{
				temp.Format("C:\\Fulvio\\SectionsNumGrains %02d %02d.txt",i,j);
				SaveSections(temp,pESections);
			}
			Center = (pESections->NumVerSections/2)*(pESections->NumHorSections) + pESections->NumHorSections/2;
			Length = (pESections->pSections + Center)->Length;
		}
		PurgeChain(&Space, &m_TrackerChains);
		m_Chains.Join(&m_TrackerChains);
	}

	delete pESections;
//	SaveSections("C:\\Fulvio\\Sections.txt",pESections);
//	Track31(pESections);
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Chain found");
	PurgeChain(&Space,&m_Chains);
	SortChains(&m_Chains);
//	SaveChains("C://Fulvio\\Chains.txt",&m_Chains);
	ChainToMips(&m_Chains,m_pTrackUp);
	
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Local Grains");
	if(TP.pSetInteger)TP.pSetInteger(TP.pContext, TP.pIdc->Mips,m_Chains.NChains);
	m_Chains.DeleteChains();
	m_IsTrackingInProgress = false;
	if(TP.pUpdateShow)TP.pUpdateShow(TP.pContext,FOG_UPDATE_TRACKS);
	return 0;
}

int CTracker::Track5(SEmulsionSpace & Space)
{
	m_IsTrackingInProgress = true;
	DeleteMips(m_pTrackUp);
	if(TP.pUpdateShow)TP.pUpdateShow(TP.pContext,FOG_UPDATE_TRACKS);
	CString temp;
	if(Space.NumGrains == 0)return 0;
	const float Degree = PI_FOG/180.f;
	float StartTheta = TP.pTrackInfo->StartTheta,EndTheta = TP.pTrackInfo->EndTheta;
	float StartPhi = TP.pTrackInfo->StartPhi,EndPhi = TP.pTrackInfo->EndPhi;
	float CellXY = TP.pTrackInfo->CellXY,CellZ = TP.pTrackInfo->CellZ;
	float Theta,Phi;
	float RefAngle = 1*Degree;//(float)((int)(Degree*(float)atan2(155.f,CellXY)) + 1);
	float DeltaPhi = TP.pTrackInfo->DeltaPhi,DeltaTheta = TP.pTrackInfo->DeltaTheta;
	DeltaPhi = DeltaTheta = 1.f*Degree;
	EndTheta = 40.f*Degree;
	StartPhi = 0.f;
	EndPhi = 360.f*Degree;
	float deltaTheta = 2.f*DeltaTheta,deltaPhi;
	int i,j,NumGrains = Space.NumGrains;
	float MaxZ = Space.ZetaRange.UpperZ + 2.f;
	float MinZ = Space.ZetaRange.BottomZ - 2.f;
	float Width = MaxZ - MinZ;
	float Fifth = Width/5.f;
	float RefZUp = MaxZ - Fifth,RefZDw = MinZ + Fifth;
	int RefIUp,RefIDw;
	float dTh = 0.f,dPh = 0.f;
	float ThreeDegree = 3.f*Degree,cosdPhi = (float)cos(DeltaPhi);
	SEmulsionSections * pES = new SEmulsionSections(&TP,&Space,0.f,0.f,dTh,dPh);
//	qsort(Space.pGrains,Space.NumGrains,sizeof(SIntGrain),CompareIntGrainZD);
	SIntGrain ** ppGrains = pES->ppGrains, * pGrain;
	SSphericals &Sp = pES->Sphericals;
	Theta = 6.f*Degree;
	Phi = 355.f*Degree;
	FILE * pSecFile = fopen("C:\\Fulvio\\Secs.txt","w");
	fclose(pSecFile);
	for(i = 0; i < NumGrains; i++)
	{
		pGrain = *(ppGrains + i);
		if(pGrain->z < RefZUp)
		{
			RefIUp = i;
			break;
		}
	}
	for(i = NumGrains - 1; i >= 0; i--)
	{
		pGrain = *(ppGrains + i);
		if(pGrain->z > RefZDw)
		{
			RefIDw = i;
			break;
		}
	}
	if(true)//StartTheta < ThreeDegree)
	{
		StartTheta = ThreeDegree;
		Sp.Update(0.f,0.f);
		Track5(pES,0.f,0.f,Degree,45.f*Degree,NumGrains,RefIUp,RefIDw);
		Theta = 2.f*Degree;
		for(j = 0; j < 6; j++)
		{
			Sp.Update(Theta,(j*60)*Degree);
			Track5(pES,Theta,(j*60)*Degree,Degree,26.7f*Degree,NumGrains,RefIUp,RefIDw);
		}
//			PurgeChain(&m_TrackerChains);
//			m_Chains.Join(&m_TrackerChains);
	}
	for(Theta = StartTheta; Theta < EndTheta; Theta += deltaTheta)
	{
		Sp.Update(Theta,StartPhi);
		DeltaPhi = (float)acos((cosdPhi - Sp.cosTheta*Sp.cosTheta)/(Sp.sinTheta*Sp.sinTheta));
		deltaPhi = 2.f*DeltaPhi;
		for(Phi = StartPhi; Phi < EndPhi; Phi += deltaPhi)
		{
			Sp.Update(Theta,Phi);
			Track5(pES,Theta,Phi,DeltaTheta,DeltaPhi,NumGrains,RefIUp,RefIDw);
		}
		PurgeChain(&Space,&m_TrackerChains);
		m_Chains.Join(&m_TrackerChains);
	}
	Track5(pES,Theta,Phi,DeltaTheta,DeltaPhi,NumGrains,RefIUp,RefIDw);

	delete pES;
//	SaveSections("C:\\Fulvio\\Sections.txt",pESections);
//	Track31(pESections);
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Chain found");
	PurgeChain(&Space,&m_Chains);
	SortChains(&m_Chains);
//	SaveChains("C://Fulvio\\Chains.txt",&m_Chains);
	ChainToMips(&m_Chains,m_pTrackUp);
	
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Local Grains");
	if(TP.pSetInteger)TP.pSetInteger(TP.pContext, TP.pIdc->Mips,m_Chains.NChains);
	m_Chains.DeleteChains();
	m_IsTrackingInProgress = false;
	if(TP.pUpdateShow)TP.pUpdateShow(TP.pContext,FOG_UPDATE_TRACKS);
	return 0;
}


void CTracker::Track5(SEmulsionSections * pES,float Theta,float Phi,float DeltaTheta,float DeltaPhi,int NumGrains,int RefIUp, int RefIDw)
{
	SIntGrain * pGrain,* pGrainDw,* pGrainUp,** ppGrains = pES->ppGrains, *pGrainS1,*pGrainS2;
	SSphericals &Sp = pES->Sphericals;

	int i,j,k;
	bool testx,testy;
	float zup,zdw,zct,dth,dph,w11 = Sp.cosPhi,w12 = -Sp.sinPhi,w21 = Sp.sinPhi,w22 = Sp.cosPhi,mdth,mdph;
	zup = pES->Space.ZetaRange.UpperZ + 2.f;
	zdw = pES->Space.ZetaRange.BottomZ - 2.f;
	zct = (zup + zdw)*0.5f;
	float wfxup,wfyup,wfzup,wfz,wfx,wfy,mx,my,nx,ny,dx,dy,wf,wnx,wny;
	float mx2,my2,nx2,ny2;
	int refi,refj,counter = 0;
	mx = Sp.sinTheta*Sp.cosPhi/Sp.cosTheta;
	my = Sp.sinTheta*Sp.sinPhi/Sp.cosTheta;
	wf = (float)tan(Theta + DeltaTheta);
	dth = 1.1f*(wf - (float)tan(Theta))*(zup - zdw);
	dph = 1.1f*wf*((float)tan(DeltaPhi))*(zup - zdw);
	mdth = -dth;
	mdph = -dph;
	float dthm = dth*0.5f,dphm = dth*0.5f;
	float mdthm = -dthm,mdphm = -dphm;
	float u11,u12,u21,u22;
	for(i = 0; i < RefIUp; i++)
	{
		pGrainUp = *(ppGrains + i);
		wfxup = pGrainUp->x;
		wfyup = pGrainUp->y;
		wfzup = pGrainUp->z;
		nx = wfxup - wfzup*mx;
		ny = wfyup - wfzup*my;
		for(j = NumGrains - 1; j  > RefIDw; j--)
		{
			pGrainDw = *(ppGrains + j);
			wfz = pGrainDw->z;
			wfx = pGrainDw->x;
			wfy = pGrainDw->y;
			wnx = wfx - wfz*mx;
			wny = wfy - wfz*my;
			dx = wnx - nx;
			dy = wny - ny;
			wf = w11*dx + w12*dy;
			testx = wf < dth && wf > mdth;
			if(testx)
			{
				wf = w21*dx + w22*dy;
				testy = wf < dph && wf > mdph;
				if(testy)
				{
					mx2 = (wfxup - wfx)/(wfzup - wfz);
					my2 = (wfyup - wfy)/(wfzup - wfz);
					for(k = 0; k < NumGrains; k++)
					{
						pGrain = *(ppGrains + k);
						wfz = pGrain->z;
						wfx = pGrain->x;
						wfy = pGrain->y;
						wnx = wfx - wfz*mx;
						wny = wfy - wfz*my;
						dx = wnx - nx;
						dy = wny - ny;
						wf = w11*dx + w12*dy;//W should be updated, Approx1
						testx = wf < dthm && wf > mdthm;
						if(testx)
						{
							wf = w21*dx + w22*dy;
							testy = wf < dphm && wf > mdphm;
							if(testy)
							{
								if(k == i || k == j)
									continue;
								if(counter == 0)
								{
									refi = i;
									refj = j;
									counter++;
									pGrainS1 = pGrain;
								}
								else
								{
									if(i == refi && j == refj)
									{
										if(counter == 1)
											pGrainS2 = pGrain;
										counter++;
									}
									else
									{
										refi = i;
										refj = j;
										pGrainS1 = pGrain;
										counter = 1;
									}
									if(counter == 3)
									{
										FILE * pSecFile = fopen("C:\\Fulvio\\Secs.txt","a");
										fprintf(pSecFile,"%.3f\t%.3f\t%.3f\n",pGrainUp->x,pGrainUp->y,pGrainUp->z);
										fprintf(pSecFile,"%.3f\t%.3f\t%.3f\n",pGrainS1->x,pGrainS1->y,pGrainS1->z);
										fprintf(pSecFile,"%.3f\t%.3f\t%.3f\n",pGrainS2->x,pGrainS2->y,pGrainS2->z);
										fprintf(pSecFile,"%.3f\t%.3f\t%.3f\n",pGrain->x,pGrain->y,pGrain->z);
										fprintf(pSecFile,"%.3f\t%.3f\t%.3f\n",pGrainDw->x,pGrainDw->y,pGrainDw->z);
										fclose(pSecFile);
										counter = 0;
									}
								}
							}
						}
					}
					PurgeChain(&pES->Space,&m_TrackerChains);
					m_Chains.Join(&m_TrackerChains);
				}
			}
		}
	}
}

int CTracker::Track6(SEmulsionSpace & Space)
{
/*	m_IsTrackingInProgress = true;
	DeleteMips(m_pTrackUp);
	if(TP.pUpdateShow)TP.pUpdateShow(TP.pContext,FOG_UPDATE_TRACKS);
	CString temp;
	if(Space.NumGrains == 0)return 0;
	const float Degree = PI_FOG/180.f;
	float StartTheta = TP.pTrackInfo->StartTheta,EndTheta = TP.pTrackInfo->EndTheta;
	float StartPhi = TP.pTrackInfo->StartPhi,EndPhi = TP.pTrackInfo->EndPhi;
	float CellXY = TP.pTrackInfo->CellXY,CellZ = TP.pTrackInfo->CellZ;
	float Theta,Phi;
	float RefAngle = 1*Degree;//(float)((int)(Degree*(float)atan2(155.f,CellXY)) + 1);
	float DeltaPhi = TP.pTrackInfo->DeltaPhi,DeltaTheta = TP.pTrackInfo->DeltaTheta;
	DeltaPhi = DeltaTheta = 1.f*Degree;
	EndTheta = 40.f*Degree;
	StartPhi = 0.f;
	EndPhi = 360.f*Degree;
	float deltaTheta = 2.f*DeltaTheta,deltaPhi;
	int i,j,NumGrains = Space.NumGrains;
	float MaxZ = Space.ZetaRange.UpperZ + 2.f;
	float MinZ = Space.ZetaRange.BottomZ - 2.f;
	float Width = MaxZ - MinZ;
	float Fifth = Width/5.f;
	float RefZUp = MaxZ - Fifth,RefZDw = MinZ + Fifth;
	int RefIUp,RefIDw;
	float dTh = 0.f,dPh = 0.f;
	float ThreeDegree = 3.f*Degree,cosdPhi = (float)cos(DeltaPhi);
	SEmulsionSections * pES = new SEmulsionSections(&TP,0.f,0.f,dTh,dPh);
//	qsort(Space.pGrains,Space.NumGrains,sizeof(SIntGrain),CompareIntGrainZD);
	SIntGrain ** ppGrains = pES->ppGrains, * pGrain;
	SSphericals &Sp = pES->Sphericals;
	Theta = 6.f*Degree;
	Phi = 355.f*Degree;
	FILE * pSecFile = fopen("C:\\Fulvio\\Secs.txt","w");
	fclose(pSecFile);
	for(i = 0; i < NumGrains; i++)
	{
		pGrain = *(ppGrains + i);
		if(pGrain->z < RefZUp)
		{
			RefIUp = i;
			break;
		}
	}
	for(i = NumGrains - 1; i >= 0; i--)
	{
		pGrain = *(ppGrains + i);
		if(pGrain->z > RefZDw)
		{
			RefIDw = i;
			break;
		}
	}
	SIntGrain * pGrain,* pGrainDw,* pGrainUp,** ppGrains = pES->ppGrains, *pGrainS1,*pGrainS2;
//	SSphericals &Sp = pES->Sphericals;

	int i,j,k;
	bool testx,testy;
	float zup,zdw,zct,dth,dph,w11 = Sp.cosPhi,w12 = -Sp.sinPhi,w21 = Sp.sinPhi,w22 = Sp.cosPhi,mdth,mdph;
	zup = pES->Space.ZetaRange.UpperZ + 2.f;
	zdw = pES->Space.ZetaRange.BottomZ - 2.f;
	zct = (zup + zdw)*0.5f;
	float wfxup,wfyup,wfzup,wfz,wfx,wfy,mx,my,nx,ny,dx,dy,wf,wnx,wny;
	float mx2,my2,nx2,ny2;
	int refi,refj,counter = 0;
	mx = Sp.sinTheta*Sp.cosPhi/Sp.cosTheta;
	my = Sp.sinTheta*Sp.sinPhi/Sp.cosTheta;
	wf = (float)tan(Theta + DeltaTheta);
	dth = 1.1f*(wf - (float)tan(Theta))*(zup - zdw);
	dph = 1.1f*wf*((float)tan(DeltaPhi))*(zup - zdw);
	mdth = -dth;
	mdph = -dph;
	float dthm = dth*0.5f,dphm = dth*0.5f;
	float mdthm = -dthm,mdphm = -dphm;
	float u11,u12,u21,u22;
	double alfa = TP.pTrackInfo->Alpha;
	for(i = 0; i < RefIUp; i++)
	{
		pGrainUp = *(ppGrains + i);
		wfxup = pGrainUp->x;
		wfyup = pGrainUp->y;
		wfzup = pGrainUp->z;
		nx = wfxup - wfzup*mx;
		ny = wfyup - wfzup*my;
		for(j = NumGrains - 1; j  > RefIDw; j--)
		{
			pGrainDw = *(ppGrains + j);
			wfz = pGrainDw->z;
			wfx = pGrainDw->x;
			wfy = pGrainDw->y;
			wnx = wfx - wfz*mx;
			wny = wfy - wfz*my;
			dx = wnx - nx;
			dy = wny - ny;
			wf = w11*dx + w12*dy;
			testx = wf < dth && wf > mdth;
			if(testx)
			{
				wf = w21*dx + w22*dy;
				testy = wf < dph && wf > mdph;
				if(testy)
				{
					mx2 = (wfxup - wfx)/(wfzup - wfz);
					my2 = (wfyup - wfy)/(wfzup - wfz);
					for(k = 0; k < NumGrains; k++)
					{
						pGrain = *(ppGrains + k);
						if(Distance(*pGrainUp,*pGrain,*pGrainDw,alfa) < 0.5;
						wfz = pGrain->z;
						wfx = pGrain->x;
						wfy = pGrain->y;
						wnx = wfx - wfz*mx;
						wny = wfy - wfz*my;
						dx = wnx - nx;
						dy = wny - ny;
						wf = w11*dx + w12*dy;//W should be updated, Approx1
						testx = wf < dthm && wf > mdthm;
						if(testx)
						{
							wf = w21*dx + w22*dy;
							testy = wf < dphm && wf > mdphm;
							if(testy)
							{
								if(k == i || k == j)
									continue;
								if(counter == 0)
								{
									refi = i;
									refj = j;
									counter++;
									pGrainS1 = pGrain;
								}
								else
								{
									if(i == refi && j == refj)
									{
										if(counter == 1)
											pGrainS2 = pGrain;
										counter++;
									}
									else
									{
										refi = i;
										refj = j;
										pGrainS1 = pGrain;
										counter = 1;
									}
									if(counter == 3)
									{
										FILE * pSecFile = fopen("C:\\Fulvio\\Secs.txt","a");
										fprintf(pSecFile,"%.3f\t%.3f\t%.3f\n",pGrainUp->x,pGrainUp->y,pGrainUp->z);
										fprintf(pSecFile,"%.3f\t%.3f\t%.3f\n",pGrainS1->x,pGrainS1->y,pGrainS1->z);
										fprintf(pSecFile,"%.3f\t%.3f\t%.3f\n",pGrainS2->x,pGrainS2->y,pGrainS2->z);
										fprintf(pSecFile,"%.3f\t%.3f\t%.3f\n",pGrain->x,pGrain->y,pGrain->z);
										fprintf(pSecFile,"%.3f\t%.3f\t%.3f\n",pGrainDw->x,pGrainDw->y,pGrainDw->z);
										fclose(pSecFile);
										counter = 0;
									}
								}
							}
						}
					}
					PurgeChain(&m_TrackerChains);
					m_Chains.Join(&m_TrackerChains);
				}
			}
		}
	}
	delete pES;
//	SaveSections("C:\\Fulvio\\Sections.txt",pESections);
//	Track31(pESections);
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Chain found");
	PurgeChain(&m_Chains);
	SortChains(&m_Chains);
//	SaveChains("C://Fulvio\\Chains.txt",&m_Chains);
	ChainToMips();
	
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Local Grains");
	if(TP.pSetInteger)TP.pSetInteger(TP.pContext, TP.pIdc->Mips,m_Chains.NChains);
	m_Chains.DeleteChains();
	m_IsTrackingInProgress = false;
	if(TP.pUpdateShow)TP.pUpdateShow(TP.pContext,FOG_UPDATE_TRACKS);
	*/return 0;
}


int CTracker::GrainChainToMip(SGrainChain * pChain, SMip * pNext)
{
	int j;
	SIntGrain * pGrain;
	float MaxZ = -NOT_USED_DEPTH,MinZ = NOT_USED_DEPTH,zeta;
	pNext->GiC = pChain->GiC;
	pNext->md = pChain->mdxy;
	pNext->mx = pChain->mx;
	pNext->nx = pChain->nx;
	pNext->my = pChain->my;
	pNext->ny = pChain->ny;
	pNext->mz = pChain->mz;
	pNext->nz = pChain->nz;
	pNext->sigmax = pChain->sigmax;
	pNext->sigmay = pChain->sigmay;
	pNext->sigmaz = pChain->sigmaz;
	pNext->NGrains = pChain->NGrains;
	pNext->MaxGap = pChain->MaxGap;
	pNext->MaxDist = pChain->MaxDist;
	pNext->MeanGap = pChain->MeanGap;
	pNext->NomLength = pChain->NomLength;
	pNext->Length = pChain->Length;
	pNext->Axe = pChain->axe;
	pNext->Alfa = pChain->Alpha;
	if(pNext->NGrains > 300)pNext->NGrains = 300;
	for(j = 0; j < pNext->NGrains; j++)
	{
		pGrain = *(pChain->ppGrains + j);
		*(pNext->pGrains + j) = *pGrain;
		zeta = pGrain->z;
		if(zeta > MaxZ)MaxZ = zeta;
		if(zeta < MinZ)MinZ = zeta;
	}
	pNext->MaxZ = MaxZ;
	pNext->MinZ = MinZ;
	MaxZ = -NOT_USED_DEPTH;
	MinZ = NOT_USED_DEPTH;

	return 0;
}

void CTracker::ChainToMips(SChains *pChains,SMip * pMips)
{
	int i;
	SMip * pNext = pMips;
	SGrainChain * pChain;
	while(pNext->pNext != NULL)
	{
		pNext = pNext->pNext;
	}
	for(i = 0; i < m_Chains.NChains; i++)
	{
		pChain = *(m_Chains.ppChains + i);
		GrainChainToMip(pChain,pNext);
		pNext->AddNew();
		pNext = pNext->pNext;
	}
	return;
}

int CTracker::MergeMips(SMip *pMip1, SMip *pMip2)
{
	float GoodValue = 0.01f; // Horizontal tracks along y;
	float dmz = pMip1->mz - pMip2->mz;
	float dmx = pMip1->mx - pMip2->mx;
	float dnz,dnx;
	if(dmz < GoodValue && dmz > -GoodValue)
	{
		GoodValue = 0.006f;
		if(dmx < GoodValue && dmx > -GoodValue)
		{
			dnz = pMip1->nz - pMip2->nz;
			dnx = pMip1->nx - pMip2->nx;
			GoodValue = 1.f;
			if(dnz < GoodValue && dnz > -GoodValue)
			{
				GoodValue = 0.6f;
				if(dnx < GoodValue && dnx > -GoodValue)
				{
//					for(i
					return 1;
				}
			}
		}
	}
	return 0;
}

int CTracker::PurgeChain(SEmulsionSpace * pSpace,SChains * pChains)
{
	float GoodValue,dmx,dmy,dmz,dnx,dny,dnz;
	int i,j,k;
	int &NChains = pChains->NChains;
	SGrainChain * pGC1,* pGC2;
	for(k = 0; k < 3; k++)
	for(i = 0; i < NChains; i++)
	{
		pGC1 = (*(pChains->ppChains + i));
		for(j = i + 1; j < NChains; j++)
		{
			pGC2 = (*(pChains->ppChains + j));
			if(pGC2->axe == pGC1->axe)
			{
				if(pGC1->axe == XAXE)
				{
					GoodValue = 0.08f;
					dmz = pGC1->mz - pGC2->mz;
					if(dmz < GoodValue && dmz > -GoodValue)
					{
						GoodValue = 0.03f;
						dmy = pGC1->my - pGC2->my;
						if(dmy < GoodValue && dmy > -GoodValue)
						{
							GoodValue = 2.f;
							dnz = pGC1->nz - pGC2->nz;
							if(dnz < GoodValue && dnz > -GoodValue)
							{
								GoodValue = 1.2f;
								dny = pGC1->ny - pGC2->ny;
								if(dny < GoodValue && dny > -GoodValue)
								{
									pGC1->Join(pGC2,false);
									pChains->PopChain(j);
									RefineTrack2(pSpace,pGC1);
									j--;
								}
							}
						}
					}
				}
				if(pGC1->axe == YAXE)
				{
					GoodValue = 0.08f;
					dmz = pGC1->mz - pGC2->mz;
					if(dmz < GoodValue && dmz > -GoodValue)
					{
						GoodValue = 0.03f;
						dmx = pGC1->mx - pGC2->mx;
						if(dmx < GoodValue && dmx > -GoodValue)
						{
							dnz = pGC1->nz - pGC2->nz;
							GoodValue = 2.f;
							if(dnz < GoodValue && dnz > -GoodValue)
							{
								GoodValue = 1.2f;
								dnx = pGC1->nx - pGC2->nx;
								if(dnx < GoodValue && dnx > -GoodValue)
								{
									pGC1->Join(pGC2,false);
									pChains->PopChain(j);
									RefineTrack2(pSpace,pGC1);
									j--;
								}
							}
						}
					}
				}
				if(pGC1->axe == ZAXE)
				{
					GoodValue = 0.03f; 
					dmy = pGC1->my - pGC2->my;
					if(dmy < GoodValue && dmy > -GoodValue)
					{
						GoodValue = 0.03f;
						dmx = pGC1->mx - pGC2->mx;
						if(dmx < GoodValue && dmx > -GoodValue)
						{
							dny = pGC1->ny - pGC2->ny;
							GoodValue = 1.2f;
							if(dny < GoodValue && dny > -GoodValue)
							{
								GoodValue = 1.2f;
								dnx = pGC1->nx - pGC2->nx;
								if(dnx < GoodValue && dnx > -GoodValue)
								{
									pGC1->Join(pGC2,false);
									pChains->PopChain(j);
									RefineTrack2(pSpace,pGC1);
									j--;
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

void CTracker::LinearFit(SGrainChain *pTrack,bool Complete)
{
	static int counter = 0;//Counter3++;
	float maxy = -300,miny = 300,maxx = -300,minx = 300;
	float minz = NOT_USED_DEPTH,maxz = -NOT_USED_DEPTH;
	int i,NGrains = pTrack->NGrains;
//	const float ErrX = 0.3f,ErrY = 0.3f,ErrZ = 0.8f;
	float wx,wy,wz,worker;
	float Alfa = TP.pTrackInfo->Alpha;
	SIntGrain ** ppGrains = pTrack->ppGrains, * pwGrain;
	if(true)
	{
		for(i = 0;i < NGrains; i++)
		{	pwGrain = *(ppGrains + i);
			wx = pwGrain->x; wy = pwGrain->y; wz = pwGrain->z;
			if(wx > maxx)maxx = wx;
			if(wy > maxy)maxy = wy;
			if(wz > maxz)maxz = wz;
			if(wx < minx)minx = wx;
			if(wy < miny)miny = wy;
			if(wz < minz)minz = wz;	}
	}
	float LenX = (maxx - minx),LenY = maxy - miny, LenZ = maxz - minz;
	float * pInd,MaxInd,MinInd;
	double SommaInd = 0,SommaDep1 = 0,SommaDep2 = 0,SommaDep1Ind = 0,SommaDep2Ind = 0;
	double SommaIndQ = 0,SommaQInd = 0;
	double wInd,wDep1,wDep2,delta;
	int cInd,cDep1,cDep2;
	switch(pTrack->axe)
	{
		case XAXE :
			MaxInd = maxx;
			MinInd = minx;
			cInd = 0; cDep1 = 1; cDep2 = 2;
			break;
		case YAXE :
			MaxInd = maxy;
			MinInd = miny;
			cInd = 1,cDep1 = 0,cDep2 = 2;
			break;
		case ZAXE :
			MaxInd = maxz;
			MinInd = minz;
			cInd = 2; cDep1 = 0; cDep2 = 1;
			break;
	}
	for(i = 0;i < NGrains; i++)
	{
		pInd = (float *)*(ppGrains + i);
		wInd = *(pInd + cInd); wDep1 = *(pInd + cDep1); wDep2 = *(pInd + cDep2);
		SommaDep1 += wDep1;
		SommaIndQ += wInd*wInd;
		SommaDep1Ind += wInd*wDep1;
		SommaDep2Ind += wInd*wDep2;
		SommaInd += wInd;
		SommaDep2 += wDep2;
	}
	SommaQInd = SommaInd*SommaInd;
	delta = NGrains*SommaIndQ - SommaQInd;
	float MDep1,MDep2,MInd,NDep1,NDep2,NInd,SigmaDep1 = 0,SigmaDep2 = 0;
	MDep1 = (float)((NGrains*SommaDep1Ind - SommaDep1*SommaInd)/delta);
	MDep2 = (float)((NGrains*SommaDep2Ind - SommaDep2*SommaInd)/delta);
	MInd = 1.f;//(float)(MaxInd - MinInd);
	NDep1 = (float)((SommaIndQ*SommaDep1 - SommaInd*SommaDep1Ind)/delta);
	NDep2 = (float)((SommaIndQ*SommaDep2 - SommaInd*SommaDep2Ind)/delta);
	NInd = 0.f;//(float)MinInd;
	if(Complete)
	{
		float SommaDiffQDep1 = 0,SommaDiffQDep2 = 0;
		for(i = 0;i < NGrains; i++)
		{
			pInd = (float *)*(ppGrains + i);
			wInd = *(pInd + cInd); wDep1 = *(pInd + cDep1); wDep2 = *(pInd + cDep2);
			worker = (float)(wDep1 - NDep1 - MDep1*wInd);
			SommaDiffQDep1 += worker*worker;
			worker = (float)(wDep2 - NDep2 - MDep2*wInd);
			SommaDiffQDep2 += worker*worker;
		}
		SigmaDep1 = (float)(sqrt(SommaDiffQDep1/(NGrains - 2)));
		SigmaDep2 = (float)(sqrt(SommaDiffQDep2/(NGrains - 2)));
	}
	switch(pTrack->axe)
	{
		case XAXE :// Y Dep1, Z Dep2;
			pTrack->mx = MInd;
			pTrack->my = MDep1;
			pTrack->mz = MDep2;
			pTrack->nx = NInd;
			pTrack->ny = NDep1;
			pTrack->nz = NDep2;
			pTrack->sigmax = 0.f;
			pTrack->sigmay = SigmaDep1;
			pTrack->sigmaz = SigmaDep2;
			break;
		case YAXE :// X Dep1, Z Dep2;
			pTrack->mx = MDep1;
			pTrack->my = MInd;
			pTrack->mz = MDep2;
			pTrack->nx = NDep1;
			pTrack->ny = NInd;
			pTrack->nz = NDep2;
			pTrack->sigmax = SigmaDep1;
			pTrack->sigmay = 0.f;
			pTrack->sigmaz = SigmaDep2;
			break;
		case ZAXE :// X Dep1, Y Dep2;
			pTrack->mx = MDep1;
			pTrack->my = MDep2;
			pTrack->mz = MInd;
			pTrack->nx = NDep1;
			pTrack->ny = NDep2;
			pTrack->nz = NInd;
			pTrack->sigmax = SigmaDep1;
			pTrack->sigmay = SigmaDep2;
			pTrack->sigmaz = 0.f;
			break;
	}
//	float Temp = 0.f;
//	float distxy,distz,distxyQ,distancesxy = 0,distancesz = 0;
	float mx = pTrack->mx,my = pTrack->my,mz = pTrack->mz;
	float nx = pTrack->nx,ny = pTrack->ny,nz = pTrack->nz;
//	float Factor1,Factor2,UnoSuDen = (1.f/(1 + MDep1*MDep1 + MDep2*MDep2)),maxdist = 0;
	float maxdist = 0,dist,distances = 0;
	if(Complete)
	{
		float nxMenox0,nyMenoy0,nzMenoz0,wf1,Add,AlfaQuadro = Alfa*Alfa;
		for(i = 0;i < NGrains; i++)
		{
			pwGrain = *(ppGrains + i);
			wx = pwGrain->x; wy = pwGrain->y; wz = pwGrain->z;
			nxMenox0 = nx - wx; nyMenoy0 = ny - wy; nzMenoz0 = nz - wz;
	//	((my*(nx-x0)+mx*(-ny+y0))²+alfa²*((mz*(nx-x0)+mx*(-nz+z0))²+(mz*(ny-y0)+my*(-nz+z0))²))/(mx²+my²+alfa²*mz²)
			wf1 = mz*nxMenox0;
			wf1 = wf1 - mx*nzMenoz0;
			Add = wf1*wf1;
			wf1 = mz*nyMenoy0;
			wf1 = wf1 - my*nzMenoz0;
			Add = Add + wf1*wf1;
			Add = AlfaQuadro*Add;
			wf1 = my*nxMenox0;
			wf1 = wf1 - mx*nyMenoy0;
			Add = Add + wf1*wf1;
			wf1 =  Add/(mx*mx + my*my + AlfaQuadro*mz*mz);
			Add = Distance(pwGrain,pTrack);
			dist = sqrtf(wf1);//Distance(MDep1,NDep1,MDep2,NDep2,wx,wy,wz,Alfa);
			if(Add - dist < -0.05 || Add - dist > 0.05)
				Add = 0;
			distances += dist;
			if(maxdist < dist)maxdist = dist;
		}
		pTrack->MaxDist = maxdist;
		pTrack->mdxy = (float)(distances/NGrains);
		pTrack->Alpha = Alfa;
	}
	float maxgap = 0,factor,gap;
	if(Complete)
	{
		int (* pCompare)(const void *,const void *) = NULL;
		int NGrainsRed = NGrains - 1;
		distances = 0;
		if(pTrack->axe == XAXE)
		{
			qsort(ppGrains,NGrains,sizeof(SIntGrain *),CompareIntGrainPointerXA);
			wx = (*ppGrains)->x;
			for(i = 0; i < NGrainsRed;)
			{
				worker = wx;
				wx = (*(ppGrains + ++i))->x;
				distances += gap = (wx - worker);
				if(maxgap < gap)maxgap = gap;
			}
		}
		if(pTrack->axe == YAXE)
		{
			qsort(ppGrains,NGrains,sizeof(SIntGrain *),CompareIntGrainPointerYA);
			wy = (*ppGrains)->y;
			for(i = 0; i < NGrainsRed;)
			{
				worker = wy;
				wy = (*(ppGrains + ++i))->y;
				distances += gap = (wy - worker);
				if(maxgap < gap)maxgap = gap;
			}
		}
		if(pTrack->axe == ZAXE)
		{
			qsort(ppGrains,NGrains,sizeof(SIntGrain *),CompareIntGrainPointerZA);
			wz = (*ppGrains)->z;
			for(i = 0; i < NGrainsRed;)
			{
				worker = wz;
				wz = (*(ppGrains + ++i))->z;
				distances += gap = (wz - worker);
				if(maxgap < gap)maxgap = gap;
			}
		}
		factor = (float)sqrt(mx*mx + my*my + mz*mz);
		pTrack->MeanGap = factor*(distances/NGrainsRed);
		pTrack->MaxGap = factor*maxgap;
	}
	pTrack->Length = (float)sqrt(LenY*LenY + LenX*LenX + LenZ*LenZ);
	pTrack->GiC = ((float)(100*(NGrains - 1)))/(pTrack->Length);
}

const float Radiants = 180.f/PI_FOG;
int CompareChains(const void * ppChain1,const void * ppChain2)
{
	SGrainChain * pGC1 = *((SGrainChain **)ppChain1);
	SGrainChain * pGC2 = *((SGrainChain **)ppChain2);
	float theta1,theta2,phi1,phi2;
	float mx1,mx2,my1,my2,mz1,mz2;
	mx1 = pGC1->mx;	mx2 = pGC2->mx;
	my1 = pGC1->my;	my2 = pGC2->my;
	mz1 = pGC1->mz; mz2 = pGC2->mz;
	theta1 = (float)atan2(sqrt(mx1*mx1 + my1*my1),sqrt(mz1*mz1));
	theta2 = (float)atan2(sqrt(mx2*mx2 + my2*my2),sqrt(mz2*mz2));
	phi1 = (float)atan2(-my1,-mx1);
	phi2 = (float)atan2(-my2,-mx2);
	if(phi1 < 0)phi1 += 6.283185f;
	if(phi2 < 0)phi2 += 6.283185f;
	return ((int)(theta1*Radiants*1000) - (int)(theta2*Radiants*1000)) + (int)((phi1 - phi2)*Radiants);
}

void CTracker::SortChains(SChains *pChains)
{
	qsort(pChains->ppChains,pChains->NChains,sizeof(SGrainChain *),CompareChains);
}
