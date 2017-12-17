#ifndef FILELIBRARY_H_INCLUDED
#define FILELIBRARY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int numberOfNonEmptyLines(const char * inputFilePath);
void readUniqueLine(const char * inputFilePath, char * inputContent, int stringLength);
int readUniqueNumber(const char * inputFilePath);

#endif // FILELIBRARY_H_INCLUDED
