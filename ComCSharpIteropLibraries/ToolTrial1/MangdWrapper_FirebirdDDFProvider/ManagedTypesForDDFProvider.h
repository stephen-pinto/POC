#include <conio.h>
#include <iostream>

namespace MangdTypes_FirebirdDDFProvider
{
	public enum class MNGD_CONSTRAINT_TYPES
	{
		CONSTRAINT_PRIMARY_KEY,
		CONSTRAINT_FOREIGN_KEY,
		CONSTRAINT_NONE
	};

	public ref class FbDBHandle
	{
	public:
		System::String^ DBConnectionString;
		System::String^ ServerAddress;
		System::String^ DatabaseName;
		System::String^ UserName;
		System::String^ Password;
		DDFProviderHandle<void*>* DDFHandle;

		FbDBHandle(System::String^ server_address, System::String^ db_name, System::String^ user_name, System::String^ password)
		{
			this->ServerAddress = server_address;
			this->DatabaseName = db_name;
			this->UserName = user_name;
			this->Password = password;
		}

		FbDBHandle(System::String^ connection_string)
		{
			this->DBConnectionString = connection_string;
		}
	};

	public ref struct Managed_BasicFieldInfo
	{
		System::String^ ColumnName;
		System::Type^ DataType;
		short FieldLength;
		short FieldScale;
		short FieldPrecision;
		System::String^ FieldCharset;
	};

	public ref struct Managed_TableColumnInfo : Managed_BasicFieldInfo
	{
		bool IsNotNull = false;
		bool IsUniqueField = false;
		bool IsAutoIncrement = false;
		MNGD_CONSTRAINT_TYPES ConstraintType;
	};

	public ref struct Managed_StoredProcedureInfo
	{
		System::Collections::Generic::List<Managed_BasicFieldInfo^>^ InputFields;
		System::Collections::Generic::List<Managed_BasicFieldInfo^>^  OutputFields;
	};
}