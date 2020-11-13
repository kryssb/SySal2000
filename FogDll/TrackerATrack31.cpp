
float GlobalDifference = 0.0001f;

void CTracker::Track31(SEmulsionSections * pESections)
{
	int i,j;
	int NumHorSections = pESections->NumHorSections;
	int NumVerSections = pESections->NumVerSections;
	int SectionIndex;
	SSection * pSection;
	float XExtension = 390.f,YExtension = 310.f,ZExtension = 42.f;
	float SectionVolume;
	FogAxe RefAxe = pESections->RefAxe;
	if(RefAxe == XAXE)
	{
		SectionVolume = pESections->CellXY*pESections->CellZ*pESections->Sphericals.FactorY*XExtension;			
	}
	else if(RefAxe == YAXE)
	{
		SectionVolume = pESections->CellXY*pESections->CellZ*pESections->Sphericals.FactorY*YExtension;	
	}
	else if(RefAxe == ZAXE)
	{
		SectionVolume = pESections->CellXY*pESections->CellXY*pESections->Sphericals.FactorZ*ZExtension;
	}
	float AverageGrainNumber = pESections->Space.Density*SectionVolume*0.001f;
	float CriticalMultiplier = (SectionVolume + 1800.f)/(SectionVolume + 360.f);
	int CriticalGrainNumber = (int)(AverageGrainNumber*CriticalMultiplier);
	SGrainChain * pTrack;
	CString temp;
	for(i = 1; i < NumVerSections - 1; i++)
	{
//		if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->LocalGrains,(temp.Format("%d/%d",i,NumHorSections - 1),temp));
		for(j = 1; j < NumHorSections - 1; j++)
		{
			SectionIndex = i*NumHorSections + j;
			pSection = pESections->pSections + SectionIndex;
			if(pSection->NGrains > CriticalGrainNumber)
			{
				pTrack = TrackSection2(pESections,SectionIndex,pESections->RefAxe);
				if(pTrack)m_TrackerChains.PushChain(pTrack);
			}
		}
	}	
}

void CTracker::Track41(SEmulsionSections * pESections)
{
	int i,j;
	int NumHorSections = pESections->NumHorSections;
	int NumVerSections = pESections->NumVerSections;
	int SectionIndex;
	FogAxe RefAxe = pESections->RefAxe;
	SGrainChain * pTrack;
	for(i = 1; i < NumVerSections - 1; i++)
	{
		for(j = 1; j < NumHorSections - 1; j++)
		{
			SectionIndex = i*NumHorSections + j;
			pTrack = TrackSection2(pESections,SectionIndex,RefAxe);
			if(pTrack)m_TrackerChains.PushChain(pTrack);
		}
	}	
}


SGrainChain * CTracker::TrackSection2(SEmulsionSections * pSections,int SectionIndex,FogAxe Axe)
{
	// needs grains sorted along Axe;
	int i,j;
	bool result;
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			*(mppSecs + j + 3*i) = pSections->pSections + SectionIndex + (i - 1) + (j - 1)*pSections->NumHorSections;
		}
	}
	int TotalGrains = 100;
	for(i = 0; i < 9; i++)TotalGrains += (*(mppSecs + i))->NGrains;
	if(mpFromSection == NULL)mpFromSection = new SGrainChain(TotalGrains);
	mpFromSection->FromSections(mppSecs,TotalGrains);
	mpFromSection->axe = Axe;
	result = RefineTrack2(&pSections->Space,mpFromSection);
	if(result)
	{
		SGrainChain * pChain = mpFromSection;
		mpFromSection = NULL;
		return pChain;
	}
	else
	{
//		delete pFromSection;
	}

	return NULL;
}

SGrainChain * CTracker::TrackSection4(SEmulsionSections * pSections,int SectionIndex,FogAxe Axe)
{
	// needs grains sorted along Axe;
	int i,j;
	bool result;
	SSection * pSec;
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			*(mppSecs + j + 3*i) = pSections->pSections + SectionIndex + (i - 1) + (j - 1)*pSections->NumHorSections;
		}
	}
	int TotalGrains = 100;
	for(i = 0; i < 9; i++)TotalGrains += (*(mppSecs + i))->NGrains;
	if(mpFromSection == NULL)
		mpFromSection = new SGrainChain(TotalGrains);
	for(i = 0; i < 9; i++)
	{
		pSec = *(mppSecs + i);
		for(j = 0; j < pSec->NGrains; j++)
		{
			(*(pSec->ppGrains + j));//fake 
	//		pSec->
		}
	}
	mpFromSection->axe = Axe;
	result = RefineTrack4(&pSections->Space,mpFromSection);
	if(result)
	{
		SGrainChain * pChain = mpFromSection;
		mpFromSection = NULL;
		return pChain;
	}
	else
	{
//		delete pFromSection;
	}

	return NULL;
}

