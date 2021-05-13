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

#ifndef TECHNOSOFTWARE_DASERVER_H
#define TECHNOSOFTWARE_DASERVER_H

#include "DaAeHdaClient/ClientBase.h"
#include "DaAeHdaClient/OpcBase.h"
#include "DaAeHdaClient/Da/DaServerStatus.h"
#include "Base/Status.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class DaServerImpl;

        /**
         * @class   DaServer
         *
         * @brief   The DaServer is the ClientSdk base class to have access to an OPC Data Access Server.
         *          
         *          To have access to several OPC DA Servers the client needs to add only multiple
         *          DaServer instances.
         *          
         *          First call DaServer::Connect() before using other methods provided by this object.
         *          Otherwise all functions returns a Technosoftware::Base::serverStatus with result code
         *          0x800401FD - 'Object is not connected to server'.
         *
         * @ingroup  DAClient
         */

        class OPCCLIENTSDK_API DaServer : protected OpcObject
        {
            friend class DaGroupImpl;
            friend class DaBrowserImpl;

        public:

            /**
             * @fn  DaServer::DaServer() noexcept(false);
             *
             * @brief   Constructs a DaServer object.
             *
             * @exception   Technosoftware::Base::Exception             Thrown when an exception error
             *                                                          condition occurs.
             * @exception   Technosoftware::Base::OutOfMemoryException  Thrown when a low memory situation
             *                                                          occurs.
             */

            DaServer() noexcept(false);

            /**
             * @fn  DaServer::~DaServer() noexcept;
             *
             * @brief   Destroys a DaServer object.
             *          
             *          If the object is still connected to an OPC DA Server then all existing subscriptions
             *          as well as groups and items will be removed and the object disconnected from the
             *          server.
             */

            ~DaServer() noexcept;

            /**
             * @fn  DaServerStatus& DaServer::GetStatus() const;
             *
             * @brief   Allows access to the status information of the currently connected server.
             *          
             *          The information is only valid if the this object is connected to an OPC Data Access
             *          Server.
             *
             * @return  A DaServerStatus&amp;
             */

            DaServerStatus& GetStatus() const;

            /**
             * @fn  bool DaServer::IsConnected() const noexcept;
             *
             * @brief   Indicates if the server object is connected to an OPC Data Access Server.
             *
             * @return  true if connected, false if not.
             */

            bool IsConnected() const noexcept;

            /**
             * @fn  Base::serverStatus DaServer::Connect(const string& serverName, const string& machineName = "", uint32_t coInit = 0);
             *
             * @brief   Connects the object to an OPC Data Access Server.
             *
             * @param   serverName  Name of the server (PorgID). The usual form is xxx.yyyy.n or xxx.yyy. The
             *                      registry is checked if the specified name is a \version independent name.
             *                      If so, the associated name is used instead. Version independent server
             *                      names can be used only on the local machine.
             * @param   machineName (Optional) Name of the machine. By default, all UNC ("\\\\server" or
             *                      "server")
             *                      and DNS names ("domain.com", "server.technosoftware.com", or
             *                      "209.130.112.180") names are allowed. If no machine name is specified
             *                      then the OPC Server on the local machine is used.
             * @param   coInit      (Optional) Optional Parameter with default value COINIT_MULTITHREADED.
             *                      Flags specifying the concurrency model and initialization options for the
             *                      thread. This parameter must be specified only if there are other COM
             *                      components in your application which does not support the multithreaded
             *                      concurrency model.
             *
             * @return  A Technosoftware::Base::serverStatus object with the result of the operation.
             */

            Base::Status Connect(const string& serverName, const string& machineName = "", uint32_t coInit = 0);

            /**
             * @fn  void DaServer::Disconnect();
             *
             * @brief   Disconnects the object from an OPC Data Access Server.
             *          
             *          This method also removes all existing subscriptions as well as groups and items.
             */

            void Disconnect();

            /**
             * @fn  Base::serverStatus DaServer::UpdateStatus();
             *
             * @brief   Retrieves new status information from the currently connected server.
             *          
             *          Use DaServer::serverStatus() to access the updated status information.
             *
             * @return  An Technosoftware::Base::serverStatus.
             */

            Base::Status UpdateStatus();

            /**
             * @fn  Base::Status DaServer::PollStatus(void(*statusSink)(Base::Status& status, DaServerStatus& serverStatus), uint32_t refreshRate = 1000);
             *
             * @brief   Activates, inactivates or changes polling of the current server status.
             *
             * @param [in,out]  statusSink  The address of the function which will be periodically called
             *                              with the current server state and result. The server status
             *                              polling can be inactivated with value Null. The status
             *                              information is only valid if Technosoftware::Base::serverStatus
             *                              contains a success code.
             * @param           refreshRate (Optional) Optional parameter which specifies the refresh rate. A
             *                              value lower than 100 is not accepted and the function Returns
             *                              with an error result of type Invalid Argument. The default value
             *                              is 1000. If this function is called and the the status polling is
             *                              already activated then only the refresh rate will be changed.
             *                              Please note that the new refresh value is first taken after the
             *                              current refresh interval has expired.
             *
             * @return  A Technosoftware::Base::Status.
             */

            Base::Status PollStatus(void(*statusSink)(Base::Status& status, DaServerStatus& serverStatus), uint32_t refreshRate = 1000);

            /**
             * @fn  Base::Status DaServer::PollStatus(void(*statusSink)(Base::Status& status, DaServerStatus& serverStatus, void* cookie), void* cookie, uint32_t refreshRate = 1000);
             *
             * @brief   Activates, inactivates or changes polling of the current server status. The callback
             *          has a user specified parameter value (Cookie).
             *
             * @param [in,out]  statusSink  The address of the function which will be periodically called
             *                              with the current server state, the result and the specified
             *                              cookie value. The server status polling can be inactivated with
             *                              value Null. The status information is only valid if
             *                              Technosoftware::Base::serverStatus contains a success code.
             * @param [in,out]  cookie      This value is forwarded unchanged to the callback function.
             * @param           refreshRate (Optional) Optional parameter which specifies the refresh rate. A
             *                              value lower than 100 is not accepted and the function Returns
             *                              with an error result of type Invalid Argument. The default value
             *                              is 1000 = 1000. If this function is called and the the status
             *                              polling is already activated then only the refresh rate will be
             *                              changed. Please note that the new refresh value is first taken
             *                              after the current refresh interval has expired.
             *                              
             *                              The specified Cookie value is forwarded to the callback function.
             *                              E.g. this can be used to identify the source of the status if
             *                              there are connections to several OPC Servers and only one
             *                              callback function is used.
             *
             * @return  A Technosoftware::Base::Status.
             */

            Base::Status PollStatus(void(*statusSink)(Base::Status& status, DaServerStatus& serverStatus, void* cookie), void* cookie, uint32_t refreshRate = 1000);

            /**
             * @fn    Technosoftware::Base::serverStatus DaServer::SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason));
             *
             * @brief    Activates or inactivates a subscription to shutdown requests from the connected
             *             server. The DaServer object should be disconnected if a server requests to shutdown.
             *             Warning: Do not call DaServer::Disconnect() or any other OPC function within the
             *             provided callback sink.
             *
             * @param [in,out]    pfnShutdownRequestSink    The address of the function which will be called when
             *                                             the server needs to shutdown. An existing shutdown
             *                                             request subscription can be removed with value Null.
             *
             * @return    An Technosoftware::Base::serverStatus.
             */

            Base::Status SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason));

            /**
             * @fn    Technosoftware::Base::serverStatus DaServer::RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix = false);
             *
             * @brief    Registers the client name with the connected server.
             *
             * @param    sClientName                The name to be registered.
             * @param    fMachineNameAsPrefix    (Optional) Optional parameter which specifies if the name of
             *                                     the local computer should be used as prefix. If \a true then the
             *                                     format of the text for the registration is \\\\\&lt;
             *                                     ComputerName\&gt;\\\&lt;
             *                                     Value of parameter \a sClientName\&gt;.
             *
             * @return    An Technosoftware::Base::serverStatus.
             */

            Technosoftware::Base::Status RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix = false);

        protected:
            OpcAutoPtr<DaServerImpl> m_Impl;
        };
    }
}


#endif /* TECHNOSOFTWARE_DASERVER_H */
