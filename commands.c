#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "commands.h"

void printBanner()
{
    setColor(CYAN);
    printf(
        "╔█████ ╔██████ ╔█████ ╔██ ╔██    ╔█████\n"
        "║██    ║██  ██ ║██    ║██ ║██    ║██\n"
        "║██    ║██████ ║█████ ║██████┌███║██\n"
        "║██    ║██     ╚═══██ ║██═╗██└──┘║██\n"
        "║█████ ║██     ╔█████ ║██ ║██    ║█████\n"
        "╚════╝ ╚═╝     ╚════╝ ╚═╝ ╚═╝    ╚════╝\n"
        "            C Command Line             \n");
    setColor(WHITE);
}

void printHelp()
{
    message(GREEN, "Available commands :D\n");
    message(GRAY, "  home - Return to home screen\n");
    message(GRAY, "  help - Show all available commands\n");
    message(GRAY, "  clear - Clear the terminal\n");
    message(GRAY, "  pwd - Show current directory\n");
    message(GRAY, "  quit - Exit CPSH-C\n ");
}

void home(void)
{
    system("cls");
    printBanner();
    printHelp();
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

void printWorkingDirectory(void)
{
    char currentPath[MAX_PATH];

    if (GetCurrentDirectoryA(MAX_PATH, currentPath))
    {
        message(CYAN, "Current path: ");
        message(GREEN, currentPath);
        printf("\n");
    }
    else
    {
        message(RED, "Couldnt get your current working directory :C");
    }
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

    else if (strcmp(command, "home") == 0)
    {
        home();
        return 0;
    }

    else if (strcmp(command, "help") == 0)
    {
        printHelp();
        return 0;
    }

    else if (strcmp(command, "pwd") == 0)
    {
        printWorkingDirectory();
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