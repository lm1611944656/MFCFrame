/*************************************************************************
*
*   Copyright (C), 2025-2045, bpg. Co., Ltd.
*
*   文件名称: timer.h
*   软件模块: 通用数据结构
*   版 本 号: 1.0
*   生成日期: 2025-11-04
*   作    者: lium
*   功    能: 基于最小堆和链表实现定时器
*
**********************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "heap.h"
#include "linklist.h"
#include <stdint.h>
#include <limits.h>

struct timer_t;
struct timer_loop;

typedef void (*timer_cb)(struct timer_t* handle);

typedef struct timer_t {
    struct heap_node node_heap;
    struct uv_queue node_queue;
    struct timer_loop* loop;
    timer_cb timer_cb;
    uint64_t timeout;
    uint64_t repeat;
    uint64_t start_id;
    unsigned int active : 1;
} timer_t;

typedef struct timer_loop {
    struct heap timer_heap;
    struct uv_queue timer_ready;
    uint64_t time;
    uint64_t timer_counter;
} timer_loop_t;

// API declarations
void timer_loop_init(timer_loop_t* loop);
int timer_init(timer_loop_t* loop, timer_t* handle);
int timer_start(timer_t* handle, timer_cb cb, uint64_t timeout, uint64_t repeat);
int timer_stop(timer_t* handle);
int timer_again(timer_t* handle);
void timer_set_repeat(timer_t* handle, uint64_t repeat);
uint64_t timer_get_repeat(const timer_t* handle);
uint64_t timer_get_due_in(const timer_t* handle);
int timer_next_timeout(const timer_loop_t* loop);
void timer_run_pending(timer_loop_t* loop);
void timer_update_time(timer_loop_t* loop);
void timer_run(timer_loop_t* loop);

#ifdef __cplusplus
}
#endif

#endif // TIMER_H_

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/