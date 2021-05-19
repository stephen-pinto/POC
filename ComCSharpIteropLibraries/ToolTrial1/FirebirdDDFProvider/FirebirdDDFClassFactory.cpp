#include "FirebirdDDFClassFactory.h"

FirebirdDDFClassFactory1::FirebirdDDFClassFactory1()
{
	this->m_cRef = 1;
}

FirebirdDDFClassFactory1::~FirebirdDDFClassFactory1()
{}

HRESULT __stdcall FirebirdDDFClassFactory1::QueryInterface(REFIID riid, void **ppvObject)
{
	if (riid == IID_IUnknown || riid == IID_IClassFactory)
	{
		*ppvObject = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppvObject)->AddRef();
	return S_OK;
}

ULONG __stdcall FirebirdDDFClassFactory1::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

ULONG __stdcall FirebirdDDFClassFactory1::Release()
{
	if (InterlockedDecrement(&m_cRef) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_cRef;
}

HRESULT __stdcall FirebirdDDFClassFactory1::CreateInstance(IUnknown* pUnknownOuter, REFIID iid, void **ppv)
{
	if (pUnknownOuter != NULL)
	{
		return CLASS_E_NOAGGREGATION;
	}

	CFirebirdDDFProviderServer1 *p_manger = new CFirebirdDDFProviderServer1;

	if (p_manger == NULL)
	{
		*ppv = NULL;
		return E_OUTOFMEMORY;
	}

	HRESULT hres = p_manger->QueryInterface(iid, ppv);

	return hres;
}

HRESULT __stdcall FirebirdDDFClassFactory1::LockServer(BOOL block)
{
	if (block)
	{
		InterlockedIncrement(&g_Serverlocks);
	}
	else
	{
		InterlockedDecrement(&g_Serverlocks);
	}

	return S_OK;
}

/*Dll functions which are exported*/

STDAPI __stdcall DllCanUnloadNow()
{
	if (g_Components == 0 && g_Serverlocks == 0)
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}
}


STDAPI __stdcall DllGetClassObject(const CLSID& clsid, REFIID iid, void** ppv)
{
	if (clsid != CLSID_FirebirdDDFProvider)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}

	FirebirdDDFClassFactory1 *pFactoryObj = new FirebirdDDFClassFactory1;

	if (pFactoryObj == NULL)
		return E_OUTOFMEMORY;

	HRESULT hres = pFactoryObj->QueryInterface(iid, ppv);
	//pFactoryObj->Release();

	return hres;
}
