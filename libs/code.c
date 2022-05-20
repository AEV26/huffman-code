#include "code.h"
#include <stdlib.h>


CODE* initCode()
{
    CODE* new_code = (CODE*)malloc(sizeof(CODE));
    new_code->sequence = (int*) malloc(sizeof(int));
    new_code->length = 1;

    return new_code;
}

void add2Sequence(CODE* code, int num)
{
    code->length += 1;
    code->sequence = (int*) realloc(code->sequence, sizeof(int) * code->length);
    code->sequence[code->length - 1] = num;
}

void popFromSequence(CODE* code)
{
    int* value = (int*) malloc(sizeof(int) * (code->length - 1));
    for (int i = 0; i < code->length - 1; ++i)
        value[i] = code->sequence[i];

    free(code->sequence);
    code->sequence = value;
}

