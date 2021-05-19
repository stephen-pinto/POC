#include "CommonHeaders.h"
#include "ComFirebirdDDFProvider.h"
#include "StandardQueries1.h"
#include "ibp/ibpp.h"
#include <iostream>
#include "UtilityClass.h"

CFirebirdDDFProviderServer1::CFirebirdDDFProviderServer1()
{
	this->m_cRef = 1;
	InterlockedIncrement(&g_Components);
}

CFirebirdDDFProviderServer1::~CFirebirdDDFProviderServer1()
{
	InterlockedDecrement(&g_Components);
}

HRESULT __stdcall CFirebirdDDFProviderServer1::QueryInterface(REFIID riid, void **ppvObject)
{
	if (riid == IID_IUnknown)
		*ppvObject = static_cast<IFirebirdDDFProvider *>(this);
	else if (riid == IID_IFirebirdDDFProvider)
		*ppvObject = static_cast<IFirebirdDDFProvider *>(this);
	else
	{
		*ppvObject = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppvObject)->AddRef();
	return(S_OK);
}
ULONG __stdcall CFirebirdDDFProviderServer1::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CFirebirdDDFProviderServer1::Release()
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

DDFProviderHandle<void*>* __stdcall CFirebirdDDFProviderServer1::GetDDFProviderHandle(const std::string ServerAddress, const std::string DatabaseName, const std::string UserName, const std::string Password)
{
	try
	{
		DDFProviderHandle<void*> *handle = new DDFProviderHandle<void*>(ServerAddress, DatabaseName, UserName, Password);
		return handle;
	}
	catch (IBPP::Exception& e)
	{
		std::cout << e.ErrorMessage();
		return NULL;
	}
}

TypedDataCollection<std::string> __stdcall CFirebirdDDFProviderServer1::GetListOfTables(DDFProviderHandle<void*> *handle)
{
	TypedDataCollection<std::string> table_list;
	try
	{
		if (handle == NULL)
			return table_list;

		IBPP::Database db_handle = IBPP::DatabaseFactory(handle->ServerAddress, handle->DatabaseName, handle->UserName, handle->Password);
		IBPP::Transaction transaction_obj = IBPP::TransactionFactory(db_handle);
		IBPP::Statement statement_obj = IBPP::StatementFactory((db_handle), transaction_obj);
		
		(db_handle)->Connect();
		(transaction_obj)->Start();
		
		statement_obj->Execute(Q_TABLE_LIST);
		while (statement_obj->Fetch())
		{
			std::string table_name;
			statement_obj->Get(1, table_name);
			table_list.Add(UtilClass::TrimString(table_name));
		}
		(transaction_obj)->Rollback();
		(db_handle)->Disconnect();
	}
	catch (IBPP::Exception& e)
	{
		std::cout << e.ErrorMessage();
		table_list.Clear();
	}	
	return table_list;
}

TypedDataCollection<std::string> __stdcall CFirebirdDDFProviderServer1::GetListOfStoredProcedures(DDFProviderHandle<void*> *handle)
{
	TypedDataCollection<std::string> stored_proc_list;
	try
	{
		if (handle == NULL)
			return stored_proc_list;

		IBPP::Database db_handle = IBPP::DatabaseFactory(handle->ServerAddress, handle->DatabaseName, handle->UserName, handle->Password);
		IBPP::Transaction transaction_obj = IBPP::TransactionFactory(db_handle);
		IBPP::Statement statement_obj = IBPP::StatementFactory((db_handle), transaction_obj);

		(db_handle)->Connect();
		(transaction_obj)->Start();

		statement_obj->Execute(Q_STORED_PROCEDURE_LIST);
		while (statement_obj->Fetch())
		{
			std::string sp_name;
			statement_obj->Get(1, sp_name);
			stored_proc_list.Add(UtilClass::TrimString(sp_name));
		}

		(transaction_obj)->Rollback();
		(db_handle)->Disconnect();
	}
	catch (IBPP::Exception& e)
	{
		std::cout << e.ErrorMessage();
		stored_proc_list.Clear();
	}
	return stored_proc_list;
}

TypedDataCollection<std::string> __stdcall CFirebirdDDFProviderServer1::GetListOfViews(DDFProviderHandle<void*> *handle)
{
	TypedDataCollection<std::string> views_list;
	try
	{
		if (handle == NULL)
			return views_list;

		IBPP::Database db_handle = IBPP::DatabaseFactory(handle->ServerAddress, handle->DatabaseName, handle->UserName, handle->Password);
		IBPP::Transaction transaction_obj = IBPP::TransactionFactory(db_handle);
		IBPP::Statement statement_obj = IBPP::StatementFactory((db_handle), transaction_obj);

		(db_handle)->Connect();
		(transaction_obj)->Start();

		statement_obj->Execute(Q_VIEWS_LIST);
		while (statement_obj->Fetch())
		{
			std::string view_name;
			statement_obj->Get(1, view_name);
			views_list.Add(UtilClass::TrimString(view_name));
		}

		(transaction_obj)->Rollback();
		(db_handle)->Disconnect();
	}
	catch (IBPP::Exception& e)
	{
		std::cout << e.ErrorMessage();
		views_list.Clear();
	}
	return views_list;
}

