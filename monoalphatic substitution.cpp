#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
void monoalphabeticSubstitution(char *plaintext, char *ciphertext, char *message) {
    int i;
    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            
            char base = isupper(message[i]) ? 'A' : 'a';
            
            message[i] = isupper(message[i]) ? ciphertext[message[i] - 'A'] : tolower(ciphertext[message[i] - 'a']);
        }
    }
}

int main() {
    char plaintext[ALPHABET_SIZE + 1];  
    char ciphertext[ALPHABET_SIZE + 1]; 
    char message[1000];                

    printf("Enter the plaintext alphabet (all 26 letters without spaces): ");
    scanf("%s", plaintext);

    printf("Enter the ciphertext alphabet (all 26 letters without spaces): ");
    scanf("%s", ciphertext);

    if (strlen(plaintext) != ALPHABET_SIZE || strlen(ciphertext) != ALPHABET_SIZE) {
        printf("Alphabet strings must contain exactly 26 characters.\n");
        return 1;
    }

    while (1) {
        printf("\nEnter a message to encrypt (press q to quit): ");
        scanf(" %[^\n]", message);

        if (message[0] == 'q' && message[1] == '\0') {
            break;
        }

        monoalphabeticSubstitution(plaintext, ciphertext, message);
        printf("Encrypted message: %s\n", message);
    }

    return 0;
}

