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
    message(WHITE, "  help - Show all available commands\n");
    message(RED, "  clear - Clear the terminal\n");
    message(CYAN, "  pwd - Show current directory\n");
    message(YELLOW, "  cd - Change the current directory\n");
    message(CYAN, "  ls - List files and folders\n");
    message(CYAN, "  history - Show previous commands\n");
    message(RED, "  quit - Exit CPSH-C\n ");
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

void changeDirectory(char path[])
{
    if (SetCurrentDirectoryA(path))
    {
        message(GREEN, "Directory changed! :D\n");
    }
    else
    {
        message(RED, "Directory not found :(\n");
    }
}

void listDirectory(void)
{
    WIN32_FIND_DATAA fileData;
    HANDLE handle = FindFirstFileA("*", &fileData);

    if (handle == INVALID_HANDLE_VALUE)
    {
        message(RED, "couldn't read directory :/ \n");
        return;
    }

    do
    {
        printf("  %s\n", fileData.cFileName);
    } while (FindNextFileA(handle, &fileData));

    FindClose(handle);
}

int runCommand(
    char command[],
    char arguments[],
    char history[][100],
    int historyCount)
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

    else if (strcmp(command, "cd") == 0)
    {
        if (arguments[0] == '\0')
        {
            message(YELLOW, "Usage: cd <directory>\n");
            return 0;
        }

        changeDirectory(arguments);
        return 0;
    }

    else if (strcmp(command, "ls") == 0)
    {
        listDirectory();
        return 0;
    }

    else if (strcmp(command, "history") == 0)
    {
        if (historyCount == 0)
        {
            message(YELLOW, "no commands in history yet\n");
            return 0;
        }

        for (int i = 0; i < historyCount; i++)
        {
            printf("  %d. %s", i + 1, history[i]);
        }

        return 0;
    }

    else if (strcmp(command, "echo") == 0)
    {
        char argsNew[1001];

        if (arguments[0] == '\0')
        {
            message(YELLOW, "Usage: echo <text>\n");
            return 0;
        }

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