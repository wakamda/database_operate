CC = g++
CFLAGS := -Wall -O3 -std=c++0x
MYSQL_INC_ROOT = /home/chengtao/Documents/mysqlsdk/mysql
OBJS = MyDB.o #.o文件与.cpp文件同名
LIB = libmysql_sdk.so # 目标文件名
MYSQL_INC = -I $(MYSQL_INC_ROOT)
INCLUDE_PATH = $(MYSQL_INC)
all : $(LIB)
%.o : %.cpp
	$(CC) $(CFLAGS) -fpic -c $< -o $@ $(INCLUDE_PATH)
# 3. 生成动态库文件
$(LIB) : $(OBJS)
	rm -f $@
	g++ -shared -o $@ $(OBJS)
	rm -f $(OBJS)
tags :
	ctags -R *
# 4. 删除中间过程生成的文件 
clean:
	rm -f $(OBJS) $(TARGET) $(LIB)