TypedDataCollection<TableColumnInfo> __stdcall CFirebirdDDFProviderServer1::GetInfoForTable(DDFProviderHandle<void*> *handle, const std::string table_name)
{
	TypedDataCollection<TableColumnInfo> column_list;
	try
	{
		if (handle == NULL)
			return column_list;

		if (UtilClass::IsStringNullOrEmpty(table_name))
			return column_list;

		IBPP::Database db_handle = IBPP::DatabaseFactory(handle->ServerAddress, handle->DatabaseName, handle->UserName, handle->Password);
		IBPP::Transaction transaction_obj = IBPP::TransactionFactory(db_handle);
		IBPP::Statement statement_obj = IBPP::StatementFactory((db_handle), transaction_obj);

		(db_handle)->Connect();
		(transaction_obj)->Start();

		std::string q_string = Q_TABLE_FIELD_LIST;
		q_string = q_string.replace(q_string.find(TABLE_NAME), (TABLE_NAME.size()), UtilClass::TrimString(table_name));
		statement_obj->Execute(q_string);

		while (statement_obj->Fetch())
		{
			TableColumnInfo col_info;
			std::string field_name;
			short field_type;
			short field_length;
			short field_scale;
			short field_precision;
			short field_charset_id;
			short field_not_null;
			std::string field_constraint;
			std::string field_charset_name;

			statement_obj->Get(1, field_name); col_info.ColumnName = UtilClass::TrimString(field_name);
			statement_obj->Get(2, field_type); col_info.DataType = GetTypeOfDBType(field_type);
			statement_obj->Get(3, field_length); col_info.FieldLength = field_length;
			statement_obj->Get(4, field_scale); col_info.FieldScale = field_scale;
			statement_obj->Get(5, field_precision); col_info.FieldPrecision = field_precision;
			statement_obj->Get(6, field_charset_id); 
			statement_obj->Get(7, field_charset_name); col_info.FieldCharset = UtilClass::TrimString(field_charset_name);
			statement_obj->Get(8, field_not_null); col_info.IsNotNull = field_not_null == 1 ? true : false;
			statement_obj->Get(9, field_constraint); col_info.IsUniqueField = field_constraint.empty() ? false : true; col_info.Constraint = GetConstraintType(field_constraint);

			column_list.Add(col_info);
		}

		(transaction_obj)->Rollback();
		(db_handle)->Disconnect();
	}
	catch (IBPP::Exception& e)
	{
		std::cout << e.ErrorMessage();
		column_list.Clear();
	}
	return column_list;
}

TypedDataCollection<TableColumnInfo> __stdcall CFirebirdDDFProviderServer1::GetInfoForView(DDFProviderHandle<void*> *handle, const std::string view_name)
{
	TypedDataCollection<TableColumnInfo> column_list;
	try
	{
		if (handle == NULL)
			return column_list;

		if (UtilClass::IsStringNullOrEmpty(view_name))
			return column_list;

		IBPP::Database db_handle = IBPP::DatabaseFactory(handle->ServerAddress, handle->DatabaseName, handle->UserName, handle->Password);
		IBPP::Transaction transaction_obj = IBPP::TransactionFactory(db_handle);
		IBPP::Statement statement_obj = IBPP::StatementFactory((db_handle), transaction_obj);

		(db_handle)->Connect();
		(transaction_obj)->Start();

		std::string q_string = Q_TABLE_FIELD_LIST;
		q_string = q_string.replace(q_string.find(TABLE_NAME), (TABLE_NAME.size()), UtilClass::TrimString(view_name));
		statement_obj->Execute(q_string);

		while (statement_obj->Fetch())
		{
			TableColumnInfo col_info;
			std::string field_name;
			short field_type;
			short field_length;
			short field_scale;
			short field_precision;
			short field_charset_id;
			short field_not_null;
			std::string field_constraint;
			std::string field_charset_name;

			statement_obj->Get(1, field_name); col_info.ColumnName = UtilClass::TrimString(field_name);
			statement_obj->Get(2, field_type); col_info.DataType = GetTypeOfDBType(field_type);
			statement_obj->Get(3, field_length); col_info.FieldLength = field_length;
			statement_obj->Get(4, field_scale); col_info.FieldScale = field_scale;
			statement_obj->Get(5, field_precision); col_info.FieldPrecision = field_precision;
			statement_obj->Get(6, field_charset_id);
			statement_obj->Get(7, field_charset_name); col_info.FieldCharset = UtilClass::TrimString(field_charset_name);
			statement_obj->Get(8, field_not_null); col_info.IsNotNull = field_not_null == 1 ? true : false;
			statement_obj->Get(9, field_constraint); col_info.IsUniqueField = field_constraint.empty() ? false : true; col_info.Constraint = GetConstraintType(field_constraint);
			column_list.Add(col_info);
		}

		(transaction_obj)->Rollback();
		(db_handle)->Disconnect();
	}
	catch (IBPP::Exception& e)
	{
		std::cout << e.ErrorMessage();
		column_list.Clear();
	}
	return column_list;
}

