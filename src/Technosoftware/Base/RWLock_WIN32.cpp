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

#include "Base/RWLock_WIN32.h"

namespace Technosoftware
{
    namespace Base
    {
        RWLockImpl::RWLockImpl() : _readers(0), _writersWaiting(0), _writers(0)
        {
            mutex_ = CreateMutexW(NULL, FALSE, NULL);
            if (mutex_ == NULL)
                throw SystemException("cannot create reader/writer lock");

            _readEvent = CreateEventW(NULL, TRUE, TRUE, NULL);
            if (_readEvent == NULL)
                throw SystemException("cannot create reader/writer lock");

            _writeEvent = CreateEventW(NULL, TRUE, TRUE, NULL);
            if (_writeEvent == NULL)
                throw SystemException("cannot create reader/writer lock");
        }


        RWLockImpl::~RWLockImpl()
        {
            CloseHandle(mutex_);
            CloseHandle(_readEvent);
            CloseHandle(_writeEvent);
        }


        inline void RWLockImpl::AddWriter()
        {
            switch (WaitForSingleObject(mutex_, INFINITE))
            {
            case WAIT_OBJECT_0:
                if (++_writersWaiting == 1) ResetEvent(_readEvent);
                ReleaseMutex(mutex_);
                break;
            default:
                throw SystemException("cannot lock reader/writer lock");
            }
        }


        inline void RWLockImpl::RemoveWriter()
        {
            switch (WaitForSingleObject(mutex_, INFINITE))
            {
            case WAIT_OBJECT_0:
                if (--_writersWaiting == 0 && _writers == 0) SetEvent(_readEvent);
                ReleaseMutex(mutex_);
                break;
            default:
                throw SystemException("cannot lock reader/writer lock");
            }
        }


        void RWLockImpl::ReadLockImpl()
        {
            HANDLE h[2];
            h[0] = mutex_;
            h[1] = _readEvent;
            switch (WaitForMultipleObjects(2, h, TRUE, INFINITE))
            {
            case WAIT_OBJECT_0:
            case WAIT_OBJECT_0 + 1:
                ++_readers;
                ResetEvent(_writeEvent);
                ReleaseMutex(mutex_);
                technosoftware_assert_dbg(_writers == 0);
                break;
            default:
                throw SystemException("cannot lock reader/writer lock");
            }
        }


        bool RWLockImpl::TryReadLockImpl()
        {
            for (;;)
            {
                if (_writers != 0 || _writersWaiting != 0)
                    return false;

                DWORD result = TryReadLockOnce();
                switch (result)
                {
                case WAIT_OBJECT_0:
                case WAIT_OBJECT_0 + 1:
                    return true;
                case WAIT_TIMEOUT:
                    continue; // try again
                default:
                    throw SystemException("cannot lock reader/writer lock");
                }
            }
        }


        void RWLockImpl::WriteLockImpl()
        {
            AddWriter();
            HANDLE h[2];
            h[0] = mutex_;
            h[1] = _writeEvent;
            switch (WaitForMultipleObjects(2, h, TRUE, INFINITE))
            {
            case WAIT_OBJECT_0:
            case WAIT_OBJECT_0 + 1:
                --_writersWaiting;
                ++_readers;
                ++_writers;
                ResetEvent(_readEvent);
                ResetEvent(_writeEvent);
                ReleaseMutex(mutex_);
                technosoftware_assert_dbg(_writers == 1);
                break;
            default:
                RemoveWriter();
                throw SystemException("cannot lock reader/writer lock");
            }
        }


        bool RWLockImpl::TryWriteLockImpl()
        {
            AddWriter();
            HANDLE h[2];
            h[0] = mutex_;
            h[1] = _writeEvent;
            switch (WaitForMultipleObjects(2, h, TRUE, 1))
            {
            case WAIT_OBJECT_0:
            case WAIT_OBJECT_0 + 1:
                --_writersWaiting;
                ++_readers;
                ++_writers;
                ResetEvent(_readEvent);
                ResetEvent(_writeEvent);
                ReleaseMutex(mutex_);
                technosoftware_assert_dbg(_writers == 1);
                return true;
            case WAIT_TIMEOUT:
                RemoveWriter();
                return false;
            default:
                RemoveWriter();
                throw SystemException("cannot lock reader/writer lock");
            }
        }


        void RWLockImpl::UnlockImpl()
        {
            switch (WaitForSingleObject(mutex_, INFINITE))
            {
            case WAIT_OBJECT_0:
                _writers = 0;
                if (_writersWaiting == 0) SetEvent(_readEvent);
                if (--_readers == 0) SetEvent(_writeEvent);
                ReleaseMutex(mutex_);
                break;
            default:
                throw SystemException("cannot unlock reader/writer lock");
            }
        }


        DWORD RWLockImpl::TryReadLockOnce()
        {
            HANDLE h[2];
            h[0] = mutex_;
            h[1] = _readEvent;
            DWORD result = WaitForMultipleObjects(2, h, TRUE, 1);
            switch (result)
            {
            case WAIT_OBJECT_0:
            case WAIT_OBJECT_0 + 1:
                ++_readers;
                ResetEvent(_writeEvent);
                ReleaseMutex(mutex_);
                technosoftware_assert_dbg(_writers == 0);
                return result;
            case WAIT_TIMEOUT:
                return result;
            default:
                throw SystemException("cannot lock reader/writer lock");
            }
        }

    }
}
