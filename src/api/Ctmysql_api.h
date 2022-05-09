///////////////////////////////////////////////////////////
//  Ctmysql_api.h
//  Original author: wakamda
//  Description file of the Ctmysql SDK API
///////////////////////////////////////////////////////////
#ifndef _CTMYSQL_API_H
#define _CTMYSQL_API_H

#include "../basic/Datatype.h"

typedef  void* TMYSQL_HANDLE;

/**
 * @brief mysql connect action.
 * @return ERR_CODE 
 */
ERR_CODE sdk_connectmysql(TMYSQL_HANDLE handle,const char* host,const char* user,const char* pwd,const char* db_name);

/**
 * @brief database create
 * 
 */
ERR_CODE sdk_createdatabase(TMYSQL_HANDLE handle,std::string &dbname);

/**
 * @brief table create
 * 
 */
ERR_CODE sdk_createtable(TMYSQL_HANDLE handle,TABLEVECTOR &vector,std::string &tablename, TABLE_TYPE tabletype);


#endif //_CTMYSQL_API_H
