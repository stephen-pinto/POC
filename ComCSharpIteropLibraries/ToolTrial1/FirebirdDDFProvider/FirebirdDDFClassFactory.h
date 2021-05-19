#ifndef __FIREBIRD_DDFCFACTORY_HEADER
#define __FIREBIRD_DDFCFACTORY_HEADER

#include "ComFirebirdDDFProvider.h"

class FirebirdDDFClassFactory1 : IClassFactory
{
public:
	/* IUnknown declaration */
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void **ppvObject);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();

	/* IClassFactory declaration */
	virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, REFIID iid, void **ppv);
	virtual HRESULT __stdcall LockServer(BOOL block);

	/*Constructor & Destructor*/
	FirebirdDDFClassFactory1();
	~FirebirdDDFClassFactory1();

private:
	ULONG m_cRef;
};

/*Base compulsory methods for DLL use*/
STDAPI __stdcall DllGetClassObject(const CLSID& clsid, REFIID iid, void** ppv);
STDAPI __stdcall DllCanUnloadNow();

#endif