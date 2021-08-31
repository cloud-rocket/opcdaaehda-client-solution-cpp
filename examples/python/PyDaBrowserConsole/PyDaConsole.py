# MIT License
# 
# Copyright (c) 2021 Meir Tseitlin
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import inspect
from opcdaaehdaclient import Status, DaServer,DaBrowseElementFilter, DaBrowseFilters, DaBrowser, DaGroup, DaItemDefinitions, DaItems, DaItem

#-----------------------------------------------------------------------------
# This handler is called for all items which cannot be added successfully.
#-----------------------------------------------------------------------------
def AddItemErrHandler(itemDef, res):
    print(f"   Python Cannot add item '{itemDef.ItemIdentifier}': {res}")

def main():

    serverName = "Matrikon.OPC.Simulation.1"
    #serverName = "Technosoftware.DaSample"
    ipAddress = "localhost"


    print("Simple OPC DA Client based on the Technosoftware Client SDK Python")

    myDaServer = DaServer()

    status = myDaServer.Connect(serverName, ipAddress)

    if status.IsNotGood():
        print(f"Cannot connect: {status}")
        return 1

    daServerstatus = myDaServer.GetStatus()

    print(f"Server Vendor: {daServerstatus.GetVendorInfo()}")

    maxLoops = 1


    for i in range(0, maxLoops):

        try:
            daGroup = DaGroup(myDaServer, 'OPC TestGroup', True, 1000)

            addedItems = DaItems()
            daItemDefinitions = DaItemDefinitions()

            status = daItemDefinitions.Add("Random.Real8", 100)
            if status.IsGood():
                status = daItemDefinitions.Add("Random1.Real4", 150)

            if status.IsNotGood():
                    print(f"   Cannot add item definition to the item definition list: {status}")
                    return 1




            status = daGroup.AddItems(daItemDefinitions, addedItems, AddItemErrHandler)
            if not status.IsGood() :
                print(f"   Cannot add all items: {status}" )
                return 1

            print('returning')

            # Write values
            writeItems = DaItems()
            writeItems.append(addedItems[0])

            #p = tagVARIANT()

            #writeItems[0].SetWriteValue(i)

        finally:
            del daGroup

    return

    # Subscription
    try:
        daGroup = DaGroup(myDaServer, 'OPC TestGroup', True, 1000)

        addedItems = DaItems()
        daItemDefinitions = DaItemDefinitions()

        status = daItemDefinitions.Add("Random.Int4", 100)
        if status.IsGood():
            status = daItemDefinitions.Add("Random.Real4", 150)

        if status.IsNotGood():
                print(f"   Cannot add item definition to the item definition list: {status}")
                return 1

        status = daGroup.AddItems(daItemDefinitions, addedItems, AddItemErrHandler)
        if not status.IsGood() :
            print(f"   Cannot add all items: {status}" )
            return 1


        # Read items from cache
        status = daGroup.Read(addedItems);
        if not status.IsGood() :
            print(f"   Cannot read all items: {status}" )
            return 1

        for item in addedItems:
            print(f'{item.Name()}    |    {item.GetClientHandle()}    |    {item.GetReadResult().GetTimeStamp().GetEpochTime()}     |     {item.GetReadResult().GetValue()}')

            item.SetWriteValue(5)

        daGroup.Write(addedItems)


        # Activate subscription
        #status = daGroup.SetDataSubscription()
        #if status.IsNotGood():

        #    print(f"   Cannot set data subscription: {status}")
        #    return 1

    finally:
        del daGroup


if __name__ == '__main__':

    main()