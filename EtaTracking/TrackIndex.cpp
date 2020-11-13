// TrackIndex.cpp: implementation of the TrackIndex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "TrackIndex.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define INDEXIDLEN 12
static const char IndexId[INDEXIDLEN] = "TkIndexFile";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TrackIndex::TrackIndex(unsigned tagallocblock, unsigned trackallocblock)
: TagAllocBlock(tagallocblock), TrackAllocBlock(trackallocblock), pTags(0), pIndex(0)
{
	if (!TagAllocBlock) TagAllocBlock = 128;
	if (!TrackAllocBlock) TrackAllocBlock = 8;
	CurrTags = CurrIndices = 0;
	pTags = (TrackIndex::ClusterTag *)malloc(sizeof(TrackIndex::ClusterTag) * (MaxTags = TagAllocBlock));
	pIndex = (TrackIndex::IndexItem *)malloc(sizeof(TrackIndex::IndexItem) * (MaxIndices = TrackAllocBlock));
	};

TrackIndex::~TrackIndex()
{
	if (pTags) free(pTags);
	if (pIndex) free(pIndex);
	};

bool TrackIndex::AddTrack(Identifier &id, float XCenter, float YCenter, Track &T, float ZRef, TrackIndex::ClusterTag *ptags)
{
	if ((CurrTags + T.PointsN) > MaxTags)
		pTags = (TrackIndex::ClusterTag *)realloc(pTags, sizeof(TrackIndex::ClusterTag) * (MaxTags += TagAllocBlock));
	memcpy(pTags + CurrTags, ptags, sizeof(TrackIndex::ClusterTag) * T.PointsN);
	IndexItem t;
	t.Id = id;
	t.Sigma = T.Sigma;
	t.Center.X = XCenter;
	t.Center.Y = YCenter;
	t.Pos.X = T.Intercept.X;
	t.Pos.Y = T.Intercept.Y;
	t.Slope.X = T.Slope.X;
	t.Slope.Y = T.Slope.Y;
	t.SpaceAngle = hypot(t.Slope.X, t.Slope.Y);
	t.PointsN = T.PointsN;
	t.FirstZ = T.FirstZ - ZRef;
	t.LastZ = T.LastZ - ZRef;
	t.StartTag = CurrTags;	
	CurrTags += T.PointsN;
	if (CurrIndices >= MaxIndices)
		pIndex = (TrackIndex::IndexItem *)realloc(pIndex, sizeof(TrackIndex::IndexItem) * (MaxIndices += TrackAllocBlock));
	int top = 0;
	int bottom = CurrIndices - 1;
	if (bottom < top) bottom = top;
	while (top < bottom)
	{
		int half = (top + bottom) / 2;
		if (pIndex[half].SpaceAngle == t.SpaceAngle) top = bottom = half;
		else if (pIndex[half].SpaceAngle < t.SpaceAngle) top = half + 1;
		else bottom = half;
		};
	if (CurrIndices && (pIndex[top].SpaceAngle < t.SpaceAngle)) top++;
	if (top < CurrIndices)
		memmove(pIndex + top + 1, pIndex + top, (CurrIndices - top) * sizeof(TrackIndex::IndexItem));
	pIndex[top] = t;
	CurrIndices++;
	return true;
	};

