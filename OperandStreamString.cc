//***************************************************************************

// Copyright (c) 2018 ClearSky Data, Inc.
// All Rights Reserved.
//
// NOTICE: All information contained herein is, and remains the property of
// ClearSky Data, Inc. and its suppliers, if any.  The intellectual and
// technical concepts contained herein are proprietary to ClearSky Data, Inc.
// and its suppliers and may be covered by U.S. and Foreign Patents, patents in
// process, and are protected by trade secret or copyright law.  Dissemination
// of this information or reproduction of this material is strictly forbidden
// unless prior written permission is obtained from ClearSky Data, Inc.

//***************************************************************************
//***************************************************************************

#include "OperandStreamString.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

bool OperandStreamString::getNext(double &a_next)
{
  try
  {
    if (!(_mNextIdx < _mStrings.size()))
      return false;

    a_next = std::stod(_mStrings[_mNextIdx]);

    _mNextIdx++;

  }catch(std::invalid_argument& inve)
  {
    std::ostringstream oss;
    oss<<"Argument "<<_mStrings[_mNextIdx]<<" not a number.";
    throw std::invalid_argument(oss.str());
  }

  return true;
}
