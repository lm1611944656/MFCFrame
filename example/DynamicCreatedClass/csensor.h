/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: csensor.cpp
*   软件模块: 应用
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: MFC的动态创建类框架头文件
*
**********************************************************************/

#ifndef CSENSOR_H
#define CSENSOR_H

#include "cMFCFrame.h"

class CSensor : public LObject {
DECLARE_DYNAMIC(CSensor)
public:
    CSensor();
    void readSensor();
};

#endif // CSENSOR_H

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/
