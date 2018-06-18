#include "EngineMultiply.h"
#include <stdexcept>
#include <memory>
#include "EngineFactory.h"
#include "EngineRegistrationHelper.h"

static EngineRegistrationHelper<EngineMultiply>
  engineRegistration("multiplier",
                     { EngineFactory::ENGINE_IN_OPT_FILE_LIST});


double EngineMultiply::run(OperandStream& operandStream)
{
  double result;

  if (!operandStream.getNext(result))
  {
    throw std::runtime_error("Null input");
  }

  double operand;

  while (operandStream.getNext(operand))
  {
    result *= operand;
  }

  return (result);
}

// static
std::unique_ptr<Engine> EngineMultiply::make()
{
  std::unique_ptr<Engine> p(new EngineMultiply);
  return p;
}
