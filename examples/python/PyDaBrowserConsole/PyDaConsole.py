import inspect
from opcdaaehdaclient import Status, DaServer,DaBrowseElementFilter, DaBrowseFilters, DaBrowser, DaGroup, DaItemDefinitions, DaItems, DaItem

#-----------------------------------------------------------------------------
# This handler is called for all items which cannot be added successfully.
#-----------------------------------------------------------------------------
def AddItemErrHandler(itemDef, res):
    print(f"   Cannot add item '{itemDef.ItemIdentifier}': {res}")

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
                status = daItemDefinitions.Add("Random.Real4", 150)

            if status.IsNotGood():
                    print(f"   Cannot add item definition to the item definition list: {status}")
                    return 1


            status = daGroup.AddItems(daItemDefinitions, addedItems)
            if not status.IsGood() :
                print(f"   Cannot add all items: {status}" )
                return 1


            # Write values
            writeItems = DaItems()
            writeItems.append(addedItems[0])

            #p = tagVARIANT()

            #writeItems[0].SetWriteValue(i)

        finally:
            del daGroup



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

        status = daGroup.AddItems(daItemDefinitions, addedItems)
        if not status.IsGood() :
            print(f"   Cannot add all items: {status}" )
            return 1


        # Read items from cache
        status = daGroup.Read(addedItems);
        if not status.IsGood() :
            print(f"   Cannot read all items: {status}" )
            return 1

        for item in addedItems:
            print(item.GetReadResult().GetTimeStamp().GetEpochTime())
            print(item.GetReadResult().GetValue())

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