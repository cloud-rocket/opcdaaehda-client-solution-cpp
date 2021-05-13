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

#ifndef Foundation_String_INCLUDED
#define Foundation_String_INCLUDED


#include "Base/Base.h"
#include "Base/Ascii.h"
#include <cstring>
#include <algorithm>


namespace Technosoftware
{
    namespace Base
    {
        /**
         * @fn  S TrimLeft(const S& str)
         *
         * @brief   Returns a copy of str with all leading whitespace removed.
         *
         * @param   str The string.
         *
         * @return  A string.
         *
         * @ingroup BaseCore
         */

        template <class S>
        S TrimLeft(const S& str)
        {
            typename S::const_iterator it = str.begin();
            typename S::const_iterator end = str.end();

            while (it != end && Ascii::IsSpace(*it)) ++it;
            return S(it, end);
        }

        /**
         * @fn  S& TrimLeftInPlace(S& str)
         *
         * @brief   Removes all leading whitespace in str.
         *
         * @param [in,out]  str The string.
         *
         * @return  A reference to a string.
         *
         * @ingroup BaseCore
         */

        template <class S>
        S& TrimLeftInPlace(S& str)
        {
            typename S::iterator it = str.begin();
            typename S::iterator end = str.end();

            while (it != end && Ascii::IsSpace(*it)) ++it;
            str.erase(str.begin(), it);
            return str;
        }

        /**
         * @fn  S TrimRight(const S& str)
         *
         * @brief   Returns a copy of str with all trailing whitespace removed.
         *
         * @param   str The string.
         *
         * @return  A string.
         *
         * @ingroup BaseCore
         */

        template <class S>
        S TrimRight(const S& str)
        {
            int pos = int(str.size()) - 1;

            while (pos >= 0 && Ascii::IsSpace(str[pos])) --pos;
            return S(str, 0, pos + 1);
        }

        /**
         * @fn  S& TrimRightInPlace(S& str)
         *
         * @brief   Removes all trailing whitespace in str.
         *
         * @param [in,out]  str The string.
         *
         * @return  A reference to a string.
         *
         * @ingroup BaseCore
         */

        template <class S>
        S& TrimRightInPlace(S& str)
        {
            int pos = int(str.size()) - 1;

            while (pos >= 0 && Ascii::IsSpace(str[pos])) --pos;
            str.resize(pos + 1);

            return str;
        }

        /**
         * @fn  S Trim(const S& str)
         *
         * @brief   Returns a copy of str with all leading and trailing whitespace removed.
         *
         * @param   str The string.
         *
         * @return  A string.
         *
         * @ingroup BaseCore
         */

        template <class S>
        S Trim(const S& str)
        {
            int first = 0;
            int last = int(str.size()) - 1;

            while (first <= last && Ascii::IsSpace(str[first])) ++first;
            while (last >= first && Ascii::IsSpace(str[last])) --last;

            return S(str, first, last - first + 1);
        }

        /**
         * @fn  S& TrimInPlace(S& str)
         *
         * @brief   Removes all leading and trailing whitespace in str.
         *
         * @param [in,out]  str The string.
         *
         * @return  A reference to a string.
         *
         * @ingroup BaseCore
         */

        template <class S>
        S& TrimInPlace(S& str)
        {
            int first = 0;
            int last = int(str.size()) - 1;

            while (first <= last && Ascii::IsSpace(str[first])) ++first;
            while (last >= first && Ascii::IsSpace(str[last])) --last;

            str.resize(last + 1);
            str.erase(0, first);

            return str;
        }

        /**
         * @fn  S ToUpper(const S& str)
         *
         * @brief   Returns a copy of str containing all upper-case characters.
         *
         * @param   str The string.
         *
         * @return  str as a string.
         *
         * @ingroup BaseCore
         */

        template <class S>
        S ToUpper(const S& str)
        {
            typename S::const_iterator it = str.begin();
            typename S::const_iterator end = str.end();

            S result;
            result.reserve(str.size());
            while (it != end) result += static_cast<typename S::value_type>(Ascii::toUpper(*it++));
            return result;
        }

        /**
         * @fn  S& ToUpperInPlace(S& str)
         *
         * @brief   Replaces all characters in str with their upper-case counterparts.
         *
         * @param [in,out]  str The string.
         *
         * @return  A reference to a string.
         *
         * @ingroup BaseCore
         */

