/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * OPC DA Sample Client
 *
 * License:
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

 //-----------------------------------------------------------------------------
 // INCLUDES
 //-----------------------------------------------------------------------------
#include <iostream>
#include <functional>
#include <tchar.h> 
#include <string>
#include <vector>

#include "DaAeHdaClient/OpcClientSdk.h"

#include "Base/DateTimeFormat.h"
#include "Base/DateTimeFormatter.h"
#include "Base/Exception.h"

using namespace Technosoftware::Base;
using namespace Technosoftware::DaAeHdaClient;

/**
 * @class   MyDataCallbackClass
 *
 * @brief   The data callback omplementation.
 */

class MyDataCallbackClass : public Technosoftware::DaAeHdaClient::DaIDataCallback
{
public:
    // Called by the DaFramwork
    void DataChange(uint32_t                                    transactionId,
        Technosoftware::DaAeHdaClient::DaGroup*                     groupHandle,
        bool                                                    allQualitiesGood,
        bool                                                    allResultsOk,
        uint32_t                                                numberOfItems,
        Technosoftware::DaAeHdaClient::DaItem**                     items);

    void ReadComplete(uint32_t                                  transactionId,
        Technosoftware::DaAeHdaClient::DaGroup*                     groupHandle,
        bool                                                    allQualitiesGood,
        bool                                                    allResultsOk,
        uint32_t                                                numberOfItems,
        Technosoftware::DaAeHdaClient::DaItem**                     items)
    {}                      // not used by this sample application

    void WriteComplete(uint32_t                                 transactionId,
        Technosoftware::DaAeHdaClient::DaGroup*                     groupHandle,
        bool                                                    allResultsOk,
        uint32_t                                                numberOfItems,
        Technosoftware::DaAeHdaClient::DaItem**                     items)
    {}                      // not used by this sample application

    void CancelComplete(uint32_t    dwTransactionID,
        Technosoftware::DaAeHdaClient::DaGroup*                     groupHandle)
    {}                      // not used by this sample application
};

/**
 * @fn  void MyDataCallbackClass::DataChange( uint32_t transactionId, Technosoftware::DaAeHdaClient::DaGroup* groupHandle, bool allQualitiesGood, bool allResultsOk, uint32_t numberOfItems, Technosoftware::DaAeHdaClient::DaItem** items)
 *
 * @brief   Receives data changes from the added items.
 *
 * @param   transactionId       Identifier for the transaction.
 * @param [in,out]  groupHandle If non-null, the group.
 * @param   allQualitiesGood    true to all qualities good.
 * @param   allResultsOk        true if all results operation was a success, false if it failed.
 * @param   numberOfItems       Number of items.
 * @param [in,out]  items       If non-null, the items.
 */

void MyDataCallbackClass::DataChange(
    uint32_t                                                    transactionId,
    Technosoftware::DaAeHdaClient::DaGroup*                         groupHandle,
    bool                                                        allQualitiesGood,
    bool                                                        allResultsOk,
    uint32_t                                                    numberOfItems,
    Technosoftware::DaAeHdaClient::DaItem**                         items)
{
    cout << "DataChange():" << endl
        << "Transaction ID: " << transactionId << endl
        << "All Qualities Good ? " << (allQualitiesGood ? "yes" : "no") << endl
        << "All Results Ok ? " << (numberOfItems ? "yes" : "no") << endl;

    Technosoftware::DaAeHdaClient::DaItem* pItem;
    while (numberOfItems--) {
        pItem = items[numberOfItems];
        cout << endl << "Client Handle : " << pItem->GetClientHandle() << endl;
        if (pItem->GetReadAsyncResult().GetResult().IsGood()) {
            cout << "Value         : " << V_I4(pItem->GetReadAsyncResult().GetValue()) << endl;
            cout << "Time Stamp    : " << DateTimeFormatter::Format(pItem->GetReadAsyncResult().GetTimeStamp(), DateTimeFormat::ISO8601_FORMAT) << endl;
            cout << "Quality       : " << pItem->GetReadAsyncResult().GetQualityAsText() << endl;
        }
        else {
            Technosoftware::Base::Status hresult = pItem->GetReadAsyncResult().GetResult();
            cout << "Result        : " << hresult.ToString() << endl;
        }
    }
    cout << endl << endl;
}


//-----------------------------------------------------------------------------
// This handler is called for all items which cannot be added successfully.
//-----------------------------------------------------------------------------
auto AddItemErrHandler = [](const Technosoftware::DaAeHdaClient::DaItemDefinition& itemDef, Technosoftware::Base::Status res)
{
    cout << "   Cannot add item '" << itemDef.ItemIdentifier << "': " << res.ToString() << endl;
};


