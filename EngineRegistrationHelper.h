
#pragma once

#include "EngineFactory.h"

/**
 * Helper class, enables engines to register with the EngineFactory
 */

template <typename T>
class EngineRegistrationHelper
{
  public:

    EngineRegistrationHelper(const char                                 *aEngineName,
                             std::set<EngineFactory::EngineInputOption>  aInputOpts)
    {
      EngineFactory::registerEngine(aEngineName, T::make, aInputOpts);
    }
};
