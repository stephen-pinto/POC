#include "DDFProviderTypes.h"
#include "DDFProviderCollectionTypes.h"

#ifndef __IFIREBIRDDDFPROVIDER_HEADER
#define __IFIREBIRDDDFPROVIDER_HEADER

/*
Interface Declaration
*/

interface IFirebirdDDFProvider : IUnknown
{
public:
	/*Base methods*/
	virtual DDFProviderHandle<void*>* __stdcall GetDDFProviderHandle(const std::string ServerAddress, const std::string DatabaseName, const std::string UserName, const std::string Password) = 0;

	/*Read operations which don't require a commit*/
	virtual TypedDataCollection<std::string> __stdcall GetListOfTables(DDFProviderHandle<void*> *handle) = 0;
	virtual TypedDataCollection<std::string> __stdcall GetListOfStoredProcedures(DDFProviderHandle<void*> *handle) = 0;
	virtual TypedDataCollection<std::string> __stdcall GetListOfViews(DDFProviderHandle<void*> *handle) = 0;


	virtual TypedDataCollection<TableColumnInfo> __stdcall GetInfoForTable(DDFProviderHandle<void*> *handle, const std::string table_name = NULL) = 0;
	virtual TypedDataCollection<TableColumnInfo> __stdcall GetInfoForView(DDFProviderHandle<void*> *handle, const std::string view_name = NULL) = 0;
	virtual StoredProcedureInfo __stdcall GetInfoForStoredProcedure(DDFProviderHandle<void*> *handle, const std::string stored_proc_name = NULL) = 0;

	/*For future*/
	virtual DDFTransactionHandle<void*> __stdcall StartTransaction(DDFProviderHandle<void*> *handle) = 0;
	virtual void __stdcall CommitTransaction(DDFProviderHandle<void*> *handle, DDFTransactionHandle<void*> *transaction) = 0;
	virtual void __stdcall RollbackTransaction(DDFProviderHandle<void*> *handle, DDFTransactionHandle<void*> *transaction) = 0;
};

/*GUIDs for using components*/

// {F58B60E3-BD93-4D45-A7FD-E540B658E49D}
const CLSID CLSID_FirebirdDDFProvider =
{ 0xf58b60e3, 0xbd93, 0x4d45, { 0xa7, 0xfd, 0xe5, 0x40, 0xb6, 0x58, 0xe4, 0x9d } };


// {89661D59-2D98-47AB-B27C-1825580DD951}
static const IID IID_IFirebirdDDFProvider
{ 0x89661d59, 0x2d98, 0x47ab, { 0xb2, 0x7c, 0x18, 0x25, 0x58, 0xd, 0xd9, 0x51 } };

#endif