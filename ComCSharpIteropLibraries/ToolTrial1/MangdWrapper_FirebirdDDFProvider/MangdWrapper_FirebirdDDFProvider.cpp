// This is the main DLL file.

#include "stdafx.h"
#include "MangdWrapper_FirebirdDDFProvider.h"


void MesssageBoxPrintInt(int x)
{
	const char * str = std::to_string(x).c_str();
	char str2[1024];
	sprintf(str2, "%s %s", "Count is", str);
	MessageBox(NULL, str2, TEXT("Table count"), MB_OK);
}

void MessageBoxPrintString(std::string text)
{
	MessageBox(NULL, text.c_str(), TEXT("Table count"), MB_OK);
}

//#define DEBUG_WINDOW_PRINT(x) OutputDebugStringA(x); OutputDebugStringA("\n");
#define DEBUG_WINDOW_PRINT(x) MessageBoxPrintString(x)

namespace MangdWrapper_FirebirdDDFProvider
{
	FirebirdDDFProviderWrapper::FirebirdDDFProviderWrapper()
	{
		InitializeDDFProviderHandle();
	}

	void FirebirdDDFProviderWrapper::InitializeDDFProviderHandle()
	{
		/*LPCWSTR dll_name = TEXT("FirebirdDDFProvider.dll");
		HINSTANCE hComponent = ::LoadLibrary(dll_name);*/
		LPCSTR dll_name = "FirebirdDDFProvider.dll";
		HINSTANCE hComponent = ::LoadLibrary(dll_name);
		if (hComponent == NULL)
		{
			DEBUG_WINDOW_PRINT("CallCreateInstance: \tError : Cannot load component. With error:");
			std::cout << GetLastError() << std::endl;
		}

		DLLGETCLASSFUNPTR DllGetClassObj = (DLLGETCLASSFUNPTR)::GetProcAddress(hComponent, "DllGetClassObject");

		if (DllGetClassObj == NULL)
		{
			DEBUG_WINDOW_PRINT("GetAddressDllGetClassObj: \tError : Cannot get address of DllGetClassObj.");
		}

		IFirebirdDDFProvider *pICompClient;
		IClassFactory *pFactory;

		HRESULT hres = DllGetClassObj(CLSID_FirebirdDDFProvider, IID_IClassFactory, (void**)&pFactory);
		if (FAILED(hres))
		{
			_com_error err(hres);
			LPCTSTR errMsg = err.ErrorMessage();
			DEBUG_WINDOW_PRINT("DLL calling failed");
			std::cout << GetLastError() << std::endl;
		}
		else
		{
			DEBUG_WINDOW_PRINT("DLL calling successful");
		}

		hres = pFactory->CreateInstance(NULL, IID_IFirebirdDDFProvider, (void**)&pICompClient);
		if (FAILED(hres))
		{
			_com_error err(hres);
			LPCTSTR errMsg = err.ErrorMessage();
			DEBUG_WINDOW_PRINT("Create instance failed");
			std::cout << GetLastError() << std::endl;
		}
		else
		{
			DEBUG_WINDOW_PRINT("Create instance successful");
		}

		this->pDDFProviderHandle = pICompClient;
	}

	System::Type^ FirebirdDDFProviderWrapper::GetManagedType(DATA_BASE_TYPES type)
	{
		switch (type)
		{
		case T_INT16:		return short::typeid;
		case T_INT32:		return System::Int32::typeid;
		case T_FLOAT:		return float::typeid;
		case T_DATE:		return System::DateTime::typeid;
		case T_TIME:		return System::DateTime::typeid;
		case T_CHAR:		return char::typeid;
		case T_INT64:		return System::Int64::typeid;
		case T_DOUBLE:		return double::typeid;
		case T_TIMESTAMP:	return System::DateTime::typeid;
		case T_VARCHAR:		return System::String::typeid;
		case T_STRING:		return System::String::typeid;
		case T_BLOB:		return System::String::typeid;
		case T_UNKNOWN:		//Fall through to default
		default: 			return System::Object::typeid;
		}
	}

	MNGD_CONSTRAINT_TYPES FirebirdDDFProviderWrapper::GetManagedConstraintType(CONSTRAINT_TYPE type)
	{
		switch (type)
		{
			case CONSTRAINT_PRIMARY_KEY:		return MNGD_CONSTRAINT_TYPES::CONSTRAINT_PRIMARY_KEY;			
			case CONSTRAINT_FOREIGN_KEY:		return MNGD_CONSTRAINT_TYPES::CONSTRAINT_FOREIGN_KEY;			
			case CONSTRAINT_NONE:				//Fall through to default		
			default:							return MNGD_CONSTRAINT_TYPES::CONSTRAINT_NONE;			
		}
	}

