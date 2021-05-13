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

#include "Base/MemoryStream.h"

namespace Technosoftware
{
    namespace Base
    {
        MemoryIOS::MemoryIOS(char* pBuffer, std::streamsize bufferSize) :
            streamBuffer_(pBuffer, bufferSize)
        {
            technosoftware_ios_init(&streamBuffer_);
        }

        MemoryIOS::~MemoryIOS()
        {
        }

        MemoryInputStream::MemoryInputStream(const char* pBuffer, std::streamsize bufferSize) :
            MemoryIOS(const_cast<char*>(pBuffer), bufferSize),
            std::istream(&streamBuffer_)
        {
        }

        MemoryInputStream::~MemoryInputStream()
        {
        }

        MemoryOutputStream::MemoryOutputStream(char* pBuffer, std::streamsize bufferSize) :
            MemoryIOS(pBuffer, bufferSize),
            std::ostream(&streamBuffer_)
        {
        }

        MemoryOutputStream::~MemoryOutputStream()
        {
        }
    }
}