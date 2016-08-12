#CMake最低版本要求
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
#定义工程名称
PROJECT(EasyWebServer)
#打印相关消息
MESSAGE(STATUS "Project:EasyWebServer")
MESSAGE(STATUS "Project Directory:${PROJECT_SOURCE_DIR}")

#指定编译类型，debug或release，debug版本会生成相关调试信息，使用GDB进行调试
SET(CMAKE_BUILE_TYPE DEBUG)

#指定编译器
#CMAKE_C_FLAGS_DEBUG	--C编译器
#CMAKE_CXX_FLAGS_DEBUG		--C++编译器
SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

#添加源文件
#aux_source_directory(./ EXE_SRC)		#将当前目录（不含子目录）下的所有源文件保存在变量SRC_LIST中
aux_source_directory(./src SRC)	#将子目录src下的源文件保存到变量SRC中
#list(APPEND EXEC_SRC ${OTHER_SRC})	#将OTHER_SRC_LIST添加到SRC_LIST中

#编译可执行文件
ADD_EXECUTABLE(EasyWebServer ${SRC})
