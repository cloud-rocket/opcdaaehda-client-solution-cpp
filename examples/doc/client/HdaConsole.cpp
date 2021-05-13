/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * OPC HDA Sample Client
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */


 //-----------------------------------------------------------------------------
 // INCLUDES
 //-----------------------------------------------------------------------------
#include <iostream>
using namespace std;
#include <tchar.h> 
#include "DaAeHdaClient/OpcClientSdk.h"
#include "Base/DateTime.h"
#include "Base/Exception.h"

using namespace Technosoftware::Base;
using namespace Technosoftware::DaAeHdaClient;

//-----------------------------------------------------------------------------
// Simple OPC HDA Client Application
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    try {
        Technosoftware::Base::Status                status;
        Technosoftware::DaAeHdaClient::HdaServer    myHdaServer;
        string                                  serverName("OPCSample.OpcHdaServer");
        string                                  ipAddress("localhost");
        char*                                   itemId("Static Data/Ramp [15 min]");
        HdaItem                                 hdaItem;
        HRESULT                                 error;

        Technosoftware::Base::DateTime              startDateTime;
        Technosoftware::Base::DateTime              endDateTime;

        cout << endl
             << "Simple OPC HDA Client based on the Technosoftware Client SDK C++" << endl
             << "------------------------------------------------------------" << endl;
        cout << "   Press <Enter> to connect to " << serverName << " on machine" << endl
             << "   with IP address " << ipAddress;
        cin.get();
        cout << "   Please wait..." << endl;

        if (LicenseHandler::IsExpired())
        {
            cout << LicenseHandler::GetLicenseStatus();
            return 1;
        }

        status = myHdaServer.Connect(serverName, ipAddress);
        if (status.IsNotGood()) {
            cout << "Cannot connect: " << status.ToString() << endl;
            return 1;
        }

	cout << "   Connected, press <Enter> to get the supported aggregates " << "." << endl;

	HdaAggregates aggregates;
	status = myHdaServer.GetAggregates(aggregates);

	HdaItemAttributes itemAttributes;
	status = myHdaServer.GetItemAttributes(itemAttributes);

        cout << "   Press <Enter> to read the raw data from item " << itemId << "." << endl;
        cin.get();
        startDateTime.Assign(2016, 1, 1, 0, 0, 0, 0, 0);
        endDateTime.Assign(2016, 1, 1, 1, 0, 0, 0, 0);

        status = myHdaServer.ReadRaw(itemId, startDateTime.GetTimestamp(), endDateTime.GetTimestamp(), 0, false, &hdaItem, &error);

        if (status.IsNotGood()) {
            cout << "Cannot read raw data: " << status.ToString() << endl;
            return 1;
        }
        else
        {
            // if data exists
            if (error == S_OK)
            {
                for (DWORD index = 0L; index < hdaItem.Count; index++)
                {
                    // hdaItem.Qualities[index];
                    // hdaItem.TimeStamps[index];
                    // hdaItem.DataValues[index];
                }
            }
        }

        // Cleanup
        if (hdaItem.Count > 0) {
            delete hdaItem.Qualities;
            delete hdaItem.TimeStamps;
            delete hdaItem.DataValues;
        }

        cout << "   Press <Enter> to disconnect from server " << serverName << "." << endl;
        cin.get();

        myHdaServer.Disconnect();
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
