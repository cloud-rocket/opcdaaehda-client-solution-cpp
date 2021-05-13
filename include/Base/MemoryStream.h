/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of MemoryStreamBuf, MemoryInputStream, MemoryOutputStream
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

#ifndef TECHNOSOFTWARE_MEMORYSTREAM_H
#define TECHNOSOFTWARE_MEMORYSTREAM_H

#include "Base/Bugcheck.h"
#include "Base/Base.h"
#include "Base/StreamUtil.h"
#include <streambuf>
#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   BasicMemoryStreamBuf
         *
         * @brief   BasicMemoryStreamBuf is a simple implementation of a stream buffer for reading and
         *          writing from a memory area.
         *          
         *          This streambuf only supports unidirectional streams. In other words, the
         *          BasicMemoryStreamBuf can be used for the implementation of an istream or an ostream,
         *          but not for an iostream.
         *
         * @ingroup BaseStreams
         */

        template <typename ch, typename tr>
        class BasicMemoryStreamBuf : public std::basic_streambuf<ch, tr>
        {
        protected:
            typedef std::basic_streambuf<ch, tr> Base;
            typedef std::basic_ios<ch, tr> IOS;
            typedef ch char_type;
            typedef tr char_traits;
            typedef typename Base::int_type int_type;
            typedef typename Base::pos_type pos_type;
            typedef typename Base::off_type off_type;

        public:
            BasicMemoryStreamBuf(char_type* pBuffer, std::streamsize bufferSize) :
                buffer_(pBuffer),
                bufferSize_(bufferSize)
            {
                this->setg(buffer_, buffer_, buffer_ + bufferSize_);
                this->setp(buffer_, buffer_ + bufferSize_);
            }

            ~BasicMemoryStreamBuf()
            {
            }

            virtual int_type Iverflow(int_type /*c*/)
            {
                return char_traits::eof();
            }

            virtual int_type Underflow()
            {
                return char_traits::eof();
            }

            virtual pos_type Seekoff(off_type off, std::ios_base::seekdir way, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out)
            {
                const pos_type fail = off_type(-1);
                off_type newoff = off_type(-1);

                if ((which & std::ios_base::in) != 0)
                {
                    if (this->gptr() == 0)
                        return fail;

                    if (way == std::ios_base::beg)
                    {
                        newoff = 0;
                    }
                    else if (way == std::ios_base::cur)
                    {
                        // cur is not valid if both in and out are specified (Condition 3)
                        if ((which & std::ios_base::out) != 0)
                            return fail;
                        newoff = this->gptr() - this->eback();
                    }
                    else if (way == std::ios_base::end)
                    {
                        newoff = this->egptr() - this->eback();
                    }
                    else
                    {
                        technosoftware_bugcheck();
                    }

                    if ((newoff + off) < 0 || (this->egptr() - this->eback()) < (newoff + off))
                        return fail;
                    this->setg(this->eback(), this->eback() + newoff + off, this->egptr());
                }

                if ((which & std::ios_base::out) != 0)
                {
                    if (this->pptr() == 0)
                        return fail;

                    if (way == std::ios_base::beg)
                    {
                        newoff = 0;
                    }
                    else if (way == std::ios_base::cur)
                    {
                        // cur is not valid if both in and out are specified (Condition 3)
                        if ((which & std::ios_base::in) != 0)
                            return fail;
                        newoff = this->pptr() - this->pbase();
                    }
                    else if (way == std::ios_base::end)
                    {
                        newoff = this->epptr() - this->pbase();
                    }
                    else
                    {
                        technosoftware_bugcheck();
                    }

                    if (newoff + off < 0 || (this->epptr() - this->pbase()) < newoff + off)
                        return fail;
                    this->pbump((int)(newoff + off - (this->pptr() - this->pbase())));
                }

                return newoff;
            }

            virtual int Sync()
            {
                return 0;
            }

            std::streamsize GetCharsWritten() const
            {
                return static_cast<std::streamsize>(this->pptr() - this->pbase());
            }

            /**
             * @fn  void BasicMemoryStreamBuf::Reset()
             *
             * @brief   Resets the buffer so that current read and write positions will be set to the
             *          beginning of the buffer.
             */

            void Reset()
            {
                this->setg(buffer_, buffer_, buffer_ + bufferSize_);
                this->setp(buffer_, buffer_ + bufferSize_);
            }

        private:
            char_type*      buffer_;
            std::streamsize bufferSize_;

            BasicMemoryStreamBuf();
            BasicMemoryStreamBuf(const BasicMemoryStreamBuf&);
            BasicMemoryStreamBuf& operator = (const BasicMemoryStreamBuf&);
        };

        /**
         * @typedef BasicMemoryStreamBuf<char, std::char_traits<char> > MemoryStreamBuf
         *
         * @brief   We provide an instantiation for char.
         *
         * @ingroup BaseStreams
         */

        typedef BasicMemoryStreamBuf<char, std::char_traits<char> > MemoryStreamBuf;

        /**
         * @class   MemoryIOS
         *
         * @brief   The base class for MemoryInputStream and MemoryOutputStream.
         *          
         *          This class is needed to ensure the correct initialization order of the stream buffer
         *          and base classes.
         *
         * @ingroup BaseStreams
         */

        class TECHNOSOFTWARE_API MemoryIOS : public virtual std::ios
        {
        public:
            MemoryIOS(char* pBuffer, std::streamsize bufferSize);
            /// Creates the basic stream.

            ~MemoryIOS();
            /// Destroys the stream.

            /**
             * @fn  MemoryStreamBuf* MemoryIOS::GetBuffer();
             *
             * @brief   Returns a pointer to the underlying streambuf.
             *
             * @return  null if it fails, else the buffer.
             */

            MemoryStreamBuf* GetBuffer();

        protected:
            MemoryStreamBuf streamBuffer_;
        };

        /**
         * @class   MemoryInputStream
         *
         * @brief   An input stream for reading from a memory area.
         *
         * @ingroup BaseStreams
         */

        class TECHNOSOFTWARE_API MemoryInputStream : public MemoryIOS, public std::istream
        {
        public:

            /**
             * @fn  MemoryInputStream::MemoryInputStream(const char* pBuffer, std::streamsize bufferSize);
             *
             * @brief   Creates a MemoryInputStream for the given memory area, ready for reading.
             *
             * @param   pBuffer     The buffer.
             * @param   bufferSize  Size of the buffer.
             */

            MemoryInputStream(const char* pBuffer, std::streamsize bufferSize);

            /**
             * @fn  MemoryInputStream::~MemoryInputStream();
             *
             * @brief   Destroys the MemoryInputStream.
             */

            ~MemoryInputStream();
        };

        /**
         * @class   MemoryOutputStream
         *
         * @brief   An input stream for reading from a memory area.
         *
         * @ingroup BaseStreams
         */

        class TECHNOSOFTWARE_API MemoryOutputStream : public MemoryIOS, public std::ostream
        {
        public:

            /**
             * @fn  MemoryOutputStream::MemoryOutputStream(char* pBuffer, std::streamsize bufferSize);
             *
             * @brief   Creates a MemoryOutputStream for the given memory area, ready for writing.
             *
             * @param [in,out]  pBuffer If non-null, the buffer.
             * @param   bufferSize      Size of the buffer.
             */

            MemoryOutputStream(char* pBuffer, std::streamsize bufferSize);

            /**
             * @fn  MemoryOutputStream::~MemoryOutputStream();
             *
             * @brief   Destroys the MemoryInputStream.
             */

            ~MemoryOutputStream();

            /**
             * @fn  std::streamsize MemoryOutputStream::GetCharsWritten() const;
             *
             * @brief   Returns the number of chars written to the buffer.
             *
             * @return  The characters written.
             */

            std::streamsize GetCharsWritten() const;
        };


        //
        // inlines
        //
        inline MemoryStreamBuf* MemoryIOS::GetBuffer()
        {
            return &streamBuffer_;
        }


        inline std::streamsize MemoryOutputStream::GetCharsWritten() const
        {
            return streamBuffer_.GetCharsWritten();
        }

    }
}


#endif /* TECHNOSOFTWARE_MEMORYSTREAM_H */
