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


#ifndef TECHNOSOFTWARE_RWLOCK_POSIX_H
#define TECHNOSOFTWARE_RWLOCK_POSIX_H

#include "Base/Base.h"
#include "Base/Exception.h"
#include <pthread.h>
#include <errno.h>

namespace Technosoftware
{
    namespace Base
    {
        class TECHNOSOFTWARE_API RWLockImpl
        {
        protected:
            RWLockImpl();
            ~RWLockImpl();
            void ReadLockImpl();
            bool TryReadLockImpl();
            void WriteLockImpl();
            bool TryWriteLockImpl();
            void UnlockImpl();

        private:
            pthread_rwlock_t _rwl;
        };


        //
        // inlines
        //
        inline void RWLockImpl::ReadLockImpl()
        {
            if (pthread_rwlock_rdlock(&_rwl))
                throw SystemException("cannot lock reader/writer lock");
        }


        inline bool RWLockImpl::TryReadLockImpl()
        {
            int rc = pthread_rwlock_tryrdlock(&_rwl);
            if (rc == 0)
                return true;
            else if (rc == EBUSY)
                return false;
            else
                throw SystemException("cannot lock reader/writer lock");

        }


        inline void RWLockImpl::WriteLockImpl()
        {
            if (pthread_rwlock_wrlock(&_rwl))
                throw SystemException("cannot lock reader/writer lock");
        }


        inline bool RWLockImpl::TryWriteLockImpl()
        {
            int rc = pthread_rwlock_trywrlock(&_rwl);
            if (rc == 0)
                return true;
            else if (rc == EBUSY)
                return false;
            else
                throw SystemException("cannot lock reader/writer lock");

        }


        inline void RWLockImpl::UnlockImpl()
        {
            if (pthread_rwlock_unlock(&_rwl))
                throw SystemException("cannot unlock mutex");
        }
    }
}

#endif /* TECHNOSOFTWARE_RWLOCK_POSIX_H */
