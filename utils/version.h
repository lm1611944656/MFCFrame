/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: version.h
*   软件模块: 程序版本
*   版 本 号: 1.0
*   生成日期: 2026-03-08
*   作    者: lium
*   功    能: 软件版本说明
*
**********************************************************************/

#ifndef __VERSION_MODULE_H
#define __VERSION_MODULE_H

/* --- 版本配置区域 --- */

/* 主版本号 */
#define VERSION_MAJOR 1

/* 次版本号 */
#define VERSION_MINOR 46

/* 修订号 */
#define VERSION_PATCH 0

/* 是否为正式发布版？
 * 1 = 是 (版本字符串不带后缀)
 * 0 = 否 (版本字符串带后缀，如 -dev)
 */
#define VERSION_IS_RELEASE 1

/* 非发布版时的后缀名称 (仅当 VERSION_IS_RELEASE 为 0 时生效) */
#define VERSION_SUFFIX "dev"

/* --- 自动计算区域 (通常不需要修改) --- */

/* 计算十六进制版本: 0xMMNNPP */
#define VERSION_HEX ((VERSION_MAJOR << 16) | \
                     (VERSION_MINOR << 8) |   \
                     (VERSION_PATCH))

/* --- 函数声明区域 --- */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取库的十六进制整数版本号
 * @return unsigned int 版本号为 0xMMNNPP 格式
 */
unsigned int version(void);

/**
 * @brief 获取库的人类可读版本字符串
 * @return const char* 静态版本字符串
 */
const char* version_string(void);

#ifdef __cplusplus
}
#endif

#endif /* __VERSION_MODULE_H */

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2026-03-08, lium
describe: 初始创建.
*************************************************************************/