#include <stdio.h>
#include <windows.h>
#include <string.h>

#include "commands.h"
#include "parser.h"

int main(void)
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    char input[1000];
    char history[100][100];
    int historyCount = 0;

    home();

    while (1)
    {
        message(WHITE, "cpsh-c$ ");
        setColor(YELLOW);

        fgets(input, sizeof(input), stdin);

        if (historyCount < 100)
        {
            strcpy(history[historyCount], input);
            historyCount++;
        }

        ParsedCommand parsed = parseCommand(input);

        if (runCommand(parsed.command, parsed.arguments, history, historyCount) == 1)
        {
            break;
        }
    }
    return 0;
}