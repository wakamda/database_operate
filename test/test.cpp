#include "../src/api/Ctmysql_api.h"
#include <iostream>

using namespace std;
static TMYSQL_HANDLE _handle_ = NULL;

void testInit(){

    Init();
    _handle_ = sdk_createinstance();

    democonncet:
    char host[20] = { 0 };
	char user[20] = { 0 };
	char passwd[20] = { 0 };
	char dbname[20] = { 0 };
	cout << "first,I want to get some details about your mysql which you will connect" << endl;
    cout << "input your mysql host:" << ""; cin >> host;
	cout << "input your mysql user name:" << ""; cin >> user;
	cout << "input your mysql password:" << ""; cin >> passwd;
	cout << "input your mysql database name:" << ""; cin >> dbname;

    ERR_CODE ret = sdk_connectdb(_handle_,(const char*)host,(const char*)user,(const char*)passwd,(const char*)dbname);

    if(ret == ERR_SUCCESS)
        cout << "connect mysql success!" << endl;
    else{
        cout << "connect mysql success!" << endl;
        goto democonncet;
    }
}

void create_database(){
    std::string str = "test_sdk"; 
    ERR_CODE ret = sdk_createdatabase(_handle_,str);
    if(ret != ERR_SUCCESS)
    {
        cout << "create database failed! " << endl;
    }
}

//void create_table(){
//    std::string st = "table_test";
//    ERR_CODE  re = sdk_createtable(_handle_,TABLEVECTOR &vector,std::string &tablename, TABLE_TYPE tabletype);
//}

int main(){
    std::cout << "wow~" << std::endl;
    testInit();
    

    create_database();

}