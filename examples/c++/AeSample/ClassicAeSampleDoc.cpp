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
#include "SelectServerDlg.h"


//----------------------------------------------------------------------------------------------------------------------
// DEBUG MACROS
//----------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//----------------------------------------------------------------------------------------------------------------------
// NewEvents
// ---------
//    The event sink called by the SDK if there are new events from the AE Server.
//    It's the responsibility of the user to release the forwarded events using the delete operator.
//----------------------------------------------------------------------------------------------------------------------
void MyEventHandlerClass::NewEvents( AeNewEvents* newEvents )
{
   CClassicAeSampleDoc* pDoc = GetDocument();
   _ASSERTE( pDoc );

   AeEvent* pEvent;
   while (pEvent = newEvents->DetachEvent()) {
      WPARAM   wViewCount = 0;                  // Specifies the View Type: 0 Current Events View, 1 History Events View
      POSITION pos = pDoc->GetFirstViewPosition();
      while (pos != NULL) {
         CView* pView = pDoc->GetNextView(pos);
         if (pView) {
            pView->SendMessage( WM_DISPLAY_EVENT, wViewCount++, (LPARAM)pEvent );
         }
      }
      delete pEvent;
   }
   delete newEvents;
}


//----------------------------------------------------------------------------------------------------------------------
// CONSTRUCTION/DESTRUCTION
//----------------------------------------------------------------------------------------------------------------------

IMPLEMENT_DYNCREATE(CClassicAeSampleDoc, CDocument)

CClassicAeSampleDoc::CClassicAeSampleDoc() : m_MyOpcEventHandler( this )
{
   m_pSubscr = NULL;
}

CClassicAeSampleDoc::~CClassicAeSampleDoc()
{
}


//----------------------------------------------------------------------------------------------------------------------
// OVERRIDES
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// OnNewDocument
//----------------------------------------------------------------------------------------------------------------------
BOOL CClassicAeSampleDoc::OnNewDocument()
{
   if (!CDocument::OnNewDocument())
      return FALSE;

   SetTitle( _T("Not connected") );
   return TRUE;
}


//----------------------------------------------------------------------------------------------------------------------
// Serialize
// ---------
// parameter:
//    & ar           A CArchive object to serialize to or from.
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleDoc::Serialize(CArchive& ar)
{
   if (ar.IsStoring())
   {
   }
   else
   {
   }
}


//----------------------------------------------------------------------------------------------------------------------
// IMPLEMENTATION MESSAGE HANDLER 
//----------------------------------------------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CClassicAeSampleDoc, CDocument)
   ON_COMMAND(ID_OPCEVENTSERVER_CONNECT, OnOpcEventServerConnect)
   ON_COMMAND(ID_OPCEVENTSERVER_DISCONNECT, OnOpcEventServerDisconnect)
   ON_COMMAND(ID_SUBSCRIPTION_ACTIVATE, OnSubscriptionActivate)
   ON_COMMAND(ID_SUBSCRIPTION_DEACTIVATE, OnSubscriptionDeactivate)
   ON_COMMAND(ID_SUBSCRIPTION_REFRESH, OnSubscriptionRefresh)
   ON_COMMAND(ID_SUBSCRIPTION_TOGGLE, OnSubscriptionToggle)
   ON_UPDATE_COMMAND_UI(ID_OPCEVENTSERVER_CONNECT, OnUpdateOpcEventServerConnect)
   ON_UPDATE_COMMAND_UI(ID_OPCEVENTSERVER_DISCONNECT, OnUpdateOpcEventServerDisconnect)
   ON_UPDATE_COMMAND_UI(ID_SUBSCRIPTION_DEACTIVATE, OnUpdateSubscriptionDeactivate)
   ON_UPDATE_COMMAND_UI(ID_SUBSCRIPTION_REFRESH, OnUpdateSubscriptionRefresh)
   ON_UPDATE_COMMAND_UI(ID_SUBSCRIPTION_TOGGLE, OnUpdateSubscriptionToggle)
   ON_UPDATE_COMMAND_UI(ID_INDICATOR_SUBSCRIPTION, OnUpdateSubscriptionIndicator)
   ON_UPDATE_COMMAND_UI(ID_SUBSCRIPTION_ACTIVATE, OnUpdateSubscription)
END_MESSAGE_MAP()


