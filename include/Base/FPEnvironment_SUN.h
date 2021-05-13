/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definitions of class FPEnvironmentImpl for Solaris.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */

#ifndef TECHNOSOFTWARE_FPENVIRONMENT_SUN_H
#define TECHNOSOFTWARE_FPENVIRONMENT_SUN_H

#include "Base/Base.h"
#include <ieeefp.h>

namespace Technosoftware
{
    namespace Base
    {
        class FPEnvironmentImpl
        {
        protected:
            enum RoundingModeImpl
            {
                FP_ROUND_DOWNWARD_IMPL = FP_RM,
                FP_ROUND_UPWARD_IMPL = FP_RP,
                FP_ROUND_TONEAREST_IMPL = FP_RN,
                FP_ROUND_TOWARDZERO_IMPL = FP_RZ
            };
            enum FlagImpl
            {
                FP_DIVIDE_BY_ZERO_IMPL = FP_X_DZ,
                FP_INEXACT_IMPL = FP_X_IMP,
                FP_OVERFLOW_IMPL = FP_X_OFL,
                FP_UNDERFLOW_IMPL = FP_X_UFL,
                FP_INVALID_IMPL = FP_X_INV
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
            fp_rnd    _rnd;
            fp_except _exc;
        };

    }
}

#endif /* TECHNOSOFTWARE_FPENVIRONMENT_SUN_H */
