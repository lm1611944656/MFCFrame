/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: cdevice.cpp
*   软件模块: 应用
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: 实例类对象源文件
*
**********************************************************************/

#include "cdevice.h"

/*实现一个CDevice， 该类的标识符为1003， 该类继承与LObject*/
IMPLEMENT_DYNAMIC(CDevice, 1003, LObject)

CDevice::CDevice() {
    std::cout << "CDevice constructed." << std::endl;
}

void CDevice::deviceRun() {
    std::cout << "[CDevice] Device is running..." << std::endl;
}

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/