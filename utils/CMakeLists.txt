# include_directories("/usr/local/include/opencv4")
include_directories(${PROJECT_SOURCE_DIR}/utils)

# 遍历当前文件下的所有源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/utils utils_LIST)

# 打印变量
message("utils目录下的所有源文件为：${utils_LIST}")

# 提升变量utils_LIST的范围， 并且给这个变量赋予新的变量名NEW_utils_LIST。
# 如果不提升utils_LIST的作用域，那么该变量的作用域只能在子目录
set(NEW_utils_LIST ${utils_LIST} PARENT_SCOPE)

# 指定静态库的输出目录
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libarys)

# 指定动态库的输出目录
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libarys)

# 生成动态库
# add_library(SRC_LIB SHARED ${SRC_LIST})