        template <class S>
        S& ToUpperInPlace(S& str)
        {
            typename S::iterator it = str.begin();
            typename S::iterator end = str.end();

            while (it != end) { *it = static_cast<typename S::value_type>(Ascii::toUpper(*it)); ++it; }
            return str;
        }


        template <class S>

        /**
         * @fn  S ToLower(const S& str)
         *
         * @brief   Returns a copy of str containing all lower-case characters.
         *
         * @param   str The string.
         *
         * @return  str as a string.
         *
         * @ingroup BaseCore
         */

        S ToLower(const S& str)
        {
            typename S::const_iterator it = str.begin();
            typename S::const_iterator end = str.end();

            S result;
            result.reserve(str.size());
            while (it != end) result += static_cast<typename S::value_type>(Ascii::ToLower(*it++));
            return result;
        }


        template <class S>

        /**
         * @fn  S& ToLowerInPlace(S& str)
         *
         * @brief   Replaces all characters in str with their lower-case counterparts.
         *
         * @param [in,out]  str The string.
         *
         * @return  A reference to a string.
         *
         * @ingroup BaseCore
         */

        S& ToLowerInPlace(S& str)
        {
            typename S::iterator it = str.begin();
            typename S::iterator end = str.end();

            while (it != end) { *it = static_cast<typename S::value_type>(Ascii::ToLower(*it)); ++it; }
            return str;
        }


#if !defined(TECHNOSOFTWARE_NO_TEMPLATE_ICOMPARE)
        /**
         * @fn  int CaseInsensitiveCompare( const S& str, typename S::size_type pos, typename S::size_type n, It it2, It end2)
         *
         * @brief   Case-insensitive string comparison.
         *
         * @param   str     The string.
         * @param   pos     The position.
         * @param   n       The S::size_type to process.
         * @param   it2     The second iterator.
         * @param   end2    The end 2.
         *
         * @return  An int.
         *
         * @ingroup BaseCore
         */

