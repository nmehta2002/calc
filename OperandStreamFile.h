#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include "OperandStream.h"

/**
 * Class that implements a stream sourced from a set of files.
 */

class OperandStreamFile : public OperandStream
{
  public:

    OperandStreamFile(
        const char* const* aFiles,
        uint32_t            aCount,
        const bool          implicitTxtExt = true):
      _mPCurrentFile(nullptr),
      _mNextFileIndex(0)
    {
      for (uint32_t i = 0; i < aCount; i++)
      {
        std::string str(aFiles[i]);

        if (implicitTxtExt)
        {
          str += ".txt";
        }

        _mFiles.push_back(str);
      }
    }

    virtual bool getNext(int64_t &aNext) final;

    virtual ~OperandStreamFile() {}

  private:

    OperandStreamFile();

    OperandStreamFile& operator =(OperandStreamFile &);

    OperandStreamFile(OperandStreamFile &);

    bool _openNextFile();

    std::vector<std::string> _mFiles;

    std::unique_ptr<std::fstream>  _mPCurrentFile;
    uint32_t                       _mNextFileIndex;

};
