import inspect
from opcdaaehdaclient import Status, DaServer,DaBrowseElementFilter, DaBrowseFilters, DaBrowser, DaGroup, DaItemDefinitions

#-----------------------------------------------------------------------------
# This handler is called for all items which cannot be added successfully.
#-----------------------------------------------------------------------------
def AddItemErrHandler(itemDef, res):
    print(f"   Cannot add item '{itemDef.ItemIdentifier}': {res}")



if __name__ == '__main__':

    serverName = "Matrikon.OPC.Simulation.1"
    #serverName = "Technosoftware.DaSample"
    ipAddress = "localhost"


    print("Simple OPC DA Client based on the Technosoftware Client SDK Python")

    myDaServer = DaServer()

    status = myDaServer.Connect(serverName, ipAddress)

    if status.IsNotGood():
        print(f"Cannot connect: {status}")
    else:

        daServerstatus = myDaServer.GetStatus()

        print(f"Server Vendor: {daServerstatus.GetVendorInfo()}")

        maxLoops = 1


        for i in range(0, maxLoops):

            daGroup = DaGroup(myDaServer, 'OPC TestGroup', True, 1000)

            addedItems = []
            daItemDefinitions = DaItemDefinitions()

            status = daItemDefinitions.Add("CTT.SimpleTypes.InOut.Integer", 100)
            if status.IsGood():
                status = daItemDefinitions.Add("SimulatedData.Random", 150)

            if status.IsNotGood():
                 print(f"   Cannot add item definition to the item definition list: {status.ToString()}")


            #status = daGroup.AddItems(daItemDefinitions, addedItems, AddItemErrHandler)
#        if (!status.IsGood()) {
#            cout << "   Cannot add all items: " << status.ToString() << endl;
#            return 1;
#            }

            del daGroup