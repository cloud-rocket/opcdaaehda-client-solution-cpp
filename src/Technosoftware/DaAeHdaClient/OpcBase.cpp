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

#include "OpcInternal.h"
#include "Base/Exception.h"

namespace Technosoftware
{
    namespace DaAeHdaClient
    {

        using namespace Base;

        /**
         * @class    OpcObjectPtrArray
         *
         * @brief    An opc object pointer array.
         */

        class OpcObjectPtrArray : public CSimpleArray<OpcObject*> {};

        OpcObject::OpcObject(OpcObject* parent, const char* name) noexcept(false)
        {
            m_parChilds.Attach(new (std::nothrow) OpcObjectPtrArray);
            if (!m_parChilds) throw OutOfMemoryException();

            if (name) {
                try {
                    m_sName = name;
                }
                catch (...) {
                    throw OutOfMemoryException();
                }
            }
            m_pParent = parent;
            if (m_pParent) {
                m_pParent->AddChild(this);              // add object to parent
            }
        }

        /**
         * @fn    OpcObject::~OpcObject() throw ()
         *
         * @brief    Destroys the object and deleting all its child objects.
         */

        OpcObject::~OpcObject() noexcept
        {
            try {
                if (m_pParent) {
                    m_pParent->RemoveChild(this);        // remove object from parent
                }
                int n = m_parChilds->GetSize();           // remove all children
                while (n--) {
                    (*m_parChilds)[n]->m_pParent = NULL;   // prevents element remove from this array
                    delete (*m_parChilds)[n];
                }
                m_parChilds->RemoveAll();
            }
            catch (...) {}
        }

        /**
         * @fn  void OpcObject::DeleteAllChildren() throw ()
         *
         * @brief   Removes and destroys all child objects.
         */

        void OpcObject::DeleteAllChildren() throw ()
        {
            try {
                int n = m_parChilds->GetSize();           // remove all children
                while (n--) {
                    (*m_parChilds)[n]->m_pParent = nullptr;   // prevents element remove from this array
                    delete (*m_parChilds)[n];
                }
                m_parChilds->RemoveAll();
            }
            catch (...) {}
        }

        void OpcObject::AddChild(OpcObject* pChild) noexcept(false)
        {
            if (!pChild) throw InvalidArgumentException();
            if (!m_parChilds->Add(pChild)) throw OutOfMemoryException();
        }

        void OpcObject::RemoveChild(OpcObject* child) noexcept(false)
        {
            if (!child) throw Technosoftware::Base::InvalidArgumentException();
            if (!m_parChilds->Remove(child)) throw Technosoftware::Base::NotFoundException();
        }

        //----------------------------------------------------------------------------------------------------------------------
        // CODE CComOPCShutdownImpl
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    CComOPCShutdownImpl::CComOPCShutdownImpl()
         *
         * @brief    Default constructor.
         */

        CComOPCShutdownImpl::CComOPCShutdownImpl()
        {
            m_pfnShutdownRequestSink = NULL;
        }

        /**
         * @fn    void CComOPCShutdownImpl::Create( void (*pfnShutdownRequestSink)( string& sReason ) )
         *
         * @brief    Creates this object.
         *
         * @param [in,out]    pfnShutdownRequestSink    If non-null, the pfn shutdown request sink.
         */

        void CComOPCShutdownImpl::Create(void(*pfnShutdownRequestSink)(string& sReason))
        {
            _ASSERTE(pfnShutdownRequestSink);
            m_pfnShutdownRequestSink = pfnShutdownRequestSink;
        }

        /**
         * @fn    CComOPCShutdownImpl::~CComOPCShutdownImpl()
         *
         * @brief    Destructor.
         */

        CComOPCShutdownImpl::~CComOPCShutdownImpl()
        {
        }


        //----------------------------------------------------------------------------------------------------------------------
        // IOPCShutdown::ShutdownRequest
        // -----------------------------
        //    Forwards the received Shutdown Resuest from the OPC Server to the user sink.
        //----------------------------------------------------------------------------------------------------------------------

        /**
         * @fn    STDMETHODIMP CComOPCShutdownImpl::ShutdownRequest( LPCWSTR szReason )
         *
         * @brief    Shutdown request.
         *
         * @param    szReason    The reason.
         *
         * @return    A STDMETHODIMP.
         */

        STDMETHODIMP CComOPCShutdownImpl::ShutdownRequest(
            /* [in] */           LPCWSTR     szReason)
        {
            USES_CONVERSION;
            m_pfnShutdownRequestSink(string(W2A(szReason)));
            return S_OK;                                 // Must be be always S_OK
        }
    }
}