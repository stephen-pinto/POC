// MangdWrapper_FirebirdDDFProvider.h
#include "IFirebirdDDFProvider.h"
#include "UnmanagedTypesGeneral.h"
#include "ManagedTypesForDDFProvider.h"
#include <msclr\marshal_cppstd.h>

#pragma once
using namespace MangdTypes_FirebirdDDFProvider;
using ListString = System::Collections::Generic::List<System::String^>;

namespace MangdWrapper_FirebirdDDFProvider {

	public ref class FirebirdDDFProviderWrapper
	{
		private:
			IFirebirdDDFProvider *pDDFProviderHandle = NULL;
			msclr::interop::marshal_context _marshal_context;

			void InitializeDDFProviderHandle();
			System::Type^ GetManagedType(DATA_BASE_TYPES type);
			MNGD_CONSTRAINT_TYPES FirebirdDDFProviderWrapper::GetManagedConstraintType(CONSTRAINT_TYPE type);

		public:

			FirebirdDDFProviderWrapper();

			FbDBHandle^ GetDDFProviderHandle(System::String^ ServerAddress, System::String^ DatabaseName, System::String^ UserName, System::String^ Password);

			System::Collections::Generic::List<System::String^>^ GetAllTablesForDatabase(FbDBHandle^ handle);

			System::Collections::Generic::List<System::String^>^ GetAllStoredProcForDatabase(FbDBHandle^ handle);

			System::Collections::Generic::List<System::String^>^ GetAllViewsForDatabase(FbDBHandle^ handle);

			System::Collections::Generic::List<Managed_TableColumnInfo^>^ GetColumnInfoForTable(FbDBHandle^ handle, System::String^ TableName);

			System::Collections::Generic::List<Managed_TableColumnInfo^>^ GetColumnInfoForView(FbDBHandle^ handle, System::String^ ViewName);

			Managed_StoredProcedureInfo^ GetColumnInfoForStoredProc(FbDBHandle^ handle, System::String^ StoredProcName);
	};
}
