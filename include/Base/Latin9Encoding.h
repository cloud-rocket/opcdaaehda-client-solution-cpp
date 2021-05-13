/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Latin9Encoding class.
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

#ifndef TECHNOSOFTWARE_LATIN9ENCODING_H
#define TECHNOSOFTWARE_LATIN9ENCODING_H

#include "Base/Base.h"
#include "Base/TextEncoding.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class    Latin9Encoding
         *
         * @brief    ISO Latin-9 (8859-15) text encoding.
         *             
         *           Latin-9 is basically Latin-1 with the EURO sign plus some other minor changes.
         *
         * @ingroup BaseText
         */

        class TECHNOSOFTWARE_API Latin9Encoding : public TextEncoding
        {
        public:
            Latin9Encoding();
            ~Latin9Encoding();
            const char* GetCanonicalName() const;
            bool IsA(const std::string& encodingName) const;
            const CharacterMap& GetCharacterMap() const;
            int Convert(const unsigned char* bytes) const;
            int Convert(int ch, unsigned char* bytes, int length) const;
            int QueryConvert(const unsigned char* bytes, int length) const;
            int GetSequenceLength(const unsigned char* bytes, int length) const;

        private:
            static const char* names_[];
            static const CharacterMap charMap_;
        };
    }
}

#endif /* TECHNOSOFTWARE_LATIN9ENCODING_H */
