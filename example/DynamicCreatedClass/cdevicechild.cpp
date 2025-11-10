/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: cdevicechild.cpp
*   软件模块: 应用
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: 实例类对象源文件
*
**********************************************************************/

#include "cdevicechild.h"

/*实现一个CDeviceChild， 该类的标识符为301， 该类继承与CDevice*/
IMPLEMENT_DYNAMIC(CDeviceChild, 301, CDevice)

CDeviceChild::CDeviceChild() {
    std::cout << "CDeviceChild constructed." << std::endl;
}

void CDeviceChild::childRun() {
    std::cout << "CDeviceChild is running." << std::endl;
}

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/