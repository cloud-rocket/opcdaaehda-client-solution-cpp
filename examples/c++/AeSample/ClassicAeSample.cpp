/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: http://www.technosoftware.com 
 * 
 * License:
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include "stdafx.h"
#include "ClassicAeSample.h"
#include "MainFrm.h"
#include "ClassicAeSampleDoc.h"
#include "ClassicAeSampleView.h"


//----------------------------------------------------------------------------------------------------------------------
// DEBUG MACROS
//----------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//----------------------------------------------------------------------------------------------------------------------
// GLOBALS
//----------------------------------------------------------------------------------------------------------------------
CClassicAeSampleApp theApp;                       // The one and only CClassicAeSampleApp object


//----------------------------------------------------------------------------------------------------------------------
// OVERRIDES
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// InitInstance
// ------------
//    CClassicAeSampleApp initialization.
//----------------------------------------------------------------------------------------------------------------------
BOOL CClassicAeSampleApp::InitInstance()
{
   // InitCommonControls() is required on Windows XP if an application
   // manifest specifies use of ComCtl32.dll version 6 or later to enable
   // visual styles.  Otherwise, any window creation will fail.
   InitCommonControls();

   CWinApp::InitInstance();

   // Standard initialization
   // If you are not using these features and wish to reduce the size
   // of your final executable, you should remove from the following
   // the specific initialization routines you do not need
   // Change the registry key under which our settings are stored

   // This version stores no settings
   // SetRegistryKey(_T("Technosoftware"));

   // Register the application's document templates.  Document templates
   //  serve as the connection between documents, frame windows and views
   CSingleDocTemplate* pDocTemplate;
   pDocTemplate = new CSingleDocTemplate(
      IDR_MAINFRAME,
      RUNTIME_CLASS(CClassicAeSampleDoc),
      RUNTIME_CLASS(CMainFrame),       // main SDI frame window
      RUNTIME_CLASS(CClassicAeSampleView));
   AddDocTemplate(pDocTemplate);
   // Parse command line for standard shell commands, DDE, file open
   CCommandLineInfo cmdInfo;
   ParseCommandLine(cmdInfo);
   // Dispatch commands specified on the command line.  Will return FALSE if
   // app was launched with /RegServer, /Register, /Unregserver or /Unregister.
   if (!ProcessShellCommand(cmdInfo))
      return FALSE;
   // The one and only window has been initialized, so show and update it
   m_pMainWnd->ShowWindow(SW_SHOW);
   m_pMainWnd->UpdateWindow();
   // call DragAcceptFiles only if there's a suffix
   //  In an SDI app, this should occur after ProcessShellCommand

   // Open the Select Server Dialog
   m_pMainWnd->SendMessage( WM_COMMAND, ID_OPCEVENTSERVER_CONNECT );

   return TRUE;
}


//----------------------------------------------------------------------------------------------------------------------
// IMPLEMENTATION MESSAGE HANDLER 
//----------------------------------------------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CClassicAeSampleApp, CWinApp)
   // Standard file based document commands
   ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
   ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()
