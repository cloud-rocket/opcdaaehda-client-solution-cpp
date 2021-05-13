/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the RWLockImpl class for POSIX Threads (VxWorks).
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#ifndef TECHNOSOFTWARE_RWLOCK_VX_H
#define TECHNOSOFTWARE_RWLOCK_VX_H

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
            void readLockImpl();
            bool tryReadLockImpl();
            void writeLockImpl();
            bool tryWriteLockImpl();
            void unlockImpl();

        private:
            pthread_mutex_t mutex_;
        };


        //
        // inlines
        //
        inline void RWLockImpl::ReadLockImpl()
        {
            if (pthread_mutex_lock(&mutex_))
                throw SystemException("cannot lock mutex");
        }


        inline bool RWLockImpl::TryReadLockImpl()
        {
            int rc = pthread_mutex_trylock(&mutex_);
            if (rc == 0)
                return true;
            else if (rc == EBUSY)
                return false;
            else
                throw SystemException("cannot lock mutex");

        }


        inline void RWLockImpl::WriteLockImpl()
        {
            readLockImpl();
        }


        inline bool RWLockImpl::TryWriteLockImpl()
        {
            return tryReadLockImpl();

        }


        inline void RWLockImpl::UnlockImpl()
        {
            if (pthread_mutex_unlock(&mutex_))
                throw SystemException("cannot unlock mutex");
        }
    }
}

#endif /* TECHNOSOFTWARE_RWLOCK_VX_H */
