/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://technosoftware.com
 *
 * Purpose:
 * Definitions of class FPEnvironmentImpl for C99.
 *
 * Based on: POCO C++ Foundation Library
 *           Copyright (c) 2005-2007, Applied Informatics Software Engineering GmbH.
 *           and Contributors.
 *
 * The Software is subject to the Technosoftware GmbH Software License Agreement,
 * which can be found here:
 * https://technosoftware.com/documents/Technosoftware_SLA.pdf
 */


#include "Base/FPEnvironment_C99.h"


namespace Technosoftware
{
    namespace Base
    {


FPEnvironmentImpl::FPEnvironmentImpl()
{
    fegetenv(&_env);
}


FPEnvironmentImpl::FPEnvironmentImpl(const FPEnvironmentImpl& env)
{
    _env = env._env;
}


FPEnvironmentImpl::~FPEnvironmentImpl()
{
    fesetenv(&_env);
}


FPEnvironmentImpl& FPEnvironmentImpl::operator = (const FPEnvironmentImpl& env)
{
    _env = env._env;
    return *this;
}


void FPEnvironmentImpl::KeepCurrentImpl()
{
    fegetenv(&_env);
}


void FPEnvironmentImpl::ClearFlagsImpl()
{
    feclearexcept(FE_ALL_EXCEPT);
}


bool FPEnvironmentImpl::IsFlagImpl(FlagImpl flag)
{
    return fetestexcept(flag) != 0;
}


void FPEnvironmentImpl::SetRoundingModeImpl(RoundingModeImpl mode)
{
    fesetround(mode);
}


FPEnvironmentImpl::RoundingModeImpl FPEnvironmentImpl::GetRoundingModeImpl()
{
    return (RoundingModeImpl) fegetround();
}


long double FPEnvironmentImpl::CopySignImpl(long double target, long double source)
{
    return (source >= 0 && target >= 0) || (source < 0 && target < 0) ? target : -target;
}

}
}
