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

#ifndef TECHNOSOFTWARE_MUTEX_POSIX_H
#define TECHNOSOFTWARE_MUTEX_POSIX_H

#include "Base/Base.h"
#include "Base/Exception.h"
#include <pthread.h>
#include <errno.h>

namespace Technosoftware
{
    namespace Base
    {
        class TECHNOSOFTWARE_API MutexImpl
        {
        protected:
            MutexImpl();
            MutexImpl(bool fast);
            ~MutexImpl();
            void LockImpl();
            bool TryLockImpl();
            bool TryLockImpl(long milliseconds);
            void UnlockImpl();

        private:
            pthread_mutex_t mutex_;
        };


        class TECHNOSOFTWARE_API FastMutexImpl : public MutexImpl
        {
        protected:
            FastMutexImpl();
            ~FastMutexImpl();
        };


        //
        // inlines
        //
        inline void MutexImpl::LockImpl()
        {
            if (pthread_mutex_lock(&mutex_))
                throw SystemException("cannot lock mutex");
        }


        inline bool MutexImpl::TryLockImpl()
        {
            int rc = pthread_mutex_trylock(&mutex_);
            if (rc == 0)
                return true;
            else if (rc == EBUSY)
                return false;
            else
                throw SystemException("cannot lock mutex");
        }


        inline void MutexImpl::UnlockImpl()
        {
            if (pthread_mutex_unlock(&mutex_))
                throw SystemException("cannot unlock mutex");
        }
    }
}

#endif /* TECHNOSOFTWARE_MUTEX_POSIX_H */
