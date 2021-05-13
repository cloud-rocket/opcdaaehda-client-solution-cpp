/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * String utility functions.
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

#include "Base/String.h"

namespace Technosoftware
{
    namespace Base
    {
#if defined(TECHNOSOFTWARE_NO_TEMPLATE_ICOMPARE)
        int CaseInsensitiveCompare(const std::string& str, std::string::size_type pos, std::string::size_type n, std::string::const_iterator it2, std::string::const_iterator end2)
        {
            std::string::size_type sz = str.size();
            if (pos > sz) pos = sz;
            if (pos + n > sz) n = sz - pos;
            std::string::const_iterator it1 = str.begin() + pos;
            std::string::const_iterator end1 = str.begin() + pos + n;
            while (it1 != end1 && it2 != end2)
            {
                std::string::value_type c1 = Ascii::ToLower(*it1);
                std::string::value_type c2 = Ascii::ToLower(*it2);
                if (c1 < c2)
                    return -1;
                else if (c1 > c2)
                    return 1;
                ++it1; ++it2;
            }

            if (it1 == end1)
                return it2 == end2 ? 0 : -1;
            else
                return 1;
        }


        int CaseInsensitiveCompare(const std::string& str1, const std::string& str2)
        {
            return CaseInsensitiveCompare(str1, 0, str1.size(), str2.begin(), str2.end());
        }


        int CaseInsensitiveCompare(const std::string& str1, std::string::size_type n1, const std::string& str2, std::string::size_type n2)
        {
            if (n2 > str2.size()) n2 = str2.size();
            return CaseInsensitiveCompare(str1, 0, n1, str2.begin(), str2.begin() + n2);
        }


        int CaseInsensitiveCompare(const std::string& str1, std::string::size_type n, const std::string& str2)
        {
            if (n > str2.size()) n = str2.size();
            return CaseInsensitiveCompare(str1, 0, n, str2.begin(), str2.begin() + n);
        }


        int CaseInsensitiveCompare(const std::string& str1, std::string::size_type pos, std::string::size_type n, const std::string& str2)
        {
            return CaseInsensitiveCompare(str1, pos, n, str2.begin(), str2.end());
        }


        int CaseInsensitiveCompare(const std::string& str1, std::string::size_type pos1, std::string::size_type n1, const std::string& str2, std::string::size_type pos2, std::string::size_type n2)
        {
            std::string::size_type sz2 = str2.size();
            if (pos2 > sz2) pos2 = sz2;
            if (pos2 + n2 > sz2) n2 = sz2 - pos2;
            return CaseInsensitiveCompare(str1, pos1, n1, str2.begin() + pos2, str2.begin() + pos2 + n2);
        }


        int CaseInsensitiveCompare(const std::string& str1, std::string::size_type pos1, std::string::size_type n, const std::string& str2, std::string::size_type pos2)
        {
            std::string::size_type sz2 = str2.size();
            if (pos2 > sz2) pos2 = sz2;
            if (pos2 + n > sz2) n = sz2 - pos2;
            return CaseInsensitiveCompare(str1, pos1, n, str2.begin() + pos2, str2.begin() + pos2 + n);
        }


        int CaseInsensitiveCompare(const std::string& str, std::string::size_type pos, std::string::size_type n, const std::string::value_type* ptr)
        {
            technosoftware_check_ptr(ptr);
            std::string::size_type sz = str.size();
            if (pos > sz) pos = sz;
            if (pos + n > sz) n = sz - pos;
            std::string::const_iterator it = str.begin() + pos;
            std::string::const_iterator end = str.begin() + pos + n;
            while (it != end && *ptr)
            {
                std::string::value_type c1 = Ascii::ToLower(*it);
                std::string::value_type c2 = Ascii::ToLower(*ptr);
                if (c1 < c2)
                    return -1;
                else if (c1 > c2)
                    return 1;
                ++it; ++ptr;
            }

            if (it == end)
                return *ptr == 0 ? 0 : -1;
            else
                return 1;
        }


        int CaseInsensitiveCompare(const std::string& str, std::string::size_type pos, const std::string::value_type* ptr)
        {
            return CaseInsensitiveCompare(str, pos, str.size() - pos, ptr);
        }


        int CaseInsensitiveCompare(const std::string& str, const std::string::value_type* ptr)
        {
            return CaseInsensitiveCompare(str, 0, str.size(), ptr);
        }


        std::string Replace(const std::string& str, const std::string& from, const std::string& to, std::string::size_type start)
        {
            std::string result(str);
            ReplaceInPlace(result, from, to, start);
            return result;
        }


        std::string replace(const std::string& str, const std::string::value_type* from, const std::string::value_type* to, std::string::size_type start)
        {
            std::string result(str);
            ReplaceInPlace(result, from, to, start);
            return result;
        }


        std::string replace(const std::string& str, const std::string::value_type from, const std::string::value_type to, std::string::size_type start)
        {
            std::string result(str);
            ReplaceInPlace(result, from, to, start);
            return result;
        }


        std::string remove(const std::string& str, const std::string::value_type ch, std::string::size_type start)
        {
            std::string result(str);
            ReplaceInPlace(result, ch, 0, start);
            return result;
        }


        std::string& replaceInPlace(std::string& str, const std::string& from, const std::string& to, std::string::size_type start)
        {
            technosoftware_assert(from.size() > 0);

            std::string result;
            std::string::size_type pos = 0;
            result.append(str, 0, start);
            do
            {
                pos = str.find(from, start);
                if (pos != std::string::npos)
                {
                    result.append(str, start, pos - start);
                    result.append(to);
                    start = pos + from.length();
                }
                else result.append(str, start, str.size() - start);
            } while (pos != std::string::npos);
            str.swap(result);
            return str;
        }


        std::string& replaceInPlace(std::string& str, const std::string::value_type* from, const std::string::value_type* to, std::string::size_type start)
        {
            technosoftware_assert(*from);

            std::string result;
            std::string::size_type pos = 0;
            std::string::size_type fromLen = std::strlen(from);
            result.append(str, 0, start);
            do
            {
                pos = str.find(from, start);
                if (pos != std::string::npos)
                {
                    result.append(str, start, pos - start);
                    result.append(to);
                    start = pos + fromLen;
                }
                else result.append(str, start, str.size() - start);
            } while (pos != std::string::npos);
            str.swap(result);
            return str;
        }


        std::string& replaceInPlace(std::string& str, const std::string::value_type from, const std::string::value_type to, std::string::size_type start)
        {
            if (from == to) return str;

            std::string::size_type pos = 0;
            do
            {
                pos = str.find(from, start);
                if (pos != std::string::npos)
                {
                    if (to) str[pos] = to;
                    else str.erase(pos, 1);
                }
            } while (pos != std::string::npos);

            return str;
        }


        std::string& removeInPlace(std::string& str, const std::string::value_type ch, std::string::size_type start)
        {
            return replaceInPlace(str, ch, 0, start);
        }


#endif

    }
}
