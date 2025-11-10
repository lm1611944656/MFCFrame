/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: cMFCFrame.cpp
*   软件模块: 应用
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: MFC的动态创建类框架源文件
*
**********************************************************************/

#include "cMFCFrame.h"

/* 静态成员初始化 */
CRuntimeClass *CRuntimeClass::m_pFirstClass = nullptr;

/* 根据类名查找类信息 */
CRuntimeClass *CRuntimeClass::load(const std::string &className) {
    for (CRuntimeClass *pClass = m_pFirstClass; pClass != nullptr; pClass = pClass->m_pNextClass) {
        if (pClass->m_className == className)
            return pClass;
    }
    std::cout << "Class not found: " << className << std::endl;
    return nullptr;
}

/* 创建对象 */
LObject *CRuntimeClass::createObject() const {
    if (m_pfnCreateObject == nullptr)
        return nullptr;
    return (*m_pfnCreateObject)();
}

/* 注册类 */
CRuntimeClassInit::CRuntimeClassInit(CRuntimeClass *pNewClass) {
    if (pNewClass) {
        pNewClass->m_pNextClass = CRuntimeClass::m_pFirstClass;
        CRuntimeClass::m_pFirstClass = pNewClass;
    }
}

/*-----------------------------------------
 * LObject 实现
 *-----------------------------------------*/
CRuntimeClass LObject::classLObject = {
        "LObject",
        sizeof(LObject),
        0,
        nullptr,
        nullptr
};

CRuntimeClass *LObject::getRuntimeClass() const {
    return &classLObject;
}

/*-----------------------------------------
 * 类型判断函数: 判断当前对象是否为指定类型或其派生类
 *-----------------------------------------*/
bool LObject::isKindOf(const CRuntimeClass *pClass) const
{
    CRuntimeClass *pCurrent = getRuntimeClass();

    while (pCurrent != nullptr)
    {
        if (pCurrent == pClass)
            return true;
        pCurrent = pCurrent->m_pBaseClass;
    }
    return false;
}

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/