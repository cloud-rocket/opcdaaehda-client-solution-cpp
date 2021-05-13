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

#include <math.h>
#include "Base/FPEnvironment_SUN.h"

namespace Technosoftware
{
    namespace Base
    {


FPEnvironmentImpl::FPEnvironmentImpl()
{
    _rnd = fpgetround();
    _exc = fpgetmask();
}


FPEnvironmentImpl::FPEnvironmentImpl(const FPEnvironmentImpl& env)
{
    _rnd = env._rnd;
    _exc = env._exc;
}


FPEnvironmentImpl::~FPEnvironmentImpl()
{
    fpsetround(_rnd);
    fpsetmask(_exc);
}


FPEnvironmentImpl& FPEnvironmentImpl::operator = (const FPEnvironmentImpl& env)
{
    _rnd = env._rnd;
    _exc = env._exc;
    return *this;
}


bool FPEnvironmentImpl::IsInfiniteImpl(float value)
{
    int cls = fpclass(value);
    return cls == FP_PINF || cls == FP_NINF;
}


bool FPEnvironmentImpl::IsInfiniteImpl(double value)
{
    int cls = fpclass(value);
    return cls == FP_PINF || cls == FP_NINF;
}


bool FPEnvironmentImpl::IsInfiniteImpl(long double value)
{
    int cls = fpclass(value);
    return cls == FP_PINF || cls == FP_NINF;
}


bool FPEnvironmentImpl::IsNaNImpl(float value)
{
    return isnanf(value) != 0;
}


bool FPEnvironmentImpl::IsNaNImpl(double value)
{
    return isnan(value) != 0;
}


bool FPEnvironmentImpl::IsNaNImpl(long double value)
{
    return isnan((double) value) != 0;
}


float FPEnvironmentImpl::CopySignImpl(float target, float source)
{
    return (float) copysign(target, source);
}


double FPEnvironmentImpl::CopySignImpl(double target, double source)
{
    return (float) copysign(target, source);
}


long double FPEnvironmentImpl::CopySignImpl(long double target, long double source)
{
    return (source > 0 && target > 0) || (source < 0 && target < 0) ? target : -target;
}


void FPEnvironmentImpl::KeepCurrentImpl()
{
    fpsetround(_rnd);
    fpsetmask(_exc);
}


void FPEnvironmentImpl::ClearFlagsImpl()
{
    fpsetsticky(0);
}


bool FPEnvironmentImpl::IsFlagImpl(FlagImpl flag)
{
    return (fpgetsticky() & flag) != 0;
}


void FPEnvironmentImpl::SetRoundingModeImpl(RoundingModeImpl mode)
{
    fpsetround((fp_rnd) mode);
}


FPEnvironmentImpl::RoundingModeImpl FPEnvironmentImpl::GetRoundingModeImpl()
{
    return (FPEnvironmentImpl::RoundingModeImpl) fpgetround();
}
}

} 
