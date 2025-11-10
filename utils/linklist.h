/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: linklist.h
*   软件模块: 通用数据结构
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: 链表的通用数据结构
*
**********************************************************************/
#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h>

/* 内部链表节点结构体 */
struct uv_queue {
    struct uv_queue *next;
    struct uv_queue *prev;
};

/* 从链表节点指针获取包含它的结构体指针 */
#define uv_queue_data(pointer, type, field)                                  \
  ((type*) ((char*) (pointer) - offsetof(type, field)))

/* 遍历链表（不包括头节点） */
#define uv_queue_foreach(q, h)                                               \
  for ((q) = (h)->next; (q) != (h); (q) = (q)->next)

/* 初始化链表头（形成循环） */
static inline void uv_queue_init(struct uv_queue *q) {
    q->next = q;
    q->prev = q;
}

/* 判断链表是否为空（只有头节点） */
static inline int uv_queue_empty(const struct uv_queue *q) {
    return q == q->next;
}

/* 获取链表第一个节点 */
static inline struct uv_queue *uv_queue_head(const struct uv_queue *q) {
    return q->next;
}

/* 获取下一个节点 */
static inline struct uv_queue *uv_queue_next(const struct uv_queue *q) {
    return q->next;
}

/* 将队列 n 添加到 h 后面（拼接两个链表）*/
static inline void uv_queue_add(struct uv_queue *h, struct uv_queue *n) {
    h->prev->next = n->next;
    n->next->prev = h->prev;
    h->prev = n->prev;
    h->prev->next = h;
}

/* 拆分链表：将 [n, q) 段从 h 链表中分离 */
static inline void uv_queue_split(struct uv_queue *h,
                                  struct uv_queue *q,
                                  struct uv_queue *n) {
    n->prev = h->prev;
    n->prev->next = n;
    n->next = q;
    h->prev = q->prev;
    h->prev->next = h;
    q->prev = n;
}

/* 移动整个链表 h 到 n 前面 */
static inline void uv_queue_move(struct uv_queue *h, struct uv_queue *n) {
    if (uv_queue_empty(h))
        uv_queue_init(n);
    else
        uv_queue_split(h, h->next, n);
}

/* 插入到头部 */
static inline void uv_queue_insert_head(struct uv_queue *h,
                                        struct uv_queue *q) {
    q->next = h->next;
    q->prev = h;
    q->next->prev = q;
    h->next = q;
}

/* 插入到尾部 */
static inline void uv_queue_insert_tail(struct uv_queue *h,
                                        struct uv_queue *q) {
    q->next = h;
    q->prev = h->prev;
    q->prev->next = q;
    h->prev = q;
}

/* 从链表中移除节点 */
static inline void uv_queue_remove(struct uv_queue *q) {
    q->prev->next = q->next;
    q->next->prev = q->prev;
}

#endif /* QUEUE_H_ */

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/