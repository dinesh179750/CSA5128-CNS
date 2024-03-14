#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

// Function to prepare the key matrix
void prepareKeyMatrix(char *key, char keyMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j, k = 0;
    char alphabet[26] = {0};

    // Mark used characters in key
    for (i = 0; i < strlen(key); i++) {
        if (key[i] != ' ') {
            alphabet[toupper(key[i]) - 'A'] = 1;
        }
    }

    // Fill the key matrix with key
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (k < strlen(key)) {
                if (alphabet[toupper(key[k]) - 'A'] == 1) {
                    keyMatrix[i][j] = toupper(key[k]);
                    alphabet[toupper(key[k]) - 'A'] = 0;
                    k++;
                } else {
                    k++;
                    j--;
                }
            } else {
                for (k = 0; k < 26; k++) {
                    if (alphabet[k] == 0) {
                        keyMatrix[i][j] = k + 'A';
                        alphabet[k] = -1;
                        break;
                    }
                }
            }
        }
    }
}

// Function to find position of a character in key matrix
void findPosition(char keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char ch, int *row, int *col) {
    int i, j;

    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a digraph
void encryptDigraph(char keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char *digraph, char *cipher) {
    int row1, col1, row2, col2;
    findPosition(keyMatrix, digraph[0], &row1, &col1);
    findPosition(keyMatrix, digraph[1], &row2, &col2);

    // If characters are in same row, shift columns to the right, wrapping around if necessary
    if (row1 == row2) {
        cipher[0] = keyMatrix[row1][(col1 + 1) % MATRIX_SIZE];
        cipher[1] = keyMatrix[row2][(col2 + 1) % MATRIX_SIZE];
    }
    // If characters are in same column, shift rows down, wrapping around if necessary
    else if (col1 == col2) {
        cipher[0] = keyMatrix[(row1 + 1) % MATRIX_SIZE][col1];
        cipher[1] = keyMatrix[(row2 + 1) % MATRIX_SIZE][col2];
    }
    // If characters form a rectangle, swap their columns
    else {
        cipher[0] = keyMatrix[row1][col2];
        cipher[1] = keyMatrix[row2][col1];
    }
}

int main() {
    char key[100], plaintext[1000], cipher[1000];
    char keyMatrix[MATRIX_SIZE][MATRIX_SIZE];

    // Get the key from user
    printf("Enter the keyword (letters only): ");
    scanf("%s", key);

    // Prepare the key matrix
    prepareKeyMatrix(key, keyMatrix);

    // Get the plaintext from user
    printf("Enter the plaintext to encrypt: ");
    scanf(" %[^\n]", plaintext);

    // Encrypt the plaintext
    int i;
    for (i = 0; i < strlen(plaintext); i += 2) {
        char digraph[2] = {toupper(plaintext[i]), '\0'};
        if (i + 1 < strlen(plaintext)) {
            if (toupper(plaintext[i]) == toupper(plaintext[i + 1])) {
                digraph[1] = 'X';
                i--;
            } else {
                digraph[1] = toupper(plaintext[i + 1]);
            }
        } else {
            digraph[1] = 'X';
        }
        encryptDigraph(keyMatrix, digraph, cipher + i);
    }
    cipher[i] = '\0';

    // Print the encrypted text
    printf("Encrypted text: %s\n", cipher);

    return 0;
}

