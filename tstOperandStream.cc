#include <cassert>
#include <iostream>
#include "OperandStreamString.h"
#include <fstream>
#include "OperandStreamFile.h"
#include <functional>

using std::ios;

void testOpStreamString()
{
  std::cout<<"Testing OperandStreamString...";

  const char *strs[] = {"1", "2", "-3"};

  OperandStreamString opStreamString(strs, 3);
  OperandStream& opStream = opStreamString;

  std::vector<int64_t> actualResult;

  int64_t item;

  while(opStream.getNext(item))
  {
    actualResult.push_back(item);
  }

  std::vector<int64_t> expectedResult {1, 2, -3};

  assert(expectedResult == actualResult);

  std::cout<<"success."<<std::endl;

}

void setupFile(std::string aName, std::function<void(std::ofstream&)> aPopulateFn)
{
  std::ofstream file;

  file.open (aName, ios::out | ios::trunc);
  aPopulateFn(file);
  file.close();
}

void testOpStreamFile()
{
  std::cout<<"Testing OperandStreamFile...";

  /**
   * Setup a file with multiple lines and multiple values in the same line.
   */

  setupFile(
    "input_complex.txt",
    [](std::ofstream& file)
    {
      file<<2<<" "<<4<<std::endl;
      file<<8;
    });

  const char *strs[] = {"input_complex"};

  OperandStreamFile opStreamFile(strs, 1);

  OperandStream& opStream = opStreamFile;

  std::vector<int64_t> actualResult;

  int64_t item;

  while(opStream.getNext(item))
  {
    actualResult.push_back(item);
  }

  std::vector<int64_t> expectedResult {2, 4, 8};

  assert(expectedResult == actualResult);

  std::cout<<"success."<<std::endl;
}

void testOpStreamFileMultipleFiles()
{
  std::cout<<"Testing testOpStreamFileMultipleFiles...";

  // Setup multiple files, each with some values and an empty file,
  // somewhere in middle.

  setupFile(
    "input1.txt",
    [](std::ofstream& file)
    {
      file<<2<<" "<<4<<std::endl;
      file<<8;
    });

  setupFile(
    "input2.txt",
    [](std::ofstream& file)
    {
      file<<4<<std::endl;
      file<<8;
    });

  setupFile(
    "input3.txt",
    [](std::ofstream& file)
    { });

  setupFile(
    "input4.txt",
    [](std::ofstream& file)
    {
      file<<10<<std::endl;
    });


  const char *strs[] = {"input1", "input2", "input3", "input4"};

  OperandStreamFile opStreamFile(strs, 4);

  OperandStream& opStream = opStreamFile;

  std::vector<int64_t> actualResult;

  int64_t item;

  while(opStream.getNext(item))
  {
    actualResult.push_back(item);
  }

  std::vector<int64_t> expectedResult {2, 4, 8, 4, 8, 10};

  assert(expectedResult == actualResult);

  std::cout<<"success."<<std::endl;
}


void testOpStreamFileNegative()
{
  {
    std::cout<<"Testing testOpStreamFileNegativeNonExistentFile...";

    const char *strs[] = {"non-existent-file"};

    OperandStreamFile opStreamFile(strs, 1);

    OperandStream& opStream = opStreamFile;

    int64_t item;
    try
    {
      opStream.getNext(item);
      assert(false);
    }catch(std::invalid_argument& inv)
    {
      assert(true);
      std::cout<<"success."<<std::endl;
    }
  }
  {
    std::cout<<"Testing testOpStreamFileNegativeNaN...";

    setupFile(
      "nan_input.txt",
      [](std::ofstream& file)
      {
        file<<'A'<<std::endl;
      });

    const char *strs[] = {"nan_input"};

    OperandStreamFile opStreamFile(strs, 1);

    OperandStream& opStream = opStreamFile;

    int64_t item;
    try
    {
      opStream.getNext(item);
      assert(false);
    }catch(std::invalid_argument& inv)
    {
      assert(true);
      std::cout<<"success."<<std::endl;
    }
  }
}

int main()
{
  testOpStreamString();
  testOpStreamFile();
  testOpStreamFileMultipleFiles();
  testOpStreamFileNegative();
}
