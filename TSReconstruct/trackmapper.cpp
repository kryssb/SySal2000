#define USE_MIDL_INCOMPATIBLE_STRUCTS
#include "trackmapper.h"
#include <malloc.h>
#include <math.h>

#define MAXINCELL 4

struct MapCell
{
	int N;
	Vector2 *Slopes;
	};

struct ExtMapCell : public MapCell
{
	TS_Segment **OrigTracks;
	};


struct MovingCell : public MapCell
{
	int x;
	int y;
	};

struct ExtMovingCell : public MovingCell
{
	TS_Segment **OrigTracks;
	};

void MapTracks(MappingParams *Result, int N1, TS_Segment *T1, int N2, TS_Segment *T2, float TolP,
	float TolS, float MaxDisplacement, float LowestPrescanPeak)
{
	MappingParams RResult = *Result;
	Vector2 Min, Max;
	int *pCoincRec;
	ExtMapCell *FixedMap;
	ExtMovingCell *MovingMap;
	int CellNX, CellNY;
	int i, j, k;
	int MovingMapN, FixedMapN;
	int rtx, rty;
	RResult.CoincN = -1;
	RResult.Pair = 0;
	int otx, oty, tx, ty;

	if ((N1 <= 0) || (N2 <= 0))
	{
   		*Result = RResult;
   		return;
		};
	RResult.CoincN = 0;      

	Min = Max = T1[0].Intercept;
	for (i = 1; i < N1; i++)
	{	if (Min.X > T1[i].Intercept.X)
   		{	Min.X = T1[i].Intercept.X; }
		else if (Max.X < T1[i].Intercept.X)
   		{	Max.X = T1[i].Intercept.X; };
		if (Min.Y > T1[i].Intercept.Y)
   		{	Min.Y = T1[i].Intercept.Y; }
		else if (Max.Y < T1[i].Intercept.Y)
   		{	Max.Y = T1[i].Intercept.Y; };
		};
	for (i = 0; i < N2; i++)
	{	if (Min.X > T2[i].Intercept.X)
   		{	Min.X = T2[i].Intercept.X; }
		else if (Max.X < T2[i].Intercept.X)
   		{	Max.X = T2[i].Intercept.X; };
		if (Min.Y > T2[i].Intercept.Y)
   		{	Min.Y = T2[i].Intercept.Y; }
		else if (Max.Y < T2[i].Intercept.Y)
   		{	Max.Y = T2[i].Intercept.Y; };
		};
	otx = ceil(MaxDisplacement / TolP);
	oty = ceil(MaxDisplacement / TolP);
	CellNX = ceil((Max.X - Min.X) / TolP + 1);
	CellNY = ceil((Max.Y - Min.Y) / TolP + 1);
	pCoincRec = new int[(CellNX + 2) * (CellNY + 2)];
	for (i = 0; i < (CellNX + 2) * (CellNY + 2); pCoincRec[i++] = 0);
	MovingMap = (ExtMovingCell *)malloc(sizeof(ExtMovingCell) * CellNX * CellNY);
	for (i = 0; i < (CellNX * CellNY); MovingMap[i++].N = 0);
	for (i = 0; i < N1; i++)
	{	int N;
   		ExtMovingCell *PCell;
   		PCell = MovingMap + ((int)((T1[i].Intercept.X - Min.X) / TolP) + (int)((T1[i].Intercept.Y - Min.Y) / TolP) * CellNX);
		N = PCell->N;
		if (N < MAXINCELL)
		{
			if (!N)
   			{
      			PCell->Slopes = (Vector2 *)malloc(sizeof(Vector2) * MAXINCELL);
      			PCell->OrigTracks = (TS_Segment **)malloc(sizeof(TS_Segment *) * MAXINCELL);
				};
			PCell->Slopes[N] = T1[i].Slope;
			PCell->OrigTracks[N] = T1 + i;
			PCell->N++;
			};
		};
	for (i = 0, j = 0; i < (CellNX * CellNY); i++)
		if (MovingMap[i].N)
		{	MovingMap[j] = MovingMap[i];
      		MovingMap[j].x = i % CellNX;
      		MovingMap[j].y = i / CellNX;
			j++;
			};
	MovingMapN = j;

	FixedMap = (ExtMapCell *)malloc(sizeof(ExtMapCell) * (FixedMapN = CellNX * CellNY));
	for (i = 0; i < (CellNX * CellNY); FixedMap[i++].N = 0);
	for (i = 0; i < N2; i++)
	{	int x, y, jx, jy;
   		x = (T2[i].Intercept.X - Min.X) / TolP;
   		y = (T2[i].Intercept.Y - Min.Y) / TolP;
		for (jx = -1; jx <= 1; jx++)
      		for (jy = -1; jy <= 1; jy++)
			{	int tx = x + jx;
         		int ty = y + jy;
				ExtMapCell *PCell;
				if ((tx >= 0) && (tx < CellNX) && (ty >= 0) && (ty < CellNY))
				{	int N;
	            	PCell = FixedMap + tx + ty * CellNX;
					N = PCell->N;
					if (N < (8 * MAXINCELL))
					{	if (!N)
	               		{
		              		PCell->Slopes = (Vector2 *)malloc(sizeof(Vector2) * 16 * MAXINCELL);
							PCell->OrigTracks = (TS_Segment **)malloc(sizeof(Vector2) * 8 * MAXINCELL);
							};
					    PCell->Slopes[2 * N].X = T2[i].Slope.X - TolS;
						PCell->Slopes[2 * N].Y = T2[i].Slope.Y - TolS;
				        PCell->Slopes[2 * N + 1].X = T2[i].Slope.X + TolS;
				        PCell->Slopes[2 * N + 1].Y = T2[i].Slope.Y + TolS;
						PCell->OrigTracks[N] = T2 + i;
						PCell->N++;
						};
					};
      			};
			};

		RResult.MovSize.X = CellNX * TolP;
		RResult.MovSize.Y = CellNY * TolP;
		RResult.FixSize.X = CellNX * TolP;
		RResult.FixSize.Y = CellNY * TolP;

		for (tx = -otx; tx <= otx; tx++)
		{		
			for (ty = -oty; ty <= oty; ty++)
			{	int CoincN = 0;
		  		for (i = 0; i < MovingMapN; i++)
      			{	MovingCell TempMoving = MovingMap[i];
         			TempMoving.y += ty;
	         		if ((TempMoving.y >= 0) && (TempMoving.y < CellNY))
					{	TempMoving.x += tx;
			    		if ((TempMoving.x >= 0) &&
				        (TempMoving.x < CellNX))
						{
   	           				MapCell TempFixed = FixedMap[TempMoving.y * CellNX + TempMoving.x];
							int TF = 2 * TempFixed.N;
							for (j = 0; j < TempMoving.N; j++)
							{	Vector2 TSlope = TempMoving.Slopes[j];
				   				for (k = 0; (k < TF) && ((TSlope.X < TempFixed.Slopes[k].X) ||
	   								(TSlope.Y < TempFixed.Slopes[k].Y) || (TSlope.X > TempFixed.Slopes[k + 1].X) ||
	               					(TSlope.Y > TempFixed.Slopes[k + 1].Y)); k += 2);
				        			if (k < TF)	CoincN++;
								};
   							};
						};
					};
				pCoincRec[(tx + otx + 1) + (ty + oty + 1) * (CellNX + 2)] = CoincN;
				if (CoincN > RResult.CoincN)
				{/*	rtx = tx;
       				rty = ty;*/
					RResult.CoincN = CoincN;
	   				};
				};
			};
		int MinPeak = LowestPrescanPeak * RResult.CoincN;
		rtx = 2 * (CellNX + 2);
		rty = 2 * (CellNY + 2);
		RResult.CoincN = 0;
		for (tx = 1; tx < (CellNX + 1); tx++)
			for (ty = 1; ty < (CellNY + 1); ty++)
			{
				int CoincN = pCoincRec[ty * (CellNX + 2) + tx];
				if (CoincN >= MinPeak)
					if (CoincN >= pCoincRec[ty * (CellNX + 2) + tx - 1] &&
						CoincN >= pCoincRec[ty * (CellNX + 2) + tx + 1] &&
						CoincN >= pCoincRec[(ty + 1) * (CellNX + 2) + tx] &&
						CoincN >= pCoincRec[(ty - 1) * (CellNX + 2) + tx] &&
						CoincN >= pCoincRec[(ty + 1) * (CellNX + 2) + tx + 1] &&
						CoincN >= pCoincRec[(ty + 1) * (CellNX + 2) + tx - 1] &&
						CoincN >= pCoincRec[(ty - 1) * (CellNX + 2) + tx - 1] &&
						CoincN >= pCoincRec[(ty - 1) * (CellNX + 2) + tx + 1])
						if (hypot(rtx, rty) > hypot(tx - otx - 1, ty - oty - 1))
						{
							RResult.CoincN = CoincN;
							rtx = tx - otx - 1;
							rty = ty - oty - 1;
							};
				};
		if (RResult.CoincN)
		{	RResult.Overlap.X = TolP * rtx;
   			RResult.Overlap.Y = TolP * rty;
   			RResult.Pair = (Diff *)malloc(sizeof(Diff) * RResult.CoincN);
   			Diff *DiffScan = RResult.Pair;
   			for (i = 0; i < MovingMapN; i++)
	     	{	ExtMovingCell TempMoving = MovingMap[i];
		    	TempMoving.y += rty;
				if ((TempMoving.y >= 0) && (TempMoving.y < CellNY))
				{	TempMoving.x += rtx;
           			if ((TempMoving.x >= 0) && (TempMoving.x < CellNX))
					{
		          		ExtMapCell TempFixed = FixedMap[TempMoving.y * CellNX + TempMoving.x];
						int TF = 2 * TempFixed.N;
	 					for (j = 0; j < TempMoving.N; j++)
						{	Vector2 TSlope = TempMoving.Slopes[j];
               				for (k = 0; (k < TF) && ((TSlope.X < TempFixed.Slopes[k].X) ||
								(TSlope.Y < TempFixed.Slopes[k].Y) || (TSlope.X > TempFixed.Slopes[k + 1].X) ||
	      						(TSlope.Y > TempFixed.Slopes[k + 1].Y)); k += 2);
		             		if (k < TF)
							{	k /= 2;
				      			DiffScan->Fix = TempFixed.OrigTracks[k];
					  			DiffScan->Mov = TempMoving.OrigTracks[j];
				  				DiffScan->FixPos = TempFixed.OrigTracks[k]->Intercept;
								DiffScan->MovPos = TempMoving.OrigTracks[j]->Intercept;
               					DiffScan->FixSlope = TempFixed.OrigTracks[k]->Slope;
								DiffScan->MovSlope = TempMoving.OrigTracks[j]->Slope;
								DiffScan->FixPos.X -= Min.X;
								DiffScan->FixPos.Y -= Min.Y;
								DiffScan->MovPos.X -= Min.X;
								DiffScan->MovPos.Y -= Min.Y;
								DiffScan++;
								};
						};
					};
				};
			};
		RResult.RawTransl.X = 0;
		for (i = 0; i < RResult.CoincN; i++)
			RResult.RawTransl.X += RResult.Pair[i].MovPos.X - RResult.Pair[i].FixPos.X;
		RResult.RawTransl.X /= RResult.CoincN;
		RResult.RawTransl.Y = 0;
		for (i = 0; i < RResult.CoincN; i++)
			RResult.RawTransl.Y += RResult.Pair[i].MovPos.Y - RResult.Pair[i].FixPos.Y;
		RResult.RawTransl.Y /= RResult.CoincN;
		};
	for (i = 0; i < MovingMapN; i++)
		if (MovingMap[i].N)
		{
   			free(MovingMap[i].Slopes);
       		free(MovingMap[i].OrigTracks);
	   		};
	for (i = 0; i < FixedMapN; i++)
		if (FixedMap[i].N)
		{
   			free(FixedMap[i].Slopes);
       		free(FixedMap[i].OrigTracks);
	   		};
	free(MovingMap);
	free(FixedMap);
	delete [] pCoincRec;
	*Result = RResult;
	};


