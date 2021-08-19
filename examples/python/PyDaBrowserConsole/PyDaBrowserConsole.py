
from opcdaaehdaclient import Status, DaServer,DaBrowseElementFilter, DaBrowseFilters, DaBrowser


def ShowProperties(properties):

    for prop in properties:
        if prop.GetResult().IsGood():
            print(f'> {prop.GetId()}, {prop.GetDescription()}, {prop.GetDataTypeAsText()}, {prop.GetItemId() if prop.GetItemId() else ""}')
        else:
            print(f"some error occurred in {prop.GetId()}")

def ShowElements(daBrowser):

     succeeded = True
     els = daBrowser.GetElements()

     for el in els:

        if el.HasChildren():
            print(el.GetName())
            ShowProperties(el.GetProperties())
            status = daBrowser.Browse(el.GetItemId())
            if status.IsNotGood():
                print(f'Cannot browse the Server Address Space: {status}')
                succeeded = False;
            else:
                succeeded = ShowElements(daBrowser)

            if not succeeded:
                break
        else:
            print(f'- {el.GetName()}')
            ShowProperties(el.GetProperties())

if __name__ == '__main__':

    serverName = "Matrikon.OPC.Simulation.1"
    #serverName = "Technosoftware.DaSample"
    ipAddress = "localhost"

    myDaServer = DaServer()


    #myDaServer.UpdateStatus()

    status = myDaServer.Connect(serverName, ipAddress);
    if status.IsNotGood():
        print(f"Cannot connect: {status}")
    else:

        daBrowseFilters = DaBrowseFilters(DaBrowseElementFilter.All, '', '', 0, True, True)

        daBrowser = DaBrowser(myDaServer, daBrowseFilters)

        properties = daBrowser.GetProperties("Random.Int1");
        #properties = daBrowser.GetProperties("SpecialItems.WithAnalogEUInfo");

        ShowProperties(properties);

        status = daBrowser.Browse("")
        if status.IsNotGood():
            print(f"Cannot browse the Server Address Space: {status}")

        els = daBrowser.GetElements();

        ShowElements(daBrowser)

        # This is needed to enforce order distruction (instead of new/delete in C++)
        del daBrowser

        myDaServer.Disconnect()




