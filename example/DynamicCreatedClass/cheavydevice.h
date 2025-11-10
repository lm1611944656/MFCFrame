/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: cheavydevice.cpp
*   软件模块: 应用
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: 实例类对象头文件
*
**********************************************************************/

#ifndef CHEAVYDEVICE_H
#define CHEAVYDEVICE_H

#include "cMFCFrame.h"
#include <vector>

class CHeavyDevice : public LObject
{
    DECLARE_DYNAMIC(CHeavyDevice)

public:
    CHeavyDevice();
    ~CHeavyDevice();

    void showInfo();

private:
    int m_id;
    double m_power;
    std::string m_name;
    std::vector<int> m_data;
    unsigned int m_buffer[128];
};

#endif // CHEAVYDEVICE_H

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/