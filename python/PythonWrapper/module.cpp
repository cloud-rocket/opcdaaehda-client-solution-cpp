// https://docs.microsoft.com/en-us/visualstudio/python/working-with-c-cpp-python-in-visual-studio?view=vs-2019

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include "DaAeHdaClient/OpcClientSdk.h"

using namespace Technosoftware::Base;
using namespace Technosoftware::DaAeHdaClient;

namespace py = pybind11;


PYBIND11_MODULE(opcdaaehdaclient, m) {

    py::class_<OpcObject, std::unique_ptr<OpcObject, py::nodelete>> opcObject(m, "OpcObject");
    opcObject.def("Name", &OpcObject::Name);


    py::class_<Status>(m, "Status", opcObject)
        .def(py::init<>())
        .def("IsError", &Status::IsError)
        .def("IsSuccess", &Status::IsSuccess)
        .def("IsOk", &Status::IsOk)
        .def("IsUncertain", &Status::IsUncertain)
        .def("IsGood", &Status::IsGood)
        .def("IsBad", &Status::IsBad)
        .def("IsNotUncertain", &Status::IsNotUncertain)
        .def("IsNotGood", &Status::IsNotGood)
        .def("IsNotBad", &Status::IsNotBad)
        .def("__str__", &Status::ToString);

    py::class_<DaServerStatus, std::unique_ptr<DaServerStatus, py::nodelete>>(m, "DaServerStatus", opcObject)
        .def("GetStartTime", &DaServerStatus::GetStartTime)
        //.def("GetCurrentTime", &DaServerStatus::GetCurrentTime)
        .def("GetLastUpdateTime", &DaServerStatus::GetLastUpdateTime)
        .def("GetServerState", &DaServerStatus::GetServerState)
        .def("GetGroupCount", &DaServerStatus::GetGroupCount)
        .def("GetBandWidth", &DaServerStatus::GetBandWidth)
        .def("GetMajorVersion", &DaServerStatus::GetMajorVersion)
        .def("GetMinorVersion", &DaServerStatus::GetMinorVersion)
        .def("GetBuildNumber", &DaServerStatus::GetBuildNumber)
        .def("GetReserved", &DaServerStatus::GetReserved)
        .def("GetVendorInfo", &DaServerStatus::GetVendorInfo);


    py::class_<DaServer>(m, "DaServer", opcObject)
        .def(py::init<>())
        .def("GetStatus", &DaServer::GetStatus, py::return_value_policy::reference)
        .def("IsConnected", &DaServer::IsConnected)
        .def("Connect", &DaServer::Connect, 
            R"pbdoc(Connects the object to an OPC Data Access Server)pbdoc", 
            py::arg("serverName"), 
            py::arg("machineName") = "", 
            py::arg("coInit") = 0)
        //.def_static("Connect", static_cast<Technosoftware::Base::Status(const std::string&, const std::string&, uint32_t coInit)> (&Technosoftware::DaAeHdaClient::DaServer::Connect))
        .def("Disconnect", &DaServer::Disconnect)
        .def("UpdateStatus", &DaServer::UpdateStatus)
        .def("RegisterClientName", &DaServer::RegisterClientName);


    py::enum_<DaBrowseElementFilter>(m, "DaBrowseElementFilter")
        .value("All", DaBrowseElementFilter::All, "All type of elements are returned.")
        .value("Branches", DaBrowseElementFilter::Branches, " Only elements with children elements are returned.")
        .value("Items", DaBrowseElementFilter::Items, " Only elements with children elements are returned.")
        .export_values();

    py::class_<DaBrowseFilters>(m, "DaBrowseFilters", opcObject)
        .def(py::init<DaBrowseElementFilter, const string&, const string&, uint32_t, bool, bool, VARTYPE, uint32_t>(),
            R"pbdoc(Constructs a DaBrowseFilters object.)pbdoc", 
            py::arg("browseElementFilter")=DaBrowseElementFilter::All,
            py::arg("elementNameFilter")="",
            py::arg("vendorFilter")="",
            py::arg("maxElementsReturned")=0,
            py::arg("returnAllProperties")=false,
            py::arg("returnPropertyValues")=false,
            py::arg("dataTypeFilter")=0, // VT_EMPTY
            py::arg("accessRightsFilter")= OPC_READABLE + OPC_WRITEABLE
        );
       
    py::class_<DaBrowseElement>(m, "DaBrowseElement", opcObject)
        .def(py::init<const DaBrowseElement&>())
        .def("GetName", &DaBrowseElement::GetName)
        .def("GetItemId", &DaBrowseElement::GetItemId)
        .def("IsItem", &DaBrowseElement::IsItem)
        .def("HasChildren", &DaBrowseElement::HasChildren)
        .def("GetProperties", &DaBrowseElement::GetProperties);

    py::class_<DaBrowser>(m, "DaBrowser", opcObject)
        .def(py::init<DaServer*, DaBrowseFilters*>(),
            R"pbdoc(Constructs a DaBrowser object.)pbdoc",
            py::arg("parent"),
            py::arg("filters") = nullptr)
        .def("GetElements", &DaBrowser::GetElements, "Allows the access to the Server Address Space elements returned by the last Browse() resp.BrowseNext() function call.")
        .def("GetFilters", &DaBrowser::GetFilters, "The currently used filters.")
        .def("HasMoreElements", &DaBrowser::HasMoreElements, "Indicates if Elements() contains all available elements from the current position or not.")
        .def("IsBrowse2Used", &DaBrowser::IsBrowse2Used)
        .def("IsBrowse3Used", &DaBrowser::IsBrowse3Used)
        .def("Browse", &DaBrowser::Browse)
        .def("BrowseNext", &DaBrowser::BrowseNext)
        .def("SetFilters", &DaBrowser::SetFilters)
        .def("GetPropertyValueAsText", &DaBrowser::GetPropertyValueAsText)
        .def("GetProperties", &DaBrowser::GetProperties);

    py::enum_<OpcTextMode>(m, "OpcTextMode")
        .value("Valuename", OpcTextMode::Valuename, "The returned text string represents the name of the value as it was defined in accordance with the appropriate OPC Specification.")
        .value("Uppercase", OpcTextMode::Uppercase, " All characters in the returned text string are uppercase.")
        .value("Lowercase", OpcTextMode::Lowercase, "All characters in the returned text string are lowercase.")
        .value("Capitalize", OpcTextMode::Lowercase, "The first character of the returned text string is a capital letter.")
        .export_values();

    py::class_<DaItemProperty>(m, "DaItemProperty", opcObject)
        .def(py::init<>())
        .def("GetId", &DaItemProperty::GetId)
        .def("GetDescription", &DaItemProperty::GetDescription)
        .def("GetDataType", &DaItemProperty::GetDataType)
        .def("GetValue", &DaItemProperty::GetValue)
        .def("GetItemId", &DaItemProperty::GetItemId)
        .def("GetResult", &DaItemProperty::GetResult)
        .def("GetDataTypeAsText", &DaItemProperty::GetDataTypeAsText, "Returns the Data Type as text string.", py::arg("textMode") = OpcTextMode::Capitalize)
        .def("GetValueAsText", &DaItemProperty::GetValueAsText)
        .def("GetValueAsText", &DaItemProperty::GetValueAsText);

    py::class_<DaItemDefinitions>(m, "DaItemDefinitions", opcObject)
        .def(py::init<OpcObject*>(), 
            R"pbdoc(Constructs a DaItemDefinitions object.)pbdoc",
            py::arg("parent") = nullptr)
        .def("Add", &DaItemDefinitions::Add,
            R"pbdoc(Adds the definitions of a new Item instance.)pbdoc",
            py::arg("itemIdentifier"),
            py::arg("clientHandle") = 0,
            py::arg("requestedDataType") = 0, //VT_EMPTY,
            py::arg("isActive") = true,
            py::arg("accessPath") = nullptr,
            py::arg("blobSize") = 0,
            py::arg("blob") = nullptr)
        .def("RemoveAll", &DaItemDefinitions::RemoveAll);

    py::class_<DaItem, std::unique_ptr<DaItem, py::nodelete>>(m, "DaItem", opcObject)
        .def("GetCanonicalDataType", &DaItem::GetCanonicalDataType)
        .def("GetClientHandle", &DaItem::GetClientHandle)
        .def("GetServerHandle", &DaItem::GetServerHandle)
        .def("GetAccessRights", &DaItem::GetAccessRights);

    py::class_<DaGroup>(m, "DaGroup", opcObject)
        .def(py::init<DaServer*, const char*, bool, uint32_t, ClientHandle, long*, float*, uint32_t>(),
            R"pbdoc(Constructs a DaGroup object.)pbdoc",
            py::arg("parent"),
            py::arg("name") = nullptr,
            py::arg("active") = true,
            py::arg("requestedUpdateRate") = 0,
            py::arg("handleClientGroup") = 0xFFFFFFFF,
            py::arg("timeBias") = nullptr,
            py::arg("percentDeadband") = nullptr,
            py::arg("lcId") = 0x800)
        .def("IsActive", &DaGroup::IsActive, R"pbdoc(Indicates the current active state of the group object.)pbdoc")
        .def("IsEnabled", &DaGroup::IsEnabled, R"pbdoc(Indicates if data change notifications via the Data Change Subscription are enabled or disabled.)pbdoc")
        .def("HasDataSubscription", &DaGroup::HasDataSubscription, R"pbdoc(Indicates if the Data Change Subscription of this group object has been activated.)pbdoc")
        .def("GetRevisedUpdateRate", &DaGroup::GetRevisedUpdateRate, R"pbdoc(The revised update rate of the group object in milliseconds.)pbdoc")
        .def("GetServerHandle", &DaGroup::GetServerHandle, R"pbdoc(The server handle of the group object.)pbdoc")
        .def("GetClientHandle", &DaGroup::GetClientHandle, R"pbdoc(The client handle of the group object.)pbdoc")
        .def("SetActive", &DaGroup::SetActive, R"pbdoc(Sets the active state of the group object.)pbdoc")
        //.def("AddItems", &DaGroup::AddItems, R"pbdoc(Adds items to the group object.)pbdoc")
        .def("Read", &DaGroup::Read, R"pbdoc(Reads the value, quality and timestamp of the specified items.)pbdoc")
        .def("Write", &DaGroup::Write, R"pbdoc(Writes the values of the specified items.)pbdoc")
        .def("SetDataSubscription", &DaGroup::SetDataSubscription, R"pbdoc(Activates or inactivate's the Data Change Subscription of this group object.)pbdoc")
        .def("ReadAsync", &DaGroup::ReadAsync, R"pbdoc(Reads the value, quality and timestamp of the specified items asynchronously.)pbdoc")
        .def("WriteAsync", &DaGroup::WriteAsync, R"pbdoc(Writes the values of the specified items asynchronously.)pbdoc")
        .def("SetEnable", &DaGroup::SetEnable, R"pbdoc(Enables or disables data change notifications via the Data Change Subscription.)pbdoc")
        .def("Cancel", &DaGroup::Cancel, R"pbdoc(Requests the server to cancel an outstanding asynchronous transaction.)pbdoc")
        .def("Refresh", &DaGroup::Refresh, R"pbdoc(Forces a data change notification for all active items.)pbdoc")
        ;




#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
