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

#ifndef __OPBASE_H
#define __OPBASE_H

#include <ostream>
#include <string>
using namespace std;

#include "ClientBase.h"
#include "Base/Exception.h"

/**
 *
 * @namespace Technosoftware::DaAeHdaClient
 * @brief Technosoftware::DaAeHdaClient contains the API used by OPC DA/AE/HDA Clients.
 */
 
/**
 *
 * @defgroup DaAeHdaClient Technosoftware DA/AE/HDA Client API
 * @brief The DaAeHdaClient group bundles all code usable by Technosoftware OPC DA/AE/HDA Client implementations.
 *
 * @defgroup DAClient Technosoftware DA Client API
 * @ingroup DaAeHdaClient
 * @brief The DAClient group bundles all code related to allow clients access to OPC DA servers.
 *
 * @defgroup AEClient Technosoftware AE Client API
 * @ingroup DaAeHdaClient
 * @brief The AEClient group bundles all code related to allow clients access to OPC AE servers.
 *
 * @defgroup HDAClient Technosoftware HDA Client API
 * @ingroup DaAeHdaClient
 * @brief The HDAClient group bundles all code related to allow clients access to OPC HDA servers.
 */


namespace Technosoftware
{
    namespace DaAeHdaClient
    {
        //----------------------------------------------------------------------------------------------------------------------
        // DEFINEs
        //----------------------------------------------------------------------------------------------------------------------
        // Error code if a server method on a disconnected server object is called.
#define OPC_E_SRVNOTCONNECTED          CO_E_OBJNOTCONNECTED
// Error code returned by some functions if the ClientSdk trial period has expired (only Linux/Solaris).
#define OPC_E_EVALUATIONEXPIRED        HRESULT_FROM_WIN32( ERROR_ACCOUNT_EXPIRED )

        /**
         * @struct  OpcVariant
         *
         * @brief   A dummy implementation.
         *          
         *          On Windows platforms pointers to OpcVariant can be typecasted to pointers to VARIANT.
         *          
         * @ingroup DaAeHdaClient
         */

        typedef struct OpcVariant {                     // Dummy implementation
        } OpcVariant;

         /**
          * @enum    OpcTextMode
          *
          * @brief    Specifies the format of text strings returned by ...AsText() functions.
          *
          * @ingroup DaAeHdaClient
          */

        enum class OpcTextMode {

            /**
             * @brief    The returned text string represents the name of the value as it was defined in
             *             accordance with the appropriate OPC Specification. E.g.
             *             AeServerStatus::ServerStateAsText( Valuename ) returns "OPCAE_STATUS_RUNNING".
             */

            Valuename,

            /**
             * @brief    All characters in the returned text string are uppercase. E.g.
             *             AeServerStatus::ServerStateAsText( Uppercase ) returns "RUNNING".
             */

            Uppercase,

            /**
             * @brief    All characters in the returned text string are lowercase. E.g.
             *             AeServerStatus::ServerStateAsText( Lowercase ) returns "running".
             */

            Lowercase,

            /**
             * @brief    The first character of the returned text string is a capital letter. E.g.
             *             AeServerStatus::ServerStateAsText( Capitalize ) returns "Running".
             */

            Capitalize
        };

        /**
         * @class    OpcAutoPtr
         *
         * @brief    A simple smart pointer implementation, used only internally.
         *
         * param    T    Generic type parameter.
         *
         * @ingroup DaAeHdaClient
         */

        template< typename T >
        class OPCCLIENTSDK_API OpcAutoPtr
        {
        public:

            /**
             * @fn  OpcAutoPtr::OpcAutoPtr() noexcept
             *
             * @brief   Default constructor.
             */

            OpcAutoPtr() noexcept : opcAutoPointer_(nullptr) {}

            /**
             * @fn  OpcAutoPtr::OpcAutoPtr(T* p) noexcept
             *
             * @brief   Constructor.
             *
             * @param [in,out]  p   If non-null, the T* to process.
             */

            OpcAutoPtr(T* p) noexcept : opcAutoPointer_(p) {}

            /**
             * @fn  OpcAutoPtr::OpcAutoPtr(OpcAutoPtr< T >& opcAutoPointer) noexcept
             *
             * @brief   Constructor.
             *
             * @param [in,out]  opcAutoPointer  The OpcAutoPtr&lt;T&gt;&amp; to process.
             */

