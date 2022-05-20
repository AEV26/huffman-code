#ifndef HUFFMAN_CODE_NODE_H
#define HUFFMAN_CODE_NODE_H

typedef struct node
{
    unsigned char symb;
    unsigned char isSymb;
    unsigned int freq;
    struct node * left, *right, *next;
} NODE;

NODE * MakeNodeFromNode(const NODE * left, const NODE * right);
void Add2List(NODE** pphead, NODE* node);
NODE * CreateNodeForLetter(int freq, char letter);
NODE * MakeTreeFromList(NODE * head);

#endif //HUFFMAN_CODE_NODE_H
