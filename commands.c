#include <stdio.h>
#include <string.h>
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

int runCommand(char input[])
{
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "quit") == 0)
    {
        printf("Quitting cpsh....\n");
        return 1;
    }
    else if (strcmp(input, "help") == 0)
    {
        printf("Available commands :) :\n");
        printf("  help - Show available commands\n");
        printf("  quit - Quit CPSH-C\n");
        return 0;
    }
    else
    {
        printf("Unknown command: %s\n", input);
        return 0;
    }
}