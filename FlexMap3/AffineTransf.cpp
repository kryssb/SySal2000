#include "StdAfx.h"
#include "AffineTransf.h"

AffineTransf::AffineTransf(IntMark::t_Pos Source[3], IntMark::t_Pos Dest[3]) throw(double)
{
	double SX1 = Source[1].X - Source[0].X;
	double SY1 = Source[1].Y - Source[0].Y;
	double SX2 = Source[2].X - Source[0].X;
	double SY2 = Source[2].Y - Source[0].Y;

	double DX1 = Dest[1].X - Dest[0].X;
	double DY1 = Dest[1].Y - Dest[0].Y;
	double DX2 = Dest[2].X - Dest[0].X;
	double DY2 = Dest[2].Y - Dest[0].Y;

	double Det = SX1 * SY2 - SX2 * SY1;
	if (Det == 0) throw(Det);
	Det = 1. / Det;

	M[0][0] = (DX1 * SY2 - DX2 * SY1) * Det;
	M[0][1] = (SX1 * DX2 - SX2 * DX1) * Det;
	M[1][0] = (DY1 * SY2 - DY2 * SY1) * Det;
	M[1][1] = (SX1 * DY2 - SX2 * DY1) * Det;

	D[0] = Dest[0].X - Source[0].X * M[0][0] - Source[0].Y * M[0][1];
	D[1] = Dest[0].Y - Source[0].X * M[1][0] - Source[0].Y * M[1][1];
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
