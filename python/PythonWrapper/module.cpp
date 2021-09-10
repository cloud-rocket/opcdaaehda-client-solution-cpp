/*
 * Copyright (c) 2021 Meir Tseitlin. All rights reserved
 * Web: https://www.linkedin.com/in/meirts/
 *
 * The source code in this file is covered under GPL V3
 *
 * GNU General Public License as published by the Free Software Foundation;
 * version 3 of the License are accompanied with this source code.
 * See https://technosoftware.com/license/GPLv3License.txt
 *
 * This source code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 */


// https://docs.microsoft.com/en-us/visualstudio/python/working-with-c-cpp-python-in-visual-studio?view=vs-2019

#define _HAS_STD_BYTE 0 // Required for CPPv17 support

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <PythonCOM.h>
#include <PyWinTypes.h>
#include "Classic/inc32/opcda.h"
#include "DaAeHdaClient/OpcClientSdk.h"
//#include "DaAeHdaClient/OpcUti.h"

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


                return PyCom_VariantFromPyObject(source, &value);



                // Try converting into a Python integer value 
                /*PyObject* tmp = PyNumber_Long(source);
                if (!tmp)
                    return false;
                // Now try to convert into a C++ int 
                value.lVal = PyLong_AsLong(tmp);
                Py_DECREF(tmp);
                // Ensure return code was OK (to avoid out-of-range errors etc) 
                return !(value.lVal == -1 && !PyErr_Occurred());*/
            }

            /**
             * Conversion part 2 (C++ -> Python): convert an inty instance into
             * a Python object. The second and third arguments are used to
             * indicate the return value policy and parent object (for
             * ``return_value_policy::reference_internal``) and are generally
             * ignored by implicit casters.
             */
            static handle cast(VARIANT src, return_value_policy /* policy */, handle /* parent */) {

                return PyCom_PyObjectFromVariant(&src);
            }
        };
    }
} // namespace pybind11::detail



//using errorHandler = std::function<void(const DaItemDefinition& itemDefinition, Status status)>;

PYBIND11_MAKE_OPAQUE(std::vector<DaItem*>);

