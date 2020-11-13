#ifndef _SYSAL_FIELD_MAP_
#define _SYSAL_FIELD_MAP_

class FieldMap
{
	protected:

		float StartX, StartY;
		float StepX, StepY;
		
		int Length;
		struct t_Pos
		{
			float X, Y;
			} *pPos;

	public:

		FieldMap(char *fname);
		FieldMap(int XN, int YN);
		virtual ~FieldMap();

		void SetStart(float X, float Y);
		void SetStep(float X, float Y);

		int GetLength();
		bool GetFieldPos(int i, float *pX, float *pY);

	};

#endif