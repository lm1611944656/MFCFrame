/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: version.cpp
*   软件模块: 程序版本
*   版 本 号: 1.0
*   生成日期: 2026-03-08
*   作    者: lium
*   功    能: 软件版本说明
*
**********************************************************************/

#include "version.h"

/* -------------------------------------------------------------------------- */
/*                             宏定义处理逻辑                                 */
/* -------------------------------------------------------------------------- */

#define STRINGIFY(v) STRINGIFY_HELPER(v)
#define STRINGIFY_HELPER(v) #v

#define VERSION_STRING_BASE  STRINGIFY(VERSION_MAJOR) "." \
                             STRINGIFY(VERSION_MINOR) "." \
                             STRINGIFY(VERSION_PATCH)

#if VERSION_IS_RELEASE
# define VERSION_STRING  VERSION_STRING_BASE
#else
# define VERSION_STRING  VERSION_STRING_BASE "-" VERSION_SUFFIX
#endif

/* -------------------------------------------------------------------------- */
/*                             函数实现逻辑                                   */
/* -------------------------------------------------------------------------- */

unsigned int version(void) {
    return VERSION_HEX;
}

const char* version_string(void) {
    return VERSION_STRING;
}

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2026-03-08, lium
describe: 初始创建.
*************************************************************************/