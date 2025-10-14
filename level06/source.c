#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <unistd.h>

int auth(char *param_login, unsigned int param_serial)
{
    size_t len;
    unsigned int checksum;
    long ptrace_ret;
    int i;

    len = strcspn(param_login, "\n");
    param_login[len] = '\0';

    len = strnlen(param_login, 0x20);
    if ((int)len < 6) {
        return 1;
    }

    ptrace_ret = ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    if (ptrace_ret == -1) {
        puts("\x1b[32m.---------------------------.");
        puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
        puts("\x1b[32m\'---------------------------\'");
        return 1;
    }

    checksum = ((unsigned int)(unsigned char)param_login[3] ^ 0x1337U) + 0x5eededU;

    for (i = 0; i < (int)len; i++) {
        if ((unsigned char)param_login[i] < ' ') {
            return 1;
        }
        checksum = checksum + (((unsigned int)(unsigned char)param_login[i] ^ checksum) % 0x539U);
    }
	// printf("%u\n", checksum);
    if (param_serial == checksum) {
        return 0;
    } else {
        return 1;
    }
}

int main(void)
{
    char login[32];
    unsigned int serial;
    int auth_result;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");
    if (fgets(login, 0x20, stdin) == NULL) {
        return 1;
    }

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");

    if (scanf("%u", &serial) != 1) {
        puts("Failed to read serial.");
        return 1;
    }

    auth_result = auth(login, serial);
    if (auth_result == 0) {
        puts("Authenticated!");
        system("/bin/sh");
    }

    return auth_result != 0;
}
