/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the SharedPtr template class.
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

#ifndef TECHNOSOFTWARE_SHAREDPTR_H
#define TECHNOSOFTWARE_SHAREDPTR_H

#include "Base/Base.h"
#include "Base/Exception.h"
#include "Base/AtomicCounter.h"
#include <algorithm>

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class    ReferenceCounter
         *
         * @brief    Simple ReferenceCounter object, does not delete itself when count reaches 0.
         *
         * @ingroup BaseCore
         */

        class ReferenceCounter
        {
        public:
            ReferenceCounter() : atomicCounter_(1)
            {
            }

            void duplicate()
            {
                ++atomicCounter_;
            }

            int release()
            {
                return --atomicCounter_;
            }

            int referenceCount() const
            {
                return atomicCounter_.Value();
            }

        private:
            AtomicCounter atomicCounter_;
        };


        /**
         * @class    ReleasePolicy
         *
         * @brief    The default release policy for SharedPtr, which simply uses the delete operator to
         *             delete an object.
         *
         * @ingroup BaseCore
         */
        template <class C>
        class ReleasePolicy
        {
        public:
            /// Delete the object.
            /// Note that pObj can be 0.
            static void release(C* pObj)
            {
                delete pObj;
            }
        };


        /**
         * @class    ReleaseArrayPolicy
         *
         * @brief    The release policy for SharedPtr holding arrays.
         *
         * @ingroup BaseCore
         */
        template <class C>
        class ReleaseArrayPolicy
        {
        public:
            static void release(C* pObj)
                /// Delete the object.
                /// Note that pObj can be 0.
            {
                delete[] pObj;
            }
        };

        /**
         * @class   SharedPtr
         *
         * @brief   SharedPtr is a "smart" pointer for classes implementing reference counting based
         *          garbage collection. SharedPtr is thus similar to AutoPtr. Unlike the AutoPtr template,
         *          which can only be used with classes that support reference counting, SharedPtr can be
         *          used with any class. For this to work, a SharedPtr manages a reference count for the
         *          object it manages.
         *          
         *          SharedPtr works in the following way: If an SharedPtr is assigned an ordinary pointer
         *          to an object (via the constructor or the assignment operator), it takes ownership of
         *          the object and the object's reference count is initialized to one. If the SharedPtr
         *          is assigned another SharedPtr, the object's reference count is incremented by one.
         *          The destructor of SharedPtr decrements the object's reference count by one and
         *          deletes the object if the reference count reaches zero. SharedPtr supports
         *          dereferencing with both the ->
         *          and the * operator. An attempt to dereference a null SharedPtr results in a
         *          NullPointerException being thrown. SharedPtr also implements all relational operators
         *          and a cast operator in case dynamic casting of the encapsulated data types is
         *          required.
         *
         * @ingroup BaseCore
         */

        template <class C, class RC = ReferenceCounter, class RP = ReleasePolicy<C> >
        class SharedPtr
        {
        public:
            SharedPtr() : counter_(new RC), ptr_(0)
            {
            }

            SharedPtr(C* ptr)
                try :
                counter_(new RC),
                ptr_(ptr)
            {
            }
            catch (...)
            {
                RP::release(ptr);
            }

            template <class Other, class OtherRP>
            SharedPtr(const SharedPtr<Other, RC, OtherRP>& ptr) : counter_(ptr.counter_), ptr_(const_cast<Other*>(ptr.Get()))
            {
                counter_->duplicate();
            }

            SharedPtr(const SharedPtr& ptr) : counter_(ptr.counter_), ptr_(ptr.ptr_)
            {
                counter_->duplicate();
            }

            ~SharedPtr()
            {
                try
                {
                    Release();
                }
                catch (...)
                {
                    technosoftware_unexpected();
                }
            }

            SharedPtr& Assign(C* ptr)
            {
                if (Get() != ptr)
                {
                    SharedPtr tmp(ptr);
                    swap(tmp);
                }
                return *this;
            }

            SharedPtr& Assign(const SharedPtr& ptr)
            {
                if (&ptr != this)
                {
                    SharedPtr tmp(ptr);
                    Swap(tmp);
                }
                return *this;
            }

            template <class Other, class OtherRP>
            SharedPtr& Assign(const SharedPtr<Other, RC, OtherRP>& ptr)
            {
                if (ptr.Get() != ptr_)
                {
                    SharedPtr tmp(ptr);
                    swap(tmp);
                }
                return *this;
            }

	void Reset()
	{
		Assign(0);
	}

	void Reset(C* ptr)
	{
		Assign(ptr);
	}

	void Reset(const SharedPtr& ptr)
	{
		Assign(ptr);
	}

	template <class Other, class OtherRP>
	void reset(const SharedPtr<Other, RC, OtherRP>& ptr)
	{
		assign<Other, OtherRP>(ptr);
	}

            SharedPtr& operator = (C* ptr)
            {
                return Assign(ptr);
            }

            SharedPtr& operator = (const SharedPtr& ptr)
            {
                return Assign(ptr);
            }

            template <class Other, class OtherRP>
            SharedPtr& operator = (const SharedPtr<Other, RC, OtherRP>& ptr)
            {
                return Assign<Other>(ptr);
            }

            void Swap(SharedPtr& ptr)
            {
                std::swap(ptr_, ptr.ptr_);
                std::swap(counter_, ptr.counter_);
            }

            /**
             * @fn  SharedPtr<Other, RC, RP> SharedPtr::cast() const
             *
             * @brief   Casts the SharedPtr via a dynamic cast to the given type. Returns an SharedPtr
             *          containing NULL if the cast fails. Example: (assume class Sub: public Super)
             *             SharedPtr&lt;Super&gt; super(new Sub());
             *             SharedPtr&lt;Sub&gt; sub = super.cast&lt;Sub&gt;();
             *             technosoftware_assert (sub.Get());
             *
             * @return  A SharedPtr&lt;Other,RC,RP&gt;
             */

            template <class Other>
            SharedPtr<Other, RC, RP> cast() const
            {
                Other* pOther = dynamic_cast<Other*>(ptr_);
                if (pOther)
                    return SharedPtr<Other, RC, RP>(counter_, pOther);
                return SharedPtr<Other, RC, RP>();
            }

            /**
             * @fn  SharedPtr<Other, RC, RP> SharedPtr::unsafeCast() const
             *
             * @brief   Casts the SharedPtr via a static cast to the given type. Example: (assume class Sub:
             *          public Super)
             *             SharedPtr&lt;Super&gt; super(new Sub());
             *             SharedPtr&lt;Sub&gt; sub = super.unsafeCast&lt;Sub&gt;();
             *             technosoftware_assert (sub.Get());
             *
             * @return  A SharedPtr&lt;Other,RC,RP&gt;
             */

            template <class Other>
            SharedPtr<Other, RC, RP> unsafeCast() const
            {
                Other* pOther = static_cast<Other*>(ptr_);
                return SharedPtr<Other, RC, RP>(counter_, pOther);
            }

            C* operator -> ()
            {
                return DeRef();
            }

            const C* operator -> () const
            {
                return DeRef();
            }

            C& operator * ()
            {
                return *DeRef();
            }

            const C& operator * () const
            {
                return *DeRef();
            }

            C* Get()
            {
                return ptr_;
            }

            const C* Get() const
            {
                return ptr_;
            }

            operator C* ()
            {
                return ptr_;
            }

            operator const C* () const
            {
                return ptr_;
            }

            bool operator ! () const
            {
                return ptr_ == 0;
            }

            bool IsNull() const
            {
                return ptr_ == 0;
            }

            bool operator == (const SharedPtr& ptr) const
            {
                return Get() == ptr.Get();
            }

            bool operator == (const C* ptr) const
            {
                return Get() == ptr;
            }

            bool operator == (C* ptr) const
            {
                return Get() == ptr;
            }

            bool operator != (const SharedPtr& ptr) const
            {
                return Get() != ptr.Get();
            }

            bool operator != (const C* ptr) const
            {
                return Get() != ptr;
            }

            bool operator != (C* ptr) const
            {
                return Get() != ptr;
            }

            bool operator < (const SharedPtr& ptr) const
            {
                return Get() < ptr.Get();
            }

            bool operator < (const C* ptr) const
            {
                return Get() < ptr;
            }

            bool operator < (C* ptr) const
            {
                return Get() < ptr;
            }

            bool operator <= (const SharedPtr& ptr) const
            {
                return Get() <= ptr.Get();
            }

            bool operator <= (const C* ptr) const
            {
                return Get() <= ptr;
            }

            bool operator <= (C* ptr) const
            {
                return Get() <= ptr;
            }

            bool operator > (const SharedPtr& ptr) const
            {
                return Get() > ptr.Get();
            }

            bool operator > (const C* ptr) const
            {
                return Get() > ptr;
            }

            bool operator > (C* ptr) const
            {
                return Get() > ptr;
            }

            bool operator >= (const SharedPtr& ptr) const
            {
                return Get() >= ptr.Get();
            }

            bool operator >= (const C* ptr) const
            {
                return Get() >= ptr;
            }

            bool operator >= (C* ptr) const
            {
                return Get() >= ptr;
            }

            int GetReferenceCount() const
            {
                return counter_->referenceCount();
            }

        private:
            C* DeRef() const
            {
                if (!ptr_)
                    throw NullPointerException();

                return ptr_;
            }

            void Release()
            {
                technosoftware_assert_dbg(counter_);
                int i = counter_->release();
                if (i == 0)
                {
                    RP::release(ptr_);
                    ptr_ = 0;

                    delete counter_;
                    counter_ = 0;
                }
            }

            SharedPtr(RC* pCounter, C* ptr) : counter_(pCounter), ptr_(ptr)
                /// for cast operation
            {
                technosoftware_assert_dbg(counter_);
                counter_->duplicate();
            }

        private:
            RC* counter_;
            C*  ptr_;

            template <class OtherC, class OtherRC, class OtherRP> friend class SharedPtr;
        };


        template <class C, class RC, class RP>
        inline void swap(SharedPtr<C, RC, RP>& p1, SharedPtr<C, RC, RP>& p2)
        {
            p1.swap(p2);
        }
    }
}

#endif /* TECHNOSOFTWARE_SHAREDPTR_H */
