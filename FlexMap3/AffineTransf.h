#ifndef _SYSAL_AFFINE_TRANSFORMATIONS_
#define _SYSAL_AFFINE_TRANSFORMATIONS_

#include "IntMarkMap.h"

class AffineTransf
{
	private:

		double M[2][2];
   		double D[2];

	public:

		AffineTransf() {};

		AffineTransf(IntMark::t_Pos Source[3], IntMark::t_Pos Dest[3]) throw(double);

		void Transform(double x, double y, double *tx, double *ty);

		void Deform(double x, double y, double *tx, double *ty);
	};

#endif