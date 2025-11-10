#ifdef _WIN32
#include <windows.h>
#define sleep_ms(x) Sleep(x)
#else
#include <unistd.h>
  #define sleep_ms(x) usleep((x) * 1000)
#endif

#include "timer.h"
#include <iostream>


// 定义三个定时器句柄
timer_t timer1;  // 每1s执行（周期）
timer_t timer2;  // 第10s执行（一次性）
timer_t timer3;  // 每2s执行，5次后停止

// 任务1：每1秒打印一次
void task1_callback(timer_t* handle) {
    std::cout << "[Task 1] Tick every 1 second." << std::endl;
    // 无需手动重启，repeat=1000 会自动重复
}

// 任务2：只在第10秒执行一次
void task2_callback(timer_t* handle) {
    std::cout << "[Task 2] Executed at 10 seconds!" << std::endl;
    // 只执行一次，无需做任何事
}

// 任务3：每2秒执行，执行5次后自动停止
void task3_callback(timer_t* handle) {
    // 使用 handle->repeat 字段来记录执行次数（或用外部变量）
    static int count = 0;
    std::cout << "[Task 3] Interval " << ++count << " / 5" << std::endl;

    if (count >= 5) {
        timer_stop(handle);
        std::cout << "[Task 3] Stopped after 5 executions." << std::endl;
    }
}

int main() {
    timer_loop_t loop;

    // 初始化定时器循环
    timer_loop_init(&loop);

    // =============== 注册三个任务 ===============

    // 任务1：每1秒执行一次（循环执行此任务）
    timer_init(&loop, &timer1);
    timer_start(&timer1, task1_callback, 1000, 1000);  // 1s 后开始，每1s重复

    // 任务2：第10秒执行一次（只执行该任务1次）
    timer_init(&loop, &timer2);
    timer_start(&timer2, task2_callback, 10000, 0);    // 10000ms = 10s，不重复

    // 任务3：每2秒执行一次（最多执行该任务5次）
    timer_init(&loop, &timer3);
    timer_start(&timer3, task3_callback, 2000, 2000);  // 2s 后开始，每2s重复

    std::cout << "Timer system started... Waiting for tasks..." << std::endl;

    // 主事件循环
    while (true) {
        int timeout = timer_next_timeout(&loop);
        if (timeout < 0) {
            std::cout << "All timers finished. Exiting." << std::endl;
            break;
        }

        // 睡眠指定时间（毫秒）
#ifdef _WIN32
        Sleep(timeout);
#else
        usleep(timeout * 1000);  // usleep 参数是微秒
#endif

        // 更新时间并运行定时器
        timer_update_time(&loop);
        timer_run_pending(&loop);
        timer_run(&loop);
    }

    return 0;
}