bool CTracker::RefineTrack4(SEmulsionSpace * pSpace,SGrainChain * pTrack)
{
	float LengthFraction = TP.pTrackInfo->LengthFraction;
	int MinLinearDensity = TP.pTrackInfo->MinLinearDensity;
	float MinGrainNumber = TP.pTrackInfo->MinNumber;
	if(pTrack->NGrains < MinGrainNumber)return false;
	LinearFit(pTrack);
	SIntGrain ** ppGrains = pTrack->ppGrains,* pGrain;
	int &NGrains = pTrack->NGrains;
	int i,OldNGrains = NGrains + 1;
	float mx = pTrack->mx,my = pTrack->my,mz = pTrack->mz,nx = pTrack->nx,ny = pTrack->ny,nz = pTrack->nz;
//	float Factor1,Factor2,UnoSuDen = (1.f/(mx*mx + my*my + mz*mz)),distxy,distz;
	float wx,wy,wz;
//	float SqrDist1,SqrDist2,SqrDist3;
	float SqrDist3;
	float alfa = TP.pTrackInfo->Alpha,SearchFactor = TP.pTrackInfo->PipeFactor;
	float ErrorXY = TP.pTrackInfo->ErrorXY;
	float AlfaQuadro = alfa*alfa,Discriminant1 = ErrorXY*ErrorXY;
	float Discriminant = Discriminant1*SearchFactor*SearchFactor;
/*	if(Discriminant > pTrack->MaxDist)
	{
		Discriminant = pTrack->MaxDist;
		Counter1++;
	}*/
	CString text;
	float Add,wf1,nxMenox0,nzMenoz0,nyMenoy0;
	while(NGrains > MinGrainNumber - 1 && (OldNGrains > NGrains || Discriminant > Discriminant1))
	{
		OldNGrains = NGrains;
		mx = pTrack->mx; mz = pTrack->mz; my = pTrack->my; nx = pTrack->nx; ny = pTrack->ny; nz = pTrack->nz;
		for(i = 0; i < NGrains; i++)
		{
			pGrain = *(ppGrains + i);
			wx = pGrain->x; wy = pGrain->y; wz = pGrain->z;
			nxMenox0 = nx - wx; nyMenoy0 = ny - wy; nzMenoz0 = nz - wz;
//			Factor1 = -(mx*(nx-wx)+my*(ny-wy)+mz*(nz-wz));
//			Factor2 = Factor1*UnoSuDen;
//			distxy = (float)((wx - nx - mx*Factor2)*(wx - nx - mx*Factor2) + (wy - my*Factor2 - ny)*(wy - my*Factor2 - ny));
//			distz = (float)(fabs(wz - mz*Factor2 - nz));
//			SqrDist2 = distxy + distz*distz;
//			SqrDist1 = Distance(mx,nx,mz,nz,wx,wy,wz,alfa);
//			SqrDist1 *= SqrDist1;
//			SqrDist3 = SquareDistance(mx,my,mz,nx - wx,ny - wy,nz - wz,AlfaQuadro);
//			SqrDistD = SquareDistanceDouble(mx,my,mz,nx - wx,ny - wy,nz - wz,AlfaQuadro);
	//	((my*(nx-x0)+mx*(-ny+y0))²+alfa²*((mz*(nx-x0)+mx*(-nz+z0))²+(mz*(ny-y0)+my*(-nz+z0))²))/(mx²+my²+alfa²*mz²)
			wf1 = mz*nxMenox0;
			wf1 -= mx*nzMenoz0;
			Add = wf1*wf1;
			wf1 = mz*nyMenoy0;
			wf1 -= my*nzMenoz0;
			Add += wf1*wf1;
			Add *= AlfaQuadro;
			wf1 = my*nxMenox0;
			wf1 -= mx*nyMenoy0;
			Add += wf1*wf1;
			SqrDist3 =  Add/(mx*mx + my*my + AlfaQuadro*mz*mz);
//			wf1 = (SqrDist3 - (float)SqrDistD);
//			wf1 *= wf1;
			Counter2++;
//			text.Format("Difference OverFlowed : %g",wf1);
//			if(wf1 > GlobalDifference || wf1 < -GlobalDifference)Counter3++;//MessageBox(NULL,text,"Tracker",MB_OK);
			if(SqrDist3 > Discriminant)
			{
				if(NGrains == MinGrainNumber)return false;
				pTrack->PopGrain(i--);
			}
		}
		LinearFit(pTrack);
		Discriminant *= 0.9f;
		if(Discriminant < Discriminant1)Discriminant = Discriminant1;
	}
	LinearFit(pTrack,true);
	if(pTrack->GiC < MinLinearDensity)return false;
	GetNominalLength(pSpace,pTrack);
	if(pTrack->Length/pTrack->NomLength < LengthFraction)return false;
	return true;
}

