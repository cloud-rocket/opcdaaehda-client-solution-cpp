/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the AutoPtr template class.
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

#ifndef TECHNOSOFTWARE_AUTOPTR_H
#define TECHNOSOFTWARE_AUTOPTR_H

#include "Base/Base.h"
#include "Base/Exception.h"
#include <algorithm>

namespace Technosoftware
{
    namespace Base
    {

        /**
         * @class   AutoPtr
         *
         * @brief   AutoPtr is a "smart" pointer for classes implementing reference counting based
         *          garbage collection. To be usable with the AutoPtr template, a class must implement
         *          the following behaviour: A class must maintain a reference count. The constructors of
         *          the object initialize the reference count to one. The class must implement a public
         *          Duplicate() method:
         *              void Duplicate();
         *          that increments the reference count by one. The class must implement a public
         *          Release() method:
         *              void Release()
         *          that decrements the reference count by one, and, if the reference count reaches zero,
         *          deletes the object.
         *          
         *          AutoPtr works in the following way: If an AutoPtr is assigned an ordinary pointer to
         *          an object (via the constructor or the assignment operator), it takes ownership of the
         *          object and the object's reference count remains unchanged. If the AutoPtr is assigned
         *          another AutoPtr, the object's reference count is incremented by one by calling
         *          Duplicate() on its object. The destructor of AutoPtr calls Release() on its object.
         *          AutoPtr supports dereferencing with both the ->
         *          and the * operator. An attempt to dereference a null AutoPtr results in a
         *          NullPointerException being thrown. AutoPtr also implements all relational operators.
         *          Note that AutoPtr allows casting of its encapsulated data types.
         *
         * @ingroup BaseCore
         */

        template <class C>
        class AutoPtr
        {
        public:
            AutoPtr() : _ptr(0)
            {
            }

            AutoPtr(C* ptr) : _ptr(ptr)
            {
            }

            AutoPtr(C* ptr, bool shared) : _ptr(ptr)
            {
                if (shared && _ptr) _ptr->Duplicate();
            }

            AutoPtr(const AutoPtr& ptr) : _ptr(ptr._ptr)
            {
                if (_ptr) _ptr->Duplicate();
            }

            template <class Other>
            AutoPtr(const AutoPtr<Other>& ptr) : _ptr(const_cast<Other*>(ptr.get()))
            {
                if (_ptr) _ptr->Duplicate();
            }

            ~AutoPtr()
            {
                if (_ptr) _ptr->Release();
            }

            AutoPtr& Assign(C* ptr)
            {
                if (_ptr != ptr)
                {
                    if (_ptr) _ptr->Release();
                    _ptr = ptr;
                }
                return *this;
            }

            AutoPtr& Assign(C* ptr, bool shared)
            {
                if (_ptr != ptr)
                {
                    if (_ptr) _ptr->Release();
                    _ptr = ptr;
                    if (shared && _ptr) _ptr->Duplicate();
                }
                return *this;
            }

            AutoPtr& Assign(const AutoPtr& ptr)
            {
                if (&ptr != this)
                {
                    if (_ptr) _ptr->Release();
                    _ptr = ptr._ptr;
                    if (_ptr) _ptr->Duplicate();
                }
                return *this;
            }

            template <class Other>
            AutoPtr& Assign(const AutoPtr<Other>& ptr)
            {
                if (ptr.get() != _ptr)
                {
                    if (_ptr) _ptr->Release();
                    _ptr = const_cast<Other*>(ptr.get());
                    if (_ptr) _ptr->Duplicate();
                }
                return *this;
            }

	void Reset()
	{
		if (_ptr)
		{
			_ptr->Release();
			_ptr = 0;
		}
	}

	void Reset(C* ptr)
	{
		Assign(ptr);
	}

	void Reset(C* ptr, bool shared)
	{
		Assign(ptr, shared);
	}

	void Reset(const AutoPtr& ptr)
	{
		Assign(ptr);
	}

	template <class Other>
	void reset(const AutoPtr<Other>& ptr)
	{
		assign<Other>(ptr);
	}

            AutoPtr& operator = (C* ptr)
            {
                return Assign(ptr);
            }

