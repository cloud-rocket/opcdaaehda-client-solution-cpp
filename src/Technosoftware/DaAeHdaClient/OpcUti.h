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

#ifndef TECHNOSOFTWARE_OPCUTI_H
#define TECHNOSOFTWARE_OPCUTI_H

#include "Base/Base.h"
#include "Base/Status.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        /**
         * @fn  const std::string QualityAsText(uint16_t quality);
         *
         * @brief   Quality as text
         *
         * @param   quality The quality.
         *
         * @return  A const std::string.
         */

        std::string QualityAsText(uint16_t quality);

        /**
         * @fn  std::string DataTypeAsText(VARTYPE value, OpcTextMode textMode = Capitalize);
         *
         * @brief   Data type as text
         *
         * @param   value       The value.
         * @param   textMode    (Optional) The text mode.
         *
         * @return  A std::string.
         */

        std::string DataTypeAsText(VARTYPE value, OpcTextMode textMode = OpcTextMode::Capitalize);

        /**
         * @fn  Base::Status GetStatusFromHResult(HRESULT result, Base::StatusCode::FuncCallType funcCallType = Base::Status::StatusCode::SysFuncCall, bool isResult = false);
         *
         * @brief   Gets status from hResult
         *
         * @param   result          The result.
         * @param   funcCallType    (Optional) Type of the function call.
         * @param   isResult        (Optional) True if is result, false if not.
         *
         * @return  The status from hResult.
         */

        Base::Status GetStatusFromHResult(HRESULT result, Base::StatusCode::FuncCallType funcCallType = Base::Status::StatusCode::SysFuncCall, bool isResult = false);
    }
} // namespace OpcUti

#endif /* TECHNOSOFTWARE_OPCUTI_H */
