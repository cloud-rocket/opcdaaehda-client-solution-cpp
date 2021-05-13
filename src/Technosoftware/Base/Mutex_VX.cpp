/*
* Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
* Web: https://technosoftware.com
*
* Purpose:
* Definition of the MutexImpl and FastMutexImpl classes for VxWorks.
*
* Based on: POCO C++ Foundation Library
*           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
*           and Contributors.
*
* The Software is subject to the Technosoftware GmbH Software License Agreement,
* which can be found here:
* https://technosoftware.com/documents/Technosoftware_SLA.pdf
*/

#include "Base/Mutex_VX.h"
#include <sysLib.h>

namespace Technosoftware
{
    namespace Base
    {


        MutexImpl::MutexImpl()
        {
            _sem = semMCreate(SEM_INVERSION_SAFE | SEM_Q_PRIORITY);
            if (_sem == 0)
                throw Base::SystemException("cannot create mutex");
        }


        MutexImpl::MutexImpl(bool fast)
        {
            if (fast)
            {
                _sem = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
            }
            else
            {
                _sem = semMCreate(SEM_INVERSION_SAFE | SEM_Q_PRIORITY);
            }
            if (_sem == 0)
                throw Base::SystemException("cannot create mutex");
        }


        MutexImpl::~MutexImpl()
        {
            semDelete(_sem);
        }


        bool MutexImpl::tryLockImpl(long milliseconds)
        {
            int ticks = milliseconds*sysClkRateGet() / 1000;
            return semTake(_sem, ticks) == OK;
        }


        FastMutexImpl::FastMutexImpl() : MutexImpl(true)
        {
        }


        FastMutexImpl::~FastMutexImpl()
        {
        }


    }
}
