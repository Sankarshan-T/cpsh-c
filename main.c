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

    char answer;

    while (1)
    {
        printf("Welcome to cpsh! Do you want to continue? :D (y/n)");
        scanf(" %c", &answer);
        if (answer == 'y')
        {
            printf("Oki! Continuing\n");
            continue;
        }
        else if (answer == 'n')
        {
            printf("Quitting.. :(\n");
            break;
        }
        else
        {
            printf("Enter y or n!\n");
            continue;
        }
    }
}