#include <cassert>
#include <iostream>
#include "EngineDivide.h"
#include "OperandStreamString.h"

void tstEngineDivide()
{
  std::cout<<"tstEngineDivide....";

  const char *strs[] = {"1.0", "2.0"};

  OperandStreamString opStreamString(strs, 2);
  OperandStream& opStream = opStreamString;

  std::unique_ptr<Engine> pEngineDivide(EngineDivide::make());

  auto actualResult = pEngineDivide->run(opStream);

  assert(actualResult == 0.5);

  std::cout<<"success"<<std::endl;

}

void tstEngineDivideNegative()
{
  std::cout<<"tstEngineDivideNegative....";

  const char *strs[] = {"1.0", "0.0"};

  OperandStreamString opStreamString(strs, 2);
  OperandStream& opStream = opStreamString;

  std::unique_ptr<Engine> pEngineDivide(EngineDivide::make());

  try
  {
    pEngineDivide->run(opStream);
    assert(false);
  }
  catch(std::overflow_error& ofe)
  {
    std::cout<<"success."<<std::endl;
  }
}

int main()
{
  tstEngineDivide();
  tstEngineDivideNegative();
}
