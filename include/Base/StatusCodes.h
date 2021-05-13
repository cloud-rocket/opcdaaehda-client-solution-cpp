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

#ifndef TECHNOSOFTWARE_STATUSCODES_H
#define TECHNOSOFTWARE_STATUSCODES_H


// STD
#include <string>
#include <vector>

// Technosoftware
#include "Base/Base.h"

/** @brief @file */


namespace Technosoftware
{
    namespace Base
    {
        namespace StatusCodes
        {
            /**
             * @enum    StatusCode
             *
             * @brief   This enum defines the status codes as specified by the OPC UA specification. A
             *          StatusCode in OPC UA is numerical value that is used to report the outcome of an
             *          operation performed by an OPC UA Server. This code may have associated diagnostic
             *          information that describes the status in more detail; however, the code by itself is
             *          intended to provide Client applications with enough information to make decisions on
             *          how to process the results of an OPC UA Service.
             *          
             *          The StatusCode is a 32-bit unsigned integer. The top 16 bits represent the numeric
             *          value of the code that shall be used for detecting specific errors or conditions. The
             *          bottom 16 bits are bit flags that contain additional information but do not affect
             *          the meaning of the StatusCode.
             *          
             *          All OPC UA Clients shall always check the StatusCode associated with a result before
             *          using it. Results that have an uncertain/warning status associated with them shall be
             *          used with care since these results might not be valid in all situations. Results with
             *          a bad/failed status shall never be used.
             *          
             *          OPC UA Servers should return good/success StatusCodes if the operation completed
             *          normally and the result is always valid. Different StatusCode values can provide
             *          additional information to the Client.
             *          
             *          OPC UA Servers should use uncertain/warning StatusCodes if they could not complete
             *          the operation in the manner requested by the Client, however, the operation did not
             *          fail entirely.
             *          
             *          The list of StatusCodes is managed by OPC UA. The complete list of StatusCodes is
             *          defined in Part 6. Servers shall not define their own StatusCodes. OPC UA companion
             *          working groups may request additional StatusCodes from the OPC Foundation to be added
             *          to the list in Part 6.
             *
             * @ingroup BaseOPC
             */

