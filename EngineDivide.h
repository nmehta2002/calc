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

class EngineDivide : public Engine
{
public:

  EngineDivide():Engine()
  { }

  static std::unique_ptr<Engine> make();

  virtual double run(OperandStream& operandStream);

  virtual ~EngineDivide() {}

private:

  Engine& operator =(const Engine &);

  EngineDivide(EngineDivide &);


};