//-----------------------------------------------------------------------------
// Simple OPC DA Client Application
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    try {
        Technosoftware::Base::Status                status;
        Technosoftware::DaAeHdaClient::DaServer     myDaServer;
        MyDataCallbackClass                     myDataCallback;
        string                                  serverName("Technosoftware.DaSample");
        //string                                  serverName("Technosoftware.DaSimpleSample");
        string                                  ipAddress("localhost");

        cout << endl
             << "Simple OPC DA Client based on the Technosoftware Client SDK C++" << endl
             << "-----------------------------------------------------------" << endl;
        cout << "   Press <Enter> to connect to " << serverName << " on machine" << endl
             << "   with IP address " << ipAddress;
        cin.get();
        cout << "   Please wait..." << endl;

        status = myDaServer.Connect(serverName, ipAddress);
        if (status.IsNotGood()) {
            cout << "Cannot connect: " << status.ToString() << endl;
            return 1;
        }

        DaServerStatus& daServerstatus = myDaServer.GetStatus();

        int maxLoops = 100;

        cout << "   Connected, press <Enter> to loop " << maxLoops << " times over " << endl;
        cout << "       1. create an active group object, add two items." << endl;
        cout << "       2. Add two items." << endl;
        cout << "       3. Write a value to one of the items." << endl;
        cout << "       4. Delete group." << endl;
        cin.get();

        Technosoftware::Base::Timestamp start = Technosoftware::Base::Timestamp();
        for (int i = 0; i < maxLoops; i++) {
            DaGroup* daGroup = new DaGroup(&myDaServer, "OPC TestGroup", true, 1000);  // active, refresh rate 1s
            if (!daGroup) {
                cout << "   Cannot create group." << endl;
                return 1;
            }

            vector<Technosoftware::DaAeHdaClient::DaItem*>      addedItems;
            Technosoftware::DaAeHdaClient::DaItemDefinitions    daItemDefinitions;

            status = daItemDefinitions.Add("CTT.SimpleTypes.InOut.Integer", 100);
            if (status.IsGood()) {
                status = daItemDefinitions.Add("SimulatedData.Random", 150);
            }
            if (status.IsNotGood()) {
                cout << "   Cannot add item definition to the item definition list: " << status.ToString() << endl;
                return 1;
            }
            status = daGroup->AddItems(daItemDefinitions, addedItems, AddItemErrHandler);
            if (!status.IsGood()) {
                cout << "   Cannot add all items: " << status.ToString() << endl;
                return 1;
            }

            // Write a value to SimpleTypes.InOut.Integer
            vector<DaItem*> writeItems;
            writeItems.push_back(addedItems[0]);
            VARIANT     varValue;
            V_VT(&varValue) = VT_INT;
            varValue.intVal = i;
            status = writeItems[0]->SetWriteValue(&varValue);
            if (status.IsGood())
            {
                status = daGroup->Write(writeItems);
                if (status.IsNotGood())
                {
                    cout << "   Cannot write value: " << status.ToString() << endl;
                }
                else
                {
                    cout << "   Written value: " << i << " " << status.ToString() << endl;
                }
            }
            else
            {
                cout << "   Cannot set value to be written: " << status.ToString() << endl;
            }
            delete daGroup;
        }
        Technosoftware::Base::Timestamp::TimeDiff elapsed = start.GetElapsed();
        double secondsPerCall = elapsed / 1000.00 / 1000.00 / maxLoops;
        cout << "   Seconds per call " << secondsPerCall << endl;

        // Read several items from cache
        //res = pGroup->Read(arAddedItems);

        // Read a specific item from cache
        //arAddedItems[0]->Read();

        //arAddedItems[0]->GetReadResult().GetValue();

        cout << "   Press <Enter> to activate a subscription and press <Enter> again to deactivate it." << endl;
        cin.get();

        DaGroup* daGroup = new DaGroup(&myDaServer, "OPC TestGroup", true, 1000);  // active, refresh rate 1s
        if (!daGroup) {
            cout << "   Cannot create group." << endl;
            return 1;
        }

        vector<Technosoftware::DaAeHdaClient::DaItem*>      addedItems;
        Technosoftware::DaAeHdaClient::DaItemDefinitions    daItemDefinitions;

        status = daItemDefinitions.Add("CTT.SimpleTypes.InOut.Integer", 100);
        if (status.IsGood()) {
            status = daItemDefinitions.Add("1SimulatedData.Random", 150);
        }
        if (status.IsNotGood()) {
            cout << "   Cannot add item definition to the item definition list: " << status.ToString() << endl;
            return 1;
        }
        status = daGroup->AddItems(daItemDefinitions, addedItems, AddItemErrHandler);
        if (!status.IsGood()) {
            cout << "   Cannot add all items: " << status.ToString() << endl;
            return 1;
        }

        // Activate subscription
        status = daGroup->SetDataSubscription(&myDataCallback);
        if (status.IsNotGood()) {
            cout << "   Cannot set data subscription: " << status.ToString() << endl;
            return 1;
        }

        cin.get();
        status = daGroup->SetDataSubscription(NULL);
        cout << "   Data change subscription deactivated, press <Enter> to remove all" << endl
             << "   and disconnect from the server.";
        delete daGroup;
        myDaServer.Disconnect();
        cin.get();
        cout << "   Disconnected from the server." << endl << endl;
    }
    catch (Technosoftware::Base::StatusException e) {
        cout << "Error occured: " << e.GetStatus().ToString() << endl;
    }
    catch (Technosoftware::Base::Exception e) {
        cout << "Error occured: " << e.GetDisplayText() << endl;
    }
    catch (std::bad_alloc) {
        cout << "Error occured: Ran out of memory" << endl;
    }
    catch (...) {
        cout << "Error occured" << endl;
    }
    return 0;
}
