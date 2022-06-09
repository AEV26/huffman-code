#include "string.h"
#include <stdlib.h>
#include <stdio.h>

STR* initString()
{
    STR* str = (STR*)malloc(sizeof(STR));
    str->length = 0;
    str->data = (char*)malloc(str->length * sizeof(char));

    return str;
}

STR* deepCopyRev(STR* str)
{
    STR* new_str = initString();
    for (int i = 0; i < str->length; ++i)
        pushSymb(new_str, str->data[i]);

    return new_str;
}

STR* stringDelete(STR* str)
{
    free(str->data);
    str->length = 0;
    str = NULL;

    return str;
}

STR* getString()
{
    STR* str = initString();

    char chr = getchar();
    while (chr != '\n')
    {
        pushSymb(str, chr);
        chr = getchar();
    }
    pushSymb(str, '\0');

    return str;
}

void pushSymb(STR* str, char symb)
{
    str->length += 1;
    str->data = (char*) realloc(
            str->data,
            sizeof(char) * str->length
            );
    str->data[str->length - 1] = symb;
}

STR* popLastSymb(STR* str)
{
    STR* new_string = initString();
    for (int i = 0; i < str->length - 1; ++i)
        pushSymb(new_string, str->data[i]);

    return new_string;
}

ARR_STR* stringSplit(STR* str, char symb)
{
    int capacity = 1;
    ARR_STR* list_of_words = (ARR_STR*) malloc(sizeof (ARR_STR) * capacity);

    STR* word = initString();
    pushSymb(str, symb);

    for (int i = 0; i < str->length; ++i)
    {
        if (str->data[i] == symb)
        {
            list_of_words[capacity - 1].element = word;
            capacity++;

            list_of_words = (ARR_STR*) realloc(list_of_words, sizeof (ARR_STR) * capacity);;
            word = initString();
            continue;
        }

        pushSymb(word, str->data[i]);
    }

    return list_of_words;
}

int stringCompare(STR* str1, STR* str2)
{
    if (str1->length != str2->length)
        return 0;

    for (int i = 0; i < str1->length; ++i)
        if (str1->data[i] != str2->data[i])
            return 0;

    return 1;
}