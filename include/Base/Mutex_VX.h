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

#ifndef Foundation_Mutex_VX_INCLUDED
#define Foundation_Mutex_VX_INCLUDED

#include "Base/Base.h"
#include "Base/Exception.h"
#include <semLib.h>
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
            SEM_ID _sem;
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
            if (semTake(_sem, WAIT_FOREVER) != OK)
                throw SystemException("cannot lock mutex");
        }


        inline bool MutexImpl::TryLockImpl()
        {
            return semTake(_sem, NO_WAIT) == OK;
        }


        inline void MutexImpl::UnlockImpl()
        {
            if (semGive(_sem) != OK)
                throw SystemException("cannot unlock mutex");
        }
    }
}

#endif /* TECHNOSOFTWARE_MUTEX_VX_H */
