/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the ScopedUnlock template class.
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

#ifndef TECHNOSOFTWARE_SCOPEDUNLOCK_H
#define TECHNOSOFTWARE_SCOPEDUNLOCK_H

#include "Base/Base.h"

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class    ScopedUnlock
         *
         * @brief    A class that simplifies thread synchronization with a mutex. The constructor accepts
         *             a Mutex and unlocks it. The destructor locks the mutex.
         *
         * @ingroup BaseThreading
         */

        template <class M>
        class ScopedUnlock
        {
        public:
            inline ScopedUnlock(M& mutex, bool unlockNow = true) : mutex_(mutex)
            {
                if (unlockNow)
                    mutex_.unlock();
            }
            inline ~ScopedUnlock()
            {
                try
                {
                    mutex_.lock();
                }
                catch (...)
                {
                    technosoftware_unexpected();
                }
            }

        private:
            M& mutex_;

            ScopedUnlock();
            ScopedUnlock(const ScopedUnlock&);
            ScopedUnlock& operator = (const ScopedUnlock&);
        };
    }
}


#endif /* TECHNOSOFTWARE_SCOPEDUNLOCK_H */
