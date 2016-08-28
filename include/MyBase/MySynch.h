#ifndef MY_SYNCH_H
#define MY_SYNCH_H

#ifdef WIN32

#include <windows.h>

// ��
#define MUTEX HANDLE
#define MUTEX_INIT(mutex) mutex = CreateMutex(NULL, false, NULL)
#define MUTEX_DESTROY(mutex) CloseHandle(mutex); mutex = NULL
#define MUTEX_LOCK(mutex) WaitForSingleObject(mutex, INFINITE)
#define MUTEX_UNLOCK(mutex) ReleaseMutex(mutex)
#define MUTEX_WAIT_TIME(mutex, time) WaitForSingleObject(mutex, time)

// �ź���
#define SEMA HANDLE
#define SEMA_INIT(sema, init, total) CreateSemaphore(NULL, init, total, NULL)
#define SEMA_DESTROY(sema) CloseHandle(sema); mutex = NULL
#define SEMA_WAIT(sema) WaitForSingleObject(sema, INFINITE)
#define SEMA_POST(sema) ReleaseSemaphore(sema, 1, NULL)
#define SEMA_WAIT_TIME(sema, time) WaitForSingleObject(sema, time)

// �ٽ�����todo

#endif

#endif//MY_SYNCH_H