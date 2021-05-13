This is the changelog file for the OPC DA/AE/HDA Client Solution C++ Libraries.

## OPC DA/AE/HDA Client Solution C++ - 2.0.0-preview (Release Date 13-MAY-2021)

###	Highlights
- Use of C++11 style

###	Changes
- Renamed from UnifiedOPC to Technosoftware
- Renamed AeEvent::GetNumEventAttrs() to GetNumberEventAttributes()
- Renames AeEvent::GetActorID() to AeEvent::GetActorId()
- Rename DaBrowseElement::GetItemID() to DaBrowseElement::GetItemId()
- Rename DaItemProperty::GetID() to DaItemProperty::GetId()

### Notes
- AESample requires Visual C++ MFC for x86 and x64

## OPC DA/AE/HDA Client Solution C++ - 1.1.0 (Release Date 15-MAY-2018)

###	Highlights
- Updated to OPC Core Components 3.00.107
- Updated to Visual Studio 2017 support

###	Discontinued
- Removed Visual Studio 2013 support
- Removed Visual Studio 2015 support

## OPC DA/AE/HDA Client Solution C++ - 1.0.0 (Release Date 22-DEC-2016)

###	Highlights
- Added some more documentation
- Added some more basic HDA features: HdaAggregate, HdaAggregateId, HdaItemAttribute, HdaItemAttributeId
- Added GetItemAttributes and GetAggregates to HdaServer class
- New enums are now using C++11 style (enum class)

## OPC DA/AE/HDA Client Solution C++ - 0.1.1 (Release Date 25-OCT-2016)

###	Highlights
- The following Compiler versions are supported
    - Developer Edition: Visual Studio 2015
	- Ultimate Edition: Visual Studio 2015
	- Source Edition: Visual Studio 2013, Visual Studio 2015
- License can now be activated
- Updated License Agreement
- Changed include files to be able to use /include as one base root include folder (adapted clients for this also)
- Removed several internal used enums, classes and functions:
    - Use HashMap instead of OpcMap
    - OpcTimeTextMode
	- OpcList
	- OpcAssert
	- OpcString
	- OpcArray
- Added ServerStates and integrated that into the corresponding DA, AE and HDA Client API
- Removed GetServerStateAsText() methods from DaServerStatus, AeServerStatus and HdaServerStatus

## OPC DA/AE/HDA Client Solution C++ - 0.1.0 (Release Date 02-OCT-2016)

###	Highlights
This is the first public release of the OPC DA/AE/HDA Client Solution C++ Components.
The release does not contain all features planned for the later 1.0 release
(the full OPC HDA functionality is missing, for example), but is already quite usable.

Please refer to the README file for more information and instructions for
using the libraries.