            enum StatusCode
            {
                /** @brief @brief    The operation was successful. */
                Good = 0x00000000,
                /** @brief    The value is uncertain but no specific reason is known. */
                Uncertain = 0x40000000,
                /** @brief    An unexpected error occurred. */
                BadUnexpectedError = 0x80010000,
                /** @brief    An internal error occurred as a result of a programming or configuration error. */
                BadInternalError = 0x80020000,
                /** @brief    Not enough memory to complete the operation. */
                BadOutOfMemory = 0x80030000,
                /** @brief  An operating system resource is not available. */
                BadResourceUnavailable = 0x80040000,
                /** @brief A low level communication error occurred. */
                BadCommunicationError = 0x80050000,
                /** @brief Encoding halted because of invalid data in the objects being serialized. */
                BadEncodingError = 0x80060000,
                /** @brief Decoding halted because of invalid data in the stream. */
                BadDecodingError = 0x80070000,
                /** @brief The message encoding/decoding limits imposed by the stack have been exceeded. */
                BadEncodingLimitsExceeded = 0x80080000,
                /** @brief The request message size exceeds limits set by the server. */
                BadRequestTooLarge = 0x80B80000,
                /** @brief The response message size exceeds limits set by the client. */
                BadResponseTooLarge = 0x80B90000,
                /** @brief An unrecognized response was received from the server. */
                BadUnknownResponse = 0x80090000,
                /** @brief The operation timed out. */
                BadTimeout = 0x800A0000,
                /** @brief The server does not support the requested service. */
                BadServiceUnsupported = 0x800B0000,
                /** @brief The operation was cancelled because the application is shutting down. */
                BadShutdown = 0x800C0000,
                /** @brief The operation could not complete because the client is not connected to the server. */
                BadServerNotConnected = 0x800D0000,
                /** @brief The server has stopped and cannot process any requests. */
                BadServerHalted = 0x800E0000,
                /** @brief There was nothing to do because the client passed a list of operations with no elements. */
                BadNothingToDo = 0x800F0000,
                /** @brief The request could not be processed because it specified too many operations. */
                BadTooManyOperations = 0x80100000,
                /** @brief The request could not be processed because there are too many monitored items in the subscription. */
                BadTooManyMonitoredItems = 0x80DB0000,
                /** @brief The extension object cannot be (de)serialized because the data type id is not recognized. */
                BadDataTypeIdUnknown = 0x80110000,
                /** @brief The certificate provided as a parameter is not valid. */
                BadCertificateInvalid = 0x80120000,
                /** @brief An error occurred verifying security. */
                BadSecurityChecksFailed = 0x80130000,
                /** @brief The Certificate has expired or is not yet valid. */
                BadCertificateTimeInvalid = 0x80140000,
                /** @brief An Issuer Certificate has expired or is not yet valid. */
                BadCertificateIssuerTimeInvalid = 0x80150000,
                /** @brief The HostName used to connect to a Server does not match a HostName in the Certificate. */
                BadCertificateHostNameInvalid = 0x80160000,
                /** @brief The URI specified in the ApplicationDescription does not match the URI in the Certificate. */
                BadCertificateUriInvalid = 0x80170000,
                /** @brief The Certificate may not be used for the requested operation. */
                BadCertificateUseNotAllowed = 0x80180000,
                /** @brief The Issuer Certificate may not be used for the requested operation. */
                BadCertificateIssuerUseNotAllowed = 0x80190000,
                /** @brief The Certificate is not trusted. */
                BadCertificateUntrusted = 0x801A0000,
                /** @brief It was not possible to determine if the Certificate has been revoked. */
                BadCertificateRevocationUnknown = 0x801B0000,
                /** @brief It was not possible to determine if the Issuer Certificate has been revoked. */
                BadCertificateIssuerRevocationUnknown = 0x801C0000,
                /** @brief The Certificate has been revoked. */
                BadCertificateRevoked = 0x801D0000,
                /** @brief The Issuer Certificate has been revoked. */
                BadCertificateIssuerRevoked = 0x801E0000,
                /** @brief User does not have permission to perform the requested operation. */
                BadUserAccessDenied = 0x801F0000,
                /** @brief The user identity token is not valid. */
                BadIdentityTokenInvalid = 0x80200000,
                /** @brief The user identity token is valid but the server has rejected it. */
                BadIdentityTokenRejected = 0x80210000,
                /** @brief The specified secure channel is no longer valid. */
                BadSecureChannelIdInvalid = 0x80220000,
                /** @brief The timestamp is outside the range allowed by the server. */
                BadInvalidTimestamp = 0x80230000,
                /** @brief The nonce does appear to be not a random value or it is not the correct length. */
                BadNonceInvalid = 0x80240000,
                /** @brief The session id is not valid. >*/
                BadSessionIdInvalid = 0x80250000,
                /** @brief The session was closed by the client. */
                BadSessionClosed = 0x80260000,
                /** @brief The session cannot be used because ActivateSession has not been called. */
                BadSessionNotActivated = 0x80270000,
                /** @brief The subscription id is not valid. */
                BadSubscriptionIdInvalid = 0x80280000,
                /** @brief The header for the request is missing or invalid. */
                BadRequestHeaderInvalid = 0x802A0000,
                /** @brief The timestamps to return parameter is invalid. */
                BadTimestampsToReturnInvalid = 0x802B0000,
                /** @brief The request was cancelled by the client. */
                BadRequestCancelledByClient = 0x802C0000,
                /** @brief The subscription was transferred to another session. */
                GoodSubscriptionTransferred = 0x002D0000,
                /** @brief The processing will complete asynchronously. */
                GoodCompletesAsynchronously = 0x002E0000,
                /** @brief Sampling has slowed down due to resource limitations. */
                GoodOverload = 0x002F0000,
                /** @brief The value written was accepted but was clamped. */
                GoodClamped = 0x00300000,
                /** @brief Communication with the data source is defined, but not established, and there is no last known value available. */
                BadNoCommunication = 0x80310000,
                /** @brief Waiting for the server to obtain values from the underlying data source. */
                BadWaitingForInitialData = 0x80320000,
                /** @brief The syntax of the node id is not valid. */
                BadNodeIdInvalid = 0x80330000,
                /** @brief The node id refers to a node that does not exist in the server address space. */
                BadNodeIdUnknown = 0x80340000,
                /** @brief The attribute is not supported for the specified Node. */
                BadAttributeIdInvalid = 0x80350000,
                /** @brief The syntax of the index range parameter is invalid. */
                BadIndexRangeInvalid = 0x80360000,
                /** @brief No data exists within the range of indexes specified. */
                BadIndexRangeNoData = 0x80370000,
                /** @brief The data encoding is invalid. */
                BadDataEncodingInvalid = 0x80380000,
                /** @brief The server does not support the requested data encoding for the node. */
                BadDataEncodingUnsupported = 0x80390000,
                /** @brief The access level does not allow reading or subscribing to the Node. */
                BadNotReadable = 0x803A0000,
                /** @brief The access level does not allow writing to the Node. */
                BadNotWritable = 0x803B0000,
                /** @brief The value was out of range. */
                BadOutOfRange = 0x803C0000,
                /** @brief The requested operation is not supported. */
                BadNotSupported = 0x803D0000,
                /** @brief A requested item was not found or a search operation ended without success. */
                BadNotFound = 0x803E0000,
                /** @brief The object cannot be used because it has been deleted. */
                BadObjectDeleted = 0x803F0000,
                /** @brief Requested operation is not implemented. */
                BadNotImplemented = 0x80400000,
                /** @brief The monitoring mode is invalid. */
                BadMonitoringModeInvalid = 0x80410000,
                /** @brief The monitoring item id does not refer to a valid monitored item. */
                BadMonitoredItemIdInvalid = 0x80420000,
                /** @brief The monitored item filter parameter is not valid. */
                BadMonitoredItemFilterInvalid = 0x80430000,
                /** @brief The server does not support the requested monitored item filter. */
                BadMonitoredItemFilterUnsupported = 0x80440000,
                /** @brief A monitoring filter cannot be used in combination with the attribute specified. */
                BadFilterNotAllowed = 0x80450000,
                /** @brief A mandatory structured parameter was missing or null. */
                BadStructureMissing = 0x80460000,
                /** @brief The event filter is not valid. */
                BadEventFilterInvalid = 0x80470000,
                /** @brief The content filter is not valid. */
                BadContentFilterInvalid = 0x80480000,
                /** @brief An unregognized operator was provided in a filter. */
                BadFilterOperatorInvalid = 0x80C10000,
                /** @brief A valid operator was provided, but the server does not provide support for this filter operator. */
                BadFilterOperatorUnsupported = 0x80C20000,
                /** @brief The number of operands provided for the filter operator was less then expected for the operand provided. */
                BadFilterOperandCountMismatch = 0x80C30000,
                /** @brief The operand used in a content filter is not valid. */
                BadFilterOperandInvalid = 0x80490000,
                /** @brief The referenced element is not a valid element in the content filter. */
                BadFilterElementInvalid = 0x80C40000,
                /** @brief The referenced literal is not a valid value. */
                BadFilterLiteralInvalid = 0x80C50000,
                /** @brief The continuation point provide is longer valid. */
                BadContinuationPointInvalid = 0x804A0000,
                /** @brief The operation could not be processed because all continuation points have been allocated. */
                BadNoContinuationPoints = 0x804B0000,
                /** @brief The operation could not be processed because all continuation points have been allocated. */
                BadReferenceTypeIdInvalid = 0x804C0000,
                /** @brief The browse direction is not valid. */
                BadBrowseDirectionInvalid = 0x804D0000,
                /** @brief The node is not part of the view. */
                BadNodeNotInView = 0x804E0000,
                /** @brief The ServerUri is not a valid URI. */
                BadServerUriInvalid = 0x804F0000,
                /** @brief No ServerName was specified. */
                BadServerNameMissing = 0x80500000,
                /** @brief No DiscoveryUrl was specified. */
                BadDiscoveryUrlMissing = 0x80510000,
                /** @brief The semaphore file specified by the client is not valid. */
                BadSempahoreFileMissing = 0x80520000,
                /** @brief The security token request type is not valid. */
                BadRequestTypeInvalid = 0x80530000,
                /** @brief The security mode does not meet the requirements set by the Server. */
                BadSecurityModeRejected = 0x80540000,
                /** @brief The security policy does not meet the requirements set by the Server. */
                BadSecurityPolicyRejected = 0x80550000,
                /** @brief The server has reached its maximum number of sessions. */
                BadTooManySessions = 0x80560000,
                /** @brief The user token signature is missing or invalid. */
                BadUserSignatureInvalid = 0x80570000,
                /** @brief The signature generated with the client certificate is missing or invalid. */
                BadApplicationSignatureInvalid = 0x80580000,
                /** @brief The client did not provide at least one software certificate that is valid and meets the profile requirements for the server. */
                BadNoValidCertificates = 0x80590000,
                /** @brief The Server does not support changing the user identity assigned to the session. */
                BadIdentityChangeNotSupported = 0x80C60000,
                /** @brief The request was cancelled by the client with the Cancel service. */
                BadRequestCancelledByRequest = 0x805A0000,
                /** @brief The parent node id does not to refer to a valid node. */
                BadParentNodeIdInvalid = 0x805B0000,
                /** @brief The reference could not be created because it violates constraints imposed by the data model. */
                BadReferenceNotAllowed = 0x805C0000,
                /** @brief The requested node id was reject because it was either invalid or server does not allow node ids to be specified by the client. */
                BadNodeIdRejected = 0x805D0000,
                /** @brief The requested node id is already used by another node. */
                BadNodeIdExists = 0x805E0000,
                /** @brief The node class is not valid. */
                BadNodeClassInvalid = 0x805F0000,
                /** @brief The browse name is invalid. */
                BadBrowseNameInvalid = 0x80600000,
                /** @brief The browse name is not unique among nodes that share the same relationship with the parent. */
                BadBrowseNameDuplicated = 0x80610000,
                /** @brief The node attributes are not valid for the node class. */
                BadNodeAttributesInvalid = 0x80620000,
                /** @brief The type definition node id does not reference an appropriate type node. */
                BadTypeDefinitionInvalid = 0x80630000,
                /** @brief The source node id does not reference a valid node. */
                BadSourceNodeIdInvalid = 0x80640000,
                /** @brief The target node id does not reference a valid node. */
                BadTargetNodeIdInvalid = 0x80650000,
                /** @brief The reference type between the nodes is already defined. */
                BadDuplicateReferenceNotAllowed = 0x80660000,
                /** @brief The server does not allow this type of self reference on this node. */
                BadInvalidSelfReference = 0x80670000,
                /** @brief The reference type is not valid for a reference to a remote server. */
                BadReferenceLocalOnly = 0x80680000,
                /** @brief The server will not allow the node to be deleted. */
                BadNoDeleteRights = 0x80690000,
                /** @brief The server was not able to delete all target references. */
                UncertainReferenceNotDeleted = 0x40BC0000,
                /** @brief The server index is not valid. */
                BadServerIndexInvalid = 0x806A0000,
                /** @brief The view id does not refer to a valid view node. */
                BadViewIdUnknown = 0x806B0000,
                /** @brief The view timestamp is not available or not supported. */
                BadViewTimestampInvalid = 0x80C90000,
                /** @brief The view parameters are not consistent with each other. */
                BadViewParameterMismatch = 0x80CA0000,
                /** @brief The view version is not available or not supported. */
                BadViewVersionInvalid = 0x80CB0000,
                /** @brief The list of references may not be complete because the underlying system is not available. */
                UncertainNotAllNodesAvailable = 0x40C00000,
                /** @brief The server should have followed a reference to a node in a remote server but did not. The result set may be incomplete. */
                GoodResultsMayBeIncomplete = 0x00BA0000,
                /** @brief The provided Nodeid was not a type definition nodeid. */
                BadNotTypeDefinition = 0x80C80000,
                /** @brief One of the references to follow in the relative path references to a node in the address space in another server. */
                UncertainReferenceOutOfServer = 0x406C0000,
                /** @brief The requested operation has too many matches to return. */
                BadTooManyMatches = 0x806D0000,
                /** @brief The requested operation requires too many resources in the server. */
                BadQueryTooComplex = 0x806E0000,
                /** @brief The requested operation has no match to return. */
                BadNoMatch = 0x806F0000,
                /** @brief The max age parameter is invalid. */
                BadMaxAgeInvalid = 0x80700000,
                /** @brief The history details parameter is not valid. */
                BadHistoryOperationInvalid = 0x80710000,
                /** @brief The server does not support the requested operation. */
                BadHistoryOperationUnsupported = 0x80720000,
                /** @brief The defined timestamp to return was invalid. */
                BadInvalidTimestampArgument = 0x80BD0000,
                /** @brief The server not does support writing the combination of value, status and timestamps provided. */
                BadWriteNotSupported = 0x80730000,
                /** @brief The value supplied for the attribute is not of the same type as the attribute's value. */
                BadTypeMismatch = 0x80740000,
                /** @brief The method id does not refer to a method for the specified object. */
                BadMethodInvalid = 0x80750000,
                /** @brief The client did not specify all of the input arguments for the method. */
                BadArgumentsMissing = 0x80760000,
                /** @brief The server has reached its  maximum number of subscriptions. */
                BadTooManySubscriptions = 0x80770000,
                /** @brief The server has reached the maximum number of queued publish requests. */
                BadTooManyPublishRequests = 0x80780000,
                /** @brief There is no subscription available for this session. */
                BadNoSubscription = 0x80790000,
                /** @brief The sequence number is unknown to the server. */
                BadSequenceNumberUnknown = 0x807A0000,
                /** @brief The requested notification message is no longer available. */
                BadMessageNotAvailable = 0x807B0000,
                /** @brief The Client of the current Session does not support one or more Profiles that are necessary for the Subscription. */
                BadInsufficientClientProfile = 0x807C0000,
                /** @brief The sub-state machine is not currently active. */
                BadStateNotActive = 0x80BF0000,
                /** @brief The server cannot process the request because it is too busy. */
                BadTcpServerTooBusy = 0x807D0000,
                /** @brief The type of the message specified in the header invalid. */
                BadTcpMessageTypeInvalid = 0x807E0000,
                /** @brief The SecureChannelId and/or TokenId are not currently in use. */
                BadTcpSecureChannelUnknown = 0x807F0000,
                /** @brief The size of the message specified in the header is too large. */
                BadTcpMessageTooLarge = 0x80800000,
                /** @brief There are not enough resources to process the request. */
                BadTcpNotEnoughResources = 0x80810000,
                /** @brief An internal error occurred. */
                BadTcpInternalError = 0x80820000,
                /** @brief The Server does not recognize the QueryString specified. */
                BadTcpEndpointUrlInvalid = 0x80830000,
                /** @brief The request could not be sent because of a network interruption. */
                BadRequestInterrupted = 0x80840000,
                /** @brief Timeout occurred while processing the request. */
                BadRequestTimeout = 0x80850000,
                /** @brief The secure channel has been closed. */
                BadSecureChannelClosed = 0x80860000,
                /** @brief The token has expired or is not recognized. */
                BadSecureChannelTokenUnknown = 0x80870000,
                /** @brief The sequence number is not valid. */
                BadSequenceNumberInvalid = 0x80880000,
                /** @brief The applications do not have compatible protocol versions. */
                BadProtocolVersionUnsupported = 0x80BE0000,
                /** @brief There is a problem with the configuration that affects the usefulness of the value. */
                BadConfigurationError = 0x80890000,
                /** @brief The variable should receive its value from another variable, but has never been configured to do so. */
                BadNotConnected = 0x808A0000,
                /** @brief There has been a failure in the device/data source that generates the value that has affected the value. */
                BadDeviceFailure = 0x808B0000,
                /** @brief There has been a failure in the sensor from which the value is derived by the device/data source. */
                BadSensorFailure = 0x808C0000,
                /** @brief The source of the data is not operational. */
                BadOutOfService = 0x808D0000,
                /** @brief The deadband filter is not valid. */
                BadDeadbandFilterInvalid = 0x808E0000,
                /** @brief Communication to the data source has failed. The variable value is the last value that had a good quality. */
                UncertainNoCommunicationLastUsableValue = 0x408F0000,
                /** @brief Whatever was updating this value has stopped doing so. */
                UncertainLastUsableValue = 0x40900000,
                /** @brief The value is an operational value that was manually overwritten. */
                UncertainSubstituteValue = 0x40910000,
                /** @brief The value is an initial value for a variable that normally receives its value from another variable. */
                UncertainInitialValue = 0x40920000,
                /** @brief The value is at one of the sensor limits. */
                UncertainSensorNotAccurate = 0x40930000,
                /** @brief The value is outside of the range of values defined for this parameter. */
                UncertainEngineeringUnitsExceeded = 0x40940000,
                /** @brief The value is derived from multiple sources and has less than the required number of Good sources. */
                UncertainSubNormal = 0x40950000,
                /** @brief The value has been overridden. */
                GoodLocalOverride = 0x00960000,
                /** @brief This Condition refresh failed, a Condition refresh operation is already in progress. */
                BadRefreshInProgress = 0x80970000,
                /** @brief This condition has already been disabled. */
                BadConditionAlreadyDisabled = 0x80980000,
                /** @brief This condition has already been enabled. */
                BadConditionAlreadyEnabled = 0x80CC0000,
                /** @brief Property not available, this condition is disabled. */
                BadConditionDisabled = 0x80990000,
                /** @brief The specified event id is not recognized. */
                BadEventIdUnknown = 0x809A0000,
                /** @brief The event cannot be acknowledged. */
                BadEventNotAcknowledgeable = 0x80BB0000,
                /** @brief The dialog condition is not active. */
                BadDialogNotActive = 0x80CD0000,
                /** @brief The response is not valid for the dialog. */
                BadDialogResponseInvalid = 0x80CE0000,
                /** @brief The condition branch has already been acknowledged. */
                BadConditionBranchAlreadyAcked = 0x80CF0000,
                /** @brief The condition branch has already been confirmed. */
                BadConditionBranchAlreadyConfirmed = 0x80D00000,
                /** @brief The condition has already been shelved. */
                BadConditionAlreadyShelved = 0x80D10000,
                /** @brief The condition is not currently shelved. */
                BadConditionNotShelved = 0x80D20000,
                /** @brief The shelving time not within an acceptable range. */
                BadShelvingTimeOutOfRange = 0x80D30000,
                /** @brief No data exists for the requested time range or event filter. */
                BadNoData = 0x809B0000,
                /** @brief No data found to provide upper or lower bound value. */
                BadBoundNotFound = 0x80D70000,
                /** @brief The server cannot retrieve a bound for the variable. */
                BadBoundNotSupported = 0x80D80000,
                /** @brief Data is missing due to collection started/stopped/lost. */
                BadDataLost = 0x809D0000,
                /** @brief Expected data is unavailable for the requested time range due to an un-mounted volume, an off-line archive or tape, or similar reason for temporary unavailability. */
                BadDataUnavailable = 0x809E0000,
                /** @brief The data or event was not successfully inserted because a matching entry exists. */
                BadEntryExists = 0x809F0000,
                /** @brief The data or event was not successfully updated because no matching entry exists. */
                BadNoEntryExists = 0x80A00000,
                /** @brief The client requested history using a timestamp format the server does not support (i.e requested ServerTimestamp when server only supports SourceTimestamp). */
                BadTimestampNotSupported = 0x80A10000,
                /** @brief The data or event was successfully inserted into the historical database. */
                GoodEntryInserted = 0x00A20000,
                /** @brief The data or event field was successfully replaced in the historical database. */
                GoodEntryReplaced = 0x00A30000,
                /** @brief The value is derived from multiple values and has less than the required number of Good values. */
                UncertainDataSubNormal = 0x40A40000,
                /** @brief No data exists for the requested time range or event filter. */
                GoodNoData = 0x00A50000,
                /** @brief The data or event field was successfully replaced in the historical database. */
                GoodMoreData = 0x00A60000,
                /** @brief The requested number of Aggregates does not match the requested number of NodeIds. */
                BadAggregateListMismatch = 0x80D40000,
                /** @brief The requested Aggregate is not support by the server. */
                BadAggregateNotSupported = 0x80D50000,
                /** @brief The aggregate value could not be derived due to invalid data inputs. */
                BadAggregateInvalidInputs = 0x80D60000,
                /** @brief The aggregate configuration is not valid for specified node. */
                BadAggregateConfigurationRejected = 0x80DA0000,
                /** @brief The request pecifies fields which are not valid for the EventType or cannot be saved by the historian. */
                GoodDataIgnored = 0x00D90000,
                /** @brief The communication layer has raised an event. */
                GoodCommunicationEvent = 0x00A70000,
                /** @brief The system is shutting down. */
                GoodShutdownEvent = 0x00A80000,
                /** @brief The operation is not finished and needs to be called again. */
                GoodCallAgain = 0x00A90000,
                /** @brief A non-critical timeout occurred. */
                GoodNonCriticalTimeout = 0x00AA0000,
                /** @brief One or more arguments are invalid. */
                BadInvalidArgument = 0x80AB0000,
                /** @brief Could not establish a network connection to remote server. */
                BadConnectionRejected = 0x80AC0000,
                /** @brief The server has disconnected from the client. */
                BadDisconnect = 0x80AD0000,
                /** @brief The network connection has been closed. */
                BadConnectionClosed = 0x80AE0000,
                /** @brief The operation cannot be completed because the object is closed, uninitialized or in some other invalid state. */
                BadInvalidState = 0x80AF0000,
                /** @brief Cannot move beyond end of the stream. */
                BadEndOfStream = 0x80B00000,
                /** @brief No data is currently available for reading from a non-blocking stream. */
                BadNoDataAvailable = 0x80B10000,
                /** @brief The asynchronous operation is waiting for a response. */
                BadWaitingForResponse = 0x80B20000,
                /** @brief The asynchronous operation was abandoned by the caller. */
                BadOperationAbandoned = 0x80B30000,
                /** @brief The stream did not return all data requested (possibly because it is a non-blocking stream). */
                BadExpectedStreamToBlock = 0x80B40000,
                /** @brief Non blocking behaviour is required and the operation would block. */
                BadWouldBlock = 0x80B50000,
                /** @brief A value had an invalid syntax. */
                BadSyntaxError = 0x80B60000,
                /** @brief The operation could not be finished because all available connections are in use. */
                BadMaxConnectionsReached = 0x80B70000,
                /** @brief    No status is given until now. */
                NoStatusError = 0x80F10000,
                /** @brief    At least one bad status is given.  */
                BadStatusError = 0x80F20000,
                /** @brief    The product license expired, e.g. the evaluation period is over.  */
                BadLicenseExpired = 0x80F30000,
            };

            /**
             * @fn  std::string TECHNOSOFTWARE_API ToString(Technosoftware::Base::StatusCodes::StatusCode code);
             *
             * @brief   Get a string representation of the status code.
             *
             * @ingroup BaseOPC
             *
             * @param   code    The status code (as an enum).
             *
             * @return  The corresponding name of the status code.
             */

            std::string TECHNOSOFTWARE_API ToString(Technosoftware::Base::StatusCodes::StatusCode code);
        }
    }
}

#endif /* @brief TECHNOSOFTWARE_STATUSCODES_H */
