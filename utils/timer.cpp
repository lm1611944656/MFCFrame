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
#include "timer.h"

#ifdef _WIN32
#include <windows.h>

/** Windows上实现 gettimeofday*/
int gettimeofday(struct timeval *tv, void *tz) {
    FILETIME ft;
    ULONGLONG us;
    GetSystemTimeAsFileTime(&ft);
    us = ((ULONGLONG)ft.dwLowDateTime + ((ULONGLONG)ft.dwHighDateTime << 32)) / 10;
    us -= 11644473600000000ULL;  // 从 1601-01-01 到 1970-01-01 的微秒数
    if (tv) {
        tv->tv_sec = (long)(us / 1000000);
        tv->tv_usec = (long)(us % 1000000);
    }
    return 0;
}
#else
#include <sys/time.h>
#include <unistd.h>
#endif

/*获取当前时间(毫秒)*/
static uint64_t now_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*定时器比较函数*/
static int timer_less_than(const struct heap_node* ha, const struct heap_node* hb) {
    const timer_t* a = uv_queue_data(ha, timer_t, node_heap);
    const timer_t* b = uv_queue_data(hb, timer_t, node_heap);

    if (a->timeout < b->timeout) return 1;
    if (a->timeout > b->timeout) return 0;
    return a->start_id < b->start_id;
}

/*初始化循环*/
void timer_loop_init(timer_loop_t* loop) {
    heap_init(&loop->timer_heap);
    uv_queue_init(&loop->timer_ready);
    loop->time = now_ms();
    loop->timer_counter = 0;
}

/*初始化定时器*/
int timer_init(timer_loop_t* loop, timer_t* handle) {
    handle->loop = loop;
    handle->timer_cb = NULL;
    handle->timeout = 0;
    handle->repeat = 0;
    handle->start_id = 0;
    handle->active = 0;
    uv_queue_init(&handle->node_queue);
    return 0;
}

/*启动定时器*/
int timer_start(timer_t* handle, timer_cb cb, uint64_t timeout, uint64_t repeat) {
    if (cb == NULL) return -1;

    timer_stop(handle);  // 先停止

    uint64_t clamped_timeout = handle->loop->time + timeout;
    if (clamped_timeout < timeout)  // 防溢出
        clamped_timeout = (uint64_t)-1;

    handle->timer_cb = cb;
    handle->timeout = clamped_timeout;
    handle->repeat = repeat;
    handle->start_id = handle->loop->timer_counter++;
    handle->active = 1;

    heap_insert(&handle->loop->timer_heap, &handle->node_heap, timer_less_than);
    return 0;
}

/*停止定时器*/
int timer_stop(timer_t* handle) {
    if (handle->active) {
        heap_remove(&handle->loop->timer_heap, &handle->node_heap, timer_less_than);
        handle->active = 0;
    } else {
        if (uv_queue_next(&handle->node_queue) != &handle->node_queue) {
            uv_queue_remove(&handle->node_queue);
        }
    }
    uv_queue_init(&handle->node_queue);
    return 0;
}

/*重新启动（用于重复定时器）*/
int timer_again(timer_t* handle) {
    if (handle->timer_cb == NULL) return -1;
    if (handle->repeat) {
        return timer_start(handle, handle->timer_cb, handle->repeat, handle->repeat);
    }
    return 0;
}

/*设置重复间隔*/
void timer_set_repeat(timer_t* handle, uint64_t repeat) {
    handle->repeat = repeat;
}

/*获取重复间隔*/
uint64_t timer_get_repeat(const timer_t* handle) {
    return handle->repeat;
}

/*距离下次触发的时间*/
uint64_t timer_get_due_in(const timer_t* handle) {
    if (handle->loop->time >= handle->timeout)
        return 0;
    return handle->timeout - handle->loop->time;
}

/*下次 sleep 时间（毫秒）*/
int timer_next_timeout(const timer_loop_t* loop) {
    const struct heap_node* min_node = heap_min(&loop->timer_heap);
    if (!min_node) return -1;

    const timer_t* handle = uv_queue_data(min_node, timer_t, node_heap);
    if (handle->timeout <= loop->time)
        return 0;

    uint64_t diff = handle->timeout - loop->time;
    if (diff > INT_MAX) diff = INT_MAX;
    return (int)diff;
}

/*更新时间*/
void timer_update_time(timer_loop_t* loop) {
    loop->time = now_ms();
}

/*将到期定时器移入 ready 队列*/
void timer_run_pending(timer_loop_t* loop) {
    struct heap_node* node;
    timer_t* handle;

    while ((node = heap_min(&loop->timer_heap)) != NULL) {
        handle = uv_queue_data(node, timer_t, node_heap);
        if (handle->timeout > loop->time)
            break;

        timer_stop(handle);
        uv_queue_insert_tail(&loop->timer_ready, &handle->node_queue);
    }
}

/*执行所有 pending 回调*/
void timer_run_pending_callbacks(timer_loop_t* loop) {
    struct uv_queue* q;   // 使用 struct uv_queue*，不是 uv__queue
    timer_t* handle;

    while (!uv_queue_empty(&loop->timer_ready)) {
        q = uv_queue_head(&loop->timer_ready);
        uv_queue_remove(q);
        uv_queue_init(q);

        handle = uv_queue_data(q, timer_t, node_queue);

        timer_again(handle);              // 重复定时器自动重启
        handle->timer_cb(handle);         // 执行回调
    }
}

/*一键运行*/
void timer_run(timer_loop_t* loop) {
    timer_update_time(loop);
    timer_run_pending(loop);
    timer_run_pending_callbacks(loop);
}

/*************************************************************************
* 改动历史纪录：
Revision 1.0, 2025-11-04, lium
describe: 初始创建.
*************************************************************************/