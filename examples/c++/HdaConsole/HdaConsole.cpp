/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * OPC HDA Sample Client
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
