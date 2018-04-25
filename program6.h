/*
  Yongda Li
  yxl161830@utdallas.edu
  CS3377.502
*/

#ifndef PROGRAM6_H_
#define PROGRAM6_H_

//Constants
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contents"
#define MAX_RECORD_STRING_LENGTH 25

//Header files
#include <iostream>
#include <fstream>
#include <iomanip>
#include "cdk.h"
#include <sstream>
#include <cstring>
#include <stdint.h>

using namespace std;

//Prototype

class BinaryFileHeader
{
 public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord
{
 public:
  uint8_t strLength;
  char stringBuffer[MAX_RECORD_STRING_LENGTH];
};

/* This method will convert the integer to hexdecimal*/
const char* convertIntToHex(uint32_t n)
{
  stringstream convert;
  convert << setfill('0') << setw(sizeof(uint32_t) * 2) << uppercase << hex << n;
  return convert.str().c_str();
}

#endif /* PROGRAM6_H_*/
