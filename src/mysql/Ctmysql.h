///////////////////////////////////////////////////////////
//  Ctmysql.h
//  Original author: wakamda
//  class Ctmysql describtion
///////////////////////////////////////////////////////////
#ifndef _CTMYSQL_H
#define _CTMYSQL_H

#include<iostream>
#include<string>
#include "../basic/Basic_db.h"
#include "../common/mysql_include/mysql.h"
#include "../common/Datatype.h"

using namespace std;

class Ctmysql :public Basic_db
{
    public:

    //init mysql
    ERR_CODE Init();
    ERR_CODE Finit();

    //connect mysql
    ERR_CODE connectdb(const char* host,const char* user,const char* pwd,const char* db_name);

    //exec SQL(can not parse sql with bin sql)
    bool execSQL(const char*sql, unsigned long sqllen = 0);
    
    //database
    ERR_CODE createdatabase(std::string &dbname);
    ERR_CODE deletedatabase(std::string &dbname);

    //table
    ERR_CODE createtable(TABLEVECTOR &vector,std::string &tablename, TABLE_TYPE tabletype);
    ERR_CODE deletetable(std::string &tablename);

    /********************************data-insert****************************************/

    /********************************data-delete****************************************/

    /********************************data-update****************************************/

    /********************************data-select****************************************/
    //ERR_CODE selectdata(std::string &tablename);
    
    private:
    MYSQL *mysql;          //连接mysql句柄指针
    MYSQL_RES *result;    //指向查询结果的指�?
    MYSQL_ROW row;       //按行返回的查询信�?
};


#endif //_CTMYSQL_H
