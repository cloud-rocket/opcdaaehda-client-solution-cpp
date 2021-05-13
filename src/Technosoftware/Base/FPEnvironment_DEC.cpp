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


//
// _XOPEN_SOURCE disables the ieee fp functions
// in <math.h>, therefore we undefine it for this file.
//
#undef _XOPEN_SOURCE


#include <math.h>
#include <fp.h>
#include <fp_class.h>
#if defined(__VMS)
#include <starlet.h>
#endif
#include "Base/FPEnvironment_DEC.h"


namespace Technosoftware
{
    namespace Base
    {


FPEnvironmentImpl::FPEnvironmentImpl()
{
#if defined(__VMS)
    #pragma pointer_size save
    #pragma pointer_size 32
    struct _ieee env;
    sys$ieee_set_fp_control(0, 0, &env);
    #pragma pointer_size restore
    _env = env;
#else
    _env = ieee_get_fp_control();
#endif
}


FPEnvironmentImpl::FPEnvironmentImpl(const FPEnvironmentImpl& env)
{
    _env = env._env;
}


FPEnvironmentImpl::~FPEnvironmentImpl()
{
#if defined(__VMS)
    #pragma pointer_size save
    #pragma pointer_size 32
    struct _ieee mask;
    mask.ieee$q_flags = 0xFFFFFFFFFFFFFFFF;
    struct _ieee env = _env;
    sys$ieee_set_fp_control(&mask, &env, 0);
    #pragma pointer_size restore
#else
    ieee_set_fp_control(_env);
#endif
}


FPEnvironmentImpl& FPEnvironmentImpl::operator = (const FPEnvironmentImpl& env)
{
    _env = env._env;
    return *this;
}


bool FPEnvironmentImpl::IsInfiniteImpl(float value)
{
    int cls = fp_classf(value);
    return cls == FP_POS_INF || cls == FP_NEG_INF;
}


bool FPEnvironmentImpl::IsInfiniteImpl(double value)
{
    int cls = fp_class(value);
    return cls == FP_POS_INF || cls == FP_NEG_INF;
}


bool FPEnvironmentImpl::IsInfiniteImpl(long double value)
{
    int cls = fp_classl(value);
    return cls == FP_POS_INF || cls == FP_NEG_INF;
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
    return isnanl(value) != 0;
}


float FPEnvironmentImpl::CopySignImpl(float target, float source)
{
    return copysignf(target, source);
}


double FPEnvironmentImpl::CopySignImpl(double target, double source)
{
    return copysign(target, source);
}


long double FPEnvironmentImpl::CopySignImpl(long double target, long double source)
{
    return copysignl(target, source);
}


void FPEnvironmentImpl::KeepCurrentImpl()
{
#if defined(__VMS)
    #pragma pointer_size save
    #pragma pointer_size 32
    struct _ieee env;
    sys$ieee_set_fp_control(0, 0, &env);
    #pragma pointer_size restore
    _env = env;
#else
    ieee_set_fp_control(_env);
#endif
}


void FPEnvironmentImpl::ClearFlagsImpl()
{
#if defined(__VMS)
    #pragma pointer_size save
    #pragma pointer_size 32
    struct _ieee mask;
    mask.ieee$q_flags = 0xFFFFFFFFFFFFFFFF;
    struct _ieee clr;
    clr.ieee$q_flags  = 0;
    sys$ieee_set_fp_control(&mask, &clr, 0);
    #pragma pointer_size restore
#else
    ieee_set_fp_control(0);
#endif
}


bool FPEnvironmentImpl::IsFlagImpl(FlagImpl flag)
{
#if defined(__VMS)
    #pragma pointer_size save
    #pragma pointer_size 32
    struct _ieee flags;
    sys$ieee_set_fp_control(0, 0, &flags);
    return (flags.ieee$q_flags & flag) != 0;
    #pragma pointer_size restore
#else
    return (ieee_get_fp_control() & flag) != 0;
#endif
}


void FPEnvironmentImpl::SetRoundingModeImpl(RoundingModeImpl mode)
{
    // not supported
}


FPEnvironmentImpl::RoundingModeImpl FPEnvironmentImpl::GetRoundingModeImpl()
{
    // not supported
    return FPEnvironmentImpl::RoundingModeImpl(0);
}

}
} 
