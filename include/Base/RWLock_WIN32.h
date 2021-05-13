/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the RWLockImpl class for WIN32.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */


#ifndef TECHNOSOFTWARE_RWLOCK_WIN32_H
#define TECHNOSOFTWARE_RWLOCK_WIN32_H

#include "Base/Base.h"
#include "Base/Exception.h"
#include "Base/UnWindows.h"

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
            void AddWriter();
            void RemoveWriter();
            DWORD TryReadLockOnce();

            HANDLE   mutex_;
            HANDLE   _readEvent;
            HANDLE   _writeEvent;
            unsigned _readers;
            unsigned _writersWaiting;
            unsigned _writers;
        };
    }
}

#endif /* TECHNOSOFTWARE_RWLOCK_WIN32_H */