	FbDBHandle^ FirebirdDDFProviderWrapper::GetDDFProviderHandle(System::String^ ServerAddress, System::String^ DatabaseName, System::String^ UserName, System::String^ Password)
	{
		FbDBHandle^ pfb_handle = gcnew FbDBHandle(ServerAddress, DatabaseName, UserName, Password);
		pfb_handle->DDFHandle = this->pDDFProviderHandle->GetDDFProviderHandle(
			_marshal_context.marshal_as<std::string>(pfb_handle->ServerAddress),
			_marshal_context.marshal_as<std::string>(pfb_handle->DatabaseName),
			_marshal_context.marshal_as<std::string>(pfb_handle->UserName),
			_marshal_context.marshal_as<std::string>(pfb_handle->Password));

		return pfb_handle;
	}

	System::Collections::Generic::List<System::String^>^ FirebirdDDFProviderWrapper::GetAllTablesForDatabase(FbDBHandle^ handle)
	{
		TypedDataCollection<std::string> table_list = this->pDDFProviderHandle->GetListOfTables(handle->DDFHandle);				
		ListString^ list = gcnew ListString();
		for (int indx = 0; indx < table_list.Count; indx++)
			list->Add(_marshal_context.marshal_as<System::String^>(table_list.ElementAt(indx).c_str()));
		return list;
	}

	System::Collections::Generic::List<System::String^>^ FirebirdDDFProviderWrapper::GetAllStoredProcForDatabase(FbDBHandle^ handle)
	{
		TypedDataCollection<std::string> sproc_list = this->pDDFProviderHandle->GetListOfTables(handle->DDFHandle);
		ListString^ list = gcnew ListString();
		for (int indx = 0; indx < sproc_list.Count; indx++)
			list->Add(_marshal_context.marshal_as<System::String^>(sproc_list.ElementAt(indx).c_str()));
		return list;
	}

	System::Collections::Generic::List<System::String^>^ FirebirdDDFProviderWrapper::GetAllViewsForDatabase(FbDBHandle^ handle)
	{
		TypedDataCollection<std::string> views_list = this->pDDFProviderHandle->GetListOfTables(handle->DDFHandle);
		ListString^ list = gcnew ListString();
		for (int indx = 0; indx < views_list.Count; indx++)
			list->Add(_marshal_context.marshal_as<System::String^>(views_list.ElementAt(indx).c_str()));
		return list;
	}

	System::Collections::Generic::List<Managed_TableColumnInfo^>^ FirebirdDDFProviderWrapper::GetColumnInfoForTable(FbDBHandle^ handle, System::String^ TableName)
	{
		System::Collections::Generic::List<Managed_TableColumnInfo^>^ col_info_list = gcnew System::Collections::Generic::List<Managed_TableColumnInfo^>();
		TypedDataCollection<TableColumnInfo> result_info = this->pDDFProviderHandle->GetInfoForTable(
			handle->DDFHandle,
			_marshal_context.marshal_as<std::string>(TableName));
		for (int indx = 0; indx < result_info.Count; indx++)
		{
			Managed_TableColumnInfo^ mngd_col_info = gcnew Managed_TableColumnInfo();
			TableColumnInfo col_info = result_info.ElementAt(indx);
			mngd_col_info->ColumnName = _marshal_context.marshal_as<System::String^>(col_info.ColumnName);
			mngd_col_info->DataType = GetManagedType(col_info.DataType);
			mngd_col_info->FieldLength = col_info.FieldLength;
			mngd_col_info->FieldScale = col_info.FieldScale;
			mngd_col_info->FieldPrecision = col_info.FieldPrecision;
			mngd_col_info->FieldCharset = _marshal_context.marshal_as<System::String^>(col_info.FieldCharset);
			mngd_col_info->IsNotNull = col_info.IsNotNull;
			mngd_col_info->IsUniqueField = col_info.IsUniqueField;
			mngd_col_info->IsAutoIncrement = col_info.IsAutoIncrement;
			mngd_col_info->ConstraintType = GetManagedConstraintType(col_info.Constraint);
			col_info_list->Add(mngd_col_info);
		}
		return col_info_list;
	}

