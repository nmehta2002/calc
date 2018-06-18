#pragma once

#include <map>
#include <memory>
#include "Engine.h"
#include <set>
#include <vector>


class EngineFactory
{
public:

  typedef std::unique_ptr<Engine>(*EngineFactoryFn)() ;

  enum EngineInputOption
  {
    ENGINE_IN_OPT_NUMBER_LIST = 0x01,
    ENGINE_IN_OPT_FILE_LIST = 0x02
  };

  struct EngineMapEntry
  {
    EngineFactoryFn factoryFn;
    std::set<EngineInputOption> inputOpts;
  };

  static void registerEngine(const char*                       aEngineName,
                             EngineFactoryFn                   aEngineFactoryFn,
                             const std::set<EngineInputOption> aInputOpts);

  static std::unique_ptr<Engine> make(const char *engineName,
                                      char       *engineInput[],
                                      int         num_args);



  static std::unique_ptr<OperandStream>
    makeOperandStream(const char  *engineName,
                      char        *engineInput[],
                      int          num_args);

  struct EngineEntry
  {
    std::string                 name;
    std::set<EngineInputOption> inputOpts;
  };

  static std::vector<EngineEntry> getRegisteredEngines();


private:

  static std::map<std::string, EngineFactory::EngineMapEntry> nameToEngineMap;

  static EngineInputOption detectInputOpt(char firstChar);

  static std::string inputOptionStr(EngineFactory::EngineInputOption opt);

};

