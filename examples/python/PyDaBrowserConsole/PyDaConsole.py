import inspect
from opcdaaehdaclient import Status, DaServer,DaBrowseElementFilter, DaBrowseFilters, DaBrowser, DaGroup, DaItemDefinitions


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

        maxLoops = 100


        daGroup = DaGroup(myDaServer, 'OPC TestGroup', True, 1000)

        daItemDefinitions = DaItemDefinitions()


        #status = daItemDefinitions.Add("CTT.SimpleTypes.InOut.Integer")