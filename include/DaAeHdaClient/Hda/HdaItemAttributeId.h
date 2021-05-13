/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://www.technosoftware.com
 *
 * The source code in this file is covered under a dual-license scenario:
 *   - Owner of a purchased license: SCLA 1.0
 *   - GPL V3: everybody else
 *
 * SCLA license terms accompanied with this source code.
 * See SCLA 1.0: https://technosoftware.com/license/Source_Code_License_Agreement.pdf
 *
 * GNU General Public License as published by the Free Software Foundation;
 * version 3 of the License are accompanied with this source code.
 * See https://technosoftware.com/license/GPLv3License.txt
 *
 * This source code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef TECHNOSOFTWARE_HdaItemAttributeId_H
#define TECHNOSOFTWARE_HdaItemAttributeId_H

namespace Technosoftware
{
	namespace DaAeHdaClient
	{
		/**
		 * @enum	HdaItemAttributeId
		 *
		 * @brief	This indicates the attribute IDs for the history data. The precise meaning of each attribute may be server specific. Attributes not supported by the server shall return OPC_E_INVALIDATTRID in the error code for that attribute. Additional attributes may be defined by vendors. Server specific attributes must be defined with values beginning at 0x80000000. The OPC foundation reserves all attribute IDs from 0 to 0x7fffffff.
		 *			This method return the attributes supported by the server, with a AttributeID, AttributeName, AttributeDescription, and AttributeDataType for each attribute. The AttributeDataType is included to enable the client to specify filter values when browsing the server's ItemIDs.
		 *
		 * @ingroup  HDAClient
		 */

		enum class HdaItemAttributeId {

			/**
			 * @brief    No item attribute specified
			 */
			NoItemAttribute = 0x00,

			/**
 			 * @brief    Specifies the data type for the item. See the definition of a VARIANT for valid values (VT_R4, etc.)
 			 */
			DataType = 0x01,

			/**
			 * @brief    Describes the item.
			 */
			 Description = 0x02,

			/**
			 * @brief    Specifies the label to use in displays to define the units for the item (e.g., kg/sec).
			 */
			 EngineeringUnits = 0x03,

			/**
			 * @brief    Specifies whether data from the history repository should be displayed as interpolated (sloped lines between points) or stepped (vertically-connected horizontal lines between points) data. Value of 0 indicates interpolated.
			 */
			 Stepped = 0x04,

			/**
			 * @brief    Indicates whether historian is recording data for this item (0 means no).
			 */
			 Archiving = 0x05,

			/**
			 * @brief    Specifies the equation to be used by a derived item to calculate its value. This is a free-form string.
			 */
			 DeriveEquation = 0x06,

			/**
			 * @brief    Specifies the machine which is the source for the item. This is intended to be the broadest category for defining sources. For an OPC Data Access Server source, this is the nodename or IP address of the server. For non-OPC sources, the meaning of this field is server-specific.
			 */
			 NodeName = 0x07,

			/**
			 * @brief    Specifies the process which is the source for the item. This is intended to the second-broadest category for defining sources. For an OPC DA server, this would be the registered server name. For non-OPC sources, the meaning of this field is server-specific.
			 */
			 ProcessName = 0x08,

			 /**
			  * @brief    Specifies the name of the item on the source. For an OPC DA server, this is the ItemID. For non-OPC sources, the meaning of this field is server-specific.
			  */
			 SourceName = 0x09,

			 /**
			  * @brief    Specifies what sort of source produces the data for the item. For an OPC DA server, this would be "OPC". For non-OPC sources, the meaning of this field is server-specific.
			  */
			 SourceType = 0x0a,

			 /**
			  * @brief    Specifies the upper limit for the normal value range for the item. NormalMaximum is used for trend display default scaling and exception deviation limit calculations. NormalMaximum should be the normal high value for the item.
			  */
			 NormalMaximum = 0x0b,

			 /**
			  * @brief    Specifies the lower limit for the normal value range for the item. NormalMinimum is used for trend display default scaling and exception deviation limit calculations. NormalMinimum should be the normal low value for the item.
			  */
			 NormalMinimum = 0x0c,

			 /**
			  * @brief    Specifies the item id. This is used to allow filtering in the CreateBrowse method, therefore the intention is to return only the leaf portion of an ItemID, not the fully qualified ItemID which would be returned from a GetItemId call.
			  */
			 ItemId = 0x0d,

			 /**
			  * @brief    Specifies the maximum interval between data points in the history repository regardless of their value change. A new value shall be stored in history whenever MaxTimeInterval seconds have passed since the last value stored for the item. Note that the binary value inside the VARIANT maps to FILETIME, such that .Hi equates to .dwHighDateTime and .Lo equates to .dwLowDateTime.
			  */
			  MaxTimeInterval = 0x0e,

			 /**
			  * @brief    Specifies the minimum interval between data points in the history repository regardless of their value change. A new value shall be not be stored in history unless MinTimeInterval seconds have passed since the last value stored for the item. Note that the binary value inside the VARIANT maps to FILETIME, such that .Hi equates to .dwHighDateTime and .Lo equates to .dwLowDateTime.
			  */
			  MinTimeInterval = 0x0f,

			 /**
			  * @brief    Specifies the minimum amount that the data for the item must change in order for the change to be reported to the history database. See ExceptionDeviationType for the specific meaning of this field.
			  */
			  ExceptionDeviation = 0x10,

			 /**
			  * @brief    Specifies whether the ExceptionDeviationType is given as an absolute value, percent of span, or percent of value. The span is defined as HighEntryLimit - LowEntryLimit.
			  */
			  ExceptionDeviationType = 0x11,

			 /**
			  * @brief    Specifies the highest valid value for the item. A value for the item that is above HighEntryLimit cannot be entered into history. This is the top of the span.
			  */
			  HighEntryLimit = 0x12,

			 /**
			  * @brief    Specifies the lowest valid value for the item. A value for the item that is below LowEntryLimit cannot be entered into history. This is the zero for the span.
			  */
			  LowEntryLimit = 0x13,
		};
	}
}

#endif // TECHNOSOFTWARE_HdaItemAttributeId_H