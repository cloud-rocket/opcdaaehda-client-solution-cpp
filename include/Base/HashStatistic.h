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


#ifndef TECHNOSOFTWARE_HASHSTATISTIC_H
#define TECHNOSOFTWARE_HASHSTATISTIC_H


#include "Base/Base.h"
#include <vector>


namespace Technosoftware
{
    namespace Base
    {


        //@ deprecated
        class TECHNOSOFTWARE_API HashStatistic
            /// HashStatistic class bundles statistical information on the current state of a HashTable
        {
        public:
            HashStatistic(
                UInt32 tableSize,
                UInt32 numEntries,
                UInt32 numZeroEntries,
                UInt32 maxEntry,
                std::vector<UInt32> details = std::vector<UInt32>());
            /// Creates the HashStatistic.

            virtual ~HashStatistic();
            /// Destroys the HashStatistic.

            UInt32 maxPositionsOfTable() const;
            /// Returns the maximum number of different hash values possible for the table

            UInt32 numberOfEntries() const;
            /// Returns the total number of entries currently stored in the HashTable

            UInt32 numberOfZeroPositions() const;
            /// Returns the number of hash positions that contain no entry.

            double avgEntriesPerHash() const;
            /// Returns the average number of entries per position in the Hashtable, the higher this value the less efficient
            /// performs hashing. If a large value is returned and getNumberOfZeroPositions also returns a large value, this
            /// indicates an inefficient hashing function. If the number of zero entries is low, resizing the HashTable, should
            /// be enough to improve performance

            double avgEntriesPerHashExclZeroEntries() const;
            /// Same as getAvgEntriesPerHash but hash values that contain no entry are ignored,
            /// getAvgEntriesPerHashExclZeroEntries >= getAvgEntriesPerHash will always be true.

            UInt32 maxEntriesPerHash() const;
            /// Returns the maximum number of entries per hash value found in the current table.

            const std::vector<UInt32> detailedEntriesPerHash() const;
            /// Will either be an empty vector or will contain for each possible hash value, the number of entries currently stored

            std::string toString() const;
            /// Converts the whole data structure into a string.

        private:
            UInt32 _sizeOfTable;
            UInt32 _numberOfEntries;
            UInt32 _numZeroEntries;
            UInt32 _maxEntriesPerHash;
            std::vector<UInt32> _detailedEntriesPerHash;
        };


        inline UInt32 HashStatistic::maxPositionsOfTable() const
        {
            return _sizeOfTable;
        }


        inline UInt32 HashStatistic::numberOfEntries() const
        {
            return _numberOfEntries;
        }


        inline UInt32 HashStatistic::numberOfZeroPositions() const
        {
            return _numZeroEntries;
        }


        inline double HashStatistic::avgEntriesPerHash() const
        {
            return ((double)numberOfEntries()) / maxPositionsOfTable();
        }


        inline double HashStatistic::avgEntriesPerHashExclZeroEntries() const
        {
            return ((double)numberOfEntries()) / (maxPositionsOfTable() - numberOfZeroPositions());
        }


        inline UInt32 HashStatistic::maxEntriesPerHash() const
        {
            return _maxEntriesPerHash;
        }


        inline const std::vector<UInt32> HashStatistic::detailedEntriesPerHash() const
        {
            return _detailedEntriesPerHash;
        }
    }
}

#endif /* TECHNOSOFTWARE_HASHSTATISTIC_H */
