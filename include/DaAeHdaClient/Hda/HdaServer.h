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

#ifndef TECHNOSOFTWARE_HDASERVER_H
#define TECHNOSOFTWARE_HDASERVER_H

#include "DaAeHdaClient/ClientBase.h"
#include "DaAeHdaClient/OpcBase.h"
#include "HdaServerStatus.h"
#include "HdaItem.h"
#include "DaAeHdaClient/Hda/HdaAggregateId.h"
#include "DaAeHdaClient/Hda/HdaAggregate.h"
#include "DaAeHdaClient/Hda/HdaItemAttributeId.h"
#include "DaAeHdaClient/Hda/HdaItemAttribute.h"
#include "Base/Status.h"
#include "Base/Timestamp.h"
#include <vector>

namespace Technosoftware
{
    namespace DaAeHdaClient
    {	
		class HdaServerImpl;

		typedef vector<HdaAggregate> HdaAggregates;
		typedef vector<HdaItemAttribute> HdaItemAttributes;

        /**
         * @class	HdaServer
         *
         * @brief	The HdaServer is the ClientSdk base class to have access to an OPC Historical Data
         * 			Access (HDA) Server.
         * 			
         * 			To have access to several OPC HDA Servers the client needs to add only multiple
         * 			HdaServer instances.
         * 			
         * 			First call HdaServer::Connect() before using other methods provided by this object.
         * 			Otherwise all functions returns a Technosoftware::Base::Status with result code
         * 			0x800401FD - 'Object is not connected to server'.
		 *
		 * @ingroup  HDAClient
		 */

        class OPCCLIENTSDK_API HdaServer : protected OpcObject
        {
            friend class HdaGroupImpl;
            friend class HdaBrowserImpl;

        public:

            /**
             * @fn	HdaServer::HdaServer() throw (Technosoftware::Base::Exception);
             *
             * @brief	Constructs a HdaServer object.
             *
             * @exception	Technosoftware::Base::Exception	Thrown when an exception error condition occurs.
             * @exception	Technosoftware::Base::Status   	Thrown when an opc error error condition occurs.
             */

            HdaServer() throw (Technosoftware::Base::Exception);

            /**
             * @fn	HdaServer::~HdaServer() throw ();
             *
             * @brief	Destroys a HdaServer object.
             * 			
             * 			If the object is still connected to an OPC HDA Server then all existing subscriptions
             * 			as well as groups and items will be removed and the object disconnected from the
             * 			server.
             */

            ~HdaServer() throw ();

            /**
             * @fn	HdaServerStatus& HdaServer::GetStatus() const;
             *
             * @brief	Allows access to the status information of the currently connected server.
             * 			
             * 			The information is only valid if the this object is connected to an OPC Data Access
             * 			Server.
             *
             * @return	A HdaServerStatus&amp;
             */

            HdaServerStatus& GetStatus() const;

            /**
             * @fn	bool HdaServer::IsConnected() const throw ();
             *
             * @brief	Indicates if the server object is connected to an OPC Historical Data Access (HDA)
             * 			Server.
             *
             * @return	true if connected, false if not.
             */

            bool IsConnected() const throw ();

            /**
             * @fn	Technosoftware::Base::Status HdaServer::Connect(const string& sServerName, const string& sMachineName = "", uint32_t dwCoInit = 0);
             *
             * @brief	Connects the object to an OPC Historical Data Access (HDA) Server.
             *
             * @param	sServerName 	Name of the server (PorgID). The usual form is xxx.yyyy.n or xxx.yyy.
             * 							The registry is checked if the specified name is a \version independent
             * 							name. If so, the associated name is used instead. Version independent
             * 							server names can be used only on the local machine.
             * @param	sMachineName	(Optional) Name of the machine. By default, all UNC ("\\\\server" or
             * 							"server")
             * 							and DNS names ("domain.com", "server.technosoftware.com", or
             * 							"209.130.112.180") names are allowed. If no machine name is specified
             * 							then the OPC Server on the local machine is used.
             * @param	dwCoInit		(Optional) Optional Parameter with default value
             * 							COINIT_MULTITHREADED. Flags specifying the concurrency model and
             * 							initialization options for the thread. This parameter must be specified
             * 							only if there are other COM components in your application which does not
             * 							support the multi\-threaded concurrency model.
             *
             * @return	A Technosoftware::Base::Status object with the result of the operation.
             */

