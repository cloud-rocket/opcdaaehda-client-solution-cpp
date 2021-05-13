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

#ifndef TECHNOSOFTWARE_AESERVER_H
#define TECHNOSOFTWARE_AESERVER_H

#include "DaAeHdaClient/ClientBase.h"
#include "DaAeHdaClient/OpcBase.h"
#include "AeServerStatus.h"
#include "Base/Status.h"


namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class AeServerImpl;

        /**
         * @class   AeServer
         *
         * @brief   The AeServer is the ClientSdk base class to have access to an OPC Alarms &amp; Events
         *          Server.
         *          
         *          To have access to several OPC AE Servers the client needs to add only multiple
         *          AeServer instances.
         *          
         *          First call AeServer::Connect() before using other methods provided by this object.
         *          Otherwise all functions returns a Technosoftware::Base::Status with result code
         *          0x800401FD - 'Object is not connected to server'.
         *
         * @ingroup  AEClient
         */

        class OPCCLIENTSDK_API AeServer : protected OpcObject
        {
            friend class AeSubscriptionImpl;

        public:

            /**
             * @fn  AeServer::AeServer() throw (Technosoftware::Base::Exception);
             *
             * @brief   Constructs a AeServer object.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             */

            AeServer() noexcept(false);

            /**
             * @fn  AeServer::~AeServer() throw ();
             *
             * @brief   Destroys a AeServer object. If the object is still connected to an OPC AE Server then
             *          all existing subscriptions will be removed and the object disconnected from the
             *          server.
             */

            ~AeServer() noexcept;

            /**
             * @fn  AeServerStatus& AeServer::GetStatus() const;
             *
             * @brief   Allows access to the status information of the currently connected server.
             *
             * @return  An AeServerStatus&amp;
             *          
             *          The information is only valid if the this object is connected to an OPC Alarms&amp;
             *          Events Server.
             */

            AeServerStatus& GetStatus() const;

            /**
             * @fn  bool AeServer::IsConnected() const noexcept;
             *
             * @brief   Indicates if the server object is connected to an OPC Alarms &amp; Events Server.
             *
             * @return  true if connected, false if not.
             */

            bool IsConnected() const noexcept;

            /**
             * @fn  Technosoftware::Base::Status AeServer::Connect(const string& serverName, const string& machineName = "", uint32_t coInit = 0);
             *
             * @brief   Connects to the server.
             *
             * @param   serverName  Name of the server.
             * @param   machineName (Optional) name of the machine.
             * @param   coInit      (Optional) the co init.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status Connect(const string& serverName, const string& machineName = "", uint32_t coInit = 0);

            /**
             * @fn    void AeServer::Disconnect();
             *
             * @brief    Disconnects the object from an OPC Alarms &amp; Events Server. This method also
             *             removes all existing subscriptions.
             */

            void        Disconnect();

            /**
             * @fn  Technosoftware::Base::Status AeServer::UpdateStatus();
             *
             * @brief   Retrieves new status information from the currently connected server. Use
             *          AeServer::Status() to access the updated status information.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status UpdateStatus();

            /**
             * @fn  Technosoftware::Base::Status AeServer::PollStatus(void(*pfnStatusSink)(Technosoftware::Base::Status& staus, AeServerStatus& serverStatus), uint32_t refreshRate = 1000);
             *
             * @brief   Activates, inactivates or changes polling of the current server status. If this
             *          function is called and the the status polling is already activated then only the
             *          refresh rate will be changed. Please note that the new refresh value is first taken
             *          after the current refresh interval has expired.
             *
             * @param [in,out]  pfnStatusSink   The address of the function which will be periodically called
             *                                  with the current server state and result. The server status
             *                                  polling can be inactivated with value Null. The status
             *                                  information is only valid if Technosoftware::Base::Status
             *                                  contains a success code.
             * @param           refreshRate     (Optional) Optional parameter which specifies the refresh
             *                                  rate.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status PollStatus(void(*pfnStatusSink)(Technosoftware::Base::Status& staus, AeServerStatus& serverStatus), uint32_t refreshRate = 1000);

            /**
             * @fn  Technosoftware::Base::Status AeServer::SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& reason));
             *
             * @brief   Activates or inactivates a subscription to shutdown requests from the connected
             *          server. The AeServer object should be disconnected if a server requests to shutdown.
             *
             * @param [in,out]  pfnShutdownRequestSink  The address of the function which will be called when
             *                                          the server needs to shutdown. An existing shutdown
             *                                          request subscription can be removed with value Null.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& reason));

            /**
             * @fn  Technosoftware::Base::Status AeServer::RegisterClientName(const string& clientName, bool machineNameAsPrefix = false);
             *
             * @brief   Registers the client name with the connected server.
             *
             * @param   clientName          The name to be registered.
             * @param   machineNameAsPrefix (Optional) Optional parameter which specifies if the name of the
             *                              local computer should be used as prefix. If true then the format
             *                              of the text for the registration is \\\\\&lt;
             *                              ComputerName\&gt;\\\&lt; Value of parameter sClientName\&gt;.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status RegisterClientName(const string& clientName, bool machineNameAsPrefix = false);

            // Implementation
        protected:
            OpcAutoPtr<AeServerImpl> impl_;
        };

    }
}

#endif // TECHNOSOFTWARE_AESERVER_H
