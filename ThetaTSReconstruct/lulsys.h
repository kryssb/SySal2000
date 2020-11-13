#ifndef LU_LINEARSYSTEMS_SOLVER
#define LU_LINEARSYSTEMS_SOLVER

class LULinSystem
{
	protected:

   	int Dim;
      double *EqMat;
      double ZeroEps;
      int *ColP;


   public:

      LULinSystem(int dim, double *eqmat, double zeroeps = 0) throw(double);
      ~LULinSystem();

		void Solve(double *DataVect, double *SolVect);

   };

#endif
