#include "StdAfx.h"
#include "FieldMap.h"

FieldMap::FieldMap(char *fname) : pPos(0)
{
	HANDLE HFile = 0;
	try
	{
		HFile = CreateFile(fname, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (HFile == INVALID_HANDLE_VALUE || !HFile) throw 0;
		ULONG br;
		if (!ReadFile(HFile, &Length, sizeof(Length), &br, NULL) || br < sizeof(Length)) throw 0;
		pPos = new t_Pos[Length];
		if (!ReadFile(HFile, pPos, Length * sizeof(t_Pos), &br, NULL) || br < (Length * sizeof(t_Pos))) throw 0;
		CloseHandle(HFile);
		}
	catch (...)
	{
		if (HFile && HFile != INVALID_HANDLE_VALUE)
			CloseHandle(HFile);
		if (pPos) delete [] pPos;
		pPos = 0;
		Length = 1;
		pPos = new t_Pos[1];
		pPos->X = pPos->Y = 0.f;
		};
	};
		
FieldMap::~FieldMap()
{
	if (pPos) delete [] pPos;
	};

void FieldMap::SetStart(float X, float Y)
{
	StartX = X;
	StartY = Y;
	};
		
void FieldMap::SetStep(float X, float Y)
{
	StepX = X;
	StepY = Y;
	};

int FieldMap::GetLength()
{
	return Length;
	};
		
bool FieldMap::GetFieldPos(int i, float *pX, float *pY)
{
	if (i < 0 || i >= Length) return false;
	*pX = StartX + StepX * pPos[i].X;
	*pY = StartY + StepY * pPos[i].Y;
	return true;
	};
