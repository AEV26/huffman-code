#include <stdio.h>
#include "libs/string.h"
#include "libs/node.h"

STR commands[3][6] = {
        {"exit", 4},
        {"comp", 4},
        {"decomp", 6}
    };

int readFromFile(STR* path, int* freq);

int main()
{
    STR* command = init_string();
    command = get_string();
    do
    {
        if (!command->length)
            printf("\tLOG: Enter your command!\n");
        else
        {
            ARR_STR *command_and_options = string_split(command, ' ');
            if (string_compare(command_and_options[0].element, commands[1]))
            {
                int freq[256] = {0};
                if (readFromFile(command_and_options[1].element, freq))
                    printf("\tLOG: The process of reading file was successful!\n");
                else
                {
                    printf("\tLOG: File wasn't open!\n");
                    command = get_string();
                    continue;
                }

                printf(
                        "\tLOG: you've input: '%s' with option '%s'\n",
                        command_and_options[0].element->data, command_and_options[1].element->data);

                NODE *list = NULL;
                for (int i = 0; i < 256; ++i)
                     if (freq[i])
                         Add2List(&list, CreateNodeForLetter(freq[i], (char) i));

                NODE *tree = MakeTreeFromList(list);
                printf("\n");
            }

            else if (string_compare(command_and_options[0].element, commands[2]))
            {
                printf(
                        "\tLOG: you've input: '%s' with option '%s'\n",
                        command_and_options[0].element->data, command_and_options[1].element->data);
            }

            else
            {
                printf(
                        "\tLOG: your command('%s') doesn't exist!\n",
                        command_and_options[0].element->data);
            }
        }
        command = get_string();
    } while (!string_compare(command, commands[0]));

    return 0;
}

int readFromFile(STR* path, int* freq)
{
    long length;
    FILE* fr = fopen(path->data, "rb");

    if (!fr)
        return 0;

    fseek(fr, 0, SEEK_END);
    length = ftell(fr);
    fseek(fr, 0, SEEK_SET);

    for (int i = 0; i < length; ++i)
        freq[(unsigned int)fgetc(fr)] += 1;
    fclose(fr);

    return 1;
}
