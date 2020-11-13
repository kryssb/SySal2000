#ifndef _SYSAL_2D_VECTORS_
#define _SYSAL_2D_VECTORS_

#include "..\Common\Vectors.h"
#include "..\Common\TVectors.h"

struct Vector2
{
	double X, Y;
	Vector2 &operator=(Vector &V)
	{
		X = V.X;
		Y = V.Y;
		return *this;
		};

	Vector2 &operator=(TVector &V)
	{
		X = V.X;
		Y = V.Y;
		return *this;
		};
	
	Vector2(Vector &V) 
	{
		X = V.X;
		Y = V.Y;							
		};

	Vector2(TVector &V) 
	{
		X = V.X;
		Y = V.Y;							
		};
	
	Vector2(double x = 0, double y = 0) : X(x), Y(y) {};
	};

#endif