            AutoPtr& operator = (const AutoPtr& ptr)
            {
                return Assign(ptr);
            }

            template <class Other>
            AutoPtr& operator = (const AutoPtr<Other>& ptr)
            {
                return Assign<Other>(ptr);
            }

            void Swap(AutoPtr& ptr)
            {
                std::swap(_ptr, ptr._ptr);
            }

            template <class Other>

            /**
             * @fn  AutoPtr<Other> AutoPtr::Cast() const
             *
             * @brief   Casts the AutoPtr via a dynamic cast to the given type. Returns an AutoPtr containing
             *          NULL if the cast fails.
             *
             * @return  An AutoPtr of the given type
             */

            AutoPtr<Other> Cast() const
            {
                Other* pOther = dynamic_cast<Other*>(_ptr);
                return AutoPtr<Other>(pOther, true);
            }

            /**
             * @fn  AutoPtr<Other> AutoPtr::UnsafeCast() const
             *
             * @brief   Casts the AutoPtr via a static cast to the given type. 
             *
             * @return  An AutoPtr of the given type
             */

            template <class Other>
            AutoPtr<Other> UnsafeCast() const
            {
                Other* pOther = static_cast<Other*>(_ptr);
                return AutoPtr<Other>(pOther, true);
            }

            C* operator -> ()
            {
                if (_ptr)
                    return _ptr;
                else
                    throw NullPointerException();
            }

            const C* operator -> () const
            {
                if (_ptr)
                    return _ptr;
                else
                    throw NullPointerException();
            }

            C& operator * ()
            {
                if (_ptr)
                    return *_ptr;
                else
                    throw NullPointerException();
            }

            const C& operator * () const
            {
                if (_ptr)
                    return *_ptr;
                else
                    throw NullPointerException();
            }

            C* get()
            {
                return _ptr;
            }

            const C* get() const
            {
                return _ptr;
            }

            operator C* ()
            {
                return _ptr;
            }

            operator const C* () const
            {
                return _ptr;
            }

            bool operator ! () const
            {
                return _ptr == 0;
            }

            bool isNull() const
            {
                return _ptr == 0;
            }

            C* Duplicate()
            {
                if (_ptr) _ptr->Duplicate();
                return _ptr;
            }

            bool operator == (const AutoPtr& ptr) const
            {
                return _ptr == ptr._ptr;
            }

            bool operator == (const C* ptr) const
            {
                return _ptr == ptr;
            }

            bool operator == (C* ptr) const
            {
                return _ptr == ptr;
            }

            bool operator != (const AutoPtr& ptr) const
            {
                return _ptr != ptr._ptr;
            }

            bool operator != (const C* ptr) const
            {
                return _ptr != ptr;
            }

            bool operator != (C* ptr) const
            {
                return _ptr != ptr;
            }

            bool operator < (const AutoPtr& ptr) const
            {
                return _ptr < ptr._ptr;
            }

            bool operator < (const C* ptr) const
            {
                return _ptr < ptr;
            }

            bool operator < (C* ptr) const
            {
                return _ptr < ptr;
            }

            bool operator <= (const AutoPtr& ptr) const
            {
                return _ptr <= ptr._ptr;
            }

            bool operator <= (const C* ptr) const
            {
                return _ptr <= ptr;
            }

            bool operator <= (C* ptr) const
            {
                return _ptr <= ptr;
            }

            bool operator > (const AutoPtr& ptr) const
            {
                return _ptr > ptr._ptr;
            }

            bool operator > (const C* ptr) const
            {
                return _ptr > ptr;
            }

            bool operator > (C* ptr) const
            {
                return _ptr > ptr;
            }

            bool operator >= (const AutoPtr& ptr) const
            {
                return _ptr >= ptr._ptr;
            }

            bool operator >= (const C* ptr) const
            {
                return _ptr >= ptr;
            }

            bool operator >= (C* ptr) const
            {
                return _ptr >= ptr;
            }

        private:
            C* _ptr;
        };


        template <class C>
        inline void Swap(AutoPtr<C>& p1, AutoPtr<C>& p2)
        {
            p1.Swap(p2);
        }
    }

}

#endif /* TECHNOSOFTWARE_AUTOPTR_H */
