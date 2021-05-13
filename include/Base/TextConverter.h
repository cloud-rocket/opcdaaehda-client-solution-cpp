/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the TextConverter class.
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

#ifndef TECHNOSOFTWARE_TEXTCONVERTER_H
#define TECHNOSOFTWARE_TEXTCONVERTER_H

#include "Base/Base.h"

namespace Technosoftware
{
    namespace Base
    {
        class TextEncoding;

        /**
         * @class   TextConverter
         *
         * @brief   A TextConverter converts strings from one encoding into another.
         *
         * @ingroup BaseText
         */

        class TECHNOSOFTWARE_API TextConverter
        {
        public:
            /// Transform function for convert.
            typedef int(*Transform)(int);

            /**
             * @fn  TextConverter::TextConverter(const TextEncoding& inEncoding, const TextEncoding& outEncoding, int defaultChar = '?');
             *
             * @brief   Creates the TextConverter. The encoding objects must not be deleted while the
             *          TextConverter is in use.
             *
             * @param   inEncoding  The in encoding.
             * @param   outEncoding The out encoding.
             * @param   defaultChar (Optional) the default character.
             */

            TextConverter(const TextEncoding& inEncoding, const TextEncoding& outEncoding, int defaultChar = '?');

            /**
             * @fn  TextConverter::~TextConverter();
             *
             * @brief   Destroys the TextConverter.
             */

            ~TextConverter();

            /**
             * @fn  int TextConverter::Convert(const std::string& source, std::string& destination, Transform trans);
             *
             * @brief   Converts the source string from inEncoding to outEncoding and appends the result to
             *          destination. Every character is passed to the transform function. If a character
             *          cannot be represented in outEncoding, defaultChar is used instead. Returns the number
             *          of encoding errors (invalid byte sequences in source).
             *
             * @param   source              Source for the.
             * @param [in,out]  destination Destination for the.
             * @param   trans               The transaction.
             *
             * @return  An int.
             */

            int Convert(const std::string& source, std::string& destination, Transform trans);

            /**
             * @fn  int TextConverter::Convert(const void* source, int length, std::string& destination, Transform trans);
             *
             * @brief   Converts the source buffer from inEncoding to outEncoding and appends the result to
             *          destination. Every character is passed to the transform function. If a character
             *          cannot be represented in outEncoding, defaultChar is used instead. Returns the number
             *          of encoding errors (invalid byte sequences in source).
             *
             * @param   source              Source for the.
             * @param   length              The length.
             * @param [in,out]  destination Destination for the.
             * @param   trans               The transaction.
             *
             * @return  An int.
             */

            int Convert(const void* source, int length, std::string& destination, Transform trans);

            /**
             * @fn  int TextConverter::Convert(const std::string& source, std::string& destination);
             *
             * @brief   Converts the source string from inEncoding to outEncoding and appends the result to
             *          destination. If a character cannot be represented in outEncoding, defaultChar is used
             *          instead. Returns the number of encoding errors (invalid byte sequences in source).
             *
             * @param   source              Source for the.
             * @param [in,out]  destination Destination for the.
             *
             * @return  An int.
             */

            int Convert(const std::string& source, std::string& destination);

            /**
             * @fn  int TextConverter::Convert(const void* source, int length, std::string& destination);
             *
             * @brief   Converts the source buffer from inEncoding to outEncoding and appends the result to
             *          destination. If a character cannot be represented in outEncoding, defaultChar is used
             *          instead. Returns the number of encoding errors (invalid byte sequences in source).
             *
             * @param   source              Source for the.
             * @param   length              The length.
             * @param [in,out]  destination Destination for the.
             *
             * @return  An int.
             */

            int Convert(const void* source, int length, std::string& destination);

        private:
            TextConverter();
            TextConverter(const TextConverter&);
            TextConverter& operator = (const TextConverter&);

            const TextEncoding& inEncoding_;
            const TextEncoding& outEncoding_;
            int                 defaultChar_;
        };
    }
}

#endif /* TECHNOSOFTWARE_TEXTCONVERTER_H */