bool CTracker::RefineTrack2(SEmulsionSpace * pSpace,SGrainChain * pTrack)
{
	float LengthFraction = TP.pTrackInfo->LengthFraction;
	int MinLinearDensity = TP.pTrackInfo->MinLinearDensity;
	int MinGrainNumber = TP.pTrackInfo->MinNumber;
	if(pTrack->NGrains < MinGrainNumber)return false;
	LinearFit(pTrack);
	SIntGrain ** ppGrains = pTrack->ppGrains,* pGrain;
	int &NGrains = pTrack->NGrains;
	int i,OldNGrains = NGrains + 1;
	float mx = pTrack->mx,my = pTrack->my,mz = pTrack->mz,nx = pTrack->nx,ny = pTrack->ny,nz = pTrack->nz;
//	float Factor1,Factor2,UnoSuDen = (1.f/(mx*mx + my*my + mz*mz)),distxy,distz;
	float wx,wy,wz;
//	float SqrDist1,SqrDist2,SqrDist3;
	float SqrDist3;
	float alfa = TP.pTrackInfo->Alpha,SearchFactor = TP.pTrackInfo->PipeFactor;
	float ErrorXY = TP.pTrackInfo->ErrorXY;
	float AlfaQuadro = alfa*alfa,Discriminant1 = ErrorXY*ErrorXY;
	float Discriminant = Discriminant1*SearchFactor*SearchFactor;
/*	if(Discriminant > pTrack->MaxDist)
	{
		Discriminant = pTrack->MaxDist;
		Counter1++;
	}*/
	CString text;
	float Add,wf1,nxMenox0,nzMenoz0,nyMenoy0;
	while(NGrains >= MinGrainNumber && (OldNGrains > NGrains || Discriminant > Discriminant1))
	{
		OldNGrains = NGrains;
		mx = pTrack->mx; mz = pTrack->mz; my = pTrack->my; nx = pTrack->nx; ny = pTrack->ny; nz = pTrack->nz;
		for(i = 0; i < NGrains; i++)
		{
			pGrain = *(ppGrains + i);
			wx = pGrain->x; wy = pGrain->y; wz = pGrain->z;
			nxMenox0 = nx - wx; nyMenoy0 = ny - wy; nzMenoz0 = nz - wz;
//			Factor1 = -(mx*(nx-wx)+my*(ny-wy)+mz*(nz-wz));
//			Factor2 = Factor1*UnoSuDen;
//			distxy = (float)((wx - nx - mx*Factor2)*(wx - nx - mx*Factor2) + (wy - my*Factor2 - ny)*(wy - my*Factor2 - ny));
//			distz = (float)(fabs(wz - mz*Factor2 - nz));
//			SqrDist2 = distxy + distz*distz;
//			SqrDist1 = Distance(mx,nx,mz,nz,wx,wy,wz,alfa);
//			SqrDist1 *= SqrDist1;
//			SqrDist3 = SquareDistance(mx,my,mz,nx - wx,ny - wy,nz - wz,AlfaQuadro);
//			SqrDistD = SquareDistanceDouble(mx,my,mz,nx - wx,ny - wy,nz - wz,AlfaQuadro);
	//	((my*(nx-x0)+mx*(-ny+y0))²+alfa²*((mz*(nx-x0)+mx*(-nz+z0))²+(mz*(ny-y0)+my*(-nz+z0))²))/(mx²+my²+alfa²*mz²)
			wf1 = mz*nxMenox0;
			wf1 -= mx*nzMenoz0;
			Add = wf1*wf1;
			wf1 = mz*nyMenoy0;
			wf1 -= my*nzMenoz0;
			Add += wf1*wf1;
			Add *= AlfaQuadro;
			wf1 = my*nxMenox0;
			wf1 -= mx*nyMenoy0;
			Add += wf1*wf1;
			SqrDist3 =  Add/(mx*mx + my*my + AlfaQuadro*mz*mz);
//			wf1 = (SqrDist3 - (float)SqrDistD);
//			wf1 *= wf1;
			Counter2++;
//			text.Format("Difference OverFlowed : %g",wf1);
//			if(wf1 > GlobalDifference || wf1 < -GlobalDifference)Counter3++;//MessageBox(NULL,text,"Tracker",MB_OK);
			if(SqrDist3 > Discriminant)
			{
				if(NGrains == MinGrainNumber)
					return false;
				pTrack->PopGrain(i--);
			}
		}
		LinearFit(pTrack);
		Discriminant *= 0.9f;
		if(Discriminant < Discriminant1)Discriminant = Discriminant1;
	}
	LinearFit(pTrack,true);
	if(pTrack->GiC < MinLinearDensity)return false;
	GetNominalLength(pSpace,pTrack);
	if(pTrack->Length/pTrack->NomLength < LengthFraction)return false;
	return true;
}

