/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Windows1252Encoding class.
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

#include "Base/TextEncoding.h"
#include "Base/Exception.h"
#include "Base/String.h"
#include "Base/ASCIIEncoding.h"
#include "Base/Latin1Encoding.h"
#include "Base/Latin2Encoding.h"
#include "Base/Latin9Encoding.h"
#include "Base/UTF32Encoding.h"
#include "Base/UTF16Encoding.h"
#include "Base/UTF8Encoding.h"
#include "Base/Windows1250Encoding.h"
#include "Base/Windows1251Encoding.h"
#include "Base/Windows1252Encoding.h"
#include "Base/RWLock.h"
#include "Base/SingletonHolder.h"
#include <map>


namespace Technosoftware
{
    namespace Base
    {


        //
        // TextEncodingManager
        //


        class TextEncodingManager
        {
        public:
            TextEncodingManager()
            {
                TextEncoding::Ptr pUtf8Encoding(new UTF8Encoding);
                Add(pUtf8Encoding, TextEncoding::GLOBAL);

                Add(new ASCIIEncoding);
                Add(new Latin1Encoding);
                Add(new Latin2Encoding);
                Add(new Latin9Encoding);
                Add(pUtf8Encoding);
                Add(new UTF16Encoding);
                Add(new UTF32Encoding);
                Add(new Windows1250Encoding);
                Add(new Windows1251Encoding);
                Add(new Windows1252Encoding);
            }

            ~TextEncodingManager()
            {
            }

            void Add(TextEncoding::Ptr pEncoding)
            {
                Add(pEncoding, pEncoding->GetCanonicalName());
            }

            void Add(TextEncoding::Ptr pEncoding, const std::string& name)
            {
                RWLock::ScopedLock lock(_lock, true);

                _encodings[name] = pEncoding;
            }

            void Remove(const std::string& name)
            {
                RWLock::ScopedLock lock(_lock, true);

                _encodings.erase(name);
            }

            TextEncoding::Ptr Find(const std::string& name) const
            {
                RWLock::ScopedLock lock(_lock);

                EncodingMap::const_iterator it = _encodings.find(name);
                if (it != _encodings.end())
                    return it->second;

                for (it = _encodings.begin(); it != _encodings.end(); ++it)
                {
                    if (it->second->IsA(name))
                        return it->second;
                }
                return TextEncoding::Ptr();
            }

        private:
            TextEncodingManager(const TextEncodingManager&);
            TextEncodingManager& operator = (const TextEncodingManager&);

            typedef std::map<std::string, TextEncoding::Ptr, CILess> EncodingMap;

            EncodingMap    _encodings;
            mutable RWLock _lock;
        };


        //
        // TextEncoding
        //


        const std::string TextEncoding::GLOBAL;


        TextEncoding::~TextEncoding()
        {
        }


        int TextEncoding::Convert(const unsigned char* bytes) const
        {
            return static_cast<int>(*bytes);
        }


        int TextEncoding::Convert(int ch, unsigned char* bytes, int length) const
        {
            return 0;
        }


        int TextEncoding::QueryConvert(const unsigned char* bytes, int length) const
        {
            return (int)*bytes;
        }


        int TextEncoding::GetSequenceLength(const unsigned char* bytes, int length) const
        {
            return 1;
        }


        TextEncoding& TextEncoding::GetByName(const std::string& encodingName)
        {
            TextEncoding* pEncoding = GetManager().Find(encodingName);
            if (pEncoding)
                return *pEncoding;
            else
                throw NotFoundException(encodingName);
        }


        TextEncoding::Ptr TextEncoding::Find(const std::string& encodingName)
        {
            return GetManager().Find(encodingName);
        }


        void TextEncoding::Add(TextEncoding::Ptr pEncoding)
        {
            GetManager().Add(pEncoding, pEncoding->GetCanonicalName());
        }


        void TextEncoding::Add(TextEncoding::Ptr pEncoding, const std::string& name)
        {
            GetManager().Add(pEncoding, name);
        }


        void TextEncoding::Remove(const std::string& encodingName)
        {
            GetManager().Remove(encodingName);
        }


        TextEncoding::Ptr TextEncoding::SetGlobal(TextEncoding::Ptr encoding)
        {
            TextEncoding::Ptr prev = Find(GLOBAL);
            Add(encoding, GLOBAL);
            return prev;
        }


        TextEncoding& TextEncoding::GetGlobal()
        {
            return GetByName(GLOBAL);
        }


        namespace
        {
            static SingletonHolder<TextEncodingManager> sh;
        }


        TextEncodingManager& TextEncoding::GetManager()
        {
            return *sh.Get();
        }

    }
}
