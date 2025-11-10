/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: cMFCMsgAndCmd.h
*   软件模块: 应用
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: MFC的消息映射与命令传递
*
**********************************************************************/

#ifndef CMFCMSGANDCMD_H
#define CMFCMSGANDCMD_H

#include <iostream>

typedef enum MsgType{
    MSG_COMMAND = 0x001,
    MSG_DESTROY = 0x002,
    MSG_SIZE    = 0x003
}TMsgType_t;

// 前向声明
class CCmdTarget;

// 成员函数指针类型，支持 void* 参数
typedef void (CCmdTarget::*AFX_PMSG)(void* param);

// 消息表项
struct AFX_MSGMAP_ENTRY {
    unsigned int nMessage;
    unsigned int nCode;
    unsigned int nID;
    unsigned int nLastID;
    unsigned int nSig;
    AFX_PMSG pfn;
};

// 消息映射表
struct AFX_MSGMAP {
    const AFX_MSGMAP* (*pfnGetBaseMap)();
    const AFX_MSGMAP_ENTRY* lpEntries;
};

#ifndef PASCAL
#define PASCAL
#endif

// 类声明用宏
#define DECLARE_MESSAGE_MAP() \
protected: \
    static const AFX_MSGMAP* PASCAL getThisMessageMap(); \
    virtual const AFX_MSGMAP* getMessageMap() const;

// 消息表宏
#define BEGIN_MESSAGE_MAP(theClass, baseClass) \
    const AFX_MSGMAP* theClass::getMessageMap() const { return getThisMessageMap(); } \
    const AFX_MSGMAP* PASCAL theClass::getThisMessageMap() { \
        typedef theClass ThisClass; \
        typedef baseClass TheBaseClass; \
        static const AFX_MSGMAP_ENTRY _messageEntries[] = {

#define END_MESSAGE_MAP() \
    {0,0,0,0,0,(AFX_PMSG)0} }; \
    static const AFX_MSGMAP messageMap = { &TheBaseClass::getThisMessageMap, &_messageEntries[0] }; \
    return &messageMap; }

#define ON_COMMAND(id, memberFxn) \
    { MSG_COMMAND, 0, (unsigned int)id, (unsigned int)id, 0, static_cast<AFX_PMSG>(memberFxn) },

#define ON_DESTROY(memberFxn) \
    { MSG_DESTROY, 0, 0, 0, 0, static_cast<AFX_PMSG>(memberFxn) },

#define ON_SIZE(memberFxn) \
    { MSG_SIZE, 0, 0, 0, 0, static_cast<AFX_PMSG>(memberFxn) },


// 基类
class CCmdTarget {
public:
    CCmdTarget() = default;
    virtual ~CCmdTarget() = default;

    virtual const AFX_MSGMAP* getMessageMap() const;
    static const AFX_MSGMAP* PASCAL getThisMessageMap();

    // 派发消息，void* param 可传 NULL 或实际指针
    bool dispatchMessage(unsigned int message, unsigned int id, void* param = nullptr);

protected:
    bool onCmdMsg(unsigned int message, unsigned int id, void* param = nullptr);
};

#endif // CMFCMSGANDCMD_H

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/