// FragmentLinkerClass.h : Declaration of the CFragmentLinkerClass

#ifndef __FRAGMENTLINKERCLASS_H_
#define __FRAGMENTLINKERCLASS_H_

#include "resource.h"       // main symbols
#include "ConfigData.h"	// Added by ClassView
#include "..\Common\datastructs.h"

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
	void CleanViews(VS_View &v, VS_View &w, bool IsSame);
	void * pContext;
	FragmentLinkerConfigData C;
	IO_CS_SS_Tracks Tks;
	UINT CurrentMaxTracks;

	UINT (*pLoadCallback)(void *pContext, UINT Index, IO_VS_Fragment **ppFrag);
	UINT (*pSaveCallback)(void *pContext, IO_CS_SS_Tracks *pTracks);
	void (*pProgressCallback)(void *pContext, float Percent);
	bool (*pStopCallback)(void *pContext);
	bool LinkViews(VS_View &v, VS_View &w);
private:
	bool ShouldStop;
};

#endif //__FRAGMENTLINKERCLASS_H_
