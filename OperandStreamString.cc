#include "OperandStreamString.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

bool OperandStreamString::getNext(int64_t &aNext)
{
  try
  {
    if (!(_mNextIdx < _mStrings.size()))
      return false;

    aNext = std::stoll(_mStrings[_mNextIdx]);

    _mNextIdx++;

  }catch(std::invalid_argument& inve)
  {
    std::ostringstream oss;
    oss<<"Argument "<<_mStrings[_mNextIdx]<<" not a number.";
    throw std::invalid_argument(oss.str());
  }

  return true;
}
