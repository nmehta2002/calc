#pragma once

#include "OperandStream.h"

//*****************************************************************************
//
// Abstract base class that represents a calculator Engine. Expect subclasses of
// engine to represent an operation like "multiply", "divide", "sum".
//


class Engine
{

public:

  //*****************************************************************************

  // All subclasses of engine should implement this method.

  Engine() {}

  virtual double run(OperandStream &operandStream) = 0;

  virtual ~Engine() {}

private:

  Engine& operator =(const Engine &);

  Engine(Engine &);

};
