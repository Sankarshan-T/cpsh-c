#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "commands.h"

#define WHITE 7
#define GREEN 10
#define YELLOW 14
#define RED 12
#define CYAN 11
#define GRAY 8

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

void error(char type[], char text[])
{
    int color;
    char label[20];

    if (strcmp(type, "warning") == 0)
    {
        color = YELLOW;
        strcpy(label, "WARNING !!");
    }
    else if (strcmp(type, "fatal") == 0)
    {
        color = RED;
        strcpy(label, "ERROR :(");
    }
    else
    {
        color = WHITE;
        strcpy(label, "MESSAGE");
    }

    char output[1100];

    snprintf(
        output,
        sizeof(output),
        "[%s] %s",
        label,
        text);

    message(color, output);
}

void printBanner(void)
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

void printHelp(void)
{
    message(GREEN, "Available commands :D\n");

    message(GRAY, "  home - Return to home screen\n");
    message(WHITE, "  help - Show all available commands\n");
    message(CYAN, "  echo <text> - Print text\n");
    message(CYAN, "  touch <filename> - Create a file\n");
    message(CYAN, "  cat <filename> - Display a file\n");
    message(CYAN, "  pwd - Show current directory\n");
    message(CYAN, "  cd <directory> - Change the current directory\n");
    message(CYAN, "  ls - List files and folders\n");
    message(CYAN, "  history - Show previous commands\n");
    message(RED, "  remove <filename> - Remove a file\n");
    message(RED, "  clear/cls - Clear the terminal\n");
    message(RED, "  quit/exit - Exit CPSH-C\n");
}

void home(void)
{
    system("cls");
    printBanner();
    printHelp();
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
        error("fatal", "Couldn't get your current working directory!\n");
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
        error("fatal", "Directory not found!\n");
    }
}

void listDirectory(void)
{
    WIN32_FIND_DATAA fileData;

    HANDLE handle = FindFirstFileA("*", &fileData);

    if (handle == INVALID_HANDLE_VALUE)
    {
        error("fatal", "Couldn't read directory :/\n");
        return;
    }

    do
    {
        if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            message(CYAN, "  [DIR]  ");
            printf("%s\n", fileData.cFileName);
        }
        else
        {
            message(WHITE, "  [FILE] ");
            printf("%s\n", fileData.cFileName);
        }

    } while (FindNextFileA(handle, &fileData));

    FindClose(handle);
}

void createFile(char filename[])
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        error("fatal", "Couldn't create file!\n");
        return;
    }

    fclose(file);

    message(GREEN, "File created! :)\n");
}

void readFile(char filename[])
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        error("fatal", "Couldn't open file!\n");
        return;
    }

    char line[500];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        message(GREEN, line);
    }

    fclose(file);
}

void removeFile(char filename[])
{
    if (remove(filename) == 0)
    {
        message(GREEN, "File removed!\n");
    }
    else
    {
        error("fatal", "Couldn't remove file!\n");
    }
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

    else if (strcmp(command, "exit") == 0)
    {
        message(GREEN, "Quitting CPSH...\n");
        return 1;
    }

    else if (strcmp(command, "clear") == 0)
    {
        system("cls");
        return 0;
    }

    else if (strcmp(command, "cls") == 0)
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
            error("warning", "Usage: cd <directory>\n");
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

    else if (strcmp(command, "cat") == 0)
    {
        if (arguments[0] == '\0')
        {
            error("warning", "Usage: cat <filename>\n");
            return 0;
        }

        readFile(arguments);
        return 0;
    }

    else if (strcmp(command, "history") == 0)
    {
        if (historyCount == 0)
        {
            error("warning", "No commands in history yet!\n");
            return 0;
        }

        for (int i = 0; i < historyCount; i++)
        {
            printf("  %d. %s", i + 1, history[i]);
        }

        return 0;
    }

    else if (strcmp(command, "touch") == 0)
    {
        if (arguments[0] == '\0')
        {
            error("warning", "Usage: touch <filename>\n");
            return 0;
        }

        createFile(arguments);
        return 0;
    }

    else if (strcmp(command, "echo") == 0)
    {
        if (arguments[0] == '\0')
        {
            error("warning", "Usage: echo <text>\n");
            return 0;
        }

        char argsNew[1001];

        snprintf(
            argsNew,
            sizeof(argsNew),
            "%s\n",
            arguments);

        message(GREEN, argsNew);

        return 0;
    }

    else if (strcmp(command, "remove") == 0)
    {
        if (arguments[0] == '\0')
        {
            error("warning", "Usage: remove <filename>\n");
            return 0;
        }

        removeFile(arguments);
        return 0;
    }

    else
    {
        char unknownCommand[1050];

        snprintf(
            unknownCommand,
            sizeof(unknownCommand),
            "Unknown command: %s\n",
            command);

        error("fatal", unknownCommand);

        return 0;
    }
}