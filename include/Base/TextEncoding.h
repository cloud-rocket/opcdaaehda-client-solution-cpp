/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the TextEncoding class.
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

#ifndef TECHNOSOFTWARE_TEXTENCODING_H
#define TECHNOSOFTWARE_TEXTENCODING_H

#include "Base/Base.h"
#include "Base/SharedPtr.h"

namespace Technosoftware
{
    namespace Base
    {
        class TextEncodingManager;

        /**
         * @class   TextEncoding
         *
         * @brief   An abstract base class for implementing text encodings like UTF-8 or ISO 8859-1.
         *          
         *          Subclasses must override the canonicalName(), isA(), characterMap() and convert()
         *          methods and need to be thread safe and stateless.
         *          
         *          TextEncoding also provides static member functions for managing mappings from
         *          encoding names to TextEncoding objects.
         *
         * @ingroup  BaseText
         */

        class TECHNOSOFTWARE_API TextEncoding
        {
        public:
            typedef SharedPtr<TextEncoding> Ptr;

            enum
            {
                /*
                 * @brief    The maximum character byte sequence length supported.
                 */
                MAX_SEQUENCE_LENGTH = 4
            };

            /**
             * @typedef int CharacterMap[256]
             *
             * @brief   The map[b] member gives information about byte sequences whose first byte is b. If
             *            map[b] is c where c is >= 0, then b by itself encodes the Unicode scalar value c.
             *            If map[b] is -1, then the byte sequence is malformed. If map[b] is -n, where n >= 2,
             *            then b is the first byte of an n-byte sequence that encodes a single Unicode scalar
             *            value. Byte sequences up to 4 bytes in length are supported.
             */

            typedef int CharacterMap[256];

            /**
             * @fn  virtual TextEncoding::~TextEncoding();
             *
             * @brief   Destroys the encoding.
             */

            virtual ~TextEncoding();

            /**
             * @fn  virtual const char* TextEncoding::GetCanonicalName() const = 0;
             *
             * @brief   Returns the canonical name of this encoding,
             *          e.g. "ISO-8859-1". Encoding name comparisons are case insensitive.
             *
             * @return  null if it fails, else the canonical name.
             */

            virtual const char* GetCanonicalName() const = 0;

            /**
             * @fn    virtual bool TextEncoding::IsA(const std::string& encodingName) const = 0;
             *
             * @brief    Returns true if the given name is one of the names of this encoding. For example, the
             *             "ISO-8859-1" encoding is also known as "Latin-1".
             *             
             *             Encoding name comparision are be case insensitive.
             *
             * @param    encodingName    Name of the encoding.
             *
             * @return    true if a, false if not.
             */

            virtual bool IsA(const std::string& encodingName) const = 0;

            /**
             * @fn    virtual const CharacterMap& TextEncoding::GetCharacterMap() const = 0;
             *
             * @brief    Returns the CharacterMap for the encoding. The CharacterMap should be kept in a
             *             static member. As characterMap() can be called frequently, it should be implemented
             *             in such a way that it just returns a static map. If the map is built at runtime, this
             *             should be done in the constructor.
             *
             * @return    The character map.
             */

            virtual const CharacterMap& GetCharacterMap() const = 0;

            /**
             * @fn    virtual int TextEncoding::Convert(const unsigned char* bytes) const;
             *
             * @brief    The convert function is used to convert multibyte sequences;
             *             bytes will point to a byte sequence of n bytes where sequenceLength(bytes, length) ==
             *             -n, with length >= n.
             *             
             *             The convert function must return the Unicode scalar value represented by this byte
             *             sequence or -1 if the byte sequence is malformed. The default implementation returns
             *             (int) bytes[0].
             *
             * @param    bytes    The bytes.
             *
             * @return    An int.
             */

            virtual int Convert(const unsigned char* bytes) const;

            /**
             * @fn    virtual int TextEncoding::QueryConvert(const unsigned char* bytes, int length) const;
             *
             * @brief    The queryConvert function is used to convert single byte characters or multibyte
             *             sequences;
             *             bytes will point to a byte sequence of length bytes.
             *             
             *             The queryConvert function must return the Unicode scalar value represented by this
             *             byte sequence or -1 if the byte sequence is malformed or -n where n is number of
             *             bytes requested for the sequence, if lenght is shorter than the sequence. The length
             *             of the sequence might not be determined by the first byte, in which case the
             *             conversion becomes an iterative process: First call with length == 1 might return -2,
             *             Then a second call with lenght == 2 might return -4 Eventually, the third call with
             *             length == 4 should return either a Unicode scalar value, or -1 if the byte sequence
             *             is malformed. The default implementation returns (int) bytes[0].
             *
             * @param    bytes     The bytes.
             * @param    length    The length.
             *
             * @return    The convert.
             */

            virtual    int QueryConvert(const unsigned char* bytes, int length) const;