            OpcAutoPtr(OpcAutoPtr< T >& opcAutoPointer) noexcept
            {
                T* pOld = opcAutoPointer;    // Transfer ownership
                opcAutoPointer = NULL;
                opcAutoPointer_ = pOld;
            }

            /**
             * @fn  OpcAutoPtr::~OpcAutoPtr() noexcept
             *
             * @brief   Destructor.
             */

            ~OpcAutoPtr() noexcept { try { if (opcAutoPointer_) { delete opcAutoPointer_; opcAutoPointer_ = NULL; } } catch (...) {} }

            /**
             * @fn  operator T*() const noexcept
             *
             * @brief   T* casting operator.
             *
             * @return  The result of the operation.
             */

            operator T*() const noexcept { return(opcAutoPointer_); }

            /**
             * @fn  T* OpcAutoPtr::operator->() const noexcept
             *
             * @brief   Member dereference operator.
             *
             * @return  The dereferenced object.
             */

            T* operator->() const noexcept { return(opcAutoPointer_); }

            /**
             * @fn  void OpcAutoPtr::Attach(T* pointer) noexcept
             *
             * @brief   Takes the ownership of an existing pointer.
             *
             * @param [in,out]  pointer   If non-null, the T* to process.
             */

            void Attach(T* pointer) noexcept { opcAutoPointer_ = pointer; }
        protected:
            T* opcAutoPointer_;
        };


        class OPCCLIENTSDK_API OpcObject;

        class OPCCLIENTSDK_API OpcObjectPtrArray;

        /**
         * @class   OpcObject
         *
         * @brief   The OpcObject class is the base class of most ClientSdk objects.
         *          
         *          OpcObject offers the following basic services:
         *             - class information
         *             - instance handling
         *          
         *          OpcObject instances organize themselves in object trees. When a OpcObject instance is
         *          created with another object as parent then the object will automatically added as
         *          child to the parent's object. The parent takes the ownership of the object i.e. it
         *          will automatically delete its children in its destructor.
         *          
         *          Only ClientSdk classes can create OpcObject instances.
         *
         * @ingroup  DaAeHdaClient
         */

        class OPCCLIENTSDK_API OpcObject
        {
        protected:

            /**
             * @fn  OpcObject::OpcObject(OpcObject* parent = NULL, const char* name = nullptr) noexcept(false);
             *
             * @brief   Constructor
             *
             * @param [in,out]  parent  (Optional) If non-null, the parent.
             * @param           name    (Optional) The name.
             */

            OpcObject(OpcObject* parent = nullptr, const char* name = nullptr) noexcept(false);

            /**
             * @fn  virtual OpcObject::~OpcObject() noexcept;
             *
             * @brief   Destructor
             */

            virtual ~OpcObject() noexcept;

        public:

            /**
             * @fn  const string& OpcObject::Name() const noexcept
             *
             * @brief   Returns the class name of this object.
             *          
             *          Reimplemented in DaBrowseElement.
             *
             * @return  A string&amp;
             */

            const string& Name() const noexcept { return m_sName; }

        protected:
            void DeleteAllChildren() noexcept;
        private:

            /**
             * @fn  void OpcObject::AddChild(OpcObject* child) noexcept(false);
             *
             * @brief   Adds a child.
             *
             * @exception   Technosoftware::Base::Exception Thrown when an exception error condition occurs.
             * @exception   InvalidArgumentException        Thrown when one of the arguments provided to this
             *                                              method is not valid.
             * @exception   OutOfMemoryException            Thrown when a low memory situation occurs.
             *
             * @param [in,out]  child   If non-null, the child.
             */

            void AddChild(OpcObject* child) noexcept(false);

            /**
             * @fn  void OpcObject::RemoveChild(OpcObject* child) noexcept(false);
             *
             * @brief   Removes the child described by child.
             *
             * @exception   Technosoftware::Base::Exception                 Thrown when an exception error
             *                                                              condition occurs.
             * @exception   Technosoftware::Base::InvalidArgumentException  Thrown when one of the arguments
             *                                                              provided to this method is not
             *                                                              valid.
             * @exception   Technosoftware::Base::NotFoundException         Thrown when the requested element
             *                                                              is not present.
             *
             * @param [in,out]  child   If non-null, the child.
             */

            void RemoveChild(OpcObject* child) noexcept(false);

        private:
            string                                  m_sName;
            OpcObject*                              m_pParent;
            OpcAutoPtr< OpcObjectPtrArray >         m_parChilds;
        };
    }
}
#endif // __OPCBASE_H
