#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decrypt(char key) {
    // Chaîne à décrypter
    char encrypted[] = "Q}|u`sfg~sf{}|a3";
    int len = 0x11; // longueur de la chaîne
    int i;

    // Décryptage de la chaîne en appliquant le XOR avec la clé
    for (i = 0; i < len; i++) {
        encrypted[i] ^= key;
    }

    // Vérification avec la chaîne "Congratulations!"
    if (strncmp(encrypted, "Congratulations!", len) == 0) {
        system("/bin/sh");
        return 1;
    } else {
        puts("\nInvalid Password");
        return 0;
    }
}

int test(int arg1, int arg2) {
    int diff = arg2 - arg1;

    switch (diff) {
        case 1: case 2: case 3: case 4: case 5:
        case 6: case 7: case 8: case 9:
        case 0x10: case 0x11: case 0x12: case 0x13:
        case 0x14: case 0x15:
            return decrypt((char)diff);
        default:
            return decrypt((char)rand());
    }
}

int main() {
    printf("***********************************\n");
    printf("*\t\tlevel03\t\t**\n");
    printf("***********************************\n");
    printf("Password:");

    int input;
    scanf("%d", &input);

    // Appel à la fonction test
    test(input, 322424845);
    return 0;
}
