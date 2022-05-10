///////////////////////////////////////////////////////////
//  Ctmysql_api.h
//  Original author: wakamda
//  Implements file of the Ctmysql SDK API
///////////////////////////////////////////////////////////
#include "Ctmysql_api.h"
#include "../basic/Basic_db.h"
#include "../mysql/Ctmysql.h"

ERR_CODE Init(){
    return ERR_SUCCESS;
}

ERR_CODE Finit(){
    return ERR_SUCCESS;
}

TMYSQL_HANDLE sdk_createinstance(){
    Basic_db* instance = new Ctmysql();
    instance->Init();
    if(instance == NULL)
    {
        cout << "create failed!\n" << endl;
    }
    return reinterpret_cast<TMYSQL_HANDLE>(instance);
}

ERR_CODE sdk_connectdb(TMYSQL_HANDLE handle,const char* host,const char* user,const char* pwd,const char* db_name){
    return ((Basic_db*)handle)->connectdb(host, user, pwd, db_name);
}

ERR_CODE sdk_createdatabase(TMYSQL_HANDLE handle,std::string &dbname){
    return ((Basic_db*)handle)->createdatabase(dbname);
}

ERR_CODE sdk_createtable(TMYSQL_HANDLE handle,TABLEVECTOR &vector,std::string &tablename, TABLE_TYPE tabletype){
    return ((Basic_db*)handle)->createtable(vector, tablename, tabletype);
}