#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "IFirebirdDDFProvider.h"
#include "DDFProviderTypes.h"

#define DEBUG_WINDOW_PRINT(x) OutputDebugStringA(x); OutputDebugStringA("\n");

extern "C"
{
	typedef HRESULT(__stdcall *DLLGETCLASSFUNPTR)(const CLSID& clsid, REFIID iid, void** ppv);
}

void print(const CHAR* msg)
{
	std::cout << msg << std::endl;		
}

int main()
{
	LPCWSTR dll_name = TEXT("FirebirdDDFProvider.dll");
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
		_getch();
		return 1;
	}

	IFirebirdDDFProvider *pICompClient;
	IClassFactory *pFactory;

	HRESULT hres = DllGetClassObj(CLSID_FirebirdDDFProvider, IID_IClassFactory, (void**)&pFactory);
	if (FAILED(hres))
	{
		_com_error err(hres);
		LPCTSTR errMsg = err.ErrorMessage();
		MessageBox(NULL, errMsg, TEXT("Error"), MB_OK);
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
		MessageBox(NULL, errMsg, TEXT("Error"), MB_OK);
		DEBUG_WINDOW_PRINT("Create instance failed");
		std::cout << GetLastError() << std::endl;
	}
	else
	{
		DEBUG_WINDOW_PRINT("Create instance successful");
	}

	//DDFProviderHandle<void*>* db_handle = pICompClient->GetDDFProviderHandle("localhost", "D:\\Database\\gpser.gdb", "SYSDBA", "masterkey");
	DDFProviderHandle<void*>* db_handle = pICompClient->GetDDFProviderHandle("localhost", "D:\\WORK\\first_test_project\\PurchaseOrderProjectSept_1 (1)\\EASYPO.FDB", "SYSDBA", "masterkey");
	TypedDataCollection<std::string> table_list = pICompClient->GetListOfTables(db_handle);

	/*DEBUG_WINDOW_PRINT("Printing table list on console : ");
	print("List count is :");
	print(std::to_string(table_list.Count).c_str());*/

	for (int i = 0; i < table_list.Count; i++)
	{
		print(table_list.ElementAt(i).c_str());
	}
	
	//table_list.Clear();
	
	//table_list = pICompClient->GetListOfStoredProcedures(db_handle);
	//DEBUG_WINDOW_PRINT("Printing store procedure list on console : ");
	//print("List count is " + table_list.Count);

	//for (int i = 0; i < table_list.Count; i++)
	//{
	//	print(table_list.ElementAt(i).c_str());
	//}

	/*table_list.Clear();
	table_list = pICompClient->GetListOfViews(db_handle);

	DEBUG_WINDOW_PRINT("Printing views list on console : ");
	print("List count is " + table_list.Count);

	for (int i = 0; i < table_list.Count; i++)
	{
		print(table_list.ElementAt(i).c_str());
	}*/

	print("\n+++++++++++++++++++++++++++++++\n");

	//TypedDataCollection<TableColumnInfo> table_col_info_list = pICompClient->GetInfoForTable(db_handle, table_list.ElementAt(5));
	TypedDataCollection<TableColumnInfo> table_col_info_list = pICompClient->GetInfoForTable(db_handle, "ITEM");

	DEBUG_WINDOW_PRINT("Printing table details for table : ");
	
	std::cout << "List count for table " << table_list.ElementAt(6) << " is : " << std::to_string(table_col_info_list.Count);
	//std::cout<< std::to_string(table_col_info_list.Count).c_str());

	print("");
	print("");

	for (int i = 0; i < table_col_info_list.Count; i++)
	{
		std::cout << " Column Name: " << table_col_info_list.ElementAt(i).ColumnName.c_str();
		//std::cout << " \tChar-set: " << table_col_info_list.ElementAt(i).FieldCharset.c_str();		
		//std::cout << " \tData Type: " << std::to_string(table_col_info_list.ElementAt(i).DataType).c_str();
		//std::cout << " \tData length: " << std::to_string(table_col_info_list.ElementAt(i).FieldLength).c_str();
		if (table_col_info_list.ElementAt(i).Constraint == CONSTRAINT_PRIMARY_KEY)
			std::cout << " \tConstraint : " << "Primary Key";
		else if (table_col_info_list.ElementAt(i).Constraint == CONSTRAINT_FOREIGN_KEY)
			std::cout << " \tConstraint : " << "Foreign Key";
		else if (table_col_info_list.ElementAt(i).Constraint == CONSTRAINT_NONE)
			std::cout << " \tConstraint : " << "No constraint";

		std::cout << std::endl;
	}

	_getch();
	return 0;
}