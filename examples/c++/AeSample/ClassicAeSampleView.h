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


//----------------------------------------------------------------------------------------------------------------------
// CLASS CClassicAeSampleView
//----------------------------------------------------------------------------------------------------------------------
class CClassicAeSampleView : public CListView
{
// Construction / Destruction
protected: // create from serialization only
   CClassicAeSampleView();
   DECLARE_DYNCREATE(CClassicAeSampleView)
public:
   virtual ~CClassicAeSampleView();

// Attributes
public:
   CClassicAeSampleDoc* GetDocument() const;

// Operations
public:
   void Clear();

// Overrides
protected:
   virtual void OnInitialUpdate(); // called first time after construct

// Implementation
protected:
   // Generated message map functions
   DECLARE_MESSAGE_MAP()
   afx_msg LRESULT OnDisplayEvent( WPARAM wParam, LPARAM lParam );

   BOOL  AddEvent( AeEvent& event );
   BOOL  UpdateEvent( AeEvent& event );
   void  UpdateItem( int iItem, AeEvent& event );

public:
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif
};

#ifndef _DEBUG  // debug version in ClassicAeSampleView.cpp
inline CClassicAeSampleDoc* CClassicAeSampleView::GetDocument() const
   { return reinterpret_cast<CClassicAeSampleDoc*>(m_pDocument); }
#endif
