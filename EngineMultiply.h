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

  EngineMultiply(std::unique_ptr<OperandStream> aPOperandStream):
    Engine(),
    _mPOperandStream(std::move(aPOperandStream))
  { }

  static std::unique_ptr<Engine> make(std::unique_ptr<OperandStream> aPOperandStream);

  virtual double run();

  virtual ~EngineMultiply() {}

private:

  Engine& operator =(const Engine &);

  EngineMultiply(EngineMultiply &);

  std::unique_ptr<OperandStream> _mPOperandStream;

};