            Technosoftware::Base::Status Connect(const string& sServerName, const string& sMachineName = "", uint32_t dwCoInit = 0);

            /**
             * @fn	void HdaServer::Disconnect();
             *
             * @brief	Disconnects the object from an OPC Historical Data Access (HDA) Server.
             * 			
             * 			This method also removes all existing subscriptions as well as groups and items.
             */

            void        Disconnect();

            /**
             * @fn	Technosoftware::Base::Status HdaServer::UpdateStatus();
             *
             * @brief	Retrieves new status information from the currently connected server.
             * 			
             * 			Use HdaServer::Status() to access the updated status information.
             *
             * @return	An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status UpdateStatus();

            /**
             * @fn	Technosoftware::Base::Status HdaServer::PollStatus(void(*pfnStatusSink)(Technosoftware::Base::Status& res, HdaServerStatus& Status), uint32_t dwRefreshRate = 1000);
             *
             * @brief	Activates, inactivates or changes polling of the current server status.
             * 			
             * 			If this function is called and the the status polling is already activated then only
             * 			the refresh rate will be changed. Please note that the new refresh value is first
             * 			taken after the current refresh interval has expired.
             *
             * @param [in,out]	pfnStatusSink	The address of the function which will be periodically called
             * 									with the current server state and result. The server status
             * 									polling can be inactivated with value Null. The status
             * 									information is only valid if Technosoftware::Base::Status
             * 									contains a success code.
             * @param 		  	dwRefreshRate	(Optional) Optional parameter which specifies the refresh
             * 									rate. A value lower than 100 is not accepted and the function
             * 									returns with an error result of type Invalid Argument. The
             * 									default value is 1000.
             *
             * @return	An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status PollStatus(void(*pfnStatusSink)(Technosoftware::Base::Status& res, HdaServerStatus& Status), uint32_t dwRefreshRate = 1000);

            /**
             * @fn	Technosoftware::Base::Status HdaServer::PollStatus(void(*pfnStatusSink)(Technosoftware::Base::Status& res, HdaServerStatus& Status, void* pCookie), void* pCookie, uint32_t dwRefreshRate = 1000);
             *
             * @brief	Activates, inactivates or changes polling of the current server status. The callback
             * 			has a user specified parameter value (Cookie).
             * 			
             * 			If this function is called and the the status polling is already activated then only
             * 			the refresh rate will be changed. Please note that the new refresh value is first
             * 			taken after the current refresh interval has expired.
             * 			
             * 			The specified Cookie value is forwarded to the callback function. E.g. this can be
             * 			used to identify the source of the status if there are connections to several OPC
             * 			Servers and only one callback function is used.
             *
             * @param [in,out]	pfnStatusSink	The address of the function which will be periodically called
             * 									with the current server state, the result and the specified
             * 									cookie value. The server status polling can be inactivated
             * 									with value Null. The status information is only valid if
             * 									Technosoftware::Base::Status contains a success code.
             * @param [in,out]	pCookie		 	This value is forwarded unchanged to the callback function.
             * @param 		  	dwRefreshRate	(Optional) Optional parameter which specifies the refresh
             * 									rate. A value lower than 100 is not accepted and the function
             * 									returns with an error result of type Invalid Argument. The
             * 									default value is 1000 = 1000.
             *
             * @return	An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status PollStatus(void(*pfnStatusSink)(Technosoftware::Base::Status& res, HdaServerStatus& Status, void* pCookie), void* pCookie, uint32_t dwRefreshRate = 1000);

            /**
             * @fn	Technosoftware::Base::Status HdaServer::SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason));
             *
             * @brief	Activates or inactivates a subscription to shutdown requests from the connected
             * 			server.
             * 			
             * 			The HdaServer object should be disconnected if a server requests to shutdown.
             * 			Warning: Do not call HdaServer::Disconnect() or any other OPC function within the
             * 			provided callback sink.
             *
             * @param [in,out]	pfnShutdownRequestSink	The address of the function which will be called when
             * 											the server needs to shutdown. An existing shutdown
             * 											request subscription can be removed with value Null.
             *
             * @return	An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status SetShutdownRequestSubscription(void(*pfnShutdownRequestSink)(string& sReason));

            /**
             * @fn	Technosoftware::Base::Status HdaServer::RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix = false);
             *
             * @brief	Registers the client name with the connected server.
             *
             * @param	sClientName				The name to be registered.
             * @param	fMachineNameAsPrefix	(Optional) Optional parameter which specifies if the name of
             * 									the local computer should be used as prefix. If \a true then the
             * 									format of the text for the registration is \\\\\&lt;
             * 									ComputerName\&gt;\\\&lt; Value of parameter \a sClientName\&gt;.
             *
             * @return	An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status RegisterClientName(const string& sClientName, bool fMachineNameAsPrefix = false);

			/**
			 * @fn	Technosoftware::Base::Status HdaServer::GetItemAttributes(HdaItemAttributes& hdaitemAtttributes);
			 *
			 * @brief	This function returns the item attributes supported by the server. The OPC defined
			 * 			attribute types are defined in section 5.2. Vendor specific attributes also are
			 * 			supported. The vendor supplied attributes are made available to allow the client to
			 * 			access and display vendor specific information. Attribute data types are intended to
			 * 			allow query filtering when browsing item ids. If no attributes are supported by the
			 * 			server, the function shall return a count of 0 and NULL pointers.
			 *
			 * @param [in,out]	hdaitemAtttributes	The OPC HDA item attributes.
			 *
			 * @return	An Technosoftware::Base::Status.
			 */

