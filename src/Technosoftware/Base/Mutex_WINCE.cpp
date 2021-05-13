/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the MutexImpl and FastMutexImpl classes for WINDOWS CE.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#include "Base/Mutex_WINCE.h"

namespace Technosoftware
{
    namespace Base
    {


        MutexImpl::MutexImpl()
        {
            mutex_ = CreateMutexW(NULL, FALSE, NULL);
            if (!mutex_) throw SystemException("cannot create mutex");
        }


        MutexImpl::~MutexImpl()
        {
            CloseHandle(mutex_);
        }


        void MutexImpl::lockImpl()
        {
            switch (WaitForSingleObject(mutex_, INFINITE))
            {
            case WAIT_OBJECT_0:
                return;
            default:
                throw SystemException("cannot lock mutex");
            }
        }


        bool MutexImpl::tryLockImpl()
        {
            switch (WaitForSingleObject(mutex_, 0))
            {
            case WAIT_TIMEOUT:
                return false;
            case WAIT_OBJECT_0:
                return true;
            default:
                throw SystemException("cannot lock mutex");
            }
        }


        bool MutexImpl::tryLockImpl(long milliseconds)
        {
            switch (WaitForSingleObject(mutex_, milliseconds + 1))
            {
            case WAIT_TIMEOUT:
                return false;
            case WAIT_OBJECT_0:
                return true;
            default:
                throw SystemException("cannot lock mutex");
            }
        }


        void MutexImpl::unlockImpl()
        {
            ReleaseMutex(mutex_);
        }


    }
}
