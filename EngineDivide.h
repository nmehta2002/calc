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

  EngineDivide(std::unique_ptr<OperandStream> aPOperandStream):
    Engine(),
    _mPOperandStream(std::move(aPOperandStream))
  { }

  static std::unique_ptr<Engine> make(std::unique_ptr<OperandStream> aPOperandStream);

  virtual double run();

  virtual ~EngineDivide() {}

private:

  Engine& operator =(const Engine &);

  EngineDivide(EngineDivide &);

  std::unique_ptr<OperandStream> _mPOperandStream;

};


