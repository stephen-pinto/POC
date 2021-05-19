#ifndef __COM_FIREBIRD_DDFPROVIDER_HEADER
#define __COM_FIREBIRD_DDFPROVIDER_HEADER

#include "IFirebirdDDFProvider.h"
#include "DDFProviderCollectionTypes.h"
#include <Windows.h>
#include <comdef.h>
#include <objbase.h>

#pragma once

/*Global variables*/
static long g_Components = 0;
static long g_Serverlocks = 0;
static HANDLE g_hModule;

/*Our main class for this com component*/

class CFirebirdDDFProviderServer1 : IFirebirdDDFProvider
{
public:
	/* IUnknown declaration */
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void **ppvObject);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();

	/* Constructor and destructor */
	CFirebirdDDFProviderServer1();
	~CFirebirdDDFProviderServer1();

	/* IFirebirdDDFProvider declaration */

	virtual DDFProviderHandle<void*>* __stdcall GetDDFProviderHandle(const std::string ServerAddress, const std::string DatabaseName, const std::string UserName, const std::string Password);
	virtual TypedDataCollection<std::string> __stdcall GetListOfTables(DDFProviderHandle<void*> *handle);
	virtual TypedDataCollection<std::string> __stdcall GetListOfStoredProcedures(DDFProviderHandle<void*> *handle);
	virtual TypedDataCollection<std::string> __stdcall GetListOfViews(DDFProviderHandle<void*> *handle);

	virtual TypedDataCollection<TableColumnInfo> __stdcall GetInfoForView(DDFProviderHandle<void*> *handle, const std::string view_name = NULL);
	virtual TypedDataCollection<TableColumnInfo> __stdcall GetInfoForTable(DDFProviderHandle<void*> *handle, const std::string table_name = NULL);
	virtual StoredProcedureInfo __stdcall GetInfoForStoredProcedure(DDFProviderHandle<void*> *handle, const std::string stored_proc_name = NULL);

	virtual DDFTransactionHandle<void*> __stdcall StartTransaction(DDFProviderHandle<void*> *handle);
	virtual void __stdcall CommitTransaction(DDFProviderHandle<void*> *handle, DDFTransactionHandle<void*> *transaction);
	virtual void __stdcall RollbackTransaction(DDFProviderHandle<void*> *handle, DDFTransactionHandle<void*> *transaction);	

private:
	ULONG m_cRef;

	/*Local usable methods*/	
	DATA_BASE_TYPES CFirebirdDDFProviderServer1::GetTypeOfDBType(short db_type);
	CONSTRAINT_TYPE CFirebirdDDFProviderServer1::GetConstraintType(std::string constraint_string);
};

#endif