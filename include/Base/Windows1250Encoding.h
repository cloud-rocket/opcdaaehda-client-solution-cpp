/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Windows1250Encoding class.
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

#ifndef TECHNOSOFTWARE_WINDOWS1250ENCODING_H
#define TECHNOSOFTWARE_WINDOWS1250ENCODING_H

#include "Base/Base.h"
#include "Base/TextEncoding.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class    Windows1250Encoding
         *
         * @brief    Windows Codepage 1250 text encoding. Based on: http://msdn.microsoft.com/en-
         *             us/goglobal/cc305143.
         *
         * @ingroup BaseText
         */

        class TECHNOSOFTWARE_API Windows1250Encoding : public TextEncoding
        {
        public:
            Windows1250Encoding();
            ~Windows1250Encoding();
            const char* GetCanonicalName() const override;
            bool IsA(const std::string& encodingName) const override;
            const CharacterMap& GetCharacterMap() const override;
            int Convert(const unsigned char* bytes) const override;
            int Convert(int ch, unsigned char* bytes, int length) const override;
            int QueryConvert(const unsigned char* bytes, int length) const override;
            int GetSequenceLength(const unsigned char* bytes, int length) const override;

        private:
            static const char* names_[];
            static const CharacterMap charMap_;
        };
    }
}

#endif /* TECHNOSOFTWARE_WINDOWS1250ENCODING_H */
