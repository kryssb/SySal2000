#ifndef _SYSAL_AFFINE_TRANSFORMATIONS_
#define _SYSAL_AFFINE_TRANSFORMATIONS_

class AffineTransf
{
	private:

		double M[2][2];
   		double D[2];

	public:

		AffineTransf() {};

		AffineTransf(double ExpCos, double ExpSin, double DX, double DY);

		void Transform(double x, double y, double *tx, double *ty);

		void Deform(double x, double y, double *tx, double *ty);
	};

#endif