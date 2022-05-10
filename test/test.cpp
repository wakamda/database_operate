#include "../src/api/DB_sdk_api.h"
#include <iostream>

using namespace std;
static TMYSQL_HANDLE _handle_ = NULL;

void testInit(){

    _handle_ = sdk_Init();

    democonncet:
    //char  host[20] = { 0 };
	//char  user[20] = { 0 };
	//char  passwd[20] = { 0 };
	//char  dbname[20] = { 0 };
    //unsigned short port = 3306;
	//cout << "first,I want to get some details about your mysql which you will connect" << endl;
    ////cout << "input your mysql host:" << ""; cin >> host;
	//cout << "input your mysql user name:" << ""; cin >> user;
	//cout << "input your mysql password:" << ""; cin >> passwd;
	//cout << "input your mysql database name:" << ""; cin >> dbname;

    //char* -> char []
    char* host = "localhost";
    char arr_host[20];
    strcpy(arr_host,host);

    char* usr = "root";
    char arr_usr[20];
    strcpy(arr_usr,usr);

    char* pwd = "123456";
    char arr_pwd[20];
    strcpy(arr_pwd,pwd);

    char* dbname = "test_sdk";
    char arr_dbname[20];
    strcpy(arr_dbname,dbname);



    ERR_CODE ret = sdk_connectdb(_handle_,sdk_Sethost(_handle_,arr_host),sdk_Setuser(_handle_,arr_usr),sdk_Setpwd(_handle_,arr_pwd),sdk_Setdbname(_handle_,arr_dbname),sdk_Setport(_handle_,3306),sdk_Setflag(_handle_,0));

    if(ret == ERR_SUCCESS)
        cout << "connect mysql success!" << endl;
    else{
        cout << "connect mysql success!" << endl;
        goto democonncet;
    }
}

void create_database(){
    std::string str = "test1_sdk"; 
    ERR_CODE ret = sdk_createdatabase(_handle_,str);
    if(ret != ERR_SUCCESS)
    {
        cout << "create database failed! " << endl;
    }
}

void create_table(){
    std::string st = "testtable";

    sdk_deletetable(_handle_,st);
    TABLEVECTOR mytable;
    TABLESTRUCT a0;
    a0.field_name = "ID";
    a0.field_type = DBTYPE_ID;
    mytable.push_back(a0);

    TABLESTRUCT a1;
	a1.field_name = "filetype";
	a1.field_type = DBTYPE_VARCHAR;
	a1.table_coding_type = GBK;
	a1.field_len = 128;
	mytable.push_back(a1);

    TABLESTRUCT a2;
	a2.field_name = "fieldata";
	a2.field_type = DBTYPE_VARCHAR;
	a2.field_len = 1024;
	mytable.push_back(a2);

	TABLESTRUCT a3;
	a3.field_name = "shuoming";
	a3.field_type = DBTYPE_VARCHAR;
	a3.field_len = 128;
	mytable.push_back(a3);

	TABLESTRUCT a4;
	a4.field_name = "shuoming2";
	a4.field_type = DBTYPE_VARCHAR;
	a4.field_len = 128;
	mytable.push_back(a4);

    ERR_CODE  re = sdk_createtable(_handle_,mytable,st);
    if (re == ERR_SUCCESS)
	{
		cout << "*********************************create testdb success*********************************" << endl;
	}
	else
	{
		cout << "*********************************create testdb failed*********************************" << endl;
	}
}

int main(){
    std::cout << "wow~" << std::endl;
    testInit();

    create_database();
    create_table();

}