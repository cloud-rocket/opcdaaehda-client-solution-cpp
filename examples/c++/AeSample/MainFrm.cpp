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
#include "ClassicAeSampleDoc.h"
#include "ClassicAeSampleView.h"
#include "MainFrm.h"


//----------------------------------------------------------------------------------------------------------------------
// DEBUG MACROS
//----------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//----------------------------------------------------------------------------------------------------------------------
// INTERNALS
//----------------------------------------------------------------------------------------------------------------------
static UINT indicators[] =
{
   ID_SEPARATOR,              // status line indicator
   ID_INDICATOR_SUBSCRIPTION, // displays the current status of the subscription object
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};


//----------------------------------------------------------------------------------------------------------------------
// CONSTRUCTION/DESTRUCTION
//----------------------------------------------------------------------------------------------------------------------

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}


//----------------------------------------------------------------------------------------------------------------------
// OVERRIDES
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// PreCreateWindow
// ---------------
//    Changes the default style so the application name is displayed before the name of the connected server.
//    (Required because the default behavior has changed in MFC 7.1).
//----------------------------------------------------------------------------------------------------------------------
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
   BOOL f = CFrameWnd::PreCreateWindow(cs);
   cs.style &= ~FWS_PREFIXTITLE;
   return f;
}


//----------------------------------------------------------------------------------------------------------------------
// OnCreateClient
// --------------
//    Called by the MFC framework during the execution of OnCreate. Never call this function directly.
//    Creates two splitter windows in the following order :
//
//          +---------------------------+
//          | Current Events View       |
//          | (CClassicAeSampleView)      |
//          |                           |
//          +---------------------------+
//          | History Events View       |
//          | (CClassicAeSampleView)      |
//          |                           |
//          +---------------------------+
//
// parameter:
//    lpcs        A pointer to a Windows CREATESTRUCT structure.
//    pContext    A pointer to a CCreateContext structure.
//
// return:
//    TRUE        creation successfully
//    FALSE       creation failed
//----------------------------------------------------------------------------------------------------------------------
BOOL CMainFrame::OnCreateClient( LPCREATESTRUCT lpcs,
                                 CCreateContext* pContext)
{
   if (!m_wndSplitter.CreateStatic(this,2,1))
   {
      TRACE0("Failed to create split bar\n");
      return FALSE;    // failed to create
   }
   if(!m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CClassicAeSampleView),CSize(10,200),pContext))
   {
      TRACE0("Failed to create the 'Current Events View'\n");
      return FALSE;    // failed to create
   }
   if(!m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(CClassicAeSampleView),CSize(10,100),pContext))
   {
      TRACE0("Failed to create the 'History Events View'\n");
      return FALSE;    // failed to create
   }
   return TRUE;
}


//----------------------------------------------------------------------------------------------------------------------
// IMPLEMENTATION MESSAGE HANDLER 
//----------------------------------------------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
   ON_WM_CREATE()
END_MESSAGE_MAP()


//----------------------------------------------------------------------------------------------------------------------
// OnCreate
// --------
//    The MFC framework calls this member function when an application requests that the Windows window be created
//    by calling the Create or CreateEx member function.
//
//    We add here the tool bar and the status bar to the main frame.
// 
// parameter:
//    lpCreateStruct    Points to a CREATESTRUCT structure that contains information about the CWnd object
//                      being created.
//
// return:
//    OnCreate must return 0 to continue the creation of the CWnd object.
//    If the application returns -1, the window will be destroy.
//----------------------------------------------------------------------------------------------------------------------
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
      return -1;

   if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
      | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
      !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }

   if (!m_wndStatusBar.Create(this) ||
      !m_wndStatusBar.SetIndicators(indicators,
      sizeof(indicators)/sizeof(UINT)))
   {
      TRACE0("Failed to create status bar\n");
      return -1;      // fail to create
   }

   m_wndToolBar.SetWindowText( _T("Session Handling") );
   m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
   EnableDocking(CBRS_ALIGN_ANY);
   DockControlBar(&m_wndToolBar);

   return 0;
}


//----------------------------------------------------------------------------------------------------------------------
// DIAGNOSTICS
//----------------------------------------------------------------------------------------------------------------------

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
   CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
   CFrameWnd::Dump(dc);
}
#endif //_DEBUG
