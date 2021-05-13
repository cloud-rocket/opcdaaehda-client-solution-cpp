/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Ascii class.
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

#ifndef TECHNOSOFTWARE_ASCII_H
#define TECHNOSOFTWARE_ASCII_H

#include "Base/Base.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   Ascii
         *
         * @brief   This class contains enumerations and static utility functions for dealing with ASCII
         *          characters and their properties.
         *          
         *          The classification functions will also work if non-ASCII character codes are passed
         *          to them, but classification will only check for ASCII characters.
         *          
         *          This allows the classification methods to be used on the single bytes of a UTF-8
         *          string, without causing assertions or inconsistent results (depending upon the
         *          current locale) on bytes outside the ASCII range, as may be produced by
         *          Ascii::IsSpace(), etc.
         *
         * @ingroup BaseCore
         */

        class TECHNOSOFTWARE_API Ascii
        {
        public:
            enum CharacterProperties
                /// ASCII character properties.
            {
                ACP_CONTROL = 0x0001,
                ACP_SPACE = 0x0002,
                ACP_PUNCT = 0x0004,
                ACP_DIGIT = 0x0008,
                ACP_HEXDIGIT = 0x0010,
                ACP_ALPHA = 0x0020,
                ACP_LOWER = 0x0040,
                ACP_UPPER = 0x0080,
                ACP_GRAPH = 0x0100,
                ACP_PRINT = 0x0200
            };

            /// Return the ASCII character properties for the
            /// character with the given ASCII value.
            ///
            /// If the character is outside the ASCII range
            /// (0 .. 127), 0 is returned.
            static int GetProperties(int ch);

            /// Returns true if the given character is
            /// within the ASCII range and has at least one of 
            /// the given properties.
            static bool hasSomeProperties(int ch, int properties);

            /// Returns true if the given character is
            /// within the ASCII range and has all of 
            /// the given properties.
            static bool HasProperties(int ch, int properties);

            /// Returns true iff the given character code is within
            /// the ASCII range (0 .. 127).
            static bool IsAscii(int ch);

            /**
             * @fn  static bool Ascii::IsSpace(int ch);
             *
             * @brief   Returns true iff the given character is a whitespace.
             *
             * @param   ch  The ch.
             *
             * @return  true if space, false if not.
             */

            static bool IsSpace(int ch);

            /**
             * @fn  static bool Ascii::IsDigit(int ch);
             *
             * @brief   Returns true iff the given character is a digit.
             *
             * @param   ch  The ch.
             *
             * @return  true if digit, false if not.
             */

            static bool IsDigit(int ch);

            /**
             * @fn  static bool Ascii::IsHexDigit(int ch);
             *
             * @brief   Returns true iff the given character is a hexadecimal digit.
             *
             * @param   ch  The ch.
             *
             * @return  true if hexadecimal digit, false if not.
             */

            static bool IsHexDigit(int ch);

            /**
             * @fn  static bool Ascii::IsPunct(int ch);
             *
             * @brief   Returns true iff the given character is a punctuation character.
             *
             * @param   ch  The ch.
             *
             * @return  true if punct, false if not.
             */

            static bool IsPunct(int ch);

            /**
             * @fn  static bool Ascii::IsAlpha(int ch);
             *
             * @brief   Returns true iff the given character is an alphabetic character.
             *
             * @param   ch  The ch.
             *
             * @return  true if alpha, false if not.
             */

            static bool IsAlpha(int ch);

            /**
             * @fn  static bool Ascii::IsAlphaNumeric(int ch);
             *
             * @brief   Returns true iff the given character is an alphabetic character.
             *
             * @param   ch  The ch.
             *
             * @return  true if alpha numeric, false if not.
             */

            static bool IsAlphaNumeric(int ch);

            /**
             * @fn  static bool Ascii::IsLower(int ch);
             *
             * @brief   Returns true iff the given character is a lowercase alphabetic character.
             *
             * @param   ch  The ch.
             *
             * @return  true if lower, false if not.
             */

            static bool IsLower(int ch);

            /// Returns true iff the given character is an uppercase alphabetic
            /// character.
            static bool IsUpper(int ch);

            /**
             * @fn  static int Ascii::ToLower(int ch);
             *
             * @brief   If the given character is an uppercase character, return its lowercase counterpart,
             *          otherwise return the character.
             *
             * @param   ch  The ch.
             *
             * @return  ch as an int.
             */

            static int ToLower(int ch);

            /**
             * @fn  static int Ascii::ToUpper(int ch);
             *
             * @brief   If the given character is a lowercase character, return its uppercase counterpart,
             *          otherwise return the character.
             *
             * @param   ch  The ch.
             *
             * @return  ch as an int.
             */

            static int ToUpper(int ch);

        private:
            static const int CHARACTER_PROPERTIES[128];
        };


        //
        // inlines
        //
        inline int Ascii::GetProperties(int ch)
        {
            if (IsAscii(ch))
                return CHARACTER_PROPERTIES[ch];
            else
                return 0;
        }


        inline bool Ascii::IsAscii(int ch)
        {
            return (static_cast<UInt32>(ch) & 0xFFFFFF80) == 0;
        }


        inline bool Ascii::HasProperties(int ch, int props)
        {
            return (GetProperties(ch) & props) == props;
        }


        inline bool Ascii::hasSomeProperties(int ch, int props)
        {
            return (GetProperties(ch) & props) != 0;
        }


        inline bool Ascii::IsSpace(int ch)
        {
            return HasProperties(ch, ACP_SPACE);
        }


        inline bool Ascii::IsDigit(int ch)
        {
            return HasProperties(ch, ACP_DIGIT);
        }


        inline bool Ascii::IsHexDigit(int ch)
        {
            return HasProperties(ch, ACP_HEXDIGIT);
        }


        inline bool Ascii::IsPunct(int ch)
        {
            return HasProperties(ch, ACP_PUNCT);
        }


        inline bool Ascii::IsAlpha(int ch)
        {
            return HasProperties(ch, ACP_ALPHA);
        }


        inline bool Ascii::IsAlphaNumeric(int ch)
        {
            return hasSomeProperties(ch, ACP_ALPHA | ACP_DIGIT);
        }


        inline bool Ascii::IsLower(int ch)
        {
            return HasProperties(ch, ACP_LOWER);
        }


        inline bool Ascii::IsUpper(int ch)
        {
            return HasProperties(ch, ACP_UPPER);
        }


        inline int Ascii::ToLower(int ch)
        {
            if (IsUpper(ch))
                return ch + 32;
            else
                return ch;
        }


        inline int Ascii::ToUpper(int ch)
        {
            if (IsLower(ch))
                return ch - 32;
            else
                return ch;
        }
    }
}

#endif /* TECHNOSOFTWARE_ASCII_H */