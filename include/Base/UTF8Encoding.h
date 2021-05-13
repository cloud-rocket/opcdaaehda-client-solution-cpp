/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the UTF8Encoding class.
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

#ifndef TECHNOSOFTWARE_UTF8ENCODING_H
#define TECHNOSOFTWARE_UTF8ENCODING_H

#include "Base/Base.h"
#include "Base/TextEncoding.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class    UTF8Encoding
         *
         * @brief    UTF-8 text encoding, as defined in RFC 2279.
         *
         * @ingroup BaseText
         */

        class TECHNOSOFTWARE_API UTF8Encoding : public TextEncoding
        {
        public:
            UTF8Encoding();
            ~UTF8Encoding();
            const char* GetCanonicalName() const override;
            bool IsA(const std::string& encodingName) const override;
            const CharacterMap& GetCharacterMap() const override;
            int Convert(const unsigned char* bytes) const override;
            int Convert(int ch, unsigned char* bytes, int length) const override;
            int QueryConvert(const unsigned char* bytes, int length) const override;
            int GetSequenceLength(const unsigned char* bytes, int length) const override;

            /**
             * @fn  static bool UTF8Encoding::IsLegal(const unsigned char *bytes, int length);
             *
             * @brief   Utility routine to tell whether a sequence of bytes is legal UTF-8. This must be
             *          called with the length pre-determined by the first byte. The sequence is illegal
             *          right away if there aren't enough bytes available. If presented with a length > 4,
             *          this function returns false. The Unicode definition of UTF-8 goes up to 4-byte
             *          sequences.
             *          
             *          Adapted from ftp://ftp.unicode.org/Public/PROGRAMS/CVTUTF/ConvertUTF.c Copyright 2001-
             *          2004 Unicode, Inc.
             *
             * @param   bytes   The bytes.
             * @param   length  The length.
             *
             * @return  true if legal, false if not.
             */

            static bool IsLegal(const unsigned char *bytes, int length);

        private:
            static const char* names_[];
            static const CharacterMap charMap_;
        };
    }
}

#endif /* TECHNOSOFTWARE_UTF8ENCODING_H */
