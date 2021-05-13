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

#include "Base/DateTimeFormat.h"
#include "Base/DateTimeFormatter.h"

using namespace Technosoftware::Base;
using namespace Technosoftware::DaAeHdaClient;

//----------------------------------------------------------------------------------------------------------------------
// DEBUG MACROS
//----------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//----------------------------------------------------------------------------------------------------------------------
// INTERNALS
//----------------------------------------------------------------------------------------------------------------------
// Indexes of the columns (subitem)
static int iSOURCE;
static int iTIMESTAMP;
static int iMESSAGE;
static int iTYPE;
static int iCATEGORY;
static int iSEVERITY;
static int iCOND;
static int iSUBCOND;
static int iCHANGEMASK;
static int iNEWSTATE;
static int iQUALITY;
static int iACKREQ;
static int iACTIVETIME;
static int iCOOKIE;
static int iACTORID;
static int iSERVER;


//----------------------------------------------------------------------------------------------------------------------
// CONSTRUCTION/DESTRUCTION
//----------------------------------------------------------------------------------------------------------------------

IMPLEMENT_DYNCREATE(CClassicAeSampleView, CListView)

CClassicAeSampleView::CClassicAeSampleView()
{
   m_dwDefaultStyle |= LVS_REPORT;
}

CClassicAeSampleView::~CClassicAeSampleView()
{
}


//----------------------------------------------------------------------------------------------------------------------
// OPERATIONS
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Clear
// -----
//    Removes all Event descriptions from the List View.
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleView::Clear()
{
   GetListCtrl().DeleteAllItems();
}


//----------------------------------------------------------------------------------------------------------------------
// OVERRIDES
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// OnInitialUpdate
// ---------------
//    Called by the MFC framework after the view is first attached to the frame window.
//
//    The columns of the List View are created. This function also initializes the column indexes.
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleView::OnInitialUpdate()
{
   ASSERT( GetStyle() & LVS_REPORT );           // This code only works for a report-mode list view

   CListView::OnInitialUpdate();                // Call the base class member

   struct _tagColumnInfo {
      LPTSTR   szText;
      int      cx;
      int*     iSubItem;
   }
   *pColumn,
                  //    ColumnText           Width SubItemIndex
   aColumnInfo[] =  { { _T("Source"),        120,  &iSOURCE       },
                      { _T("Time Stamp"),     80,  &iTIMESTAMP    },
                      { _T("Message"),       120,  &iMESSAGE      }, 
                      { _T("Type"),           60,  &iTYPE         },
                      { _T("Category"),       60,  &iCATEGORY     },
                      { _T("Severity"),       60,  &iSEVERITY     }, 
                      { _T("Condition"),     140,  &iCOND         },
                      { _T("Subcondition"),  140,  &iSUBCOND      },
                      { _T("Change Mask"),   180,  &iCHANGEMASK   },
                      { _T("New State"),     180,  &iNEWSTATE     },
                      { _T("Quality"),       200,  &iQUALITY      },
                      { _T("Ack Required"),   80,  &iACKREQ       },
                      { _T("Active Time"),    80,  &iACTIVETIME   },
                      { _T("Cookie"),         60,  &iCOOKIE       },
                      { _T("ActorID"),       120,  &iACTORID      },
                      { NULL,                  0,  NULL           }
                     };
                     // Note: The column for the Event Attributes is not
                     //       created because the Event Subscription has
                     //       not selected attributes.

   CListCtrl& list = GetListCtrl();

   LV_COLUMN lvc;
   lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;

   int i = 0;
   pColumn = aColumnInfo; 

   while (pColumn->szText) {
      lvc.iSubItem = *pColumn->iSubItem = i;
      lvc.pszText = pColumn->szText;
      lvc.cx = pColumn->cx;
      list.InsertColumn( i, &lvc );
      pColumn++;
      i++;
   }
}


//----------------------------------------------------------------------------------------------------------------------
// IMPLEMENTATION MESSAGE HANDLER
//----------------------------------------------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CClassicAeSampleView, CListView)
   ON_MESSAGE( WM_DISPLAY_EVENT, OnDisplayEvent )
END_MESSAGE_MAP()


//----------------------------------------------------------------------------------------------------------------------
// OnDisplayEvent
// --------------
//    Displays the description of an event.
//    If this view class instance is the
//    - 'History Events View' then the description is added to the List View.
//    - 'Current Events View' then the description is updated or added if it not yet exist.
//
// parameter:
//    wParam      Specifies the View Type: 0=Current Events View, 1=History Events View
//    lParam      Pointer to the event of type AeEvent
//
// return:
//    0
//----------------------------------------------------------------------------------------------------------------------
LRESULT CClassicAeSampleView::OnDisplayEvent( WPARAM wParam, LPARAM lParam )
{
   CListCtrl&  list = GetListCtrl();
   AeEvent& event = *(AeEvent*)lParam;  

   if (wParam == 0) {                           // Refresh the Current Events View
      if (!UpdateEvent( event )) {
         AfxMessageBox( _T("Cannot update Event in the 'Current Events View'") );
      }
   }
   else {                                       // Add the Event to the Events History View
      if (list.GetItemCount() >= 1000) {        // Events History View is limited to 1000 entries
         Clear();
      }
      if (!AddEvent( event )) {
         AfxMessageBox( _T("Cannot add Event to the 'History Events View'") );
      }
   }
   return 0;
}