        template <class S, class It>
        int CaseInsensitiveCompare(
            const S& str,
            typename S::size_type pos,
            typename S::size_type n,
            It it2,
            It end2)
        {
            typename S::size_type sz = str.size();
            if (pos > sz) pos = sz;
            if (pos + n > sz) n = sz - pos;
            It it1 = str.begin() + pos;
            It end1 = str.begin() + pos + n;
            while (it1 != end1 && it2 != end2)
            {
                typename S::value_type c1(static_cast<typename S::value_type>(Ascii::ToLower(*it1)));
                typename S::value_type c2(static_cast<typename S::value_type>(Ascii::ToLower(*it2)));
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

        /**
         * @fn  int CaseInsensitiveCompare(const S& str1, const S& str2)
         *
         * @brief   A special optimization for an often used case.
         *
         * @param   str1    The first string.
         * @param   str2    The second string.
         *
         * @return  An int.
         *
         * @ingroup BaseCore
         */

        template <class S>
        int CaseInsensitiveCompare(const S& str1, const S& str2)
        {
            typename S::const_iterator it1(str1.begin());
            typename S::const_iterator end1(str1.end());
            typename S::const_iterator it2(str2.begin());
            typename S::const_iterator end2(str2.end());
            while (it1 != end1 && it2 != end2)
            {
                typename S::value_type c1(static_cast<typename S::value_type>(Ascii::ToLower(*it1)));
                typename S::value_type c2(static_cast<typename S::value_type>(Ascii::ToLower(*it2)));
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


        template <class S>
        int CaseInsensitiveCompare(const S& str1, typename S::size_type n1, const S& str2, typename S::size_type n2)
        {
            if (n2 > str2.size()) n2 = str2.size();
            return CaseInsensitiveCompare(str1, 0, n1, str2.begin(), str2.begin() + n2);
        }


        template <class S>
        int CaseInsensitiveCompare(const S& str1, typename S::size_type n, const S& str2)
        {
            if (n > str2.size()) n = str2.size();
            return CaseInsensitiveCompare(str1, 0, n, str2.begin(), str2.begin() + n);
        }


        template <class S>
        int CaseInsensitiveCompare(const S& str1, typename S::size_type pos, typename S::size_type n, const S& str2)
        {
            return CaseInsensitiveCompare(str1, pos, n, str2.begin(), str2.end());
        }


        template <class S>
        int CaseInsensitiveCompare(
            const S& str1,
            typename S::size_type pos1,
            typename S::size_type n1,
            const S& str2,
            typename S::size_type pos2,
            typename S::size_type n2)
        {
            typename S::size_type sz2 = str2.size();
            if (pos2 > sz2) pos2 = sz2;
            if (pos2 + n2 > sz2) n2 = sz2 - pos2;
            return CaseInsensitiveCompare(str1, pos1, n1, str2.begin() + pos2, str2.begin() + pos2 + n2);
        }


        template <class S>
        int CaseInsensitiveCompare(
            const S& str1,
            typename S::size_type pos1,
            typename S::size_type n,
            const S& str2,
            typename S::size_type pos2)
        {
            typename S::size_type sz2 = str2.size();
            if (pos2 > sz2) pos2 = sz2;
            if (pos2 + n > sz2) n = sz2 - pos2;
            return CaseInsensitiveCompare(str1, pos1, n, str2.begin() + pos2, str2.begin() + pos2 + n);
        }


        template <class S>
        int CaseInsensitiveCompare(
            const S& str,
            typename S::size_type pos,
            typename S::size_type n,
            const typename S::value_type* ptr)
        {
            technosoftware_check_ptr(ptr);
            typename S::size_type sz = str.size();
            if (pos > sz) pos = sz;
            if (pos + n > sz) n = sz - pos;
            typename S::const_iterator it = str.begin() + pos;
            typename S::const_iterator end = str.begin() + pos + n;
            while (it != end && *ptr)
            {
                typename S::value_type c1(static_cast<typename S::value_type>(Ascii::ToLower(*it)));
                typename S::value_type c2(static_cast<typename S::value_type>(Ascii::ToLower(*ptr)));
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


        template <class S>
        int CaseInsensitiveCompare(
            const S& str,
            typename S::size_type pos,
            const typename S::value_type* ptr)
        {
            return CaseInsensitiveCompare(str, pos, str.size() - pos, ptr);
        }


        template <class S>
        int CaseInsensitiveCompare(
            const S& str,
            const typename S::value_type* ptr)
        {
            return CaseInsensitiveCompare(str, 0, str.size(), ptr);
        }


#else


        int TECHNOSOFTWARE_API CaseInsensitiveCompare(const std::string& str, std::string::size_type pos, std::string::size_type n, std::string::const_iterator it2, std::string::const_iterator end2);
        int TECHNOSOFTWARE_API CaseInsensitiveCompare(const std::string& str1, const std::string& str2);
        int TECHNOSOFTWARE_API CaseInsensitiveCompare(const std::string& str1, std::string::size_type n1, const std::string& str2, std::string::size_type n2);
        int TECHNOSOFTWARE_API CaseInsensitiveCompare(const std::string& str1, std::string::size_type n, const std::string& str2);
        int TECHNOSOFTWARE_API CaseInsensitiveCompare(const std::string& str1, std::string::size_type pos, std::string::size_type n, const std::string& str2);
        int TECHNOSOFTWARE_API CaseInsensitiveCompare(const std::string& str1, std::string::size_type pos1, std::string::size_type n1, const std::string& str2, std::string::size_type pos2, std::string::size_type n2);
        int TECHNOSOFTWARE_API CaseInsensitiveCompare(const std::string& str1, std::string::size_type pos1, std::string::size_type n, const std::string& str2, std::string::size_type pos2);
        int TECHNOSOFTWARE_API CaseInsensitiveCompare(const std::string& str, std::string::size_type pos, std::string::size_type n, const std::string::value_type* ptr);
        int TECHNOSOFTWARE_API CaseInsensitiveCompare(const std::string& str, std::string::size_type pos, const std::string::value_type* ptr);
        int TECHNOSOFTWARE_API CaseInsensitiveCompare(const std::string& str, const std::string::value_type* ptr);


#endif


        template <class S>

        /**
         * @fn  S Translate(const S& str, const S& from, const S& to)
         *
         * @brief   Returns a copy of str with all characters in from replaced by the corresponding (by
         *          position)
         *          characters in to. If there is no corresponding character in to, the character is
         *          removed from the copy.
         *
         * @param   str     The string.
         * @param   from    Source for the.
         * @param   to      to.
         *
         * @return  A string.
         *
         * @ingroup BaseCore
         */

        S Translate(const S& str, const S& from, const S& to)
        {
            S result;
            result.reserve(str.size());
            typename S::const_iterator it = str.begin();
            typename S::const_iterator end = str.end();
            typename S::size_type toSize = to.size();
            while (it != end)
            {
                typename S::size_type pos = from.find(*it);
                if (pos == S::npos)
                {
                    result += *it;
                }
                else
                {
                    if (pos < toSize) result += to[pos];
                }
                ++it;
            }
            return result;
        }


        template <class S>
        S Translate(const S& str, const typename S::value_type* from, const typename S::value_type* to)
        {
            technosoftware_check_ptr(from);
            technosoftware_check_ptr(to);
            return translate(str, S(from), S(to));
        }


        template <class S>

        /**
         * @fn  S& TranslateInPlace(S& str, const S& from, const S& to)
         *
         * @brief   Replaces in str all occurences of characters in from with the corresponding (by
         *          position) characters in to. If there is no corresponding character, the character is
         *          removed.
         *
         * @param [in,out]  str The string.
         * @param   from        Source for the.
         * @param   to          to.
         *
         * @return  A reference to a string.
         *
         * @ingroup BaseCore
         */

        S& TranslateInPlace(S& str, const S& from, const S& to)
        {
            str = translate(str, from, to);
            return str;
        }


        template <class S>
        S TranslateInPlace(S& str, const typename S::value_type* from, const typename S::value_type* to)
        {
            technosoftware_check_ptr(from);
            technosoftware_check_ptr(to);
            str = translate(str, S(from), S(to));
            return str;
        }


#if !defined(TECHNOSOFTWARE_NO_TEMPLATE_ICOMPARE)


        template <class S>
        S& ReplaceInPlace(S& str, const S& from, const S& to, typename S::size_type start = 0)
        {
            technosoftware_assert(from.size() > 0);

            S result;
            typename S::size_type pos = 0;
            result.append(str, 0, start);
            do
            {
                pos = str.find(from, start);
                if (pos != S::npos)
                {
                    result.append(str, start, pos - start);
                    result.append(to);
                    start = pos + from.length();
                }
                else result.append(str, start, str.size() - start);
            } while (pos != S::npos);
            str.swap(result);
            return str;
        }


        template <class S>
        S& ReplaceInPlace(S& str, const typename S::value_type* from, const typename S::value_type* to, typename S::size_type start = 0)
        {
            technosoftware_assert(*from);

            S result;
            typename S::size_type pos = 0;
            typename S::size_type fromLen = std::strlen(from);
            result.append(str, 0, start);
            do
            {
                pos = str.find(from, start);
                if (pos != S::npos)
                {
                    result.append(str, start, pos - start);
                    result.append(to);
                    start = pos + fromLen;
                }
                else result.append(str, start, str.size() - start);
            } while (pos != S::npos);
            str.swap(result);
            return str;
        }


        template <class S>
        S& ReplaceInPlace(S& str, const typename S::value_type from, const typename S::value_type to = 0, typename S::size_type start = 0)
        {
            if (from == to) return str;

            typename S::size_type pos = 0;
            do
            {
                pos = str.find(from, start);
                if (pos != S::npos)
                {
                    if (to) str[pos] = to;
                    else str.erase(pos, 1);
                }
            } while (pos != S::npos);

            return str;
        }


        template <class S>
        S& RemoveInPlace(S& str, const typename S::value_type ch, typename S::size_type start = 0)
        {
            return ReplaceInPlace(str, ch, 0, start);
        }


        template <class S>

        /**
         * @fn  S Replace(const S& str, const S& from, const S& to, typename S::size_type start = 0)
         *
         * @brief   Replace all occurences of from (which must not be the empty string)
         *          in str with to, starting at position start.
         *
         * @param   str     The string.
         * @param   from    Source for the.
         * @param   to      to.
         * @param   start   (Optional) the start.
         *
         * @return  A string.
         *
         * @ingroup BaseCore
         */

        S Replace(const S& str, const S& from, const S& to, typename S::size_type start = 0)
        {
            S result(str);
            replaceInPlace(result, from, to, start);
            return result;
        }


        template <class S>
        S Replace(const S& str, const typename S::value_type* from, const typename S::value_type* to, typename S::size_type start = 0)
        {
            S result(str);
            replaceInPlace(result, from, to, start);
            return result;
        }


        template <class S>
        S Replace(const S& str, const typename S::value_type from, const typename S::value_type to = 0, typename S::size_type start = 0)
        {
            S result(str);
            replaceInPlace(result, from, to, start);
            return result;
        }


        template <class S>
        S Remove(const S& str, const typename S::value_type ch, typename S::size_type start = 0)
        {
            S result(str);
            replaceInPlace(result, ch, 0, start);
            return result;
        }


#else


        TECHNOSOFTWARE_API std::string Replace(const std::string& str, const std::string& from, const std::string& to, std::string::size_type start = 0);
        TECHNOSOFTWARE_API std::string Replace(const std::string& str, const std::string::value_type* from, const std::string::value_type* to, std::string::size_type start = 0);
        TECHNOSOFTWARE_API std::string Replace(const std::string& str, const std::string::value_type from, const std::string::value_type to = 0, std::string::size_type start = 0);
        TECHNOSOFTWARE_API std::string Remove(const std::string& str, const std::string::value_type ch, std::string::size_type start = 0);
        TECHNOSOFTWARE_API std::string& ReplaceInPlace(std::string& str, const std::string& from, const std::string& to, std::string::size_type start = 0);
        TECHNOSOFTWARE_API std::string& ReplaceInPlace(std::string& str, const std::string::value_type* from, const std::string::value_type* to, std::string::size_type start = 0);
        TECHNOSOFTWARE_API std::string& ReplaceInPlace(std::string& str, const std::string::value_type from, const std::string::value_type to = 0, std::string::size_type start = 0);
        TECHNOSOFTWARE_API std::string& RemoveInPlace(std::string& str, const std::string::value_type ch, std::string::size_type start = 0);


#endif    

        /**
         * @fn  S Cat(const S& s1, const S& s2)
         *
         * @brief   Concatenates two strings.
         *
         * @param   s1  The first S.
         * @param   s2  The second S.
         *
         * @return  A string.
         *
         * @ingroup BaseCore
         */

        template <class S>

        S Cat(const S& s1, const S& s2)
        {
            S result = s1;
            result.reserve(s1.size() + s2.size());
            result.append(s2);
            return result;
        }

        /**
         * @fn  S Cat(const S& s1, const S& s2, const S& s3)
         *
         * @brief   Concatenates three strings.
         *
         * @param   s1  The first S.
         * @param   s2  The second S.
         * @param   s3  The third S.
         *
         * @return  A string.
         *
         * @ingroup BaseCore
         */

        template <class S>
        S Cat(const S& s1, const S& s2, const S& s3)
        {
            S result = s1;
            result.reserve(s1.size() + s2.size() + s3.size());
            result.append(s2);
            result.append(s3);
            return result;
        }


        template <class S>

        /**
         * @fn  S Cat(const S& s1, const S& s2, const S& s3, const S& s4)
         *
         * @brief   Concatenates four strings.
         *
         * @param   s1  The first S.
         * @param   s2  The second S.
         * @param   s3  The third S.
         * @param   s4  The fourth S.
         *
         * @return  A string.
         *
         * @ingroup BaseCore
         */

        S Cat(const S& s1, const S& s2, const S& s3, const S& s4)
        {
            S result = s1;
            result.reserve(s1.size() + s2.size() + s3.size() + s4.size());
            result.append(s2);
            result.append(s3);
            result.append(s4);
            return result;
        }


        template <class S>

        /**
         * @fn  S Cat(const S& s1, const S& s2, const S& s3, const S& s4, const S& s5)
         *
         * @brief   Concatenates five strings.
         *
         * @param   s1  The first S.
         * @param   s2  The second S.
         * @param   s3  The third S.
         * @param   s4  The fourth S.
         * @param   s5  The fifth S.
         *
         * @return  A string.
         *
         * @ingroup BaseCore
         */

        S Cat(const S& s1, const S& s2, const S& s3, const S& s4, const S& s5)
        {
            S result = s1;
            result.reserve(s1.size() + s2.size() + s3.size() + s4.size() + s5.size());
            result.append(s2);
            result.append(s3);
            result.append(s4);
            result.append(s5);
            return result;
        }


        template <class S>

        /**
         * @fn  S Cat(const S& s1, const S& s2, const S& s3, const S& s4, const S& s5, const S& s6)
         *
         * @brief   Concatenates six strings.
         *
         * @param   s1  The first S.
         * @param   s2  The second S.
         * @param   s3  The third S.
         * @param   s4  The fourth S.
         * @param   s5  The fifth S.
         * @param   s6  The s 6.
         *
         * @return  A string.
         *
         * @ingroup BaseCore
         */

        S Cat(const S& s1, const S& s2, const S& s3, const S& s4, const S& s5, const S& s6)
        {
            S result = s1;
            result.reserve(s1.size() + s2.size() + s3.size() + s4.size() + s5.size() + s6.size());
            result.append(s2);
            result.append(s3);
            result.append(s4);
            result.append(s5);
            result.append(s6);
            return result;
        }


        template <class S, class It>

        /**
         * @fn  S Cat(const S& delim, const It& begin, const It& end)
         *
         * @brief   Concatenates a sequence of strings, delimited by the string given in delim.
         *
         * @param   delim   The delimiter.
         * @param   begin   The begin.
         * @param   end     The end.
         *
         * @return  A string.
         *
         * @ingroup BaseCore
         */

        S Cat(const S& delim, const It& begin, const It& end)
        {
            S result;
            for (It it = begin; it != end; ++it)
            {
                if (!result.empty()) result.append(delim);
                result += *it;
            }
            return result;
        }


        //
        // case-insensitive string equality
        //


        template <typename charT>
        struct i_char_traits : public std::char_traits<charT>
        {
            inline static bool eq(charT c1, charT c2)
            {
                return Ascii::ToLower(c1) == Ascii::ToLower(c2);
            }

            inline static bool ne(charT c1, charT c2)
            {
                return !eq(c1, c2);
            }

            inline static bool lt(charT c1, charT c2)
            {
                return Ascii::ToLower(c1) < Ascii::ToLower(c2);
            }

            static int Compare(const charT* s1, const charT* s2, size_t n)
            {
                for (int i = 0; i < n && s1 && s2; ++i, ++s1, ++s2)
                {
                    if (Ascii::ToLower(*s1) == Ascii::ToLower(*s2)) continue;
                    else if (Ascii::ToLower(*s1) < Ascii::ToLower(*s2)) return -1;
                    else return 1;
                }

                return 0;
            }

            static const charT* find(const charT* s, int n, charT a)
            {
                while (n-- > 0 && Ascii::ToLower(*s) != Ascii::ToLower(a)) { ++s; }
                return s;
            }
        };

        /**
         * @typedef std::basic_string<char, i_char_traits<char> > IString
         *
         * @brief   Case-insensitive std::string counterpart.
         *
         * @ingroup BaseCore
         */

        typedef std::basic_string<char, i_char_traits<char> > IString;


        template<typename T>

        /**
         * @fn  std::size_t CaseInsensitiveSubstr(const T& str, const T& sought)
         *
         * @brief   Case insensitive substr.
         *
         * @param   str     The string.
         * @param   sought  The sought.
         *
         * @return  A std::size_t.
         *
         * @ingroup BaseCore
         */

        std::size_t CaseInsensitiveSubstr(const T& str, const T& sought)
        {
            typename T::const_iterator it = std::search(str.begin(), str.end(),
                sought.begin(), sought.end(),
                i_char_traits<typename T::value_type>::eq);

            if (it != str.end()) return it - str.begin();
            else return static_cast<std::size_t>(T::npos);
        }

        /**
         * @struct  CILess
         *
         * @brief   Case-insensitive less-than functor; useful for standard maps and sets with
         *          std::strings keys and case-insensitive ordering requirement.
         *
         * @ingroup BaseCore
         */

        struct CILess
        {
            inline bool operator() (const std::string& s1, const std::string& s2) const
            {
                return CaseInsensitiveCompare(s1, s2) < 0;
            }
        };
    }
}

#endif /* TECHNOSOFTWARE_STRING_H */
