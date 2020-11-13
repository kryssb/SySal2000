#ifndef _SYSAL_ROOT_INTERFACE_
#define _SYSAL_ROOT_INTERFACE_ 1

#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"
#include "SySalROOTs.h"

class TSySalTLG : public TObject
{
protected:

	TTree *pHeader;
	TTree *pBaseTracks;
	TTree *pTopTracks;
	TTree *pBottomTracks;

	TFile *pFile;

public:

	inline TTree *GetHeader() { return pHeader; }
	inline TTree *GetBaseTracks() { return pBaseTracks; }
	inline TTree *GetTopTracks() { return pTopTracks; }
	inline TTree *GetBottomTracks() { return pBottomTracks; }
	inline TFile *GetFile() { return pFile; }

	enum TLGFormat { tlgFmtOld = 0x08, tlgFmtOld2 = 0x02, tlgFmtNoExtents = 0x01, tlgFmtNormal = 0x03, tlgFmtNormalWithIndex = 0x04, tlgFmtNormalDoubleWithIndex = 0x05 };

	TSySalTLG(TFile *pfile);
	virtual ~TSySalTLG();

	bool LoadTLG(char *tlgfilename);
	bool SaveTLG(char *tlgfilename, int number = 0);

	ClassDef(TSySalTLG, 1);
};

class TSySalRWD : public TObject
{
protected:

	TTree *pHeader;
	TTree *pViews;
	TTree *pTopLayers;
	TTree *pBottomLayers;
	TTree *pTopTracks;
	TTree *pBottomTracks;
	TTree *pTopGrains;
	TTree *pBottomGrains;

	TFile *pFile;

public:

	inline TTree *GetHeader() { return pHeader; }
	inline TTree *GetViews() { return pViews; }
	inline TTree *GetTopLayers() { return pTopLayers; }
	inline TTree *GetBottomLayers() { return pBottomLayers; }
	inline TTree *GetTopTracks() { return pTopTracks; }
	inline TTree *GetBottomTracks() { return pBottomTracks; }
	inline TTree *GetTopGrains() { return pTopGrains; }
	inline TTree *GetBottomGrains() { return pBottomGrains; }
	inline TFile *GetFile() { return pFile; }

	enum RWDFormat { rwdFmtOld = 0x0701, rwdFmtNormal = 0x0702, rwdFmtNormalDouble = 0x0703 };

	enum RWDGrainCompression { rwdGCNull = 0, rwdGCSuppressed = 0x0102 };

	TSySalRWD(TFile *pfile);
	virtual ~TSySalRWD();

	bool LoadRWD(char *rwdfilename);
	bool SaveRWD(char *rwdfilename, int number = 0);

	ClassDef(TSySalRWD, 1);
};

class TSySalTSR : public TObject
{
protected:

	TTree *pHeader;
	TTree *pLayers;
	TTree *pSegments;
	TTree *pTracks;
	TTree *pTrackSegments;
	TTree *pVertices;
	TTree *pVertexTracks;

	TFile *pFile;

public:

	inline TTree *GetHeader() { return pHeader; }
	inline TTree *GetLayers() { return pLayers; }
	inline TTree *GetSegments() { return pSegments; }
	inline TTree *GetTracks() { return pTracks; }
	inline TTree *GetTrackSegments() { return pTrackSegments; }
	inline TTree *GetVertices() { return pVertices; }
	inline TTree *GetVertexTracks() { return pVertexTracks; }
	inline TFile *GetFile() { return pFile; }

	enum TSRFormat { tsrFmtNormalDouble = 0x0401, tsrFmtNormal = 0x0400 };

	TSySalTSR(TFile *pfile);
	virtual ~TSySalTSR();

	bool LoadTSR(char *tsrfilename);
	bool SaveTSR(char *tsrfilename, int number = 0);

	ClassDef(TSySalTSR, 1);
};

#endif