//----------------------------------------------------------------------------------------------------------------------
// IMPLEMENTATION
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// AddEvent
// --------
//    Inserts the description of the specified Event into the List View.
//----------------------------------------------------------------------------------------------------------------------
BOOL CClassicAeSampleView::AddEvent( AeEvent& event )
{
   CListCtrl&  list = GetListCtrl();
   LV_ITEM     lv_item;

   lv_item.mask      = LVIF_PARAM;
   lv_item.iItem     = 0;                       // Insert item ahead
   lv_item.iSubItem  = 0;
   lv_item.lParam    = event.GetCookie();
   
   int iItem = list.InsertItem( &lv_item );     // Insert item in List View
   if (iItem == -1) {
      return FALSE;
   }
   UpdateItem( iItem, event );                  // Initialize item with Event description
   return TRUE;
}


//----------------------------------------------------------------------------------------------------------------------
// UpdateEvent
// -----------
//    Refreshs the description of the specified Event in the List View if it's a condition-related Event. A new
//    description is inserted if the description not yet exist or if the event type is not condition-related.
//----------------------------------------------------------------------------------------------------------------------
BOOL CClassicAeSampleView::UpdateEvent( AeEvent& event )
{
   CListCtrl&  list = GetListCtrl();
   int         iItem = -1;

   if (event.GetEventType() == OPC_CONDITION_EVENT) {
      LVFINDINFO  lv_info;                      // Search the specified item if it's a condition-related Event
      lv_info.flags  = LVFI_PARAM;
      lv_info.lParam = event.GetCookie();

      iItem = list.FindItem( &lv_info );
   }

   if (iItem == -1) {                           // Not found, insert new description
      return AddEvent( event );
   }
   else {                                       // Found, refresh description
      UpdateItem( iItem, event );
      return TRUE;
   }
}


//----------------------------------------------------------------------------------------------------------------------
// UpdateItem
// ----------
//    Updates all columns of an item with the descriprion of the specified Event.
//----------------------------------------------------------------------------------------------------------------------
void CClassicAeSampleView::UpdateItem( int iItem, AeEvent& event )
{
   CString     str;
   CListCtrl&  list = GetListCtrl();

   // Source
   list.SetItemText( iItem, iSOURCE, S2CT( event.GetSource() ) );

   // Time Stamp
   list.SetItemText( iItem, iTIMESTAMP, S2CT( DateTimeFormatter::Format(event.GetTime(), DateTimeFormat::ISO8601_FORMAT) ) );

   // Message
   list.SetItemText( iItem, iMESSAGE, S2CT( event.GetMessage() ) );

   // Type
   list.SetItemText( iItem, iTYPE, S2CT( event.GetEventTypeAsText() ) );

   // Category
   str.Format( _T("%lu"), event.GetEventCategory() );
   list.SetItemText( iItem, iCATEGORY, str );

   // Severity
   str.Format( _T("%lu"), event.GetSeverity() );
   list.SetItemText( iItem, iSEVERITY, str );

   // Attributes
   //    None selected

   // Values which are present only for Condition-Related Events
   if (event.GetEventType() == OPC_CONDITION_EVENT) {

      // Condition
      list.SetItemText( iItem, iCOND, S2CT( event.GetConditionName() ) );
      
      // Subcondition
      list.SetItemText( iItem, iSUBCOND, S2CT( event.GetSubconditionName() ) );
      
      // Change Mask
      list.SetItemText( iItem, iCHANGEMASK, S2CT( event.GetChangeMaskAsText() ) );
      
      // New State
      list.SetItemText( iItem, iNEWSTATE, S2CT( event.GetNewStateAsText() ) );
      
      // Quality
      list.SetItemText( iItem, iQUALITY, S2CT( event.GetQualityAsText() ) );
      
      // Ack Required
      list.SetItemText( iItem, iACKREQ, event.IsAckRequired() ? _T("Yes") : _T("No") );
      
      // Active Time
      list.SetItemText( iItem, iACTIVETIME, S2CT(DateTimeFormatter::Format(event.GetActiveTime(), DateTimeFormat::ISO8601_FORMAT) ) );
      
      // Cookie
      str.Format( _T("%lu"), event.GetCookie() );
      list.SetItemText( iItem, iCOOKIE, str );

   } // Condition-related Events

   // ActorID
   list.SetItemText( iItem, iACTORID, S2CT( event.GetActorId() ) );
}


//----------------------------------------------------------------------------------------------------------------------
// DIAGNOSTICS
//----------------------------------------------------------------------------------------------------------------------

#ifdef _DEBUG
void CClassicAeSampleView::AssertValid() const
{
   CListView::AssertValid();
}

void CClassicAeSampleView::Dump(CDumpContext& dc) const
{
   CListView::Dump(dc);
}

CClassicAeSampleDoc* CClassicAeSampleView::GetDocument() const // non-debug version is inline
{
   ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClassicAeSampleDoc)));
   return (CClassicAeSampleDoc*)m_pDocument;
}
#endif //_DEBUG
