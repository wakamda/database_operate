///////////////////////////////////////////////////////////
//  Ctmysql.h
//  Original author: wakamda
//  class Ctmysql describtion
///////////////////////////////////////////////////////////
#ifndef _CTMYSQL_H
#define _CTMYSQL_H

#include<iostream>
#include<string>
#include "../mysql_include/mysql.h"
#include "../../basic/Datatype.h"

using namespace std;

class Ctmysql
{
    public:

    //init mysql
    Ctmysql();
    ~Ctmysql();

    //connect mysql
    ERR_CODE connectmysql(const char* host,const char* user,const char* pwd,const char* db_name);

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
    MYSQL_RES *result;    //指向查询结果的指针
    MYSQL_ROW row;       //按行返回的查询信息
};


#endif //_CTMYSQL_H
