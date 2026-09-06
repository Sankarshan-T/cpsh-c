#include <stdio.h>
#include <windows.h>

void printBanner() {
    printf(
        "╔█████ ╔██████ ╔█████ ╔██ ╔██    ╔█████\n"
        "║██    ║██  ██ ║██    ║██ ║██    ║██\n"
        "║██    ║██████ ║█████ ║██████┌███║██\n"
        "║██    ║██     ╚═══██ ║██═╗██└──┘║██\n"  
        "║█████ ║██     ╔█████ ║██ ║██    ║█████\n"
        "╚════╝ ╚═╝     ╚════╝ ╚═╝ ╚═╝    ╚════╝\n"
        "            C Command Line             \n"
    );
}

int main(void) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    char name[] = "CPSH";
    char learning[] = "C programming";
    int version = 1;
    char language = 'C';

    printf("String: %s\n", name);
    printf("Version: %d\n", version);
    printf("language: %c\n", language);
    printf("Learning: %s\n", learning);
    
    return 0;
}