#include "EngineSum.h"
#include <stdexcept>
#include <memory>
#include "EngineFactory.h"
#include "EngineRegistrationHelper.h"

static EngineRegistrationHelper<EngineSum>
  engineRegistration(
    "sum",
    { EngineFactory::ENGINE_IN_OPT_NUMBER_LIST,
      EngineFactory::ENGINE_IN_OPT_FILE_LIST});


uint64_t EngineSum::run()
{
  uint64_t result;

  if (!_mPOperandStream->getNext(result))
  {
    throw std::runtime_error("Null input");
  }

  uint64_t operand;

  while (_mPOperandStream->getNext(operand))
  {
    result += operand;
  }

  return (result);
}

// static
std::unique_ptr<Engine> EngineSum::make(std::unique_ptr<OperandStream> aPOperandStream)
{
  std::unique_ptr<Engine> p(new EngineSum(std::move(aPOperandStream)));
  return p;
}
