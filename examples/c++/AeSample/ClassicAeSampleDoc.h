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

#pragma once

#include "DaAeHdaClient/OpcClientSdk.h"

#include "Base/Exception.h"

using namespace Technosoftware::Base;
using namespace Technosoftware::DaAeHdaClient;

//----------------------------------------------------------------------------------------------------------------------
// MACROS
//----------------------------------------------------------------------------------------------------------------------
#define  S2CT(s)   A2CT( s.c_str() )            // Text conversion macro: std::string to LPCTSTR


//----------------------------------------------------------------------------------------------------------------------
// DEFINES
//----------------------------------------------------------------------------------------------------------------------
#define  WM_DISPLAY_EVENT     (WM_USER + 1)


//----------------------------------------------------------------------------------------------------------------------
// CLASS MyEventHandlerClass
//----------------------------------------------------------------------------------------------------------------------
class CClassicAeSampleDoc;                        // forward declaration

class MyEventHandlerClass : public AeIEventSink
{
    // Construction / Destruction
public:
    MyEventHandlerClass(CClassicAeSampleDoc* pDoc) : m_pDoc(pDoc) {};
    ~MyEventHandlerClass() {}

    // Operations
public:
    inline CClassicAeSampleDoc* GetDocument() const { return m_pDoc; }
    // Called by the AeFramwork
    void NewEvents(AeNewEvents* pNewEvents);

    // Implementation
protected:
    CClassicAeSampleDoc* m_pDoc;
};


//----------------------------------------------------------------------------------------------------------------------
// CLASS CClassicAeSampleDoc
//----------------------------------------------------------------------------------------------------------------------
class CClassicAeSampleDoc : public CDocument
{
    // Creation / Destruction
protected: // create from serialization only
    CClassicAeSampleDoc();
    DECLARE_DYNCREATE(CClassicAeSampleDoc)
public:
    virtual ~CClassicAeSampleDoc();

    // Overrides
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);

    // Implementation
protected:
    //
    // Generated message map functions
    //
    DECLARE_MESSAGE_MAP()

    // Command handlers
    afx_msg void OnOpcEventServerConnect();
    afx_msg void OnOpcEventServerDisconnect();
    afx_msg void OnSubscriptionActivate();
    afx_msg void OnSubscriptionDeactivate();
    afx_msg void OnSubscriptionRefresh();
    afx_msg void OnSubscriptionToggle();

    // Update User Interface objects  
    afx_msg void OnUpdateOpcEventServerConnect(CCmdUI *pCmdUI);
    afx_msg void OnUpdateOpcEventServerDisconnect(CCmdUI *pCmdUI);
    afx_msg void OnUpdateSubscriptionDeactivate(CCmdUI *pCmdUI);
    afx_msg void OnUpdateSubscriptionRefresh(CCmdUI *pCmdUI);
    afx_msg void OnUpdateSubscriptionToggle(CCmdUI *pCmdUI);
    afx_msg void OnUpdateSubscriptionIndicator(CCmdUI *pCmdUI);
    afx_msg void OnUpdateSubscription(CCmdUI *pCmdUI);

    void EnablePopupMenu(CCmdUI* pCmdUI, BOOL fEnable);

    AeServer          m_OpcAeServer;
    AeSubscription*   m_pSubscr;
    MyEventHandlerClass  m_MyOpcEventHandler;

public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};
