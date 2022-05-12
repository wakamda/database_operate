///////////////////////////////////////////////////////////
//  Ctmysql.cpp
//  Original author: wakamda
//  Implementation of class Ctmysql 
///////////////////////////////////////////////////////////
#include<iostream>
#include<string>
#include "Ctmysql.h"

using namespace std;

/************************************************************************
 *  config
************************************************************************/
ERR_CODE Ctmysql::SwitchDBType(TABLE_CODING_TYPE tablecodingtype){
    bool bresult = false;
	string stype;
	switch (tablecodingtype)
	{
	case GBK:{
        bresult = Query("set names gbk"); 
        stype = "gbk"; 
        break;
    }
	case UTF8:{
        bresult = Query("set names utf8");
        stype = "utf8";
        break;
    }
	case NOTYPE:{
        bresult = true;
        break;
    }   
	default:
        break;
	}
	cout << "switchtype to "<< stype.c_str() << "return " << str_err_code[bresult ? ERR_SUCCESS : ERR_FAILED] << endl;
	return bresult ? ERR_SUCCESS : ERR_FAILED;
}

ERR_CODE Ctmysql::SetMysqlOption(MSQL_OPT opt,const void *arg){
    if (!mysql)
	{
		cout << "Option failed:mysql is NULL" << endl;
		return ERR_FAILED;
	}
	int re = mysql_options(mysql, (mysql_option)opt, arg);
	if (re != 0)
	{
		cout << "mysql_options failed!error is " << mysql_error(mysql) << endl;
		return ERR_FAILED;
	}
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::SetConnectTimeout(int sec){
    return SetMysqlOption(MSQL_OPT_CONNECT_TIMEOUT, &sec);
}

ERR_CODE Ctmysql::SetReconnect(bool isre){
	return SetMysqlOption(MSQL_OPT_RECONNECT, &isre);
}

ERR_CODE Ctmysql::Init(){
    Finit();
    cout << "mysql Init " << endl;
    mysql=mysql_init(NULL);
    if(mysql==NULL)
    {
        cerr << "mysql_init failed!" << endl;
        return ERR_FAILED;
    }
    cout << "mysql_init success, mysql = " << mysql << endl;
    return ERR_SUCCESS;
}

ERR_CODE Ctmysql::Finit(){
    FreeResult();

    if(mysql!=NULL)  
    {
        mysql_close(mysql);
        mysql = NULL;
        cout << "mysql Finit success!" << endl;
        return ERR_SUCCESS;
    }
    cout << "mysql Finit failed!" << endl;
    return ERR_FAILED;
}

ERR_CODE Ctmysql::connectdb(const char* host,const char* user,const char* passwd,const char* dbname,unsigned short port,unsigned long flag){   
    if (!mysql && !Init())
	{
		cerr << "Mysql connect failed! msyql is not init!" << endl;
		return ERR_FAILED;
	}
    mysql = mysql_real_connect(mysql, host, user, passwd, dbname, port, NULL, flag);
    if(mysql == NULL)
    {  
        cerr << "Mysql connect failed!" << mysql_error(mysql) << endl;
		return ERR_FAILED;  
    }  
    return ERR_SUCCESS;  
}

/***********************************************************************
 *  operation
************************************************************************/
bool Ctmysql::Query(const char*sql, unsigned long sqllen)
{
    if (!mysql)
	{
		cerr << "Query failed:mysql is NULL" << endl;
		return false;
	}
    if (!sql)
	{
		cerr <<"sql is null"<< endl;
		return false;
	}
    if (sqllen <= 0)
        sqllen = (unsigned long)strlen(sql);
    if (sqllen <= 0)
	{
		cout<< "Query sql is empty or wrong format!" ;
		return false;
	}
    //Query
    int re =mysql_real_query(mysql, sql, sqllen);
    if (re != 0)
    {
        cout<<"Query Error: "<<mysql_error(mysql);
        return false;
    }
    return true;
}

ERR_CODE Ctmysql::createdatabase(std::string &dbname){
    if(dbname.empty()){
        cout << "return" <<  str_err_code[ERR_INVALID_ARG] << endl;
        return ERR_INVALID_ARG;
    }
    std::string queryStr = "create database if not exists `"+dbname+"`";
    if(Query(queryStr.c_str(),0))
    {
        queryStr = "use "+dbname;
        if(Query(queryStr.c_str(),0))
        {
            cout << "create database success!!" << endl;
            return ERR_SUCCESS;
        }
    }
    cout << "create database " << dbname.c_str() <<" failed!!" << endl;
    return ERR_FAILED;
}

ERR_CODE Ctmysql::deletedatabase(std::string &dbname){
    if(dbname.empty()){
        cout << "return" << str_err_code[ERR_INVALID_ARG] << endl;
        return ERR_INVALID_ARG;
    }
    std::string queryStr = "drop database if exists `"+dbname+"`";
    if(Query(queryStr.c_str(),0))
    {
        cout << "delete database " << dbname.c_str() << "success!" << endl;
        return ERR_SUCCESS;
    }
    cout << "delete database " << dbname.c_str() <<" failed!!" << endl;
    return ERR_FAILED;
}

ERR_CODE Ctmysql::createtable(TABLEVECTOR &vector,std::string &tablename, TABLE_CODING_TYPE tablecodingtype){
    if(vector.empty() || tablename.empty() || tablecodingtype > NOTYPE){
        cout << "return" << str_err_code[ERR_INVALID_ARG] << endl;
        return ERR_INVALID_ARG;
    }
    string sql = "CREATE TABLE IF NOT EXISTS `" + tablename + "` (";
    TABLEVECTOR::iterator iter = vector.begin();
	for (;iter != vector.end(); ++iter)
	{
		sql += GetAutogenCreateSql(&(*iter));
		sql += ",";
	}
	sql[sql.size() - 1] = ' ';
	sql += ")";
	cout << sql.c_str() << endl;
	return Query(sql.c_str()) == true ? ERR_SUCCESS : ERR_FAILED;
}

ERR_CODE Ctmysql::deletetable(std::string &tablename){
    if (tablename.empty())
	{
		cout << "return "<< str_err_code[ERR_INVALID_ARG] << endl;
		return ERR_INVALID_ARG;
	}
	string sql = "DROP TABLE IF EXISTS `" + tablename + "`";
	return Query(sql.c_str()) == true ? ERR_SUCCESS : ERR_FAILED;
}

ERR_CODE Ctmysql::Insert(TableDataMap &da, std::string &tablename){
    if (da.empty() || tablename.empty())
	{
		cout << "return " << str_err_code[ERR_INVALID_ARG] << endl;
		return ERR_INVALID_DATA;
	}
	if (!mysql)
	{
		cout << "Insert failed:mysql is NULL"<< endl;
		return ERR_FAILED;
	}
	string sql = GetAutogenInsertSql(da, tablename);
	if (sql.empty())
		return ERR_FAILED;
	if (!Query(sql.c_str()))
		return ERR_FAILED;
	uint64_t num = mysql_affected_rows(mysql);
	if (num <= 0)
		return ERR_FAILED;
	cout << "return success" << endl;
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::DeleteDataWithId(std::string &tablename, std::string &idname, std::string &idnum){
    //delete FROM A WHERE id = 'B' 
	if (tablename.empty() || idname.empty() || idnum.empty())
	{
		cout << "return "<< str_err_code[ERR_INVALID_ARG] << endl;
		return ERR_INVALID_DATA;
	}
	string sql = "delete from " + tablename + " where " + idname + "=" + idnum;
	if (!Query(sql.c_str()))
	{
		printf("delete faield in table:%s, col:%s, data:%s\n", tablename.c_str(), idname.c_str(), idnum.c_str());
		return ERR_FAILED;
	}
	printf("delete success in table:%s, col:%s, data:%s\n", tablename.c_str(), idname.c_str(), idnum.c_str());
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::DeleteDataLikeWithFieldname(std::string &tablename, std::string &fieldname, std::string &fielddata){
    //DELETE from tablename where 字段名 like '%字段值%'
	if (tablename.empty() || fieldname.empty() || fielddata.empty())
	{
		printf("return %s", str_err_code[ERR_INVALID_ARG]);
		return ERR_INVALID_DATA;
	}
	string sql = "delete from " + tablename + " where `" + fieldname + "` like '%" + fielddata + "%'";
	if (!Query(sql.c_str()))
	{
		printf("drop faield in table:%s, col:%s, data:%s\n", tablename.c_str(), fieldname.c_str(), fielddata.c_str());
		return ERR_FAILED;
	}
	printf("drop success in table:%s, col:%s, data:%s\n", tablename.c_str(), fieldname.c_str(), fielddata.c_str());
	return ERR_SUCCESS;
}

uint64_t Ctmysql::UpdateData(TableDataMap &da, std::string &tablename, std::string &where, std::string &idnum){
    if (da.empty() || tablename.empty() || where.empty())
	{
		printf("return %s",str_err_code[ERR_INVALID_ARG]);
		return -1;
	}
	if (!mysql)return -1;
	string sql = GetAutogenUpdateSql(da, tablename, where, idnum);
	if (sql.empty())
		return -1;
	if (!Query(sql.c_str()))
	{
		return -1;
	}
	printf("return success\n");
	return mysql_affected_rows(mysql);
}

ERR_CODE Ctmysql::SelectFromTable(std::string &tablename){
    if(tablename.empty())
        return ERR_INVALID_ARG;
    string sql = "select * from " + tablename;
    return (Query(sql.c_str()) == true) ? ERR_SUCCESS:ERR_FAILED;
}

ERR_CODE Ctmysql::SelectDataWithX(std::string &tablename, std::string &fieldname, std::string &fielddata){
    if (tablename.empty() || fieldname.empty() || fielddata.empty())
	{
		printf("return %s", str_err_code[ERR_INVALID_ARG]);
		return ERR_INVALID_ARG;
	}
	string sql = "select * from " + tablename + " where " + fieldname + " like '%" + fielddata + "%'";
	return (Query(sql.c_str()) == true) ? ERR_SUCCESS : ERR_FAILED;
}

ERR_CODE Ctmysql::StoreResult(){
    if (!mysql)
	{
		printf("StoreResult failed:mysql is NULL" );
		return ERR_FAILED;
	}
	FreeResult();
	result = mysql_store_result(mysql);
	if (!result)
	{
		printf("mysql_store_result failed!error is:%s", mysql_error(mysql));
		return ERR_FAILED;
	}
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::UseResult(){
    if (!mysql)
	{
		printf("UseResult failed:mysql is NULL");
		return ERR_FAILED;
	}
	FreeResult();
	result = mysql_use_result(mysql);
	if (!result)
	{
		printf("mysql_use_result failed!erorr is:%s", mysql_error(mysql));
		return ERR_FAILED;
	}
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::FreeResult()
{
	if (result)
	{
		mysql_free_result(result);
		result = NULL;
		return ERR_SUCCESS;
	}
	return ERR_FAILED;
}

ROW Ctmysql::FetchRow(){
    ROW re;
	if (!result)
	{
		printf("reult is null");
		return re;
	}
	MYSQL_ROW row = mysql_fetch_row(result);
	if (!row)
	{
		printf("row is null");
		return re;
	}
	//列数
	int num = mysql_num_fields(result);

	unsigned long *lens = mysql_fetch_lengths(result);
	for (int i = 0; i < num; i++)
	{
		Table_Data data;
		data.data = row[i];
		data.size = lens[i];
		//获取列的类型
		auto field = mysql_fetch_field_direct(result, i);
		data.type = (TABLE_DATA_TYPE)field->type;
		re.push_back(data);
	}
	printf("return success");
	return re;
}
//简易接口,返回select的数据结果，每次调用清理上一次的结果集
ERR_CODE Ctmysql::EasySelect(std::string &tablename, ROWS &rows){
	if (tablename.empty())
	{
		printf("return %s", str_err_code[ERR_INVALID_ARG]);
		return ERR_INVALID_ARG;
	}
	string sql = "select * from " + tablename;
	FreeResult();
	if (!Query(sql.c_str()))
		return ERR_FAILED;
	if (StoreResult() != ERR_SUCCESS)
		return ERR_FAILED;
	for (;;)
	{
		auto row = FetchRow();
		if (row.empty())break;
		rows.push_back(row);
	}
	printf("return success");
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::EasyLike(std::string &tablename, std::string &fieldname,std::string &fielddata, ROWS &rows){
	if (tablename.empty() || fieldname.empty() || fielddata.empty())
	{
		printf("return %s", str_err_code[ERR_INVALID_ARG]);
		return ERR_INVALID_ARG;
	}
	FreeResult();
	string sql = "select * from " + tablename + " where " + fieldname + " like '%" + fielddata + "%'";
	if (!Query(sql.c_str()))
		return ERR_FAILED;
	if (StoreResult() != ERR_SUCCESS)
		return ERR_FAILED;
	for (;;)
	{
		auto row = FetchRow();
		if (row.empty())break;
		rows.push_back(row);
	}
	printf("return success");
	return ERR_SUCCESS;
}
/***********************************************************************
 * underlying operation
************************************************************************/
std::string Ctmysql::GetTableFieldTypeString(TABLE_FIELD_TYPE gbkorutf)
{
	std::string typestring = str_table_field_type[gbkorutf];
	return typestring;
}

std::string Ctmysql::GetAutogenCreateSql(LPTABLESTRUCT pfield)
{
	std::string fieldsql = "`" + pfield->field_name + "` ";
	fieldsql += GetTableFieldTypeString(pfield->field_type);
	if (pfield->field_len != 0)
	{
		fieldsql += "(";
		fieldsql += to_string(pfield->field_len);
		fieldsql += ")";
	}
	if (pfield->table_coding_type == GBK)
	{
		fieldsql += " CHARACTER SET gbk COLLATE gbk_bin";
	}
	else if (pfield->table_coding_type == UTF8)
	{
		fieldsql += " CHARACTER SET utf8 COLLATE utf8_bin";
	}
	else//NOTYPE才考虑是否将此字段设为自增ID
	{
		if (pfield->field_type == DBTYPE_ID)
		{
			fieldsql += ",PRIMARY KEY(`";
			fieldsql += pfield->field_name;
			fieldsql += "`)";
		}
	}
	return fieldsql;
}

std::string Ctmysql::GetAutogenInsertSql(TableDataMap &da, std::string &tablename){
    string sql = "";
	sql = "insert into `";
	sql += tablename;
	sql += "`";
	//insert into t_video (name,size) values("name1","1024")
	string keys = "";
	string vals = "";

	//迭代map
	for (TableDataMap::iterator ptr = da.begin(); ptr != da.end(); ptr++)
	{
		//字段名
		keys += "`";
		keys += ptr->first;
		keys += "`,";

		vals += "'";
		vals += ptr->second.data;
		vals += "',";
	}
	//去除多余的逗号
	keys[keys.size() - 1] = ' ';
	vals[vals.size() - 1] = ' ';

	sql += "(";
	sql += keys;
	sql += ")values(";
	sql += vals;
	sql += ")";
	return sql;
}

std::string Ctmysql::GetAutogenUpdateSql(TableDataMap &da, std::string &tablename, std::string &where, std::string &idnum){
    //update t_video set name='update001',size=1000 where id=10
	string sql = "";
	sql = "update `";
	sql += tablename;
	sql += "` set ";
	for (TableDataMap::iterator ptr = da.begin(); ptr != da.end(); ptr++)
	{
		sql += "`";
		sql += ptr->first;
		sql += "`='";
		sql += ptr->second.data;
		sql += "',";
	}
	//去除多余的逗号
	sql[sql.size() - 1] = ' ';
	sql += " where ";
	sql += where;
	sql += "=";
	sql += idnum;
	return sql;
}
