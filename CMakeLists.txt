# 指定cmake的最低版本要求
cmake_minimum_required(VERSION 3.20)

# 指定项目名称
project(application)
message(STATUS "???????${PROJECT_SOURCE_DIR}")

# ******************************************************************
# 启用 C++14 标准
set(CMAKE_CXX_STANDARD 14)  # 设置 C++14 标准
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 确保必须使用指定的标准
set(CMAKE_CXX_EXTENSIONS OFF) # 禁用编译器特定扩展

# 指定可执行文件最后运行在哪个操作系统上
# set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86)      # (arm还是x86)

# 指定编译工具的绝对位置
# set(CMAKE_C_COMPILER /usr/bin/gcc)
# set(CMAKE_CXX_COMPILER /usr/bin/g++)

# 查看自己的编译工具链
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")

# *****************************************************************

# 查找配置文件, 这个配置文件是必须的(没它不行)
# find_package(OpenCV REQUIRED)
# message(STATUS "Found OpenCV version: ${OpenCV_VERSION}")
# message(STATUS "OpenCV libraries to link: ${OpenCV_LIBS}")
# message(STATUS "OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")

# 到子目录下执行CMakeLists.txt文件
add_subdirectory(${PROJECT_SOURCE_DIR}/DynamicCreatedClass)
add_subdirectory(${PROJECT_SOURCE_DIR}/MsgMapAndCmdPass)
add_subdirectory(${PROJECT_SOURCE_DIR}/utils)
add_subdirectory(${PROJECT_SOURCE_DIR}/example/DynamicCreatedClass)
add_subdirectory(${PROJECT_SOURCE_DIR}/example/MsgMapAndCmdPass)
add_subdirectory(${PROJECT_SOURCE_DIR}/example/timer)

# # 包含头文件，方便src目录下的源文件使用
#include_directories(
#     ${CMAKE_SOURCE_DIR}/DynamicCreatedClass
#)

# 指定动态库和静态库所在位置
# link_directories(${PROJECT_SOURCE_DIR}/library)

# 指定静态库的名称libUTILS.a
# link_libraries(UTILS)

# 扫描 项目 目录并将所有源文件存储到 src_list 变量中
# aux_source_directory(${CMAKE_SOURCE_DIR} PRO_SRC_LIST)
# message(STATUS "所有源文件：${SRC_LIST}")

# 增加可执行文件
#add_executable(application
#        ${PROJECT_SOURCE_DIR}/example/DynamicCreatedClass/main.cpp
#        ${NEW_example_DCC_LIST}
#        ${NEW_MFC_DCC_LIST})

add_executable(application
        ${PROJECT_SOURCE_DIR}/example/MsgMapAndCmdPass/main.cpp
        ${NEW_MFC_MMACP_LIST})

#add_executable(application
#        ${PROJECT_SOURCE_DIR}/example/timer/main.cpp
#        ${NEW_utils_LIST})

# message(STATUS "OpenCV ??${OpenCV_LIBS}")

# 为目标添加头文件
target_include_directories(application PRIVATE
        ${PROJECT_SOURCE_DIR}/DynamicCreatedClass
        ${PROJECT_SOURCE_DIR}/MsgMapAndCmdPass
        ${PROJECT_SOURCE_DIR}/utils
        ${PROJECT_SOURCE_DIR}/example/DynamicCreatedClass
        )

# 可执行文件链接动态库
target_link_libraries(application
        # ${OpenCV_LIBS}
        # pthread                  # 使用多线程需要包含这个库
        # SRC_LIB                  # 要链接的动态库名字
)