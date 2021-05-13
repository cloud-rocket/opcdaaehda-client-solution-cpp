/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Array class
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

#ifndef TECHNOSOFTWARE_ARRAY_H
#define TECHNOSOFTWARE_ARRAY_H

#include <algorithm>

#include "Base/Exception.h"
#include "Base/Bugcheck.h"

namespace Technosoftware
{
    namespace Base
    {

        template<class T, std::size_t N>
        class Array
            /// STL container like C-style array replacement class. 
            /// 
            /// This implementation is based on the idea of Nicolai Josuttis.
            /// His original implementation can be found at http://www.josuttis.com/cppcode/array.html . 
        {

        public:

            typedef T				value_type;
            typedef T*				iterator;
            typedef const T*		const_iterator;
            typedef T&				reference;
            typedef const T&		const_reference;
            typedef std::size_t		size_type;
            typedef std::ptrdiff_t  difference_type;

            iterator begin()
            {
                return elems;
            }

            const_iterator begin() const
            {
                return elems;
            }

            iterator end()
            {
                return elems + N;
            }

            const_iterator end() const
            {
                return elems + N;
            }

            typedef std::reverse_iterator<iterator>			reverse_iterator;
            typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

            reverse_iterator rbegin()
            {
                return reverse_iterator(end());
            }

            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(end());
            }

            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            }

            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }

            reference operator[](size_type i)
                /// Element access without range check. If the index is not small than the given size, the behavior is undefined.
            {
                technosoftware_assert(i < N && "out of range");
                return elems[i];
            }

            const_reference operator[](size_type i) const
                /// Element access without range check. If the index is not small than the given size, the behavior is undefined.
            {
                technosoftware_assert(i < N && "out of range");
                return elems[i];
            }

            reference at(size_type i)
                /// Element access with range check. Throws Base::InvalidArgumentException if the index is over range.
            {
                if (i >= size())
                    throw Base::InvalidArgumentException("Array::at() range check failed: index is over range");
                return elems[i];
            }

            const_reference at(size_type i) const
                /// Element access with range check. Throws Base::InvalidArgumentException if the index is over range.
            {
                if (i >= size())
                    throw Base::InvalidArgumentException("Array::at() range check failed: index is over range");
                return elems[i];
            }

            reference front()
            {
                return elems[0];
            }

            const_reference front() const
            {
                return elems[0];
            }

            reference back()
            {
                return elems[N - 1];
            }

            const_reference back() const
            {
                return elems[N - 1];
            }

            static size_type size()
            {
                return N;
            }

            static bool empty()
            {
                return false;
            }

            static size_type max_size()
            {
                return N;
            }

            enum { static_size = N };

            void swap(Array<T, N>& y) {
                std::swap_ranges(begin(), end(), y.begin());
            }

            const T* data() const
                /// Direct access to data (read-only)
            {
                return elems;
            }

            T* data()
            {
                return elems;
            }

            T* c_array() {
                /// Use array as C array (direct read/write access to data)
                return elems;
            }

            template <typename Other>
            Array<T, N>& operator= (const Array<Other, N>& rhs)
                /// Assignment with type conversion 
            {
                std::copy(rhs.begin(), rhs.end(), begin());
                return *this;
            }

            void assign(const T& value)
                /// Assign one value to all elements
            {
                std::fill_n(begin(), size(), value);
            }

        public:

            T elems[N];
            /// Fixed-size array of elements of type T, public specifier used to make this class a aggregate.

        };

        // comparisons
        template<class T, std::size_t N>
        bool operator== (const Array<T, N>& x, const Array<T, N>& y)
        {
            return std::equal(x.begin(), x.end(), y.begin());
        }

        template<class T, std::size_t N>
        bool operator< (const Array<T, N>& x, const Array<T, N>& y)
        {
            return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
        }

        template<class T, std::size_t N>
        bool operator!= (const Array<T, N>& x, const Array<T, N>& y)
        {
            return !(x == y);
        }

        template<class T, std::size_t N>
        bool operator> (const Array<T, N>& x, const Array<T, N>& y)
        {
            return y < x;
        }

        template<class T, std::size_t N>
        bool operator<= (const Array<T, N>& x, const Array<T, N>& y)
        {
            return !(y < x);
        }

        template<class T, std::size_t N>
        bool operator>= (const Array<T, N>& x, const Array<T, N>& y)
        {
            return !(x < y);
        }

        template<class T, std::size_t N>
        inline void swap(Array<T, N>& x, Array<T, N>& y)
            /// global swap()
        {
            x.swap(y);
        }
    }
}

#endif /* TECHNOSOFTWARE_ARRAY_H */

