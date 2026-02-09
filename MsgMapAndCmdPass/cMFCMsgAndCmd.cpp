/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: cMFCMsgAndCmd.cpp
*   软件模块: 应用
*   版 本 号: 2.0
*   生成日期: 2026-02-09
*   作    者: lium
*   功    能: MFC风格消息映射与命令传递（哈希索引加速版）
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

/*-----------------------------------------
 * 构建哈希索引缓存
 *-----------------------------------------*/
void CCmdTarget::buildMsgMapCache() const {
    if (m_msgMapBuilt) return;

    const AFX_MSGMAP* pMap = getMessageMap();
    while (pMap) {
        const AFX_MSGMAP_ENTRY* entry = pMap->lpEntries;
        if (!entry) break;

        while (entry->nMessage != 0) {
            MsgKey key{ entry->nMessage, entry->nID };

            // 子类优先，不覆盖已有的 handler
            if (m_msgMapCache.find(key) == m_msgMapCache.end()) {
                m_msgMapCache[key] = entry->pfn;
            }

            ++entry;
        }

        pMap = (pMap->pfnGetBaseMap) ? (*pMap->pfnGetBaseMap)() : nullptr;
    }

    m_msgMapBuilt = true;
}

/*-----------------------------------------
 * 消息派发
 *-----------------------------------------*/
bool CCmdTarget::dispatchMessage(unsigned int message, unsigned int id, void* param) {
    buildMsgMapCache();  // 第一次用时构建索引

    MsgKey key{ message, id };
    auto it = m_msgMapCache.find(key);
    if (it != m_msgMapCache.end()) {
        AFX_PMSG pfn = it->second;
        if (pfn) {
            (this->*pfn)(param);
            return true;
        }
    }
    return false;
}

bool CCmdTarget::onCmdMsg(unsigned int message, unsigned int id, void* param) {
    return dispatchMessage(message, id, param);
}

/*************************************************************************
* 改动历史纪录：
Revision 2.0, 2026-02-09, lium
describe: 增加哈希索引缓存，dispatchMessage 性能优化。
*************************************************************************/
