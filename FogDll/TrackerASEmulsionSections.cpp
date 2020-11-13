


SSphericals::SSphericals(float theta,float phi): Theta(theta),Phi(phi)
{
	Update(theta,phi);
}

void SSphericals::Update(float theta,float phi)
{
	Theta = theta;
	Phi = phi;
	sinTheta = (float)sin(theta);
	cosTheta = (float)cos(theta);
	sinPhi = (float)sin(phi);
	cosPhi = (float)cos(phi);
	tanTheta = sinTheta/cosTheta;
	tanPhi = sinPhi/cosPhi;
	cotTheta = cosTheta/sinTheta;
	cotPhi = cosPhi/sinPhi;
	float refPhi = Phi;// + 4*PI_FOG;
	if(refPhi < 0)refPhi += 2*PI_FOG;
	if(Theta < PI_QUARTI)RefAxe = ZAXE;
	else if((refPhi < PI_QUARTI || refPhi > 7*PI_QUARTI) || (refPhi < 5*PI_QUARTI && refPhi > 3*PI_QUARTI))RefAxe = XAXE;
	else RefAxe = YAXE;
	if(RefAxe == XAXE)
	{
		FactorX = (float)sqrt(1 + cotTheta*cotTheta + tanPhi*tanPhi);
		FactorY = 0;//(float)sqrt(1 + cotTheta*cotTheta + cotPhi*cotPhi);
		FactorZ = 0;//(float)sqrt(1 + tanTheta*tanTheta);
	}
	if(RefAxe == YAXE)
	{
		FactorX = 0;//(float)sqrt(1 + cotTheta*cotTheta + tanPhi*tanPhi);
		FactorY = (float)sqrt(1 + cotTheta*cotTheta + cotPhi*cotPhi);
		FactorZ = 0;//(float)sqrt(1 + tanTheta*tanTheta);
	}
	if(RefAxe == ZAXE)
	{
		FactorX = 0;//(float)sqrt(1 + cotTheta*cotTheta + tanPhi*tanPhi);
		FactorY = 0;//(float)sqrt(1 + cotTheta*cotTheta + cotPhi*cotPhi);
		FactorZ = (float)sqrt(1 + tanTheta*tanTheta);
	}
}


SEmulsionSections::SEmulsionSections(STracker * TC,SEmulsionSpace * pSpace,float Theta,float Phi,float CellXY,float CellZ):Space(*pSpace),
Sphericals(Theta,Phi),RefAxe(Sphericals.RefAxe),pTService(TC)
{
	AllocatedSections = 300000;
	ppGrains = (SIntGrain **)malloc(sizeof(SIntGrain *)*Space.NumGrains);
	if(ppGrains == NULL)MessageBox(TC->pContext->m_hWnd,"Error 1 in Constructor!\nCrashing!","SEmulsionSections",MB_OK);
	pSections = (SSection *)malloc(sizeof(SSection)*AllocatedSections);
	if(pSections == NULL)MessageBox(pTService->pContext->m_hWnd,"Error 2 in Constructor!\nCrashing!","SEmulsionSections",MB_OK);
	pIncrements = (int *)malloc(sizeof(int)*AllocatedSections);
	if(pIncrements == NULL)MessageBox(pTService->pContext->m_hWnd,"Error 3 in Constructor!\nCrashing!","SEmulsionSections",MB_OK);
	pIndexes = (int *)malloc(sizeof(int *)*Space.NumGrains);
	if(pIndexes == NULL)MessageBox(pTService->pContext->m_hWnd,"Error4 in Constructor!\nCrashing!","SEmulsionSections",MB_OK);

	ppGrainsZ = ppGrains;
	int i;
	for(i = 0; i < Space.NumGrains; i++)
	{
		*(ppGrainsZ + i) = Space.pGrains + i;
	}
	qsort(ppGrainsZ,Space.NumGrains,sizeof(SIntGrain *),CompareIntGrainPointerZD);
	ppGrainsX = NULL;
	ppGrainsY = NULL;
	pNewCoordinates = NULL;
	SZetaRange * pRange = &Space.ZetaRange;
	CenterZ = (pRange->DeadZoneUp + pRange->DeadZoneDw)/2.f;
	HalfFieldX = pRange->MaxX + 2*CellXY;
	HalfFieldY = pRange->MaxY + 2*CellXY;
	HalfFieldZ = (pRange->UpperZ - pRange->BottomZ + 8.f)/2.f;
	BottomZ = pRange->BottomZ - 4.f;
	UpperZ = pRange->UpperZ + 4.f;
}

