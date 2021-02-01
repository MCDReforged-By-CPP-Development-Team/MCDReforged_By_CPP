#pragma once
//来自 https://blog.csdn.net/luoweifu/article/details/51449364
#ifndef CTHREAD_H_

#include <windows.h>

// 封装的线程类
class CThread
{
public:
    CThread()
        : m_bStopped(false)
    {
        m_hThread = CreateThread(NULL, 0, StartRoutine, this, CREATE_SUSPENDED, &m_nId);
    }

    virtual ~CThread()
    {
        if (m_hThread) {
            CloseHandle(m_hThread);
        }
    }

protected:
    // 执行函数，子类应该实现这个方法，否则线程什么也不做
    virtual void Run()
    {
    }

public:
    // 开始执行线程
    virtual void Start()
    {
        ResumeThread(m_hThread);
    }

    // 线程是否停止
    bool Stopped()
    {
        return m_bStopped;
    }


    void Join()
    {
        if (m_hThread) {
            WaitForSingleObject(m_hThread, INFINITE);
        }
    }

private:
    // 线程执行的起始地址，也叫线程函数
    static DWORD WINAPI StartRoutine(LPVOID param)
    {
        CThread* thread = (CThread*)param;
        thread->Run();
        thread->m_bStopped = true;
        return 0;
    }

private:
    HANDLE          m_hThread;      // 线程句柄
    bool            m_bStopped;     // 线程是否停止
    DWORD           m_nId;          // 线程ID
};

// 封装的互斥量类
class CMutex
{

public:
    CMutex()
    {
        // 创建互斥量锁
        m_hMutex = CreateMutex(NULL, FALSE, NULL);
    }
    ~CMutex()
    {
        // 释放互斥量锁
        if (m_hMutex)
            CloseHandle(m_hMutex);
    }

public:
    // 加锁，获取互斥量锁，锁定资源
    bool Lock()
    {
        if (m_hMutex)
        {
            return WaitForSingleObject(m_hMutex, INFINITE) == WAIT_OBJECT_0;
        }
        return false;
    }

    // 试图锁定资源，判断当前的互斥量是否被占用。
    // 返回true说明该锁为非占用状态，可获得该锁；返回false说明该锁为占用状态，需等待被释放
    bool TryLock()
    {
        if (m_hMutex) {
            return WaitForSingleObject(m_hMutex, 0) == WAIT_OBJECT_0;
        }
        return false;
    }

    // 解锁，释放互斥量锁
    void Unlock()
    {
        if (m_hMutex)
            ReleaseMutex(m_hMutex);
    }

private:
    HANDLE          m_hMutex;       // 互斥量句柄
};

// 互斥量锁的抽象
// 只要声明该对象即锁定资源，当退出其(该对象)作用域时即释放锁
class CLock
{
public:
    CLock(CMutex& mutex)
        : m_mutex(mutex)
    {
        m_bLocked = m_mutex.Lock();
    }

    ~CLock()
    {
        if (m_bLocked)
            m_mutex.Unlock();
    }

private:
    // 禁用赋值操作符
    CLock& operator = (CLock&)
    {
        return *this;
    }

private:
    CMutex& m_mutex;        // 互斥量句柄的引用
    bool            m_bLocked;      // 互斥量是否被锁定(占用)
};

#endif  // CTHREAD_H_