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

#ifndef TECHNOSOFTWARE_TEXTITERATOR_H
#define TECHNOSOFTWARE_TEXTITERATOR_H

#include "Base/Base.h"

namespace Technosoftware
{
    namespace Base
    {
        class TextEncoding;

        /**
         * @class   TextIterator
         *
         * @brief   An unidirectional iterator for iterating over characters in a string. The
         *          TextIterator uses a TextEncoding object to work with multi-byte character encodings
         *          like UTF-8. Characters are reported in Unicode.
         *          
         *          Example: Count the number of UTF-8 characters in a string.
         *          
         *              UTF8Encoding utf8Encoding;
         *              std::string utf8String("....");
         *              TextIterator it(utf8String, utf8Encoding);
         *              TextIterator end(utf8String);
         *              int n = 0;
         *              while (it != end) { ++n; ++it; }
         *          
         *          NOTE: When an UTF-16 encoding is used, surrogate pairs will be reported as two
         *          separate characters, due to restrictions of the TextEncoding class.
         *          
         *          For iterating over char buffers, see the TextBufferIterator class.
         *
         * @ingroup BaseText
         */

        class TECHNOSOFTWARE_API TextIterator
        {
        public:

            /**
             * @fn  TextIterator::TextIterator();
             *
             * @brief   Creates an uninitialized TextIterator.
             */

            TextIterator();

            /**
             * @fn  TextIterator::TextIterator(const std::string& str, const TextEncoding& encoding);
             *
             * @brief   Creates a TextIterator for the given string. The encoding object must not be deleted
             *          as long as the iterator is in use.
             *
             * @param   str         The string.
             * @param   encoding    The encoding.
             */

            TextIterator(const std::string& str, const TextEncoding& encoding);

            /**
             * @fn  TextIterator::TextIterator(const std::string::const_iterator& begin, const std::string::const_iterator& end, const TextEncoding& encoding);
             *
             * @brief   Creates a TextIterator for the given range. The encoding object must not be deleted
             *          as long as the iterator is in use.
             *
             * @param   begin       The begin.
             * @param   end         The end.
             * @param   encoding    The encoding.
             */

            TextIterator(const std::string::const_iterator& begin, const std::string::const_iterator& end, const TextEncoding& encoding);

            /**
             * @fn  TextIterator::TextIterator(const std::string& str);
             *
             * @brief   Creates an end TextIterator for the given string.
             *
             * @param   str The string.
             */

            TextIterator(const std::string& str);

            /**
             * @fn  TextIterator::TextIterator(const std::string::const_iterator& end);
             *
             * @brief   Creates an end TextIterator.
             *
             * @param   end The end.
             */

            TextIterator(const std::string::const_iterator& end);

            /**
             * @fn  TextIterator::~TextIterator();
             *
             * @brief   Destroys the TextIterator.
             */

            ~TextIterator();

            /**
             * @fn  TextIterator::TextIterator(const TextIterator& it);
             *
             * @brief   Copy constructor.
             *
             * @param   it  The iterator.
             */

            TextIterator(const TextIterator& it);

            /**
             * @fn  TextIterator& TextIterator::operator= (const TextIterator& it);
             *
             * @brief   Assignment operator.
             *
             * @param   it  The iterator.
             *
             * @return  A shallow copy of this object.
             */

            TextIterator& operator = (const TextIterator& it);

            /**
             * @fn  void TextIterator::Swap(TextIterator& it);
             *
             * @brief   Swaps the iterator with another one.
             *
             * @param [in,out]  it  The iterator.
             */

            void Swap(TextIterator& it);

            /**
             * @fn  int TextIterator::operator* () const;
             *
             * @brief   Returns the Unicode value of the current character. If there is no valid character at
             *          the current position,
             *          -1 is returned.
             *
             * @return  The result of the operation.
             */

            int operator * () const;

            /**
             * @fn  TextIterator& TextIterator::operator++ ();
             *
             * @brief   Prefix increment operator.
             *
             * @return  The result of the operation.
             */

            TextIterator& operator ++ ();

            /**
             * @fn  TextIterator TextIterator::operator++ (int increment);
             *
             * @brief   Postfix increment operator.
             *
             * @param   increment   The first parameter.
             *
             * @return  The result of the operation.
             */

            TextIterator operator ++ (int increment);

            /**
             * @fn  bool TextIterator::operator== (const TextIterator& it) const;
             *
             * @brief   Compares two iterators for equality.
             *
             * @param   it  The iterator.
             *
             * @return  true if the parameters are considered equivalent.
             */

            bool operator == (const TextIterator& it) const;

            /**
             * @fn  bool TextIterator::operator!= (const TextIterator& it) const;
             *
             * @brief   Compares two iterators for inequality.
             *
             * @param   it  The iterator.
             *
             * @return  true if the parameters are not considered equivalent.
             */

            bool operator != (const TextIterator& it) const;

            /**
             * @fn  TextIterator TextIterator::GetEnd() const;
             *
             * @brief   Returns the end iterator for the range handled by the iterator.
             *
             * @return  A TextIterator.
             */

            TextIterator GetEnd() const;

        private:
            const TextEncoding*         textEncoding_;
            std::string::const_iterator iterator_;
            std::string::const_iterator end_;
        };


        //
        // inlines
        //
        inline bool TextIterator::operator == (const TextIterator& it) const
        {
            return iterator_ == it.iterator_;
        }


        inline bool TextIterator::operator != (const TextIterator& it) const
        {
            return iterator_ != it.iterator_;
        }


        inline void swap(TextIterator& it1, TextIterator& it2)
        {
            it1.Swap(it2);
        }


        inline TextIterator TextIterator::GetEnd() const
        {
            return TextIterator(end_);
        }
    }
}

#endif /* TECHNOSOFTWARE_TEXTITERATOR_H */
