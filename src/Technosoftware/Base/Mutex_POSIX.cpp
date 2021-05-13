/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the MutexImpl and FastMutexImpl classes for POSIX Threads.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#include "Base/Mutex_POSIX.h"
#include "Base/Timestamp.h"
#if !defined(TECHNOSOFTWARE_NO_SYS_SELECT_H)
#include <sys/select.h>
#endif
#include <unistd.h>
#if defined(TECHNOSOFTWARE_VXWORKS)
#include <timers.h>
#include <cstring>
#else
#include <sys/time.h>
#endif


#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS - 200112L) >= 0L
#if defined(_POSIX_THREADS) && (_POSIX_THREADS - 200112L) >= 0L
	#if defined(_POSIX_THREADS) && (_POSIX_THREADS - 200112L) >= 0L
		#define TECHNOSOFTWARE_HAVE_MUTEX_TIMEOUT
	#endif
#endif


#ifndef TECHNOSOFTWARE_HAVE_CLOCK_GETTIME
	#if (defined(_POSIX_TIMERS) && defined(CLOCK_REALTIME)) || defined(POCO_VXWORKS) || defined(__QNX__)
		#ifndef __APPLE__ // See GitHub issue #1453 - not available before Mac OS 10.12/iOS 10
			#define TECHNOSOFTWARE_HAVE_CLOCK_GETTIME
		#endif
	#endif
#endif


namespace Technosoftware
{
    namespace Base
    {


MutexImpl::MutexImpl()
{
#if defined(TECHNOSOFTWARE_VXWORKS)
    // This workaround is for VxWorks 5.x where
    // pthread_mutex_init() won't properly initialize the mutex
    // resulting in a subsequent freeze in pthread_mutex_destroy()
    // if the mutex has never been used.
    std::memset(&mutex_, 0, sizeof(mutex_));
#endif
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
#if defined(PTHREAD_MUTEX_RECURSIVE_NP)
    pthread_mutexattr_settype_np(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
#elif !defined(TECHNOSOFTWARE_VXWORKS) 
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
#endif
    if (pthread_mutex_init(&mutex_, &attr))
    {
        pthread_mutexattr_destroy(&attr);
        throw SystemException("cannot create mutex");
    }
    pthread_mutexattr_destroy(&attr);
}


MutexImpl::MutexImpl(bool fast)
{
#if defined(TECHNOSOFTWARE_VXWORKS)
    // This workaround is for VxWorks 5.x where
    // pthread_mutex_init() won't properly initialize the mutex
    // resulting in a subsequent freeze in pthread_mutex_destroy()
    // if the mutex has never been used.
    std::memset(&mutex_, 0, sizeof(mutex_));
#endif
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
#if defined(PTHREAD_MUTEX_RECURSIVE_NP)
    pthread_mutexattr_settype_np(&attr, fast ? PTHREAD_MUTEX_NORMAL_NP : PTHREAD_MUTEX_RECURSIVE_NP);
#elif !defined(TECHNOSOFTWARE_VXWORKS)
    pthread_mutexattr_settype(&attr, fast ? PTHREAD_MUTEX_NORMAL : PTHREAD_MUTEX_RECURSIVE);
#endif
    if (pthread_mutex_init(&mutex_, &attr))
    {
        pthread_mutexattr_destroy(&attr);
        throw SystemException("cannot create mutex");
    }
    pthread_mutexattr_destroy(&attr);
}


MutexImpl::~MutexImpl()
{
    pthread_mutex_destroy(&mutex_);
}


bool MutexImpl::tryLockImpl(long milliseconds)
{
#if defined(TECHNOSOFTWARE_HAVE_MUTEX_TIMEOUT)
    struct timespec abstime;
#if defined(TECHNOSOFTWARE_HAVE_CLOCK_GETTIME)
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec  += milliseconds / 1000;
    abstime.tv_nsec += (milliseconds % 1000)*1000000;
    if (abstime.tv_nsec >= 1000000000)
    {
        abstime.tv_nsec -= 1000000000;
        abstime.tv_sec++;
    }
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    abstime.tv_sec  = tv.tv_sec + milliseconds / 1000;
    abstime.tv_nsec = tv.tv_usec*1000 + (milliseconds % 1000)*1000000;
    if (abstime.tv_nsec >= 1000000000)
    {
        abstime.tv_nsec -= 1000000000;
        abstime.tv_sec++;
    }
#endif
    int rc = pthread_mutex_timedlock(&mutex_, &abstime);
    if (rc == 0)
        return true;
    else if (rc == ETIMEDOUT)
        return false;
    else
        throw SystemException("cannot lock mutex");
#else
    const int sleepMillis = 5;
    Timestamp now;
    Timestamp::TimeDiff diff(Timestamp::TimeDiff(milliseconds)*1000);
    do
    {
        int rc = pthread_mutex_trylock(&mutex_);
        if (rc == 0)
            return true;
        else if (rc != EBUSY)
            throw SystemException("cannot lock mutex");
#if defined(TECHNOSOFTWARE_VXWORKS)
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = sleepMillis*1000000;
        nanosleep(&ts, NULL);
        
#else
        struct timeval tv;
        tv.tv_sec  = 0;
        tv.tv_usec = sleepMillis * 1000;
        select(0, NULL, NULL, NULL, &tv);
#endif
    }
    while (!now.isElapsed(diff));
    return false;
#endif
}


FastMutexImpl::FastMutexImpl(): MutexImpl(true)
{
}


FastMutexImpl::~FastMutexImpl()
{
}

}
}
