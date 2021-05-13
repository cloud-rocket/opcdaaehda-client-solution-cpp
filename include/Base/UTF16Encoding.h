/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the UTF16Encoding class.
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

#ifndef TECHNOSOFTWARE_UTF16ENCODING_H
#define TECHNOSOFTWARE_UTF16ENCODING_H

#include "Base/Base.h"
#include "Base/TextEncoding.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   UTF16Encoding
         *
         * @brief   UTF-16 text encoding, as defined in RFC 2781.
         *          
         *          When converting from UTF-16 to Unicode, surrogates are reported as they are - in
         *          other words, surrogate pairs are not combined into one Unicode character. When
         *          converting from Unicode to UTF-16, however, characters outside the 16-bit range are
         *          converted into a low and high surrogate.
         *
         * @ingroup BaseText
         */

        class TECHNOSOFTWARE_API UTF16Encoding : public TextEncoding
        {
        public:

            /**
             * @enum    ByteOrderType
             *
             * @brief   Values that represent the byte order types.
             */

            enum ByteOrderType
            {
                ///< An enum constant representing the big endian byte order option
                BIG_ENDIAN_BYTE_ORDER,
                ///< An enum constant representing the little endian byte order option
                LITTLE_ENDIAN_BYTE_ORDER,
                ///< An enum constant representing the native byte order option
                NATIVE_BYTE_ORDER
            };

            /**
             * @fn  UTF16Encoding::UTF16Encoding(ByteOrderType byteOrder = NATIVE_BYTE_ORDER);
             *
             * @brief   Creates and initializes the encoding for the given byte order.
             *
             * @param   byteOrder   (Optional) the byte order.
             */

            UTF16Encoding(ByteOrderType byteOrder = NATIVE_BYTE_ORDER);

            /**
             * @fn  UTF16Encoding::UTF16Encoding(int byteOrderMark);
             *
             * @brief   Creates and initializes the encoding for the byte-order indicated by the given byte-
             *          order mark, which is the Unicode character 0xFEFF.
             *
             * @param   byteOrderMark   The byte order mark.
             */

            UTF16Encoding(int byteOrderMark);

            ~UTF16Encoding();

            /**
             * @fn  ByteOrderType UTF16Encoding::GetByteOrder() const;
             *
             * @brief   Returns the byte-order currently in use.
             *
             * @return  The byte order.
             */

            ByteOrderType GetByteOrder() const;

            /**
             * @fn  void UTF16Encoding::SetByteOrder(ByteOrderType byteOrder);
             *
             * @brief   Sets the byte order.
             *
             * @param   byteOrder   The byte order.
             */

            void SetByteOrder(ByteOrderType byteOrder);

            /**
             * @fn  void UTF16Encoding::SetByteOrder(int byteOrderMark);
             *
             * @brief   Sets the byte order according to the given byte order mark, which is the Unicode
             *          character 0xFEFF.
             *
             * @param   byteOrderMark   The byte order mark.
             */

            void SetByteOrder(int byteOrderMark);

            const char* GetCanonicalName() const override;
            bool IsA(const std::string& encodingName) const override;
            const CharacterMap& GetCharacterMap() const override;
            int Convert(const unsigned char* bytes) const override;
            int Convert(int ch, unsigned char* bytes, int length) const override;
            int QueryConvert(const unsigned char* bytes, int length) const override;
            int GetSequenceLength(const unsigned char* bytes, int length) const override;

        private:
            bool flipBytes_;
            static const char* names_[];
            static const CharacterMap charMap_;
        };
    }
}

#endif /* TECHNOSOFTWARE_UTF16ENCODING_H */
