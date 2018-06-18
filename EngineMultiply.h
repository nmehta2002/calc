#pragma once


#include <memory>
#include "Engine.h"
#include "EngineFactory.h"

/**
 * Impelments an Engine to multiply a stream of numbers.
 */
class EngineMultiply : public Engine
{
public:

  EngineMultiply(std::unique_ptr<OperandStream> aPOperandStream):
    Engine(),
    _mPOperandStream(std::move(aPOperandStream))
  { }

  /**
   * A factory method to instantiate this engine.
   *
   * @param aPOperandStream: Input stream for the engine. The caller yields
   * ownership of the operandStream and expects the engine to free it.
   * @return The constructured engine, expects the caller to take
   * ownership of this engine and free it when its done.
   */
  static std::unique_ptr<Engine> make(std::unique_ptr<OperandStream> aPOperandStream);

  double run() final;

  virtual ~EngineMultiply() {}

private:

  Engine& operator =(const Engine &);

  EngineMultiply(EngineMultiply &);

  std::unique_ptr<OperandStream> _mPOperandStream;

};