void CTracker::GetNominalLength(SEmulsionSpace * pSpace,SGrainChain * pChain)
{
	SZetaRange * pRange = &pSpace->ZetaRange;
	float MaxX,MinX,MaxY,MinY,MaxZ,MinZ;
	float & Length = pChain->NomLength;
	MaxX = pRange->MaxX; MinX = pRange->MinX;
	MinY = pRange->MinY; MaxY = pRange->MaxY;
	MinZ = pRange->BottomZ; MaxZ = pRange->UpperZ;
	float Ranges[10] = {pRange->MaxX,pRange->MinX,pRange->MaxY,pRange->MinY,pRange->UpperZ,pRange->BottomZ,pRange->MaxX,pRange->MinX,pRange->MaxY,pRange->MinY};
	float Denos[5] = {1.f/pChain->mx,1.f/pChain->my,1.f/pChain->mz,1.f/pChain->mx,1.f/pChain->my};
	float Coeff[5] = {pChain->mx,pChain->my,pChain->mz,pChain->mx,pChain->my};
	float Inter[5] = {pChain->nx,pChain->ny,pChain->nz,pChain->nx,pChain->ny};
	float Den,Diff;
	float worker1,worker2,worker;
	Vector v[6];
	float values[3];
	int i,imezzi,j;
	int Surfaces1 = 0,Surfaces2 = 0;
	int count = 0;
	for(i = 0; i < 6; i++)
	{
		imezzi = i/2;
		Den = *(Denos + imezzi);
		Diff = *(Ranges + i) - *(Inter + imezzi);
		worker1 = *(Inter + ++imezzi) + Den*Diff*(*(Coeff + imezzi));
		j = i - (i&1) + 2;
		if(worker1 < *(Ranges + j) && worker1 > *(Ranges + ++j))
		{
			worker2 = *(Inter + ++imezzi) + Den*Diff*(*(Coeff + imezzi));
			if(worker2 < *(Ranges + ++j) && worker2 > *(Ranges + ++j))
			{
				Surfaces1 |= (1 << i);
				*(values + 0) = *(Ranges + i);
				*(values + 1) = worker1;
				*(values + 2) = worker2;
				j = 3 - i/2;
				*(v + count++) = Vector(*(values + (j%3)),*(values + ((j+1)%3)),*(values + ((j+2)%3)));
			}
		}
	}
	if(count > 2)ASSERT(FALSE);
	count = 0;
	Den = 1.f/pChain->mx;
	Diff = MaxX - pChain->nx;
	worker = pChain->ny + pChain->my*Den*Diff;
	if(worker < MaxY && worker > MinY)
	{
		worker = pChain->nz + pChain->mz*Den*Diff;
		if(worker < MaxZ && worker > MinZ)
		{
			Surfaces2 |= 1;
			count++;
		}
	}
	Diff = MinX - pChain->nx;
	worker = pChain->ny + pChain->my*Den*Diff;
	if(worker < MaxY && worker > MinY)
	{
		worker = pChain->nz + pChain->mz*Den*Diff;
		if(worker < MaxZ && worker > MinZ)
		{
			Surfaces2 |= 2;
			count++;
		}
	}
	Den = 1.f/pChain->my;
	Diff = MaxY - pChain->ny;
	worker = pChain->nx + pChain->mx*Den*Diff;
	if(worker < MaxX && worker > MinX)
	{
		worker = pChain->nz + pChain->mz*Den*Diff;
		if(worker < MaxZ && worker > MinZ)
		{
			Surfaces2 |= 4;
			count++;
		}
	}
	Diff = MinY - pChain->ny;
	worker = pChain->nx + pChain->mx*Den*Diff;
	if(worker < MaxX && worker > MinX)
	{
		worker = pChain->nz + pChain->mz*Den*Diff;
		if(worker < MaxZ && worker > MinZ)
		{
			Surfaces2 |= 8;
			count++;
		}
	}
	Den = 1.f/pChain->mz;
	Diff = MaxZ - pChain->nz;
	worker = pChain->nx + pChain->mx*Den*Diff;
	if(worker < MaxX && worker > MinX)
	{
		worker = pChain->ny + pChain->my*Den*Diff;
		if(worker < MaxY && worker > MinY)
		{
			Surfaces2 |= 16;
			count++;
		}
	}
	Diff = MinZ - pChain->nz;
	worker = pChain->nx + pChain->mx*Den*Diff;
	if(worker < MaxX && worker > MinX)
	{
		worker = pChain->ny + pChain->my*Den*Diff;
		if(worker < MaxY && worker > MinY)
		{
			Surfaces2 |= 32;
			count++;
		}
	}
	if(Surfaces2 != Surfaces1)ASSERT(FALSE);
	if(count > 2)ASSERT(FALSE);
	Vector V = (*v - *(v + 1));
	Length = V.Module();
}

