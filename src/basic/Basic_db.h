#ifndef _BASIC_DB_H
#define _BASIC_DB_H

#include "../common/Datatype.h"

class Basic_db
{
    public:
    virtual ERR_CODE Init() {};
    virtual ERR_CODE Finit() {};
    virtual ERR_CODE connectdb(const char* host,const char* user,const char* pwd,const char* db_name) {};

    virtual ERR_CODE createdatabase(std::string &dbname) {};
    virtual ERR_CODE deletedatabase(std::string &dbname) {};

    virtual ERR_CODE createtable(TABLEVECTOR &vector,std::string &tablename, TABLE_TYPE tabletype) {};
    virtual ERR_CODE deletetable(std::string &tablename) {};
};

#endif //_BASIC_DB_H
