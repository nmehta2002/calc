
#include "EngineFactory.h"
#include <sstream>
#include <string.h>
#include <cassert>

#include "OperandStream.h"
#include "OperandStreamFile.h"
#include "OperandStreamString.h"
#include <sstream>

std::map<std::string, EngineFactory::EngineMapEntry> EngineFactory::nameToEngineMap;

/* static */
void EngineFactory::
  registerEngine(const char*                        aEngineName,
                  EngineFactoryFn                   aEngineFactoryFn,
                  const std::set<EngineInputOption> aInputOpts)
{
  EngineMapEntry engineMapEntry;

  engineMapEntry.factoryFn = aEngineFactoryFn;
  engineMapEntry.inputOpts = aInputOpts;

  std::pair<std::string, EngineFactory::EngineMapEntry> pair;
  pair.first = aEngineName;
  pair.second = engineMapEntry;


  auto result = nameToEngineMap.insert(pair);

  if (!result.second)
  {
    std::ostringstream sstream;
    sstream<<"Failed to register engine "<<aEngineName<<" engine with this name already exists."<<std::endl;
    throw std::invalid_argument(sstream.str());
  }
}

// static
std::unique_ptr<Engine> EngineFactory::make(const char *aEngineName, char *aEngineInput[], int aNumArgs)
{
  try
  {
    EngineMapEntry &engineMapEntry = nameToEngineMap.at(aEngineName);

    // If here means found a good engine to run
    std::unique_ptr<OperandStream> pOperandStream =
      _makeOperandStream(aEngineName, aEngineInput, aNumArgs);

    return(engineMapEntry.factoryFn(std::move(pOperandStream)));

  }catch(std::out_of_range &ofr)
  {
    std::ostringstream sstream;
    sstream<<"Invalid engine name :"<<aEngineName<<std::endl;
    throw std::invalid_argument(sstream.str());
  }
}

//static
std::unique_ptr<OperandStream>
EngineFactory::_makeOperandStream(const char* aEngineName, char *aEngineInput[], int aNumArgs)
{
  std::unique_ptr<OperandStream> pOperandStream;

  EngineMapEntry &engineMapEntry = nameToEngineMap.at(aEngineName);

  auto opt = _detectInputOpt(aEngineInput[0][0]);

  if (engineMapEntry.inputOpts.find(opt) == engineMapEntry.inputOpts.end())
  {
    std::ostringstream sstream;
    sstream<<"Input option "<<_inputOptionStr(opt)<<" not supported."<<std::endl;
    throw std::invalid_argument(sstream.str());
  }

  // If here engine supports the input option, instantiate the stream based
  // on input option.

  switch (opt)
  {
    case ENGINE_IN_OPT_FILE_LIST:
      pOperandStream.reset(new OperandStreamFile(aEngineInput, aNumArgs));
      break;

    case ENGINE_IN_OPT_NUMBER_LIST:
      pOperandStream.reset(new OperandStreamString(aEngineInput, aNumArgs));
      break;
  };

  return (std::move(pOperandStream));
}

//static
std::string EngineFactory::_inputOptionStr(EngineFactory::EngineInputOption aOpt)
{
  std::string result;

  switch(aOpt)
  {
    case ENGINE_IN_OPT_FILE_LIST:
      result = "file_list";
      break;
    case ENGINE_IN_OPT_NUMBER_LIST:
      result = "number_list";
      break;

    default:
      assert(false);
  }

  return (result);
}

//static
EngineFactory::EngineInputOption
EngineFactory::_detectInputOpt(char aFirstChar)
{
  if (isalpha(aFirstChar))
  {
    return ENGINE_IN_OPT_FILE_LIST;
  }
  return (ENGINE_IN_OPT_NUMBER_LIST);
}

//static
std::vector<EngineFactory::EngineEntry> EngineFactory::getRegisteredEngines()
{

  std::vector<EngineFactory::EngineEntry> result_vec;

  for (auto it = nameToEngineMap.begin(); it != nameToEngineMap.end(); it++)
  {
    EngineEntry entry;

    entry.name = it->first;
    entry.inputOpts = it->second.inputOpts;

    result_vec.push_back(entry);
  }

  return (result_vec);
}
