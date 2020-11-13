#include "StdAfx.h"
#include "AffineTransf.h"

AffineTransf::AffineTransf(double ExpCos, double ExpSin, double DX, double DY)
{
	M[0][0] = ExpCos;
	M[0][1] = -ExpSin;
	M[1][0] = ExpSin;
	M[1][1] = ExpCos;

	D[0] = DX;
	D[1] = DY;
	};

void AffineTransf::Transform(double x, double y, double *tx, double *ty)
{
	*tx = M[0][0] * x + M[0][1] * y + D[0];
	*ty = M[1][0] * x + M[1][1] * y + D[1];
	};

void AffineTransf::Deform(double x, double y, double *tx, double *ty)
{
	*tx = M[0][0] * x + M[0][1] * y;
	*ty = M[1][0] * x + M[1][1] * y;
	};
