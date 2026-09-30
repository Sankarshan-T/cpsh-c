#ifndef COMMAND_TABLE_H
#define COMMAND_TABLE_H

typedef int (*CommandFunction)(
    char arguments[],
    char history[][100],
    int historyCount);

typedef struct
{
    char name[20];
    CommandFunction function;
} Command;

extern Command commands[];

extern int commandCount;

#endif