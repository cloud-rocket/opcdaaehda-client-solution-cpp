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

#include "Base/FPEnvironment_DUMMY.h"

namespace Technosoftware
{
    namespace Base
    {


FPEnvironmentImpl::RoundingModeImpl FPEnvironmentImpl::_roundingMode;


FPEnvironmentImpl::FPEnvironmentImpl()
{
}


FPEnvironmentImpl::FPEnvironmentImpl(const FPEnvironmentImpl& env)
{
}


FPEnvironmentImpl::~FPEnvironmentImpl()
{
}


FPEnvironmentImpl& FPEnvironmentImpl::operator = (const FPEnvironmentImpl& env)
{
    return *this;
}


void FPEnvironmentImpl::KeepCurrentImpl()
{
}


void FPEnvironmentImpl::ClearFlagsImpl()
{
}


bool FPEnvironmentImpl::IsFlagImpl(FlagImpl flag)
{
    return false;
}


void FPEnvironmentImpl::SetRoundingModeImpl(RoundingModeImpl mode)
{
    _roundingMode = mode;
}


FPEnvironmentImpl::RoundingModeImpl FPEnvironmentImpl::GetRoundingModeImpl()
{
    return _roundingMode;
}


long double FPEnvironmentImpl::CopySignImpl(long double target, long double source)
{
    return (source >= 0 && target >= 0) || (source < 0 && target < 0) ? target : -target;
}

}
} 
