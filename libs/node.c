#include "node.h"
#include <stdlib.h>

NODE* MakeNodeFromNode(const NODE * left, const NODE * right)
{
    NODE * res = (NODE*)malloc(sizeof(NODE));
    res->freq = left->freq + right->freq;
    res->isSymb = 0;
    res->symb = 0;
    res->left = left;
    res->right = right;
    res->next = 0;
    return res;
}

void Add2List(NODE** pphead, NODE* node)
{
    while (*pphead)
    {
        if ((*pphead)->freq > node->freq)
            break;
        pphead = &((*pphead)->next);
    }
    NODE* pnew;
    pnew = node;

    pnew->next = *pphead;
    *pphead = pnew;
}

NODE * CreateNodeForLetter(int freq, char letter)
{
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    new_node->freq = freq;
    new_node->symb = letter;
    new_node->isSymb = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->next = 0;
    return new_node;
}

NODE * MakeTreeFromList(NODE * head)
{
    while (head && head->next)
    {
        NODE * left = head;
        NODE * right = head->next;
        Add2List(&(head->next->next), MakeNodeFromNode(left, right));
        head = head->next->next;
    }
    return head;
}
