/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of the Alignment class.
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

 // Adapted for Technosoftware from LLVM Compiler Infrastructure code:
 //
 //                     The LLVM Compiler Infrastructure
 //
 // This file is distributed under the University of Illinois Open Source License
 //
 //===----------------------------------------------------------------------===//
 //
 // This file defines the AlignOf function that computes alignments for
 // arbitrary types.
 //
 //===----------------------------------------------------------------------===//


#ifndef TECHNOSOFTWARE_ALIGNMENT_H
#define TECHNOSOFTWARE_ALIGNMENT_H


#include <cstddef>


#ifdef TECHNOSOFTWARE_ENABLE_CPP11


#include <type_traits>
#define TECHNOSOFTWARE_HAVE_ALIGNMENT


#else


namespace Technosoftware
{
    namespace Base
    {


        template <typename T>
        struct AlignmentCalcImpl
        {
            char x;
            T t;
        private:
            AlignmentCalcImpl() {} // Never instantiate.
        };

        /**
         * @struct  AlignOf
         *
         * @brief   A templated class that contains an enum value representing the alignment of the
         *          template argument.  For example, AlignOf<int>::Alignment represents the
         *          alignment of type "int".  The alignment calculated is the minimum alignment, and not
         *          necessarily the "desired" alignment returned by GCC's __alignof__ (for example).
         *          Note that because the alignment is an enum value, it can be used as a compile-time
         *          constant (e.g., for template instantiation).
         *
         * @ingroup BaseCore
         */

        template <typename T>
        struct AlignOf
        {
            enum
            {
                Alignment = static_cast<unsigned int>(sizeof(AlignmentCalcImpl<T>) - sizeof(T))
            };

            enum { Alignment_GreaterEqual_2Bytes = Alignment >= 2 ? 1 : 0 };
            enum { Alignment_GreaterEqual_4Bytes = Alignment >= 4 ? 1 : 0 };
            enum { Alignment_GreaterEqual_8Bytes = Alignment >= 8 ? 1 : 0 };
            enum { Alignment_GreaterEqual_16Bytes = Alignment >= 16 ? 1 : 0 };

            enum { Alignment_LessEqual_2Bytes = Alignment <= 2 ? 1 : 0 };
            enum { Alignment_LessEqual_4Bytes = Alignment <= 4 ? 1 : 0 };
            enum { Alignment_LessEqual_8Bytes = Alignment <= 8 ? 1 : 0 };
            enum { Alignment_LessEqual_16Bytes = Alignment <= 16 ? 1 : 0 };

        };


        /**
         * @fn  inline unsigned AlignOf()
         *
         * @brief   A templated function that returns the minimum alignment of of a type.  This provides
         *          no extra functionality beyond the AlignOf class besides some cosmetic cleanliness.
         *          Example usage: AlignOf<int>() returns the alignment of an int.
         *
         * @return  An unsigned.
         *
         * @ingroup BaseCore
         */

        template <typename T>
        inline unsigned AlignOf()
        {
            return AlignOf<T>::Alignment;
        }

        /**
         * @struct  AlignedCharArrayImpl
         *
         * @brief   Helper for building an aligned character array type.
         *          
         *          This template is used to explicitly build up a collection of aligned character types.
         *          We have to build these up using a macro and explicit specialization to cope with old
         *          versions of MSVC and GCC where only an integer literal can be used to specify an
         *          alignment constraint. Once built up here, we can then begin to indirect between these
         *          using normal C++ template parameters.
         *
         * @tparam  Alignment   Type of the alignment.
         *
         * @ingroup BaseCore
         */

        template <std::size_t Alignment> struct AlignedCharArrayImpl;


    // MSVC requires special handling here.
#ifndef _MSC_VER

#ifdef TECHNOSOFTWARE_COMPILER_CLANG

#if __has_feature(cxx_alignas)
#define TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(x) \
                    template <> struct AlignedCharArrayImpl<x> \
                    { \
                        char aligned alignas(x); \
                    }
#define TECHNOSOFTWARE_HAVE_ALIGNMENT
#endif

#elif defined(__GNUC__) || defined(__IBM_ATTRIBUTES)

#define TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(x) \
                template <> struct AlignedCharArrayImpl<x> \
                { \
                    char aligned __attribute__((aligned(x))); \
                }
#define TECHNOSOFTWARE_HAVE_ALIGNMENT

#endif

#ifdef TECHNOSOFTWARE_HAVE_ALIGNMENT
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(1);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(2);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(4);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(8);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(16);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(32);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(64);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(128);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(512);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(1024);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(2048);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(4096);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(8192);

#undef TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT
#endif // TECHNOSOFTWARE_HAVE_ALIGNMENT

#else // _MSC_VER

    // We provide special variations of this template for the most common
    // alignments because __declspec(align(...)) doesn't actually work when it is
    // a member of a by-value function argument in MSVC, even if the alignment
    // request is something reasonably like 8-byte or 16-byte.
        template <> struct AlignedCharArrayImpl<1> { char aligned; };
        template <> struct AlignedCharArrayImpl<2> { short aligned; };
        template <> struct AlignedCharArrayImpl<4> { int aligned; };
        template <> struct AlignedCharArrayImpl<8> { double aligned; };

#define TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(x) \
            template <> struct AlignedCharArrayImpl<x> { \
                __declspec(align(x)) char aligned; \
            }

        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(16);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(32);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(64);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(128);

#if (_MSC_VER > 1600)  // MSVC 2010 complains on alignment  larger than 128
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(512);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(1024);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(2048);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(4096);
        TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(8192);
#endif  // _MSC_VER > 1600

        // Any larger and MSVC complains.
#undef TECHNOSOFTWARE_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT

#define TECHNOSOFTWARE_HAVE_ALIGNMENT
#endif // _MSC_VER

// TECHNOSOFTWARE_HAVE_ALIGNMENT will be defined on the pre-C++11 platforms/compilers where
// it can be reliably determined and used. Uncomment the line below to explicitly
// disable use of alignment even for those platforms. 
// #undef TECHNOSOFTWARE_HAVE_ALIGNMENT


#ifdef TECHNOSOFTWARE_HAVE_ALIGNMENT

        template <typename T1, typename T2 = char, typename T3 = char, typename T4 = char>
        union AlignedCharArrayUnion
            /// This union template exposes a suitably aligned and sized character
            /// array member which can hold elements of any of up to four types.
            ///
            /// These types may be arrays, structs, or any other types. The goal is to
            /// produce a union type containing a character array which, when used, forms
            /// storage suitable to placement new any of these types over. Support for more
            /// than four types can be added at the cost of more boiler plate.
        {
        private:
            class AlignerImpl
            {
                T1 t1;
                T2 t2;
                T3 t3;
                T4 t4;

                AlignerImpl(); // Never defined or instantiated.
            };

            union SizerImpl
            {
                char arr1[sizeof(T1)];
                char arr2[sizeof(T2)];
                char arr3[sizeof(T3)];
                char arr4[sizeof(T4)];
            };

        public:
            char buffer[sizeof(SizerImpl)];
            /// The character array buffer for use by clients.
            ///
            /// No other member of this union should be referenced. They exist purely to
            /// constrain the layout of this character array.

        private:
            Technosoftware::Base::AlignedCharArrayImpl<AlignOf<AlignerImpl>::Alignment> _nonceMember;

        };

#endif // TECHNOSOFTWARE_HAVE_ALIGNMENT
    }
}


#endif // TECHNOSOFTWARE_ENABLE_CPP11


#endif /* TECHNOSOFTWARE_ALIGNMENT_H */
