/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definitions of class FPEnvironment.
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

#ifndef TECHNOSOFTWARE_FPENVIRONMENT_H
#define TECHNOSOFTWARE_FPENVIRONMENT_H

#include "Base/Base.h"

#if defined(TECHNOSOFTWARE_NO_FPENVIRONMENT)
#include "Base/FPEnvironment_DUMMY.h"
#elif defined(__osf__) || defined(__VMS)
#include "Base/FPEnvironment_DEC.h"
#elif defined(sun) || defined(__sun)
#include "Base/FPEnvironment_SUN.h"
#elif defined(TECHNOSOFTWARE_OS_FAMILY_UNIX)
#include "Base/FPEnvironment_C99.h"
#elif defined(TECHNOSOFTWARE_OS_FAMILY_WINDOWS)
#include "Base/FPEnvironment_WIN32.h"
#else
#include "Base/FPEnvironment_DUMMY.h"
#endif

namespace Technosoftware
{
    namespace Base
    {
        /**
         * @class   FPEnvironment
         *
         * @brief   Instances of this class can be used to save and later restore the current floating
         *          point environment (consisting of rounding mode and floating-point flags). The class
         *          also provides various static methods to query certain properties of a floating-point
         *          number.
         *
         * @ingroup BaseCore
         */

        class TECHNOSOFTWARE_API FPEnvironment : private FPEnvironmentImpl
        {
        public:
            enum RoundingMode
            {
                FP_ROUND_DOWNWARD = FP_ROUND_DOWNWARD_IMPL,
                FP_ROUND_UPWARD = FP_ROUND_UPWARD_IMPL,
                FP_ROUND_TONEAREST = FP_ROUND_TONEAREST_IMPL,
                FP_ROUND_TOWARDZERO = FP_ROUND_TOWARDZERO_IMPL
            };

            enum Flag
            {
                FP_DIVIDE_BY_ZERO = FP_DIVIDE_BY_ZERO_IMPL,
                FP_INEXACT = FP_INEXACT_IMPL,
                FP_OVERFLOW = FP_OVERFLOW_IMPL,
                FP_UNDERFLOW = FP_UNDERFLOW_IMPL,
                FP_INVALID = FP_INVALID_IMPL
            };

            /**
             * @fn  FPEnvironment::FPEnvironment();
             *
             * @brief   Standard constructor. Remembers the current environment.
             */

            FPEnvironment();

            /**
             * @fn  FPEnvironment::FPEnvironment(RoundingMode mode);
             *
             * @brief   Remembers the current environment and sets the given rounding mode.
             *
             * @param   mode    The mode.
             */

            FPEnvironment(RoundingMode mode);

            /**
             * @fn  FPEnvironment::FPEnvironment(const FPEnvironment& env);
             *
             * @brief   Copy constructor.
             *
             * @param   env The environment.
             */

            FPEnvironment(const FPEnvironment& env);

            /**
             * @fn  FPEnvironment::~FPEnvironment();
             *
             * @brief   Restores the previous environment (unless keepCurrent() has been called previously)
             */

            ~FPEnvironment();

            /**
             * @fn  FPEnvironment& FPEnvironment::operator= (const FPEnvironment& env);
             *
             * @brief   Assignment operator.
             *
             * @param   env The environment.
             *
             * @return  A shallow copy of this object.
             */

            FPEnvironment& operator = (const FPEnvironment& env);

            /**
             * @fn  void FPEnvironment::KeepCurrent();
             *
             * @brief   Keep the current environment even after destroying the FPEnvironment object.
             */

            void KeepCurrent();

            /**
             * @fn  static void FPEnvironment::ClearFlags();
             *
             * @brief   Resets all flags.
             */

            static void ClearFlags();

            /**
             * @fn  static bool FPEnvironment::IsFlag(Flag flag);
             *
             * @brief   Returns true iff the given flag is set.
             *
             * @param   flag    The flag.
             *
             * @return  true if flag, false if not.
             */

            static bool IsFlag(Flag flag);

            /**
             * @fn  static void FPEnvironment::SetRoundingMode(RoundingMode mode);
             *
             * @brief   Sets the rounding mode.
             *
             * @param   mode    The mode.
             */

            static void SetRoundingMode(RoundingMode mode);

            /**
             * @fn  static RoundingMode FPEnvironment::GetRoundingMode();
             *
             * @brief   Returns the current rounding mode.
             *
             * @return  The rounding mode.
             */

