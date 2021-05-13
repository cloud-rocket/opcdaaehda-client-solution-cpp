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

#ifndef TECHNOSOFTWARE_ATOMICCOUNTERT_H
#define TECHNOSOFTWARE_ATOMICCOUNTERT_H

#include "Base/Base.h"
#if TECHNOSOFTWARE_OS == TECHNOSOFTWARE_OS_WINDOWS_NT
#include "Base/UnWindows.h"
#elif TECHNOSOFTWARE_OS == TECHNOSOFTWARE_OS_MAC_OS_X
	#if __MAC_OS_X_VERSION_MAX_ALLOWED >= 101200 || __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000 || __TV_OS_VERSION_MAX_ALLOWED >= 100000 || __WATCH_OS_VERSION_MAX_ALLOWED >= 30000
		#ifndef TECHNOSOFTWARE_HAVE_STD_ATOMICS
			#if __cplusplus >= 201103L
				#define TECHNOSOFTWARE_HAVE_STD_ATOMICS
			#endif
		#endif
	#else
		#include <libkern/OSAtomic.h>
	#endif
#elif ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2) || __GNUC__ > 4) && (defined(__x86_64__) || defined(__i386__))
#if !defined(TECHNOSOFTWARE_HAVE_GCC_ATOMICS) && !defined(TECHNOSOFTWARE_NO_GCC_ATOMICS)
#define TECHNOSOFTWARE_HAVE_GCC_ATOMICS
#endif
#elif ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3) || __GNUC__ > 4)
#if !defined(TECHNOSOFTWARE_HAVE_GCC_ATOMICS) && !defined(TECHNOSOFTWARE_NO_GCC_ATOMICS)
#define TECHNOSOFTWARE_HAVE_GCC_ATOMICS
#endif
#endif // TECHNOSOFTWARE_OS
#ifdef POCO_HAVE_STD_ATOMICS
#include <atomic>
#endif

#include "Base/Mutex.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   AtomicCounter
         *
         * @brief   This class implements a simple counter, which provides atomic operations that are
         *          safe to use in a multithreaded environment.
         *          
         *          Typical usage of AtomicCounter is for implementing reference counting and similar
         *          things.
         *          
         *          On some platforms, the implementation of AtomicCounter is based on atomic primitives
         *          specific to the platform (such as InterlockedIncrement, etc. on Windows), and thus
         *          very efficient. On platforms that do not support atomic primitives, operations are
         *          guarded by a FastMutex.
         *          
         *          The following platforms currently have atomic primitives:
         *            - Windows
         *            - Mac OS X
         *            - GCC 4.1+ (Intel platforms only)
         *
         * @ingroup  BaseCore
         */

        class TECHNOSOFTWARE_API AtomicCounter
        {
        public:

            /**
             * @typedef int ValueType
             *
             * @brief   The underlying integer type.
             */

            typedef int ValueType; 

            /**
             * @fn  AtomicCounter::AtomicCounter();
             *
             * @brief   Creates a new AtomicCounter and initializes it to zero.
             */

            AtomicCounter();

            /**
             * @fn  explicit AtomicCounter::AtomicCounter(ValueType initialValue);
             *
             * @brief   Creates a new AtomicCounter and initializes it with the given value.
             *
             * @param   initialValue    The initial value.
             */

            explicit AtomicCounter(ValueType initialValue);

            /**
             * @fn  AtomicCounter::AtomicCounter(const AtomicCounter& counter);
             *
             * @brief   Creates the counter by copying another one.
             *
             * @param   counter The counter.
             */

            AtomicCounter(const AtomicCounter& counter);

            /**
             * @fn  AtomicCounter::~AtomicCounter();
             *
             * @brief   Destroys the AtomicCounter.
             */

            ~AtomicCounter();

            /**
             * @fn  AtomicCounter& AtomicCounter::operator= (const AtomicCounter& counter);
             *
             * @brief   Assigns the value of another AtomicCounter.
             *
             * @param   counter The counter.
             *
             * @return  A shallow copy of this object.
             */

            AtomicCounter& operator = (const AtomicCounter& counter);

            /**
             * @fn  AtomicCounter& AtomicCounter::operator= (ValueType value);
             *
             * @brief   Assigns a value to the counter.
             *
             * @param   value   The value.
             *
             * @return  A shallow copy of this object.
             */

            AtomicCounter& operator = (ValueType value);

            /**
             * @fn  operator AtomicCounter::ValueType () const;
             *
             * @brief   Returns the value of the counter.
             *
             * @return  The result of the operation.
             */

            operator ValueType () const;

            /**
             * @fn  ValueType AtomicCounter::Value() const;
             *
             * @brief   Returns the value of the counter.
             *
             * @return  A ValueType.
             */

            ValueType Value() const;

            /**
             * @fn  ValueType AtomicCounter::operator++ ();
             *
             * @brief   Increments the counter and returns the result.
             *
             * @return  The result of the operation.
             */

            ValueType operator ++ (); // prefix

            /**
             * @fn  ValueType AtomicCounter::operator++ (int);
             *
             * @brief   Increments the counter and returns the previous value.
             *
             * @param   increment  Increments.
             *
             * @return  The result of the operation.
             */

            ValueType operator ++ (int increment); // postfix

            /**
             * @fn  ValueType AtomicCounter::operator-- ();
             *
             * @brief   Decrements the counter and returns the result.
             *
             * @return  The result of the operation.
             */

            ValueType operator -- (); // prefix

            /**
             * @fn  ValueType AtomicCounter::operator-- (int);
             *
             * @brief   Decrements the counter and returns the previous value.
             *
             * @param   decrement  Decrements.
             *
             * @return  The result of the operation.
             */

            ValueType operator -- (int decrement); // postfix

            /**
             * @fn  bool AtomicCounter::operator! () const;
             *
             * @brief   Returns true if the counter is zero, false otherwise.
             *
             * @return  The logical inverse of this value.
             */

            bool operator ! () const;

        private:
#if defined(TECHNOSOFTWARE_HAVE_STD_ATOMICS)
	typedef std::atomic<int> ImplType;
#elif TECHNOSOFTWARE_OS == TECHNOSOFTWARE_OS_WINDOWS_NT
            typedef volatile LONG ImplType;
#elif TECHNOSOFTWARE_OS == TECHNOSOFTWARE_OS_MAC_OS_X
            typedef int32_t ImplType;
#elif defined(TECHNOSOFTWARE_HAVE_GCC_ATOMICS)
            typedef int ImplType;
#else // generic implementation based on FastMutex
            struct ImplType
            {
                mutable FastMutex mutex;
                volatile int      value;
            };
#endif // TECHNOSOFTWARE_OS

            ImplType counter_;
        };


        //
        // inlines
        //


