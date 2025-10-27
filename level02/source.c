#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv, char** envp)
{
    char password[42] = {0};
    char input_password[64] = {0};
    char username[100] = {0};

    FILE* fp = fopen("/home/users/level03/.pass", "r");
    if (!fp) {
        fwrite("ERROR: failed to open password file\n", 1, 0x24, stderr);
        exit(1);
    }

    if (fread(password, 1, 0x29, fp) != 0x29) {
        fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
        exit(1);
    }
    fclose(fp);

    // Remove newline from password
    password[strcspn(password, "\n")] = 0;

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");

    printf("--[ Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("--[ Password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = 0;

    puts("*****************************************");

    if (!strncmp(password, input_password, 0x29)) {
        printf("Greetings, %s!\n", username);
        system("/bin/sh");
        return 0;
    }

    printf("%s does not have access!\n", username);
    exit(1);
}
