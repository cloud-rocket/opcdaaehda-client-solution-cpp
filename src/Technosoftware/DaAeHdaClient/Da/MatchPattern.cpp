/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://www.technosoftware.com
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

#include <windows.h>
#include "matchpattern.h"



inline int ConvertCase( int c, BOOL bCaseSensitive )
{
    return bCaseSensitive ? c : toupper(c);
}



//*************************************************************************          
// return TRUE if String Matches Pattern -- 
// -- uses Visual Basic LIKE operator syntax
// CAUTION: Function is recursive
//*************************************************************************          

/**
 * @fn    BOOL MatchPattern( const MCHAR *String, const MCHAR *Pattern, BOOL bCaseSensitive )
 *
 * @brief    Match pattern.
 *
 * @param    String              The string.
 * @param    Pattern              Specifies the pattern.
 * @param    bCaseSensitive    true to case sensitive.
 *
 * @return    true if it succeeds, false if it fails.
 */

BOOL MatchPattern( const MCHAR *String, const MCHAR *Pattern, BOOL bCaseSensitive )
{ 
    if( !String )
        return FALSE;
    if( !Pattern )
        return TRUE;
    MCHAR   c, p, l;
    for (; ;)
    {
        switch (p = ConvertCase( *Pattern++, bCaseSensitive ) )
        {
        case 0:                             // end of pattern
            return *String ? FALSE : TRUE;  // if end of string TRUE

        case _M('*'):
            while (*String) 
            {               // match zero or more char
                if (MatchPattern (String++, Pattern, bCaseSensitive))
                    return TRUE; 
            }
            return MatchPattern (String, Pattern, bCaseSensitive );

        case _M('?'):
            if (*String++ == 0)             // match any one char 
                return FALSE;                   // not end of string 
            break; 

        case _M('['): 
            if ( (c = ConvertCase( *String++, bCaseSensitive) ) == 0)      // match char set 
                return FALSE;                   // syntax 
            l = 0; 
            if( *Pattern == _M('!') )  // match a char if NOT in set []
            {
                ++Pattern;

                while( (p = ConvertCase( *Pattern++, bCaseSensitive) ) != _M('\0') ) 
                {
                    if (p == _M(']'))               // if end of char set, then 
                        break;           // no match found 

                    if (p == _M('-')) 
                    {            // check a range of chars? 
                        p = ConvertCase( *Pattern, bCaseSensitive );   // get high limit of range 
                        if (p == 0  ||  p == _M(']')) 
                            return FALSE;           // syntax 

                        if (c >= l  &&  c <= p) 
                            return FALSE;              // if in range, return FALSE 
                    } 
                    l = p;
                    if (c == p)                 // if char matches this element 
                        return FALSE;                  // return false 
                } 
            }
            else    // match if char is in set []
            {
                while( (p = ConvertCase( *Pattern++, bCaseSensitive) ) != _M('\0') ) 
                {
                    if (p == _M(']'))               // if end of char set, then 
                        return FALSE;           // no match found 

                    if (p == _M('-')) 
                    {            // check a range of chars? 
                        p = ConvertCase( *Pattern, bCaseSensitive );   // get high limit of range 
                        if (p == 0  ||  p == _M(']')) 
                            return FALSE;           // syntax 

                        if (c >= l  &&  c <= p) 
                            break;              // if in range, move on 
                    } 
                    l = p;
                    if (c == p)                 // if char matches this element 
                        break;                  // move on 
                } 

                while (p  &&  p != _M(']'))         // got a match in char set 
                    p = *Pattern++;             // skip to end of set 
            }

            break; 

        case _M('#'):
            c = *String++; 
            if( !_ismdigit( c ) )
                return FALSE;        // not a digit

            break;

        default: 
            c = ConvertCase( *String++, bCaseSensitive ); 
            if( c != p )            // check for exact char 
                return FALSE;                   // not a match 

            break; 
        } 
    } 
} 
