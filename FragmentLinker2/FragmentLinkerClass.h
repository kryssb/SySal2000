// FragmentLinkerClass.h : Declaration of the CFragmentLinkerClass

#ifndef __FRAGMENTLINKERCLASS_H_
#define __FRAGMENTLINKERCLASS_H_

#include "resource.h"       // main symbols
#include "ConfigData.h"	// Added by ClassView
#include "..\Common\datastructs.h"

#pragma pack(push)
#pragma pack(2)

struct IntTrack
{
	short PointsN;
	bool Valid;
	TVector Intercept;
	TVector Slope;
	float Sigma;
	};

struct IntCell
{
	UINT TCount;
	union t_Tracks
	{
		IntTrack **p;
		UINT *i;
		} pTracks;
	};

struct IntView
{
	UINT TCount[2];
	IntTrack *pTracks[2];
	IntCell *pCells[2];
	UINT TileX;
	float MinX[2], MinY[2];
	USHORT CellsX[2], CellsY[2];
	float ZBase[2];
	float ZExt[2];
	};

struct IntFragment
{
	FILE *f;
	UINT VCount;
	UINT Index;
	IntView *pViews;
	};

struct IntTileLine
{
	UINT VCount;
	UINT FCount;
	IntFragment *pEncFrags;
	};

#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////
// CFragmentLinkerClass
class ATL_NO_VTABLE CFragmentLinkerClass : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFragmentLinkerClass, &CLSID_FragmentLinker>,
	public IFragmentLinker
{
public:
	CFragmentLinkerClass();

DECLARE_REGISTRY_RESOURCEID(IDR_FRAGMENTLINKERCLASS)
DECLARE_NOT_AGGREGATABLE(CFragmentLinkerClass)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFragmentLinkerClass)
	COM_INTERFACE_ENTRY(IFragmentLinker)
END_COM_MAP()

// IFragmentLinker
public:
	STDMETHOD(SetConfig)(FragmentLinkerConfigData *pConfig);
	STDMETHOD(GetConfig)(FragmentLinkerConfigData *pConfig);
	STDMETHOD(SetCallbacks)(BYTE *pContext, BYTE *pLoadCallback, BYTE *pSaveCallback, BYTE *pProgressCallback, BYTE *pStopCallback);
	STDMETHOD(Link)(BYTE *pIO_VS_Catalog);

protected:

	IntFragment *pFragmentEdges;

	int EncodeFragment(IO_VS_Fragment *pFrag, IntTileLine *pTileLine, int TileLine, UINT XViews);
	bool SaveFragment(IntFragment *pEncFrag);
	bool LoadFragment(IntFragment *pEncFrag);
	bool FlushFragmentFromMemory(IntFragment *pEncFrag);
	bool DeleteFragment(IntFragment *pEncFrag);
	bool ResetFragment(IntFragment *pEncFrag);

	bool LoadTileLine(IO_VS_Catalog *pCat, IntTileLine *pTileLines, int TileLine, bool *pFragLoaded);

	void CleanViews(IntView &v, IntView &w);
	void LinkViews(IntView &v, IntView &w, bool IsSame);

	void * pContext;
	FragmentLinkerConfigData C;
	IO_CS_SS_Tracks Tks;
	UINT CurrentMaxTracks;

	UINT (*pLoadCallback)(void *pContext, UINT Index, IO_VS_Fragment **ppFrag);
	UINT (*pSaveCallback)(void *pContext, IO_CS_SS_Tracks *pTracks);
	void (*pProgressCallback)(void *pContext, float Percent);
	bool (*pStopCallback)(void *pContext);

private:
	bool ShouldStop;
};

#endif //__FRAGMENTLINKERCLASS_H_
