/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Hash class.
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

#ifndef TECHNOSOFTWARE_HASH_H
#define TECHNOSOFTWARE_HASH_H

#include <cstddef>

#include "Base/Base.h"
#include "Base/Handles.h"

namespace Technosoftware
{
    namespace Base
    {

        std::size_t TECHNOSOFTWARE_API hash(const std::string& str);
        std::size_t TECHNOSOFTWARE_API hash(ServerHandle n);

        template <class T>

        /**
         * @struct  Hash
         *
         * @brief   A generic hash function.
         *
         * @ingroup Hashing
         */

        struct Hash
        {
            /**
             * @fn  std::size_t operator() (T value) const
             *
             * @brief   Returns the hash for the given value.
             *
             * @return  The result of the operation.
             */

            std::size_t operator () (T value) const
            {
                return Base::hash(value);
            }
        };


        //
        // inlines
        //
        inline std::size_t hash(ServerHandle n)
        {
            return static_cast<std::size_t>(n) * 2654435761U;
        }
    }
}

#endif /* TECHNOSOFTWARE_HASH_H */
