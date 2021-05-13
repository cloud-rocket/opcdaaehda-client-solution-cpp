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

#include "Base/TextConverter.h"
#include "Base/TextIterator.h"
#include "Base/TextEncoding.h"


namespace {
    int nullTransform(int ch)
    {
        return ch;
    }
}


namespace Technosoftware
{
    namespace Base
    {


TextConverter::TextConverter(const TextEncoding& inEncoding, const TextEncoding& outEncoding, int defaultChar):
    inEncoding_(inEncoding),
    outEncoding_(outEncoding),
    defaultChar_(defaultChar)
{
}


TextConverter::~TextConverter()
{
}


int TextConverter::Convert(const std::string& source, std::string& destination, Transform trans)
{
    int errors = 0;
    TextIterator it(source, inEncoding_);
    TextIterator end(source);
    unsigned char buffer[TextEncoding::MAX_SEQUENCE_LENGTH];

    while (it != end)
    {
        int c = *it;
        if (c == -1) { ++errors; c = defaultChar_; }
        c = trans(c);
        int n = outEncoding_.Convert(c, buffer, sizeof(buffer));
        if (n == 0) n = outEncoding_.Convert(defaultChar_, buffer, sizeof(buffer));
        technosoftware_assert (n <= sizeof(buffer));
        destination.append((const char*) buffer, n);
        ++it;
    }
    return errors;
}


int TextConverter::Convert(const void* source, int length, std::string& destination, Transform trans)
{
    technosoftware_check_ptr (source);

    int errors = 0;
    const unsigned char* it  = (const unsigned char*) source;
    const unsigned char* end = (const unsigned char*) source + length;
    unsigned char buffer[TextEncoding::MAX_SEQUENCE_LENGTH];
    
    while (it < end)
    {
        int n = inEncoding_.QueryConvert(it, 1);
        int uc;
        int read = 1;

        while (-1 > n && (end - it) >= -n)
        {
            read = -n;
            n = inEncoding_.QueryConvert(it, read);
        }

        if (-1 > n)
        {
            it = end;
        }
        else
        {
            it += read;
        }

        if (-1 >= n)
        {
            uc = defaultChar_;
            ++errors;
        }
        else
        {
            uc = n;
        }

        uc = trans(uc);
        n = outEncoding_.Convert(uc, buffer, sizeof(buffer));
        if (n == 0) n = outEncoding_.Convert(defaultChar_, buffer, sizeof(buffer));
        technosoftware_assert (n <= sizeof(buffer));
        destination.append((const char*) buffer, n);
    }
    return errors;
}


int TextConverter::Convert(const std::string& source, std::string& destination)
{
    return Convert(source, destination, nullTransform);
}


int TextConverter::Convert(const void* source, int length, std::string& destination)
{
    return Convert(source, length, destination, nullTransform);
}

    }
} 
