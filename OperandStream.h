#pragma once

//***************************************************************************
//***************************************************************************

// Purpose:
// 
// Abstract base class that represents a stream of operands read from some
// source, e.g. sources could be a command line or a list of files.

//***************************************************************************
//***************************************************************************

class OperandStream
{
  public:

  OperandStream() {}
  //*************************************************************************
  //
  // Sets output to the next element and returns true.
  // If the stream has reached its end, returns false.

  virtual bool getNext(double &aOutput) = 0;

  virtual ~OperandStream() {}

  private:

    OperandStream& operator =(OperandStream &);

    OperandStream(OperandStream &);

};
