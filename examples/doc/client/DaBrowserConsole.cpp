/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * OPC DA Sample Client showing th usage of the DaBrowser class.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

//-----------------------------------------------------------------------------
// INCLUDES
//-----------------------------------------------------------------------------
#include <iostream>
#include <tchar.h>  
#include "DaAeHdaClient/OpcClientSdk.h"
#include "Base/Exception.h"

using namespace Technosoftware::Base;
using namespace Technosoftware::DaAeHdaClient;

//-----------------------------------------------------------------------------
// ShowProperties
// --------------
//    Shows the properties of the specified browse object.
//-----------------------------------------------------------------------------
void ShowProperties(DaItemProperties& properties, int nestingCount)
{
    for (int i = 0; i < properties.size(); i++) {
        // Insert blanks to show the properties related to its owner element
        for (int tab = 0; tab < nestingCount + 1; tab++) cout << "   ";

        DaItemProperty* pProp = &properties[i];
        if (pProp->GetResult().IsGood()) {
            cout << "> " << pProp->GetId()
                << ", " << pProp->GetDescription()
                << ", " << pProp->GetDataTypeAsText()
                << " (" << pProp->GetDataTypeAsText() << ")";
            //<< ", " << (pProp->GetValueAsText().length() ? pProp->ValueAsText().c_str() : "<no value>");

            if (pProp->GetItemId().length()) {
                cout << ", " << pProp->GetItemId();
            }
            cout << endl;
        }
        else {
            // Note: pProp->ID() is always valid, also in case of error
            cout << "some error occurred in " << pProp->GetId() << endl;
            //         cout  << "> " << pProp->ID() << ", Error Item Property: " << pProp->Result() << endl;
        }
    }
}


//-----------------------------------------------------------------------------
// ShowElements
// ------------
//    Shows the element names of the specified browse object and browses all branches. This function may be called
//    recursively. If an error occurs a message will be displayed and the function returns with 'false'; otherwise
//    the function returns with 'true'.
//-----------------------------------------------------------------------------
bool ShowElements(DaBrowser* daBrowser)
{
    static int                      nestingCount = 0;      // Used to show the element names in a hierarchy
    bool                            succeeded = true;
    Technosoftware::Base::Status        status;
    // Make a copy of the current elements because these
    // are modified by the next Browse() call
    DaBrowseElements  els = daBrowser->GetElements();

    nestingCount++;

    for (int i = 0; i < els.size(); i++) {      // Handle all elements

        // Insert blanks to show the element names in a hierarchy
        for (int tab = 0; tab < nestingCount; tab++) cout << "   ";

        if (els[i].HasChildren()) {               // The element has children
            cout << "+ " << els[i].GetName() << endl; // Show the element name and browse the branch
            ShowProperties(els[i].GetProperties(), nestingCount);
            status = daBrowser->Browse(els[i].GetItemId());
            if (status.IsNotGood()) {
                cout << "Cannot browse the Server Address Space: " << status.ToString() << endl;
                succeeded = false;
            }
            else {
                succeeded = ShowElements(daBrowser);
            }
            if (!succeeded) break;                // Stop browsing if an error occured
        }
        else {                                    // The element has no children
            cout << "- " << els[i].GetName() << endl; // Show the item name
            // Show the item properties
            ShowProperties(els[i].GetProperties(), nestingCount);
        }
    }

    nestingCount--;
    return succeeded;
}


//-----------------------------------------------------------------------------
// Simple OPC Server Address Space Browser
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    try {
        Technosoftware::Base::Status                status;
        Technosoftware::DaAeHdaClient::DaServer     myDaServer;
        string                                  serverName("Technosoftware.DaSample");
        //string                                  serverName("Technosoftware.DaSimpleSample");
        string                                  ipAddress("localhost");

        cout << endl
             << "Simple OPC Server Address Space Browser based on the Technosoftware Client SDK C++" << endl
             << "------------------------------------------------------------------------------" << endl;
        cout << "   Press <Enter> to connect to " << serverName << " on machine" << endl
            << "   with IP address " << ipAddress;
        cin.get();
        cout << "   Please wait..." << endl;

        if (Technosoftware::DaAeHdaClient::LicenseHandler::IsExpired())
        {
            cout << Technosoftware::DaAeHdaClient::LicenseHandler::GetLicenseStatus();
            return 1;
        }

        status = myDaServer.Connect(serverName, ipAddress);
        if (status.IsNotGood()) {
            cout << "Cannot connect: " << status.ToString() << endl;
            return 1;
        }

        cout << "   Connected, press <Enter> to show the Server Address Space." << endl;
        cin.get();

        DaBrowseFilters daBrowseFilters(
            DaBrowseElementFilter::All, "", "", 0,         // Default filters
            true,                   // Return all properties
            true);                  // Return property vlaues

        DaBrowser* daBrowser = new DaBrowser(&myDaServer, &daBrowseFilters);
        if (!daBrowser) throw std::bad_alloc();    // Whether this test is necessary depends on the used compiler options

        // Get the item properties of a specific item
        DaItemProperties& properties = daBrowser->GetProperties("SpecialItems.WithAnalogEUInfo");
        ShowProperties(properties, 1);

        status = daBrowser->Browse("");             // Start browsing at root
        if (status.IsNotGood()) {
            cout << "   Cannot browse the Server Address Space: " << status.ToString() << endl;
            return 1;
        }
        DaBrowseElements  els = daBrowser->GetElements();

        if (ShowElements(daBrowser)) {           // Show the element names and browse all branches
            cout << endl
                << "   Server Address Space displayed, press <Enter> to" << endl
                << "   disconnect from the server.";
            cin.get();
        }
        delete daBrowser;

        myDaServer.Disconnect();
    }
    catch (Technosoftware::Base::StatusException e) {
        cout << "Error occured: " << e.GetStatus().ToString() << endl;
    }
    catch (Technosoftware::Base::Exception e) {
        cout << "Error occured: " << e.GetDisplayText() << endl;
    }
    catch (...) {
        cout << "Error occured" << endl;
    }
    return 0;
}
