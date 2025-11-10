/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: cMFCMsgAndCmd.cpp
*   软件模块: 应用
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: MFC的消息映射与命令传递
*
**********************************************************************/

#include "cMFCMsgAndCmd.h"

// 空消息表
static const AFX_MSGMAP_ENTRY _CCmdTargetEntries[] = {
        {0,0,0,0,0,nullptr}
};

static const AFX_MSGMAP _CCmdTargetMessageMap = { nullptr, _CCmdTargetEntries };

const AFX_MSGMAP* PASCAL CCmdTarget::getThisMessageMap() {
    return &_CCmdTargetMessageMap;
}

const AFX_MSGMAP* CCmdTarget::getMessageMap() const {
    return &_CCmdTargetMessageMap;
}

bool CCmdTarget::dispatchMessage(unsigned int message, unsigned int id, void* param) {
    const AFX_MSGMAP* pMap = getMessageMap();
    while (pMap) {
        const AFX_MSGMAP_ENTRY* entry = pMap->lpEntries;
        if (!entry) break;

        while (entry->nMessage != 0) {
            if (entry->nMessage == message && entry->nID == id) {
                AFX_PMSG pfn = entry->pfn;
                (this->*pfn)(param); // 调用成员函数
                return true;
            }
            ++entry;
        }

        pMap = (pMap->pfnGetBaseMap) ? (*pMap->pfnGetBaseMap)() : nullptr;
    }
    return false;
}

bool CCmdTarget::onCmdMsg(unsigned int message, unsigned int id, void* param) {
    return dispatchMessage(message, id, param);
}

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/
