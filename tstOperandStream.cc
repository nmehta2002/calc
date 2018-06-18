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

  const char *strs[] = {"1.0", "2.2"};

  OperandStreamString opStreamString(strs, 2);
  OperandStream& opStream = opStreamString;

  std::vector<double> actualResult;

  double item;

  while(opStream.getNext(item))
  {
    actualResult.push_back(item);
  }

  std::vector<double> expectedResult {1.0, 2.2};

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
      file<<2.0<<" "<<4.0<<std::endl;
      file<<8.0;
    });

  const char *strs[] = {"input_complex"};

  OperandStreamFile opStreamFile(strs, 1);

  OperandStream& opStream = opStreamFile;

  std::vector<double> actualResult;

  double item;

  while(opStream.getNext(item))
  {
    actualResult.push_back(item);
  }

  std::vector<double> expectedResult {2.0, 4.0, 8.0};

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
      file<<2.0<<" "<<4.0<<std::endl;
      file<<8.0;
    });

  setupFile(
    "input2.txt",
    [](std::ofstream& file)
    {
      file<<4.0<<std::endl;
      file<<8.0;
    });

  setupFile(
    "input3.txt",
    [](std::ofstream& file)
    { });

  setupFile(
    "input4.txt",
    [](std::ofstream& file)
    {
      file<<10.0<<std::endl;
    });


  const char *strs[] = {"input1", "input2", "input3", "input4"};

  OperandStreamFile opStreamFile(strs, 4);

  OperandStream& opStream = opStreamFile;

  std::vector<double> actualResult;

  double item;

  while(opStream.getNext(item))
  {
    actualResult.push_back(item);
  }

  std::vector<double> expectedResult {2.0, 4.0, 8.0, 4.0, 8.0, 10.0};

  assert(expectedResult == actualResult);

  std::cout<<"success."<<std::endl;
}


void testOpStreamFileNegative()
{
  {
    std::cout<<"Testing testOpStreamFileNegativeNonExistentFile...";

    // Setup multiple files, each with some values and an empty file,
    // somewhere in middle.

    const char *strs[] = {"non-existent-file"};

    OperandStreamFile opStreamFile(strs, 1);

    OperandStream& opStream = opStreamFile;

    double item;
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

    // Setup multiple files, each with some values and an empty file,
    // somewhere in middle.

    const char *strs[] = {"nan_input"};

    OperandStreamFile opStreamFile(strs, 1);

    OperandStream& opStream = opStreamFile;

    double item;
    try
    {
      opStream.getNext(item);
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
