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

#ifndef TECHNOSOFTWARE_HDAITEM_H
#define TECHNOSOFTWARE_HDAITEM_H

#include "Base/Handles.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        /**
         * @struct  HdaItem
         *
         * @brief   Defines an alias representing the tag hda item.
         *
         * @ingroup  HDAClient
         */

        typedef struct HdaItem
        {
            /** @brief    Handle of the client. */
            Base::ClientHandle      ClientHandle;
            /** @brief    The aggregate. */
            DWORD                   Aggregate;
            /** @brief    Number of TimeStamps, Qualities and DataValues. */
            DWORD                   Count;
            /** @brief    The time stamps. */
            FILETIME*               TimeStamps;
            /** @brief    The qualities. */
            DWORD*                  Qualities;
            /** @brief    The data values. */
            VARIANT*                DataValues;
        } HdaItem;

    }
}

#endif /* TECHNOSOFTWARE_HDAITEM_H */
