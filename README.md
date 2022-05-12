# database-moudle
## mysql
Mysql API:
```c++
config:

TMYSQL_HANDLE sdk_Init();

ERR_CODE sdk_Finit(TMYSQL_HANDLE handle);

ERR_CODE sdk_connectdb(TMYSQL_HANDLE handle,const char* host,const char* user,const char* pwd,const char* db_name,unsigned short port,unsigned long flag = 0);

ERR_CODE sdk_SwitchDBType(TMYSQL_HANDLE handle,TABLE_CODING_TYPE type = UTF8);

ERR_CODE sdk_SetMysqlOption(TMYSQL_HANDLE handle,MSQL_OPT opt,const void *arg);

ERR_CODE sdk_SetConnectTimeout(TMYSQL_HANDLE handle,int sec);

ERR_CODE sdk_SetReconnect(TMYSQL_HANDLE handle,bool isre);

char* sdk_Gethost(TMYSQL_HANDLE handle);

char* sdk_Sethost(TMYSQL_HANDLE handle,char* newVal);

...

operation:

bool sdk_Query(TMYSQL_HANDLE handle,const char*sql, unsigned long sqllen = 0);

ERR_CODE sdk_createdatabase(TMYSQL_HANDLE handle,std::string dbname);

ERR_CODE sdk_deletedatabase(TMYSQL_HANDLE handle,std::string dbname);

ERR_CODE sdk_createtable(TMYSQL_HANDLE handle,TABLEVECTOR &vector,std::string tablename, TABLE_CODING_TYPE tablecodingtype = UTF8);

ERR_CODE sdk_deletetable(TMYSQL_HANDLE handle,std::string tablename);

ERR_CODE sdk_Insert(TMYSQL_HANDLE handle,TableDataMap &da, std::string tablename);

ERR_CODE sdk_DeleteDataWithId(TMYSQL_HANDLE handle,std::string tablename, std::string idname, std::string idnum);

......

```