#pragma once

#include "OperandStream.h"
#include <cstdint>
#include <string>
#include <vector>

//*****************************************************************************
//
// Class that implements a stream sourced from a set of strings.
//

class OperandStreamString : public OperandStream
{
  public:

    OperandStreamString(const char* aStrings[], int aCount):
      _mNextIdx(0)
    {
      for (int i = 0; i < aCount; i++)
      {
        std::string str(aStrings[i]);
        _mStrings.push_back(str);
      }
    }

    bool getNext(double &a_next);

    virtual ~OperandStreamString() {}

  private:

    OperandStreamString();

    OperandStreamString& operator =(OperandStreamString &);

    OperandStreamString(OperandStreamString &);

    std::vector<std::string> _mStrings;

    uint64_t _mNextIdx;

};
