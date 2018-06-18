
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
std::unique_ptr<Engine> EngineFactory::make(const char *engineName, char *engineInput[], int num_args)
{
  try
  {
    EngineMapEntry &engineMapEntry = nameToEngineMap.at(engineName);

    // If here means found a good engine to run

    std::unique_ptr<Engine> p_engine = engineMapEntry.factoryFn();

    return (p_engine);

  }catch(std::out_of_range &ofr)
  {
    std::ostringstream sstream;
    sstream<<"Invalid engine name :"<<engineName<<std::endl;
    throw std::invalid_argument(sstream.str());
  }
}

//static
std::unique_ptr<OperandStream>
EngineFactory::makeOperandStream(const char* engineName, char *engineInput[], int num_args)
{
  std::unique_ptr<OperandStream> pOperandStream;

  EngineMapEntry &engineMapEntry = nameToEngineMap.at(engineName);

  auto opt = detectInputOpt(engineInput[0][0]);

  if (engineMapEntry.inputOpts.find(opt) == engineMapEntry.inputOpts.end())
  {
    std::ostringstream sstream;
    sstream<<"Input option "<<inputOptionStr(opt)<<" not supported."<<std::endl;
    throw std::invalid_argument(sstream.str());
  }

  // If here engine supports the input option, instantiate the stream based
  // on input option.

  switch (opt)
  {
    case ENGINE_IN_OPT_FILE_LIST:
      pOperandStream.reset(new OperandStreamFile(engineInput, num_args));
      break;

    case ENGINE_IN_OPT_NUMBER_LIST:
      pOperandStream.reset(new OperandStreamString(engineInput, num_args));
      break;
  };

  return (std::move(pOperandStream));
}

//*****************************************************************************

// Maps enum option to a string.
std::string EngineFactory::inputOptionStr(EngineFactory::EngineInputOption opt)
{
  std::string result;

  switch(opt)
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


//*****************************************************************************

// Detects if the input is either a file-list or a list of numbers.
// Uses the first character of the first input string.
// If the input is a list of files, would expect the first character of the
// file-name to be a letter.

//static
EngineFactory::EngineInputOption
EngineFactory::detectInputOpt(char firstChar)
{
  if (isalpha(firstChar))
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