            /**
             * @fn    virtual int TextEncoding::GetSequenceLength(const unsigned char* bytes, int length) const;
             *
             * @brief    The sequenceLength function is used to get the lenth of the sequence pointed by
             *             bytes. The length paramater should be greater or equal to the length of the sequence.
             *             
             *             The sequenceLength function must return the lenght of the sequence represented by
             *             this byte sequence or a negative value -n if length is shorter than the sequence,
             *             where n is the number of byte requested to determine the length of the sequence. The
             *             length of the sequence might not be determined by the first byte, in which case the
             *             conversion becomes an iterative process as long as the result is negative: First call
             *             with length == 1 might return -2, Then a second call with lenght == 2 might return -4
             *             Eventually, the third call with length == 4 should return 4. The default
             *             implementation returns 1.
             *
             * @param    bytes     The bytes.
             * @param    length    The length.
             *
             * @return    The sequence length.
             */

            virtual int GetSequenceLength(const unsigned char* bytes, int length) const;

            /**
             * @fn    virtual int TextEncoding::Convert(int ch, unsigned char* bytes, int length) const;
             *
             * @brief    Transform the Unicode character ch into the encoding's byte sequence. The method
             *             returns the number of bytes used. The method must not use more than length
             *             characters. Bytes and length can also be null - in this case only the number of bytes
             *             required to represent ch is returned. If the character cannot be converted, 0 is
             *             returned and the byte sequence remains unchanged. The default implementation simply
             *             returns 0.
             *
             * @param    ch                 The ch.
             * @param [in,out]    bytes    If non-null, the bytes.
             * @param    length             The length.
             *
             * @return    An int.
             */

            virtual int Convert(int ch, unsigned char* bytes, int length) const;

            /**
             * @fn    static TextEncoding& TextEncoding::GetByName(const std::string& encodingName);
             *
             * @brief    Returns the TextEncoding object for the given encoding name.
             *             
             *           Throws a NotFoundException if the encoding with given name is not available.
             *
             * @param    encodingName    Name of the encoding.
             *
             * @return    The by name.
             */

            static TextEncoding& GetByName(const std::string& encodingName);

            /**
             * @fn    static TextEncoding::Ptr TextEncoding::Find(const std::string& encodingName);
             *
             * @brief    Returns a pointer to the TextEncoding object for the given encodingName, or NULL if
             *             no such TextEncoding object exists.
             *
             * @param    encodingName    Name of the encoding.
             *
             * @return    A TextEncoding::Ptr.
             */

            static TextEncoding::Ptr Find(const std::string& encodingName);

            /**
             * @fn    static void TextEncoding::Add(TextEncoding::Ptr encoding);
             *
             * @brief    Adds the given TextEncoding to the table of text encodings, under the encoding's
             *             canonical name.
             *             
             *             If an encoding with the given name is already registered, it is replaced.
             *
             * @param    encoding    The encoding to add.
             */

            static void Add(TextEncoding::Ptr encoding);

            /**
             * @fn    static void TextEncoding::Add(TextEncoding::Ptr encoding, const std::string& name);
             *
             * @brief    Adds the given TextEncoding to the table of text encodings, under the given name.
             *             
             *             If an encoding with the given name is already registered, it is replaced.
             *
             * @param    encoding    The encoding.
             * @param    name        The name.
             */

            static void Add(TextEncoding::Ptr encoding, const std::string& name);

            /**
             * @fn    static void TextEncoding::Remove(const std::string& encodingName);
             *
             * @brief    Removes the encoding with the given name from the table of text encodings.
             *
             * @param    encodingName    The encoding name to remove.
             */

            static void Remove(const std::string& encodingName);

            /**
             * @fn    static TextEncoding::Ptr TextEncoding::SetGlobal(TextEncoding::Ptr encoding);
             *
             * @brief    Sets global TextEncoding object.
             *             
             *             This function sets the global encoding to the argument and returns a reference of the
             *             previous global encoding.
             *
             * @param    encoding    The encoding.
             *
             * @return    A TextEncoding::Ptr.
             */

            static TextEncoding::Ptr SetGlobal(TextEncoding::Ptr encoding);

            /**
             * @fn    static TextEncoding& TextEncoding::GetGlobal();
             *
             * @brief    Return the current global TextEncoding object.
             *
             * @return    The global.
             */

            static TextEncoding& GetGlobal();

            /** @brief    Name of the global TextEncoding, which is the empty string. */
            static const std::string GLOBAL;

        protected:

            /**
             * @fn    static TextEncodingManager& TextEncoding::GetManager();
             *
             * @brief    Returns the TextEncodingManager.
             *
             * @return    The manager.
             */

            static TextEncodingManager& GetManager();
        };
    }
}

#endif /* TECHNOSOFTWARE_TEXTENCODING_H */
