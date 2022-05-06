/*************************************************************************
    > File Name: test.cpp
    > Author:fengxin 
    > Mail:903087053@qq.com 
    > Created Time: 2017年07月21日 星期五 16时43分55秒
 ************************************************************************/

#include<iostream>
#include"./mysqlsdk/MyDB.h"
using namespace std;


int main()
{
    MyDB db; 
    //连接数据库
    db.initDB("localhost","root","123456","test");
    //将用户信息添加到数据库
    db.exeSQL("INSERT accounts values('ct','123');");

    //将所有用户信息读出，并输出。
    db.exeSQL("SELECT * from accounts;");

    return 0;
}
