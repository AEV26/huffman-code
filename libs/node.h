#ifndef HUFFMAN_CODE_NODE_H
#define HUFFMAN_CODE_NODE_H

typedef struct node {
    unsigned char symb;
    unsigned char isSymb;
    unsigned int freq;
    struct node * left, *right, *next;
}NODE;

typedef union bit2char {
    char symb;
    struct bit {
        unsigned b1 : 1;
        unsigned b2 : 1;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
        unsigned b7 : 1;
        unsigned b8 : 1;
    } mbit;
} BIT2CHAR;

NODE * MakeNodeFromNode(const NODE * left, const NODE * right);
void Add2List(NODE** pphead, NODE* node);
NODE * CreateNodeForLetter(int freq, char letter);
NODE * MakeTreeFromList(NODE * head);

#endif //HUFFMAN_CODE_NODE_H
