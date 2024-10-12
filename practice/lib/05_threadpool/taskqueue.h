#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <stdbool.h>
#include <stdio.h>

#define err_proc(condition, message, process)                                                                                                                                      \
    do                                                                                                                                                                             \
    {                                                                                                                                                                              \
        if (condition)                                                                                                                                                             \
        {                                                                                                                                                                          \
            fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #message);                                                                                                          \
            process;                                                                                                                                                               \
        }                                                                                                                                                                          \
    } while (0);

typedef struct Task
{
    void (*task_func)(void *); // 任务函数
    void *arg;                 // 参数
} Task;

typedef struct TaskQueue
{
    Task *tasks;  // 任务
    int capacity; // 队列容量
    int size;     // 任务数量
    int front;    // 队头
    int rear;     // 队尾
} TaskQueue;

TaskQueue *taskqueue_create(int capacity);                // 创建任务队列
Task *task_create(void (*task_func)(void *), void *arg);  // 创建任务
void taskqueue_enqueue(TaskQueue *taskqueue, Task *task); // 入队
Task *taskqueue_dequeue(TaskQueue *taskqueue);            // 出队

bool taskqueue_isempty(TaskQueue *taskqueue); // 队列是否为空
bool taskqueue_isfull(TaskQueue *taskqueue);  // 队列是否为满

#endif // !task_queue_h
