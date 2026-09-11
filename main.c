#include <stdio.h>
#include <windows.h>
#include <string.h>

#include "commands.h"

int main(void)
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    char input[1000];

    printBanner();

    while (1)
    {
        printf("cpsh-c$ ");

        fgets(input, sizeof(input), stdin);

        if (runCommand(input) == 1)
        {
            break;
        }
    }
    return 0;
}