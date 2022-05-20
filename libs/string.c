#include "string.h"
#include <stdlib.h>
#include <stdio.h>

STR* init_string()
{
    STR* str = (STR*)malloc(sizeof(STR));
    str->data = (char*)malloc(sizeof(char));
    str->length = 0;

    return str;
}

STR* string_delete(STR* str)
{
    free(str->data);
    str->length = 0;
    str = NULL;

    return str;
}

STR* get_string()
{
    STR* str = init_string();

    char chr = getchar();
    while (chr != '\n')
    {
        str = push_symb(str, chr);
        chr = getchar();
    }
    str = push_symb(str, '\0');

    return str;
}

STR* push_symb(STR* str, char symb)
{
    str->length += 1;
    str->data = (char*) realloc(
            str->data,
            sizeof(char) * str->length
            );
    str->data[str->length - 1] = symb;

    return str;
}

ARR_STR* string_split(STR* str, char symb)
{
    int capacity = 1;
    ARR_STR* list_of_words = (ARR_STR*) malloc(sizeof (ARR_STR) * capacity);

    STR* word = init_string();
    str = push_symb(str, symb);

    for (int i = 0; i < str->length; ++i)
    {
        if (str->data[i] == symb)
        {
            list_of_words[capacity - 1].element = word;
            capacity++;

            list_of_words = (ARR_STR*) realloc(list_of_words, sizeof (ARR_STR) * capacity);;
            word = init_string();
            continue;
        }

        word = push_symb(word, str->data[i]);
    }

    return list_of_words;
}

int string_compare(STR* str1, STR* str2)
{
    if (str1->length != str2->length)
        return 0;

    for (int i = 0; i < str1->length; ++i)
        if (str1->data[i] != str2->data[i])
            return 0;

    return 1;
}