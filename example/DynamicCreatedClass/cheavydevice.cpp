/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: cheavydevice.cpp
*   软件模块: 应用
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: 实例类对象源文件
*
**********************************************************************/

#include "cheavydevice.h"
#include <iostream>

/*实现一个CHeavyDevice， 该类的标识符为1002， 该类继承与LObject*/
IMPLEMENT_DYNAMIC(CHeavyDevice, 1002, LObject)
CHeavyDevice::CHeavyDevice()
        : m_id(1001), m_power(123.45), m_name("Big Device"), m_data(50, 42)
{
    std::fill(std::begin(m_buffer), std::end(m_buffer), 0xAA);
}

CHeavyDevice::~CHeavyDevice() = default;

void CHeavyDevice::showInfo()
{
    std::cout << "Name: " << m_name
              << " | Power: " << m_power
              << " | ID: " << m_id
              << " | Data size: " << m_data.size() << std::endl;
}

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/