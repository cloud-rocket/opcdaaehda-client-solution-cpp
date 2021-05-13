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

 //-------------------------------------------------------------------------
 // INCLUDES
 //-------------------------------------------------------------------------
#include <new>
#include <tchar.h>
#include "OpcAccess.h"
#include "DaAeHdaClient/OpcBase.h"

// Note : ClientSDK_i.c must be added to your project


namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        //-------------------------------------------------------------------------
        // CONSTRUCTION/DESTRUCTION
        //-------------------------------------------------------------------------

        OpcAccess::OpcAccess()
        {
            m_pIMalloc = nullptr;                 // Initialze attributes
            m_pIOPCServer = nullptr;
            iOPCEventServer_ = nullptr;
            m_pIOPCHistoricalServer = nullptr;
            m_fCOMIsInitialized = FALSE;                // Initialze internals
        }

        OpcAccess::~OpcAccess()
        {
            DisconnectFromServer();                      // Be sure the server is disconnected
            DisconnectFromEventServer();                 // bevor the instance will be destroyed.
            DisconnectFromHistoricalServer();            // bevor the instance will be destroyed.
        }



        //-------------------------------------------------------------------------
        // OPERATIONS Data Server
        //-------------------------------------------------------------------------

        HRESULT OpcAccess::ConnectToServer(LPCTSTR szMachineName,
            LPCTSTR szServerName,
            BOOL    fErrorBox,  // = TRUE
            DWORD   dwCoInit    // = COINIT_MULTITHREADED
        )
        {
            if (szMachineName && *szMachineName) {       // Remote Machine
                HRESULT  hres;
                CLSID    clsid;
                // Try if it is registered local
                hres = GetLocalCLSID(szServerName, FALSE, &clsid);
                if (FAILED(hres)) {

                    BOOL fReleaseCOMInitialization = FALSE;
                    if (!m_fCOMIsInitialized) {
                        hres = InitializeDCOM(fErrorBox, dwCoInit);
                        if (SUCCEEDED(hres)) {
                            fReleaseCOMInitialization = TRUE;
                        }
                        else {
                            return hres;
                        }
                    }
                    // Try it via the OPCBroser object
                    hres = GetRemoteCLSID(szMachineName, szServerName, fErrorBox, &clsid);

                    if (fReleaseCOMInitialization) {
                        DisconnectFromServer();             // Release all DCOM Initialization
                    }
                }
                if (SUCCEEDED(hres)) {
                    hres = ConnectToServer(szMachineName, clsid, fErrorBox, dwCoInit);
                }
                return hres;
            }
            else {                                       // If no machine name is specified
                // then try local server
                return ConnectToServer(szServerName, fErrorBox, dwCoInit);
            }
        }

        HRESULT OpcAccess::ConnectToServer(LPCTSTR szServerName,
            BOOL    fErrorBox,  // = TRUE
            DWORD   dwCoInit    // = COINIT_MULTITHREADED
        )
        {
            CLSID    clsid;
            HRESULT  hres;

            hres = GetLocalCLSID(szServerName, fErrorBox, &clsid);
            if (SUCCEEDED(hres)) {
                hres = ConnectToServer(NULL, clsid, fErrorBox, dwCoInit);
            }
            return hres;
        }

        HRESULT OpcAccess::ConnectToServer(LPCTSTR szMachineName,
            CLSID   clsidServer,
            BOOL    fErrorBox,  // = TRUE
            DWORD   dwCoInit    // = COINIT_MULTITHREADED
        )
        {
            COSERVERINFO   SrvInfo, *pSrvInfo;
            DWORD          dwClsCtx;
            MULTI_QI       mqi;
            HRESULT        hres;

            if (m_pIOPCServer != NULL) {                 // Already connected
                if (fErrorBox) ErrorMessage(_T("Already connected to an OPC Data Server!"), E_FAIL);
                return E_FAIL;
            }

            hres = InitializeDCOM(fErrorBox, dwCoInit);
            if (FAILED(hres)) {
                return hres;                              // Error message already displayed
            }

            LPWSTR pszMachineNameW = NULL;

            // Set up the server info
            if (szMachineName && *szMachineName) {

#if defined (UNICODE) || defined (_UNICODE)
                pszMachineNameW = (LPTSTR)szMachineName;
#else
                hres = DupToWStr(szMachineName, &pszMachineNameW);
                if (FAILED(hres)) {
                    if (fErrorBox) ErrorMessage(_T("Cannot convert Machine Name to wide-character string !"), hres);
                    return hres;
                }
#endif

                SrvInfo.dwReserved1 = 0;
                SrvInfo.dwReserved2 = 0;
                SrvInfo.pAuthInfo = NULL;              // Use the default activation security.
                SrvInfo.pwszName = pszMachineNameW;
                pSrvInfo = &SrvInfo;
                dwClsCtx = CLSCTX_SERVER;
            }
            else {                                       // If no machine name is specified
                // then try local server
                pSrvInfo = NULL;
                dwClsCtx = CLSCTX_LOCAL_SERVER | CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER;
            }

            // Set up mqi
            mqi.pIID = &IID_IOPCServer;
            mqi.hr = 0;
            mqi.pItf = 0;

            hres = CoCreateInstanceEx(clsidServer, NULL, dwClsCtx, pSrvInfo, 1, &mqi);

            if (pszMachineNameW) {                       // Release temporary string copy
#if defined (UNICODE) || defined (_UNICODE)
        //
#else
                delete[] pszMachineNameW;
#endif
            }

            if (FAILED(hres) || FAILED(mqi.hr)) {
                DisconnectFromServer();
                if (SUCCEEDED(hres)) {
                    hres = mqi.hr;
                }
                if (fErrorBox) ErrorMessage(_T("Function 'CoCreateInstanceEx' failed !"), hres);
                return hres;
            }
            // All succeeded
            m_pIOPCServer = (IOPCServer *)mqi.pItf;
            return S_OK;
        }

        void OpcAccess::DisconnectFromServer()
        {
            if (m_pIOPCServer) {                         // Release the Data Access Server Interface
                m_pIOPCServer->Release();
                m_pIOPCServer = NULL;
            }

            if (iOPCEventServer_ == NULL) {            // Other things must be released only if there
                // is no connection to an Event Server

                if (m_pIMalloc) {                         // Release Global Interface to the COM memory manager.
                    m_pIMalloc->Release();
                    m_pIMalloc = NULL;
                }

                if (m_fCOMIsInitialized) {                // Uninitialize COM only if succesfully initialized.
                    CoUninitialize();
                    m_fCOMIsInitialized = FALSE;
                }
            }
        }



        //-------------------------------------------------------------------------
        // OPERATIONS Events Server
        //-------------------------------------------------------------------------

        HRESULT OpcAccess::ConnectToEventServer(
            LPCTSTR szMachineName,
            LPCTSTR szServerName,
            BOOL    fErrorBox,  // = TRUE
            DWORD   dwCoInit    // = COINIT_MULTITHREADED
        )
        {
            if (szMachineName && *szMachineName) {       // Remote Machine
                HRESULT  hres;
                CLSID    clsid;
                // Try if it is registered local
                hres = GetLocalCLSID(szServerName, FALSE, &clsid);
                if (FAILED(hres)) {

                    BOOL fReleaseCOMInitialization = FALSE;
                    if (!m_fCOMIsInitialized) {
                        hres = InitializeDCOM(fErrorBox, dwCoInit);
                        if (SUCCEEDED(hres)) {
                            fReleaseCOMInitialization = TRUE;
                        }
                        else {
                            return hres;
                        }
                    }
                    // Try it via the OPCBroser object
                    hres = GetRemoteCLSID(szMachineName, szServerName, fErrorBox, &clsid);

                    if (fReleaseCOMInitialization) {
                        DisconnectFromEventServer();        // Release all DCOM Initialization
                    }
                }
                if (SUCCEEDED(hres)) {
                    hres = ConnectToEventServer(szMachineName, clsid, fErrorBox, dwCoInit);
                }
                return hres;
            }
            else {                                       // If no machine name is specified
                // then try local server
                return ConnectToEventServer(szServerName, fErrorBox, dwCoInit);
            }
        }




        //=========================================================================
        // Connects to the OPC Event Server with the specified name on the
        // specified machine. If szMachineName is NULL or a NULL-String then the
        // local machine will be used. The Class ID associated with the server
        // name is retrieved from the local machine if available. Is the server is
        // not registered and a remote machine is specified then the OPC Browser
        // object on the remote machine is used to get the Class ID of the server.
        //=========================================================================

        /**
         * @fn    HRESULT OpcAccess::ConnectToEventServer( LPCTSTR szServerName, BOOL fErrorBox, DWORD dwCoInit )
         *
         * @brief    Connects to event server.
         *
         * @param    szServerName    Name of the server.
         * @param    fErrorBox       true to error box.
         * @param    dwCoInit        The co initialise.
         *
         * @return    A HRESULT.
         */

        HRESULT OpcAccess::ConnectToEventServer(
            LPCTSTR szServerName,
            BOOL    fErrorBox,  // = TRUE
            DWORD   dwCoInit    // = COINIT_MULTITHREADED
        )
        {
            CLSID    clsid;
            HRESULT  hres;

            hres = GetLocalCLSID(szServerName, fErrorBox, &clsid);
            if (SUCCEEDED(hres)) {
                hres = ConnectToEventServer(NULL, clsid, fErrorBox, dwCoInit);
            }
            return hres;
        }




        //=========================================================================
        // Connects to the OPC Event Server with the specified Class ID on the
        // specified machine. if szMachineName is NULL or a NULL-String then
        // the local machine will be used. It is not necessary that the OPC
        // Browser object is installed on the local or on the remote machine.
        //=========================================================================

        /**
         * @fn    HRESULT OpcAccess::ConnectToEventServer( LPCTSTR szMachineName, CLSID clsidServer, BOOL fErrorBox, DWORD dwCoInit )
         *
         * @brief    Connects to event server.
         *
         * @param    szMachineName    Name of the machine.
         * @param    clsidServer      The clsid server.
         * @param    fErrorBox         true to error box.
         * @param    dwCoInit         The co initialise.
         *
         * @return    A HRESULT.
         */

        HRESULT OpcAccess::ConnectToEventServer(
            LPCTSTR szMachineName,
            CLSID   clsidServer,
            BOOL    fErrorBox,  // = TRUE
            DWORD   dwCoInit    // = COINIT_MULTITHREADED
        )
        {
            COSERVERINFO   SrvInfo, *pSrvInfo;
            DWORD          dwClsCtx;
            MULTI_QI       mqi;
            HRESULT        hres;

            if (iOPCEventServer_ != NULL) {            // Already connected
                if (fErrorBox) ErrorMessage(_T("Already connected to an OPC Event Server!"), E_FAIL);
                return E_FAIL;
            }

            hres = InitializeDCOM(fErrorBox, dwCoInit);
            if (FAILED(hres)) {
                return hres;                              // Error message already displayed
            }

            LPWSTR pszMachineNameW = NULL;

            // Set up the server info
            if (szMachineName && *szMachineName) {

#if defined (UNICODE) || defined (_UNICODE)
                pszMachineNameW = (LPTSTR)szMachineName;
#else
                hres = DupToWStr(szMachineName, &pszMachineNameW);
                if (FAILED(hres)) {
                    if (fErrorBox) ErrorMessage(_T("Cannot convert Machine Name to wide-character string !"), hres);
                    return hres;
                }
#endif

                SrvInfo.dwReserved1 = 0;
                SrvInfo.dwReserved2 = 0;
                SrvInfo.pAuthInfo = NULL;              // Use the default activation security.
                SrvInfo.pwszName = pszMachineNameW;
                pSrvInfo = &SrvInfo;
                dwClsCtx = CLSCTX_SERVER;
            }
            else {                                       // If no machine name is specified
                // then try local server
                pSrvInfo = NULL;
                dwClsCtx = CLSCTX_LOCAL_SERVER | CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER;
            }

            // Set up mqi
            mqi.pIID = &IID_IOPCEventServer;
            mqi.hr = 0;
            mqi.pItf = 0;

            hres = CoCreateInstanceEx(clsidServer, NULL, dwClsCtx, pSrvInfo, 1, &mqi);

            if (pszMachineNameW) {                       // Release temporary string copy
#if defined (UNICODE) || defined (_UNICODE)
        //
#else
                delete[] pszMachineNameW;
#endif
            }

            if (FAILED(hres) || FAILED(mqi.hr)) {
                DisconnectFromEventServer();
                if (SUCCEEDED(hres)) {
                    hres = mqi.hr;
                }
                if (fErrorBox) ErrorMessage(_T("Function 'CoCreateInstanceEx' failed !"), hres);
                return hres;
            }
            // All succeeded
            iOPCEventServer_ = (IOPCEventServer *)mqi.pItf;
            return S_OK;
        }




        //=========================================================================
        // DisconnectFromEventServer
        // -------------------------
        //    
        //=========================================================================

        void OpcAccess::DisconnectFromEventServer()
        {
            if (iOPCEventServer_) {                    // Release the Event Server Interface
                iOPCEventServer_->Release();
                iOPCEventServer_ = NULL;
            }

            if (m_pIOPCServer == NULL) {                 // Other things must be released only if there
                // is no connection to an Data Access Server

                if (m_pIMalloc) {                         // Release Global Interface to the COM memory manager.
                    m_pIMalloc->Release();
                    m_pIMalloc = NULL;
                }

                if (m_fCOMIsInitialized) {                // Uninitialize COM only if succesfully initialized.
                    CoUninitialize();
                    m_fCOMIsInitialized = FALSE;
                }
            }
        }

        //-------------------------------------------------------------------------
        // OPERATIONS Historical Server
        //-------------------------------------------------------------------------

        HRESULT OpcAccess::ConnectToHistoricalServer(
            LPCTSTR szMachineName,
            LPCTSTR szServerName,
            BOOL    fErrorBox,  // = TRUE
            DWORD   dwCoInit    // = COINIT_MULTITHREADED
        )
        {
            if (szMachineName && *szMachineName) {       // Remote Machine
                HRESULT  hres;
                CLSID    clsid;
                // Try if it is registered local
                hres = GetLocalCLSID(szServerName, FALSE, &clsid);
                if (FAILED(hres)) {

                    BOOL fReleaseCOMInitialization = FALSE;
                    if (!m_fCOMIsInitialized) {
                        hres = InitializeDCOM(fErrorBox, dwCoInit);
                        if (SUCCEEDED(hres)) {
                            fReleaseCOMInitialization = TRUE;
                        }
                        else {
                            return hres;
                        }
                    }
                    // Try it via the OPCBroser object
                    hres = GetRemoteCLSID(szMachineName, szServerName, fErrorBox, &clsid);

                    if (fReleaseCOMInitialization) {
                        DisconnectFromHistoricalServer();        // Release all DCOM Initialization
                    }
                }
                if (SUCCEEDED(hres)) {
                    hres = ConnectToHistoricalServer(szMachineName, clsid, fErrorBox, dwCoInit);
                }
                return hres;
            }
            else {                                       // If no machine name is specified
                // then try local server
                return ConnectToHistoricalServer(szServerName, fErrorBox, dwCoInit);
            }
        }




        //=========================================================================
        // Connects to the OPC Historical Server with the specified name on the
        // specified machine. If szMachineName is NULL or a NULL-String then the
        // local machine will be used. The Class ID associated with the server
        // name is retrieved from the local machine if available. Is the server is
        // not registered and a remote machine is specified then the OPC Browser
        // object on the remote machine is used to get the Class ID of the server.
        //=========================================================================

        /**
        * @fn    HRESULT OpcAccess::ConnectToHistoricalServer( LPCTSTR szServerName, BOOL fErrorBox, DWORD dwCoInit )
        *
        * @brief    Connects to historical server.
        *
        * @param    szServerName    Name of the server.
        * @param    fErrorBox       true to error box.
        * @param    dwCoInit        The co initialise.
        *
        * @return    A HRESULT.
        */

        HRESULT OpcAccess::ConnectToHistoricalServer(
            LPCTSTR szServerName,
            BOOL    fErrorBox,  // = TRUE
            DWORD   dwCoInit    // = COINIT_MULTITHREADED
        )
        {
            CLSID    clsid;
            HRESULT  hres;

            hres = GetLocalCLSID(szServerName, fErrorBox, &clsid);
            if (SUCCEEDED(hres)) {
                hres = ConnectToHistoricalServer(NULL, clsid, fErrorBox, dwCoInit);
            }
            return hres;
        }




        //=========================================================================
        // Connects to the OPC Historical Server with the specified Class ID on the
        // specified machine. if szMachineName is NULL or a NULL-String then
        // the local machine will be used. It is not necessary that the OPC
        // Browser object is installed on the local or on the remote machine.
        //=========================================================================

        /**
        * @fn    HRESULT OpcAccess::ConnectToHistoricalServer( LPCTSTR szMachineName, CLSID clsidServer, BOOL fErrorBox, DWORD dwCoInit )
        *
        * @brief    Connects to historical server.
        *
        * @param    szMachineName    Name of the machine.
        * @param    clsidServer      The clsid server.
        * @param    fErrorBox         true to error box.
        * @param    dwCoInit         The co initialise.
        *
        * @return    A HRESULT.
        */

        HRESULT OpcAccess::ConnectToHistoricalServer(
            LPCTSTR szMachineName,
            CLSID   clsidServer,
            BOOL    fErrorBox,  // = TRUE
            DWORD   dwCoInit    // = COINIT_MULTITHREADED
        )
        {
            COSERVERINFO   SrvInfo, *pSrvInfo;
            DWORD          dwClsCtx;
            MULTI_QI       mqi;
            HRESULT        hres;

            if (m_pIOPCHistoricalServer != NULL) {            // Already connected
                if (fErrorBox) ErrorMessage(_T("Already connected to an OPC Historical Server!"), E_FAIL);
                return E_FAIL;
            }

            hres = InitializeDCOM(fErrorBox, dwCoInit);
            if (FAILED(hres)) {
                return hres;                              // Error message already displayed
            }

            LPWSTR pszMachineNameW = NULL;

            // Set up the server info
            if (szMachineName && *szMachineName) {

#if defined (UNICODE) || defined (_UNICODE)
                pszMachineNameW = (LPTSTR)szMachineName;
#else
                hres = DupToWStr(szMachineName, &pszMachineNameW);
                if (FAILED(hres)) {
                    if (fErrorBox) ErrorMessage(_T("Cannot convert Machine Name to wide-character string !"), hres);
                    return hres;
                }
#endif

                SrvInfo.dwReserved1 = 0;
                SrvInfo.dwReserved2 = 0;
                SrvInfo.pAuthInfo = NULL;                    // Use the default activation security.
                SrvInfo.pwszName = pszMachineNameW;
                pSrvInfo = &SrvInfo;
                dwClsCtx = CLSCTX_SERVER;
            }
            else {                                            // If no machine name is specified
                // then try local server
                pSrvInfo = NULL;
                dwClsCtx = CLSCTX_LOCAL_SERVER | CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER;
            }

            // Set up mqi
            mqi.pIID = &IID_IOPCHDA_Server;
            mqi.hr = 0;
            mqi.pItf = 0;

            hres = CoCreateInstanceEx(clsidServer, NULL, dwClsCtx, pSrvInfo, 1, &mqi);

            if (pszMachineNameW) {                       // Release temporary string copy
#if defined (UNICODE) || defined (_UNICODE)
        //
#else
                delete[] pszMachineNameW;
#endif
            }

            if (FAILED(hres) || FAILED(mqi.hr)) {
                DisconnectFromHistoricalServer();
                if (SUCCEEDED(hres)) {
                    hres = mqi.hr;
                }
                if (fErrorBox) ErrorMessage(_T("Function 'CoCreateInstanceEx' failed !"), hres);
                return hres;
            }
            // All succeeded
            m_pIOPCHistoricalServer = (IOPCHDA_Server *)mqi.pItf;
            return S_OK;
        }




        //=========================================================================
        // DisconnectFromHistoricalServer
        // ------------------------------
        //    
        //=========================================================================

        void OpcAccess::DisconnectFromHistoricalServer()
        {
            if (m_pIOPCHistoricalServer) {                    // Release the Historical Server Interface
                m_pIOPCHistoricalServer->Release();
                m_pIOPCHistoricalServer = NULL;
            }

            if (m_pIOPCServer == NULL) {                 // Other things must be released only if there
                // is no connection to an Data Access Server

                if (m_pIMalloc) {                         // Release Global Interface to the COM memory manager.
                    m_pIMalloc->Release();
                    m_pIMalloc = NULL;
                }

                if (m_fCOMIsInitialized) {                // Uninitialize COM only if succesfully initialized.
                    CoUninitialize();
                    m_fCOMIsInitialized = FALSE;
                }
            }
        }

        //-------------------------------------------------------------------------
        // IMPLEMENTATION
        //-------------------------------------------------------------------------

        //=========================================================================
        // ErrorMessage
        // ------------
        //    Displays an error message in a message box. The detailed description
        //    of the error code will be added to the message.
        //
        // parameter: 
        //    szErrorMsg        Address of the string with the error
        //                      message to display.
        //    hres              Error code
        //
        //=========================================================================

        /**
         * @fn    void OpcAccess::ErrorMessage( LPCTSTR szErrorMsg, HRESULT hres )
         *
         * @brief    Error message.
         *
         * @param    szErrorMsg    Message describing the error.
         * @param    hres          The hres.
         */

        void OpcAccess::ErrorMessage(LPCTSTR szErrorMsg, HRESULT hres)
        {
            TCHAR szTitle[_MAX_PATH];
            TCHAR szMsg[512];

            _tcscpy(szMsg, szErrorMsg);                // Copy message text from user

            LPTSTR   pDescr = NULL;
            DWORD    dwLen;
            // Get the description of the error from the system.
            dwLen = FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,                            // No message source
                hres,                            // Error Code
                // Language Identifier
                LANGIDFROMLCID(LOCALE_SYSTEM_DEFAULT),
                (LPTSTR)&pDescr,                 // Output string buffer
                0,                               // no static message buffer
                NULL);                          // no message insertion.

            if (dwLen) {                                 // Description found
                _tcscat(szMsg, _T("\n\nError : "));
                _tcscat(szMsg, pDescr);                 // Add description to the message to display
                LocalFree(pDescr);
            }
            // Get Application Title