	System::Collections::Generic::List<Managed_TableColumnInfo^>^ FirebirdDDFProviderWrapper::GetColumnInfoForView(FbDBHandle^ handle, System::String^ ViewName)
	{
		System::Collections::Generic::List<Managed_TableColumnInfo^>^ col_info_list = gcnew System::Collections::Generic::List<Managed_TableColumnInfo^>();
		TypedDataCollection<TableColumnInfo> result_info = this->pDDFProviderHandle->GetInfoForTable(
			handle->DDFHandle,
			_marshal_context.marshal_as<std::string>(ViewName));
		for (int indx = 0; indx < result_info.Count; indx++)
		{
			Managed_TableColumnInfo^ mngd_col_info = gcnew Managed_TableColumnInfo();
			TableColumnInfo col_info = result_info.ElementAt(indx);
			mngd_col_info->ColumnName = _marshal_context.marshal_as<System::String^>(col_info.ColumnName);
			mngd_col_info->DataType = GetManagedType(col_info.DataType);
			mngd_col_info->FieldLength = col_info.FieldLength;
			mngd_col_info->FieldScale = col_info.FieldScale;
			mngd_col_info->FieldPrecision = col_info.FieldPrecision;
			mngd_col_info->FieldCharset = _marshal_context.marshal_as<System::String^>(col_info.FieldCharset);
			mngd_col_info->IsNotNull = col_info.IsNotNull;
			mngd_col_info->IsUniqueField = col_info.IsUniqueField;
			mngd_col_info->IsAutoIncrement = col_info.IsAutoIncrement;
			mngd_col_info->ConstraintType = GetManagedConstraintType(col_info.Constraint);
			col_info_list->Add(mngd_col_info);
		}
		return col_info_list;
	}

	Managed_StoredProcedureInfo^ FirebirdDDFProviderWrapper::GetColumnInfoForStoredProc(FbDBHandle^ handle, System::String^ StoredProcName)
	{
		Managed_StoredProcedureInfo^ stored_proc_info = gcnew Managed_StoredProcedureInfo();
		stored_proc_info->InputFields = gcnew System::Collections::Generic::List<Managed_BasicFieldInfo^>();
		stored_proc_info->OutputFields = gcnew System::Collections::Generic::List<Managed_BasicFieldInfo^>();
		StoredProcedureInfo result_info = this->pDDFProviderHandle->GetInfoForStoredProcedure(
			handle->DDFHandle,
			_marshal_context.marshal_as<std::string>(StoredProcName));

		//First we fill input fields
		for (int indx = 0; indx < result_info.InputFields.Count; indx++)
		{
			Managed_BasicFieldInfo^ mngd_col_info = gcnew Managed_BasicFieldInfo();
			BasicFieldInfo col_info = result_info.InputFields.ElementAt(indx);
			mngd_col_info->ColumnName = _marshal_context.marshal_as<System::String^>(col_info.ColumnName);
			mngd_col_info->DataType = GetManagedType(col_info.DataType);
			mngd_col_info->FieldLength = col_info.FieldLength;
			mngd_col_info->FieldScale = col_info.FieldScale;
			mngd_col_info->FieldPrecision = col_info.FieldPrecision;
			mngd_col_info->FieldCharset = _marshal_context.marshal_as<System::String^>(col_info.FieldCharset);
			stored_proc_info->InputFields->Add(mngd_col_info);
		}

		//Now we fill output fields
		for (int indx = 0; indx < result_info.OutputFields.Count; indx++)
		{
			Managed_BasicFieldInfo^ mngd_col_info = gcnew Managed_BasicFieldInfo();
			BasicFieldInfo col_info = result_info.OutputFields.ElementAt(indx);
			mngd_col_info->ColumnName = _marshal_context.marshal_as<System::String^>(col_info.ColumnName);
			mngd_col_info->DataType = GetManagedType(col_info.DataType);
			mngd_col_info->FieldLength = col_info.FieldLength;
			mngd_col_info->FieldScale = col_info.FieldScale;
			mngd_col_info->FieldPrecision = col_info.FieldPrecision;
			mngd_col_info->FieldCharset = _marshal_context.marshal_as<System::String^>(col_info.FieldCharset);
			stored_proc_info->OutputFields->Add(mngd_col_info);
		}

		return stored_proc_info;
	}
}