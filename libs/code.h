#ifndef HUFFMAN_CODE_CODE_H
#define HUFFMAN_CODE_CODE_H


typedef struct Code
{
    int* sequence;
    int length;
} CODE;


CODE* initCode();
void add2Sequence(CODE* code, int num);
void popFromSequence(CODE* code);

#endif //HUFFMAN_CODE_CODE_H
