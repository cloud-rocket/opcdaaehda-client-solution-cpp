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

#ifndef __OPCCLIENTSDK_H
#define __OPCCLIENTSDK_H

#define _SDK_VERSION           0x0100              // Version 1.0.0

#include "Base/Status.h"

#include "ClientBase.h"

#include "Da\DaServer.h"
#include "Da\DaBrowser.h"
#include "Da\DaGroup.h"
#include "Da\DaItem.h"

#ifdef _WIN64                                    // Common macros and definitions for OPC Alarm & Events
#include "Classic/inc64/opcaedef.h"
#else
#include "Classic/inc32/opcaedef.h"
#endif // _WIN64
                     
#include "Ae\AeServer.h"
#include "Ae\AeSubscription.h"
#include "Ae\AeEvent.h"

#include "Hda\HdaServer.h"
#include "Hda\HdaItem.h"


#endif // __OPCCLIENTSDK_H
