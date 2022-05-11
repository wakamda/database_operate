# db_sdk
## mysql_sdk
#### The 5th update:
**complete**:
```c++
virtual ERR_CODE EasySelect(std::string &tablename, ROWS &rows){};
virtual ERR_CODE EasyLike(std::string &tablename, std::string &fieldname,std::string &fielddata, ROWS &rows){};
```
**problem still:**
```c++
/home/chengtao/Documents/db_sdk/src/api/../mysql/../basic/Basic_db.h: In member function ‘virtual ERR_CODE Basic_db::Init()’:
/home/chengtao/Documents/db_sdk/src/api/../mysql/../basic/Basic_db.h:12:31: warning: no return statement in function returning non-void [-Wreturn-type]
   12 |     virtual ERR_CODE Init() { };

```
```
/home/chengtao/Documents/db_sdk/src/api/DB_sdk_api.cpp: In function ‘ERR_CODE sdk_Finit(TMYSQL_HANDLE)’:
/home/chengtao/Documents/db_sdk/src/api/DB_sdk_api.cpp:24:9: warning: deleting object of polymorphic class type ‘Basic_db’ which has non-virtual destructor might cause undefined behavior [-Wdelete-non-virtual-dtor]
   24 |  delete phandle;
```

#### The 6th update:
**complete:**
```c++
ERR_CODE sdk_deletedatabase(TMYSQL_HANDLE handle,std::string dbname);
test.cpp
```
**problem still:**
```

```