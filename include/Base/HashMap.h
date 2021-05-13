/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the HashMap class.
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


#ifndef TECHNOSOFTWARE_HASHMAP_H
#define TECHNOSOFTWARE_HASHMAP_H


#include "Base/Base.h"
#include "Base/LinearHashTable.h"
#include "Base/Exception.h"
#include <utility>


namespace Technosoftware
{
    namespace Base
    {


        template <class Key, class Value>
        struct HashMapEntry
            /// This class template is used internally by HashMap.
        {
            Key   first;
            Value second;

            HashMapEntry() :
                first(),
                second()
            {
            }

            HashMapEntry(const Key& key) :
                first(key),
                second()
            {
            }

            HashMapEntry(const Key& key, const Value& value) :
                first(key),
                second(value)
            {
            }

            bool operator == (const HashMapEntry& entry) const
            {
                return first == entry.first;
            }

            bool operator != (const HashMapEntry& entry) const
            {
                return first != entry.first;
            }
        };


        template <class HME, class KeyHashFunc>
        struct HashMapEntryHash
            /// This class template is used internally by HashMap.
        {
            std::size_t operator () (const HME& entry) const
            {
                return _func(entry.first);
            }

        private:
            KeyHashFunc _func;
        };


        template <class Key, class Mapped, class HashFunc = Hash<Key> >
        class HashMap
            /// This class implements a map using a LinearHashTable.
            ///
            /// A HashMap can be used just like a std::map.
        {
        public:
            typedef Key                 KeyType;
            typedef Mapped              MappedType;
            typedef Mapped&             Reference;
            typedef const Mapped&       ConstReference;
            typedef Mapped*             Pointer;
            typedef const Mapped*       ConstPointer;

            typedef HashMapEntry<Key, Mapped>      ValueType;
            typedef std::pair<KeyType, MappedType> PairType;

            typedef HashMapEntryHash<ValueType, HashFunc> HashType;
            typedef LinearHashTable<ValueType, HashType>  HashTable;

            typedef typename HashTable::Iterator      Iterator;
            typedef typename HashTable::ConstIterator ConstIterator;

            HashMap()
                /// Creates an empty HashMap.
            {
            }

            HashMap(std::size_t initialReserve) :
                _table(initialReserve)
                /// Creates the HashMap with room for initialReserve entries.
            {
            }

            HashMap& operator = (const HashMap& map)
                /// Assigns another HashMap.
            {
                HashMap tmp(map);
                swap(tmp);
                return *this;
            }

            void swap(HashMap& map)
                /// Swaps the HashMap with another one.
            {
                _table.swap(map._table);
            }

            ConstIterator begin() const
            {
                return _table.begin();
            }

            ConstIterator end() const
            {
                return _table.end();
            }

            Iterator begin()
            {
                return _table.begin();
            }

            Iterator end()
            {
                return _table.end();
            }

            ConstIterator find(const KeyType& key) const
            {
                ValueType value(key);
                return _table.find(value);
            }

            Iterator find(const KeyType& key)
            {
                ValueType value(key);
                return _table.find(value);
            }

            std::size_t count(const KeyType& key) const
            {
                ValueType value(key);
                return _table.find(value) != _table.end() ? 1 : 0;
            }

            std::pair<Iterator, bool> insert(const PairType& pair)
            {
                ValueType value(pair.first, pair.second);
                return _table.insert(value);
            }

            std::pair<Iterator, bool> insert(const ValueType& value)
            {
                return _table.insert(value);
            }

            void erase(Iterator it)
            {
                _table.erase(it);
            }

            void erase(const KeyType& key)
            {
                Iterator it = find(key);
                _table.erase(it);
            }

            void clear()
            {
                _table.clear();
            }

            std::size_t size() const
            {
                return _table.size();
            }

            bool empty() const
            {
                return _table.empty();
            }

            ConstReference operator [] (const KeyType& key) const
            {
                ConstIterator it = _table.find(key);
                if (it != _table.end())
                    return it->second;
                else
                    throw NotFoundException();
            }

            Reference operator [] (const KeyType& key)
            {
                ValueType value(key);
                std::pair<Iterator, bool> res = _table.insert(value);
                return res.first->second;
            }

        private:
            HashTable _table;
        };
    }
}

#endif /* TECHNOSOFTWARE_HASHMAP_H */
