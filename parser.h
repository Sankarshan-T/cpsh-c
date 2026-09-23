#ifndef PARSER_H
#define PARSER_H

typedef struct
{
    char command[50];
    char arguments[1000];
} ParsedCommand;

ParsedCommand parseCommand(char input[]);

#endif