#ifdef _OCS_UNIX
            printf(": %lx\n", hres);
#else
    // Get Application Title
            HWND hWnd = GetActiveWindow();            // Return value may be NULL
            GetWindowText(hWnd, szTitle, sizeof(szTitle));
            // Display the message box with the error info
            MessageBox(hWnd, szMsg, szTitle, MB_OK | MB_ICONEXCLAMATION);
#endif
        }




        //=========================================================================
        // InitializeDCOM
        // --------------
        //    Initializes the COM library an gets access to the
        //    COM memory manager.
        //
        // parameter: 
        //    IN
        //       fErrorBox            Displays errors in a message box if
        //                            flag is TRUE.
        //       dwCoInit             Specifies the flags for the COM library
        //                            initialization.
        //
        // return:
        //    Return code of type HRESULT.
        //
        //=========================================================================

        /**
         * @fn    HRESULT OpcAccess::InitializeDCOM( BOOL fErrorBox, DWORD dwCoInit )
         *
         * @brief    Initializes the dcom.
         *
         * @param    fErrorBox    true to error box.
         * @param    dwCoInit     The co initialise.
         *
         * @return    A HRESULT.
         */

        HRESULT OpcAccess::InitializeDCOM(BOOL fErrorBox, DWORD dwCoInit)
        {
            if (m_fCOMIsInitialized) {
                return S_OK;                              // Already initialized
            }
            // General COM initialization
            HRESULT hres = CoInitializeEx(NULL, dwCoInit);
            if (FAILED(hres)) {
                if (fErrorBox) ErrorMessage(_T("Function 'CoInitializeEx' failed !"), hres);
                return hres;
            }
            m_fCOMIsInitialized = TRUE;                  // Now COM library is initialized successfully

            // Get access to the COM memory manager
            hres = CoGetMalloc(MEMCTX_TASK, &m_pIMalloc);
            if (FAILED(hres)) {
                CoUninitialize();                         // Uninitialize the COM library.
                m_fCOMIsInitialized = FALSE;
                if (fErrorBox) ErrorMessage(_T("Function 'CoGetMalloc' failed !"), hres);
                return hres;
            }

            // Use own security attributes for DCOM
            hres = CoInitializeSecurity(
                NULL,                   // There is no access-control list
                -1,                     // COM choose authentication services
                NULL,                   // Default authentication service
                NULL,                   // Reserved for future use 
                RPC_C_AUTHN_LEVEL_NONE,       // Default authentication level for proxies
                RPC_C_IMP_LEVEL_IMPERSONATE,  // Default impersonation level for proxies
                NULL,                   // Reserved; must be set to  NULL 
                EOAC_NONE,              // No additional capabilities
                NULL);                 // Reserved for future use 

            if (FAILED(hres)) {
                if (hres == RPC_E_TOO_LATE) {
                    hres = S_OK;                           // CoInitializeSecurity has already been called.
                }
            }
            return hres;
        }




        //=========================================================================
        // DupToWStr
        // ---------
        //    Duplicates a multy-byte string to a wide-char string.
        //    The returned wide-char string must be freed by the caller using
        //    the delete [] operator.
        //
        // parameter: 
        //    IN
        //       pszM                 The multi-byte string to be duplicated.
        //    OUT
        //      **pszW                Address where the wide-char string can
        //                            be strored.
        //
        // return:
        //    Return code of type HRESULT.
        //
        //=========================================================================

        /**
         * @fn    HRESULT OpcAccess::DupToWStr( LPCSTR pszM, LPWSTR* pszW )
         *
         * @brief    Duplicate to w string.
         *
         * @param    pszM            The m.
         * @param [in,out]    pszW    If non-null, the w.
         *
         * @return    A HRESULT.
         */

        HRESULT OpcAccess::DupToWStr(LPCSTR pszM, LPWSTR* pszW)
        {
            *pszW = new (std::nothrow) WCHAR[(strlen(pszM) + 1) * sizeof(WCHAR)];
            if (*pszW == NULL)
                return E_OUTOFMEMORY;

            size_t rtc = mbstowcs(*pszW, pszM, strlen(pszM) + 1);
            if (rtc != strlen(pszM)) {
                delete[] * pszW;
                *pszW = NULL;
                return E_FAIL;
            }
            return S_OK;
        }




        //=========================================================================
        // GetLocalCLSID
        // -------------
        //    Returns the Class ID associated with the specified server name from
        //    the Registry on the local machine.
        //
        // parameter: 
        //    IN
        //       wszServerName        Name of the OPC Server.
        //       fErrorBox            Displays errors in a message box if
        //                            flag is TRUE.
        //    OUT
        //       *pClsid              The associated Class ID.
        //
        // return:
        //    Return code of type HRESULT.
        //
        //=========================================================================

        /**
         * @fn    HRESULT OpcAccess::GetLocalCLSID( LPCTSTR szServerName, BOOL fErrorBox, LPCLSID pClsid )
         *
         * @brief    Gets local clsid.
         *
         * @param    szServerName    Name of the server.
         * @param    fErrorBox       true to error box.
         * @param    pClsid            The clsid.
         *
         * @return    The local clsid.
         */

        HRESULT OpcAccess::GetLocalCLSID(LPCTSTR szServerName, BOOL fErrorBox, LPCLSID pClsid)
        {
            // Get full server name
            LPWSTR lpszFullServerNameW;
            HRESULT hres = GetFullServerName(szServerName, &lpszFullServerNameW);
            if (FAILED(hres)) {
                if (fErrorBox) ErrorMessage(_T("Cannot read full Server Name from the Registry !"), hres);
                return hres;
            }
            // Get the CLSID from the server name
            hres = CLSIDFromProgID(lpszFullServerNameW, pClsid);
            delete[] lpszFullServerNameW;               // Full server name is no longer used

            if (FAILED(hres) && fErrorBox) {
                ErrorMessage(_T("Function 'CLSIDFromProgID' failed !"), hres);
            }
            return hres;
        }




        //=========================================================================
        // GetRemoteCLSID
        // --------------
        //    Returns he Class ID associated with the specified server name via
        //    the OPC Browser object on the specified remote machine.
        //
        //    Note :   This method assumes that InitializeDCOM() is called
        //             outside of this function.
        //
        // parameter: 
        //    IN
        //       szMachineName        Name of the remote machine.
        //       szServerName         Name of the OPC Server.
        //       fErrorBox            Displays errors in a message box if
        //                            flag is TRUE.
        //    OUT
        //       *pClsid              The associated Class ID.
        //
        // return:
        //    Return code of type HRESULT.
        //
        //=========================================================================

        /**
         * @fn    HRESULT OpcAccess::GetRemoteCLSID( LPCTSTR szMachineName, LPCTSTR szServerName, BOOL fErrorBox, LPCLSID pClsid )
         *
         * @brief    Gets remote clsid.
         *
         * @param    szMachineName    Name of the machine.
         * @param    szServerName     Name of the server.
         * @param    fErrorBox         true to error box.
         * @param    pClsid             The clsid.
         *
         * @return    The remote clsid.
         */

        HRESULT OpcAccess::GetRemoteCLSID(LPCTSTR szMachineName, LPCTSTR szServerName,
            BOOL fErrorBox, LPCLSID pClsid)
        {
            COSERVERINFO   SrvInfo;
            MULTI_QI       mqi;
            HRESULT        hres;

            LPWSTR pszMachineNameW = NULL;
            LPWSTR pszServerNameW = NULL;

#if defined (UNICODE) || defined (_UNICODE)
            pszMachineNameW = (LPTSTR)szMachineName;
            pszServerNameW = (LPTSTR)szServerName;
#else
            hres = DupToWStr(szMachineName, &pszMachineNameW);
            if (FAILED(hres)) {
                if (fErrorBox) ErrorMessage(_T("Cannot convert Machine Name to wide-character string !"), hres);
                return hres;
            }
            hres = DupToWStr(szServerName, &pszServerNameW);
            if (FAILED(hres)) {
                if (fErrorBox) ErrorMessage(_T("Cannot convert Server Name to wide-character string !"), hres);
                delete[] pszMachineNameW;
                return hres;
            }
#endif

            SrvInfo.dwReserved1 = 0;
            SrvInfo.dwReserved2 = 0;
            SrvInfo.pAuthInfo = NULL;                 // Use the default activation security.
            SrvInfo.pwszName = pszMachineNameW;

            // Set up mqi
            mqi.pIID = &IID_IOPCServerList;
            mqi.hr = 0;
            mqi.pItf = 0;
            // Note : CLSCTX_LOCAL_SERVER must be definied if the
            // machine name is the name of the local machine.
            hres = CoCreateInstanceEx(CLSID_OpcServerList, NULL,
                CLSCTX_REMOTE_SERVER | CLSCTX_LOCAL_SERVER,
                &SrvInfo, 1, &mqi);

            if (FAILED(hres) || FAILED(mqi.hr)) {
                if (SUCCEEDED(hres)) {
                    hres = mqi.hr;
                }
                if (fErrorBox) ErrorMessage(_T("Cannot connect to OPCBrowser on remote machine !"), hres);
            }
            else {
                // OPC Browser object created
                hres = ((IOPCServerList *)mqi.pItf)->CLSIDFromProgID(pszServerNameW, pClsid);
                ((IOPCServerList *)mqi.pItf)->Release();  // OPCBrowser Object no longer used
            }
            if (FAILED(hres) && fErrorBox) {
                ErrorMessage(_T("Function 'IOPCServerList::CLSIDFromProgID' on remote machine failed !"), hres);
            }

#if defined (UNICODE) || defined (_UNICODE)
            // 
#else                                           // Release temporary string copies
            delete[] pszMachineNameW;
            delete[] pszServerNameW;
#endif

            return hres;
        }




        //=========================================================================
        // GetFullServerName
        // -----------------
        //    If the specified server name is version independent then the full
        //    server name will be read from the Registry.
        //
        //    The returned server name must be freed by the caller using
        //    the delete [] operator.
        //
        // parameter: 
        //    IN
        //       szServerName         Name of the OPC Server.
        //    OUT
        //       *lpszFullServerName  Address of pointer where the text-string
        //                            with the full server name can be stored.
        // return:
        //    S_OK, E_OUTOFMEMORY
        //
        //=========================================================================

        /**
         * @fn    HRESULT OpcAccess::GetFullServerName( LPCTSTR szServerName, LPWSTR* lpszFullServerNameW )
         *
         * @brief    Gets full server name.
         *
         * @param    szServerName                   Name of the server.
         * @param [in,out]    lpszFullServerNameW    If non-null, the full server name w.
         *
         * @return    The full server name.
         */

        HRESULT OpcAccess::GetFullServerName(LPCTSTR szServerName, LPWSTR* lpszFullServerNameW)
        {
            TCHAR    szTmp[256];
            DWORD    wBufSize = sizeof(szTmp);
            HKEY     hProgID;

            // Create the name of the SubKey with the
            // version independent info.
            LPTSTR pszSubKey = new (std::nothrow) TCHAR[_tcslen(szServerName) + _tcslen(_T("\\CurVer")) + 1];
            if (pszSubKey == NULL) {
                return E_OUTOFMEMORY;
            }
            _tcscpy(pszSubKey, szServerName);
            _tcscat(pszSubKey, _T("\\CurVer"));
            // Check if we would connect to a version
            // indepenent OPC Server.
            if (RegOpenKeyEx(HKEY_CLASSES_ROOT,
                pszSubKey,                 // SubKey
                0,                         // Reserved, must be 0
                KEY_READ,                  // Security access mask
                &hProgID) == ERROR_SUCCESS) {

                if (RegQueryValueEx(hProgID,
                    NULL,                // Use default value
                    NULL,
                    NULL,
                    (LPBYTE)szTmp, &wBufSize)
                    == ERROR_SUCCESS) {
                    // The name of the Server to connect to is the name of a
                    // a version independent Server.
                    // Use the current version of the OPC Server.
                    szServerName = szTmp;

                } // Subkey has a 'CurVer' entry.

                RegCloseKey(hProgID);

            } // Subkey with defined Server name exist.

            delete[] pszSubKey;                         // No loger used.
            pszSubKey = NULL;
            // Build a wide char string with the full server name.
#if defined (UNICODE) || defined (_UNICODE)
    // Make a copy of the wide-char string.
            *lpszFullServerNameW = new (std::nothrow) WCHAR[wcslen(szServerName) + 1];
            if (*lpszFullServerNameW == NULL)
                return E_OUTOFMEMORY;

            if (wcscpy(*lpszFullServerNameW, szServerName) == NULL) {
                delete[](*lpszFullServerNameW);
                *lpszFullServerNameW = NULL;
                return E_FAIL;
            }
            return S_OK;
#else
            return DupToWStr(szServerName, lpszFullServerNameW);
#endif
        }
    }
}