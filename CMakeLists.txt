project(db_sdk)
set(CMAKE_SYSTEM_NAME Linux)
cmake_minimum_required(VERSION 2.8)

#compile flags
set(CMAKE_C_FLAGS "-O0 -g -ggdb -fPIC -std=gnu99")
set(CMAKE_CXX_FLAGS "-O0 -g -ggdb -fPIC -std=c++0x")

# build the .so
include_directories(${PROJECT_SOURCE_DIR}/src)
aux_source_directory(./src/mysql/Ctmysql SRC_DIR)
aux_source_directory(./src/api API_SRC_DIR)
add_library(db_sdk SHARED ${SRC_DIR} ${API_SRC_DIR})
target_link_libraries(db_sdk mysqlclient)

