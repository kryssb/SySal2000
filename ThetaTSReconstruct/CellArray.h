#ifndef _TS_RECONSTRUCT_CELL_ARRAY_
#define _TS_RECONSTRUCT_CELL_ARRAY_

#include "..\Common\Vectors.h"
#include <memory.h>
#include <math.h>

template <class T> class CellArray
{
	public:

		struct Lock
		{
			int Count;
			T **pItems;
			} ExternalLock;

	protected:

		Vector Min;
		float DXCell, DYCell;
		int XCells, YCells;
		float RefZ;
		struct Cell
		{
			int Count;
			T **pItems;
			} *pCells;

		Lock InternalLock;

	public:

		CellArray(int Count, T *pItems, float ReferenceZ, float XTol, float YTol) : XCells(0), YCells(0), pCells(0)
		{
			InternalLock.pItems = 0;
			InternalLock.Count = 0;
			ExternalLock = InternalLock;
			RefZ = ReferenceZ;
			DXCell = XTol;
			DYCell = YTol;
			if (Count > 0)
			{
				Vector Max;
				int i;
				Vector *pV = new Vector[Count];
				int *pI = new int[Count];
				Max = Min = pV[0] = pItems[0].Intercept + (RefZ - pItems[0].Intercept.Z) * pItems[0].Slope;
				for (i = 1; i < Count; i++)
				{
					pV[i] = pItems[i].Intercept + (RefZ - pItems[i].Intercept.Z) * pItems[i].Slope;
					if (pV[i].X < Min.X) Min.X = pV[i].X;
					else if (pV[i].X > Max.X) Max.X = pV[i].X;
					if (pV[i].Y < Min.Y) Min.Y = pV[i].Y;
					else if (pV[i].Y > Max.Y) Max.Y = pV[i].Y;
					};
				XCells = floor((Max.X - Min.X) / DXCell + 1.);
				YCells = floor((Max.Y - Min.Y) / DYCell + 1.);
				pCells = (Cell *)malloc(sizeof(Cell) * XCells * YCells);
				int *pC = new int[XCells * YCells];
				for (i = 0; i < XCells * YCells; i++)
				{
					pC[i] = pCells[i].Count = 0;
					pCells[i].pItems = 0;
					};
				for (i = 0; i < Count; i++)
					pCells[pI[i] = floor((pV[i].X - Min.X) / DXCell) + (floor((pV[i].Y - Min.Y) / DYCell) * XCells)].Count++;
				for (i = 0; i < XCells * YCells; i++)
					pCells[i].pItems = (T **)malloc(sizeof(T *) * pCells[i].Count);
				for (i = 0; i < Count; i++)
					pCells[pI[i]].pItems[pC[pI[i]]++] = &pItems[i];

				delete [] pC;
				delete [] pI;
				delete [] pV;
				};
			};

		virtual ~CellArray()
		{
			Unlock();
			if (pCells)
			{
				int i;
				for (i = 0; i < (XCells * YCells); i++)
					if (pCells[i].pItems) free(pCells[i].pItems);
				free(pCells);
				};
			};

		bool Lock(T &Item)
		{
			Unlock();
			Vector V = Item.Intercept + (RefZ - Item.Intercept.Z) * Item.Slope;
			int cx, cy, i, ix, iy;
			cx = (V.X - Min.X) / DXCell;
			cy = (V.Y - Min.Y) / DYCell;
			if (cx < -1 || cx > XCells) return false;
			if (cy < -1 || cy > YCells) return false;
			static int ConnectivityMatrix[9][2] = 
			{
				{0, 0}, {-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}
				};
			for (i = 0; i < 9; i++)
			{
				ix = cx + ConnectivityMatrix[i][0];
				iy = cy + ConnectivityMatrix[i][1];
				if (ix >= 0 && ix < XCells && iy >= 0 && iy < YCells)
					InternalLock.Count += pCells[ix + iy * XCells].Count;
				};
			if (!InternalLock.Count) return false;
			InternalLock.pItems = (T **)malloc(sizeof(T *) * InternalLock.Count);
			InternalLock.Count = 0;
			for (i = 0; i < 9; i++)
			{
				ix = cx + ConnectivityMatrix[i][0];
				iy = cy + ConnectivityMatrix[i][1];
				if (ix >= 0 && ix < XCells && iy >= 0 && iy < YCells)
				{
					int n = pCells[ix + iy * XCells].Count;
					memcpy(&InternalLock.pItems[InternalLock.Count], pCells[ix + iy * XCells].pItems, sizeof(T *) * n);
					InternalLock.Count += n;
					};
				};
			
			ExternalLock = InternalLock;
			return true;
			};
		
		void Unlock()
		{
			if (InternalLock.pItems)
			{
				free(InternalLock.pItems);
				InternalLock.pItems = 0;
				InternalLock.Count = 0;
				};
			ExternalLock = InternalLock;
			};

	};

#endif