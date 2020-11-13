


void CTracker::ApplyDistorsionCorrection(SDistorsion Dist,SEmulsionSpace &Space)
{
	double x0,y0,A,B,R,deltax,deltay,r,a,b;
	float dx,dy,x,y;
	int i;
	x0 = Dist.xzero; y0 = Dist.yzero; A = Dist.A;
	B = Dist.B;R = Dist.R;
	a = Dist.a; b = Dist.b;
	Space.Distorsion = Dist;
	SIntGrain *pGrains = Space.pGrains;
	for(i = 0; i < Space.NumGrains;i++)
	{
		SIntGrain & wg = *(pGrains + i);
		x = wg.xx; y = wg.yy;
		deltax = (x - x0);
		deltay = (y - y0);
		r = deltax*deltax + deltay*deltay;
		wg.z = (float)(- A*r - B*r*r + wg.zz + a*x + b*y);
		dx = (float)(R * deltax * r);
		dy = (float)(R * deltay * r);
		wg.x = dx + x;
		wg.y = dy + y;
	}
}

void CTracker::FindGlobalDistorsion(SDistorsion &Dist)
{
	// This function searchs parameters minimizing the mean distance of grains in a group of
	// Horizontal tracks and the searchs a linear transformation that minimize grains laying
	// int the central zone of emulsion space.
	int count = CountTracks(m_pTrack);
	SMip * pMip;
	STrackingInfo Par = Parameters;
	double x0,y0,A,B,r,R,deltax,deltay;
	float x,y,dx,dy;
	double xmin = Par.x0min,xmax = Par.x0max,DX = Par.dx;
	double ymin = Par.y0min,ymax = Par.y0max,DY = Par.dy;
	double Rmin = Par.Rmin,Rmax = Par.Rmax,DR = Par.dR;
	double Bmin = Par.Bmin,Bmax = Par.Bmax;
	double Amin = Par.Amin,Amax = Par.Amax;
	double DB = Par.dB,DA = Par.dA;
	double weight,MD = 50,WMD,VDS,ZetaWeight = 0.004;
	if(count < 2)return ;
	if(TP.pSetDlgItemText)TP.pSetDlgItemText(TP.pContext, TP.pIdc->StaticLocalGrains,"Searching");
	for(int j = 0; j < 2; j++)
	{
		for(A = Amin; A < Amax; A += DA)
		{
			if(TP.pSetInteger)TP.pSetInteger(TP.pContext, TP.pIdc->LocalGrains,(int)((A - Amin)/DA + 1));
			for(B = Bmin; B < Bmax; B += DB)
			{
				for(x0 = xmin; x0 <= xmax; x0 += DX)
				{
					for(y0 = ymin; y0 <= ymax; y0 += DY)
					{
						for(R = Rmin; R < Rmax; R += DR)
						{
							pMip = m_pTrack;weight = 0;WMD = 0;
							while(pMip->pNext != NULL)
							{
								for(int m = 0; m < pMip->NGrains; m++)
								{
									SIntGrain &wg = *(pMip->pGrains + m);
									x = wg.xx; y = wg.yy;
									deltax = (x - x0);
									deltay = (y - y0);
									r = deltax*deltax + deltay*deltay;
									wg.z = (float)(- A*r - B*r*r + wg.zz);
									dx = (float)(R * deltax * r);
									dy = (float)(R * deltay * r);
									wg.x = dx + x;
									wg.y = dy + y;
								}
								LinearFit(*pMip);
								WMD += pMip->md*pMip->NGrains;
								weight += pMip->NGrains;
								pMip = pMip->pNext;
							}
							WMD = WMD/weight;
							VDS = 0;
							for(int k = -100; k < 200; k += 200)
							{
								for(int l = -100; l < 200; l += 200)
								{
									deltax = (k - x0);
									deltay = (l - y0);
									r = deltax*deltax + deltay*deltay;
									VDS += fabs(A*r + B*r*r + 6);
								}
							}
							WMD += ZetaWeight * VDS;
							if(WMD < MD)
							{
								MD = WMD;
								Dist = SDistorsion(x0,y0,A,B,R);
							}
						}
					}
				}
			}
		}
		xmin = Dist.xzero - DX; xmax = Dist.xzero + DX;
		ymin = Dist.yzero - DY; ymax = Dist.yzero + DY;
		Rmin = Dist.R - DR; Rmax = Dist.R + DR;
		DX /= 2.5;DY /= 2.5;DR /= 2.5;
		Bmin = Dist.B - DB; Bmax = Dist.B + DB;
		Amin = Dist.A + DA; Amax = Dist.A - DA;
		DA /= 5; DB /= 5; 
	}
	double a,b,BestA = Dist.A,BestB = Dist.B;
	{
		SEmulsionSpace &Space = *TP.pEmulsionRegion;
		SIntGrain *pGrains = Space.pGrains;
		int NumGrains = Space.NumGrains;
		int i;
		double amin = -0.1, amax = 0.1,bmin = -0.1,bmax = 0.1,da = 0.02,db = 0.02;
		float x,y,z,maxz = -10000,minz = 10000;
		int MinTriCounts = 1000;
		float spessore;
		for(i = 0; i < NumGrains; i++)
		{
			SIntGrain &gr = *(pGrains + i);
			z = gr.z;
			if(maxz < z)maxz = z;
			if(minz > z)minz = z;
		}
		spessore = maxz - minz;
		int *pBins = (int *)malloc(sizeof(int)*600);
		if(pBins)
		{
		A = Dist.A; B = Dist.B; x0 = Dist.xzero; y0 = Dist.yzero; R = Dist.R;
		for(int j = 1; j < 3; j++)
		{
			for(a = amin; a < amax; a += da)
			{
				for(b = bmin; b < bmax; b += db)
				{
					int i;
					for(i = 0; i < 600; i++){*(pBins + i) = 0;}
					maxz = -100000;minz = 100000;
					for(i = 0; i < NumGrains; i++)
					{
						SIntGrain &gr = *(pGrains + i);
						x = (gr.xx - (float)x0);
						y = (gr.yy - (float)y0);
						r = x*x + y*y;
						z = (float)(gr.zz - A*r - B*r*r + a*x + b*y);
						if(maxz < z)maxz = z;
						if(minz > z)minz = z;
						gr.z = z;
					}
					minz = minz - .01f;
					maxz = maxz + .01f;
					int NumBins = (int)(1 + 5*(maxz - minz));
					if(NumBins > 600)continue;
					int NotZeroBins = 0;
						for(i = 0; i < NumBins; i++){*(pBins + i) = 0;}
					for(i = 0; i < NumGrains; i++)
					{
						(*(pBins + (int)(5*((pGrains + i)->z - minz))))++;
					}
					for(i = 0; i < NumBins; i++){if(*(pBins + i) > 0)NotZeroBins++;}
					int mean,index = 0,MinMiddleBin = 1000,MMBIndex,TriCounts;
					int rangemin,rangemax;
					float minbin = 0, maxbin = 0;
					mean = (int)NumGrains/NotZeroBins;
					for(i = 0; i < NumBins; i++)
					{
						if(*(pBins + i) < mean/2)minbin += 0.2f;
						else break;
					}
					for(i = NumBins - 1; i >= 0; i--)
					{
						if(*(pBins + i) < mean/2)maxbin += 0.2f;
						else break;
					}
					if((maxz - maxbin) - (minz + minbin) > spessore)continue;
					float midZ = ((maxz - maxbin) + (minz + minbin))/2.f;
					rangemin = 5*(int)(midZ - minz - 5);
					rangemax = 5*(int)(midZ - minz + 5);
					for(i = rangemin; i < rangemax + 1; i++)
					{
						if(MinMiddleBin > *(pBins + i))
						{
							MinMiddleBin = *(pBins + i);
							MMBIndex = i;
						}
					}
					TriCounts = *(pBins + MMBIndex - 1) + *(pBins + MMBIndex) + *(pBins + MMBIndex + 1);
					TriCounts = *(pBins + MMBIndex - 2) + TriCounts + *(pBins + MMBIndex + 2);
					if(TriCounts < MinTriCounts)
					{
						MinTriCounts = TriCounts;
						BestA = a;
						BestB = b;
					}
				}
			}
			bmin = BestB - db; bmax = BestB + db;
			amin = BestA - da; amax = BestA + da;
			da /= 5; db /= 5; 
		}
		}
		free(pBins);
	}
	Dist.a = BestA; Dist.b = BestB;
	return ;
}

