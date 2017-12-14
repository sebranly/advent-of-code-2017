#ifndef KNOTHASH_H_INCLUDED
#define KNOTHASH_H_INCLUDED

#include <string.h>

#define SIZE_KNOT_HASH_ARRAY 256
#define SIZE_DENSE_HASH (SIZE_KNOT_HASH_ARRAY / 16)
#define FINAL_KNOT_HASH_STRING_LENGTH (2 * SIZE_DENSE_HASH + 1)
#define HEXADECIMAL_NUMBER_STRING_LENGTH 3 // because max is 255 => ff then we need 3 characters (do not forget the '\0')
#define KNOT_HASH_BEGINNING_OF_ADDITIONAL_SEQUENCE 17
#define KNOT_HASH_END_OF_ADDITIONAL_SEQUENCE -1
#define KNOT_HASH_TYPICAL_NUMBER_OF_ROUNDS 64

typedef struct KnotHashElements KnotHashElements;
struct KnotHashElements
{
    int skipSize;
    int currentIndex;
    int array[SIZE_KNOT_HASH_ARRAY];
    char finalKnotHash[FINAL_KNOT_HASH_STRING_LENGTH];
    char hexadecimalNumber[HEXADECIMAL_NUMBER_STRING_LENGTH];
};

int nextInAdditionalSequence(int current);
int bitXor(int x, int y);
int performXorOn16NumberBlock(const int * array, int startingIndex);
void initializeKnotHashElements(KnotHashElements * elements);
void operateArrayChangesBasedOnNumber(int currentNumber, KnotHashElements * elements);
void determineFinalKnotHashString(const char * initialString, KnotHashElements * knotHashElements);

#endif // KNOTHASH_H_INCLUDED
