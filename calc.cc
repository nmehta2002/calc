#include <string.h>
#include <map>
#include <iostream>
#include "EngineFactory.h"
#include "OperandStreamFile.h"
#include "OperandStreamString.h"
#include <sstream>


std::string makeEngineUsageStr(
    const std::string                      aName,
    const EngineFactory::EngineInputOption aInputOpt)
{
  std::ostringstream ostream;

  ostream<<"calc "<<aName<<" ";

  switch(aInputOpt)
  {
    case EngineFactory::ENGINE_IN_OPT_NUMBER_LIST:
      ostream<<"<number1> [<number2> <number3> ....]";
      break;
    case EngineFactory::ENGINE_IN_OPT_FILE_LIST:
      ostream<<"<file1> [<file2> <file3> ....]";
      break;
  }
  return(ostream.str());
}

// Generates the usage string based on the registered engines.

void print_usage()
{
  std::cerr<<"Usage:"<<std::endl;

  std::cerr<<"calc help"<<std::endl;

  auto engineEntries = EngineFactory::getRegisteredEngines();

  for (auto engineEntry : engineEntries)
  {
    for (auto inputOpt : engineEntry.inputOpts)
    {
      std::cerr<<makeEngineUsageStr(engineEntry.name, inputOpt)<<std::endl;
    }
  }
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr<<"Missing required arguments"<<std::endl;
    print_usage();
    return (-1);
  }

  if (strcmp(argv[1], "help") == 0)
  {
    print_usage();
    return (0);
  }

  // If here not printing help string, now need minimum of 3 arguments.
  // For e.g. calc dividier 1

  if (argc < 3)
  {
    std::cerr<<"Missing required arguments"<<std::endl;
    print_usage();
    return (-1);
  }

  const char* engineName = argv[1];

  try
  {
    std::unique_ptr<Engine> pEngine =
        EngineFactory::make(engineName, &argv[2], argc - 2);

    double result = pEngine->run();

    std::cout<<"Engine result is : "<<result<<std::endl;

  }
  catch (std::exception &e)
  {
    std::cerr<<"Engine operation failed with error: " << e.what()<<std::endl;
    return (-1);
  }

  return (0);
}
