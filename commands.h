#ifndef COMMANDS_H
#define COMMANDS_C

#define WHITE 7
#define GREEN 10
#define YELLOW 14
#define RED 12
#define CYAN 11
#define GRAY 8

void welcome();
void printBanner(void);
void setColor(int color);
void message(int color, char message[]);
int runCommand(char command[], char arguments[]);

#endif