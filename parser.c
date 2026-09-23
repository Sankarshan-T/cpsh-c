#include <stdio.h>
#include <string.h>

#include "parser.h"

ParsedCommand parseCommand(char input[])
{
    ParsedCommand result;

    result.command[0] = '\0';
    result.arguments[0] = '\0';

    char *space = strchr(input, ' ');

    if (space != NULL)
    {
        size_t commandLength = space - input;

        strncpy(result.command, input, commandLength);
        result.command[commandLength] = '\0';

        strcpy(result.arguments, space + 1);
    }
    else
    {
        strcpy(result.command, input);
    }

    return result;
}