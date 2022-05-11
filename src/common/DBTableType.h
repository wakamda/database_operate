///////////////////////////////////////////////////////////
//  DbTableType.h
//  Original author: wakamda
//  Basic data type of the table
///////////////////////////////////////////////////////////
#ifndef _DBTABLETYPE_H_
#define _DBTABLETYPE_H_

#include <string>
#include <vector>
#include <map>

//table type
typedef enum{
    UTF8 = 0,
    GBK,
    NOTYPE
}TABLE_CODING_TYPE;

//table field type
enum TABLE_FIELD_TYPE {
	DBTYPE_INT = 0,
	DBTYPE_VARCHAR,
	DBTYPE_DATETIME,
	DBTYPE_BLOB,
	DBTYPE_BINARY,
	DBTYPE_LONGBLOB,
	DBTYPE_MEDIUMBLOB,
	DBTYPE_TINYBLOB,//255
	DBTYPE_VARBINARY,
	DBTYPE_DATA,
	DBTYPE_TIME,
	DBTYPE_TIMESTAMP,
	DBTYPE_YEAR,
	DBTYPE_GEOMETRY,
	DBTYPE_GEOMETRYCOLLECTION,
	DBTYPE_LINESTRING,
	DBTYPE_MULTILINESTRING,
	DBTYPE_MULTIPOINT,
	DBTYPE_POINT,
	DBTYPE_POLYGON,
	DBTYPE_BIGINT,
	DBTYPE_DECIMAL,
	DBTYPE_DOUBLE,
	DBTYPE_FLOAT,
	DBTYPE_MEDIUMINT,
	DBTYPE_REAL,
	DBTYPE_SMALLINT,
	DBTYPE_TINYINT,
	DBTYPE_CHAR,
	DBTYPE_JSON,
	DBTYPE_NCHAR,
	DBTYPE_NVARCHAR,
	DBTYPE_LONGTEXT,
	DBTYPE_MEDIUMTEXT,
	DBTYPE_TEXT,
	DBTYPE_TINYTEXT,
	DBTYPE_BIT,
	DBTYPE_BOOLEAN,
	DBTYPE_ENUM,
	DBTYPE_SET,
	DBTYPE_ID
};

//TABLE_FIELD_TYPE string
static const char *str_table_field_type[41] = {
    "INT",
    "VARCHAR",
    "DATETIME",
    "BLOB",//65K
    "BINARY",
    "LONGBLOB",//4G
    "MEDIUMBLOB",//16MB
    "TINYBLOB",//255
    "VARBINARY",
    "DATA",
    "TIME",
    "TIMESTAMP",
    "YEAR",
    "GEOMETRY",
    "GEOMETRYCOLLECTION",
    "LINESTRING",
    "MULTILINESTRING",
    "MULTIPOINT",
    "POINT",
    "POLYGON",
    "BIGINT",
    "DECIMAL",
    "DOUBLE",
    "FLOAT",
    "MEDIUMINT",
    "REAL",
    "SMALLINT",
    "TINYINT",
    "CHAR",
    "JSON",
    "NCHAR",
    "NVARCHAR",
    "LONGTEXT",
    "MEDIUMTEXT",
    "TEXT",
    "TINYTEXT",
    "BIT",
    "BOOLEAN",
    "ENUM",
    "SET",
    "INT AUTO_INCREMENT"//自增ID
};

//table construct
typedef struct{
    std::string        field_name;
    TABLE_FIELD_TYPE   field_type;
    TABLE_CODING_TYPE  table_coding_type;
    int                field_len = 0;
}TABLESTRUCT, *LPTABLESTRUCT;

//table constrcuction used for create table
typedef std::vector<TABLESTRUCT>   TABLEVECTOR;

//数据列表, 在使用简易查询接口时会一次性获取所有查询的数据。容器内元素为数据库内的一行数据
typedef std::vector<ROW>					ROWS;

#endif //_DBTABLETYPE_H_