            static RoundingMode GetRoundingMode();

            /**
             * @fn  static bool FPEnvironment::IsInfinite(float value);
             *
             * @brief   Returns true iff the given number is infinite.
             *
             * @param   value   The value.
             *
             * @return  true if infinite, false if not.
             */

            static bool IsInfinite(float value);

            /**
             * @fn  static bool FPEnvironment::IsInfinite(double value);
             *
             * @brief   Returns true iff the given number is infinite.
             *
             * @param   value   The value.
             *
             * @return  true if infinite, false if not.
             */

            static bool IsInfinite(double value);

            /**
             * @fn  static bool FPEnvironment::IsInfinite(long double value);
             *
             * @brief   Returns true iff the given number is infinite.
             *
             * @param   value   The value.
             *
             * @return  true if infinite, false if not.
             */

            static bool IsInfinite(long double value);

            /**
             * @fn  static bool FPEnvironment::IsNaN(float value);
             *
             * @brief   Returns true iff the given number is NaN.
             *
             * @param   value   The value.
             *
             * @return  true if nan, false if not.
             */

            static bool IsNaN(float value);

            /**
             * @fn  static bool FPEnvironment::IsNaN(double value);
             *
             * @brief   Returns true iff the given number is NaN.
             *
             * @param   value   The value.
             *
             * @return  true if nan, false if not.
             */

            static bool IsNaN(double value);

            /**
             * @fn  static bool FPEnvironment::IsNaN(long double value);
             *
             * @brief   Returns true iff the given number is NaN.
             *
             * @param   value   The value.
             *
             * @return  true if nan, false if not.
             */

            static bool IsNaN(long double value);

            /**
             * @fn  static float FPEnvironment::CopySign(float target, float source);
             *
             * @brief   Copies the sign from source to target.
             *
             * @param   target  Target for the.
             * @param   source  Another instance to copy.
             *
             * @return  A float.
             */

            static float CopySign(float target, float source);

            /**
             * @fn  static double FPEnvironment::CopySign(double target, double source);
             *
             * @brief   Copies the sign from source to target.
             *
             * @param   target  Target for the.
             * @param   source  Another instance to copy.
             *
             * @return  A double.
             */

            static double CopySign(double target, double source);

            /**
             * @fn  static long double FPEnvironment::CopySign(long double target, long double source);
             *
             * @brief   Copies the sign from source to target.
             *
             * @param   target  Target for the.
             * @param   source  Another instance to copy.
             *
             * @return  A double.
             */

            static long double CopySign(long double target, long double source);
        };

        /**
         * @typedef FPEnvironment FPE
         *
         * @brief   For convenience, we provide a shorter name for the FPEnvironment class.
         *
         * @ingroup BaseCore
         */

        typedef FPEnvironment FPE;


        //
        // inline's
        //
        inline bool FPEnvironment::IsFlag(Flag flag)
        {
            return IsFlagImpl(FlagImpl(flag));
        }


        inline void FPEnvironment::SetRoundingMode(RoundingMode mode)
        {
            SetRoundingModeImpl(RoundingModeImpl(mode));
        }


        inline FPEnvironment::RoundingMode FPEnvironment::GetRoundingMode()
        {
            return RoundingMode(GetRoundingModeImpl());
        }


        inline bool FPEnvironment::IsInfinite(float value)
        {
            return IsInfiniteImpl(value);
        }


        inline bool FPEnvironment::IsInfinite(double value)
        {
            return IsInfiniteImpl(value);
        }


        inline bool FPEnvironment::IsInfinite(long double value)
        {
            return IsInfiniteImpl(value);
        }


        inline bool FPEnvironment::IsNaN(float value)
        {
            return IsNaNImpl(value);
        }


        inline bool FPEnvironment::IsNaN(double value)
        {
            return IsNaNImpl(value);
        }


        inline bool FPEnvironment::IsNaN(long double value)
        {
            return IsNaNImpl(value);
        }


        inline float FPEnvironment::CopySign(float target, float source)
        {
            return CopySignImpl(target, source);
        }


        inline double FPEnvironment::CopySign(double target, double source)
        {
            return CopySignImpl(target, source);
        }


        inline long double FPEnvironment::CopySign(long double target, long double source)
        {
            return CopySignImpl(target, source);
        }
    }
}

#endif /* TECHNOSOFTWARE_FPENVIRONMENT_H */