StoredProcedureInfo __stdcall CFirebirdDDFProviderServer1::GetInfoForStoredProcedure(DDFProviderHandle<void*> *handle, const std::string stored_proc_name)
{
	StoredProcedureInfo sp_info;
	try
	{
		if (handle == NULL)
			return sp_info;

		if (UtilClass::IsStringNullOrEmpty(stored_proc_name))
			return sp_info;

		IBPP::Database db_handle = IBPP::DatabaseFactory(handle->ServerAddress, handle->DatabaseName, handle->UserName, handle->Password);
		IBPP::Transaction transaction_obj = IBPP::TransactionFactory(db_handle);
		IBPP::Statement statement_obj = IBPP::StatementFactory((db_handle), transaction_obj);

		(db_handle)->Connect();
		(transaction_obj)->Start();

		std::string q_string = Q_STORED_PROCEDURE_FIELD_LIST;
		q_string = q_string.replace(q_string.find(STORED_PROCEDURE_NAME), (STORED_PROCEDURE_NAME.size()), UtilClass::TrimString(stored_proc_name));
		statement_obj->Execute(q_string);

		while (statement_obj->Fetch())
		{
			short ip_or_op = -1;
			if (statement_obj->Get(8, ip_or_op))
			{
				BasicFieldInfo fld_info;
				std::string field_name;
				short field_type;
				short field_length;
				short field_scale;
				short field_precision;
				short field_charset_id;
				std::string field_charset_name;

				statement_obj->Get(1, field_name); fld_info.ColumnName = UtilClass::TrimString(field_name);
				statement_obj->Get(2, field_type); fld_info.DataType = GetTypeOfDBType(field_type);
				statement_obj->Get(3, field_length); fld_info.FieldLength = field_length;
				statement_obj->Get(4, field_scale); fld_info.FieldScale = field_scale;
				statement_obj->Get(5, field_precision); fld_info.FieldPrecision = field_precision;
				statement_obj->Get(6, field_charset_id);
				statement_obj->Get(7, field_charset_name); fld_info.FieldCharset = UtilClass::TrimString(field_charset_name);								
				
				if (ip_or_op == 0)
					sp_info.InputFields.Add(fld_info);
				else if (ip_or_op == 1)
					sp_info.OutputFields.Add(fld_info);
			}			
		}

		(transaction_obj)->Rollback();
		(db_handle)->Disconnect();
	}
	catch (IBPP::Exception& e)
	{
		std::cout << e.ErrorMessage();		
	}
	return sp_info;
}

DDFTransactionHandle<void*> __stdcall CFirebirdDDFProviderServer1::StartTransaction(DDFProviderHandle<void*> *handle)
{
	throw std::bad_exception("Method not implemented yet");
}

void __stdcall CFirebirdDDFProviderServer1::CommitTransaction(DDFProviderHandle<void*> *handle, DDFTransactionHandle<void*> *transaction)
{
	throw std::bad_exception("Method not implemented yet");
}

void __stdcall CFirebirdDDFProviderServer1::RollbackTransaction(DDFProviderHandle<void*> *handle, DDFTransactionHandle<void*> *transaction)
{
	throw std::bad_exception("Method not implemented yet");
}

DATA_BASE_TYPES CFirebirdDDFProviderServer1::GetTypeOfDBType(short db_type)
{
	switch (db_type)
	{
	case 7:
		return T_INT16;
		break;
	case 8:
		return T_INT32;
		break;
	case 10:
	case 11:
		return T_FLOAT;
		break;
	case 12:
		return T_DATE;
		break;
	case 13:
		return T_TIME;
		break;
	case 14:
		return T_CHAR;
		break;
	case 16:
		return T_INT64;
		break;
	case 27:
		return T_DOUBLE;
		break;
	case 35:
		return T_TIMESTAMP;
		break;
	case 37:
		return T_VARCHAR;
		break;
	case 40:
		return T_STRING;
		break;
	case 261:
		return T_BLOB;
		break;
	default:
		return T_UNKNOWN;
		break;
	}
}

CONSTRAINT_TYPE CFirebirdDDFProviderServer1::GetConstraintType(std::string constraint_string)
{
	//std::cout << std::endl << UtilClass::TrimEnds(constraint_string) << std::endl;
	if (constraint_string.empty())
		return CONSTRAINT_NONE;
	else if (UtilClass::TrimString(PRIMARY_KEY_CONST).compare(UtilClass::TrimString(constraint_string)) == 0)
		return CONSTRAINT_PRIMARY_KEY;
	else if (UtilClass::TrimString(FOREIGN_KEY_CONST).compare(UtilClass::TrimString(constraint_string)) == 0)
		return CONSTRAINT_FOREIGN_KEY;
	else
		return CONSTRAINT_NONE;
}
