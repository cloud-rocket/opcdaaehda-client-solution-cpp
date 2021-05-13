 /*
  * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
  * Web: https://technosoftware.com
  *
  * Purpose:
  * Definition of the UnicodeConverter class.
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

#ifndef TECHNOSOFTWARE_UNICODECONVERTER_H
#define TECHNOSOFTWARE_UNICODECONVERTER_H

#include "Base/Base.h"
#include "Base/UTFString.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class    UnicodeConverter
         *
         * @brief    A convenience class that converts strings from UTF-8 encoded std::strings to UTF-16
         *           or UTF-32 encoded std::wstrings and vice-versa.
         *             
         *           This class is mainly used for working with the Unicode Windows APIs and probably
         *           won't be of much use anywhere else ???
         *
         * @ingroup BaseText
         */

        class TECHNOSOFTWARE_API UnicodeConverter
        {
        public:

            /**
             * @fn  static void UnicodeConverter::Convert(const std::string& utf8String, UTF32String& utf32String);
             *
             * @brief   Converts the given UTF-8 encoded string into an UTF-32 encoded wide string.
             *
             * @param   utf8String          The UTF 8 string.
             * @param [in,out]  utf32String The UTF 32 string.
             */

            static void Convert(const std::string& utf8String, UTF32String& utf32String);

            /**
             * @fn  static void UnicodeConverter::Convert(const char* utf8String, std::size_t length, UTF32String& utf32String);
             *
             * @brief   Converts the given UTF-8 encoded character sequence into an UTF-32 encoded wide
             *          string.
             *
             * @param   utf8String          The UTF 8 string.
             * @param   length              The length.
             * @param [in,out]  utf32String The UTF 32 string.
             */

            static void Convert(const char* utf8String, std::size_t length, UTF32String& utf32String);

            /**
             * @fn  static void UnicodeConverter::Convert(const char* utf8String, UTF32String& utf32String);
             *
             * @brief   Converts the given zero-terminated UTF-8 encoded character sequence into an UTF-32
             *          encoded wide string.
             *
             * @param   utf8String          The UTF 8 string.
             * @param [in,out]  utf32String The UTF 32 string.
             */

            static void Convert(const char* utf8String, UTF32String& utf32String);

            /**
             * @fn  static void UnicodeConverter::Convert(const std::string& utf8String, UTF16String& utf16String);
             *
             * @brief   Converts the given UTF-8 encoded string into an UTF-16 encoded wide string.
             *
             * @param   utf8String          The UTF 8 string.
             * @param [in,out]  utf16String The UTF 16 string.
             */

            static void Convert(const std::string& utf8String, UTF16String& utf16String);

            /**
             * @fn  static void UnicodeConverter::Convert(const char* utf8String, std::size_t length, UTF16String& utf16String);
             *
             * @brief   Converts the given UTF-8 encoded character sequence into an UTF-16 encoded wide
             *          string.
             *
             * @param   utf8String          The UTF 8 string.
             * @param   length              The length.
             * @param [in,out]  utf16String The UTF 16 string.
             */

            static void Convert(const char* utf8String, std::size_t length, UTF16String& utf16String);

            /**
             * @fn  static void UnicodeConverter::Convert(const char* utf8String, UTF16String& utf16String);
             *
             * @brief   Converts the given zero-terminated UTF-8 encoded character sequence into an UTF-16
             *          encoded wide string.
             *
             * @param   utf8String          The UTF 8 string.
             * @param [in,out]  utf16String The UTF 16 string.
             */

            static void Convert(const char* utf8String, UTF16String& utf16String);

            /**
             * @fn  static void UnicodeConverter::Convert(const UTF16String& utf16String, std::string& utf8String);
             *
             * @brief   Converts the given UTF-16 encoded wide string into an UTF-8 encoded string.
             *
             * @param   utf16String         The UTF 16 string.
             * @param [in,out]  utf8String  The UTF 8 string.
             */

            static void Convert(const UTF16String& utf16String, std::string& utf8String);

            /**
             * @fn  static void UnicodeConverter::Convert(const UTF32String& utf32String, std::string& utf8String);
             *
             * @brief   Converts the given UTF-32 encoded wide string into an UTF-8 encoded string.
             *
             * @param   utf32String         The UTF 32 string.
             * @param [in,out]  utf8String  The UTF 8 string.
             */

            static void Convert(const UTF32String& utf32String, std::string& utf8String);

            /**
             * @fn  static void UnicodeConverter::Convert(const UTF16Char* utf16String, std::size_t length, std::string& utf8String);
             *
             * @brief   Converts the given zero-terminated UTF-16 encoded wide character sequence into an UTF-
             *          8 encoded string.
             *
             * @param   utf16String         The UTF 16 string.
             * @param   length              The length.
             * @param [in,out]  utf8String  The UTF 8 string.
             */

            static void Convert(const UTF16Char* utf16String, std::size_t length, std::string& utf8String);

            /**
             * @fn  static void UnicodeConverter::Convert(const UTF32Char* utf16String, std::size_t length, std::string& utf8String);
             *
             * @brief   Converts the given zero-terminated UTF-32 encoded wide character sequence into an UTF-
             *          8 encoded string.
             *
             * @param   utf16String         The UTF 16 string.
             * @param   length              The length.
             * @param [in,out]  utf8String  The UTF 8 string.
             */

            static void Convert(const UTF32Char* utf16String, std::size_t length, std::string& utf8String);

            /**
             * @fn  static void UnicodeConverter::Convert(const UTF16Char* utf16String, std::string& utf8String);
             *
             * @brief   Converts the given UTF-16 encoded zero terminated character sequence into an UTF-8
             *          encoded string.
             *
             * @param   utf16String         The UTF 16 string.
             * @param [in,out]  utf8String  The UTF 8 string.
             */

            static void Convert(const UTF16Char* utf16String, std::string& utf8String);

            /**
             * @fn  static void UnicodeConverter::Convert(const UTF32Char* utf32String, std::string& utf8String);
             *
             * @brief   Converts the given UTF-32 encoded zero terminated character sequence into an UTF-8
             *          encoded string.
             *
             * @param   utf32String         The UTF 32 string.
             * @param [in,out]  utf8String  The UTF 8 string.
             */

            static void Convert(const UTF32Char* utf32String, std::string& utf8String);

            template <typename F, typename T>
            static void toUTF32(const F& f, T& t)
            {
                Convert(f, t);
            }

            template <typename F, typename T>
            static void toUTF32(const F& f, std::size_t l, T& t)
            {
                Convert(f, l, t);
            }

            template <typename F, typename T>
            static void toUTF16(const F& f, T& t)
            {
                Convert(f, t);
            }

            template <typename F, typename T>
            static void toUTF16(const F& f, std::size_t l, T& t)
            {
                Convert(f, l, t);
            }

            template <typename F, typename T>
            static void toUTF8(const F& f, T& t)
            {
                Convert(f, t);
            }

            template <typename F, typename T>
            static void toUTF8(const F& f, std::size_t l, T& t)
            {
                Convert(f, l, t);
            }

            template <typename T>
            static T to(const char* pChar)
            {
                T utfStr;
                Base::UnicodeConverter::Convert(pChar, utfStr);
                return utfStr;
            }


            template <typename T>
            static T to(const std::string& str)
            {
                T utfStr;
                Base::UnicodeConverter::Convert(str, utfStr);
                return utfStr;
            }

            template <typename T>

            /**
             * @fn  static std::size_t UnicodeConverter::UTFStrlen(const T* ptr)
             *
             * @brief   Returns the length (in characters) of a zero-terminated UTF string.
             *
             * @param   ptr The pointer.
             *
             * @return  A std::size_t.
             */

            static std::size_t UTFStrlen(const T* ptr)
            {
                if (ptr == nullptr) return 0;
                const T* p;
                for (p = ptr; *p; ++p);
                return p - ptr;
            }
        };
    }
}

#endif /* TECHNOSOFTWARE_UNICODECONVERTER_H */
