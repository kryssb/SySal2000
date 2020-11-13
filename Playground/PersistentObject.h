// PersistentObject.h: interface for the CPersistentObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERSISTENTOBJECT_H__B7306D20_7392_11D3_A47B_FD22ED367B20__INCLUDED_)
#define AFX_PERSISTENTOBJECT_H__B7306D20_7392_11D3_A47B_FD22ED367B20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Common\SySalObj2.h"

class CPersistentObject  
{
protected:
	void InternalCopy(CPersistentObject &X);

public:
	void ResetConnections(unsigned number);

	struct XPersistentObject
	{
		int Type;

		XPersistentObject(int type = 0) : Type(type) {};
		XPersistentObject(XPersistentObject &X) : Type(X.Type) {};
		XPersistentObject &operator=(XPersistentObject &X) { Type = X.Type; };
		};

	ConnectionName * pConnections;
	int CountOfConnections;
	CPoint Position;
	ConnectionName Name;
	ISySalObject *iObject;
	HICON HIcon;
	CLSID clsId;
	char ConfigName[SYSAL_MAXCONFIG_NAME_LEN];

	CPersistentObject() throw(XPersistentObject);
	CPersistentObject(CPersistentObject &X) throw(XPersistentObject);
	CPersistentObject(CLSID &rCLSID) throw(XPersistentObject);
	virtual ~CPersistentObject();

	CPersistentObject &operator=(CPersistentObject &X);

private:
	HINSTANCE HDLLInstance;
	static HRESULT SySal_CoGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv, HINSTANCE *pHInst);
};

#endif // !defined(AFX_PERSISTENTOBJECT_H__B7306D20_7392_11D3_A47B_FD22ED367B20__INCLUDED_)
