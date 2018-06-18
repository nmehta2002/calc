#pragma once


#include <memory>
#include "Engine.h"
#include "EngineFactory.h"

/*
 * Implements an engine to divide a stream of numbers.
 */
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


