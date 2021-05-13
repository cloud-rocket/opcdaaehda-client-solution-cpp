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

#include "Base/FPEnvironment_WIN32.h"

namespace Technosoftware
{
    namespace Base
    {


        FPEnvironmentImpl::FPEnvironmentImpl()
        {
            _env = _controlfp(0, 0);
        }


        FPEnvironmentImpl::FPEnvironmentImpl(const FPEnvironmentImpl& env)
        {
            _env = env._env;
        }


        FPEnvironmentImpl::~FPEnvironmentImpl()
        {
            _controlfp(_env, _MCW_RC);
        }


        FPEnvironmentImpl& FPEnvironmentImpl::operator = (const FPEnvironmentImpl& env)
        {
            _env = env._env;
            return *this;
        }


        void FPEnvironmentImpl::KeepCurrentImpl()
        {
            _env = _controlfp(0, 0);
        }


        void FPEnvironmentImpl::ClearFlagsImpl()
        {
            _clearfp();
        }


        bool FPEnvironmentImpl::IsFlagImpl(FlagImpl flag)
        {
            return (_statusfp() & flag) != 0;
        }


        void FPEnvironmentImpl::SetRoundingModeImpl(RoundingModeImpl mode)
        {
            _controlfp(mode, _MCW_RC);
        }


        FPEnvironmentImpl::RoundingModeImpl FPEnvironmentImpl::GetRoundingModeImpl()
        {
            return RoundingModeImpl(_controlfp(0, 0) & _MCW_RC);
        }

    }
}
