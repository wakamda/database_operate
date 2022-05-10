#ifndef _BASIC_DB_H
#define _BASIC_DB_H

#include "../common/Datatype.h"

class Basic_db
{
public:
/********************************************************************************
 * database config
********************************************************************************/
    virtual ERR_CODE Init() { };
    
    virtual ERR_CODE Finit() { };
    
    virtual ERR_CODE connectdb(const char* host,const char* user,const char* pwd,const char* db_name,unsigned short port,unsigned long flag) {};
    
    virtual ERR_CODE SwitchDBType(TABLE_CODING_TYPE type) {};

    virtual ERR_CODE SetMysqlOption(MSQL_OPT opt,const void *arg) {};

    virtual ERR_CODE SetConnectTimeout(int sec) {};

    virtual ERR_CODE SetReconnect(bool isre) {};
    
    virtual char * Gethost() {};
    virtual char * Sethost(char* newVal) {};
    
    virtual char* Getuser() {};
    virtual char* Setuser(char* newVal){};
    
    virtual char* Getpwd(){};
    virtual char* Setpwd(char* newVal){};
    
    virtual char* Getdbname(){};
    virtual char* Setdbname(char* newVal){};
    
    virtual unsigned short Getport(){};
    virtual unsigned short Setport(unsigned short newVal){};
    
    virtual unsigned long Getflag(){};
    virtual unsigned long Setflag(unsigned long newVal){};   

/********************************************************************************
 * database operation
********************************************************************************/

    virtual bool Query(const char* sql, unsigned long sqllen = 0) {};

    virtual ERR_CODE createdatabase(std::string &dbname) {};
    virtual ERR_CODE deletedatabase(std::string &dbname) {};

    virtual ERR_CODE createtable(TABLEVECTOR &vector,std::string &tablename, TABLE_CODING_TYPE tabletype) {};
    virtual ERR_CODE deletetable(std::string &tablename) {};

    virtual ERR_CODE Insert(TableDataMap &da, std::string &tablename) {};

    virtual ERR_CODE DeleteDataWithId(std::string &tablename, std::string &idname, std::string &idnum){};

    virtual ERR_CODE DeleteDataLikeWithFieldname(std::string &tablename, std::string &fieldname, std::string &fielddata) {};

    virtual uint64_t UpdateData(TableDataMap &da, std::string &tablename, std::string &where, std::string &idnum) {};

    virtual ERR_CODE SelectTable(std::string &tablename) { };

    virtual ERR_CODE SelectDataWithX(std::string &tablename, std::string &fieldname, std::string &fielddata) {};

    virtual ERR_CODE StoreResult(){};

    virtual ERR_CODE UseResult() {};

    virtual ERR_CODE FreeResult() {};

    virtual ROW FetchRow() {};

protected:
    char* host;
    char* user;
    char* pwd;
    char* dbname;
    unsigned short port;
    unsigned long flag;

};

#endif //_BASIC_DB_H