			Technosoftware::Base::Status GetItemAttributes(HdaItemAttributes& hdaitemAtttributes);

			/**
			 * @fn	Technosoftware::Base::Status HdaServer::GetAggregates(HdaAggregates& hdaAggregates);
			 *
			 * @brief	This function returns the list of aggregates supported by the server. The OPC defined
			 * 			aggregates are defined by HdaAggregateId. Vendor specific aggregates also are
			 * 			supported. The vendor supplied aggregates are made available to allow the client to
			 * 			use all the functions available to their specific server.
			 *
			 * @param [in,out]	hdaAggregates	The OPC HDA aggregates.
			 *
			 * @return	An Technosoftware::Base::Status.
			 */

			Technosoftware::Base::Status GetAggregates(HdaAggregates& hdaAggregates);

            /**
             * @fn	Technosoftware::Base::Status HdaServer::ReadRaw(const char* itemId, Base::Timestamp startTime, Base::Timestamp endTime, DWORD maxValues, BOOL bounds, HdaItem* hdaItem, HRESULT* error);
             *
             * @brief	This function reads the values, qualities, and timestamps from the history database
             * 			for the specified time domain for one item. When bounds is true, the bounding values
             * 			for the time domain are returned. This function is intended for use by clients
             * 			wanting the actual data saved within the historian. The actual data may be compressed
             * 			or may be all data collected for the item depending on the historian and the storage
             * 			rules invoked when the item values were saved.  The optional bounding values are
             * 			provided to allow clients to interpolate values for the start and end times when
             * 			trending the actual data on a display.
             *
             * @param 		  	itemId   	The item name to be read from.
             * @param 		  	startTime	The beginning of the history period to be read.
             * @param 		  	endTime  	The end of the history period to be read.
             * @param 		  	maxValues	The maximum number of values returned for any item over the time
             * 								range. If only one time is specified, the time range must extend
             * 								to return this number of values.
             * @param 		  	bounds   	True if bounding values should be returned. Default is false.
             * @param [in,out]	hdaItem  	The HdaItem.
             * @param [in,out]	error	 	The result for the operation.
             *
             * @return	An Technosoftware::Base::Status.
             */

            Technosoftware::Base::Status ReadRaw(const char* itemId, Base::Timestamp startTime, Base::Timestamp endTime, DWORD maxValues, BOOL bounds, HdaItem* hdaItem, HRESULT* error);

        protected:
            OpcAutoPtr<HdaServerImpl> m_Impl;
        };
    }
}

#endif /* TECHNOSOFTWARE_HDASERVER_H */