unsigned TrackIndex::FindTrack(float XSlope, float YSlope, float RadAccept, bool Isotropic, unsigned MinPts, float ZTop, float ZBottom, unsigned **pIndices)
{
	unsigned currsel = 0;
	*pIndices = 0;	
	float sl = hypot(XSlope, YSlope);
	float losl = sl - RadAccept, hisl = sl + RadAccept;
	int lolim, hilim, h, l, m;
	l = 0;
	h = CurrIndices - 1;	
	while (l < h)
	{
		m = (l + h) / 2;
		if (pIndex[m].SpaceAngle == losl) 
		{
			h = l = m;
			break;
			};
		if (pIndex[m].SpaceAngle < losl) 
		{
			if ((m + 1 <= h) && pIndex[m + 1].SpaceAngle > losl)
			{
				h = l = (m + 1);
				break;
				}
			l = m + 1;
			}
		else if (pIndex[m].SpaceAngle > losl) h = m - 1;
		if (h < 0) h = 0;
		if (l > h) l = h;		
		};
	lolim = l;
	h = CurrIndices - 1;	
	while (l < h)
	{
		m = (l + h) / 2;
		if (pIndex[m].SpaceAngle == hisl) 
		{
			l = h = m;
			break;
			};
		if (pIndex[m].SpaceAngle < hisl) 
		{
			if ((m + 1 <= h) && pIndex[m + 1].SpaceAngle > hisl)
			{
				h = l = m;
				break;
				}
			l = m + 1;
			}
		else if (pIndex[m].SpaceAngle > hisl) h = m - 1;
		if (h < 0) h = 0;
		if (l > h) l = h;		
		};
	hilim = l;
	if (hilim < lolim) return 0;
	*pIndices = (unsigned *)malloc(sizeof(unsigned) * (hilim - lolim + 1));
	if (Isotropic)
	{		
		for (l = lolim; l <= hilim; l++)
			if (pIndex[l].PointsN >= MinPts && pIndex[l].FirstZ >= ZTop && pIndex[l].LastZ <= ZBottom)
				(*pIndices)[currsel++] = l;
		}
	else
	{
		h = 0;
		for (l = lolim; l <= hilim; l++)
			if (pIndex[l].PointsN >= MinPts && pIndex[l].FirstZ >= ZTop && pIndex[l].LastZ <= ZBottom && 
				hypot(pIndex[l].Slope.X - XSlope, pIndex[l].Slope.Y - YSlope) <= RadAccept)
				(*pIndices)[currsel++] = l;
		};
	if (!currsel) free(*pIndices);
	return currsel;
	};

void TrackIndex::FreeIndices(unsigned *pIndices)
{
	free(pIndices);
	};

bool TrackIndex::Save(char *FileName) 
{
	if (!FileName[0]) return false;
	FILE *f = fopen(FileName, "wb");
	if (!f) return false;	
	try
	{
		if (fwrite(IndexId, INDEXIDLEN, 1, f) != 1) throw 0;
		if (fwrite(&CurrTags, sizeof(CurrTags), 1, f) != 1) throw 1;
		if (fwrite(&CurrIndices, sizeof(CurrIndices), 1, f) != 1) throw 2;
		if (fwrite(pTags, sizeof(TrackIndex::ClusterTag), CurrTags, f) != CurrTags) throw 3;
		if (fwrite(pIndex, sizeof(TrackIndex::IndexItem), CurrIndices, f) != CurrIndices) throw 4;		
		}
	catch (...)
	{
		fclose(f);
		return false;
		};
	fclose(f);
	return true;	
	};

bool TrackIndex::Read(char *FileName) 
{
	if (!FileName[0]) return false;
	FILE *f = fopen(FileName, "rb");
	if (!f) return false;
	TrackIndex::ClusterTag *ptags = 0;
	TrackIndex::IndexItem *pindex = 0;
	unsigned currtags = 0, currindices = 0;	
	try
	{
		char temp[INDEXIDLEN];
		if (fread(temp, INDEXIDLEN, 1, f) != 1) throw 0;
		if (strncmp(temp, IndexId, INDEXIDLEN)) throw 1;
		if (fread(&currtags, sizeof(currtags), 1, f) != 1) throw 2;
		if (fread(&currindices, sizeof(currindices), 1, f) != 1) throw 3;
		if (!(ptags = (TrackIndex::ClusterTag *)malloc(sizeof(TrackIndex::ClusterTag) * currtags))) throw 4;
		if (!(pindex = (TrackIndex::IndexItem *)malloc(sizeof(TrackIndex::IndexItem) * currindices))) throw 5;
		if (fread(ptags, sizeof(TrackIndex::ClusterTag), currtags, f) != currtags) throw 6;
		if (fread(pindex, sizeof(TrackIndex::IndexItem), currindices, f) != currindices) throw 7;
		}
	catch (...)
	{
		if (ptags) free(ptags);
		if (pindex) free(pindex);
		fclose(f);
		return false;
		};
	if (pTags) free(pTags);
	if (pIndex) free(pIndex);
	pTags = ptags;
	pIndex = pindex;
	CurrTags = MaxTags = currtags;
	CurrIndices = MaxIndices = currindices;
	fclose(f);
	return true;
	};

TrackIndex::IndexItem &TrackIndex::operator[](unsigned i) 
{
	return pIndex[i];
	};

TrackIndex::ClusterTag *TrackIndex::Tags(TrackIndex::IndexItem &T)
{
	return pTags + T.StartTag;
	};
