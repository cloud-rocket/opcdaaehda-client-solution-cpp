/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the RWLockImpl class for Android Threads.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#include "Base/RWLock_Android.h"

namespace Technosoftware
{
    namespace Base
    {


RWLockImpl::RWLockImpl()
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    if (pthread_mutex_init(&mutex_, &attr))
    {
        pthread_mutexattr_destroy(&attr);
        throw SystemException("cannot create mutex");
    }
    pthread_mutexattr_destroy(&attr);}


RWLockImpl::~RWLockImpl()
{
    pthread_mutex_destroy(&mutex_);
}


    }
}
