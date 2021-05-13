/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the DateTimeFormat class.
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

#ifndef TECHNOSOFTWARE_DATETIMEFORMAT_H
#define TECHNOSOFTWARE_DATETIMEFORMAT_H

#include "Base/Base.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class    DateTimeFormat
         *
         * @brief    Definition of date/time formats and various constants used by DateTimeFormatter and
         *             DateTimeParser.
         *
         * @ingroup    BaseDateTime
         */

        class TECHNOSOFTWARE_API DateTimeFormat
            /// 
        {
        public:

            /**
             * @brief    The date/time format defined in the ISO 8601 standard.
             *             
             *             Examples:
             *               2005-01-01T12:00:00+01:00, 2005-01-01T11:00:00Z.
             */

            static const std::string ISO8601_FORMAT;

            /**
             * @brief    The date/time format defined in the ISO 8601 standard, with fractional seconds.
             *             
             *             Examples:
             *               2005-01-01T12:00:00.000000+01:00, 2005-01-01T11:00:00.000000Z.
             */
            
            static const std::string ISO8601_FRAC_FORMAT;

            /**
             * @brief    The date/time format defined in RFC 822 (obsoleted by RFC 1123).
             *             
             *             Examples:
             *               Sat, 1 Jan 05 12:00:00 +0100, Sat, 1 Jan 05 11:00:00 GMT.
             */

            static const std::string RFC822_FORMAT;

            /**
             * @brief    The date/time format defined in RFC 1123 (obsoletes RFC 822).
             *             
             *             Examples:
             *              Sat, 1 Jan 2005 12:00:00 +0100 Sat, 1 Jan 2005 11:00:00 GMT.
             */

            static const std::string RFC1123_FORMAT;

            /**
             * @brief    The date/time format defined in the HTTP specification (RFC 2616), which is basically
             *             a variant of RFC 1036 with a zero-padded day field.
             *             
             *             Examples:
             *               Sat, 01 Jan 2005 12:00:00 +0100 Sat, 01 Jan 2005 11:00:00 GMT.
             */

            static const std::string HTTP_FORMAT;

            /**
             * @brief    The date/time format defined in RFC 850 (obsoleted by RFC 1036).
             *             
             *             Examples:
             *               Saturday, 1-Jan-05 12:00:00 +0100 Saturday, 1-Jan-05 11:00:00 GMT.
             */

            static const std::string RFC850_FORMAT;

            /**
             * @brief    The date/time format defined in RFC 1036 (obsoletes RFC 850).
             *             
             *             Examples:
             *               Saturday, 1 Jan 05 12:00:00 +0100 Saturday, 1 Jan 05 11:00:00 GMT.
             */

            static const std::string RFC1036_FORMAT;

            /**
             * @brief    The date/time format produced by the ANSI C asctime() function.
             *             
             *             Example:
             *               Sat Jan  1 12:00:00 2005.
             */

            static const std::string ASCTIME_FORMAT;

            /**
             * @brief    A simple, sortable date/time format.
             *             
             *             Example:
             *               2005-01-01 12:00:00.
             */

            static const std::string SORTABLE_FORMAT;


            /** @brief    English names of week days (Sunday, Monday, Tuesday, ...). */
            static const std::string WEEKDAY_NAMES[7];

            /** @brief    English names of months (January, February, ...). */
            static const std::string MONTH_NAMES[12];
        };
    }
}

#endif /* TECHNOSOFTWARE_DATETIMEFORMAT_H */
