/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definitions of class FPEnvironmentImpl for WIN32.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#ifndef TECHNOSOFTWARE_FPENVIRONMENT_WIN32_H
#define TECHNOSOFTWARE_FPENVIRONMENT_WIN32_H

#include "Base/Base.h"
#include <float.h>
#include <math.h>

#ifndef _SW_INEXACT
#    define _SW_INEXACT 0x00000001 // inexact (precision)
#endif
#ifndef _SW_UNDERFLOW
#    define _SW_UNDERFLOW 0x00000002 // underflow
#endif
#ifndef _SW_OVERFLOW
#    define _SW_OVERFLOW 0x00000004 // overflow
#endif
#ifndef _SW_ZERODIVIDE
#    define _SW_ZERODIVIDE 0x00000008 // zero divide
#endif
#ifndef _SW_INVALID
#    define _SW_INVALID 0x00000010 // invalid
#endif
#ifndef _SW_DENORMAL
#    define _SW_DENORMAL 0x00080000 // denormal status bit
#endif


namespace Technosoftware
{
    namespace Base
    {
        class TECHNOSOFTWARE_API FPEnvironmentImpl
        {
        protected:
            enum RoundingModeImpl
            {
                FP_ROUND_DOWNWARD_IMPL = _RC_DOWN,
                FP_ROUND_UPWARD_IMPL = _RC_UP,
                FP_ROUND_TONEAREST_IMPL = _RC_NEAR,
                FP_ROUND_TOWARDZERO_IMPL = _RC_CHOP
            };
            enum FlagImpl
            {
                FP_DIVIDE_BY_ZERO_IMPL = _SW_ZERODIVIDE,
                FP_INEXACT_IMPL = _SW_INEXACT,
                FP_OVERFLOW_IMPL = _SW_OVERFLOW,
                FP_UNDERFLOW_IMPL = _SW_UNDERFLOW,
                FP_INVALID_IMPL = _SW_INVALID
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
            unsigned _env;
        };


        //
        // inlines
        //
        inline bool FPEnvironmentImpl::IsInfiniteImpl(float value)
        {
            return _finite(value) == 0;
        }


        inline bool FPEnvironmentImpl::IsInfiniteImpl(double value)
        {
            return _finite(value) == 0;
        }


        inline bool FPEnvironmentImpl::IsInfiniteImpl(long double value)
        {
            return _finite(value) == 0;
        }


        inline bool FPEnvironmentImpl::IsNaNImpl(float value)
        {
            return _isnan(value) != 0;
        }


        inline bool FPEnvironmentImpl::IsNaNImpl(double value)
        {
            return _isnan(value) != 0;
        }


        inline bool FPEnvironmentImpl::IsNaNImpl(long double value)
        {
            return _isnan(value) != 0;
        }


        inline float FPEnvironmentImpl::CopySignImpl(float target, float source)
        {
            return float(_copysign(target, source));
        }


        inline double FPEnvironmentImpl::CopySignImpl(double target, double source)
        {
            return _copysign(target, source);
        }


        inline long double FPEnvironmentImpl::CopySignImpl(long double target, long double source)
        {
            return (source > 0 && target > 0) || (source < 0 && target < 0) ? target : -target;
        }
    }
}

#endif /* TECHNOSOFTWARE_FPENVIRONMENT_WIN32_H */
