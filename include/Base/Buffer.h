/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Buffer class.
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

#ifndef TECHNOSOFTWARE_BUFFER_H
#define TECHNOSOFTWARE_BUFFER_H

#include "Base/Base.h"
#include "Base/Exception.h"
#include <cstring>
#include <cstddef>

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   Buffer
         *
         * @brief   A buffer class that allocates a buffer of a given type and size in the constructor
         *          and deallocates the buffer in the destructor.
         *          
         *          This class is useful everywhere where a temporary buffer is needed.
         *
         * @ingroup BaseCore
         */

        template <class T>
        class Buffer
        {
        public:
            Buffer(std::size_t capacity) :
                capacity_(capacity),
                used_(capacity),
                ptr_(0),
                ownMem_(true)
                /// Creates and allocates the Buffer.
            {
                if (capacity > 0)
                {
                    ptr_ = new T[capacity];
                }
            }

            /**
             * @fn  Buffer::Buffer(T* pMem, std::size_t length)
             *
             * @brief   Creates the Buffer. Length argument specifies the length of the supplied memory
             *          pointed to by pMem in the number of elements of type T. Supplied pointer is
             *          considered blank and not owned by Buffer, so in this case Buffer only acts as a
             *          wrapper around externally supplied (and lifetime-managed) memory.
             *
             * @param [in,out]  pMem    If non-null, the memory.
             * @param   length          The length.
             */

            Buffer(T* pMem, std::size_t length) :
                capacity_(length),
                used_(length),
                ptr_(pMem),
                ownMem_(false)
            {
            }

            /**
             * @fn  Buffer::Buffer(const T* pMem, std::size_t length)
             *
             * @brief   Creates and allocates the Buffer; copies the contents of the supplied memory into the
             *          buffer. Length argument specifies the length of the supplied memory pointed to by
             *          pMem in the number of elements of type T.
             *
             * @param   pMem    The memory.
             * @param   length  The length.
             */

            Buffer(const T* pMem, std::size_t length) :
                capacity_(length),
                used_(length),
                ptr_(0),
                ownMem_(true)
            {
                if (capacity_ > 0)
                {
                    ptr_ = new T[capacity_];
                    std::memcpy(ptr_, pMem, used_ * sizeof(T));
                }
            }

            /**
             * @fn  Buffer::Buffer(const Buffer& other)
             *
             * @brief   Copy constructor.
             *
             * @param   other   The other.
             */

            Buffer(const Buffer& other) :
                capacity_(other.used_),
                used_(other.used_),
                ptr_(0),
                ownMem_(true)
            {
                if (used_)
                {
                    ptr_ = new T[used_];
                    std::memcpy(ptr_, other.ptr_, used_ * sizeof(T));
                }
            }

            /**
             * @fn  Buffer& Buffer::operator= (const Buffer& other)
             *
             * @brief   Assignment operator.
             *
             * @param   other   The other.
             *
             * @return  A shallow copy of this object.
             */

            Buffer& operator = (const Buffer& other)
            {
                if (this != &other)
                {
                    Buffer tmp(other);
                    swap(tmp);
                }

                return *this;
            }

            /**
             * @fn  Buffer::~Buffer()
             *
             * @brief   Destroys the Buffer.
             */

            ~Buffer()
            {
                if (ownMem_) delete[] ptr_;
            }

            /**
             * @fn  void Buffer::Resize(std::size_t newCapacity, bool preserveContent = true)
             *
             * @brief   Resizes the buffer capacity and size. If preserveContent is true, the content of the
             *          old buffer is copied over to the new buffer. The new capacity can be larger or
             *          smaller than the current one; if it is smaller, capacity will remain intact. Size
             *          will always be set to the new capacity.
             *          
             *          Buffers only wrapping externally owned storage can not be resized. If resize is
             *          attempted on those, IllegalAccessException is thrown.
             *
             * @exception   Base::InvalidAccessException    Thrown when an Invalid Access error condition
             *                                              occurs.
             *
             * @param   newCapacity     The new capacity.
             * @param   preserveContent (Optional) true to preserve content.
             */

            void Resize(std::size_t newCapacity, bool preserveContent = true)
            {
                if (!ownMem_) throw Base::InvalidAccessException("Cannot resize buffer which does not own its storage.");

                if (newCapacity > capacity_)
                {
                    T* ptr = new T[newCapacity];
                    if (preserveContent)
                    {
                        std::memcpy(ptr, ptr_, used_ * sizeof(T));
                    }
                    delete[] ptr_;
                    ptr_ = ptr;
                    capacity_ = newCapacity;
                }

                used_ = newCapacity;
            }

            /**
             * @fn  void Buffer::SetCapacity(std::size_t newCapacity, bool preserveContent = true)
             *
             * @brief   Sets the buffer capacity. If preserveContent is true, the content of the old buffer
             *          is copied over to the new buffer. The new capacity can be larger or smaller than the
             *          current one; size will be set to the new capacity only if new capacity is smaller
             *          than the current size, otherwise it will remain intact.
             *          
             *          Buffers only wrapping externally owned storage can not be resized. If resize is
             *          attempted on those, IllegalAccessException is thrown.
             *
             * @exception   Base::InvalidAccessException    Thrown when an Invalid Access error condition
             *                                              occurs.
             *
             * @param   newCapacity     The new capacity.
             * @param   preserveContent (Optional) true to preserve content.
             */

            void SetCapacity(std::size_t newCapacity, bool preserveContent = true)
            {
                if (!ownMem_) throw Base::InvalidAccessException("Cannot resize buffer which does not own its storage.");

                if (newCapacity != capacity_)
                {
                    T* ptr = 0;
                    if (newCapacity > 0)
                    {
                        ptr = new T[newCapacity];
                        if (preserveContent)
                        {
                            std::size_t newSz = used_ < newCapacity ? used_ : newCapacity;
                            std::memcpy(ptr, ptr_, newSz * sizeof(T));
                        }
                    }
                    delete[] ptr_;
                    ptr_ = ptr;
                    capacity_ = newCapacity;

                    if (newCapacity < used_) used_ = newCapacity;
                }
            }

            /**
             * @fn  void Buffer::Assign(const T* buf, std::size_t sz)
             *
             * @brief   Assigns the argument buffer to this buffer. If necessary, resizes the buffer.
             *
             * @param   buf The buffer.
             * @param   sz  The size.
             */

            void Assign(const T* buf, std::size_t sz)
            {
                if (0 == sz) return;
                if (sz > capacity_) resize(sz, false);
                std::memcpy(ptr_, buf, sz * sizeof(T));
                used_ = sz;
            }

            /**
             * @fn  void Buffer::Append(const T* buf, std::size_t sz)
             *
             * @brief   Resizes this buffer and appends the argument buffer.
             *
             * @param   buf The buffer.
             * @param   sz  The size.
             */

            void Append(const T* buf, std::size_t sz)
            {
                if (0 == sz) return;
                resize(used_ + sz, true);
                std::memcpy(ptr_ + used_ - sz, buf, sz * sizeof(T));
            }

            /**
             * @fn  void Buffer::Append(T val)
             *
             * @brief   Resizes this buffer by one element and appends the argument value.
             *
             * @param   val The value to append.
             */

            void Append(T val)
            {
                resize(used_ + 1, true);
                ptr_[used_ - 1] = val;
            }

            /**
             * @fn  void Buffer::Append(const Buffer& buf)
             *
             * @brief   Resizes this buffer and appends the argument buffer.
             *
             * @param   buf The buffer to append.
             */

            void Append(const Buffer& buf)
            {
                append(buf.begin(), buf.size());
            }

            /**
             * @fn  std::size_t Buffer::GetCapacity() const
             *
             * @brief   Returns the allocated memory size in elements.
             *
             * @return  The capacity.
             */

            std::size_t GetCapacity() const
            {
                return capacity_;
            }

            /**
             * @fn  std::size_t Buffer::GetCpacityBytes() const
             *
             * @brief   Returns the allocated memory size in bytes.
             *
             * @return  The cpacity bytes.
             */

            std::size_t GetCpacityBytes() const
            {
                return capacity_ * sizeof(T);
            }

            /**
             * @fn  void Buffer::Swap(Buffer& other)
             *
             * @brief   Swaps the buffer with another one.
             *
             * @param [in,out]  other   The other.
             */

            void Swap(Buffer& other)
            {
                using std::swap;

                Swap(ptr_, other.ptr_);
                Swap(capacity_, other.capacity_);
                Swap(used_, other.used_);
            }

            /**
             * @fn  bool Buffer::operator== (const Buffer& other) const
             *
             * @brief   Compare operator.
             *
             * @param   other   The other.
             *
             * @return  true if the parameters are considered equivalent.
             */

            bool operator == (const Buffer& other) const
            {
                if (this != &other)
                {
                    if (used_ == other.used_)
                    {
                        if (std::memcmp(ptr_, other.ptr_, used_ * sizeof(T)) == 0)
                        {
                            return true;
                        }
                    }
                    return false;
                }

                return true;
            }

            /**
             * @fn  bool Buffer::operator!= (const Buffer& other) const
             *
             * @brief   Compare operator.
             *
             * @param   other   The other.
             *
             * @return  true if the parameters are not considered equivalent.
             */

            bool operator != (const Buffer& other) const
            {
                return !(*this == other);
            }

            /**
             * @fn  void Buffer::Clear()
             *
             * @brief   Sets the contents of the buffer to zero.
             */

            void Clear()
            {
                std::memset(ptr_, 0, used_ * sizeof(T));
            }

            /**
             * @fn  std::size_t Buffer::GetSize() const
             *
             * @brief   Returns the used size of the buffer in elements.
             *
             * @return  The size.
             */

            std::size_t GetSize() const
            {
                return used_;
            }

            /**
             * @fn  std::size_t Buffer::GetSizeBytes() const
             *
             * @brief   Returns the used size of the buffer in bytes.
             *
             * @return  The size bytes.
             */

            std::size_t GetSizeBytes() const
            {
                return used_ * sizeof(T);
            }

            /**
             * @fn  T* Buffer::Begin()
             *
             * @brief   Returns a pointer to the beginning of the buffer.
             *
             * @return  null if it fails, else a pointer to a T.
             */

            T* Begin()
            {
                return ptr_;
            }

            /**
             * @fn  const T* Buffer::Begin() const
             *
             * @brief   Returns a pointer to the beginning of the buffer.
             *
             * @return  null if it fails, else a pointer to a const T.
             */

            const T* Begin() const
            {
                return ptr_;
            }

            /**
             * @fn  T* Buffer::End()
             *
             * @brief   Returns a pointer to end of the buffer.
             *
             * @return  null if it fails, else a pointer to a T.
             */

            T* End()
            {
                return ptr_ + used_;
            }

            /**
             * @fn  const T* Buffer::End() const
             *
             * @brief   Returns a pointer to the end of the buffer.
             *
             * @return  null if it fails, else a pointer to a const T.
             */

            const T* End() const
            {
                return ptr_ + used_;
            }

            /**
             * @fn  bool Buffer::IsEmpty() const
             *
             * @brief   Return true if buffer is empty.
             *
             * @return  true if empty, false if not.
             */

            bool IsEmpty() const
            {
                return 0 == used_;
            }

            T& operator [] (std::size_t index)
            {
                technosoftware_assert(index < used_);

                return ptr_[index];
            }

            const T& operator [] (std::size_t index) const
            {
                technosoftware_assert(index < used_);

                return ptr_[index];
            }

        private:
            Buffer();

            std::size_t capacity_;
            std::size_t used_;
            T*          ptr_;
            bool        ownMem_;
        };

    }
}

#endif /* TECHNOSOFTWARE_BUFFER_H */
