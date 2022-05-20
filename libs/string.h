#ifndef HUFFMAN_CODE_STRING_H
#define HUFFMAN_CODE_STRING_H

typedef struct String
{
    char* data;
    int length;
} STR;

typedef struct String_Array
{
    STR* element;
} ARR_STR;


STR* get_string();
STR* init_string();
STR* string_delete(STR* str);
STR* push_symb(STR* str, char symb);
int string_compare(STR* str1, STR* str2);
ARR_STR* string_split(STR* str, char symb);

#endif //HUFFMAN_CODE_STRING_H