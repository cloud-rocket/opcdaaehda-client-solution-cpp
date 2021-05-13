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

#include "Base/Mutex_WIN32.h"
#include "Base/Timestamp.h"

namespace Technosoftware
{
    namespace Base
    {
        MutexImpl::MutexImpl()
        {
            // the fct has a boolean return value under WInnNt/2000/XP but not on Win98
            // the return only checks if the input address of &cs_ was valid, so it is safe to omit it
            InitializeCriticalSectionAndSpinCount(&cs_, 4000);
        }


        MutexImpl::~MutexImpl()
        {
            DeleteCriticalSection(&cs_);
        }


        bool MutexImpl::TryLockImpl(long milliseconds)
        {
            const int sleepMillis = 5;
            Timestamp now;
            Timestamp::TimeDiff diff(Timestamp::TimeDiff(milliseconds) * 1000);
            do
            {
                try
                {
                    if (TryEnterCriticalSection(&cs_) == TRUE)
                        return true;
                }
                catch (...)
                {
                    throw SystemException("cannot lock mutex");
                }
                Sleep(sleepMillis);
            } while (!now.IsElapsed(diff));
            return false;
        }
    }
}