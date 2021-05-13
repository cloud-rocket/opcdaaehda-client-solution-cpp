/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definitions of class FPEnvironmentImpl for Tru64 and OpenVMS Alpha.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#ifndef TECHNOSOFTWARE_FPENVIRONMENT_DEC_H
#define TECHNOSOFTWARE_FPENVIRONMENT_DEC_H

#include "Base/Base.h"
#if defined(__VMS)
#include <ieeedef.h>
#else
#include <machine/fpu.h>
#endif

namespace Technosoftware
{
    namespace Base
    {
        class FPEnvironmentImpl
        {
        protected:
            enum RoundingModeImpl
            {
                FP_ROUND_DOWNWARD_IMPL = 0,
                FP_ROUND_UPWARD_IMPL = 0,
                FP_ROUND_TONEAREST_IMPL = 0,
                FP_ROUND_TOWARDZERO_IMPL = 0
            };
            enum FlagImpl
            {
#if defined(__VMS)
                FP_DIVIDE_BY_ZERO_IMPL = IEEE$M_STATUS_DZE,
                FP_INEXACT_IMPL = IEEE$M_STATUS_INE,
                FP_OVERFLOW_IMPL = IEEE$M_STATUS_OVF,
                FP_UNDERFLOW_IMPL = IEEE$M_STATUS_UNF,
                FP_INVALID_IMPL = IEEE$M_STATUS_INV
#else
                FP_DIVIDE_BY_ZERO_IMPL = IEEE_STATUS_DZE,
                FP_INEXACT_IMPL = IEEE_STATUS_INE,
                FP_OVERFLOW_IMPL = IEEE_STATUS_OVF,
                FP_UNDERFLOW_IMPL = IEEE_STATUS_UNF,
                FP_INVALID_IMPL = IEEE_STATUS_INV
#endif
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
#if defined(__VMS)
            struct _ieee _env;
#else
            unsigned long _env;
#endif
        };
    }
}

#endif /* TECHNOSOFTWARE_FPENVIRONMENT_DEC_H */