bool SEmulsionSections::Create2(float Theta,float Phi,float dTh,float dPh)
{
	Sphericals.Update(Theta,Phi);
	int i;
	if(RefAxe == XAXE && ppGrainsX == NULL)
	{
		ppGrainsX = (SIntGrain **)calloc(sizeof(SIntGrain *),Space.NumGrains);
		if(ppGrainsX == NULL)
		{
			MessageBox(NULL,"Memory Error","SEmulsionSection",MB_OK);
			return false;
		}
		memcpy(ppGrainsX,ppGrainsZ,sizeof(SIntGrain *)*Space.NumGrains);
		qsort(ppGrainsX,Space.NumGrains,sizeof(SIntGrain *),CompareIntGrainPointerXD);
	}
	if(RefAxe == YAXE && ppGrainsY == NULL)
	{
		ppGrainsY = (SIntGrain **)calloc(sizeof(SIntGrain *),Space.NumGrains);
		if(ppGrainsY == NULL)
		{
			MessageBox(NULL,"Memory Error","SEmulsionSection",MB_OK);
			return false;
		}
		memcpy(ppGrainsY,ppGrainsZ,sizeof(SIntGrain *)*Space.NumGrains);
		qsort(ppGrainsY,Space.NumGrains,sizeof(SIntGrain *),CompareIntGrainPointerYD);
	}
	SIntGrain * pGrains = Space.pGrains,*pGrain;
	int Ander = 0,NumGrains = Space.NumGrains;
	// Vector VersorZ((float)(sinTheta*cosPhi),(float)(sinTheta*sinPhi),(float)cosTheta);
	float worker = Sphericals.sinTheta*Sphericals.sinTheta;
	CellXY = 2.f;
	float UnoSuSectX = ((float)sqrt(1 - worker*Sphericals.cosPhi*Sphericals.cosPhi))/CellXY;
	float UnoSuSectY = ((float)sqrt(1 - worker*Sphericals.sinPhi*Sphericals.sinPhi))/CellXY;
	float UnoSuSectZ = 0.f;//(float)fabs(Sphericals.sinTheta/cellZ);
	float HalfRangeX,HalfRangeY,HalfRangeZ;
	float CoordX,CoordZ,CoordY,z,y,x;
	int index,indexx,indexy,indexz;
	FogAxe refaxe = RefAxe;// RefAxe -> alias of Sphericals.RefAxe;
	if(RefAxe == XAXE)
	{
		float AbsTanPhi,AbsCotThetaSecPhi;
		AbsCotThetaSecPhi = (float)fabs(Sphericals.cotTheta/Sphericals.cosPhi);
		AbsTanPhi = (float)fabs(Sphericals.tanPhi);
		HalfRangeY = HalfFieldY + HalfFieldX*AbsTanPhi;
		HalfRangeZ = HalfFieldZ + HalfFieldX*AbsCotThetaSecPhi;
		NumHorSections = (int)(2*HalfRangeY*UnoSuSectY + 1.f);
		NumVerSections = (int)(2*HalfRangeZ*UnoSuSectZ + 1.f);
	}
	else if(RefAxe == YAXE)
	{
		float AbsCotPhi,AbsCotThetaCosecPhi;
		AbsCotThetaCosecPhi = (float)fabs(Sphericals.cotTheta/Sphericals.sinPhi);
		AbsCotPhi = (float)fabs(Sphericals.cotPhi);
		HalfRangeX = HalfFieldX + HalfFieldY*AbsCotPhi;
		HalfRangeZ = HalfFieldZ + HalfFieldY*AbsCotThetaCosecPhi;
		NumHorSections = (int)(2*HalfRangeX*UnoSuSectX + 1.f);
		NumVerSections = (int)(2*HalfRangeZ*UnoSuSectZ + 1.f);
	}
	else if(RefAxe == ZAXE)
	{
		float AbsTanThetaSinPhi,AbsTanThetaCosPhi;
		AbsTanThetaCosPhi = (float)fabs(Sphericals.tanTheta*Sphericals.cosPhi);
		AbsTanThetaSinPhi = (float)fabs(Sphericals.tanTheta*Sphericals.sinPhi);
		HalfRangeX = HalfFieldX + HalfFieldZ*AbsTanThetaCosPhi;
		HalfRangeY = HalfFieldY + HalfFieldZ*AbsTanThetaSinPhi;
		HalfRangeZ = HalfFieldZ;//Not really needed
		NumHorSections = (int)(2*HalfRangeX*UnoSuSectX + 1.f);
		NumVerSections = (int)(2*HalfRangeY*UnoSuSectY + 1.f);
	}
	UsedSections = NumVerSections*NumHorSections;
	if(UsedSections > AllocatedSections)return false;
	memset(pSections,0,sizeof(SSection)*UsedSections);
	if(RefAxe == XAXE)
	{
	// T = (X - X0)/(sinTheta*cosPhi);
	// {Y0 + ((X - X0)/(sinTheta*cosPhi))*sinTheta*sinPhi,Z0 + ((X - X0)/(sinTheta*cosPhi))*cosTheta}
	//Intersezione del piano x=0 con la retta passante per {x0,y0,z0} parallela al vettore versorz;
	// {Y0 - X0*tanPhi,Z0 - X0*cotTheta/cosPhi} // XAXE
		float CenterZPiuHalfRangeZ = CenterZ + HalfRangeZ;
		float tanPhi = Sphericals.tanPhi;
		float cotThetaSecPhi = Sphericals.cotTheta/Sphericals.cosPhi;
		for(i = 0; i < NumGrains; i++)
		{
			pGrain = pGrains + i;
			z = pGrain->z;
			if(z < BottomZ || z > UpperZ){*(pIndexes + i) = UsedSections;continue;}
			x = pGrain->x;
			CoordZ = z - x*cotThetaSecPhi;
			CoordY = pGrain->y - x*tanPhi;
			indexy = (int)((CoordY + HalfRangeY)*UnoSuSectY);
			indexz = (int)((CenterZPiuHalfRangeZ - CoordZ)*UnoSuSectZ);
			index = indexy + indexz*NumHorSections;
			*(pIndexes + i) = index;
			(pSections + index)->NGrains++;
		}
	}
	else if(RefAxe == YAXE)
	{
	// {X0 + T sinTheta*cosPhi,Y0 + T sinTheta*sinPhi,Z0 + T cosTheta}
	// T = (Y - Y0)/(sinTheta*sinPhi);
	// {X0 + (Y - Y0)/(sinTheta*sinPhi))*sinTheta*cosPhi,Z0 + ((Y - Y0)/(sinTheta*sinPhi))*cosTheta}
	//Intersezione del piano y=0 con la retta passante per {x0,y0,z0} parallela al vettore versorz;
	// {X0 - Y0*(cosPhi/sinPhi),Z0 - Y0*(cosTheta/(sinTheta*sinPhi))} // YAXE
		float CenterZPiuHalfRangeZ = CenterZ + HalfRangeZ;
		float cotThetaCosecPhi = Sphericals.cotTheta/Sphericals.sinPhi;
		float cotPhi = Sphericals.cotPhi;
		for(i = 0; i < NumGrains; i++)
		{
			pGrain = pGrains + i;
			z = pGrain->z;
			if(z < BottomZ || z > UpperZ){*(pIndexes + i) = UsedSections;continue;}
			y = pGrain->y;
			CoordZ = z - y*cotThetaCosecPhi;
			CoordX = pGrain->x - y*cotPhi;
			indexx = (int)((CoordX + HalfRangeX)*UnoSuSectX);
			indexz = (int)((CenterZPiuHalfRangeZ - CoordZ)*UnoSuSectZ);
			index = indexx + indexz*NumHorSections;
			*(pIndexes + i) = index;
			(pSections + index)->NGrains++;
		}
	}
	else if(RefAxe == ZAXE)
	{
	// T = (Z - Z0)/cosTheta;
	// {X0 + ((Z - Z0)/cosTheta)*sinTheta*cosPhi,Y0 + ((Z - Z0)/cosTheta)*sinTheta*sinPhi}
	//Intersezione del piano z = Z0 (Z0 = CenterZ) con la retta passante per {x0,y0,z0} parallela al vettore versorz;
	// {X0 + (Z - Z0)*tanTheta*cosPhi,Y0 + (Z - Z0)*tanTheta*sinPhi} // ZAXE
//		float CenterZPiuHalfRangeZ = CenterZ + HalfRangeZ;
		float tanThetaCosPhi = Sphericals.tanTheta*Sphericals.cosPhi;
		float tanThetaSinPhi = Sphericals.tanTheta*Sphericals.sinPhi;
		for(i = 0; i < NumGrains; i++)
		{
			pGrain = *(ppGrainsZ + i);
			z = pGrain->z;
			if(z < BottomZ -4.f || z > UpperZ + 4.f)
			{
				*(pIndexes + i) = UsedSections;
				continue;
			}
			z -= CenterZ;
			CoordX = pGrain->x - z*tanThetaCosPhi;
			CoordY = pGrain->y - z*tanThetaSinPhi;
			indexx = (int)((CoordX + HalfRangeX)*UnoSuSectX);
			indexy = (int)((CoordY + HalfRangeY)*UnoSuSectY);
			index = indexx + indexy*NumHorSections;
			*(pIndexes + i) = index;
			(pSections + index)->NGrains++;
		}
	}
	for(i = 0; i < UsedSections; )
	{
		Ander += (pSections + i)->NGrains;
		(pSections + i)->ppGrains = ppGrains + *(pIncrements + i);
		*(pIncrements + ++i) = Ander;
	}
	for(i = 0; i < NumGrains; i++)
	{
		*(ppGrains + (*(pIncrements + *(pIndexes + i)))++) = pGrains + i;
	}
	if(true)
	{
		SZetaRange * pRange = &Space.ZetaRange;
		float MaxX,MinX,MaxY,MinY,MaxZ,MinZ;
		float sectx = 1.f/UnoSuSectX,secty = 1.f/UnoSuSectY,sectz = 1.f/UnoSuSectZ;
		MaxX = pRange->MaxX; MinX = pRange->MinX;
		MinY = pRange->MinY; MaxY = pRange->MaxY;
		MinZ = pRange->BottomZ; MaxZ = pRange->UpperZ;
		float nx,ny,nz,mx,my,mz;
		if(RefAxe == XAXE){mx = 1;my = Sphericals.tanPhi; mz = Sphericals.cotTheta/Sphericals.cosPhi; nx = 0;}
		if(RefAxe == YAXE){mx = Sphericals.cotPhi; my = 1; mz = Sphericals.cotTheta/Sphericals.sinPhi;ny = 0;}
		if(RefAxe == ZAXE){mx = Sphericals.tanTheta*Sphericals.cosPhi; my = Sphericals.tanTheta*Sphericals.sinPhi; mz = 1;nz = CenterZ;}
		float DenX = 1.f/mx,DenY = 1.f/my,DenZ = 1.f/mz;
		float CenterZPiuHalfRangeZ = CenterZ + HalfRangeZ;
		float Diff;
		Vector v[2];
		int j,count,count2 = 0;
		for(i = 0; i < NumVerSections; i++)
		{
			if(RefAxe == ZAXE){ny =	secty*i - HalfRangeY;}
			else {nz = CenterZPiuHalfRangeZ - sectz*i;}
/*			if(RefAxe == XAXE){nz = CenterZPiuHalfRangeZ - sectz*i;}
			if(RefAxe == YAXE){nz = CenterZPiuHalfRangeZ - sectz*i;}*/
			for(j = 0; j < NumHorSections; j++)
			{
				if(RefAxe == XAXE){ny = secty*j - HalfRangeY;}
				else {nx = sectx*j - HalfRangeX;}
			/*	if(RefAxe == YAXE){nx = sectx*j - HalfRangeX;}
				if(RefAxe == ZAXE){nx = sectx*j - HalfRangeX;}*/
				count = 0;
				Diff = MaxX - nx;
				worker = ny + my*DenX*Diff;
				if(worker < MaxY && worker > MinY)
				{
					worker = nz + mz*DenX*Diff;
					if(worker < MaxZ && worker > MinZ)
					{
						v[count].x = MaxX;
						v[count].y = ny + my*DenX*Diff;
						v[count].z = worker;
						count++;
					}
				}
				Diff = MinX - nx;
				worker = ny + my*DenX*Diff;
				if(worker < MaxY && worker > MinY)
				{
					worker = nz + mz*DenX*Diff;
					if(worker < MaxZ && worker > MinZ)
					{
						v[count].x = MinX;
						v[count].y = ny + my*DenX*Diff;
						v[count].z = worker;
						count++;
					}
				}
				if(count < 2)
				{
					Diff = MaxY - ny;
					worker = nx + mx*DenY*Diff;
					if(worker < MaxX && worker > MinX)
					{
						worker = nz + mz*DenY*Diff;
						if(worker < MaxZ && worker > MinZ)
						{
							v[count].x = nx + mx*DenY*Diff;
							v[count].y = MaxY;
							v[count].z = worker;
							count++;
						}
					}
					if(count < 2)
					{
						Diff = MinY - ny;
						worker = nx + mx*DenY*Diff;
						if(worker < MaxX && worker > MinX)
						{
							worker = nz + mz*DenY*Diff;
							if(worker < MaxZ && worker > MinZ)
							{
								v[count].x = nx + mx*DenY*Diff;
								v[count].y = MinY;
								v[count].z = worker;
								count++;
							}
						}
						if(count < 2)
						{
							Diff = MaxZ - nz;
							worker = nx + mx*DenZ*Diff;
							if(worker < MaxX && worker > MinX)
							{
								worker = ny + my*DenZ*Diff;
								if(worker < MaxY && worker > MinY)
								{
									v[count].x = nx + mx*DenZ*Diff;
									v[count].y = worker;
									v[count].z = MaxZ;
									count++;
								}
							}
							if(count < 2)
							{
								Diff = MinZ - nz;
								worker = nx + mx*DenZ*Diff;
								if(worker < MaxX && worker > MinX)
								{
									worker = ny + my*DenZ*Diff;
									if(worker < MaxY && worker > MinY)
									{
										v[count].x = nx + mx*DenZ*Diff;
										v[count].y = worker;
										v[count].z = MinZ;
										count++;
									}
								}
							}
						}
					}
				}
				float &Length = (pSections + j + NumHorSections*i)->Length;
				if(count < 2)Length = 0;
				else if(count > 2)ASSERT(FALSE);
				else if(count == 2)
				{
					if(RefAxe == XAXE){Length = (v[0].x - v[1].x)*Sphericals.FactorX;}
					if(RefAxe == YAXE){Length = (v[0].y - v[1].y)*Sphericals.FactorY;}
					if(RefAxe == ZAXE){Length = (v[0].z - v[1].z)*Sphericals.FactorZ;}
				}
			}
		}
	}
	else
	{
		SZetaRange * pRange = &Space.ZetaRange;
		float MaxX,MinX,MaxY,MinY,MaxZ,MinZ;
		float sectx = 1.f/UnoSuSectX,secty = 1.f/UnoSuSectY,sectz = 1.f/UnoSuSectZ;
		MaxX = pRange->MaxX; MinX = pRange->MinX;
		MinY = pRange->MinY; MaxY = pRange->MaxY;
		MinZ = pRange->BottomZ; MaxZ = pRange->UpperZ;
		float nx,ny,nz,mx,my,mz;
		if(RefAxe == XAXE){mx = 1;my = Sphericals.tanPhi; mz = Sphericals.cotTheta/Sphericals.cosPhi; nx = 0;}
		if(RefAxe == YAXE){mx = Sphericals.cotPhi; my = 1; mz = Sphericals.cotTheta/Sphericals.sinPhi;ny = 0;}
		if(RefAxe == ZAXE){mx = Sphericals.tanTheta*Sphericals.cosPhi; my = Sphericals.tanTheta*Sphericals.sinPhi; mz = 1;nz = CenterZ;}
		float DenX = 1.f/mx,DenY = 1.f/my,DenZ = 1.f/mz;
		float CenterZPiuHalfRangeZ = CenterZ + HalfRangeZ;
		float Diff;
		Vector v[2];
		int j,count,count2 = 0;
		int Center = (NumVerSections/2)*(NumHorSections) + NumHorSections/2;
		for(i = NumVerSections/2; i < NumVerSections/2 + 1; i++)
		{
			if(RefAxe == ZAXE){ny =	secty*i - HalfRangeY;}
			else {nz = CenterZPiuHalfRangeZ - sectz*i;}
/*			if(RefAxe == XAXE){nz = CenterZPiuHalfRangeZ - sectz*i;}
			if(RefAxe == YAXE){nz = CenterZPiuHalfRangeZ - sectz*i;}*/
			for(j = NumHorSections/2; j < NumHorSections/2 + 1; j++)
			{
				if(RefAxe == XAXE){ny = secty*j - HalfRangeY;}
				else {nx = sectx*j - HalfRangeX;}
			/*	if(RefAxe == YAXE){nx = sectx*j - HalfRangeX;}
				if(RefAxe == ZAXE){nx = sectx*j - HalfRangeX;}*/
				count = 0;
				Diff = MaxX - nx;
				worker = ny + my*DenX*Diff;
				if(worker < MaxY && worker > MinY)
				{
					worker = nz + mz*DenX*Diff;
					if(worker < MaxZ && worker > MinZ)
					{
						v[count].x = MaxX;
						v[count].y = ny + my*DenX*Diff;
						v[count].z = worker;
						count++;
					}
				}
				Diff = MinX - nx;
				worker = ny + my*DenX*Diff;
				if(worker < MaxY && worker > MinY)
				{
					worker = nz + mz*DenX*Diff;
					if(worker < MaxZ && worker > MinZ)
					{
						v[count].x = MinX;
						v[count].y = ny + my*DenX*Diff;
						v[count].z = worker;
						count++;
					}
				}
				if(count < 2)
				{
					Diff = MaxY - ny;
					worker = nx + mx*DenY*Diff;
					if(worker < MaxX && worker > MinX)
					{
						worker = nz + mz*DenY*Diff;
						if(worker < MaxZ && worker > MinZ)
						{
							v[count].x = nx + mx*DenY*Diff;
							v[count].y = MaxY;
							v[count].z = worker;
							count++;
						}
					}
					if(count < 2)
					{
						Diff = MinY - ny;
						worker = nx + mx*DenY*Diff;
						if(worker < MaxX && worker > MinX)
						{
							worker = nz + mz*DenY*Diff;
							if(worker < MaxZ && worker > MinZ)
							{
								v[count].x = nx + mx*DenY*Diff;
								v[count].y = MinY;
								v[count].z = worker;
								count++;
							}
						}
						if(count < 2)
						{
							Diff = MaxZ - nz;
							worker = nx + mx*DenZ*Diff;
							if(worker < MaxX && worker > MinX)
							{
								worker = ny + my*DenZ*Diff;
								if(worker < MaxY && worker > MinY)
								{
									v[count].x = nx + mx*DenZ*Diff;
									v[count].y = worker;
									v[count].z = MaxZ;
									count++;
								}
							}
							if(count < 2)
							{
								Diff = MinZ - nz;
								worker = nx + mx*DenZ*Diff;
								if(worker < MaxX && worker > MinX)
								{
									worker = ny + my*DenZ*Diff;
									if(worker < MaxY && worker > MinY)
									{
										v[count].x = nx + mx*DenZ*Diff;
										v[count].y = worker;
										v[count].z = MinZ;
										count++;
									}
								}
							}
						}
					}
				}
				float &Length = (pSections + j + NumHorSections*i)->Length;
				if(count < 2)Length = 0;
				else if(count > 2)ASSERT(FALSE);
				else if(count == 2)
				{
					if(RefAxe == XAXE){Length = (v[0].x - v[1].x)*Sphericals.FactorX;}
					if(RefAxe == YAXE){Length = (v[0].y - v[1].y)*Sphericals.FactorY;}
					if(RefAxe == ZAXE){Length = (v[0].z - v[1].z)*Sphericals.FactorZ;}
				}
			}
		}
	}
	return true;
}

