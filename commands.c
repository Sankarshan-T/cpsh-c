#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "commands.h"
#include "command-table.h"

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
    message(GREEN, "C command line :D\n");
    message(WHITE, "-----------------------------\n");
    message(GRAY, "  home - Return to home screen\n");
    message(WHITE, "  help - Show all available commands\n");
    message(WHITE, "  about - about the shell\n");
    message(CYAN, "  echo <text> - Print text\n");
    message(CYAN, "  touch <filename> - Create a file\n");
    message(CYAN, "  cat <filename> - Display a file\n");
    message(CYAN, "  pwd - Show current directory\n");
    message(CYAN, "  cd <directory> - Change the current directory\n");
    message(CYAN, "  ls - List files and folders\n");
    message(CYAN, "  history - Show previous commands\n");
    message(CYAN, "  calc <a> <operator> <b> - Calculate\n");
    message(CYAN, "  mkdir <directory> - Create a directory\n");
    message(RED, "  remove <filename> - Remove a file\n");
    message(RED, "  clear/cls - Clear the terminal\n");
    message(RED, "  quit/exit - Exit CPSH-C\n");
    message(WHITE, "-----------------------------\n");
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

void removeDirectory(char dirName[])
{
    if (RemoveDirectoryA(dirName))
    {
        message(GREEN, "directory removed!\n");
    }
    else
    {
        error("fatal", "Couldn't remove directory :/ \n");
    }
}

void makeDirectory(char name[])
{
    if (CreateDirectoryA(name, NULL))
    {
        message(GREEN, "Directory created! :D\n");
    }
    else
    {
        DWORD errorCode = GetLastError();

        char output[200];

        snprintf(
            output,
            sizeof(output),
            "couldnt create directory :C (Error code: %lu)\n",
            errorCode);

        error("fatal", output);
    }
}

void about()
{
    message(GREEN, "CPSH-C\n");
    message(CYAN, "Creator: coolcream\n");
    message(CYAN, "Version: 1.0.0\n");
    message(YELLOW, "OS: windows (obviously)\n");
    message(YELLOW, "Compiler: gcc\n");
}

int runCommand(
    char command[],
    char arguments[],
    char history[][100],
    int historyCount)
{
    for (int i = 0; i < commandCount; i++)
    {
        if (strcmp(command, commands[i].name) == 0)
        {
            return commands[i].function(
                arguments,
                history,
                historyCount);
        }
    }

    char unknownCommand[1050];

    snprintf(
        unknownCommand,
        sizeof(unknownCommand),
        "Unknown command: %s\n",
        command);

    error("fatal", unknownCommand);

    return 0;
}