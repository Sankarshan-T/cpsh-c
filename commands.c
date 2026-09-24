#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

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

void setColor(int color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color);
}

void message(int color, char message[])
{
    setColor(color);
    printf("%s", message);
    setColor(WHITE);
}

int runCommand(char command[], char arguments[])
{
    if (strcmp(command, "quit") == 0)
    {
        message(GREEN, "Quitting CPSH...\n");
        return 1;
    }

    else if (strcmp(command, "clear") == 0)
    {
        system("cls");
        return 0;
    }

    else if (strcmp(command, "help") == 0)
    {
        message(GREEN, "Available commands\n");
        message(CYAN, "  help - Show available commands\n");
        message(CYAN, "  clear - Clear the terminal\n");
        message(CYAN, "  quit - quir CPSH-C\n ");

        return 0;
    }

    else if (strcmp(command, "echo") == 0)
    {
        char argsNew[1001];
        snprintf(argsNew, sizeof(argsNew), "%s\n", arguments);
        message(GREEN, argsNew);
        return 0;
    }

    else
    {
        char unknownCommand[1050];
        snprintf(unknownCommand, sizeof(unknownCommand), "Unknown command: %s\n", command);
        message(RED, unknownCommand);
        return 0;
    }
}