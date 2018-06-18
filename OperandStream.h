#pragma once

#include <cstdint>

/**
 * Abstract base class that represents a stream of operands read from some
 * source, e.g. sources could be a command line or a list of files.
 */
class OperandStream
{
  public:

  OperandStream() {}

  /**
   * Retrieves the next element from the stream.
   * Sets aOutput to the next element.
   *
   * @param aOutput
   * @return
   *  If unread elements exists returns true and element is returned in aOutput
   *  If no more elements left returns false.
   *
   */
  virtual bool getNext(uint64_t &aOutput) = 0;

  virtual ~OperandStream() {}

  private:

    OperandStream& operator =(OperandStream &);

    OperandStream(OperandStream &);

};
