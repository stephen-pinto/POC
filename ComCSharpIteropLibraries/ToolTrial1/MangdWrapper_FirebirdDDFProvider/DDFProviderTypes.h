#ifndef __DDFPROVIDER_TYPES_HEADER
#define __DDFPROVIDER_TYPES_HEADER

#include <objbase.h>
#include <algorithm>
#include "DDFProviderCollectionTypes.h"
#pragma once

enum DATA_BASE_TYPES
{
	T_CHAR,
	T_BOOL,
	T_INT16,
	T_INT32,
	T_INT64,
	T_FLOAT,
	T_DOUBLE,
	T_DECIMAL,
	T_DATE,
	T_TIME,
	T_TIMESTAMP,
	T_STRING,
	T_VARCHAR,
	T_BLOB,
	T_UNKNOWN
};

enum CONSTRAINT_TYPE
{
	CONSTRAINT_PRIMARY_KEY,
	CONSTRAINT_FOREIGN_KEY,
	CONSTRAINT_NONE
};

struct BasicFieldInfo
{
	std::string ColumnName;
	DATA_BASE_TYPES DataType;
	short FieldLength;
	short FieldScale;
	short FieldPrecision;
	std::string FieldCharset;
};

struct TableColumnInfo : BasicFieldInfo
{
	bool IsNotNull = false;
	bool IsUniqueField = false;
	bool IsAutoIncrement = false;
	CONSTRAINT_TYPE Constraint;
};

struct StoredProcedureInfo
{
	TypedDataCollection<BasicFieldInfo> InputFields;
	TypedDataCollection<BasicFieldInfo>  OutputFields;
};

template <typename T>
struct DDFProviderHandle
{
	std::string DBConnectionString;
	std::string ServerAddress;
	std::string DatabaseName;
	std::string UserName;
	std::string Password;
	T DBConnectionObj;
	DDFProviderHandle(std::string server_address, std::string db_name, std::string user_name, std::string password)
	{
		this->ServerAddress = server_address;
		this->DatabaseName = db_name;
		this->UserName = user_name;
		this->Password = password;
	}
};

template <typename T>
struct DDFTransactionHandle
{
	T DBTransactionObject;
};
#endif