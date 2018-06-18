#include "EngineMultiply.h"
#include <stdexcept>
#include <memory>
#include "EngineFactory.h"
#include "EngineRegistrationHelper.h"

static EngineRegistrationHelper<EngineMultiply>
  engineRegistration("multiplier",
                     { EngineFactory::ENGINE_IN_OPT_FILE_LIST});


int64_t EngineMultiply::run()
{
  int64_t result;

  if (!_mPOperandStream->getNext(result))
  {
    throw std::runtime_error("Null input");
  }

  int64_t operand;

  while (_mPOperandStream->getNext(operand))
  {
    result *= operand;
  }

  return (result);
}

// static
std::unique_ptr<Engine> EngineMultiply::make(std::unique_ptr<OperandStream> aPOperandStream)
{
  std::unique_ptr<Engine> p(new EngineMultiply(std::move(aPOperandStream)));
  return p;
}
