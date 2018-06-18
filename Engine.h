#pragma once

#include "OperandStream.h"
#include <cstdint>

/**
 * Abstract base class that represents a calculator Engine. Expect subclasses of
 * engine to represent an operation like "multiply", "divide", "sum".
 *
 * This class is central to the frame-work thus requires some explanation.
 *
 * Note:
 * - All implementers of Engine are expected to do the following:
 *
 *   1. A static factory method that takes operandStream as input of the form below:
 *   static std::unique_ptr<Engine> make(std::unique_ptr<OperandStream> aPOperandStream);
 *
 *
 *   2. A run() method that implements the engine specific computation and
 *   returns the result.
 *
 *   3. Register the engine with the EngineFactory using EngineRegistrationHelper
 *      Follow EngineDivide.cc, should be straight forward.
 *
 */
class Engine
{

public:

  Engine() {}

  /**
   * Subclasses need to provide an implementation of this operation.
   * The implementation will typically include some computation like
   * "multiply", "divide", "sum" over a stream of integers.
   * @return
   */
  virtual uint64_t run() = 0;

  virtual ~Engine() {}

private:

  Engine& operator =(const Engine &);

  Engine(Engine &);

};