#if defined(TECHNOSOFTWARE_HAVE_STD_ATOMICS)
//
// C++11 atomics
//
inline AtomicCounter::operator AtomicCounter::ValueType () const
{
	return _counter.load();
}

	
inline AtomicCounter::ValueType AtomicCounter::value() const
{
	return _counter.load();
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
{
	return ++_counter;
}

	
inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
{
	return _counter++;
}


inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
{
	return --_counter;
}

	
inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
{
	return _counter--;
}

	
inline bool AtomicCounter::operator ! () const
{
	return _counter.load() == 0;
}


#elif TECHNOSOFTWARE_OS == TECHNOSOFTWARE_OS_WINDOWS_NT
//
// Windows
//
        inline AtomicCounter::operator AtomicCounter::ValueType() const
        {
            return counter_;
        }


        inline AtomicCounter::ValueType AtomicCounter::Value() const
        {
            return counter_;
        }


        inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
        {
            return InterlockedIncrement(&counter_);
        }


        inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
        {
            ValueType result = InterlockedIncrement(&counter_);
            return --result;
        }


        inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
        {
            return InterlockedDecrement(&counter_);
        }


        inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
        {
            ValueType result = InterlockedDecrement(&counter_);
            return ++result;
        }


        inline bool AtomicCounter::operator ! () const
        {
            return counter_ == 0;
        }


#elif TECHNOSOFTWARE_OS == TECHNOSOFTWARE_OS_MAC_OS_X
//
// Mac OS X
//
        inline AtomicCounter::operator AtomicCounter::ValueType() const
        {
            return counter_;
        }


        inline AtomicCounter::ValueType AtomicCounter::Value() const
        {
            return counter_;
        }


        inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
        {
            return OSAtomicIncrement32(&counter_);
        }


        inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
        {
            ValueType result = OSAtomicIncrement32(&counter_);
            return --result;
        }


        inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
        {
            return OSAtomicDecrement32(&counter_);
        }


        inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
        {
            ValueType result = OSAtomicDecrement32(&counter_);
            return ++result;
        }


        inline bool AtomicCounter::operator ! () const
        {
            return counter_ == 0;
        }

#elif defined(TECHNOSOFTWARE_HAVE_GCC_ATOMICS)
//
// GCC 4.1+ atomic builtins.
//
        inline AtomicCounter::operator AtomicCounter::ValueType() const
        {
            return counter_;
        }


        inline AtomicCounter::ValueType AtomicCounter::Value() const
        {
            return counter_;
        }


        inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
        {
            return __sync_add_and_fetch(&counter_, 1);
        }


        inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
        {
            return __sync_fetch_and_add(&counter_, 1);
        }


        inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
        {
            return __sync_sub_and_fetch(&counter_, 1);
        }


        inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
        {
            return __sync_fetch_and_sub(&counter_, 1);
        }


        inline bool AtomicCounter::operator ! () const
        {
            return counter_ == 0;
        }


#else
//
// Generic implementation based on FastMutex
//
        inline AtomicCounter::operator AtomicCounter::ValueType() const
        {
            ValueType result;
            {
                FastMutex::ScopedLock lock(counter_.mutex);
                result = counter_.value;
            }
            return result;
        }


        inline AtomicCounter::ValueType AtomicCounter::Value() const
        {
            ValueType result;
            {
                FastMutex::ScopedLock lock(counter_.mutex);
                result = counter_.value;
            }
            return result;
        }


        inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
        {
            ValueType result;
            {
                FastMutex::ScopedLock lock(counter_.mutex);
                result = ++counter_.value;
            }
            return result;
        }


        inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
        {
            ValueType result;
            {
                FastMutex::ScopedLock lock(counter_.mutex);
                result = counter_.value++;
            }
            return result;
        }


        inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
        {
            ValueType result;
            {
                FastMutex::ScopedLock lock(counter_.mutex);
                result = --counter_.value;
            }
            return result;
        }


        inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
        {
            ValueType result;
            {
                FastMutex::ScopedLock lock(counter_.mutex);
                result = counter_.value--;
            }
            return result;
        }


        inline bool AtomicCounter::operator ! () const
        {
            bool result;
            {
                FastMutex::ScopedLock lock(counter_.mutex);
                result = counter_.value == 0;
            }
            return result;
        }


#endif // TECHNOSOFTWARE_OS

    }
}

#endif /* TECHNOSOFTWARE_ATOMICCOUNTERT_H */
