#ifndef FILELIBRARY_H_INCLUDED
#define FILELIBRARY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

int numberOfNonEmptyLines(const char * inputFilePath);
void readUniqueLine(const char * inputFilePath, char * inputContent, int stringLength);

#endif // FILELIBRARY_H_INCLUDED
