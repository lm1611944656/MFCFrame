#include "cMFCFrame.h"
#include "CSensor.h"
#include "CDevice.h"
#include "cheavydevice.h"
#include "cdevicechild.h"
#include <iostream>
#include <iomanip>

/**
 *      类名             对象大小     标号      基类
 *   --------------------------------------------------
 *   CSensor             8         1001      LObject
 *   CDevice             8         1003      LObject
 *   CHeavyDevice        592       1002      LObject
 *   CDeviceChild        8         301       CDevice
 *   --------------------------------------------------
 */
void PrintAllRegisteredClasses()
{
    std::cout << "===== 当前已注册类列表 =====" << std::endl;
    std::cout << std::left
              << std::setw(20) << "类名"
              << std::setw(10) << "对象大小"
              << std::setw(10) << "标号"
              << "基类" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    for (CRuntimeClass *pClass = CRuntimeClass::m_pFirstClass; pClass != nullptr; pClass = pClass->m_pNextClass)
    {
        std::string baseName = (pClass->m_pBaseClass) ? pClass->m_pBaseClass->m_className : "(无)";
        std::cout << std::left
                  << std::setw(20) << pClass->m_className
                  << std::setw(10) << pClass->m_objectSize
                  << std::setw(10) << pClass->m_schema
                  << baseName << std::endl;
    }

    std::cout << "--------------------------------------------------" << std::endl;
}

int main() {
    /*打印所有已经注册的类*/
    PrintAllRegisteredClasses();

    /*查找出指定类名的对象，并创建该类*/
    LObject *p1 = CRuntimeClass::load("CSensor")->createObject();
    LObject *p2 = CRuntimeClass::load("CDevice")->createObject();
    LObject* p3 = CRuntimeClass::load("CDeviceChild")->createObject();

    std::cout << "\n===== 类型判断测试 =====" << std::endl;
    /*判断类型*/
    if (p1->isKindOf(RUNTIME_CLASS(LObject)))
        std::cout << "p1 是 LObject 或其派生类" << std::endl;

    if (p1->isKindOf(RUNTIME_CLASS(CSensor)))
        std::cout << "p1 是 CSensor 类" << std::endl;

    if (!p1->isKindOf(RUNTIME_CLASS(CDevice)))
        std::cout << "p1 不是 CDevice 类" << std::endl;

    if (p2->isKindOf(RUNTIME_CLASS(CDevice)))
        std::cout << "p2 是 CDevice 类" << std::endl;

    if (p3->isKindOf(RUNTIME_CLASS(CDevice))) {
        std::cout << "p3 是 CDevice 或其子类" << std::endl;
    }

    LObject* obj = CRuntimeClass::load("CHeavyDevice")->createObject();
    auto* heavy = dynamic_cast<CHeavyDevice*>(obj);
    if (heavy)
        heavy->showInfo();

    /*调用子类方法*/
    CDeviceChild* child = dynamic_cast<CDeviceChild*>(p3);
    if (child) {
        child->childRun();
    }

    delete p1;
    delete p2;
    delete p3;
    return 0;
}
