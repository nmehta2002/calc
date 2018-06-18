
#pragma once

#include "EngineFactory.h"

/**
 * Helper class, to let engines to register with the EngineFactory
 * at load time. See example in EngineDivide.cc
 *
 * Each engine implementation is expected to create a static instance.
 * The act of creating the static instance will do the following
 * - Instantiate the template with T set to EngineType (generate the code.)
 * - Call the constructor, the constructor in turn will register the factory
 *   method and the input options with the factory.
 *
 * The advantage of this method:
 * - Engine registration is automatic and happens even before main is called.
 * - The code to register the engine lives with the engine implementation.
 * - The EngineImplementation header file is not included in any .cc or .h file,
 *   thus can save on compile time.
 *
 * The class uses CRTP (Curiously recurring template pattern).
 *
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
