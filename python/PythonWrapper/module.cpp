// https://docs.microsoft.com/en-us/visualstudio/python/working-with-c-cpp-python-in-visual-studio?view=vs-2019

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "DaAeHdaClient/OpcClientSdk.h"

using namespace Technosoftware::Base;
using namespace Technosoftware::DaAeHdaClient;

namespace py = pybind11;


PYBIND11_MODULE(opcdaaehdaclient, m) {
    py::class_<Status>(m, "Status")
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

    py::class_<DaServer>(m, "DaServer")
        .def(py::init<>())
        .def("GetStatus", &DaServer::GetStatus)
        .def("IsConnected", &DaServer::IsConnected)
        .def("Connect", &DaServer::Connect, 
            R"pbdoc(Connects the object to an OPC Data Access Server)pbdoc", 
            py::arg("serverName"), py::arg("machineName") = "", py::arg("coInit") = 0)
        //.def_static("Connect", static_cast<Technosoftware::Base::Status(const std::string&, const std::string&, uint32_t coInit)> (&Technosoftware::DaAeHdaClient::DaServer::Connect))
        .def("Disconnect", &DaServer::Disconnect)
        .def("UpdateStatus", &DaServer::UpdateStatus)
        .def("RegisterClientName", &DaServer::RegisterClientName);


    py::enum_<DaBrowseElementFilter>(m, "DaBrowseElementFilter")
        .value("All", DaBrowseElementFilter::All, "All type of elements are returned.")
        .value("Branches", DaBrowseElementFilter::Branches, " Only elements with children elements are returned.")
        .value("Items", DaBrowseElementFilter::Items, " Only elements with children elements are returned.")
        .export_values();

    py::class_<DaBrowseFilters>(m, "DaBrowseFilters")
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
       
    py::class_<DaBrowseElement>(m, "DaBrowseElement")
        .def(py::init<const DaBrowseElement&>())
        .def("GetName", &DaBrowseElement::GetName)
        .def("GetItemId", &DaBrowseElement::GetItemId)
        .def("IsItem", &DaBrowseElement::IsItem)
        .def("HasChildren", &DaBrowseElement::HasChildren)
        .def("GetProperties", &DaBrowseElement::GetProperties);

    py::class_<DaBrowser>(m, "DaBrowser")
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

    py::class_<DaItemProperty>(m, "DaItemProperty")
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


/*    py::class_<Technosoftware::DaAeHdaClient::DaServerStatus>(m, "DaServerStatus")
        //.def(py::init<>());
        .def("GetStartTime", &Technosoftware::DaAeHdaClient::DaServerStatus::GetStartTime)
        //.def("GetCurrentTime", &Technosoftware::DaAeHdaClient::DaServerStatus::GetCurrentTime)
        .def("GetLastUpdateTime", &Technosoftware::DaAeHdaClient::DaServerStatus::GetLastUpdateTime);
        */

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}


/*PYBIND11_MODULE(opcdaaehdaclient, m) {
    m.def("fast_tanh2", &tanh_impl, R"pbdoc(
        Compute a hyperbolic tangent of a single argument expressed in radians.
    )pbdoc");*/

