// https://docs.microsoft.com/en-us/visualstudio/python/working-with-c-cpp-python-in-visual-studio?view=vs-2019

#define _HAS_STD_BYTE 0

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
//#include <pybind11/chrono.h>
#include "DaAeHdaClient/OpcClientSdk.h"

namespace py = pybind11;

using namespace Technosoftware::Base;
using namespace Technosoftware::DaAeHdaClient;


// Converting from Python types to VARIANT
// https://windowsquestions.com/2020/12/11/expressing-a-python-class-as-a-type-in-stdvariant-in-c-using-pybind11/
//py::object Decimal = py::module_::import("decimal").attr("Decimal");



namespace pybind11 {
    namespace detail {
        template <> struct type_caster<tagVARIANT> {
        public:
            /**
             * This macro establishes the name 'inty' in
             * function signatures and declares a local variable
             * 'value' of type inty
             */
            PYBIND11_TYPE_CASTER(tagVARIANT, _("object"));

            /**
             * Conversion part 1 (Python->C++): convert a PyObject into a inty
             * instance or return false upon failure. The second argument
             * indicates whether implicit conversions should be applied.
             */
            bool load(handle src, bool) {
                /* Extract PyObject from handle */
                PyObject* source = src.ptr();
                /* Try converting into a Python integer value */
                PyObject* tmp = PyNumber_Long(source);
                if (!tmp)
                    return false;
                /* Now try to convert into a C++ int */
                value.lVal = PyLong_AsLong(tmp);
                Py_DECREF(tmp);
                /* Ensure return code was OK (to avoid out-of-range errors etc) */
                return !(value.lVal == -1 && !PyErr_Occurred());
            }

            /**
             * Conversion part 2 (C++ -> Python): convert an inty instance into
             * a Python object. The second and third arguments are used to
             * indicate the return value policy and parent object (for
             * ``return_value_policy::reference_internal``) and are generally
             * ignored by implicit casters.
             */
            static handle cast(VARIANT src, return_value_policy /* policy */, handle /* parent */) {


                switch (src.vt) {
                case VT_EMPTY:
                    return Py_None;

                case VT_BOOL:
                    return PyBool_FromLong(src.boolVal);

                case VT_I2:
                case VT_I4:
                case VT_DECIMAL:
                    return PyLong_FromLong(src.lVal);


                case VT_R4:
                case VT_R8:
                    return PyFloat_FromDouble(src.dblVal);
                default:
                    return  PyLong_FromLong(5);
                }
            }
        };
    }
} // namespace pybind11::detail



using errorHandler = std::function<void(const DaItemDefinition& itemDefinition, Status status)>;

PYBIND11_MAKE_OPAQUE(std::vector<DaItem*>);



class DaGroupTrampoline : public DaGroup {
public:
    using DaGroup::DaGroup; // Inherit the constructors

    Status AddItemsSimple(DaItemDefinitions& itemDefinitions,
        vector<DaItem*>& items) {
        return AddItems(itemDefinitions, items);
    }
};


/*class PyDaIDataCallback : public DaIDataCallback {
public:
    using DaIDataCallback::DaIDataCallback; // Inherit the constructors

    void DataChange(uint32_t        transactionId,
        DaGroup* group,
        bool            allQualitiesGood,
        bool            allResultsOk,
        uint32_t        numberOfItems,
        DaItem** items) override {
            PYBIND11_OVERRIDE_PURE(
                void, // Return type 
                DaIDataCallback,      // Parent class 
                DataChange,          // Name of function in C++ (must match Python name) 
                transactionId,          // Argument(s) 
                group,
                allQualitiesGood,
                allResultsOk,
                numberOfItems,
                items
            );

    }
};
    
    */


  /*  void ReadComplete(uint32_t        transactionId,
        DaGroup* group,
        bool            allQualitiesGood,
        bool            allResultsOk,
        uint32_t        numberOfItems,
        DaItem** items) override {
            PYBIND11_OVERRIDE_PURE(
                void, // Return type 
                DaIDataCallback,      // Parent class 
                DataChange,          // Name of function in C++ (must match Python name) 
                transactionId,          // Argument(s) 
                group,
                allQualitiesGood,
                allResultsOk,
                numberOfItems,
                items
            );

    }*/