void CTracker::GetNominalLength(SEmulsionSpace * pSpace,SMip * pMip)
{
	SZetaRange * pRange = &pSpace->ZetaRange;
	float MaxX,MinX,MaxY,MinY,MaxZ,MinZ;
	MaxX = pRange->MaxX; MinX = pRange->MinX;
	MinY = pRange->MinY; MaxY = pRange->MaxY;
	MinZ = pRange->BottomZ; MaxZ = pRange->UpperZ;
	float Ranges[10] = {pRange->MaxX,pRange->MinX,pRange->MaxY,pRange->MinY,pRange->UpperZ,pRange->BottomZ,pRange->MaxX,pRange->MinX,pRange->MaxY,pRange->MinY};
	float Denos[5] = {1.f/pMip->mx,1.f/pMip->my,1.f/pMip->mz,1.f/pMip->mx,1.f/pMip->my};
	float Coeff[5] = {pMip->mx,pMip->my,pMip->mz,pMip->mx,pMip->my};
	float Inter[5] = {pMip->nx,pMip->ny,pMip->nz,pMip->nx,pMip->ny};
	float Den,Diff;
	float worker1,worker2;
	Vector v[6];
	float values[3];
	int i,imezzi,j;
	int Surfaces1 = 0,Surfaces2 = 0;
	int count = 0;
	for(i = 0; i < 6; i++)
	{
		imezzi = i/2;
		Den = *(Denos + imezzi);
		Diff = *(Ranges + i) - *(Inter + imezzi);
		worker1 = *(Inter + ++imezzi) + Den*Diff*(*(Coeff + imezzi));
		j = i - (i&1) + 2;
		if(worker1 < *(Ranges + j) && worker1 > *(Ranges + ++j))
		{
			worker2 = *(Inter + ++imezzi) + Den*Diff*(*(Coeff + imezzi));
			if(worker2 < *(Ranges + ++j) && worker2 > *(Ranges + ++j))
			{
				Surfaces1 |= (1 << i);
				*(values + 0) = *(Ranges + i);
				*(values + 1) = worker1;
				*(values + 2) = worker2;
				j = 3 - i/2;
				*(v + count++) = Vector(*(values + (j%3)),*(values + ((j+1)%3)),*(values + ((j+2)%3)));
			}
		}
	}
	if(count != 2)ASSERT(FALSE);

	Vector V = (*v - *(v + 1));
	pMip->NomLength = V.Module();
}

	