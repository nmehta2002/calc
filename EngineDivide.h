#pragma once


#include <memory>
#include "Engine.h"
#include "EngineFactory.h"

/**
 * Impelments an Engine to divide a stream of numbers.
 */
class EngineDivide : public Engine
{
public:

  /**
   *
   * @param aPOperandStream
   */
  EngineDivide(std::unique_ptr<OperandStream> aPOperandStream):
    Engine(),
    _mPOperandStream(std::move(aPOperandStream))
  { }

  /**
   * A factory method to instantiate this engine.
   *
   * @param aPOperandStream: Input stream for the engine. The caller yields
   * ownership of the operandStream and expects the engine to free it,
   * when the engine is destroyed.
   * @return The constructured engine, expects the caller to take
   * ownership of this engine and free it when its done.
   *
   */
  static std::unique_ptr<Engine> make(std::unique_ptr<OperandStream> aPOperandStream);

  virtual uint64_t run() final;

  virtual ~EngineDivide() {}

private:

  Engine& operator =(const Engine &);

  EngineDivide(EngineDivide &);

  std::unique_ptr<OperandStream> _mPOperandStream;

};


