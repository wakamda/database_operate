///////////////////////////////////////////////////////////
//  DB_sdk_api.h
//  Original author: wakamda
//  Description file of the DB SDK API
///////////////////////////////////////////////////////////
#ifndef _DB_SDK_API_H
#define _DB_SDK_API_H

#include "../common/Datatype.h"
#include "../mysql/Ctmysql.h"
#include "../basic/Log.h"

#define ERROR_NO_ERROR                 (0)
#define ERROR_UNKOWN_ERROR             (-1)
#define ERROR_API_PARAM_INVALID        (-2)
#define ERROR_INTERNEL_PARAM_INVALID   (-3)
#define ERROR_CREATE_CONNECTION_ERR    (-4)


typedef enum{
    LOG_VERBOSE    = 0x00, /*!< VERBOSE */
    LOG_DEBUG      = 0x01, /*!< DEBUG  */
    LOG_INFO       = 0x03, /*!< INFO  */ 
    LOG_WARN       = 0x04, /*!< WARN  */
    LOG_ERROR      = 0x05, /*!< ERROR  */
    LOG_FATAL      = 0x06, /*!< FATAL  */
}DoipLogLevel_t;

typedef  void* TMYSQL_HANDLE;

/************************************************************************
 *  config
************************************************************************/

int SetLogLevel(int level);

int GetLogLevel(void);

/**
 * @brief create a instance for database
 * 
 * @return TMYSQL_HANDLE 
 */
TMYSQL_HANDLE sdk_Init();

/**
 * @brief release
 * 
 * @param handle 
 * @return ERR_CODE 
 */
ERR_CODE sdk_Finit(TMYSQL_HANDLE handle);

/**
 * @brief connection
 * 
 * @param handle 
 * @param host 
 * @param user 
 * @param pwd 
 * @param db_name 
 * @param port 
 * @param flag 
 * @return ERR_CODE 
 */
ERR_CODE sdk_connectdb(TMYSQL_HANDLE handle,const char* host,const char* user,const char* pwd,const char* db_name,unsigned short port,unsigned long flag = 0);

/**
 * @brief Set the database encoding format
 * 
 * @param handle 
 * @param type 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SwitchDBType(TMYSQL_HANDLE handle,TABLE_CODING_TYPE type = UTF8);

/**
 * @brief Set additional connection options in mysql
 * 
 * @param handle 
 * @param opt 
 * @param arg 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SetMysqlOption(TMYSQL_HANDLE handle,MSQL_OPT opt,const void *arg);

/**
 * @brief Set the connect timeout seconds
 * 
 * @param handle 
 * @param sec 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SetConnectTimeout(TMYSQL_HANDLE handle,int sec);

/**
 * @brief Automatic reconnection, not automatic by default
 * 
 * @param handle 
 * @param isre 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SetReconnect(TMYSQL_HANDLE handle,bool isre);

/**
 * @brief Get host name
 * 
 * @param handle 
 * @return char* 
 */
char* sdk_Gethost(TMYSQL_HANDLE handle);

/**
 * @brief set host name
 * 
 * @param handle 
 * @param newVal 
 * @return char* 
 */
char* sdk_Sethost(TMYSQL_HANDLE handle,char* newVal);

/**
 * @brief get username
 * 
 * @param handle 
 * @return char* 
 */
char* sdk_Getuser(TMYSQL_HANDLE handle);

/**
 * @brief set username
 * 
 * @param handle 
 * @param newVal 
 * @return char* 
 */
char* sdk_Setuser(TMYSQL_HANDLE handle,char* newVal);

/**
 * @brief get password
 * 
 * @param handle 
 * @return char* 
 */
char* sdk_Getpwd(TMYSQL_HANDLE handle);

/**
 * @brief set password
 * 
 * @param handle 
 * @param newVal 
 * @return char* 
 */
char* sdk_Setpwd(TMYSQL_HANDLE handle,char* newVal);

/***/
char* sdk_Getdbname(TMYSQL_HANDLE handle);

/**
 * @brief set database name
 * 
 * @param handle 
 * @param newVal 
 * @return char* 
 */
char* sdk_Setdbname(TMYSQL_HANDLE handle,char* newVal);

/**
 * @brief 
 * 
 * @param handle 
 * @return unsigned short 
 */
unsigned short sdk_Getport(TMYSQL_HANDLE handle);

/**
 * @brief set connection port
 * 
 * @param handle 
 * @param newVal 
 * @return unsigned short 
 */
unsigned short sdk_Setport(TMYSQL_HANDLE handle,unsigned short newVal);

/**
 * @brief 
 * 
 * @param handle 
 * @return unsigned long 
 */
unsigned long sdk_Getflag(TMYSQL_HANDLE handle);

