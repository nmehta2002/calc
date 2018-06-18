#pragma once

#include "OperandStream.h"

/*
 * Abstract base class that represents a calculator Engine. Expect subclasses of
 * engine to represent an operation like "multiply", "divide", "sum".
 */
class Engine
{

public:

  Engine() {}

  virtual double run() = 0;

  virtual ~Engine() {}

private:

  Engine& operator =(const Engine &);

  Engine(Engine &);

};
