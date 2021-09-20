/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */


#ifndef __OPCACCESS_H
#define __OPCACCESS_H

#if defined( _OBJBASE_H_)           // objbase.h is already inlcuded
 // Test if DCOM is activated
#if ! ((_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM)) // no DCOM
#error _WIN32_DCOM must be defined in your project settings or in the included standard header file.
#endif

#else
#ifndef _WIN32_WCE
#define  _WIN32_DCOM 1        // Used for the CoInitializeEx function
#include <objbase.h>          // and the COM initialization flags.
#endif
#endif

#include "ClientSdk.h"
#include "OpcErrors.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {
         /**
          * @class  OpcAccess
          *
          * @brief  General OPC access functionality.
          */

         class OpcAccess
        {
            // Construction
        public:

            /**
             * @fn  OpcAccess();
             *
             * @brief   Default constructor.
             */

            OpcAccess();

            /**
             * @fn  virtual ~OpcAccess();
             *
             * @brief   Destructor.
             */

            virtual ~OpcAccess();

            // Attributes
        public:
            IOPCServer*         m_pIOPCServer;              // OPC Server Interface of OPCServer Object.
            IOPCEventServer*    iOPCEventServer_;           // OPC Server Interface of OPCEventServer Object.
            IOPCHDA_Server*     m_pIOPCHistoricalServer;    // OPC Server Interface of OPCHistoricalServer Object.
            IMalloc*            m_pIMalloc;                 // Interface to the COM memory manager.

         // Operations
        public:

            /**
             * @fn    HRESULT ConnectToServer(LPCTSTR szMachineName, LPCTSTR szServerName, BOOL fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED );
             *
             * @brief    Connects to the specified OPC Data Server
             *
             *             First all general stuff for COM is initialized. Then the class attributes m_pIMaloc
             *             and m_pIOPCServer are initialzed with the appropriate interface pointers from COM
             *             respectively the specified OPC Server. Errors are displayed in a message box (option
             *             can be inactivated with a function parameter).
             *
             *             Standard for local usage :
             *                 ConnectToServer( LPCTSTR szServerName, ... )
             *             Standard for remote usage :
             *                 ConnectToServer( LPCTSTR szMachineName, LPCTSTR szServerName,.)
             *             For remote usage if there is no OPC Browser object :
             *                 ConnectToServer( LPCTSTR szMachineName, CLSID clsidServer, ... )
             *
             * @param    szMachineName    Name  of the remote machine or NULL to use the local machine.
             * @param    szServerName     Name  of the OPC Data Server name to connect to. The version
             *                             independent Server name can be used only if the server is registered
             *                             on the local machine.
             * @param    fErrorBox         (Optional) Displays errors in a message box if flag is TRUE. Default
             *                             = TRUE.
             * @param    dwCoInit         (Optional) Specifies the flags for the COM library initialization.
             *                             Default = COINIT_MULTITHREADED.
             *
             * @return    This function supports the standard HRESULT return values.
             */

            HRESULT        ConnectToServer(LPCTSTR  szMachineName, LPCTSTR szServerName,
                BOOL     fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED);

            /**
             * @fn    void DisconnectFromServer();
             *
             * @brief    Disconnects from a previous connected OPC Data Server and releases all initialized
             *             interfaces if there is no connection to an OPC Event Server.
             */

            void           DisconnectFromServer();

        protected:
            HRESULT        ConnectToServer(LPCTSTR  szServerName,
                BOOL     fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED);

            HRESULT        ConnectToServer(LPCTSTR  szMachineName, CLSID clsidServer,
                BOOL     fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED);

            //
            // Event Server Functions
            //
        public:

            /**
             * @fn    HRESULT ConnectToEventServer( LPCTSTR szMachineName, LPCTSTR szServerName, BOOL fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED );
             *
             * @brief    Connects to the specified OPC Events Server
             *
             *                    First all general stuff for COM is initialized. Then the class attributes
             *                    m_pIMaloc and m_pIOPCEventServer are initialzed with the appropriate interface
             *                    pointers from COM respectively the specified OPC Server. Errors are displayed in
             *                    a message box (option can be inactivated with a function parameter).
             *
             *             @syntax
             *
             *                    Standard for local usage :
             *                       ConnectToEventServer(   LPCTSTR szServerName, ... )
             *                    Standard for remote usage :
             *                       ConnectToEventServer(   LPCTSTR szMachineName,
             *                                               LPCTSTR szServerName,.)
             *                    For remote usage if there is no OPC Browser object :
             *                       ConnectToEventServer(   LPCTSTR szMachineName,
             *                                               CLSID clsidServer, ... )
             *
             * @param    szMachineName    Name  of the remote machine or NULL to use the local machine.
             * @param    szServerName     Name  of the OPC Event Server name to connect
             *                                      to. The version independent Server name can be used only if
             *                                      the server is registered on the local machine.
             * @param    fErrorBox         (Optional) Displays errors in a message box if flag is TRUE.
             *                                      Default = TRUE.
             * @param    dwCoInit         (Optional) Specifies the flags for the COM library
             *                                      initialization. Default = COINIT_MULTITHREADED.
             *
             * @return    This function supports the standard HRESULT return values.
             */

            HRESULT        ConnectToEventServer(LPCTSTR  szMachineName, LPCTSTR szServerName,
                BOOL     fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED);

            /**
             * @fn    void DisconnectFromEventServer();
             *
             * @brief    Disconnects from a previous connected OPC Event Server and releases all initialized
             *             interfaces if there is no connection to an OPC Data Server.
             */

            void           DisconnectFromEventServer();


            vector<string> GetOPCServers(LPCTSTR  szMachineName, DWORD dwCoInit = COINIT_MULTITHREADED);


            //
            // Historical Server Functions
            //
        public:

            /**
            * @fn    HRESULT ConnectToHistoricalServer( LPCTSTR szMachineName, LPCTSTR szServerName, BOOL fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED );
            *
            * @brief    Connects to the specified OPC Historical Data Access Server
            *
            *                    First all general stuff for COM is initialized. Then the class attributes
            *                    m_pIMaloc and m_pIOPCEventServer are initialzed with the appropriate interface
            *                    pointers from COM respectively the specified OPC Server. Errors are displayed in
            *                    a message box (option can be inactivated with a function parameter).
            *
            *             @syntax
            *
            *                    Standard for local usage :
            *                       ConnectToEventServer(   LPCTSTR szServerName, ... )
            *                    Standard for remote usage :
            *                       ConnectToEventServer(   LPCTSTR szMachineName,
            *                                               LPCTSTR szServerName,.)
            *                    For remote usage if there is no OPC Browser object :
            *                       ConnectToEventServer(   LPCTSTR szMachineName,
            *                                               CLSID clsidServer, ... )
            *
            * @param    szMachineName    Name  of the remote machine or NULL to use the local machine.
            * @param    szServerName     Name  of the OPC Event Server name to connect
            *                                      to. The version independent Server name can be used only if
            *                                      the server is registered on the local machine.
            * @param    fErrorBox         (Optional) Displays errors in a message box if flag is TRUE.
            *                                      Default = TRUE.
            * @param    dwCoInit         (Optional) Specifies the flags for the COM library
            *                                      initialization. Default = COINIT_MULTITHREADED.
            *
            * @return    This function supports the standard HRESULT return values.
            */

            HRESULT        ConnectToHistoricalServer(LPCTSTR  szMachineName, LPCTSTR szServerName,
                BOOL     fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED);

            /**
            * @fn    void DisconnectFromHistoricalServer();
            *
            * @brief    Disconnects from a previous connected OPC Event Server and releases all initialized
            *             interfaces if there is no connection to an OPC Data Server.
            */

            void           DisconnectFromHistoricalServer();

        protected:
            HRESULT        ConnectToEventServer(LPCTSTR  szServerName,
                BOOL     fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED);

            HRESULT        ConnectToEventServer(LPCTSTR  szMachineName, CLSID clsidServer,
                BOOL     fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED);

            HRESULT        ConnectToHistoricalServer(LPCTSTR  szServerName,
                BOOL     fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED);

            HRESULT        ConnectToHistoricalServer(LPCTSTR  szMachineName, CLSID clsidServer,
                BOOL     fErrorBox = TRUE, DWORD dwCoInit = COINIT_MULTITHREADED);

            // Implementation
        protected:
            void        ErrorMessage(LPCTSTR szErrorMsg, HRESULT hres);

        private:
            HRESULT     DupToWStr(LPCSTR pszM, LPWSTR* pszW);
            HRESULT     GetFullServerName(LPCTSTR szServerName, LPWSTR* lpszFullServerNameW);
            HRESULT     GetLocalCLSID(LPCTSTR szServerName, BOOL fErrorBox, LPCLSID pClsid);
            HRESULT     GetRemoteCLSID(LPCTSTR szMachineName, LPCTSTR szServerName,
                BOOL fErrorBox, LPCLSID pClsid);

            HRESULT     InitializeDCOM(BOOL fErrorBox, DWORD dwCoInit);
            BOOL        m_fCOMIsInitialized;             // Flag if (D)COM library is initialized successfully.
        };
    }
}
#endif   // not defined __OPCACCESS_H
