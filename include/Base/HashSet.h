/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the HashSet class.
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


#ifndef TECHNOSOFTWARE_HASHSET_H
#define TECHNOSOFTWARE_HASHSET_H


#include "Base/Base.h"
#include "Base/LinearHashTable.h"


namespace Technosoftware
{
    namespace Base
    {


        template <class Value, class HashFunc = Hash<Value> >
        class HashSet
            /// This class implements a set using a LinearHashTable.
            ///
            /// A HashSet can be used just like a std::set.
        {
        public:
            typedef Value        ValueType;
            typedef Value&       Reference;
            typedef const Value& ConstReference;
            typedef Value*       Pointer;
            typedef const Value* ConstPointer;
            typedef HashFunc     Hash;

            typedef LinearHashTable<ValueType, Hash> HashTable;

            typedef typename HashTable::Iterator      Iterator;
            typedef typename HashTable::ConstIterator ConstIterator;

            HashSet()
                /// Creates an empty HashSet.
            {
            }

            HashSet(std::size_t initialReserve) :
                _table(initialReserve)
                /// Creates the HashSet, using the given initialReserve.
            {
            }

            HashSet(const HashSet& set) :
                _table(set._table)
                /// Creates the HashSet by copying another one.
            {
            }

            ~HashSet()
                /// Destroys the HashSet.
            {
            }

            HashSet& operator = (const HashSet& table)
                /// Assigns another HashSet.
            {
                HashSet tmp(table);
                swap(tmp);
                return *this;
            }

            void swap(HashSet& set)
                /// Swaps the HashSet with another one.
            {
                _table.swap(set._table);
            }

            ConstIterator begin() const
                /// Returns an iterator pointing to the first entry, if one exists.
            {
                return _table.begin();
            }

            ConstIterator end() const
                /// Returns an iterator pointing to the end of the table.
            {
                return _table.end();
            }

            Iterator begin()
                /// Returns an iterator pointing to the first entry, if one exists.
            {
                return _table.begin();
            }

            Iterator end()
                /// Returns an iterator pointing to the end of the table.
            {
                return _table.end();
            }

            ConstIterator find(const ValueType& value) const
                /// Finds an entry in the table.
            {
                return _table.find(value);
            }

            Iterator find(const ValueType& value)
                /// Finds an entry in the table.
            {
                return _table.find(value);
            }

            std::size_t count(const ValueType& value) const
                /// Returns the number of elements with the given
                /// value, with is either 1 or 0.
            {
                return _table.count(value);
            }

            std::pair<Iterator, bool> insert(const ValueType& value)
                /// Inserts an element into the set.
                ///
                /// If the element already exists in the set,
                /// a pair(iterator, false) with iterator pointing to the 
                /// existing element is returned.
                /// Otherwise, the element is inserted an a 
                /// pair(iterator, true) with iterator
                /// pointing to the new element is returned.
            {
                return _table.insert(value);
            }

            void erase(Iterator it)
                /// Erases the element pointed to by it.
            {
                _table.erase(it);
            }

            void erase(const ValueType& value)
                /// Erases the element with the given value, if it exists.
            {
                _table.erase(value);
            }

            void clear()
                /// Erases all elements.
            {
                _table.clear();
            }

            std::size_t size() const
                /// Returns the number of elements in the table.
            {
                return _table.size();
            }

            bool empty() const
                /// Returns true iff the table is empty.
            {
                return _table.empty();
            }

        private:
            HashTable _table;
        };
    }
}

#endif /* TECHNOSOFTWARE_HASHSET_H */
