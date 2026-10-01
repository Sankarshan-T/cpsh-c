#ifndef COMMANDS_H
#define COMMANDS_H

#define WHITE 7
#define GREEN 10
#define YELLOW 14
#define RED 12
#define CYAN 11
#define GRAY 8

void setColor(int color);
void message(int color, char message[]);
void error(char type[], char text[]);

void printBanner(void);
void printHelp(void);
void home(void);

void printWorkingDirectory(void);
void changeDirectory(char path[]);
void listDirectory(void);
void createFile(char filename[]);
void readFile(char filename[]);
void removeFile(char filename[]);
void makeDirectory(char name[]);
void about();

int runCommand(
    char command[],
    char arguments[],
    char history[][100],
    int historyCount);

#endif