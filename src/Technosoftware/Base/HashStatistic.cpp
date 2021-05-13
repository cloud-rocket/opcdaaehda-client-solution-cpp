/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the HashStatistic class.
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

#include "Base/HashStatistic.h"
#include <sstream>

namespace Technosoftware
{
    namespace Base
    {


        HashStatistic::HashStatistic(
            UInt32 tableSize,
            UInt32 numEntries,
            UInt32 numZeroEntries,
            UInt32 maxEntry,
            std::vector<UInt32> details) :
            _sizeOfTable(tableSize),
            _numberOfEntries(numEntries),
            _numZeroEntries(numZeroEntries),
            _maxEntriesPerHash(maxEntry),
            _detailedEntriesPerHash(details)
        {
        }


        HashStatistic::~HashStatistic()
        {
        }


        std::string HashStatistic::toString() const
        {
            std::ostringstream str;
            str << "HashTable of size " << _sizeOfTable << " containing " << _numberOfEntries << " entries:\n";
            str << "  NumberOfZeroEntries: " << _numZeroEntries << "\n";
            str << "  MaxEntry: " << _maxEntriesPerHash << "\n";
            str << "  AvgEntry: " << avgEntriesPerHash() << ", excl Zero slots: " << avgEntriesPerHashExclZeroEntries() << "\n";
            str << "  DetailedStatistics: \n";
            for (int i = 0; i < _detailedEntriesPerHash.size(); ++i)
            {
                // 10 entries per line
                if (i % 10 == 0)
                {
                    str << "\n  " << i << ":";
                }
                str << " " << _detailedEntriesPerHash[i];
            }
            str << "\n";
            str.flush();
            return str.str();
        }
    }
}
