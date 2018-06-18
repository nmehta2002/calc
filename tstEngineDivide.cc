#include <cassert>
#include <iostream>
#include "EngineDivide.h"
#include "OperandStreamString.h"

void tstEngineDivide()
{
  std::cout<<"tstEngineDivide....";

  const char *strs[] = {"1.0", "2.0"};

  std::unique_ptr<OperandStream> pOpStreamString(new OperandStreamString(strs, 2));

  std::unique_ptr<Engine> pEngineDivide(EngineDivide::make(std::move(pOpStreamString)));

  auto actualResult = pEngineDivide->run();

  assert(actualResult == 0.5);

  std::cout<<"success"<<std::endl;

}


void tstEngineDivideNegative()
{
  std::cout<<"tstEngineDivideNegative....";

  const char *strs[] = {"1.0", "0.0"};

  std::unique_ptr<OperandStream> pOpStreamString(new OperandStreamString(strs, 2));

  std::unique_ptr<Engine> pEngineDivide(EngineDivide::make(std::move(pOpStreamString)));

  try
  {
    pEngineDivide->run();
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
