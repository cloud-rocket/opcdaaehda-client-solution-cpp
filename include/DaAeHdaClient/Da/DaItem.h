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

#ifndef TECHNOSOFTWARE_DAITEM_H
#define TECHNOSOFTWARE_DAITEM_H

#include "DaAeHdaClient/ClientBase.h"
#include "DaAeHdaClient/OpcBase.h"
#include "Base/Handles.h"
#include "Base/Status.h"
#include <Base/Timestamp.h>

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        class DaGroup;

        /**
         * @class   DaIDataCallback
         *
         * @brief   Defines the interface of the user specific callback function for data changes of a
         *          group. To receive group-related data change notifications and the results of
         *          asynchronous operations the user must define a data callback class which inherits
         *          from class DaIDataCallback. Also all pure virtual functions must be implemented but
         *          not used callback functions can be implemented as dummy function.
         *
         *          The user data callback class is used as parameter of function
         *          DaGroup::SetDataSubscription().
         */

        class OPCCLIENTSDK_API DaIDataCallback
        {
        public:

            /**
             * @fn  virtual void DaIDataCallback::DataChange(uint32_t transactionId, DaGroup* group, bool allQualitiesGood, bool allResultsOk, uint32_t numberOfItems, DaItem** items) = 0;
             *
             * @brief   This client provided method receives exception based data changes as well as the
             *          completion results of asynchronous refresh operations.
             *
             * @param           transactionId       The transaction ID is 0 if the call is the result of an
             *                                      ordinary data change notification. Otherwise this is the
             *                                      value passed to an asynchronous refresh operation.
             * @param [in,out]  group               The group where the data change notifications come from.
             * @param           allQualitiesGood    Indicates if the quality of all items is good. If so, it
             *                                      is not required to test the quality of the individual items.
             * @param           allResultsOk        Indicates if the result of all items is OK. If so, it is
             *                                      not required to test the \result of the individual items for
             *                                      success.
             * @param           numberOfItems       The number of items in the item list items.
             * @param [in,out]  items               The list of items which have changed. The individual item
             *                                      results can be accessed with the item method
             *                                      DaItem::ReadAsyncResult().
             */

            virtual void DataChange(uint32_t        transactionId,
                                    DaGroup*        group,
                                    bool            allQualitiesGood,
                                    bool            allResultsOk,
                                    uint32_t        numberOfItems,
                                    DaItem**        items) = 0;

            /**
             * @fn  virtual void DaIDataCallback::ReadComplete( uint32_t transactionId, DaGroup* group, bool allQualitiesGood, bool allResultsOk, uint32_t numberOfItems, DaItem** items) = 0;
             *
             * @brief   This client provided method receives the completion results of asynchronous read
             *          operations.
             *
             * @param           transactionId       The client provided transaction ID passed to an
             *                                      asynchronous read operation.
             * @param [in,out]  group               The read operation was initiated via this group object.
             * @param           allQualitiesGood    Indicates if the quality of all items is good. If so, it
             *                                      is not required to test the quality of the individual items.
             * @param           allResultsOk        Indicates if the result of all items is OK. If so, it is
             *                                      not required to test the \result of the individual items for
             *                                      success.
             * @param           numberOfItems       The number of items in the item list items.
             * @param [in,out]  items               The list of items which were read. The individual item
             *                                      results can be accessed with the item method
             *                                      DaItem::ReadAsyncResult().
             */

            virtual void ReadComplete(  uint32_t        transactionId,
                                        DaGroup*        group,
                                        bool            allQualitiesGood,
                                        bool            allResultsOk,
                                        uint32_t        numberOfItems,
                                        DaItem**        items) = 0;

            /**
             * @fn    virtual void DaIDataCallback::WriteComplete( uint32_t transactionId, DaGroup* group, bool allResultsOk, uint32_t numberOfItems, DaItem** items) = 0;
             *
             * @brief    This client provided method receives the completion results of asynchronous write
             *           operations.
             *
             * @param    transactionId    The client provided transaction ID passed to an asynchronous write
             *                            operation.
             * @param [in,out]    group   The write operation was initiated via this group object.
             * @param    allResultsOk     Indicates if the result of all items is OK. If so, it is not required
             *                            to test the result of the individual items for success.
             * @param    numberOfItems    The number of items in the item list items.
             * @param [in,out]    items   The list of items which were written. The individual item results can
             *                            be accessed with the item method DaItem::WriteAsyncResult().
             */

            virtual void WriteComplete( uint32_t        transactionId,
                                        DaGroup*        group,
                                        bool            allResultsOk,
                                        uint32_t        numberOfItems,
                                        DaItem**        items) = 0;

            /**
             * @fn  virtual void DaIDataCallback::CancelComplete(uint32_t transactionId, DaGroup* group) = 0;
             *
             * @brief   This client provided method receives the acknowledgment of canceled asynchronous
             *          operations.
             *
             * @param           transactionId   The client provided transaction ID passed to a cancel
             *                                  operation.
             * @param [in,out]  group           The cancel operation was initiated via this group object.
             */

            virtual void CancelComplete(uint32_t    transactionId,
                                        DaGroup*    group) = 0;
        };

        /**
         * @class   DaItem
         *
         * @brief   The DaItem is the ClientSdk class to access OPC DA Item related data.
         *          
         *          An item instance provides methods to access the individual data sources provided by
         *          an OPC Server. The item instances can be created with the function
         *          DaGroup::AddItems(). To access the data of multiple items the methods of DaGroup
         *          objects provides better performance.
         *
         * @ingroup  DAClient
         */

        class OPCCLIENTSDK_API DaItem : protected OpcObject
        {
        protected:
            DaItem(DaGroupImpl* parent, Base::ClientHandle clientHandle) noexcept(false);
            void FinalConstruct(OPCITEMRESULT* itemResult) noexcept;
            ~DaItem() noexcept;

        public:

            /**
             * @fn  uint16_t DaItem::GetCanonicalDataType() const noexcept
             *
             * @brief   The canonical data type of the item.
             *
             * @return  An uint16_t.
             */

            uint16_t GetCanonicalDataType() const noexcept { return canonicalDataType_; }

            /**
             * @fn  Base::ClientHandle DaItem::GetClientHandle() const noexcept
             *
             * @brief   The client specific handle of the item.
             *          
             *          This handle allows the client to identify the item.
             *
             * @return  An ClientHandle.
             */

            Base::ClientHandle GetClientHandle() const noexcept { return clientHandle_; }

            /**
             * @fn  Base::ServerHandle DaItem::GetServerHandle() const noexcept
             *
             * @brief   The server specific handle of the item.
             *          
             *          This value is only for information and cannot be used directly by the client.
             *
             * @return  A ServerHandle.
             */

            Base::ServerHandle GetServerHandle() const noexcept { return serverHandle_; }

            /**
             * @fn  uint32_t DaItem::GetAccessRights() const noexcept
             *
             * @brief   The access rights for reading and writing operations of the item.
             *
             * @return  1 OPC_READABLE The item has read access
             *          
             *          2 OPC_WRITEABLE The item has write access
             *          
             *          3 OPC_READABLE + OPC_WRITEABLE The item has read and write access.
             */

            uint32_t GetAccessRights() const noexcept { return accessRights_; }

            /**
             * @class   DaReadResult
             *
             * @brief   Allows the access to the result of the last read operations.
             *
             * @ingroup  DAClient
             */

            class OPCCLIENTSDK_API DaReadResult
            {
            public:

                /**
                 * @fn  VARIANT* DaReadResult::GetValue()
                 *
                 * @brief   The value itself as a variant.
                 *
                 * @return  null if it fails, else a VARIANT*.
                 */

                VARIANT* GetValue() { return &value_; }

                /**
                 * @fn  Base::Timestamp DaReadResult::GetTimeStamp() const noexcept
                 *
                 * @brief   The time stamp (UTC) associated with the value.
                 *
                 * @return  A Base::Timestamp.
                 */

                Base::Timestamp GetTimeStamp() const noexcept { return timestamp_; }

                /**
                 * @fn  uint16_t DaReadResult::GetQuality() const throw ()
                 *
                 * @brief   The quality associated with the value.
                 *
                 * @return  An uint16_t.
                 */

                uint16_t GetQuality() const noexcept { return quality_; }

                /**
                 * @fn  string DaReadResult::GetQualityAsText();
                 *
                 * @brief   Returns the decoded quality flags as text string.
                 *
                 * @return  A string.
                 */

                string GetQualityAsText();

                /**
                 * @fn    Technosoftware::Base::Status DaReadResult::GetResult() const throw()
                 *
                 * @brief    The return value of a read operation.
                 *           
                 *           Value(), Quality(), TimeStamp() and TimeStampAsLocalTimeText() are only valid if the
                 *           result is OK.
                 *
                 * @return    An Technosoftware::Base::Status.
                 */

                Base::Status GetResult() const noexcept { return result_; }

            protected:
                friend class DaItem;                // Access to c'tor, d'tor and Set()
                friend class DaGroupImpl;           // Access to Attach()
                friend class CComOPCDataCallbackImpl;  // Access to Set()
                DaReadResult();
                ~DaReadResult();
                void Attach(OPCITEMSTATE* itemState, Base::Status& status);
                bool Set(LPVARIANT value, const FILETIME* timeStamp, uint16_t quality, Base::Status& status);

                bool Set(OPCITEMSTATE* itemState, Base::Status& status)
                {
                    if (!itemState)                    // itemState may be NULL if status contains an error code
                    {
                        return Set(nullptr, nullptr, 0, status);
                    }
                    else
                    {
                        return Set(&itemState->vDataValue, &itemState->ftTimeStamp, itemState->wQuality, status);
                    }
                }
            private:
                VARIANT         value_;
                Base::Timestamp timestamp_;
                uint16_t        quality_;
                Base::Status    result_;
            };

            /**
             * @class   DaWriteResult
             *
             * @brief   Allows the access to the result of the last write operations.
             *
             * @ingroup  DAClient
             */

            class OPCCLIENTSDK_API DaWriteResult
            {
            public:

                /**
                 * @fn    inline Technosoftware::Base::Status DaWriteResult::Result() const throw()
                 *
                 * @brief    The return value of a write operation.
                 *
                 * @return    An Technosoftware::Base::Status.
                 */

                Base::Status Result() const noexcept { return status_; }

            protected:
                friend class DaItem;                // Access to c'tor and d'tor
                friend class DaGroupImpl;           // Access to Set()
                friend class CComOPCDataCallbackImpl;  // Access to Set()
                DaWriteResult();
                ~DaWriteResult();
                void Set(Base::Status& status) { status_ = status; }
            private:
                Base::Status status_;
            };

            /**
             * @fn  DaReadResult& DaItem::GetReadResult() noexcept
             *
             * @brief   The result of the last synchonous read operation.
             *
             * @return  The result.
             */

            DaReadResult& GetReadResult() noexcept { return readResult_; }

            /**
             * @fn  DaReadResult& DaItem::GetReadAsyncResult() noexcept
             *
             * @brief   The result of the last asynchonous read operation.
             *
             * @return  The asynchronous result.
             */

            DaReadResult& GetReadAsyncResult() noexcept { return readAsyncResult_; }

            /**
             * @fn  DaWriteResult& DaItem::GetWriteResult() noexcept
             *
             * @brief   The result of the last synchronous write operation.
             *
             * @return  A DaWriteResult&amp;
             */

            DaWriteResult& GetWriteResult() noexcept { return writeResult_; }

            /**
             * @fn    inline DaWriteResult& DaItem::GetWriteAsyncResult() throw()
             *
             * @brief    The result of the last asynchronous write operation.
             *
             * @return    A DaWriteResult&amp;
             */

            DaWriteResult& GetWriteAsyncResult() noexcept { return writeAsyncResult_; }

            /**
             * @fn  Base::Status& DaItem::GetAsyncCommandResult() noexcept
             *
             * @brief   The result of the last asynchronous command initiation.
             *
             * @return  An Technosoftware::Base::Status&amp;
             */

            Base::Status& GetAsyncCommandResult() noexcept { return asyncCommandResult_; }

        public:

            /**
             * @fn  Base::Status DaItem::SetWriteValue(LPVARIANT value);
             *
             * @brief   Sets the next value to be written with the operations Write()
             *          or WriteAsync().
             *
             * @param   value   The value.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Base::Status SetWriteValue(LPVARIANT value);

            /**
             * @fn  void DaItem::Write();
             *
             * @brief   Writes the last set value to the server.
             *          
             *          Use SetWriteValue() to set the value to be written and use WriteResult() to test the
             *          result of the write operation.
             *
             */

            void Write();

            /**
             * @fn  Base::Status DaItem::Write(LPVARIANT value);
             *
             * @brief   Writes the specified value to the server.
             *          
             *          This is an overloaded member function, provided for convenience if only the value of
             *          a single item needs to be written. It behaves essentially like the function sequence
             *          SetWriteValue(), Write(), WriteResult().
             *
             * @param   value   The pv value to write.
             *
             * @return  An Technosoftware::Base::Status.
             */

            Base::Status Write(LPVARIANT value);

            /**
             * @fn  Base::Status& DaItem::WriteAsync(uint32_t transactionId, uint32_t* cancelId);
             *
             * @brief   Writes the last set value to the server asynchronously.
             *          
             *          The result is returned via the DaIDataCallback::WriteComplete() notification if this
             *          function succeeds. If there is no Data Callback Subscription this method returns a
             *          Technosoftware::Base::Status with result code 0x80040200. Use SetWriteValue() to set
             *          the value to be written.
             *
             * @param           transactionId   A client provided value to identify the results of
             *                                  asynchronous operations.
             * @param [in,out]  cancelId        Address of a variable where the server stores an identifier
             *                                  which can be used in case the operation needs to be canceled.
             *
             * @return  An Technosoftware::Base::Status&amp;
             */

            Base::Status& WriteAsync(uint32_t transactionId, uint32_t* cancelId);

            /**
             * @fn  Base::Status& DaItem::WriteAsync(LPVARIANT value, uint32_t transactionId, uint32_t* cancelId);
             *
             * @brief   Writes the specified value to the server asynchronously. This is an overloaded member
             *          function, provided for convenience if only the value of a single item needs to be
             *          written asynchronously. It behaves essentially like the function sequence
             *          SetWriteValue(), WriteAsync().
             *
             * @param           value           Value to be written asynchronously.
             * @param           transactionId   A client provided value to identify the results of
             *                                  asynchronous operations.
             * @param [in,out]  cancelId        Address of a variable where the server stores an identifier
             *                                  which can be used in case the operation needs to be canceled.
             *
             * @return  An Technosoftware::Base::Status&amp;
             */

            Base::Status& WriteAsync(LPVARIANT value, uint32_t transactionId, uint32_t* cancelId);

            /**
             * @fn  void DaItem::Read(bool fromCache = true);
             *
             * @brief   Reads the value, quality and timestamp for this item from the server.
             *          
             *          The read results can be accessed with method ReadResult().
             *
             * @param   fromCache   (Optional) Optional parameter which specifies if the cache or the device
             *                      is used as data source. In general clients should read from cache. Please
             *                      refer to the OPC DA Specification for a general discussion about the
             *                      differences between reading from cache and reading from device.
             */

            void Read(bool fromCache = true);

            /**
             * @fn  Base::Status& DaItem::ReadAsync(uint32_t transactionId, uint32_t* cancelId);
             *
             * @brief   Reads the value, quality and timestamp for this item asynchronously.
             *          
             *          The results are returned via the DaIDataCallback::ReadComplete() notification if this
             *          function succeeds. If there is no Data Callback Subscription this method returns a
             *          Technosoftware::Base::Status with result code 0x80040200.
             *
             * @param           transactionId   A client provided value to identify the results of
             *                                  asynchronous operations.
             * @param [in,out]  cancelId        Address of a variable where the server stores an identifier
             *                                  which can be used in case the operation needs to be canceled.
             *
             * @return  The asynchronous.
             */

            Base::Status& ReadAsync(uint32_t transactionId, uint32_t* cancelId);

            /**
             * @fn  Base::Status& DaItem::Cancel(uint32_t cancelId);
             *
             * @brief   Requests the server to cancel an outstanding asynchronous transaction.
             *          
             *          If this operation succeeds then no callback will occur. If this operation fails then
             *          a callback may already have occurred or will occur because it was to late to cancel
             *          the transaction.
             *
             * @param   cancelId    The server generated identifier which was returned by the asynchronous
             *                      operation to be canceled now.
             *
             * @return  An Technosoftware::Base::Status&amp;
             */

            Base::Status& Cancel(uint32_t cancelId);

        protected:
            friend class DaGroupImpl;
            VARIANT                         writeValue_;

            // Results of I/O Operations
            DaReadResult                    readResult_;
            DaReadResult                    readAsyncResult_;
            DaWriteResult                   writeResult_;
            DaWriteResult                   writeAsyncResult_;
            Base::Status                    asyncCommandResult_;
            unsigned long                   internalClientHandle_;

        private:
            uint16_t                        canonicalDataType_;
            Base::ClientHandle              clientHandle_;
            Base::ServerHandle              serverHandle_;
            uint32_t                        accessRights_;
            DaGroupImpl*                    parent_;
        };
    }
}

#endif /* TECHNOSOFTWARE_DAITEM_H */
