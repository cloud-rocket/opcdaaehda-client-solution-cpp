/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definition of class FPEnvironmentImpl for platforms that do not
 * support IEEE 754 extensions.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#ifndef TECHNOSOFTWARE_FPENVIRONMENT_DUMMY_H
#define TECHNOSOFTWARE_FPENVIRONMENT_DUMMY_H

#include "Base/Base.h"
#include <cmath>

namespace Technosoftware
{
    namespace Base
    {
        class TECHNOSOFTWARE_API FPEnvironmentImpl
        {
        protected:
            enum RoundingModeImpl
            {
                FP_ROUND_DOWNWARD_IMPL,
                FP_ROUND_UPWARD_IMPL,
                FP_ROUND_TONEAREST_IMPL,
                FP_ROUND_TOWARDZERO_IMPL
            };
            enum FlagImpl
            {
                FP_DIVIDE_BY_ZERO_IMPL,
                FP_INEXACT_IMPL,
                FP_OVERFLOW_IMPL,
                FP_UNDERFLOW_IMPL,
                FP_INVALID_IMPL
            };
            FPEnvironmentImpl();
            FPEnvironmentImpl(const FPEnvironmentImpl& env);
            ~FPEnvironmentImpl();
            FPEnvironmentImpl& operator = (const FPEnvironmentImpl& env);
            void KeepCurrentImpl();
            static void ClearFlagsImpl();
            static bool IsFlagImpl(FlagImpl flag);
            static void SetRoundingModeImpl(RoundingModeImpl mode);
            static RoundingModeImpl GetRoundingModeImpl();
            static bool IsInfiniteImpl(float value);
            static bool IsInfiniteImpl(double value);
            static bool IsInfiniteImpl(long double value);
            static bool IsNaNImpl(float value);
            static bool IsNaNImpl(double value);
            static bool IsNaNImpl(long double value);
            static float CopySignImpl(float target, float source);
            static double CopySignImpl(double target, double source);
            static long double CopySignImpl(long double target, long double source);

        private:
            static RoundingModeImpl _roundingMode;
        };


        //
        // inlines
        //
        inline bool FPEnvironmentImpl::IsInfiniteImpl(float value)
        {
            return std::isinf(value) != 0;
        }


        inline bool FPEnvironmentImpl::IsInfiniteImpl(double value)
        {
            return std::isinf(value) != 0;
        }


        inline bool FPEnvironmentImpl::IsInfiniteImpl(long double value)
        {
            return std::isinf((double)value) != 0;
        }


        inline bool FPEnvironmentImpl::IsNaNImpl(float value)
        {
            return std::isnan(value) != 0;
        }


        inline bool FPEnvironmentImpl::IsNaNImpl(double value)
        {
            return std::isnan(value) != 0;
        }


        inline bool FPEnvironmentImpl::IsNaNImpl(long double value)
        {
            return std::isnan((double)value) != 0;
        }


        inline float FPEnvironmentImpl::CopySignImpl(float target, float source)
        {
            return copysignf(target, source);
        }


        inline double FPEnvironmentImpl::CopySignImpl(double target, double source)
        {
            return copysign(target, source);
        }
    }
}

#endif /* TECHNOSOFTWARE_FPENVIRONMENT_DUMMY_H */
