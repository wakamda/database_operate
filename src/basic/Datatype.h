///////////////////////////////////////////////////////////
//  Datatype.h
//  Original author: wakamda
//  Basic data type of the Ctmysql SDK
///////////////////////////////////////////////////////////
#ifndef _DATATYPE_H
#define _DATATYPE_H

#include <string>
#include <string.h>
#include <vector>

// error number
typedef enum{
    ERR_SUCCESS = 0,
    ERR_FAILED,
    ERR_UNSUPPORT_CONNAND,
    ERR_INVALID_ARG,
    ERR_INVALID_DATA
}ERR_CODE;

/***********table************/
// table data type
enum TABLE_DATA_TYPE{
    _INT = 0,
    _VARCHAR
};

//table type
typedef enum{
    UTF8 = 0,
    GBK,
    NOTYPE
}TABLE_TYPE;

//table config
typedef struct{
    std::string fieldname;
    TABLE_DATA_TYPE data_type;
    TABLE_TYPE table_type;
    int len = 0;
}TABLESTRUCT, *LPTABLESTRUCT;

//table constrcuction used for create table
typedef std::vector<TABLESTRUCT>   TABLEVECTOR;

/***********table************/

#endif 