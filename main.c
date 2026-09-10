#include <stdio.h>
#include <windows.h>
#include <string.h>

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

int main(void)
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    char name[50];
    int age;

    printf("What is your name?");

    fgets(name, sizeof(name), stdin);

    name[strcspn(name, "\n")] = '\0';
    printf("Your name is %s\n", name);

    printf("What is your age?");
    scanf("%d", &age);

    printf("You are %d years old.\n", age);
}