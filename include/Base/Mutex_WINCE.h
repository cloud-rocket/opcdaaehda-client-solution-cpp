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

#ifndef Foundation_Mutex_WINCE_INCLUDED
#define Foundation_Mutex_WINCE_INCLUDED

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
            HANDLE mutex_;
        };

        typedef MutexImpl FastMutexImpl;
    }
}

#endif /* TECHNOSOFTWARE_MUTEX_WINCE_H */