bool SEmulsionSections::Create(float Theta,float Phi,float cellXY,float cellZ)
{
	Sphericals.Update(Theta,Phi);
	CellXY =  cellXY; CellZ = cellZ;
	SIntGrain * pGrains = Space.pGrains,*pGrain;
	int i,Ander = 0,NumGrains = Space.NumGrains;
	// Vector VersorZ((float)(sinTheta*cosPhi),(float)(sinTheta*sinPhi),(float)cosTheta);
	float worker = Sphericals.sinTheta*Sphericals.sinTheta;
	float UnoSuSectX = ((float)sqrt(1 - worker*Sphericals.cosPhi*Sphericals.cosPhi))/CellXY;
	float UnoSuSectY = ((float)sqrt(1 - worker*Sphericals.sinPhi*Sphericals.sinPhi))/CellXY;
	float UnoSuSectZ = (float)fabs(Sphericals.sinTheta/cellZ);
	float HalfRangeX,HalfRangeY,HalfRangeZ;
	float CoordX,CoordZ,CoordY,z,y,x;
	int index,indexx,indexy,indexz;
	FogAxe refaxe = RefAxe;
	if(RefAxe == XAXE)
	{
		float AbsTanPhi,AbsCotThetaSecPhi;
		AbsCotThetaSecPhi = (float)fabs(Sphericals.cotTheta/Sphericals.cosPhi);
		AbsTanPhi = (float)fabs(Sphericals.tanPhi);
		HalfRangeY = HalfFieldY + HalfFieldX*AbsTanPhi;
		HalfRangeZ = HalfFieldZ + HalfFieldX*AbsCotThetaSecPhi;
		NumHorSections = (int)(2*HalfRangeY*UnoSuSectY + 1.f);
		NumVerSections = (int)(2*HalfRangeZ*UnoSuSectZ + 1.f);
	}
	else if(RefAxe == YAXE)
	{
		float AbsCotPhi,AbsCotThetaCosecPhi;
		AbsCotThetaCosecPhi = (float)fabs(Sphericals.cotTheta/Sphericals.sinPhi);
		AbsCotPhi = (float)fabs(Sphericals.cotPhi);
		HalfRangeX = HalfFieldX + HalfFieldY*AbsCotPhi;
		HalfRangeZ = HalfFieldZ + HalfFieldY*AbsCotThetaCosecPhi;
		NumHorSections = (int)(2*HalfRangeX*UnoSuSectX + 1.f);
		NumVerSections = (int)(2*HalfRangeZ*UnoSuSectZ + 1.f);
	}
	else if(RefAxe == ZAXE)
	{
		float AbsTanThetaSinPhi,AbsTanThetaCosPhi;
		AbsTanThetaCosPhi = (float)fabs(Sphericals.tanTheta*Sphericals.cosPhi);
		AbsTanThetaSinPhi = (float)fabs(Sphericals.tanTheta*Sphericals.sinPhi);
		HalfRangeX = HalfFieldX + HalfFieldZ*AbsTanThetaCosPhi;
		HalfRangeY = HalfFieldY + HalfFieldZ*AbsTanThetaSinPhi;
		HalfRangeZ = HalfFieldZ;//Not really needed
		NumHorSections = (int)(2*HalfRangeX*UnoSuSectX + 1.f);
		NumVerSections = (int)(2*HalfRangeY*UnoSuSectY + 1.f);
	}
	UsedSections = NumVerSections*NumHorSections;
	if(UsedSections > AllocatedSections)return false;
	memset(pSections,0,sizeof(SSection)*UsedSections);
	if(RefAxe == XAXE)
	{
	// T = (X - X0)/(sinTheta*cosPhi);
	// {Y0 + ((X - X0)/(sinTheta*cosPhi))*sinTheta*sinPhi,Z0 + ((X - X0)/(sinTheta*cosPhi))*cosTheta}
	//Intersezione del piano x=0 con la retta passante per {x0,y0,z0} parallela al vettore versorz;
	// {Y0 - X0*tanPhi,Z0 - X0*cotTheta/cosPhi} // XAXE
		float CenterZPiuHalfRangeZ = CenterZ + HalfRangeZ;
		float tanPhi = Sphericals.tanPhi;
		float cotThetaSecPhi = Sphericals.cotTheta/Sphericals.cosPhi;
		for(i = 0; i < NumGrains; i++)
		{
			pGrain = pGrains + i;
			z = pGrain->z;
			if(z < BottomZ || z > UpperZ){*(pIndexes + i) = UsedSections;continue;}
			x = pGrain->x;
			CoordZ = z - x*cotThetaSecPhi;
			CoordY = pGrain->y - x*tanPhi;
			indexy = (int)((CoordY + HalfRangeY)*UnoSuSectY);
			indexz = (int)((CenterZPiuHalfRangeZ - CoordZ)*UnoSuSectZ);
			index = indexy + indexz*NumHorSections;
			*(pIndexes + i) = index;
			(pSections + index)->NGrains++;
		}
	}
	else if(RefAxe == YAXE)
	{
	// {X0 + T sinTheta*cosPhi,Y0 + T sinTheta*sinPhi,Z0 + T cosTheta}
	// T = (Y - Y0)/(sinTheta*sinPhi);
	// {X0 + (Y - Y0)/(sinTheta*sinPhi))*sinTheta*cosPhi,Z0 + ((Y - Y0)/(sinTheta*sinPhi))*cosTheta}
	//Intersezione del piano y=0 con la retta passante per {x0,y0,z0} parallela al vettore versorz;
	// {X0 - Y0*(cosPhi/sinPhi),Z0 - Y0*(cosTheta/(sinTheta*sinPhi))} // YAXE
		float CenterZPiuHalfRangeZ = CenterZ + HalfRangeZ;
		float cotThetaCosecPhi = Sphericals.cotTheta/Sphericals.sinPhi;
		float cotPhi = Sphericals.cotPhi;
		for(i = 0; i < NumGrains; i++)
		{
			pGrain = pGrains + i;
			z = pGrain->z;
			if(z < BottomZ || z > UpperZ){*(pIndexes + i) = UsedSections;continue;}
			y = pGrain->y;
			CoordZ = z - y*cotThetaCosecPhi;
			CoordX = pGrain->x - y*cotPhi;
			indexx = (int)((CoordX + HalfRangeX)*UnoSuSectX);
			indexz = (int)((CenterZPiuHalfRangeZ - CoordZ)*UnoSuSectZ);
			index = indexx + indexz*NumHorSections;
			*(pIndexes + i) = index;
			(pSections + index)->NGrains++;
		}
	}
	else if(RefAxe == ZAXE)
	{
	// T = (Z - Z0)/cosTheta;
	// {X0 + ((Z - Z0)/cosTheta)*sinTheta*cosPhi,Y0 + ((Z - Z0)/cosTheta)*sinTheta*sinPhi}
	//Intersezione del piano z = Z0 (Z0 = CenterZ) con la retta passante per {x0,y0,z0} parallela al vettore versorz;
	// {X0 + (Z - Z0)*tanTheta*cosPhi,Y0 + (Z - Z0)*tanTheta*sinPhi} // ZAXE
//		float CenterZPiuHalfRangeZ = CenterZ + HalfRangeZ;
		float tanThetaCosPhi = Sphericals.tanTheta*Sphericals.cosPhi;
		float tanThetaSinPhi = Sphericals.tanTheta*Sphericals.sinPhi;
		for(i = 0; i < NumGrains; i++)
		{
			pGrain = pGrains + i;
			z = pGrain->z;
			if(z < BottomZ -4.f || z > UpperZ + 4.f){*(pIndexes + i) = UsedSections;continue;}
			z -= CenterZ;
			CoordX = pGrain->x - z*tanThetaCosPhi;
			CoordY = pGrain->y - z*tanThetaSinPhi;
			indexx = (int)((CoordX + HalfRangeX)*UnoSuSectX);
			indexy = (int)((CoordY + HalfRangeY)*UnoSuSectY);
			index = indexx + indexy*NumHorSections;
			*(pIndexes + i) = index;
			(pSections + index)->NGrains++;
		}
	}
	for(i = 0; i < UsedSections; )
	{
		Ander += (pSections + i)->NGrains;
		(pSections + i)->ppGrains = ppGrains + *(pIncrements + i);
		*(pIncrements + ++i) = Ander;
	}
	for(i = 0; i < NumGrains; i++)
	{
		*(ppGrains + (*(pIncrements + *(pIndexes + i)))++) = pGrains + i;
	}
	if(true)
	{
		SZetaRange * pRange = &Space.ZetaRange;
		float MaxX,MinX,MaxY,MinY,MaxZ,MinZ;
		float sectx = 1.f/UnoSuSectX,secty = 1.f/UnoSuSectY,sectz = 1.f/UnoSuSectZ;
		MaxX = pRange->MaxX; MinX = pRange->MinX;
		MinY = pRange->MinY; MaxY = pRange->MaxY;
		MinZ = pRange->BottomZ; MaxZ = pRange->UpperZ;
		float nx,ny,nz,mx,my,mz;
		if(RefAxe == XAXE){mx = 1;my = Sphericals.tanPhi; mz = Sphericals.cotTheta/Sphericals.cosPhi; nx = 0;}
		if(RefAxe == YAXE){mx = Sphericals.cotPhi; my = 1; mz = Sphericals.cotTheta/Sphericals.sinPhi;ny = 0;}
		if(RefAxe == ZAXE){mx = Sphericals.tanTheta*Sphericals.cosPhi; my = Sphericals.tanTheta*Sphericals.sinPhi; mz = 1;nz = CenterZ;}
		float DenX = 1.f/mx,DenY = 1.f/my,DenZ = 1.f/mz;
		float CenterZPiuHalfRangeZ = CenterZ + HalfRangeZ;
		float Diff;
		Vector v[2];
		int j,count,count2 = 0;
		for(i = 0; i < NumVerSections; i++)
		{
			if(RefAxe == ZAXE){ny =	secty*i - HalfRangeY;}
			else {nz = CenterZPiuHalfRangeZ - sectz*i;}
/*			if(RefAxe == XAXE){nz = CenterZPiuHalfRangeZ - sectz*i;}
			if(RefAxe == YAXE){nz = CenterZPiuHalfRangeZ - sectz*i;}*/
			for(j = 0; j < NumHorSections; j++)
			{
				if(RefAxe == XAXE){ny = secty*j - HalfRangeY;}
				else {nx = sectx*j - HalfRangeX;}
			/*	if(RefAxe == YAXE){nx = sectx*j - HalfRangeX;}
				if(RefAxe == ZAXE){nx = sectx*j - HalfRangeX;}*/
				count = 0;
				Diff = MaxX - nx;
				worker = ny + my*DenX*Diff;
				if(worker < MaxY && worker > MinY)
				{
					worker = nz + mz*DenX*Diff;
					if(worker < MaxZ && worker > MinZ)
					{
						v[count].x = MaxX;
						v[count].y = ny + my*DenX*Diff;
						v[count].z = worker;
						count++;
					}
				}
				Diff = MinX - nx;
				worker = ny + my*DenX*Diff;
				if(worker < MaxY && worker > MinY)
				{
					worker = nz + mz*DenX*Diff;
					if(worker < MaxZ && worker > MinZ)
					{
						v[count].x = MinX;
						v[count].y = ny + my*DenX*Diff;
						v[count].z = worker;
						count++;
					}
				}
				if(count < 2)
				{
					Diff = MaxY - ny;
					worker = nx + mx*DenY*Diff;
					if(worker < MaxX && worker > MinX)
					{
						worker = nz + mz*DenY*Diff;
						if(worker < MaxZ && worker > MinZ)
						{
							v[count].x = nx + mx*DenY*Diff;
							v[count].y = MaxY;
							v[count].z = worker;
							count++;
						}
					}
					if(count < 2)
					{
						Diff = MinY - ny;
						worker = nx + mx*DenY*Diff;
						if(worker < MaxX && worker > MinX)
						{
							worker = nz + mz*DenY*Diff;
							if(worker < MaxZ && worker > MinZ)
							{
								v[count].x = nx + mx*DenY*Diff;
								v[count].y = MinY;
								v[count].z = worker;
								count++;
							}
						}
						if(count < 2)
						{
							Diff = MaxZ - nz;
							worker = nx + mx*DenZ*Diff;
							if(worker < MaxX && worker > MinX)
							{
								worker = ny + my*DenZ*Diff;
								if(worker < MaxY && worker > MinY)
								{
									v[count].x = nx + mx*DenZ*Diff;
									v[count].y = worker;
									v[count].z = MaxZ;
									count++;
								}
							}
							if(count < 2)
							{
								Diff = MinZ - nz;
								worker = nx + mx*DenZ*Diff;
								if(worker < MaxX && worker > MinX)
								{
									worker = ny + my*DenZ*Diff;
									if(worker < MaxY && worker > MinY)
									{
										v[count].x = nx + mx*DenZ*Diff;
										v[count].y = worker;
										v[count].z = MinZ;
										count++;
									}
								}
							}
						}
					}
				}
				float &Length = (pSections + j + NumHorSections*i)->Length;
				if(count < 2)Length = 0;
				else if(count > 2)ASSERT(FALSE);
				else if(count == 2)
				{
					if(RefAxe == XAXE){Length = (v[0].x - v[1].x)*Sphericals.FactorX;}
					if(RefAxe == YAXE){Length = (v[0].y - v[1].y)*Sphericals.FactorY;}
					if(RefAxe == ZAXE){Length = (v[0].z - v[1].z)*Sphericals.FactorZ;}
				}
			}
		}
	}
	else
	{
		SZetaRange * pRange = &Space.ZetaRange;
		float MaxX,MinX,MaxY,MinY,MaxZ,MinZ;
		float sectx = 1.f/UnoSuSectX,secty = 1.f/UnoSuSectY,sectz = 1.f/UnoSuSectZ;
		MaxX = pRange->MaxX; MinX = pRange->MinX;
		MinY = pRange->MinY; MaxY = pRange->MaxY;
		MinZ = pRange->BottomZ; MaxZ = pRange->UpperZ;
		float nx,ny,nz,mx,my,mz;
		if(RefAxe == XAXE){mx = 1;my = Sphericals.tanPhi; mz = Sphericals.cotTheta/Sphericals.cosPhi; nx = 0;}
		if(RefAxe == YAXE){mx = Sphericals.cotPhi; my = 1; mz = Sphericals.cotTheta/Sphericals.sinPhi;ny = 0;}
		if(RefAxe == ZAXE){mx = Sphericals.tanTheta*Sphericals.cosPhi; my = Sphericals.tanTheta*Sphericals.sinPhi; mz = 1;nz = CenterZ;}
		float DenX = 1.f/mx,DenY = 1.f/my,DenZ = 1.f/mz;
		float CenterZPiuHalfRangeZ = CenterZ + HalfRangeZ;
		float Diff;
		Vector v[2];
		int j,count,count2 = 0;
		int Center = (NumVerSections/2)*(NumHorSections) + NumHorSections/2;
		for(i = NumVerSections/2; i < NumVerSections/2 + 1; i++)
		{
			if(RefAxe == ZAXE){ny =	secty*i - HalfRangeY;}
			else {nz = CenterZPiuHalfRangeZ - sectz*i;}
/*			if(RefAxe == XAXE){nz = CenterZPiuHalfRangeZ - sectz*i;}
			if(RefAxe == YAXE){nz = CenterZPiuHalfRangeZ - sectz*i;}*/
			for(j = NumHorSections/2; j < NumHorSections/2 + 1; j++)
			{
				if(RefAxe == XAXE){ny = secty*j - HalfRangeY;}
				else {nx = sectx*j - HalfRangeX;}
			/*	if(RefAxe == YAXE){nx = sectx*j - HalfRangeX;}
				if(RefAxe == ZAXE){nx = sectx*j - HalfRangeX;}*/
				count = 0;
				Diff = MaxX - nx;
				worker = ny + my*DenX*Diff;
				if(worker < MaxY && worker > MinY)
				{
					worker = nz + mz*DenX*Diff;
					if(worker < MaxZ && worker > MinZ)
					{
						v[count].x = MaxX;
						v[count].y = ny + my*DenX*Diff;
						v[count].z = worker;
						count++;
					}
				}
				Diff = MinX - nx;
				worker = ny + my*DenX*Diff;
				if(worker < MaxY && worker > MinY)
				{
					worker = nz + mz*DenX*Diff;
					if(worker < MaxZ && worker > MinZ)
					{
						v[count].x = MinX;
						v[count].y = ny + my*DenX*Diff;
						v[count].z = worker;
						count++;
					}
				}
				if(count < 2)
				{
					Diff = MaxY - ny;
					worker = nx + mx*DenY*Diff;
					if(worker < MaxX && worker > MinX)
					{
						worker = nz + mz*DenY*Diff;
						if(worker < MaxZ && worker > MinZ)
						{
							v[count].x = nx + mx*DenY*Diff;
							v[count].y = MaxY;
							v[count].z = worker;
							count++;
						}
					}
					if(count < 2)
					{
						Diff = MinY - ny;
						worker = nx + mx*DenY*Diff;
						if(worker < MaxX && worker > MinX)
						{
							worker = nz + mz*DenY*Diff;
							if(worker < MaxZ && worker > MinZ)
							{
								v[count].x = nx + mx*DenY*Diff;
								v[count].y = MinY;
								v[count].z = worker;
								count++;
							}
						}
						if(count < 2)
						{
							Diff = MaxZ - nz;
							worker = nx + mx*DenZ*Diff;
							if(worker < MaxX && worker > MinX)
							{
								worker = ny + my*DenZ*Diff;
								if(worker < MaxY && worker > MinY)
								{
									v[count].x = nx + mx*DenZ*Diff;
									v[count].y = worker;
									v[count].z = MaxZ;
									count++;
								}
							}
							if(count < 2)
							{
								Diff = MinZ - nz;
								worker = nx + mx*DenZ*Diff;
								if(worker < MaxX && worker > MinX)
								{
									worker = ny + my*DenZ*Diff;
									if(worker < MaxY && worker > MinY)
									{
										v[count].x = nx + mx*DenZ*Diff;
										v[count].y = worker;
										v[count].z = MinZ;
										count++;
									}
								}
							}
						}
					}
				}
				float &Length = (pSections + j + NumHorSections*i)->Length;
				if(count < 2)Length = 0;
				else if(count > 2)ASSERT(FALSE);
				else if(count == 2)
				{
					if(RefAxe == XAXE){Length = (v[0].x - v[1].x)*Sphericals.FactorX;}
					if(RefAxe == YAXE){Length = (v[0].y - v[1].y)*Sphericals.FactorY;}
					if(RefAxe == ZAXE){Length = (v[0].z - v[1].z)*Sphericals.FactorZ;}
				}
			}
		}
	}
	return true;
}

SEmulsionSections::~SEmulsionSections()
{
	if(ppGrainsX)free(ppGrainsX);
	if(ppGrainsY)free(ppGrainsY);
	if(ppGrainsZ)free(ppGrainsZ);
	free(pSections);
	free(pIncrements);
	free(pIndexes);
	if(pNewCoordinates)free(pNewCoordinates);
}
