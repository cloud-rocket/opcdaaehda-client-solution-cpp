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




