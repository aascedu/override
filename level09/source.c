#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct s_message {
    char text[140];      // offset 0x00
    char username[40];   // offset 0x8c
    int len;             // offset 0xb4
} t_message;

void secret_backdoor(void)
{
    char input[128];

    fgets(input, 0x80, stdin);
    system(input);
    return;
}

void handle_msg(void)
{
    unsigned char workspace[140];
    uint64_t a, b, c, d, e;
    uint32_t flags;

    a = 0;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
    flags = 0x8c;
    set_username((char *)workspace);
    set_msg((char *)workspace);
    puts(">: Msg sent!");
    return;
}

void set_msg(char *user_struct)
{
    long i;
    char input_buf[1024];
    char *p = input_buf;

    for (i = 0x80; i != 0; i = i - 1) {
        p[0] = '\0';
        p[1] = '\0';
        p[2] = '\0';
        p[3] = '\0';
        p[4] = '\0';
        p[5] = '\0';
        p[6] = '\0';
        p[7] = '\0';
        p = p + 8;
    }

    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets(input_buf, 0x400, stdin);
    strncpy(user_struct, input_buf, (long)*(int *)(user_struct + 0xb4));
    return;
}

void set_username(char *user_struct)
{
    long i;
    char name_buf[140];
    char *p = name_buf;
    int idx;

    for (i = 0x10; i != 0; i = i - 1) {
        p[0] = '\0';
        p[1] = '\0';
        p[2] = '\0';
        p[3] = '\0';
        p[4] = '\0';
        p[5] = '\0';
        p[6] = '\0';
        p[7] = '\0';
        p = p + 8;
    }

    puts(">: Enter your username");
    printf(">>: ");
    fgets(name_buf, 0x80, stdin);

    for (idx = 0; (idx < 0x29 && (name_buf[idx] != '\0')); idx = idx + 1) {
        *(char *)(user_struct + 0x8c + (long)idx) = name_buf[idx];
    }

    printf(">: Welcome, %s", user_struct + 0x8c);
    return;
}

int main(void)
{
    puts(
        "--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n--------------------------------------------"
    );
    handle_msg();
    return 0;
}