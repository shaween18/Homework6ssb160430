#ifndef _MYPROJ_6_
#define _MYPROJ_6_
/*                                                                             
 * CS3377                                                                       
 * myproject.h                                                                  
 *Shireen Bahadur                                                               
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string>
#include <inttypes.h>
#include "cdk.h"

using namespace std;

class BinaryFileHeader
{
 public:
  uint32_t magicNumber; /* Should be 0xFEEDFACE */
  uint32_t versionNumber;
  uint64_t numRecords;
};

/*
 * Records in the file have a fixed length buffer
 * that will hold a C-Style string. This is the
 * size of the fixed length buffer.
 */
const int maxRecordStringLength = 25;
class BinaryFileRecord
{
 public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

#endif /* _MYPROJ_6_ */
