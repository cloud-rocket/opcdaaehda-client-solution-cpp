/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the RWLockImpl class for WINCE.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#ifndef TECHNOSOFTWARE_RWLOCK_WINCE_H
#define TECHNOSOFTWARE_RWLOCK_WINCE_H

#include "Base/Base.h"
#include "Base/Exception.h"
#include "Base/UnWindows.h"

namespace Technosoftware
{
    namespace Base
    {
        class TECHNOSOFTWARE_API RWLockImpl
            /// This implementation is based on the one from Stone Steps Inc,
            /// licensed under the BSD license.
            /// http://forums.stonesteps.ca/thread.asp?t=105
            ///
            /// Note that with this implementation, writers always take
            /// precedence over readers.
        {
        protected:
            RWLockImpl();
            ~RWLockImpl();
            void ReadLockImpl();
            bool TryReadLockImpl(DWORD timeout = 1);
            void WriteLockImpl();
            bool TryWriteLockImpl(DWORD timeout = 1);
            void UnlockImpl();

        private:
            DWORD _readerCount;
            DWORD _readerWaiting;
            DWORD _writerCount;
            DWORD _writerWaiting;
            HANDLE _readerGreen;
            HANDLE _writerGreen;
            CRITICAL_SECTION _cs;
            bool _writeLock;
        };
    }
}

#endif /* TECHNOSOFTWARE_RWLOCK_WINCE_H */