/*
void AddItemErrHandler(const Technosoftware::DaAeHdaClient::DaItemDefinition& itemDef, Technosoftware::Base::Status res)
{
    cout << "   Cannot add item '" << itemDef.ItemIdentifier << "': " << res.ToString() << endl;
}

class DaGroupTrampoline : public DaGroup {
public:
    using DaGroup::DaGroup; // Inherit the constructors

    Status AddItemsSimple(DaItemDefinitions& itemDefinitions,
        vector<DaItem*>& items) {
        return AddItems(itemDefinitions, items);
    }

    Status AddItemsWithCallback(DaItemDefinitions& itemDefinitions,
        vector<DaItem*>& items, 
        const std::function<void(const DaItemDefinition& itemDefinition, Status status)> &errHandler) {


            return AddItems(itemDefinitions, items, AddItemErrHandler);
    }
};


class PyDaIDataCallback : public DaIDataCallback {
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


enum class OpcDaPropertyName {
    DataType = OPC_PROPERTY_DATATYPE,
    Value = OPC_PROPERTY_VALUE,
    Quality = OPC_PROPERTY_QUALITY,
    Timestamp = OPC_PROPERTY_TIMESTAMP,
    AccessRights = OPC_PROPERTY_ACCESS_RIGHTS,
    ScanRate = OPC_PROPERTY_SCAN_RATE,
    EuType = OPC_PROPERTY_EU_TYPE,
    EuInfo = OPC_PROPERTY_EU_INFO,
    EuUnits = OPC_PROPERTY_EU_UNITS,
    Description = OPC_PROPERTY_DESCRIPTION,
    HighEu = OPC_PROPERTY_HIGH_EU,
    LoEu = OPC_PROPERTY_LOW_EU,
    HighIr = OPC_PROPERTY_HIGH_IR,
    LowIr = OPC_PROPERTY_LOW_IR,
    CloseLabel = OPC_PROPERTY_CLOSE_LABEL,
    OpenLabel = OPC_PROPERTY_OPEN_LABEL,
    Timezone = OPC_PROPERTY_TIMEZONE,
    ConditionStatus = OPC_PROPERTY_CONDITION_STATUS,
    AlarmQuickHelp = OPC_PROPERTY_ALARM_QUICK_HELP,
    AlarmAreaList = OPC_PROPERTY_ALARM_AREA_LIST,
    PrimaryAlarmArea = OPC_PROPERTY_PRIMARY_ALARM_AREA,
    ConditionLogic = OPC_PROPERTY_CONDITION_LOGIC,
    LimitExceeded = OPC_PROPERTY_LIMIT_EXCEEDED,
    DeadBand = OPC_PROPERTY_DEADBAND,
    HihiLimit = OPC_PROPERTY_HIHI_LIMIT,
    HiLimit = OPC_PROPERTY_HI_LIMIT,
    LoLimit = OPC_PROPERTY_LO_LIMIT,
    LoLoLimit = OPC_PROPERTY_LOLO_LIMIT,
    ChangeRateLimit = OPC_PROPERTY_CHANGE_RATE_LIMIT,
    DeviationLimit = OPC_PROPERTY_DEVIATION_LIMIT,
    SoundFile = OPC_PROPERTY_SOUND_FILE,
    TypeSystemId = OPC_PROPERTY_TYPE_SYSTEM_ID,
    DictionaryId = OPC_PROPERTY_DICTIONARY_ID,
    TypeId = OPC_PROPERTY_TYPE_ID,
    Dictionary = OPC_PROPERTY_DICTIONARY,
    TypeDictionary = OPC_PROPERTY_TYPE_DESCRIPTION,
    ConsistencyWindow = OPC_PROPERTY_CONSISTENCY_WINDOW,
    WriteBehavior = OPC_PROPERTY_WRITE_BEHAVIOR,
    UnconvertedItemId = OPC_PROPERTY_UNCONVERTED_ITEM_ID,
    UnfilteredItemId = OPC_PROPERTY_UNFILTERED_ITEM_ID,
    DataFilterValue = OPC_PROPERTY_DATA_FILTER_VALUE
};


PYBIND11_MODULE(opcdaaehdaclient, m) {

    py::class_<OpcObject, std::unique_ptr<OpcObject, py::nodelete>> opcObject(m, "OpcObject");
    opcObject.def("Name", &OpcObject::Name);

    py::bind_vector<std::vector<DaItem*>>(m, "DaItems", py::module_local(false));

    // void(*errorHandler)(const DaItemDefinition& itemDefinition, Base::Status status)

    // Enums
    py::enum_<COINIT>(m, "COINIT")
        .value("AppartmentThreaded", COINIT_APARTMENTTHREADED, "Initializes the thread for apartment-threaded object concurrency.")
        .value("MultiThreaded", COINIT_MULTITHREADED, "Initializes the thread for multithreaded object concurrency.")
        .value("DisableOle1DDE", COINIT_DISABLE_OLE1DDE, "Disables DDE for OLE1 support..")
        .value("SpeedOverMemory", COINIT_SPEED_OVER_MEMORY, "Increase memory usage in an attempt to increase performance.")
        .export_values();

    py::enum_<DaBrowseElementFilter>(m, "DaBrowseElementFilter")
        .value("All", DaBrowseElementFilter::All, "All type of elements are returned.")
        .value("Branches", DaBrowseElementFilter::Branches, " Only elements with children elements are returned.")
        .value("Items", DaBrowseElementFilter::Items, " Only elements with children elements are returned.")
        .export_values();

    py::enum_<ServerStates::ServerState>(m, "ServerState")
        .value("Running", ServerStates::ServerState::Running, "The server is running normally.")
        .value("Failed", ServerStates::ServerState::Failed, "A vendor-specific fatal error has occurred within the server. The server is no longer functioning. The recovery procedure from this situation is vendor-specific. Most Service requests should be expected to fail.")
        .value("NoConfiguration", ServerStates::ServerState::NoConfiguration, "The server is running but has no configuration information loaded and therefore does not transfer data.")
        .value("Suspended", ServerStates::ServerState::Suspended, "The server has been temporarily suspended by some vendor-specific method and is not receiving or sending data.")
        .value("Shutdown", ServerStates::ServerState::Shutdown, "The server has shut down or is in the process of shutting down. Depending on the implementation, this might or might not be visible to clients.")
        .value("Test", ServerStates::ServerState::Test, "The server is in Test Mode. The outputs are disconnected from the real hardware, but the server will otherwise behave normally. Inputs may be real or may be simulated depending on the vendor implementation. StatusCode will generally be returned normally.")
        .value("CommunicationFault", ServerStates::ServerState::CommunicationFault, "The server is running properly, but is having difficulty accessing data from its data sources. This may be due to communication problems or some other problem preventing the underlying device, control system, etc. from returning valid data. It may be a complete failure, meaning that no data is available, or a partial failure, meaning that some data is still available. It is expected that items affected by the fault will individually return with a BAD FAILURE status code indication for the items.")
        .value("Unknown", ServerStates::ServerState::Unknown, "This state is used only to indicate that the OPC server does not know the state of underlying servers.")
        .export_values();

    py::enum_<OpcTextMode>(m, "OpcTextMode")
        .value("Valuename", OpcTextMode::Valuename, "The returned text string represents the name of the value as it was defined in accordance with the appropriate OPC Specification.")
        .value("Uppercase", OpcTextMode::Uppercase, " All characters in the returned text string are uppercase.")
        .value("Lowercase", OpcTextMode::Lowercase, "All characters in the returned text string are lowercase.")
        .value("Capitalize", OpcTextMode::Lowercase, "The first character of the returned text string is a capital letter.")
        .export_values();


    // Functions
    //m.def("QualityAsText", &Technosoftware::DaAeHdaClient::QualityAsText);


    // Objects
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
        .def("UpdateStatus", &DaServer::UpdateStatus, "Retrieves new status information from the currently connected server.")
        //.def("PollStatus", &DaServer::PollStatus, "Activates, inactivates or changes polling of the current server status. The callback has a user specified parameter value(Cookie).")
        //.def("SetShutdownRequestSubscription", &DaServer::SetShutdownRequestSubscription, "Activates or inactivates a subscription to shutdown requests from the connected server.")
        .def("RegisterClientName", &DaServer::RegisterClientName, 
            "Registers the client name with the connected server.",
            py::arg("sClientName"),
            py::arg_v("fMachineNameAsPrefix", false, "(Optional) Optional parameter which specifies if the name of the local computer should be used as prefix.")
            );


    py::class_<DaBrowseFilters>(m, "DaBrowseFilters", opcObject)
        .def(py::init<DaBrowseElementFilter, const string&, const string&, uint32_t, bool, bool, VARTYPE, uint32_t>(),
            R"pbdoc(Constructs a DaBrowseFilters object.)pbdoc", 
            py::arg_v("browseElementFilter", DaBrowseElementFilter::All, "(Optional) Specifies which type of elements are returned."),
            py::arg_v("elementNameFilter", "", "(Optional) Specifies the text string which will be used to filter the element names.This text string may contain wildcard characters that conforms to the LIKE operator from Visual Basic."),
            py::arg_v("vendorFilter", "", "(Optional) Specifies the text string which will be used for vendor specific filtering. "),
            py::arg_v("maxElementsReturned", 0, "(Optional) Specifies the maximum number of elements returned by the server.A value 0 turns this filter off."),
            py::arg_v("returnAllProperties", false, "(Optional) Specifies if each returned single element contains all available properties."),
            py::arg_v("returnPropertyValues", false, "(Optional) Specifies if the returned properties contains the property value too.This value is ignored if parameter returnAllProperties is false."),
            py::arg_v("dataTypeFilter", 0, "(Optional) Specifies the data type filter. All elements which match this data type are returned.The data type VT_EMPTY turns this filter off."), // VT_EMPTY=0
            py::arg_v("accessRightsFilter", OPC_READABLE + OPC_WRITEABLE, "(Optional) Specifies the access rights filter. All elements which match this access rights are returned. ")
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
        .def("IsBrowse2Used", &DaBrowser::IsBrowse2Used, "Indicates if the browser object uses the OPC 2.0 Browse functions.")
        .def("IsBrowse3Used", &DaBrowser::IsBrowse3Used, "Indicates if the browser object uses the OPC 3.0 Browse functions.")
        .def("Browse", &DaBrowser::Browse, "Returns all elements from the specified position which matches the filter criteria. The returned elements can be accessed via the function member Elements(). If this function is called then all elements returned by a previous call are removed.")
        .def("BrowseNext", &DaBrowser::BrowseNext, "Returns the next elements from the current position.")
        .def("SetFilters", &DaBrowser::SetFilters, "Sets new filters.")
        .def("GetPropertyValueAsText", &DaBrowser::GetPropertyValueAsText, "Gets property value as text.")
        .def("GetProperties", &DaBrowser::GetProperties, "Returns the item properties of the specified item ID.");

    py::class_<DaItemProperty>(m, "DaItemProperty", opcObject)
        .def(py::init<>())
        .def("GetId", &DaItemProperty::GetId)
        //.def("GetName", static_cast<OpcDaPropertyName>(&DaItemProperty::GetId))
        .def("GetDescription", &DaItemProperty::GetDescription)
        .def("GetDataType", &DaItemProperty::GetDataType)
        .def("GetValue", &DaItemProperty::GetValue)
        .def("GetItemId", &DaItemProperty::GetItemId)
        .def("GetResult", &DaItemProperty::GetResult)
        .def("GetDataTypeAsText", &DaItemProperty::GetDataTypeAsText, "Returns the Data Type as text string.", py::arg("textMode") = OpcTextMode::Capitalize)
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


    py::class_<DaGroup>(m, "DaGroup", opcObject)
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
        .def("IsActive", &DaGroup::IsActive, R"pbdoc(Indicates the current active state of the group object.)pbdoc")
        .def("IsEnabled", &DaGroup::IsEnabled, R"pbdoc(Indicates if data change notifications via the Data Change Subscription are enabled or disabled.)pbdoc")
        .def("HasDataSubscription", &DaGroup::HasDataSubscription, R"pbdoc(Indicates if the Data Change Subscription of this group object has been activated.)pbdoc")
        .def("GetRevisedUpdateRate", &DaGroup::GetRevisedUpdateRate, R"pbdoc(The revised update rate of the group object in milliseconds.)pbdoc")
        .def("GetServerHandle", &DaGroup::GetServerHandle, R"pbdoc(The server handle of the group object.)pbdoc")
        .def("GetClientHandle", &DaGroup::GetClientHandle, R"pbdoc(The client handle of the group object.)pbdoc")
        .def("SetActive", &DaGroup::SetActive, R"pbdoc(Sets the active state of the group object.)pbdoc")
        //.def("AddItems", &DaGroupTrampoline::AddItemsSimple)
        //.def("AddItems", &DaGroupTrampoline::AddItemsWithCallback)
        .def("AddItems", &DaGroup::AddItems,
            py::return_value_policy::reference,
            R"pbdoc(Adds items to the group object.)pbdoc",
            py::arg("itemDefinitions"), 
            py::arg("items"), 
            py::arg("errorHandler") = nullptr
            )
        .def("Read", &DaGroup::Read,
            R"pbdoc(Reads the value, quality and timestamp of the specified items.)pbdoc",
            py::arg("items"),
            py::arg("fromCache") = true
            )
        .def("Write", &DaGroup::Write, R"pbdoc(Writes the values of the specified items.)pbdoc")
        .def("SetDataSubscription", &DaGroup::SetDataSubscription, R"pbdoc(Activates or inactivate's the Data Change Subscription of this group object.)pbdoc")
        .def("ReadAsync", &DaGroup::ReadAsync, R"pbdoc(Reads the value, quality and timestamp of the specified items asynchronously.)pbdoc")
        .def("WriteAsync", &DaGroup::WriteAsync, R"pbdoc(Writes the values of the specified items asynchronously.)pbdoc")
        .def("SetEnable", &DaGroup::SetEnable, R"pbdoc(Enables or disables data change notifications via the Data Change Subscription.)pbdoc")
        .def("Cancel", &DaGroup::Cancel, R"pbdoc(Requests the server to cancel an outstanding asynchronous transaction.)pbdoc")
        .def("Refresh", &DaGroup::Refresh, R"pbdoc(Forces a data change notification for all active items.)pbdoc")
        ;


   // py::class_<DaIDataCallback>

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
