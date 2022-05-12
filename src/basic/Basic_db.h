#ifndef _BASIC_DB_H
#define _BASIC_DB_H

#include "../common/Datatype.h"

class Basic_db
{
public:
    Basic_db() {};
    virtual ~Basic_db(){};
/********************************************************************************
 * database config
********************************************************************************/
    //create instance
    virtual ERR_CODE Init() = 0;
    
    //delete instance
    virtual ERR_CODE Finit() = 0;
    
    //connect mysql
    virtual ERR_CODE connectdb(const char* host,const char* user,const char* pwd,const char* db_name,unsigned short port,unsigned long flag) = 0;
    
    //Set the database encoding format
    virtual ERR_CODE SwitchDBType(TABLE_CODING_TYPE type) = 0;

    //Set additional connection options in mysql
    virtual ERR_CODE SetMysqlOption(MSQL_OPT opt,const void *arg) { return ERR_FAILED;};

    //Set the connect timeout seconds
    virtual ERR_CODE SetConnectTimeout(int sec) = 0;

    //Automatic reconnection, not automatic by default
    virtual ERR_CODE SetReconnect(bool isre) = 0;
    
    char * Gethost() {return host;};
    char * Sethost(char* newVal) {host = newVal;return host;};
    
    char* Getuser() {return user;};
    char* Setuser(char* newVal){user = newVal;return user;};
    
    char* Getpwd(){return pwd;};
    char* Setpwd(char* newVal){pwd = newVal;return pwd;};
    
    char* Getdbname(){return dbname;};
    char* Setdbname(char* newVal){ dbname = newVal;return dbname;};
    
    unsigned short Getport(){return port;};
    unsigned short Setport(unsigned short newVal){port = newVal;return port;};
    
    unsigned long Getflag(){return flag;};
    unsigned long Setflag(unsigned long newVal){flag = newVal;return flag;};   

/********************************************************************************
 * database operation
********************************************************************************/

    //Query SQL(can not parse sql with bin sql)
    virtual bool Query(const char* sql, unsigned long sqllen = 0) = 0;

    //database
    virtual ERR_CODE createdatabase(std::string &dbname)  = 0;
    virtual ERR_CODE deletedatabase(std::string &dbname) = 0;

    //table
    virtual ERR_CODE createtable(TABLEVECTOR &vector,std::string &tablename, TABLE_CODING_TYPE tabletype) = 0;
    virtual ERR_CODE deletetable(std::string &tablename) = 0;
    virtual ERR_CODE SelectFromTable(std::string &tablename) = 0;

    //data insert
    virtual ERR_CODE Insert(TableDataMap &da, std::string &tablename) = 0;
    
    //data delete with id
    virtual ERR_CODE DeleteDataWithId(std::string &tablename, std::string &idname, std::string &idnum) = 0;
    
    //delete data where fieldname like ...
    virtual ERR_CODE DeleteDataLikeWithFieldname(std::string &tablename, std::string &fieldname, std::string &fielddata) = 0;
    
    //update data
    virtual uint64_t UpdateData(TableDataMap &da, std::string &tablename, std::string &where, std::string &idnum) = 0;

    //select data where like...
    virtual ERR_CODE SelectDataWithX(std::string &tablename, std::string &fieldname, std::string &fielddata) = 0;

    //select data returns all results
    virtual ERR_CODE StoreResult()= 0;

    //Start receiving results, Fetch via Fetch
    virtual ERR_CODE UseResult() = 0;

    //Frees the space occupied by the result set
    virtual ERR_CODE FreeResult() = 0;

    //receive a row data
    virtual ROW FetchRow() = 0;

    //Simple interface, return select data results, each call to clean up the last result set  
	virtual ERR_CODE EasySelect(std::string &tablename, ROWS &rows) = 0;

	//Simple interface, fuzzy search
	virtual ERR_CODE EasyLike(std::string &tablename, std::string &fieldname,std::string &fielddata, ROWS &rows) = 0;

protected:
    char* host;
    char* user;
    char* pwd;
    char* dbname;
    unsigned short port;
    unsigned long flag;
};

#endif //_BASIC_DB_H
