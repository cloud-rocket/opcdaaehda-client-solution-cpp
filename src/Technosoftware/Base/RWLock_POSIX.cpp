/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the RWLockImpl class for POSIX Threads.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */


#include "Base/RWLock_POSIX.h"


namespace Technosoftware
{
    namespace Base
    {


RWLockImpl::RWLockImpl()
{
    if (pthread_rwlock_init(&_rwl, NULL))
        throw SystemException("cannot create reader/writer lock");
}


RWLockImpl::~RWLockImpl()
{
    pthread_rwlock_destroy(&_rwl);
}


    }
}
