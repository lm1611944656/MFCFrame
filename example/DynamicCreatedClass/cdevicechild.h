/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: cdevicechild.cpp
*   软件模块: 应用
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: 实例类对象头文件
*
**********************************************************************/

#ifndef CDEVICECHILD_H
#define CDEVICECHILD_H

#include "cdevice.h"
#include <iostream>

class CDeviceChild : public CDevice {
DECLARE_DYNAMIC(CDeviceChild)
public:
    CDeviceChild();
    void childRun();
};

#endif // CDEVICECHILD_H

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/