PYBIND11_MODULE(opcdaaehdaclient, m) {

    py::class_<OpcObject, std::unique_ptr<OpcObject, py::nodelete>> opcObject(m, "OpcObject");
    opcObject.def("Name", &OpcObject::Name);

    py::bind_vector<std::vector<DaItem*>>(m, "DaItems", py::module_local(false));

    // void(*errorHandler)(const DaItemDefinition& itemDefinition, Base::Status status)

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

    py::class_<Timestamp>(m, "Timestamp")
        .def(py::init<>())
        .def("Swap", &Timestamp::Swap)
        .def("Update", &Timestamp::Update)
        .def("GetEpochTime", &Timestamp::GetEpochTime)
        .def("GetUtcTime", &Timestamp::GetUtcTime)
        .def("GetEpochMicroseconds", &Timestamp::GetEpochMicroseconds)
        .def("GetElapsed", &Timestamp::GetElapsed)
        .def("IsElapsed", &Timestamp::IsElapsed)
        .def("GetRaw", &Timestamp::GetRaw)
        .def("FromEpochTime", &Timestamp::FromEpochTime)
        .def("FromUtcTime", &Timestamp::FromUtcTime)
        .def("GetResolution", &Timestamp::GetResolution)
        .def("FromFileTime", &Timestamp::FromFileTime)
        .def("ToFileTime", &Timestamp::ToFileTime);


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

    //py::class_<DaItemDefinition>(m, "DaItemDefinitions");

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
            py::arg("accessPath") = "",
            py::arg("blobSize") = 0,
            py::arg("blob") = 0)
        .def("RemoveAll", &DaItemDefinitions::RemoveAll);

    py::class_<DaItem::DaReadResult, std::unique_ptr<DaItem::DaReadResult, py::nodelete>>(m, "DaReadResult")
        .def("GetValue", &DaItem::DaReadResult::GetValue)
        .def("GetTimeStamp", &DaItem::DaReadResult::GetTimeStamp)
        .def("GetQuality", &DaItem::DaReadResult::GetQuality)
        .def("GetQualityAsText", &DaItem::DaReadResult::GetQualityAsText)
        .def("GetResult", &DaItem::DaReadResult::GetResult);

    py::class_<DaItem::DaWriteResult, std::unique_ptr<DaItem::DaWriteResult, py::nodelete>>(m, "DaWriteResult")
        .def("Result", &DaItem::DaWriteResult::Result);

    py::class_<DaItem, std::unique_ptr<DaItem, py::nodelete>>(m, "DaItem", opcObject)
        .def("GetCanonicalDataType", &DaItem::GetCanonicalDataType)
        .def("GetClientHandle", &DaItem::GetClientHandle)
        .def("GetServerHandle", &DaItem::GetServerHandle)
        .def("GetAccessRights", &DaItem::GetAccessRights)
        .def("GetReadResult", &DaItem::GetReadResult, py::return_value_policy::reference)
        .def("GetReadAsyncResult", &DaItem::GetReadAsyncResult, py::return_value_policy::reference)
        .def("GetWriteResult", &DaItem::GetWriteResult, py::return_value_policy::reference)
        .def("GetWriteAsyncResult", &DaItem::GetWriteAsyncResult, py::return_value_policy::reference)
        .def("GetAsyncCommandResult", &DaItem::GetAsyncCommandResult)
        .def("SetWriteValue", &DaItem::SetWriteValue)
        .def("Write", py::overload_cast<>(&DaItem::Write))
        .def("Write", py::overload_cast<LPVARIANT>(&DaItem::Write))
        .def("WriteAsync", py::overload_cast<uint32_t, uint32_t*>(&DaItem::WriteAsync))
        .def("WriteAsync", py::overload_cast<LPVARIANT, uint32_t, uint32_t*>(&DaItem::WriteAsync))
        .def("Read", &DaItem::Read)
        .def("ReadAsync", py::overload_cast<uint32_t, uint32_t*>(&DaItem::ReadAsync))
        .def("Cancel", &DaItem::Cancel);


    py::class_<DaGroupTrampoline>(m, "DaGroup", opcObject)
        .def(py::init<DaServer*, const char*, bool, uint32_t, ClientHandle, long*, float*, uint32_t>(),
            R"pbdoc(Constructs a DaGroup object.)pbdoc",
            py::arg("parent"),
            py::arg("name") = "", //nullptr,
            py::arg("active") = true,
            py::arg("requestedUpdateRate") = 0,
            py::arg("handleClientGroup") = 0xFFFFFFFF,
            py::arg("timeBias") = 0, //nullptr,
            py::arg("percentDeadband") = 0, // nullptr,
            py::arg("lcId") = 0x800)
        .def("IsActive", &DaGroupTrampoline::IsActive, R"pbdoc(Indicates the current active state of the group object.)pbdoc")
        .def("IsEnabled", &DaGroupTrampoline::IsEnabled, R"pbdoc(Indicates if data change notifications via the Data Change Subscription are enabled or disabled.)pbdoc")
        .def("HasDataSubscription", &DaGroupTrampoline::HasDataSubscription, R"pbdoc(Indicates if the Data Change Subscription of this group object has been activated.)pbdoc")
        .def("GetRevisedUpdateRate", &DaGroupTrampoline::GetRevisedUpdateRate, R"pbdoc(The revised update rate of the group object in milliseconds.)pbdoc")
        .def("GetServerHandle", &DaGroupTrampoline::GetServerHandle, R"pbdoc(The server handle of the group object.)pbdoc")
        .def("GetClientHandle", &DaGroupTrampoline::GetClientHandle, R"pbdoc(The client handle of the group object.)pbdoc")
        .def("SetActive", &DaGroupTrampoline::SetActive, R"pbdoc(Sets the active state of the group object.)pbdoc")
        .def("AddItems", &DaGroupTrampoline::AddItemsSimple)
        /*.def("AddItems", &DaGroup::AddItems,
            //py::return_value_policy::reference,
            R"pbdoc(Adds items to the group object.)pbdoc",
            py::arg("itemDefinitions"), 
            py::arg("items"), 
            py::arg("errorHandler") = nullptr
            )*/
        .def("Read", &DaGroupTrampoline::Read, 
            R"pbdoc(Reads the value, quality and timestamp of the specified items.)pbdoc",
            py::arg("items"),
            py::arg("fromCache") = true
            )
        .def("Write", &DaGroupTrampoline::Write, R"pbdoc(Writes the values of the specified items.)pbdoc")
        .def("SetDataSubscription", &DaGroupTrampoline::SetDataSubscription, R"pbdoc(Activates or inactivate's the Data Change Subscription of this group object.)pbdoc")
        .def("ReadAsync", &DaGroupTrampoline::ReadAsync, R"pbdoc(Reads the value, quality and timestamp of the specified items asynchronously.)pbdoc")
        .def("WriteAsync", &DaGroupTrampoline::WriteAsync, R"pbdoc(Writes the values of the specified items asynchronously.)pbdoc")
        .def("SetEnable", &DaGroupTrampoline::SetEnable, R"pbdoc(Enables or disables data change notifications via the Data Change Subscription.)pbdoc")
        .def("Cancel", &DaGroupTrampoline::Cancel, R"pbdoc(Requests the server to cancel an outstanding asynchronous transaction.)pbdoc")
        .def("Refresh", &DaGroupTrampoline::Refresh, R"pbdoc(Forces a data change notification for all active items.)pbdoc")
        ;


   // py::class_<DaIDataCallback>

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