//----------------------------------------------------------------------------------------------------------------------
// OnOpcEventServerConnect
// -----------------------
//    This method tries to connect to the specified OPC Server.
//    If connected successfully, this method also registers the name of the client with the server and
//    creates an event subscription object to receive event notifications.
//    A dialog box is opened first to specify the name of the server. 
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleDoc::OnOpcEventServerConnect()
{
   try {
      CSelectServerDlg  dlg;                    // Open dialog to specify the Server
      if (dlg.DoModal() != IDOK) {
         return;
      }
      CWaitCursor cur;                          // Try to connect
	  Status res = m_OpcAeServer.Connect((LPCSTR)dlg.m_strServerName, (LPCSTR)dlg.m_strMachineName);
      cur.Restore();
      if (res.IsError()) {
         string sMsg = "Cannot connect to the specified OPC Server: " + res.ToString();
         AfxMessageBox(S2CT( sMsg ) );
         return;
      }
                                                // Add the name of the Server to the Application title
      SetTitle( "Connected to '" + dlg.m_strServerName + "'" );

      res = m_OpcAeServer.RegisterClientName( "Technosoftware's <OPC AE Sample>", true );
      if (res.IsError()) {
         string sMsg = "Cannot register the name of the client with the server: " + res.ToString();
         AfxMessageBox( S2CT( sMsg ) );         // Only warning
      }

      m_pSubscr = new AeSubscription( &m_OpcAeServer, &m_MyOpcEventHandler, 0x55 );
   }
   catch (Technosoftware::Base::Exception e) {      // Handle SDK exceptions
      string sMsg = "Error occured in object " + e.GetDisplayText();
      AfxMessageBox( S2CT( sMsg ) );
   }
   catch (CException* e) {                      // Handle MFC exceptions
      e->ReportError();
   }
   catch (...) {                                // Handle all other exceptions
      AfxMessageBox( "Error occured" );
   }
}


//----------------------------------------------------------------------------------------------------------------------
// OnOpcEventServerDisconnect
// --------------------------
//    Disconnects from the connected OPC Server and clear all views.
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleDoc::OnOpcEventServerDisconnect()
{
   m_pSubscr = NULL;                            // Clear the reference pointer before Disconnect() removes the instance
   m_OpcAeServer.Disconnect();

   SetTitle( _T("Not connected") );             // Remove the name of the Server from the Application title
                                                
   POSITION pos = GetFirstViewPosition();       // Clear all views
   while (pos != NULL) {
      static_cast<CClassicAeSampleView*>(GetNextView(pos))->Clear();
   }
}


//----------------------------------------------------------------------------------------------------------------------
// OnSubscriptionActivate
// ----------------------
//    Sets the state of the event subscription to active.
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleDoc::OnSubscriptionActivate()
{
   Status res = m_pSubscr->SetActive();
   if (res.IsError()) {
      string sMsg = "Cannot activate the Event Subscription: " + res.ToString();
      AfxMessageBox( S2CT( sMsg ) );
   }
}


//----------------------------------------------------------------------------------------------------------------------
// OnSubscriptionDeactivate
// ------------------------
//    Sets the state of the event subscription to inactive.
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleDoc::OnSubscriptionDeactivate()
{
   Status res = m_pSubscr->SetActive( false );
   if (res.IsError()) {
      string sMsg = "Cannot deactivate the Event Subscription: " + res.ToString();
      AfxMessageBox( S2CT( sMsg ) );
   }
}


//----------------------------------------------------------------------------------------------------------------------
// OnSubscriptionRefresh
// ---------------------
//    Forces a Refresh for all active conditions and inactive, unacknowledged conditions.
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleDoc::OnSubscriptionRefresh()
{
   POSITION pos = GetFirstViewPosition();
   static_cast<CClassicAeSampleView*>(GetNextView(pos))->Clear();
   Status res = m_pSubscr->Refresh();
   if (res.IsError()) {
      string sMsg = "Cannot refresh the Event Subscription: " + res.ToString();
      AfxMessageBox( S2CT( sMsg ) );
   }
}


//----------------------------------------------------------------------------------------------------------------------
// OnSubscriptionToggle
// --------------------
//    Toggles the current state of the event subscription.
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleDoc::OnSubscriptionToggle()
{
   Status res = m_pSubscr->ToggleActive();
   if (res.IsError()) {
      string sMsg = "Cannot activate or deactivate the Event Subscription: " + res.ToString();
      AfxMessageBox( S2CT( sMsg ) );
   }
}


