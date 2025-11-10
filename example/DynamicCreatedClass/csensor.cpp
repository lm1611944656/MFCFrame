/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: csensor.cpp
*   软件模块: 应用
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: MFC的动态创建类框架源文件
*
**********************************************************************/

#include "csensor.h"

/*实现一个CSensor， 该类的标识符为1001， 该类继承与LObject*/
IMPLEMENT_DYNAMIC(CSensor, 1001, LObject)
CSensor::CSensor() {
    std::cout << "CSensor constructed." << std::endl;
}

void CSensor::readSensor() {
    std::cout << "[CSensor] Reading sensor data..." << std::endl;
}

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/