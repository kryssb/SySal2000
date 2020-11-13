#include "lulsys.h"
#include <malloc.h>
#include <math.h>

LULinSystem::LULinSystem(int dim, double *eqmat, double zeroeps) throw(double)
	: Dim(dim), EqMat(eqmat), ZeroEps(zeroeps)
{
	int i, j, k;
	int *colp = ColP = (int *)malloc(sizeof(int) * dim);
	double *RBase;

	for (i = 0; i < dim; i++) ColP[i] = i;

	for (i = 0; i < dim; i++)
	{
   		int c = colp[i];
		double *REq = eqmat + i * dim;
		if (fabs(REq[c]) < zeroeps)
		{
			for (j = i + 1; (j < dim) && fabs(REq[ColP[j]]) < zeroeps; j++);
			if (j == dim) throw(zeroeps);
			colp[i] = colp[j];
			colp[j] = c;
			c = colp[i];
      		};

		double Inv = 1 / REq[c];
		RBase = REq + c;
   		for (j = i + 1; j < dim; j++)
		{
			RBase += dim;
      		*RBase *= Inv;
      		};

		RBase = eqmat + i * dim;
		for (j = i + 1; j < dim; j++)
		{
      		RBase += dim;
			double Mult = RBase[c];
			for (k = i + 1; k < dim; k++)
         	RBase[ColP[k]] -= Mult * REq[ColP[k]];
      		};
   		};
   };

LULinSystem::~LULinSystem()
{	free(ColP); };

void LULinSystem::Solve(double *DataVect, double *SolVect)
{
	int dim = Dim;
	int *colp = ColP;
	double *RBase = EqMat;

	int i, j;
	for (i = 0; i < dim; i++)
	{
		double Datum = DataVect[i];
		for (j = 0; j < i; j++) Datum -= RBase[colp[j]] * DataVect[j];
		DataVect[i] = Datum;
		RBase += dim;
   		};

	for (i = dim - 1; i >= 0; i--)
	{
		RBase -= dim;
   		double Datum = DataVect[i];
   		for (j = i + 1; j < dim; j++) Datum -= RBase[colp[j]] * DataVect[j];
		DataVect[i] = Datum / RBase[colp[i]];
   		};

	for (i = 0; i < dim; i++) SolVect[colp[i]] = DataVect[i];
	};

