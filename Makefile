CC = g++
CFLAGS  := -L /home/chengtao/Documents/mysqlsdk -lmysql_sdk

MYSQL_INC_ROOT = /home/chengtao/Documents/mysqlsdk/mysql
MY_LIB_ROOT = /home/chengtao/Documents/mysqlsdk

MYSQL_INC = -I $(MYSQL_INC_ROOT)
MY_INC = -I $(MY_ROOT)

all:test

test:test.cpp
	$(CC) test.cpp -o test $(CFLAGS) `mysql_config --cflags --libs`
