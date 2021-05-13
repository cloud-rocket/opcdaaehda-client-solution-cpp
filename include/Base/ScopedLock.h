/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the ScopedLock template class.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The source code in this file is covered under a dual-license scenario:
 *   - Owner of a purchased license: SCLA 1.0
 *   - GPL V3: everybody else
 *
 * SCLA license terms accompanied with this source code.
 * See SCLA 1.0: https://technosoftware.com/license/Source_Code_License_Agreement.pdf
 *
 * GNU General Public License as published by the Free Software Foundation;
 * version 3 of the License are accompanied with this source code.
 * See https://technosoftware.com/license/GPLv3License.txt
 *
 * This source code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef TECHNOSOFTWARE_SCOPEDLOCK_H
#define TECHNOSOFTWARE_SCOPEDLOCK_H

#include "Base/Base.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   ScopedLock
         *
         * @brief   A class that simplifies thread synchronization with a mutex. The constructor accepts
         *          a Mutex (and optionally a timeout value in milliseconds) and locks it. The destructor
         *          unlocks the mutex.
         *
         * @ingroup BaseThreading
         */

        template <class M>
        class ScopedLock
        {
        public:
            explicit ScopedLock(M& mutex) : mutex_(mutex)
            {
                mutex_.Lock();
            }

            ScopedLock(M& mutex, long milliseconds) : mutex_(mutex)
            {
                mutex_.Lock(milliseconds);
            }

            ~ScopedLock()
            {
                try
                {
                    mutex_.Unlock();
                }
                catch (...)
                {
                    technosoftware_unexpected();
                }
            }

        private:
            M& mutex_;

            ScopedLock();
            ScopedLock(const ScopedLock&);
            ScopedLock& operator = (const ScopedLock&);
        };


        template <class M>

        /**
         * @class   ScopedLockWithUnlock
         *
         * @brief   A class that simplifies thread synchronization with a mutex. The constructor accepts
         *          a Mutex (and optionally a timeout value in milliseconds) and locks it. The destructor
         *          unlocks the mutex. The unlock() member function allows for manual unlocking of the
         *          mutex.
         *
         * @ingroup BaseThreading
         */

        class ScopedLockWithUnlock
        {
        public:
            explicit ScopedLockWithUnlock(M& mutex) : _pMutex(&mutex)
            {
                _pMutex->lock();
            }

            ScopedLockWithUnlock(M& mutex, long milliseconds) : _pMutex(&mutex)
            {
                _pMutex->lock(milliseconds);
            }

            ~ScopedLockWithUnlock()
            {
                try
                {
                    unlock();
                }
                catch (...)
                {
                    technosoftware_unexpected();
                }
            }

            void unlock()
            {
                if (_pMutex)
                {
                    _pMutex->unlock();
                    _pMutex = 0;
                }
            }

        private:
            M* _pMutex;

            ScopedLockWithUnlock();
            ScopedLockWithUnlock(const ScopedLockWithUnlock&);
            ScopedLockWithUnlock& operator = (const ScopedLockWithUnlock&);
        };
    }
}

#endif /* TECHNOSOFTWARE_SCOPEDLOCK_H */
