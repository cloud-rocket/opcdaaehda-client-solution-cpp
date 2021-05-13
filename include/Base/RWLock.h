/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the RWLock class.
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

#ifndef TECHNOSOFTWARE_RWLOCK_H
#define TECHNOSOFTWARE_RWLOCK_H

#include "Base/Base.h"
#include "Base/Exception.h"

#if defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
#if defined(_WIN32_WCE)
#include "Base/RWLock_WINCE.h"
#else
#include "Base/RWLock_WIN32.h"
#endif
#elif TECHNOSOFTWARE_OS == TECHNOSOFTWARE_OS_ANDROID
#include "Base/RWLock_Android.h"
#elif defined(TECHNOSOFTWARE_VXWORKS)
#include "Base/RWLock_VX.h"
#else
#include "Base/RWLock_POSIX.h"
#endif


namespace Technosoftware
{
    namespace Base
    {
        class ScopedRWLock;
        class ScopedReadRWLock;
        class ScopedWriteRWLock;

        /**
         * @class    RWLock
         *
         * @brief    A reader writer lock allows multiple concurrent readers or one exclusive writer.
         *
         * @ingroup BaseThreading
         */

        class TECHNOSOFTWARE_API RWLock : private RWLockImpl
        {
        public:
            typedef ScopedRWLock ScopedLock;
            typedef ScopedReadRWLock ScopedReadLock;
            typedef ScopedWriteRWLock ScopedWriteLock;

            /**
             * @fn    RWLock::RWLock();
             *
             * @brief    Creates the Reader/Writer lock.
             */

            RWLock();

            /**
             * @fn    RWLock::~RWLock();
             *
             * @brief    Destroys the Reader/Writer lock.
             */

            ~RWLock();

            /**
             * @fn    void RWLock::ReadLock();
             *
             * @brief    Acquires a read lock. If another thread currently holds a write lock, waits until the
             *             write lock is released.
             */

            void ReadLock();

            /**
             * @fn    bool RWLock::TryReadLock();
             *
             * @brief    Tries to acquire a read lock. Immediately returns true if successful, or false if
             *             another thread currently holds a write lock.
             *
             * @return    true if it succeeds, false if it fails.
             */

            bool TryReadLock();

            /**
             * @fn    void RWLock::WriteLock();
             *
             * @brief    Acquires a write lock. If one or more other threads currently hold locks, waits until
             *             all locks are released. The results are undefined if the same thread already holds a
             *             read or write lock.
             */

            void WriteLock();

            /**
             * @fn    bool RWLock::TryWriteLock();
             *
             * @brief    Tries to acquire a write lock. Immediately returns true if successful, or false if
             *             one or more other threads currently hold locks. The result is undefined if the same
             *             thread already holds a read or write lock.
             *
             * @return    true if it succeeds, false if it fails.
             */

            bool TryWriteLock();

            /**
             * @fn    void RWLock::Unlock();
             *
             * @brief    Releases the read or write lock.
             */

            void Unlock();

        private:
            RWLock(const RWLock&);
            RWLock& operator = (const RWLock&);
        };


        class TECHNOSOFTWARE_API ScopedRWLock
            /// A variant of ScopedLock for reader/writer locks.
        {
        public:
            ScopedRWLock(RWLock& rwl, bool write = false);
            ~ScopedRWLock();

        private:
            RWLock& _rwl;

            ScopedRWLock();
            ScopedRWLock(const ScopedRWLock&);
            ScopedRWLock& operator = (const ScopedRWLock&);
        };


        class TECHNOSOFTWARE_API ScopedReadRWLock : public ScopedRWLock
            /// A variant of ScopedLock for reader locks.
        {
        public:
            ScopedReadRWLock(RWLock& rwl);
            ~ScopedReadRWLock();
        };


        class TECHNOSOFTWARE_API ScopedWriteRWLock : public ScopedRWLock
            /// A variant of ScopedLock for writer locks.
        {
        public:
            ScopedWriteRWLock(RWLock& rwl);
            ~ScopedWriteRWLock();
        };


        //
        // inlines
        //
        inline void RWLock::ReadLock()
        {
            ReadLockImpl();
        }


        inline bool RWLock::TryReadLock()
        {
            return TryReadLockImpl();
        }


        inline void RWLock::WriteLock()
        {
            WriteLockImpl();
        }


        inline bool RWLock::TryWriteLock()
        {
            return TryWriteLockImpl();
        }


        inline void RWLock::Unlock()
        {
            UnlockImpl();
        }


        inline ScopedRWLock::ScopedRWLock(RWLock& rwl, bool write) : _rwl(rwl)
        {
            if (write)
                _rwl.WriteLock();
            else
                _rwl.ReadLock();
        }


        inline ScopedRWLock::~ScopedRWLock()
        {
            try
            {
                _rwl.Unlock();
            }
            catch (...)
            {
                technosoftware_unexpected();
            }
        }


        inline ScopedReadRWLock::ScopedReadRWLock(RWLock& rwl) : ScopedRWLock(rwl, false)
        {
        }


        inline ScopedReadRWLock::~ScopedReadRWLock()
        {
        }


        inline ScopedWriteRWLock::ScopedWriteRWLock(RWLock& rwl) : ScopedRWLock(rwl, true)
        {
        }


        inline ScopedWriteRWLock::~ScopedWriteRWLock()
        {
        }
    }
}

#endif /* TECHNOSOFTWARE_RWLOCK_H */