//----------------------------------------------------------------------------------------------------------------------
// OnUpdateOpcEventServerConnect
// OnUpdateOpcEventServerDisconnect
// OnUpdateSubscriptionDeactivate
// OnUpdateSubscriptionRefresh
// OnUpdateSubscriptionToggle
// OnUpdateSubscriptionIndicator
// -----------------------------
//    Update User Interface objects appropriate to the current state.
// 
// parameter:
//    pCmdUI      A pointer to the user interface object to be updated.
//----------------------------------------------------------------------------------------------------------------------

void CClassicAeSampleDoc::OnUpdateOpcEventServerConnect(CCmdUI *pCmdUI)
{
   pCmdUI->Enable( !m_OpcAeServer.IsConnected() );
}

void CClassicAeSampleDoc::OnUpdateOpcEventServerDisconnect(CCmdUI *pCmdUI)
{
   pCmdUI->Enable( m_OpcAeServer.IsConnected() );
}

void CClassicAeSampleDoc::OnUpdateSubscriptionDeactivate(CCmdUI *pCmdUI)
{
   if (m_pSubscr)
      pCmdUI->Enable( m_pSubscr->IsActive() );
}

void CClassicAeSampleDoc::OnUpdateSubscriptionRefresh(CCmdUI *pCmdUI)
{
   pCmdUI->Enable( m_pSubscr ? TRUE : FALSE );
}

void CClassicAeSampleDoc::OnUpdateSubscriptionToggle(CCmdUI *pCmdUI)
{
   if (m_pSubscr) {
      pCmdUI->Enable( TRUE );
      pCmdUI->SetCheck( !m_pSubscr->IsActive() );
   }
   else {
      pCmdUI->Enable( FALSE );
      pCmdUI->SetCheck( 0 );
   }
}

void CClassicAeSampleDoc::OnUpdateSubscriptionIndicator(CCmdUI *pCmdUI)
{
   pCmdUI->Enable();
   if (m_pSubscr) {
      if (m_pSubscr->IsActive()) {
         pCmdUI->SetText( _T("Active Subscription") );
      }
      else {
         pCmdUI->SetText( _T("Inactive Subscription") );
      }
   }
   else {
      pCmdUI->SetText( _T("No Subscription") );
   }
}

//----------------------------------------------------------------------------------------------------------------------
// OnUpdateSubscription
// --------------------
//    Update handler for Menu Items with Submenus (popup menu items).
//    Be sure this menu update handler is attached to the first item of the submenu.
// 
// parameter:
//    pCmdUI      A pointer to the user interface object of the first subitem of a popup menu item to be updated.
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleDoc::OnUpdateSubscription(CCmdUI *pCmdUI)
{
   if (m_pSubscr) {
      EnablePopupMenu( pCmdUI, TRUE );
      pCmdUI->Enable( !m_pSubscr->IsActive() );
   }
   else {
      EnablePopupMenu( pCmdUI, FALSE );
   }
}


//----------------------------------------------------------------------------------------------------------------------
// IMPLEMENTATION
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// EnablePopupMenu
// ---------------
//    Enables or diables a popup menu item.
//
// parameter:
//    pCmdUI      Must be a pointer to the user interface object of the first subitem of the popup menu item to enable.
//    fEnable     New state of the popup menu item. 
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleDoc::EnablePopupMenu( CCmdUI* pCmdUI, BOOL fEnable )
{
   if (pCmdUI->m_pSubMenu != NULL) {
      // CCmdUI::Enable is a no-op for this case, so we must do what it would have done.
      pCmdUI->m_pMenu->EnableMenuItem( pCmdUI->m_nIndex,
            MF_BYPOSITION | 
            (fEnable ? MF_ENABLED : (MF_DISABLED | MF_GRAYED)));
   }
}


//----------------------------------------------------------------------------------------------------------------------
// DIAGNOSTICS
//----------------------------------------------------------------------------------------------------------------------

#ifdef _DEBUG
void CClassicAeSampleDoc::AssertValid() const
{
   CDocument::AssertValid();
}

void CClassicAeSampleDoc::Dump(CDumpContext& dc) const
{
   CDocument::Dump(dc);
}
#endif //_DEBUG
