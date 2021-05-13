/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#include "Base/ServerStates.h"

namespace Technosoftware
{
    namespace Base
    {
        namespace ServerStates
        {

            using namespace Technosoftware::Base::ServerStates;

            std::string ToString(ServerState state)
            {
                switch (state)
                {
                case Running:               return "Running";
                case Failed:                return "Failed";
                case NoConfiguration:       return "NoConfiguration";
                case Suspended:             return "Suspended";
                case Shutdown:              return "Shutdown";
                case Test:                  return "Test";
                case CommunicationFault:    return "CommunicationFault";
                case Unknown:               return "Unknown";
                default:                    return "INVALID";
                }
            }
        }
    }
}
