#ifndef HUFFMAN_CODE_STRING_H
#define HUFFMAN_CODE_STRING_H

#include "node.h"

typedef struct String
{
    char* data;
    int length;
} STR;

typedef struct String_Array
{
    STR* element;
} ARR_STR;


STR* getString();
STR* initString();
STR* stringDelete(STR* str);
STR* popLastSymb(STR* str);
void pushSymb(STR* str, char symb);
STR* deepCopyRev(STR* str);
int stringCompare(STR* str1, STR* str2);
ARR_STR* stringSplit(STR* str, char symb);

#endif //HUFFMAN_CODE_STRING_H