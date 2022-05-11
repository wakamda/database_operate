///////////////////////////////////////////////////////////
//  DBDataType.h
//  Original author: wakamda
//  Basic data type of the data in table
///////////////////////////////////////////////////////////
#ifndef _DBDATATYPE_H_
#define _DBDATATYPE_H_

#include <vector>
#include <map>
#include <string.h>

enum TABLE_DATA_TYPE {
	TABLE_DATA_TYPE_DECIMAL,
	TABLE_DATA_TYPE_TINY,
	TABLE_DATA_TYPE_SHORT,
	TABLE_DATA_TYPE_LONG,
	TABLE_DATA_TYPE_FLOAT,
	TABLE_DATA_TYPE_DOUBLE,
	TABLE_DATA_TYPE_NULL,
	TABLE_DATA_TYPE_TIMESTAMP,
	TABLE_DATA_TYPE_LONGLONG,
	TABLE_DATA_TYPE_INT24,
	TABLE_DATA_TYPE_DATE,
	TABLE_DATA_TYPE_TIME,
	TABLE_DATA_TYPE_DATETIME,
	TABLE_DATA_TYPE_YEAR,
	TABLE_DATA_TYPE_NEWDATE, /**< Internal to MySQL. Not used in protocol */
	TABLE_DATA_TYPE_VARCHAR,
	TABLE_DATA_TYPE_BIT,
	TABLE_DATA_TYPE_TIMESTAMP2,
	TABLE_DATA_TYPE_DATETIME2, /**< Internal to MySQL. Not used in protocol */
	TABLE_DATA_TYPE_TIME2,     /**< Internal to MySQL. Not used in protocol */
	TABLE_DATA_TYPE_JSON = 245,
	TABLE_DATA_TYPE_NEWDECIMAL = 246,
	TABLE_DATA_TYPE_ENUM = 247,
	TABLE_DATA_TYPE_SET = 248,
	TABLE_DATA_TYPE_TINY_BLOB = 249,
	TABLE_DATA_TYPE_MEDIUM_BLOB = 250,
	TABLE_DATA_TYPE_LONG_BLOB = 251,
	TABLE_DATA_TYPE_BLOB = 252,
	TABLE_DATA_TYPE_VAR_STRING = 253,
	TABLE_DATA_TYPE_STRING = 254,
	TABLE_DATA_TYPE_GEOMETRY = 255
};

//table data struct type
struct Table_Data
{  
	Table_Data(const char* data = 0)
	{
		this->type = TABLE_DATA_TYPE_STRING;
		if (!data)return;
		this->data = data;
		this->size = (unsigned int)strlen(data);
	}
	Table_Data(const uint32_t *d)
	{
		this->type = TABLE_DATA_TYPE_LONG;
		this->data = (const char*)d;
		this->size = sizeof(uint32_t);
	}
	const char * data = 0;
	unsigned int size = 0;
	TABLE_DATA_TYPE type;
};

//插入和更新数据的数据结构,string字段名称,Table_Data字段数据
typedef std::map <std::string, Table_Data>		TableDataMap;

//存放数据库内一行数据的容器，容器元素为每个域的值
typedef std::vector<Table_Data>					ROW;

#endif //_DBDATATYPE_H_