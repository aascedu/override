#include <stdio.h>
#include <string.h>

char a_user_name[256];

int verify_user_name(void) {
    const char *correct_username = "dat_wil";
    if (strncmp(a_user_name, correct_username, strlen(correct_username)) == 0) {
        return 0;
    } else {
        return 1;
    }
}

int verify_user_pass(const char *input_password) {
    const char *correct_password = "admin";
    if (strncmp(input_password, correct_password, strlen(correct_password)) == 0) {
        return 0;
    } else {
        return 1;
    }
}

int main(void) {
    char password_input[100] = {0};
    int result;

    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(a_user_name, sizeof(a_user_name), stdin);
    a_user_name[strcspn(a_user_name, "\n")] = 0;

    result = verify_user_name();
    if (result == 0) {
        printf("Enter Password: ");
        fgets(password_input, sizeof(password_input), stdin);
        password_input[strcspn(password_input, "\n")] = 0;

        result = verify_user_pass(password_input);
        if (result == 0) {
            puts("Access granted.\n");
            return 0;
        } else {
            puts("nope, incorrect password...\n");
            return 1;
        }
    } else {
        puts("nope, incorrect username...\n");
        return 1;
    }
}