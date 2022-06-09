#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "libs/string.h"
#include "libs/node.h"
#define BIT8 8

STR* codes[256];
void in(NODE* node, STR* seq);
int codesCompare(STR* code);

char file_in[] = "/home/a1k0u/Documents/C/huffman-code/texts/1.bmp";
char file_out[] = "/home/a1k0u/Documents/C/huffman-code/texts/out.txt";
char file_decode[] = "/home/a1k0u/Documents/C/huffman-code/texts/2.bmp";

int main()
{
    int freq[256] = {0};

    printf("[LOG]: Open file...\n");
    long length;
    FILE* fr = fopen(file_in,"rb");
    fseek(fr, 0, SEEK_END);
    length = ftell(fr);
    fseek(fr, 0, SEEK_SET);

    printf("[LOG]: Count freq...\n");
    for (int i = 0; i < length; ++i)
        freq[(unsigned int)fgetc(fr)] += 1;

    printf("[LOG]: Make list...\n");
    NODE *list = NULL;
    for (int i = 0; i < 256; ++i)
        if (freq[i])
            Add2List(&list, CreateNodeForLetter(freq[i], (char) i));

    printf("[LOG]: Create tree...\n");
    NODE *tree = MakeTreeFromList(list);

    printf("[LOG]: Form codes...\n");
    STR* sequence = initString();
    in(tree, sequence);

    printf("[LOG]: Code file...\n");
    STR* codedSting = initString();
    fseek(fr, 0, SEEK_SET);
    for (int i = 0; i < length; ++i)
    {
        STR* code = codes[(unsigned int) fgetc(fr)];
        for (int j = 0; j < code->length; ++j)
            pushSymb(codedSting, code->data[j]);
    }

    printf("[LOG]: Form meta data...\n");
    int count = codedSting->length / BIT8;
    int tail = (8 - codedSting->length % BIT8) % 8;
    for (int i = 0; i < tail; ++i)
        pushSymb(codedSting, '0');
    int len = count + 1;

    printf("[LOG]: Put code to bits...\n");
    BIT2CHAR symb;
    char * res = (char*)malloc(len * sizeof(char));
    for (int i = 0; i < len; ++i)
    {
        symb.mbit.b1 = codedSting->data[i*BIT8 + 0];
        symb.mbit.b2 = codedSting->data[i*BIT8 + 1];
        symb.mbit.b3 = codedSting->data[i*BIT8 + 2];
        symb.mbit.b4 = codedSting->data[i*BIT8 + 3];
        symb.mbit.b5 = codedSting->data[i*BIT8 + 4];
        symb.mbit.b6 = codedSting->data[i*BIT8 + 5];
        symb.mbit.b7 = codedSting->data[i*BIT8 + 6];
        symb.mbit.b8 = codedSting->data[i*BIT8 + 7];
        res[i] = symb.symb;
    }
    fclose(fr);

    printf("[LOG]: Write result...\n");
    FILE* fout = fopen(file_out,"wb");
    fwrite(res, sizeof(res[0]), len, fout);
    fclose(fout);

    printf("[LOG]: Decode file...\n");
    FILE* decodeFile = fopen(file_out,"rb");
    fseek(decodeFile, 0, SEEK_END);
    length = ftell(decodeFile);
    fseek(decodeFile, 0, SEEK_SET);

    char* information = (char*)malloc(sizeof(char) * length);
    fread(information, sizeof(char), length, decodeFile);

    printf("[LOG]: Uncompress...\n");
    char str[9] = { 0 };
    STR* decodeString = initString();
    for (int j = 0; j < length; ++j)
    {
        char c = information[j];
        for (int i = 0; i < 8; i++)
        {
            str[i] = ((c >> (i)) & 1) ? '1' : '0';
            pushSymb(decodeString, str[i]);
        }
    }

    printf("[LOG]: Output decoded result...\n");
    FILE* resultDecode = fopen(file_decode, "w");
    STR* current = initString();
    STR* decodedResult = initString();
    for (int i = 0; i < decodeString->length - tail; ++i)
    {
        pushSymb(current, decodeString->data[i]);
        int find_code = codesCompare(current);
        if (find_code)
        {
            pushSymb(decodedResult, (char) (find_code - 1));
            char a = (char) (find_code - 1);
            fwrite(&a, sizeof(a), 1, resultDecode);
            current = initString();
        }
    }

    fclose(resultDecode);
    fclose(decodeFile);

    return 0;
}

int codesCompare(STR* code)
{
    for (int j = 0; j < 256; ++j)
        if (codes[j] && stringCompare(code, codes[j]))
            return j + 1;
    return 0;
}

void in(NODE* node, STR* seq)
{
    if (node)
    {
        if (node->isSymb)
            codes[node->symb] = deepCopyRev(seq);

        if (node->left)
        {
            STR* a = deepCopyRev(seq);
            pushSymb(a, '0');
            in(node->left, a);
        }

        if (node->right)
        {
            STR* b = deepCopyRev(seq);
            pushSymb(b, '1');
            in(node->right, b);
        }
    }
}
