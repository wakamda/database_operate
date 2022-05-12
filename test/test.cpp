#include "../src/api/DB_sdk_api.h"
#include <iostream>
#include <unistd.h>

using namespace std;
static TMYSQL_HANDLE _handle_ = NULL;

bool sdkInit(){
    _handle_ = sdk_Init();
    
    char arr_host[20]= "localhost";
    char arr_usr[20]= "root";
    char arr_pwd[20]= "123456";
    char arr_dbname[20]="mysql";
    ERR_CODE ret = sdk_connectdb(_handle_,sdk_Sethost(_handle_,arr_host),sdk_Setuser(_handle_,arr_usr),sdk_Setpwd(_handle_,arr_pwd),sdk_Setdbname(_handle_,arr_dbname),sdk_Setport(_handle_,3306),sdk_Setflag(_handle_,0));
    if(ret == ERR_SUCCESS){
        cout << "connect mysql success!" << endl;
        return true;
    }
    else{
        cout << "connect mysql failded!" << endl;
        return false;
    }
}

void create_table(){
    std::string st = "testtable";
    sdk_deletetable(_handle_,st);

    TABLEVECTOR mytable;
    TABLESTRUCT a0;
    a0.field_name = "ID";
    a0.field_type = DBTYPE_ID;
    a0.table_coding_type = NOTYPE;
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

void insertdata(){
    ERR_CODE ret;
	sdk_SwitchDBType(_handle_, UTF8);
	for (int i = 0; i < 20; ++i)
	{
		TableDataMap k;
		k["filetype"] = "文字";
		char szbufp[12] = { 0 };
		sprintf(szbufp, "%d", i);
		k["fieldata"] = szbufp;
		k["shuoming"] = "shuoming111";
		k["shuoming2"] = "shuoming222";
		ret = sdk_Insert(_handle_, k, "testtable");
	}
	ROWS rows;
	sdk_EasySelect(_handle_, "testtable", rows);
	rows.begin();
	for (auto row : rows)
	{
		//遍历每一列
		for (auto c : row)
		{
			if (c.data) cout << c.data << " ";
		}
		cout << endl;
	}
	if (ret == ERR_SUCCESS)
	{
		cout << "*********************************insert data success*********************************" << endl;
	}
	else
	{
		cout << "*********************************insert data failed*********************************" << endl;
	}
}

void updatedata()
{
	TableDataMap k2;
	k2["filetype"] = "文字";
	char szbufp[12] = { 0 };
	sprintf(szbufp, "%d", 6666);
	k2["fieldata"] = szbufp;
	k2["shuoming"] = "shuoming111";
	k2["shuoming2"] = "shuoming222";
	uint64_t ret = sdk_UpdateData(_handle_, k2, "testtable", "ID", "9");
	
	sdk_SelectFromTable(_handle_, "testtable");
	sdk_StoreResult(_handle_);
	while (true)
	{
		ROW rowdata;
		sdk_FetchRow(_handle_, rowdata);
		if (rowdata.empty())
		{
			break;
		}
		ROW::iterator iter = rowdata.begin();
		for (; iter != rowdata.end(); ++iter)
		{
			cout << (*iter).data << " ";
		}
		cout << endl;
	}
	sdk_FreeResult(_handle_);
	if (ret > 0)
	{
		cout << "*********************************update data success*********************************" << endl;
		cout << "*********************************I change the date in ID9*********************************" << endl;
	}
	else
	{
		cout << "*********************************update data failed*********************************" << endl;
	}
}

int main(){
    std::cout << "wow~" << std::endl;
    std::string str = "test_sdk";
    std::string str1 = "test1_sdk";
    std::string str2 = "test2_sdk";
    if(!sdkInit()){
        return -1;
    }

    //delete test1_sdk and test_sdk
    ERR_CODE ret = sdk_deletedatabase(_handle_,str);
    if(ret != ERR_SUCCESS){
        cout << "delete database failed! " << endl;
		return -1;
    }
    else
        cout << "delete database success " << endl;
    ERR_CODE ret1 = sdk_deletedatabase(_handle_,str1);
    if(ret1 != ERR_SUCCESS){
        cout << "delete database failed! " << endl;
		return -1;
    }
    else
        cout << "delete database success " << endl;
    
    
    //create_database
     ERR_CODE ret2 = sdk_createdatabase(_handle_,str2);
    if(ret2 != ERR_SUCCESS){
        cout << "cerate database failed! " << endl;
		return -1;
    }
    else
        cout << "cerate database success " << endl;

    create_table();
    insertdata();
	cout << "wait a while , will update a field data << endl" ;
	sleep(3);
    updatedata();
    sdk_Finit(_handle_);

    return 0;
}