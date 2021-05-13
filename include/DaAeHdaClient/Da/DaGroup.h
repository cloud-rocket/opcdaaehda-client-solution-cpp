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

#ifndef TECHNOSOFTWARE_DAGROUP_H
#define TECHNOSOFTWARE_DAGROUP_H

#include "DaAeHdaClient/ClientBase.h"
#include "DaAeHdaClient/OpcBase.h"
#include "DaAeHdaClient/Da/DaCommon.h"
#include "Base/Handles.h"
#include "Base/Status.h"


namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class DaServer;
        class DaItem;
        class DaIDataCallback;
        class DaGroupImpl;

        /**
         * @class   DaGroup
         *
         * @brief   The DaGroup is the class to handle OPC DA Group objects.
         *          
         *          A DaGroup object can be used to manage collection of items which can be read and
         *          written. By activating the Data Change Subscription the value changes of all readable
         *          items of this group can be received in an own callback function.
         *
         * @ingroup  DAClient
         */

        class OPCCLIENTSDK_API DaGroup : protected OpcObject
        {
        public:

            /**
             * @fn  DaGroup::DaGroup(DaServer* parent, const char* name = NULL, bool active = true, uint32_t requestedUpdateRate = 0, Base::ClientHandle handleClientGroup = -1, long* timeBias = NULL, float* percentDeadband = NULL, uint32_t lcId = 0x800) noexcept(false);
             *
             * @brief   Constructs a DaGroup object.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   Technosoftware::Base::Status    Thrown when an opc error error condition occurs.
             *
             * @param [in,out]  parent              Address of a DaServer object which takes the ownership of
             *                                      this group object.
             * @param           name                (Optional) Optional parameter which defines the name of
             *                                      the group. A name must be unique among the other groups
             *                                      created by this client. If this parameter is not
             *                                      specified or name is pointer to a NULL string then the
             *                                      server will generate a unique name.
             * @param           active              (Optional) Optional parameter which defines if the group
             *                                      is to be created active or inactive. Only active groups
             *                                      can receive value changes via Data Change Subscriptions.
             *                                      See also SetActive().
             * @param           requestedUpdateRate (Optional) Optional parameter which defines the requested
             *                                      update rate in milliseconds. This value specifies the
             *                                      fastest rate at which data changes may be sent to the own
             *                                      callback function for items in this group. If this
             *                                      parameter is not specified or requestedUpdateRate is 0
             *                                      then the server should use the fastest practical rate.
             *                                      Use RevisedUpdateRate()
             *                                      to see which update rate the server has accepted.
             * @param           handleClientGroup   (Optional) Client provided handle of this group. This
             *                                      value can be used to help the client identify the group
             *                                      object.
             * @param [in,out]  timeBias            Initial TimeBias for this group in minutes. Pass a NULL
             *                                      pointer if you wish the group to use the default system
             *                                      TimeBias. Please refer to the OPC DA Specification for a
             *                                      detailed description of TimeBias.
             * @param [in,out]  percentDeadband     The percent change in an item value that will cause a
             *                                      subscription callback for that value to a client. A NULL
             *                                      pointer is equivalent to 0.0. Please refer to the OPC DA
             *                                      Specification for a detailed description of Percent
             *                                      Deadband.
             * @param           lcId                (Optional) The language to be used by the server when
             *                                      returning values (including EU enumeration's) as text for
             *                                      operations on this group.
             */

            DaGroup(DaServer*           parent,
                const char*             name = nullptr,
                bool                    active = true,
                uint32_t                requestedUpdateRate = 0,
                Base::ClientHandle      handleClientGroup = -1,
                long*                   timeBias = nullptr,
                float*                  percentDeadband = nullptr,
                uint32_t                lcId = 0x800) noexcept(false);

            /**
             * @fn  DaGroup::~DaGroup() throw ();
             *
             * @brief   Destroys a DaGroup object.
             *          
             *          If the object is still connected to an OPC DA Server then all existing subscriptions
             *          as well as groups and items will be removed and the object disconnected from the
             *          server.
             */

            ~DaGroup() noexcept;

        public:

            /**
             * @fn  bool DaGroup::IsActive() const noexcept;
             *
             * @brief   Indicates the current active state of the group object.
             *
             * @return  true if active, false if not.
             */

            bool IsActive() const noexcept;

            /**
             * @fn  bool DaGroup::IsEnabled() const noexcept;
             *
             * @brief   Indicates if data change notifications via the Data Change Subscription are enabled
             *          or disabled.
             *          
             *          If there is no Data Callback Subscription the return value of this method is always
             *          'false'.
             *
             * @return  true if enabled, false if not.
             */

            bool IsEnabled() const noexcept;

            /**
             * @fn  bool DaGroup::HasDataSubscription() const throw ();
             *
             * @brief   Indicates if the Data Change Subscription of this group object has been activated.
             *
             * @return  true if data subscription, false if not.
             */

            bool HasDataSubscription() const noexcept;

            /**
             * @fn  uint32_t DaGroup::GetRevisedUpdateRate() const noexcept;
             *
             * @brief   The revised update rate of the group object in milliseconds.
             *
             * @return  An uint32_t.
             */

            uint32_t GetRevisedUpdateRate() const noexcept;

            /**
             * @fn  Base::ServerHandle DaGroup::GetServerHandle() const throw ();
             *
             * @brief   The server handle of the group object.
             *
             * @return  A ServerHandle.
             */

            Base::ServerHandle GetServerHandle() const noexcept;

            /**
             * @fn  Base::ClientHandle DaGroup::GetClientHandle() const noexcept;
             *
             * @brief   The client handle of the group object.
             *
             * @return  A ClientHandle.
             */

            Base::ClientHandle GetClientHandle() const noexcept;

            /**
             * @fn  Technosoftware::Base::Status DaGroup::SetActive(bool active = true);
             *
             * @brief   Sets the active state of the group object.
             *
             * @param   active  (Optional) The new active state of the group object. Use true to activate and
             *                  false to deactivate the group object.
             *
             * @return  An Technosoftware::Base::Status.
             *
             * ### remarks  Please refer to the OPC DA Specification, chapter 'Data Acquisition and Active
             *              State Behavior', for details on the behavior of the active state of groups with
             *              respect to read operations and data change notifications.
             */

            Base::Status SetActive(bool active = true);

            /**
             * @fn  Base::Status DaGroup::AddItems( DaItemDefinitions& itemDefinitions, vector<DaItem*>& items, void(*errorHandler)(const DaItemDefinition& itemDefinition, Base::Status status) = nullptr);
             *
             * @brief   Adds items to the group object.
             *          
             *          This method can partly be successful.
             *
             * @param [in,out]  itemDefinitions Reference to the definitions of the items to be added.
             * @param [in,out]  items           Reference to an array with DaItem pointers. If this function
             *                                  succeeds this array contains the DaItem pointers of all
             *                                  successfully added items.
             * @param [in,out]  errorHandler    Address of an optional Error Handler. This handler is called
             *                                  for all items which cannot be added successfully.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Base::Status AddItems(  DaItemDefinitions& itemDefinitions,
                                    vector<DaItem*>& items,
                                    void(*errorHandler)(const DaItemDefinition& itemDefinition, Base::Status status) = nullptr);

            /**
             * @fn  Base::Status DaGroup::Read(vector<DaItem*>& items, bool fromCache = true);
             *
             * @brief   Reads the value, quality and timestamp of the specified items.
             *          
             *          If the function succeeds the value, quality and timestamp of the individual items can
             *          be accessed with DaItem::ReadResult(). If this function succeeds only partially then
             *          the results of each item in the list first must be verified with
             *          DaItem::ReadResult().Result().
             *          
             *          If only the value of a single element must be read the function DaItem::Read()
             *          also can be used.
             *
             * @param [in,out]  items       List of items with values to be read.
             * @param           fromCache   (Optional) Optional parameter which specifies if the cache or the
             *                              device is used as data source. In general clients should read
             *                              from cache. Please refer to the OPC DA Specification for a
             *                              general discussion about the differences between reading from
             *                              cache and reading from device.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Base::Status Read(vector<DaItem*>& items, bool fromCache = true);

            /**
             * @fn  Base::Status DaGroup::Write(vector<DaItem*>& items);
             *
             * @brief   Writes the values of the specified items.
             *          
             *          First the values of the individual items must be set with DaItem::SetWriteValue(). If
             *          this function succeeds only partially then the results of each item in the list can
             *          be verified with DaItem::WriteResult(). See also Technosoftware::Base::Status for an
             *          example.
             *          
             *          If only the value of a single element must be written the function DaItem::Write(
             *          LPVARIANT ) also can be used.
             *
             * @param [in,out]  items   List of items with values to be written.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Base::Status Write(vector<DaItem*>& items);

            /**
             * @fn  Base::Status DaGroup::SetDataSubscription(DaIDataCallback* userDataCallback);
             *
             * @brief   Activates or inactivate's the Data Change Subscription of this group object.
             *          
             *          To receive data change notifications and the results of asynchronus operations a Data
             *          Change Subscription must be activated.
             *
             * @param [in,out]  userDataCallback    Address of the object which implements the callback
             *                                      functions for asynchronous notifications. An existing Data
             *                                      Change Subscription can be removed with value Null.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Base::Status SetDataSubscription(DaIDataCallback* userDataCallback);

            /**
             * @fn  Base::Status DaGroup::ReadAsync(vector<DaItem*>& items, uint32_t transactionId, uint32_t* cancelId);
             *
             * @brief   Reads the value, quality and timestamp of the specified items asynchronously.
             *          
             *          The results are returned via the DaIDataCallback::ReadComplete() notification. If
             *          this function succeeds only partially then the results of each item in the list can
             *          be verified with DaItem::AsyncCommandResult(). Only items with a success code will
             *          also have a result returned in the read complete callback. If there is no Data
             *          Callback Subscription this method returns a Technosoftware::Base::Status with result
             *          code 0x80040200.
             *          
             *          If only the value of a single element must be read the function DaItem::ReadAsync()
             *          also can be used.
             *
             * @param [in,out]  items           List of items with values to be read.
             * @param           transactionId   A client provided value to identify the results of
             *                                  asynchronous operations.
             * @param [in,out]  cancelId        Address of a variable where the server stores an identifier
             *                                  which can be used in case the operation needs to be canceled.
             *
             * @return  A Technosoftware::Base::Status.
             */

            Base::Status ReadAsync(vector<DaItem*>& items, uint32_t transactionId, uint32_t* cancelId);

            /**
             * @fn  Base::Status DaGroup::WriteAsync(vector<DaItem*>& items, uint32_t transactionId, uint32_t* cancelId);
             *
             * @brief   Writes the values of the specified items asynchronously.
             *
             * @param [in,out]  items           List of items with values to be written.
             * @param           transactionId   A client provided value to identify the results of
             *                                  asynchronous operations.
             * @param [in,out]  cancelId        Address of a variable where the server stores an identifier
             *                                  which can be used in case the operation needs to be canceled.
             *
             * @return  A Technosoftware::Base::Status.
             *
             * ### remarks  First the values of the individual items must be set with
             *              DaItem::SetWriteValue(). The results are returned via the
             *              DaIDataCallback::WriteComplete() notification. If this function succeeds only
             *              partially then the results of each item in the list can be verified with
             *              DaItem::AsyncCommandResult(). Only items with a success code will also have a
             *              result returned in the write complete callback. If there is no Data Callback
             *              Subscription this method returns a Technosoftware::Base::Status with result code
             *              0x80040200.
             *              
             *              If only the value of a single element must be read the function
             *              DaItem::WriteAsync()
             *              also can be used.
             */

            Base::Status WriteAsync(vector<DaItem*>& items, uint32_t transactionId, uint32_t* cancelId);

            /**
             * @fn  Base::Status DaGroup::SetEnable(bool enable = true);
             *
             * @brief   Enables or disables data change notifications via the Data Change Subscription.
             *          
             *          If there is no Data Callback Subscription this method returns a
             *          Technosoftware::Base::Status with result code 0x80040200.
             *
             * @param   enable  (Optional) The new enable state of the group object. Use true to enable and
             *                  false to disable DaIDataCallback\:\:DataChange()
             *                  callbacks subscribed with this group object.
             *
             * @return  A Technosoftware::Base::Status.
             */

            Base::Status SetEnable(bool enable = true);

            /**
             * @fn  Base::Status DaGroup::Cancel(uint32_t cancelId);
             *
             * @brief   Requests the server to cancel an outstanding asynchronous transaction.
             *
             * @param   cancelId    The server generated identifier which was returned by the asynchronous
             *                      operation to be canceled now.
             *
             * @return  A Technosoftware::Base::Status.
             *
             * ### remarks  If this operation succeeds then no callback will occur. If this operation fails
             *              then a callback may already have occurred or will occur because it was to late to
             *              cancel the transaction.
             */

            Base::Status Cancel(uint32_t cancelId);

            /**
             * @fn  Base::Status DaGroup::Refresh(uint32_t transactionId, uint32_t* cancelId, bool fromCache = true);
             *
             * @brief   Forces a data change notification for all active items.
             *          
             *          If this method returns with an error code then no callback will occur. If there is no
             *          Data Callback Subscription this method returns a Technosoftware::Base::Status with
             *          result code 0x80040200.
             *
             * @param           transactionId   A client provided value to identify the results of
             *                                  asynchronous operations.
             * @param [in,out]  cancelId        Address of a variable where the server stores an identifier
             *                                  which can be used in case the operation needs to be canceled.
             * @param           fromCache       (Optional) Optional parameter which specifies if the cache or
             *                                  the device is used as data source. In general clients should
             *                                  read from cache. Please refer to the OPC DA Specification for
             *                                  a general discussion about the differences between reading
             *                                  from cache and reading from device.
             *
             * @return  A Technosoftware::Base::Status.
             */

            Base::Status Refresh(uint32_t transactionId, uint32_t* cancelId, bool fromCache = true);

        protected:
            OpcAutoPtr<DaGroupImpl> impl_;
        };
    }
}

#endif // TECHNOSOFTWARE_DAGROUP_H
