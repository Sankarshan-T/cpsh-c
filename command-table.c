#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "commands.h"
#include "command-table.h"

int commandHelp(
    char arguments[],
    char history[][100],
    int historyCount)
{
    printHelp();
    return 0;
}

int commandPwd(
    char arguments[],
    char history[][100],
    int historyCount)
{
    printWorkingDirectory();
    return 0;
}

int commandLs(
    char arguments[],
    char history[][100],
    int historyCount)
{
    listDirectory();
    return 0;
}

int commandClear(
    char arguments[],
    char history[][100],
    int historyCount)
{
    system("cls");
    return 0;
}

int commandHome(
    char arguments[],
    char history[][100],
    int historyCount)
{
    home();
    return 0;
}

int commandQuit(
    char arguments[],
    char history[][100],
    int historyCount)
{
    message(GREEN, "Quitting CPSH...\n");
    return 1;
}

int commandCd(
    char arguments[],
    char history[][100],
    int historyCount)
{
    if (arguments[0] == '\0')
    {
        error("warning", "Usage: cd <directory>\n");
        return 0;
    }

    changeDirectory(arguments);
    return 0;
}

int commandCat(
    char arguments[],
    char history[][100],
    int historyCount)
{
    if (arguments[0] == '\0')
    {
        error("warning", "Usage: cat <filename>\n");
        return 0;
    }

    readFile(arguments);
    return 0;
}

int commandTouch(
    char arguments[],
    char history[][100],
    int historyCount)
{
    if (arguments[0] == '\0')
    {
        error("warning", "Usage: touch <filename>\n");
        return 0;
    }

    createFile(arguments);
    return 0;
}

int commandEcho(
    char arguments[],
    char history[][100],
    int historyCount)
{
    if (arguments[0] == '\0')
    {
        error("warning", "Usage: echo <text>\n");
        return 0;
    }

    char output[1001];

    snprintf(
        output,
        sizeof(output),
        "%s\n",
        arguments);

    message(GREEN, output);

    return 0;
}

int commandRemove(
    char arguments[],
    char history[][100],
    int historyCount)
{
    if (arguments[0] == '\0')
    {
        error("warning", "Usage: remove <filename>\n");
        return 0;
    }

    removeFile(arguments);
    return 0;
}

int commandCalc(
    char arguments[],
    char history[][100],
    int historyCount)
{
    double a, b;
    char operator;

    if (scanf(arguments, "%lf % c % lf", &a, &operator, &b) != 3)
    {
        error("warning", "Usage: calc <number> <operator> <number>\n");
        return 0;
    }

    double result;

    switch (operator)
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        if (b == 0)
        {
            error("fatal", "Cannot divide by zero!\n");
            return 0;
        }

        result = a / b;
        break;

    default:
        error("warning", "Unknown operator :C\n");
        return 0;
    }

    printf("= %.2f\n", result);

    return 0;
}

int commandAbout(
    char arguments[],
    char history[][100],
    int historyCount)
{
    about();
    return 0;
}

int commandMkdir(
    char arguments[],
    char history[][100],
    int historycCount)
{
    if (arguments[0] == '\0')
    {
        error("warning", "usage: mkdir <name>\n");
        return 0;
    }
    makeDirectory(arguments);
    return 0;
}

int commandRmdir(
    char arguments[],
    char history[][100],
    int historycCount)
{
    if (arguments[0] == '\0')
    {
        error("warning", "usage: rmdir <name>\n");
        return 0;
    }
    removeDirectory(arguments);
    return 0;
}

int commandHistory(
    char arguments[],
    char history[][100],
    int historyCount)
{
    if (historyCount == 0)
    {
        error("warning", "No commands in history yet :D\n");
        return 0;
    }

    for (int i = 0; i < historyCount; i++)
    {
        printf("  %d. %s", i + 1, history[i]);
    }

    return 0;
}

Command commands[] =
    {
        {"help", commandHelp},
        {"pwd", commandPwd},
        {"ls", commandLs},
        {"clear", commandClear},
        {"cls", commandClear},
        {"home", commandHome},
        {"quit", commandQuit},
        {"exit", commandQuit},
        {"cd", commandCd},
        {"cat", commandCat},
        {"touch", commandTouch},
        {"echo", commandEcho},
        {"remove", commandRemove},
        {"calc", commandCalc},
        {"mkdir", commandMkdir},
        {"rmdir", commandRmdir},
        {"about", commandAbout},
        {"history", commandHistory}};

int commandCount = sizeof(commands) / sizeof(commands[0]);