#include "taskqueue.h"
#include <stdlib.h>

TaskQueue *taskqueue_create(int capacity)
{
    err_proc(capacity <= 0, argument, goto ERR1);

    TaskQueue *taskqueue = (TaskQueue *)malloc(sizeof(TaskQueue));
    err_proc(!taskqueue, malloc, goto ERR1);

    taskqueue->tasks = (Task *)malloc(sizeof(Task) * capacity);
    err_proc(!taskqueue->tasks, malloc, goto ERR2);

    taskqueue->capacity = capacity;
    taskqueue->size = 0;
    taskqueue->front = 0;
    taskqueue->rear = 0;

    return taskqueue;

ERR2:
    free(taskqueue);
ERR1:
    return NULL;
}

Task *task_create(void (*task_func)(void *), void *arg)
{
    err_proc(!task_func, argument, goto ERR1);

    Task *task = (Task *)malloc(sizeof(Task));
    err_proc(!task, malloc, goto ERR1);

    task->task_func = task_func;
    task->arg = arg;

    return task;

ERR1:
    return NULL;
}

void taskqueue_enqueue(TaskQueue *taskqueue, Task *task)
{
    err_proc(!taskqueue || !task, argument, return);

    if (taskqueue->size < taskqueue->capacity)
    {
        taskqueue->tasks[taskqueue->rear].task_func = task->task_func;
        taskqueue->tasks[taskqueue->rear].arg = task->arg;
        taskqueue->rear = (taskqueue->rear + 1) % taskqueue->capacity;
        taskqueue->size++;
    }
}

Task *taskqueue_dequeue(TaskQueue *taskqueue)
{
    err_proc(!taskqueue, argument, return NULL);

    Task *task;
    if (taskqueue->size > 0)
    {
        task->task_func = taskqueue->tasks[taskqueue->front].task_func;
        task->arg = taskqueue->tasks[taskqueue->front].arg;
        taskqueue->front = (taskqueue->front + 1) % taskqueue->capacity;
        taskqueue->size--;
    }

    return task;
}

bool taskqueue_isempty(TaskQueue *taskqueue)
{
    return taskqueue->size == 0 ? true : false;
}

bool taskqueue_isfull(TaskQueue *taskqueue)
{
    return taskqueue->size == taskqueue->capacity ? true : false;
}
