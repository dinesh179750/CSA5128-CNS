#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
void encrypt(char msg[], int shift) {
    for (int i = 0; msg[i]; i++) {
        if (isalpha(msg[i])) {
            if (isupper(msg[i]))
                msg[i] = ('A' + (msg[i] - 'A' + shift) % 26);
            else
                msg[i] = ('a' + (msg[i] - 'a' + shift) % 26);
        }
    }
}
void decrypt(char msg[], int shift) {
    for (int i = 0; msg[i]; i++) {
        if (isalpha(msg[i])) {
            if (isupper(msg[i]))
                msg[i] = ('A' + (msg[i] - 'A' - shift + 26) % 26);
            else
                msg[i] = ('a' + (msg[i] - 'a' - shift + 26) % 26);
        }
    }
}

int main() {
    char msg[MAX];
    int shift;

    printf("Enter the message: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';

    printf("Enter the shift: ");
    scanf("%d", &shift);
    encrypt(msg, shift);
    printf("Encrypted message: %s\n", msg);
    decrypt(msg, shift);
    printf("Decrypted message: %s\n", msg);

    return 0;
}
