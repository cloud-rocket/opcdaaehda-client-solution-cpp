/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Mutex and FastMutex classes.
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

#ifndef TECHNOSOFTWARE_MUTEX_H
#define TECHNOSOFTWARE_MUTEX_H

#include "Base/Base.h"
#include "Base/Exception.h"
#include "ScopedLock.h"

#if defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
#if defined(_WIN32_WCE)
#include "Base/Mutex_WINCE.h"
#else
#include "Base/Mutex_WIN32.h"
#endif
#elif defined(TECHNOSOFTWARE_VXWORKS)
#include "Base/Mutex_VX.h"
#else
#include "Base/Mutex_POSIX.h"
#endif

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   Mutex
         *
         * @brief   A Mutex (mutual exclusion) is a synchronization mechanism used to control access to a
         *          shared resource in a concurrent (multithreaded) scenario. Mutexes are recursive, that
         *          is, the same mutex can be locked multiple times by the same thread (but, of course,
         *          not by other threads). Using the ScopedLock class is the preferred way to
         *          automatically lock and unlock a mutex.
         *
         * @ingroup BaseThreading
         */

        class TECHNOSOFTWARE_API Mutex : private MutexImpl
        {
        public:
            typedef ScopedLock<Mutex> ScopedLock;

            /**
             * @fn  Mutex::Mutex();
             *
             * @brief   creates the Mutex.
             */

            Mutex();

            /**
             * @fn  Mutex::~Mutex();
             *
             * @brief   destroys the Mutex.
             */

            ~Mutex();

            /**
             * @fn  void Mutex::Lock();
             *
             * @brief   Locks the mutex. Blocks if the mutex is held by another thread.
             */

            void Lock();

            /**
             * @fn  void Mutex::Lock(long milliseconds);
             *
             * @brief   Locks the mutex. Blocks up to the given number of milliseconds if the mutex is held
             *          by another thread. Throws a TimeoutException if the mutex can not be locked within
             *          the given timeout.
             *          
             *          Performance Note: On most platforms (including Windows), this member function is
             *          implemented using a loop calling (the equivalent of) tryLock() and Thread::sleep().
             *          On POSIX platforms that support pthread_mutex_timedlock(), this is used.
             *
             * @param   milliseconds    The milliseconds.
             */

            void Lock(long milliseconds);

            /**
             * @fn  bool Mutex::TryLock();
             *
             * @brief   Tries to lock the mutex. Returns false immediately if the mutex is already held by
             *          another thread. Returns true if the mutex was successfully locked.
             *
             * @return  true if it succeeds, false if it fails.
             */

            bool TryLock();

            /**
             * @fn  bool Mutex::TryLock(long milliseconds);
             *
             * @brief   Locks the mutex. Blocks up to the given number of milliseconds if the mutex is held
             *          by another thread. Returns true if the mutex was successfully locked.
             *          
             *          Performance Note: On most platforms (including Windows), this member function is
             *          implemented using a loop calling (the equivalent of) tryLock() and Thread::sleep().
             *          On POSIX platforms that support pthread_mutex_timedlock(), this is used.
             *
             * @param   milliseconds    The milliseconds.
             *
             * @return  true if it succeeds, false if it fails.
             */

            bool TryLock(long milliseconds);

            /**
             * @fn  void Mutex::Unlock();
             *
             * @brief   Unlocks the mutex so that it can be acquired by other threads.
             */

            void Unlock();

        private:
            Mutex(const Mutex&);
            Mutex& operator = (const Mutex&);
        };

        /**
         * @class   FastMutex
         *
         * @brief   A FastMutex (mutual exclusion) is similar to a Mutex. Unlike a Mutex, however, a
         *          FastMutex is not recursive, which means that a deadlock will occur if the same thread
         *          tries to lock a mutex it has already locked again. Locking a FastMutex is faster than
         *          locking a recursive Mutex. Using the ScopedLock class is the preferred way to
         *          automatically lock and unlock a mutex.
         *
         * @ingroup BaseThreading
         */

        class TECHNOSOFTWARE_API FastMutex : private FastMutexImpl
        {
        public:
            typedef Base::ScopedLock<FastMutex> ScopedLock;

            /**
             * @fn  FastMutex::FastMutex();
             *
             * @brief   creates the Mutex.
             */

            FastMutex();

            /**
             * @fn  FastMutex::~FastMutex();
             *
             * @brief   destroys the Mutex.
             */

            ~FastMutex();

            /**
             * @fn  void FastMutex::Lock();
             *
             * @brief   Locks the mutex. Blocks if the mutex is held by another thread.
             */

            void Lock();

            /**
             * @fn  void FastMutex::Lock(long milliseconds);
             *
             * @brief   Locks the mutex. Blocks up to the given number of milliseconds if the mutex is held
             *          by another thread. Throws a TimeoutException if the mutex can not be locked within
             *          the given timeout.
             *          
             *          Performance Note: On most platforms (including Windows), this member function is
             *          implemented using a loop calling (the equivalent of) tryLock() and Thread::sleep().
             *          On POSIX platforms that support pthread_mutex_timedlock(), this is used.
             *
             * @param   milliseconds    The milliseconds.
             */

            void Lock(long milliseconds);

            /**
             * @fn  bool FastMutex::TryLock();
             *
             * @brief   Tries to lock the mutex. Returns false immediately if the mutex is already held by
             *          another thread. Returns true if the mutex was successfully locked.
             *
             * @return  true if it succeeds, false if it fails.
             */

            bool TryLock();

            /**
             * @fn  bool FastMutex::TryLock(long milliseconds);
             *
             * @brief   Locks the mutex. Blocks up to the given number of milliseconds if the mutex is held
             *          by another thread. Returns true if the mutex was successfully locked.
             *          
             *          Performance Note: On most platforms (including Windows), this member function is
             *          implemented using a loop calling (the equivalent of) tryLock() and Thread::sleep().
             *          On POSIX platforms that support pthread_mutex_timedlock(), this is used.
             *
             * @param   milliseconds    The milliseconds.
             *
             * @return  true if it succeeds, false if it fails.
             */

            bool TryLock(long milliseconds);

            /**
             * @fn  void FastMutex::Unlock();
             *
             * @brief   Unlocks the mutex so that it can be acquired by other threads.
             */

            void Unlock();

        private:
            FastMutex(const FastMutex&);
            FastMutex& operator = (const FastMutex&);
        };

        /**
         * @class   NullMutex
         *
         * @brief   A NullMutex is an empty mutex implementation which performs no locking at all. Useful
         *          in policy driven design where the type of mutex used can be now a template parameter
         *          allowing the user to switch between thread-safe and not thread-safe depending on his
         *          need Works with the ScopedLock class.
         *
         * @ingroup BaseThreading
         */

        class TECHNOSOFTWARE_API NullMutex
        {
        public:
            typedef Base::ScopedLock<NullMutex> ScopedLock;

            /**
             * @fn  NullMutex::NullMutex()
             *
             * @brief   Creates the NullMutex.
             */

            NullMutex()
            {
            }

            /**
             * @fn  NullMutex::~NullMutex()
             *
             * @brief   Destroys the NullMutex.
             */

            ~NullMutex()
            {
            }

            /**
             * @fn  void NullMutex::Lock()
             *
             * @brief   Does nothing.
             */

            void Lock()
            {
            }

            /**
             * @fn  void NullMutex::Lock(long)
             *
             * @brief   Does nothing.
             *
             * @param   milliseconds    The milliseconds.
             */

            void Lock(long milliseconds)
            {
            }

            /**
             * @fn  bool NullMutex::TryLock()
             *
             * @brief   Does nothing and always returns true.
             *
             * @return  true if it succeeds, false if it fails.
             */

            bool TryLock()
            {
                return true;
            }

            /**
             * @fn  bool NullMutex::TryLock(long milliseconds)
             *
             * @brief   Does nothing and always returns true.
             *
             * @param   milliseconds    The milliseconds.
             *
             * @return  true if it succeeds, false if it fails.
             */

            bool TryLock(long milliseconds)
            {
                return true;
            }

            /**
             * @fn  void NullMutex::Unlock()
             *
             * @brief   Does nothing.
             */

            void Unlock()
            {
            }
        };


        //
        // inlines
        //
        inline void Mutex::Lock()
        {
            LockImpl();
        }


        inline void Mutex::Lock(long milliseconds)
        {
            if (!TryLockImpl(milliseconds))
                throw TimeoutException();
        }


        inline bool Mutex::TryLock()
        {
            return TryLockImpl();
        }


        inline bool Mutex::TryLock(long milliseconds)
        {
            return TryLockImpl(milliseconds);
        }


        inline void Mutex::Unlock()
        {
            UnlockImpl();
        }


        inline void FastMutex::Lock()
        {
            LockImpl();
        }


        inline void FastMutex::Lock(long milliseconds)
        {
            if (!TryLockImpl(milliseconds))
                throw TimeoutException();
        }


        inline bool FastMutex::TryLock()
        {
            return TryLockImpl();
        }


        inline bool FastMutex::TryLock(long milliseconds)
        {
            return TryLockImpl(milliseconds);
        }


        inline void FastMutex::Unlock()
        {
            UnlockImpl();
        }
    }
}

#endif /* TECHNOSOFTWARE_MUTEX_H */
