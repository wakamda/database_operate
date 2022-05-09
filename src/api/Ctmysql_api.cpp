///////////////////////////////////////////////////////////
//  Ctmysql_api.h
//  Original author: wakamda
//  Implements file of the Ctmysql SDK API
///////////////////////////////////////////////////////////
#include "Ctmysql_api.h"
#include "../mysql/Ctmysql/Ctmysql.h"

ERR_CODE sdk_connectmysql(TMYSQL_HANDLE handle,const char* host,const char* user,const char* pwd,const char* db_name){
    return ((Ctmysql*)handle)->connectmysql(host, user, pwd, db_name);
}

ERR_CODE sdk_createdatabase(TMYSQL_HANDLE handle,std::string &dbname){
    return ((Ctmysql*)handle)->createdatabase(dbname);
}

ERR_CODE sdk_createtable(TMYSQL_HANDLE handle,TABLEVECTOR &vector,std::string &tablename, TABLE_TYPE tabletype){
    return ((Ctmysql*)handle)->createtable(vector, tablename, tabletype);
}