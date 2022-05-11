///////////////////////////////////////////////////////////
//  Ctmysql_api.h
//  Original author: wakamda
//  Implements file of the Ctmysql SDK API
///////////////////////////////////////////////////////////
#include "DB_sdk_api.h"
#include "../mysql/Ctmysql.h"

ERR_CODE CHECKHANDLE(TMYSQL_HANDLE handle){
    if(handle == NULL)
        return ERR_INVALID_ARG;
}

TMYSQL_HANDLE sdk_Init(){
    Basic_db* instance = new Ctmysql();
    instance->Init();
    if(instance == NULL)
    {
        std::cout << "sdk init failed! Can not create instance!\n" << std::endl;
    }
    std::cout << "sdk init success! Instance = " << instance << std::endl;
    return reinterpret_cast<TMYSQL_HANDLE>(instance);
}

ERR_CODE sdk_Finit(TMYSQL_HANDLE handle){
    CHECKHANDLE(handle);
    Basic_db *phandle = reinterpret_cast<Ctmysql*>(handle);
	phandle->Finit();
	delete phandle;
	handle = NULL;
	printf("release instance success handle = %p\n", handle);
	return ERR_SUCCESS;
}

ERR_CODE sdk_connectdb(TMYSQL_HANDLE handle,const char* host,const char* user,const char* pwd,const char* db_name,unsigned short port,unsigned long flag){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->connectdb(host, user, pwd, db_name,port,flag);
}

ERR_CODE sdk_SwitchDBType(TMYSQL_HANDLE handle,TABLE_CODING_TYPE type){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->SwitchDBType(type);
}

ERR_CODE sdk_SetMysqlOption(TMYSQL_HANDLE handle,MSQL_OPT opt,const void* arg){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->SetMysqlOption(opt,arg);
}

ERR_CODE sdk_SetConnectTimeout(TMYSQL_HANDLE handle,int sec){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->SetConnectTimeout(sec);
}

ERR_CODE sdk_SetReconnect(TMYSQL_HANDLE handle,bool isre){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->SetReconnect(isre);
}

char* sdk_Gethost(TMYSQL_HANDLE handle){
    return ((Basic_db*)handle)->Gethost();
}

char* sdk_Sethost(TMYSQL_HANDLE handle,char* newVal){
    return ((Basic_db*)handle)->Sethost(newVal);
}

char* sdk_Getuser(TMYSQL_HANDLE handle){
    return ((Basic_db*)handle)->Getuser();
}

char* sdk_Setuser(TMYSQL_HANDLE handle,char* newVal){
    return ((Basic_db*)handle)->Setuser(newVal);
}

char* sdk_Getpwd(TMYSQL_HANDLE handle){
    return ((Basic_db*)handle)->Getpwd();
}

char* sdk_Setpwd(TMYSQL_HANDLE handle,char* newVal){
    return ((Basic_db*)handle)->Setpwd(newVal);
}

char* sdk_Getdbname(TMYSQL_HANDLE handle){
    return ((Basic_db*)handle)->Getdbname();
}

char* sdk_Setdbname(TMYSQL_HANDLE handle,char* newVal){
    return ((Basic_db*)handle)->Setdbname(newVal);
}

unsigned short sdk_Getport(TMYSQL_HANDLE handle){
    return ((Basic_db*)handle)->Getport();
}

unsigned short sdk_Setport(TMYSQL_HANDLE handle,unsigned short newVal){
    return ((Basic_db*)handle)->Setport(newVal);
}

unsigned long sdk_Getflag(TMYSQL_HANDLE handle){
    return ((Basic_db*)handle)->Getflag();
}

unsigned long sdk_Setflag(TMYSQL_HANDLE handle,unsigned long newVal){
    return ((Basic_db*)handle)->Setflag(newVal);
}

/************************************************************************
 *  operation
************************************************************************/

bool sdk_Query(TMYSQL_HANDLE handle,const char* sql, unsigned long sqllen){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->Query(sql,sqllen);
}

ERR_CODE sdk_createdatabase(TMYSQL_HANDLE handle,std::string dbname){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->createdatabase(dbname);
}

ERR_CODE sdk_deletedatabase(TMYSQL_HANDLE handle,std::string dbname){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->deletedatabase(dbname);
}

ERR_CODE sdk_createtable(TMYSQL_HANDLE handle,TABLEVECTOR &vector,std::string tablename, TABLE_CODING_TYPE tablecodingtype){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->createtable(vector, tablename, tablecodingtype);
}

ERR_CODE sdk_deletetable(TMYSQL_HANDLE handle,std::string tablename){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->deletetable(tablename);
}

ERR_CODE sdk_Insert(TMYSQL_HANDLE handle,TableDataMap &da, std::string tablename){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->Insert(da,tablename);
}

ERR_CODE sdk_DeleteDataWithId(TMYSQL_HANDLE handle,std::string tablename, std::string idname, std::string idnum){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->DeleteDataWithId(tablename,idname,idnum);
}

ERR_CODE sdk_DeleteDataLikeWithFieldname(TMYSQL_HANDLE handle,std::string tablename, std::string fieldname, std::string fielddata){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->DeleteDataLikeWithFieldname(tablename,fieldname,fielddata);
}

uint64_t sdk_UpdateData(TMYSQL_HANDLE handle,TableDataMap &da, std::string tablename, std::string where, std::string idnum){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->UpdateData(da,tablename,where,idnum);
}

ERR_CODE sdk_SelectFromTable(TMYSQL_HANDLE handle,std::string tablename){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->SelectFromTable(tablename);
}

ERR_CODE sdk_SelectDataWithX(TMYSQL_HANDLE handle,std::string tablename, std::string fieldname, std::string fielddata){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->SelectDataWithX(tablename,fieldname,fielddata);
}

ERR_CODE sdk_StoreResult(TMYSQL_HANDLE handle){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->StoreResult();
}

ERR_CODE sdk_UseResult(TMYSQL_HANDLE handle){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->UseResult();
}

ERR_CODE sdk_FreeResult(TMYSQL_HANDLE handle){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->FreeResult();
}

ROW sdk_FetchRow(TMYSQL_HANDLE handle, ROW &row){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->FetchRow();
}

ERR_CODE sdk_EasySelect(TMYSQL_HANDLE handle,std::string tablename, ROWS &rows){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->EasySelect(tablename,rows);
}

ERR_CODE sdk_EasyLike(TMYSQL_HANDLE handle,std::string tablename, std::string fieldname,std::string fielddata, ROWS &rows){
    CHECKHANDLE(handle);
    return ((Basic_db*)handle)->EasyLike(tablename,fieldname,fielddata,rows);
}