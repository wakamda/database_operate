///////////////////////////////////////////////////////////
//  Ctmysql.cpp
//  Original author: wakamda
//  Implementation of class Ctmysql 
///////////////////////////////////////////////////////////
#include<iostream>
#include<string>
#include "Ctmysql.h"

using namespace std;

Ctmysql::Ctmysql()
{
    //create a new mysql object
    mysql=mysql_init(NULL);   
    if(mysql==NULL)
    {
        cout<<"Error:"<<mysql_error(mysql);
        exit(1);
    }
}

Ctmysql::~Ctmysql()
{
    //close mysql object
    if(mysql!=NULL)  
    {
        mysql_close(mysql);
    }
}

ERR_CODE Ctmysql::connectmysql(const char* host,const char* user,const char* passwd,const char* db_name)
{ 
    mysql = mysql_real_connect(mysql, host, user, passwd, db_name, 0, NULL, 0);  
    if(mysql == NULL)  
    {  
        cout << "Error: " << mysql_error(mysql);  
        exit(1);  
    }  
    return ERR_SUCCESS;  
}

bool Ctmysql::execSQL(const char*sql, unsigned long sqllen)
{
    if (sqllen <= 0)
        sqllen = (unsigned long)strlen(sql);
    if (sqllen <= 0)
	{
		cout<< "Query sql is empty or wrong format!" ;
		return false;
	}
    //mysql_query()执行成功返回0,执行失败返回非0值。
    int re =mysql_real_query(mysql, sql, sqllen);
    if (re != 0)
    {
        cout<<"Query Error: "<<mysql_error(mysql);
        return false;
    }
    return true;
}

ERR_CODE Ctmysql::createdatabase(std::string &dbname){
    if(dbname.empty())
        return ERR_INVALID_ARG;
    std::string queryStr = "create database "+dbname;
    if(execSQL(queryStr.c_str(),0))
    {
        queryStr = "use "+dbname;
        if(execSQL(queryStr.c_str(),0))
        {
            cout << "create database success!!" << endl;
            return ERR_SUCCESS;
        }
    }
    cout << "create database failed!!" << endl;
    return ERR_FAILED;
}

ERR_CODE Ctmysql::deletedatabase(std::string &dbname){

}

ERR_CODE Ctmysql::createtable(TABLEVECTOR &vector,std::string &tablename, TABLE_TYPE tabletype){

}

ERR_CODE Ctmysql::deletetable(std::string &tablename){

}

/********************************data-insert****************************************/

/********************************data-delete****************************************/

/********************************data-update****************************************/

/********************************data-select****************************************/
//ERR_CODE Ctmysql::selectdata(std::string &tablename){
//    if(tablename.empty())
//        return ERR_INVALID_ARG;
//    string sql = "select * from " + tablename;
//    return (execSQL(sql.c_str,0) == true) ? ERR_SUCCESS:ERR_FAILED;
//}
