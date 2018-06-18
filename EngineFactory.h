#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>
#include "Engine.h"

/**
 * Class responsible for instantiating engines.
 *
 * Indiviual engines are expected to register with this class using
 * EngineRegistrationHelper. Once registered this class can then be used
 * to instantiate the engines.
 */
class EngineFactory
{
public:

  typedef std::unique_ptr<Engine>(*EngineFactoryFn)(
      std::unique_ptr<OperandStream> aPOpStream) ;


  enum EngineInputOption
  {
    ENGINE_IN_OPT_NUMBER_LIST = 0x01,//!< ENGINE_IN_OPT_NUMBER_LIST
    ENGINE_IN_OPT_FILE_LIST = 0x02   //!< ENGINE_IN_OPT_FILE_LIST
  };

  struct EngineMapEntry
  {
    EngineFactoryFn factoryFn;
    std::set<EngineInputOption> inputOpts;
  };

  /**
   * Registers a new engine with the EngineFactory, once registered the engine
   * can then be instantiated using the make function.
   *
   * @param aEngineName: Name of the engine
   * @param aEngineFactoryFn: The static factory function that will instantiate the engine.
   * @param aInputOpts: The input options allowed for this engine.
   */
  static void registerEngine(const char*                       aEngineName,
                             EngineFactoryFn                   aEngineFactoryFn,
                             const std::set<EngineInputOption> aInputOpts);


  /**
   * The factory function to instantiate an engine.
   * @param aEngineName
   * @param aEngineInput
   * @param aNumArgs
   * @return
   */
  static std::unique_ptr<Engine> make(const char *aEngineName,
                                      char       *aEngineInput[],
                                      int         aNumArgs);



  struct EngineEntry
  {
    std::string                 name;
    std::set<EngineInputOption> inputOpts;
  };

  /**
   * Provides inspection API to query all registered engines.
   * @return
   */
  static std::vector<EngineEntry> getRegisteredEngines();


private:

  static std::unique_ptr<OperandStream>
      _makeOperandStream(const char  *aEngineName,
                         char        *aEngineInput[],
                         int          aNumArgs);


  static std::map<std::string, EngineFactory::EngineMapEntry> nameToEngineMap;

  static EngineInputOption detectInputOpt(char firstChar);

  static std::string inputOptionStr(EngineFactory::EngineInputOption opt);

};

