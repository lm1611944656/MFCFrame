# include_directories("/usr/local/include/opencv4")
include_directories(${PROJECT_SOURCE_DIR}/DynamicCreatedClass)

# 遍历当前文件下的所有源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/DynamicCreatedClass MFC_DCC_LIST)

# 打印变量
message("DynamicCreatedClass目录下的所有源文件为：${MFC_DCC_LIST}")

# 提升变量MFC_DCC_LIST的范围， 并且给这个变量赋予新的变量名NEW_MFC_DCC_LIST。
# 如果不提升MFC_DCC_LIST的作用域，那么该变量的作用域只能在子目录
set(NEW_MFC_DCC_LIST ${MFC_DCC_LIST} PARENT_SCOPE)

# 指定静态库的输出目录
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libarys)

# 指定动态库的输出目录
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libarys)

# 生成动态库
# add_library(SRC_LIB SHARED ${SRC_LIST})