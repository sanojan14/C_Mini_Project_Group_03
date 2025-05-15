#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Password generator function
void generatePassword(int length, int useUpper, int useLower, int useDigit, int useSpecial) {
    char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower[] = "abcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    char special[] = "!@#$%^&*()";
    char pool[100] = "";
    if (useUpper) strcat(pool, upper);
    if (useLower) strcat(pool, lower);
    if (useDigit) strcat(pool, digits);
    if (useSpecial) strcat(pool, special);

    if (strlen(pool) == 0) {
        printf("No character sets selected.\n");
        return;
    }

    char password[length + 1];
    srand(time(0));
    for (int i = 0; i < length; i++) {
        int idx = rand() % strlen(pool);
        password[i] = pool[idx];
    }
    password[length] = '\0';
    printf("Generated Password: %s\n", password);
}

// Password strength checker function
void checkPasswordStrength(const char *password) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    int len = strlen(password);

    for (int i = 0; i < len; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSpecial = 1;
    }

    printf("Password Strength: ");
    if (len < 8)
        printf("Weak (too short)\n");
    else if (hasUpper && hasLower && hasDigit && hasSpecial)
        printf("Strong\n");
    else if ((hasUpper || hasLower) && hasDigit && hasSpecial)
        printf("Moderate\n");
    else
        printf("Weak\n");
}

int main() {
    int choice;
    while (1) {
        printf("\nPassword Utility\n");
        printf("1. Generate Password\n");
        printf("2. Check Password Strength\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            int length, upper, lower, digit, special;
            printf("Enter password length: ");
            scanf("%d", &length);
            printf("Include uppercase letters? (1-Yes, 0-No): ");
            scanf("%d", &upper);
            printf("Include lowercase letters? (1-Yes, 0-No): ");
            scanf("%d", &lower);
            printf("Include digits? (1-Yes, 0-No): ");
            scanf("%d", &digit);
            printf("Include special characters? (1-Yes, 0-No): ");
            scanf("%d", &special);
            generatePassword(length, upper, lower, digit, special);
        } else if (choice == 2) {
            char password[100];
            printf("Enter password to check: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = 0; // remove newline
            checkPasswordStrength(password);
        } else if (choice == 3) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
