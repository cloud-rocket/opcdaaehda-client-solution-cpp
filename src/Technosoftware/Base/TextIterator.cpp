/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the TextIterator class.
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

#include "Base/TextIterator.h"
#include "Base/TextEncoding.h"
#include <algorithm>


namespace Technosoftware
{
    namespace Base
    {


        TextIterator::TextIterator() :
            textEncoding_(0)
        {
        }


        TextIterator::TextIterator(const std::string& str, const TextEncoding& encoding) :
            textEncoding_(&encoding),
            iterator_(str.begin()),
            end_(str.end())
        {
        }


        TextIterator::TextIterator(const std::string::const_iterator& begin, const std::string::const_iterator& end, const TextEncoding& encoding) :
            textEncoding_(&encoding),
            iterator_(begin),
            end_(end)
        {
        }


        TextIterator::TextIterator(const std::string& str) :
            textEncoding_(0),
            iterator_(str.end()),
            end_(str.end())
        {
        }


        TextIterator::TextIterator(const std::string::const_iterator& end) :
            textEncoding_(0),
            iterator_(end),
            end_(end)
        {
        }


        TextIterator::~TextIterator()
        {
        }


        TextIterator::TextIterator(const TextIterator& it) :
            textEncoding_(it.textEncoding_),
            iterator_(it.iterator_),
            end_(it.end_)
        {
        }


        TextIterator& TextIterator::operator = (const TextIterator& it)
        {
            if (&it != this)
            {
                textEncoding_ = it.textEncoding_;
                iterator_ = it.iterator_;
                end_ = it.end_;
            }
            return *this;
        }


        void TextIterator::Swap(TextIterator& it)
        {
            std::swap(textEncoding_, it.textEncoding_);
            std::swap(iterator_, it.iterator_);
            std::swap(end_, it.end_);
        }


        int TextIterator::operator * () const
        {
            technosoftware_check_ptr(textEncoding_);
            technosoftware_assert(iterator_ != end_);
            std::string::const_iterator it = iterator_;

            unsigned char buffer[TextEncoding::MAX_SEQUENCE_LENGTH];
            unsigned char* p = buffer;

            if (it != end_)
                *p++ = *it++;
            else
                *p++ = 0;

            int read = 1;
            int n = textEncoding_->QueryConvert(buffer, 1);

            while (-1 > n && (end_ - it) >= -n - read)
            {
                while (read < -n && it != end_)
                {
                    *p++ = *it++;
                    read++;
                }
                n = textEncoding_->QueryConvert(buffer, read);
            }

            if (-1 > n)
            {
                return -1;
            }
            else
            {
                return n;
            }
        }


        TextIterator& TextIterator::operator ++ ()
        {
            technosoftware_check_ptr(textEncoding_);
            technosoftware_assert(iterator_ != end_);

            unsigned char buffer[TextEncoding::MAX_SEQUENCE_LENGTH];
            unsigned char* p = buffer;

            if (iterator_ != end_)
                *p++ = *iterator_++;
            else
                *p++ = 0;

            int read = 1;
            int n = textEncoding_->GetSequenceLength(buffer, 1);

            while (-1 > n && (end_ - iterator_) >= -n - read)
            {
                while (read < -n && iterator_ != end_)
                {
                    *p++ = *iterator_++;
                    read++;
                }
                n = textEncoding_->GetSequenceLength(buffer, read);
            }
            while (read < n && iterator_ != end_)
            {
                iterator_++;
                read++;
            }

            return *this;
        }


        TextIterator TextIterator::operator ++ (int)
        {
            TextIterator prev(*this);
            operator ++ ();
            return prev;
        }

    }
}
