// TrackIndex.h: interface for the TrackIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACKINDEX_H__E13C62A1_F599_11D3_BF87_002018B80960__INCLUDED_)
#define AFX_TRACKINDEX_H__E13C62A1_F599_11D3_BF87_002018B80960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Common\Track.h"
#include "..\Common\id.h"

class TrackIndex 
{
public:

#pragma pack(push)
#pragma pack(1)
	struct ClusterTag
	{
		unsigned short Plane;
		unsigned InPlaneIndex;
		};

	struct IndexItem
	{	
		Identifier Id;
		float Sigma;
		struct t_V2
		{
			float X, Y;
			} Pos, Slope, Center;
		unsigned PointsN;	
		float SpaceAngle;
		float FirstZ, LastZ;
		unsigned StartTag;
		};
#pragma pack(pop)

	TrackIndex(unsigned tagallocblock = 3000, unsigned trackallocblock = 100);
	virtual ~TrackIndex();

	bool AddTrack(Identifier &id, float XCenter, float YCenter, Track &T, float ZRef, TrackIndex::ClusterTag *ptags);
	unsigned FindTrack(float XSlope, float YSlope, float RadAccept, bool Isotropic, unsigned MinPts, float ZTop, float ZBottom, unsigned **pIndices);
	void FreeIndices(unsigned *pIndices);
	bool Save(char *FileName);
	bool Read(char *FileName);
	TrackIndex::IndexItem &operator[](unsigned i);
	TrackIndex::ClusterTag *Tags(TrackIndex::IndexItem &T);

protected:

	unsigned TagAllocBlock;
	unsigned TrackAllocBlock;
	unsigned CurrTags, MaxTags;
	unsigned CurrIndices, MaxIndices;
	ClusterTag *pTags;
	IndexItem *pIndex;
};

#endif // !defined(AFX_TRACKINDEX_H__E13C62A1_F599_11D3_BF87_002018B80960__INCLUDED_)
