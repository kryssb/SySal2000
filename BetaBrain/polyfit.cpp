#include "polyfit.h"
#include <math.h>
#include <malloc.h>

int Linear_Fit(int NPoints, double *X, double *Y, double *C0, double *C1, double *Sigma)
{	double V, W;
	double SumY = 0, SumX = 0, SumX2 = 0, SumXY = 0, Den;
	double *ScanX, *EndX, *ScanY;

	EndX = X + NPoints;
	for (ScanX = X, ScanY = Y; ScanX < EndX;)
	{	V = *ScanX++;
		W = *ScanY++;
		SumX += V;
		SumX2 += V * V;
		SumY += W;
		SumXY += V * W;
		};

	Den = NPoints * SumX2 - SumX * SumX;

	if (Den == 0.0) return 0;

	Den = 1. / Den;

	*C0 = (SumY * SumX2 - SumX * SumXY) * Den;
	*C1 = (NPoints * SumXY - SumX * SumY) * Den;

   if (Sigma)
   {  SumX = 0;
   	for (ScanX = X, ScanY = Y; ScanX < EndX;)
      {	SumY = (*C0 + *C1 * *ScanX++ - *ScanY++);
      	SumX += SumY * SumY;
         };
      *Sigma = sqrt(SumX / (NPoints - 1));
   	};

	return 1;
	};

int Parabolic_Fit(int NPoints, double *X, double *Y, double *C0, double *C1, double *C2, double *Sigma)
{	double V, W, Z;
	double SumX = 0, SumX2 = 0, SumX3 = 0, SumX4 = 0, SumY = 0, SumXY = 0,
		SumX2Y = 0, Den;
	double *ScanX, *EndX, *ScanY;
	double P24,P14,P13;

	EndX = X + NPoints;
	for (ScanX = X, ScanY = Y; ScanX < EndX;)
	{	Z = V = *ScanX++;
		W = *ScanY++;
		SumX += Z;
		SumY += W;
		SumXY += W * Z;
		Z *= V;
		SumX2 += Z;
		SumX2Y += W * Z;
		Z *= V;
		SumX3 += Z;
		Z *= V;
		SumX4 += Z;
		};

	P24 = SumX2 * SumX4 - SumX3 * SumX3;
	P14 = SumX * SumX4 -	SumX3 * SumX2;
	P13 = SumX * SumX3 - SumX2 * SumX2;
	Den = NPoints * P24 - SumX * P14 + SumX2 * P13;

	if (Den == 0.0) return 0;

	Den = 1. / Den;

	*C0 = (SumY * P24 - SumX * (SumXY * SumX4  - SumX3 * SumX2Y) + SumX2 *
		(SumXY * SumX3 - SumX2Y * SumX2)) * Den;
	*C1 = (NPoints * (SumXY * SumX4 - SumX3 * SumX2Y) - SumY * P14 + SumX2 *
		(SumX * SumX2Y - SumXY * SumX2)) * Den;
	*C2 = (NPoints * (SumX2 * SumX2Y - SumXY * SumX3) - SumX * (SumX * SumX2Y -
		SumXY * SumX2) + SumY * P13) * Den;

	if (Sigma)
	{  SumX = 0;
		for (ScanX = X, ScanY = Y; ScanX < EndX;)
		{  V = *ScanX++;
			SumY = (*C0 + (*C1 + *C2 * V) * V - *ScanY++);
			SumX += SumY * SumY;
			};
		*Sigma = sqrt(SumX / (NPoints - 2));
		};

	return 1;
	};

double Det(int N, double **A);

int MultiLinearFit(int NPoints, int NVars, double *Data, double *Out)
{
	int i, j, k;
	double Sum;
	double det;
	double *TCol, *TData1, *TData2;
	double **Cols = (double **)malloc(sizeof(double *) * (NVars + 2));
	for (i = 0; i < (NVars + 2); i++) Cols[i] = (double *)malloc(sizeof(double) * (NVars + 1));

	Sum = 0;
	for (k = 0; k < NPoints; k++) Sum += Data[k];
	Cols[0][0] = Sum;

	TData1 = Data;
	TCol = Cols[0];
	for (j = 1; j < (NVars + 1); j++)
	{	Sum = 0;
		TData2 = Data + NPoints * j;
		for (k = 0; k < NPoints; k++) Sum += TData1[k] * TData2[k];
		TCol[j] = Sum;
		};

	Cols[1][0] = NPoints;

	for (i = 2; i < (NVars + 2); i++)
	{
		TData1 = Data + (i - 1) * NPoints;
		Sum = 0;
		for (k = 0; k < NPoints; k++) Sum += TData1[k];
		Cols[i][0] = Cols[1][i - 1] = Sum;
		};

	for (i = 1; i < (NVars + 1); i++)
	{	TCol = Cols[i + 1];
		TData1 = Data + i * NPoints;
		for (j = 1; j < (NVars + 1); j++)
		{	TData2 = Data + j * NPoints;
			Sum = 0;
			for (k = 0; k < NPoints; k++) Sum += TData1[k] * TData2[k];
			TCol[j] = Sum;
			};
		};
	det = Det(NVars + 1, Cols + 1);
	if (det == 0.)
	{
		for (i = 0; i < (NVars + 2); i++) free(Cols[i]);
		free(Cols);
		return 0;
		};
	det = 1. / det;
	for (i = 0; i < (NVars + 1); i++)
	{	double *Swap = Cols[i + 1];
		Cols[i + 1] = Cols[0];
		Out[i] = Det(NVars + 1, Cols + 1) * det;
		Cols[i + 1] = Swap;
		};

	for (i = 0; i < (NVars + 2); i++) free(Cols[i]);
	free(Cols);
	return 1;
	};

double Det(int N, double **A)
{
	if (N == 1) return A[0][0];
	int i, j;
	double det = 0;
	double **TA = (double **)malloc(sizeof(double *) * (N - 1));
	for (i = 0; i < N; i++)
	{	for (j = 0; j < i; j++) TA[j] = A[j] + 1;
		for (j = (i + 1); j < N; j++) TA[j - 1] = A[j] + 1;
		det += A[i][0] * Det(N - 1, TA) * ((i % 2) ? -1 : 1);
		};
	free(TA);
   return det;
	};
