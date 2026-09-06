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

    int number = 42;
    float decimal = 4.5;
    char letter = 'C';
    char name[] = "CPSH";

    printf("Number: %d\n", number);
    printf("Decimal: %f\n", decimal);
    printf("Character: %c\n", letter);
    printf("String: %s\n", name);

    return 0;
}