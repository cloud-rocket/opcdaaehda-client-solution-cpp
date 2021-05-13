/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the SingletonHolder template.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
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

#ifndef TECHNOSOFTWARE_SINGLETONHOLDER_H
#define TECHNOSOFTWARE_SINGLETONHOLDER_H

#include "Base/Base.h"
#include "Base/Mutex.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   SingletonHolder
         *
         * @brief   This is a helper template class for managing singleton objects allocated on the heap.
         *          The class ensures proper deletion (including calling of the destructor) of singleton
         *          objects when the application that created them terminates.
         *
         * @ingroup BaseCore
         */

        template <class S>
        class SingletonHolder
        {
        public:

            /**
             * @fn  SingletonHolder::SingletonHolder()
             *
             * @brief   Creates the SingletonHolder.
             */

            SingletonHolder() :
                singleton_(0)
            {
            }

            /**
             * @fn  SingletonHolder::~SingletonHolder()
             *
             * @brief   Destroys the SingletonHolder and the singleton object that it holds.
             */

            ~SingletonHolder()
            {
                delete singleton_;
            }

            /**
             * @fn  S* SingletonHolder::Get()
             *
             * @brief   Returns a pointer to the singleton object hold by the SingletonHolder. The first call
             *          to get will create the singleton.
             *
             * @return  null if it fails, else a pointer to a S.
             */

            S* Get()
            {
                FastMutex::ScopedLock lock(_m);
                if (!singleton_) singleton_ = new S;
                return singleton_;
            }

            /**
             * @fn  void SingletonHolder::Reset()
             *
             * @brief   Deletes the singleton object.
             */

            void Reset()
            {
                FastMutex::ScopedLock lock(_m);
                delete singleton_;
                singleton_ = 0;
            }

        private:
            S* singleton_;
            FastMutex _m;
        };
    }
}

#endif /* TECHNOSOFTWARE_SINGLETONHOLDER_H */
