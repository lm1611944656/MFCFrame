/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: cMFCFrame.h
*   软件模块: 应用
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: MFC的动态创建类框架头文件
*
**********************************************************************/

#ifndef CMFCFRAME_H
#define CMFCFRAME_H

#include <iostream>
#include <string>

/*
 * 框架的优点：获取所有类列表 + 对象大小 + schema + 继承层级图
 * */

/*-----------------------------------------
 * 基础类型定义
 *-----------------------------------------*/
class LObject;

/*-----------------------------------------
 * CRuntimeClass 运行时类描述结构
 *-----------------------------------------*/
struct CRuntimeClass {
    std::string m_className;                          // 类名
    int m_objectSize;                                 // 类大小
    unsigned int m_schema;                            // 类的唯一识别码
    LObject *(*m_pfnCreateObject)();                  // 创建对象的函数指针
    CRuntimeClass *m_pBaseClass;                      // 基类信息
    CRuntimeClass *m_pNextClass;                      // 链表中的下一个类
    static CRuntimeClass *m_pFirstClass;              // 全局类链表头

    /* 根据类名查找 */
    static CRuntimeClass *load(const std::string &className);
    /* 创建对象 */
    LObject *createObject() const;
};

/*-----------------------------------------
 * 自动注册器（静态对象）
 *-----------------------------------------*/
struct CRuntimeClassInit {
    explicit CRuntimeClassInit(CRuntimeClass *pNewClass);
};

/*-----------------------------------------
 * 宏定义：声明类的运行时类型信息
 *-----------------------------------------*/
#define DECLARE_DYNAMIC(class_name) \
public: \
    static CRuntimeClass class##class_name; \
    virtual CRuntimeClass *getRuntimeClass() const override; \
    static LObject *createObject();

/*-----------------------------------------
 * 宏定义：实现类的运行时类型信息
 *-----------------------------------------*/
#define IMPLEMENT_DYNAMIC(class_name, schema_value, base_class_name) \
CRuntimeClass class_name::class##class_name = { \
    #class_name, \
    sizeof(class_name), \
    schema_value,  \
    &class_name::createObject, \
    &base_class_name::class##base_class_name, \
    nullptr \
}; \
static CRuntimeClassInit _init_##class_name(&class_name::class##class_name); \
CRuntimeClass *class_name::getRuntimeClass() const { return &class_name::class##class_name; } \
LObject *class_name::createObject() { return new class_name; }

#define RUNTIME_CLASS(class_name) (&class_name::class##class_name)

/*-----------------------------------------
 * LObject 基类
 *-----------------------------------------*/
class LObject {
public:
    LObject() = default;
    virtual ~LObject() = default;

    virtual CRuntimeClass *getRuntimeClass() const;
    static CRuntimeClass classLObject;
    bool isKindOf(const CRuntimeClass *pClass) const;
};

#endif // CMFCFRAME_H


/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/
