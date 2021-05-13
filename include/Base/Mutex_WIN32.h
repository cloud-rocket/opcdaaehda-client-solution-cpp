/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the MutexImpl and FastMutexImpl classes for WIN32.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#ifndef TECHNOSOFTWARE_MUTEX_WIN32_H
#define TECHNOSOFTWARE_MUTEX_WIN32_H

#include "Base/Base.h"
#include "Base/Exception.h"
#include "Base/UnWindows.h"

namespace Technosoftware
{
    namespace Base
    {
        class TECHNOSOFTWARE_API MutexImpl
        {
        protected:
            MutexImpl();
            ~MutexImpl();
            void LockImpl();
            bool TryLockImpl();
            bool TryLockImpl(long milliseconds);
            void UnlockImpl();

        private:
            CRITICAL_SECTION cs_;
        };


        typedef MutexImpl FastMutexImpl;


        //
        // inlines
        //
        inline void MutexImpl::LockImpl()
        {
            try
            {
                EnterCriticalSection(&cs_);
            }
            catch (...)
            {
                throw SystemException("cannot lock mutex");
            }
        }


        inline bool MutexImpl::TryLockImpl()
        {
            try
            {
                return TryEnterCriticalSection(&cs_) != 0;
            }
            catch (...)
            {
            }
            throw SystemException("cannot lock mutex");
        }


        inline void MutexImpl::UnlockImpl()
        {
            LeaveCriticalSection(&cs_);
        }
    }
}

#endif /* TECHNOSOFTWARE_MUTEX_WIN32_H */
