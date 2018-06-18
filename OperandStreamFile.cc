#include <iostream>
#include <fstream>
#include <sstream>
#include "OperandStreamFile.h"
#include <cassert>


bool OperandStreamFile::getNext(double &aNext)
{
  double nextValue;

  /**
   *
   *  The loop below reads the next value from the current file, if the current
   * file has has reached EOF it will open the next file and read the first value
   * from the next file.
   * The loop should also handle empty files, by just skipping over them.
   *
   */

  while (true)
  {
    if (!_mPCurrentFile)
    {
      if (!_openNextFile())
        return false;
    }

    // If here _mPCurrentFile has a good open file.

    if (((*_mPCurrentFile) >> nextValue))
    {
      // Got a new value return it.
      aNext = nextValue;
      return true;
    }
    else
    {
      if (_mPCurrentFile->fail() && !_mPCurrentFile->eof())
      {
        std::ostringstream sstream;
        sstream<<"Failed to extract numbers from file: "<<_mFiles[_mNextFileIndex-1];
        throw std::invalid_argument(sstream.str());
      }

      assert(_mPCurrentFile->eof());

      // If here a file was open but reached the end of file.
      // Need to open the next file, and read the value from the next file.
      // Close the current file and free the memory, and repeat the loop.

      std::unique_ptr<std::fstream> pFile(std::move(_mPCurrentFile));
    }
  }

  return(true);
}

bool OperandStreamFile::_openNextFile()
{
  if (!(_mNextFileIndex < _mFiles.size()))
      return false;

  std::unique_ptr<std::fstream> pCurrentFile(
        new std::fstream(_mFiles[_mNextFileIndex], std::ios_base::in));

  if (!pCurrentFile->good())
  {
    std::ostringstream sstream;
    sstream<<"Failed to open file : "<< _mFiles[_mNextFileIndex];
    throw std::invalid_argument(sstream.str());
  }

  // If here the file was opened successfully.
  _mPCurrentFile = std::move(pCurrentFile);
  _mNextFileIndex++;

  return true;
}


