#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "commands.h"

void printBanner()
{
    printf(
        "╔█████ ╔██████ ╔█████ ╔██ ╔██    ╔█████\n"
        "║██    ║██  ██ ║██    ║██ ║██    ║██\n"
        "║██    ║██████ ║█████ ║██████┌███║██\n"
        "║██    ║██     ╚═══██ ║██═╗██└──┘║██\n"
        "║█████ ║██     ╔█████ ║██ ║██    ║█████\n"
        "╚════╝ ╚═╝     ╚════╝ ╚═╝ ╚═╝    ╚════╝\n"
        "            C Command Line             \n");
}

int runCommand(char command[], char arguments[])
{
    if (strcmp(command, "quit") == 0)
    {
        printf("Quitting cpsh....\n");
        return 1;
    }

    else if (strcmp(command, "clear") == 0)
    {
        system("cls");
        return 0;
    }

    else if (strcmp(command, "help") == 0)
    {
        printf("Available commands:\n");
        printf("  help - Show available commands\n");
        printf("  clear - Clear the terminal\n");
        printf("  quit - Quit CPSH-C\n");
        return 0;
    }

    else if (strcmp(command, "echo") == 0)
    {
        printf("%s\n", arguments);
        return 0;
    }

    else
    {
        printf("Unknown command: %s\n", command);
        return 0;
    }
}