#pragma once

//***************************************************************************
//***************************************************************************

// Purpose:
//
// Impelments an Engine that divides numbers.
//***************************************************************************
//***************************************************************************

#include <memory>
#include "Engine.h"
#include "EngineFactory.h"

class EngineMultiply : public Engine
{
public:

  EngineMultiply():Engine()
  { }

  static std::unique_ptr<Engine> make();

  virtual double run(OperandStream& p_operandStream);

  virtual ~EngineMultiply() {}

private:

  Engine& operator =(const Engine &);

  EngineMultiply(EngineMultiply &);

};
