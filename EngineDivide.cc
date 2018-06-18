#include "EngineDivide.h"
#include <stdexcept>
#include <memory>
#include "EngineFactory.h"
#include "EngineRegistrationHelper.h"

static EngineRegistrationHelper<EngineDivide>
  engineRegistration(
    "divider",
    { EngineFactory::ENGINE_IN_OPT_NUMBER_LIST,
      EngineFactory::ENGINE_IN_OPT_FILE_LIST});


double EngineDivide::run(OperandStream& operandStream)
{
  double result;

  if (!operandStream.getNext(result))
  {
    throw std::runtime_error("Null input");
  }

  double operand;

  while (operandStream.getNext(operand))
  {
    // Checking for divide by zero.
    if (operand == 0)
    {
      throw std::overflow_error("0 is illegal input for EngineDivide, will lead to DIV BY 0 exception.");
    }

    result /= operand;
  }

  return (result);
}

// static
std::unique_ptr<Engine> EngineDivide::make()
{
  std::unique_ptr<Engine> p(new EngineDivide);
  return p;
}
