/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the AtomicCounter class.
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

#include "Base/AtomicCounter.h"

namespace Technosoftware
{
    namespace Base
    {


#if defined(TECHNOSOFTWARE_HAVE_STD_ATOMICS)
//
// C++11 atomics
//
AtomicCounter::AtomicCounter():
	counter_(0)
{
}

	
AtomicCounter::AtomicCounter(AtomicCounter::ValueType initialValue):
	counter_(initialValue)
{
}


AtomicCounter::AtomicCounter(const AtomicCounter& counter):
	counter_(counter.Value())
{
}


AtomicCounter::~AtomicCounter()
{
}


AtomicCounter& AtomicCounter::operator = (const AtomicCounter& counter)
{
	counter_.store(counter._counter.load());
	return *this;
}

	
AtomicCounter& AtomicCounter::operator = (AtomicCounter::ValueType value)
{
	counter_.store(value);
	return *this;
}


#elif TECHNOSOFTWARE_OS == TECHNOSOFTWARE_OS_WINDOWS_NT
        //
        // Windows
        //
        AtomicCounter::AtomicCounter() :
            counter_(0)
        {
        }


        AtomicCounter::AtomicCounter(AtomicCounter::ValueType initialValue) :
            counter_(initialValue)
        {
        }


        AtomicCounter::AtomicCounter(const AtomicCounter& counter) :
            counter_(counter.Value())
        {
        }


        AtomicCounter::~AtomicCounter()
        {
        }


        AtomicCounter& AtomicCounter::operator = (const AtomicCounter& counter)
        {
            InterlockedExchange(&counter_, counter.Value());
            return *this;
        }


        AtomicCounter& AtomicCounter::operator = (AtomicCounter::ValueType value)
        {
            InterlockedExchange(&counter_, value);
            return *this;
        }


#elif TECHNOSOFTWARE_OS == TECHNOSOFTWARE_OS_MAC_OS_X
        //
        // Mac OS X
        //
        AtomicCounter::AtomicCounter() :
            counter_(0)
        {
        }


        AtomicCounter::AtomicCounter(AtomicCounter::ValueType initialValue) :
            counter_(initialValue)
        {
        }


        AtomicCounter::AtomicCounter(const AtomicCounter& counter) :
            counter_(counter.Value())
        {
        }


        AtomicCounter::~AtomicCounter()
        {
        }


        AtomicCounter& AtomicCounter::operator = (const AtomicCounter& counter)
        {
            counter_ = counter.Value();
            return *this;
        }


        AtomicCounter& AtomicCounter::operator = (AtomicCounter::ValueType value)
        {
            counter_ = value;
            return *this;
        }


#elif defined(TECHNOSOFTWARE_HAVE_GCC_ATOMICS)
        //
        // GCC 4.1+ atomic builtins.
        //
        AtomicCounter::AtomicCounter() :
            counter_(0)
        {
        }


        AtomicCounter::AtomicCounter(AtomicCounter::ValueType initialValue) :
            counter_(initialValue)
        {
        }


        AtomicCounter::AtomicCounter(const AtomicCounter& counter) :
            counter_(counter.Value())
        {
        }


        AtomicCounter::~AtomicCounter()
        {
        }


        AtomicCounter& AtomicCounter::operator = (const AtomicCounter& counter)
        {
            __sync_lock_test_and_set(&counter_, counter.Value());
            return *this;
        }


        AtomicCounter& AtomicCounter::operator = (AtomicCounter::ValueType value)
        {
            __sync_lock_test_and_set(&counter_, value);
            return *this;
        }


#else
        //
        // Generic implementation based on FastMutex
        //
        AtomicCounter::AtomicCounter()
        {
            counter_.value = 0;
        }


        AtomicCounter::AtomicCounter(AtomicCounter::ValueType initialValue)
        {
            counter_.value = initialValue;
        }


        AtomicCounter::AtomicCounter(const AtomicCounter& counter)
        {
            counter_.value = counter.Value();
        }


        AtomicCounter::~AtomicCounter()
        {
        }


        AtomicCounter& AtomicCounter::operator = (const AtomicCounter& counter)
        {
            FastMutex::ScopedLock lock(counter_.mutex);
            counter_.value = counter.Value();
            return *this;
        }


        AtomicCounter& AtomicCounter::operator = (AtomicCounter::ValueType value)
        {
            FastMutex::ScopedLock lock(counter_.mutex);
            counter_.value = value;
            return *this;
        }


#endif // TECHNOSOFTWARE_OS

    }
}
