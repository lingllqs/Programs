#include <iostream>
#include <mutex>
#include <atomic>

using namespace std;

class TaskQueue 
{
public:
//    TaskQueue() = delete;
    TaskQueue(const TaskQueue & t) = delete;
    TaskQueue &operator=(const TaskQueue &t) = delete;

    static TaskQueue * getInstance() 
    {
        TaskQueue *tq = m_taskQ.load();
        if (tq == nullptr)
        {
            m_mutex.lock();
            tq = m_taskQ.load();
            if (tq == nullptr)
            {
                tq = new TaskQueue;// 有线程安全问题
                m_taskQ.store(tq);
            }
            m_mutex.unlock();
        }
        return tq;
    }

    void print()
    {
        cout << "单例对象成员函数\n";
    }


private:
    TaskQueue() = default;
    /* 
     *  TaskQueue(const TaskQueue & t) = default;
     *  TaskQueue & operator=(const TaskQueue & t) = default;
     */
    //static TaskQueue * m_taskQ;
    static atomic<TaskQueue *> m_taskQ;
    static mutex m_mutex;
};

//TaskQueue * TaskQueue::m_taskQ = new TaskQueue;
atomic<TaskQueue *> TaskQueue::m_taskQ;
mutex TaskQueue::m_mutex;

int main()
{
    TaskQueue *taskQ = TaskQueue::getInstance();
    taskQ->print();

    return 0;
}