/**
 * @brief set connection flag
 * 
 * @param handle 
 * @param newVal 
 * @return unsigned long 
 */
unsigned long sdk_Setflag(TMYSQL_HANDLE handle,unsigned long newVal);

/************************************************************************
 *  operation
************************************************************************/

/**
 * @brief Query SQL(can not parse sql with bin sql)
 * 
 * @param handle 
 * @param sql 
 * @param sqllen 
 * @return true 
 * @return false 
 */
bool sdk_Query(TMYSQL_HANDLE handle,const char*sql, unsigned long sqllen = 0);

/**
 * @brief create database
 * 
 * @param handle 
 * @param dbname 
 * @return ERR_CODE 
 */
ERR_CODE sdk_createdatabase(TMYSQL_HANDLE handle,std::string dbname);

/**
 * @brief delete database
 * 
 * @param handlestd 
 * @param dbname 
 * @return ERR_CODE 
 */
ERR_CODE sdk_deletedatabase(TMYSQL_HANDLE handle,std::string dbname);

/**
 * @brief create table
 * 
 * @param handle 
 * @param vector 
 * @param tablename 
 * @param tablecodingtype 
 * @return ERR_CODE 
 */
ERR_CODE sdk_createtable(TMYSQL_HANDLE handle,TABLEVECTOR &vector,std::string tablename, TABLE_CODING_TYPE tablecodingtype = UTF8);

/**
 * @brief delete table
 * 
 * @param handle 
 * @param tablename 
 * @return ERR_CODE 
 */
ERR_CODE sdk_deletetable(TMYSQL_HANDLE handle,std::string tablename);

/**
 * @brief data insert 
 * 
 * @param handle 
 * @param da 
 * @param tablename 
 * @return ERR_CODE 
 */
ERR_CODE sdk_Insert(TMYSQL_HANDLE handle,TableDataMap &da, std::string tablename);

/**
 * @brief data delete with id
 * 
 * @param handle 
 * @param tablename 
 * @param idname 
 * @param idnum 
 * @return RR_CODE 
 */
ERR_CODE sdk_DeleteDataWithId(TMYSQL_HANDLE handle,std::string tablename, std::string idname, std::string idnum);

/**
 * @brief delete data where fieldname like ...
 * 
 * @param handle 
 * @param tablename 
 * @param fieldname 
 * @param fielddata 
 * @return ERR_CODE 
 */
ERR_CODE sdk_DeleteDataLikeWithFieldname(TMYSQL_HANDLE handle,std::string tablename, std::string fieldname, std::string fielddata);

/**
 * @brief update data
 * 
 * @param handle 
 * @param da 
 * @param tablename 
 * @param where 
 * @param idnum 
 * @return UINT64 
 */
uint64_t sdk_UpdateData(TMYSQL_HANDLE handle,TableDataMap &da, std::string tablename, std::string where, std::string idnum);

/**
 * @brief select table
 * 
 * @param handle 
 * @param tablename 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SelectFromTable(TMYSQL_HANDLE handle,std::string tablename);

/**
 * @brief select data where like...
 * 
 * @param handle 
 * @param tablename 
 * @param fieldname 
 * @param fielddata 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SelectDataWithX(TMYSQL_HANDLE handle,std::string tablename, std::string fieldname, std::string fielddata);

/**
 * @brief select data returns all results
 * 
 * @param handle 
 * @return ERR_CODE 
 */
ERR_CODE sdk_StoreResult(TMYSQL_HANDLE handle);

/**
 * @brief Start receiving results, Fetch via Fetch
 * 
 * @param handle 
 * @return ERR_CODE 
 */
ERR_CODE sdk_UseResult(TMYSQL_HANDLE handle);

/**
 * @brief Frees the space occupied by the result set
 * 
 * @param handle 
 * @return ERR_CODE 
 */
ERR_CODE sdk_FreeResult(TMYSQL_HANDLE handle);

/**
 * @brief receive a row data
 * 
 * @param handle 
 * @return ROW 
 */
ROW sdk_FetchRow(TMYSQL_HANDLE handle, ROW &row);

/**
 * @brief Simple interface, return select data results, each call to clean up the last result set
 * 
 * @param handle 
 * @param tablename 
 * @param rows 
 * @return ERR_CODE 
 */
ERR_CODE sdk_EasySelect(TMYSQL_HANDLE handle,std::string tablename, ROWS &rows);

/**
 * @brief Simple interface, fuzzy search
 * 
 * @param handle 
 * @param tablename 
 * @param fieldname 
 * @param fielddata 
 * @param rows 
 * @return ERR_CODE 
 */
ERR_CODE sdk_EasyLike(TMYSQL_HANDLE handle,std::string tablename, std::string fieldname,std::string fielddata, ROWS &rows);



#endif //_CTMYSQL_API_H
