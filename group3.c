#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void printCentered(char *text, int width) {
    int pad = (width - strlen(text)) / 2;
    for (int i = 0; i < pad; i++) {
        printf(" ");
    }
    printf("%s\n",   text);
}

void generatePassword(int length, int useUpper, int useLower, int useDigit, int useSpecial) {
    char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower[] = "abcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    char special[] = "!@#$%^&*()-_=+[]{}|;:',.<>?/`~";
    char pool[100] = "";
    if (useUpper) strcat(pool, upper);
    if (useLower) strcat(pool, lower);
    if (useDigit) strcat(pool, digits);
    if (useSpecial) strcat(pool, special);

    if (strlen(pool) == 0) {
        printf("                   No character sets selected.\n\n\n");
        return;
    }

    char password[length + 1];
    srand(time(0));
    for (int i = 0; i < length; i++) {
        int idx = rand() % strlen(pool);
        password[i] = pool[idx];
    }
    password[length] = '\0';
    printf("                   Generated Password: %s\n\n\n", password);
}

//enabil
void enableVirtualTerminal() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}


void checkPasswordStrength(const char *password) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    int len = strlen(password);

    for (int i = 0; i < len; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSpecial = 1;
    }

    printf("                   Password Strength: ");
    if (len < 8)
        printf("Weak (too short)\n\n\n");
    else if (hasUpper && hasLower && hasDigit && hasSpecial)
        printf("Strong\n\n\n");
    else if ((hasUpper || hasLower) && hasDigit && hasSpecial)
        printf("Moderate\n\n\n");
    else
        printf("Weak\n\n\n");
}

int main() {

    enableVirtualTerminal();
    int choice;

    printCentered("\33[1;32m                  DDDDDDD     IIIIIII      GGGGG      IIIIIII   TTTTTTTTT       AAA         LLLL        IIIIIII   ZZZZZZZZZ  EEEEEEE\033[0m",120);
    printCentered("\33[1;32m                    DD  DDD     III      GGG            III        TTT        AAA AAA       LLLL          III          ZZZ   EE\033[0m",120);
    printCentered("\33[1;32m                    DD   DDD    III     GGG             III        TTT       AAA   AAA      LLLL          III         ZZZ    EEEEEEE\033[0m",120);
    printCentered("\33[1;32m                    DD   DDD    III     GGG  GGGGG      III        TTT      AAAAAAAAAAA     LLLL          III       ZZZ      EEEEEEE\033[0m",120);
    printCentered("\33[1;32m                    DD  DDD     III      GGG  GG G      III        TTT     AAAAAAAAAAAAA    LLLLLLLLL     III      ZZZ       EE\033[0m",120);
    printCentered("\33[1;32m                  DDDDDDD     IIIIIII      GGGGG G    IIIIIII      TTT    AAA         AAA   LLLLLLLLL   IIIIIII   ZZZZZZZZZ  EEEEEEE\033[0m\n",120);
    while (1) {
        printCentered("Password Utility\n",120);
        printCentered("\33[1;31m###############################################\033[0m",160);
        printCentered("\33[1;31m#                                             #\033[0m",160);
        printCentered("\33[1;31m#           1. Generate Password              #\033[0m",160);
        printCentered("\33[1;31m#           2. Check Password Strength        #\033[0m",160);
        printCentered("\33[1;31m#           3. Exit                           #\033[0m",160);
        printCentered("\33[1;31m#                                             #\033[0m",160);
        printCentered("\33[1;31m###############################################\033[0m",160);
        printf("\n                   Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            int length, upper, lower, digit, special;
            printf("                   Enter password length: ");
            scanf("%d", &length);
            printf("                   Include uppercase letters? (1-Yes, 0-No): ");
            scanf("%d", &upper);
            printf("                   Include lowercase letters? (1-Yes, 0-No): ");
            scanf("%d", &lower);
            printf("                   Include digits? (1-Yes, 0-No): ");
            scanf("%d", &digit);
            printf("                   Include special characters? (1-Yes, 0-No): ");
            scanf("%d", &special);
            printf("\n");
            generatePassword(   length, upper, lower, digit, special);

        } else if (choice == 2) {
            char password[100];
            printf("                   Enter password to check: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = 0;
            checkPasswordStrength(password);

        } else if (choice == 3) {
            printf("\n                   Goodbye!\n\n\n");
            break;

        } else {
            printf("\n                   Invalid choice. Try again.\n\n\n");
        }
    }
    return 0;
}
