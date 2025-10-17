uint32_t store_number(uint32_t *data_base)
{
    uint32_t value;
    uint32_t index;
    uint32_t ret;

    printf(" Number: ");
    value = get_unum();

    printf(" Index: ");
    index = get_unum();

    if ((index % 3 == 0) || ((value >> 24) == 0xb7)) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        ret = 1;
    } else {
        data_base[index] = value;
        ret = 0;
    }

    return ret;
}

uint32_t read_number(uint32_t *data_base)
{
    int index;

    printf(" Index: ");
    index = (int)get_unum();

    printf(" Number at data[%u] is %u\n", (unsigned)index, data_base[index]);

    return 0;
}

int main(int argc, char **argv, char **envp)
{
    uint32_t data_storage[100];
    int last_status = 0;
    unsigned char cmd_buf[20];
    int i;

    for (i = 0; i < 100; ++i) {
        data_storage[i] = 0;
    }

    if (argv != NULL) {
        for (char **a = argv; *a != NULL; ++a) {
            size_t len = 0;
            while ((*a)[len] != '\0') ++len;
            memset(*a, 0, len);
        }
    }

    if (envp != NULL) {
        for (char **e = envp; *e != NULL; ++e) {
            size_t len = 0;
            while ((*e)[len] != '\0') ++len;
            memset(*e, 0, len);
        }
    }

    puts(
"----------------------------------------------------\n"
"  Welcome to wil's crappy number storage service!   \n"
"----------------------------------------------------\n"
" Commands:                                          \n"
"    store - store a number into the data storage    \n"
"    read  - read a number from the data storage     \n"
"    quit  - exit the program                        \n"
"----------------------------------------------------\n"
"   wil has reserved some storage :>                 \n"
"----------------------------------------------------\n"
    );

    for (;;) {
        printf("Input command: ");

        last_status = 1;
        if (fgets((char *)cmd_buf, sizeof(cmd_buf), stdin) == NULL) {
            break;
        }

        size_t cmdlen = 0;
        while (cmdlen < sizeof(cmd_buf) && cmd_buf[cmdlen] != 0) {
            ++cmdlen;
        }

        {
            char *p = (char *)&last_status;
            p[cmdlen + 2] = 0;
        }

        if (strncmp((char *)cmd_buf, "store", 5) == 0) {
            last_status = store_number(data_storage);
        } else if (strncmp((char *)cmd_buf, "read", 4) == 0) {
            last_status = read_number(data_storage);
        } else if (strncmp((char *)cmd_buf, "quit", 4) == 0) {
            return 0;
        }

        if (last_status == 0) {
            printf(" Completed %s command successfully\n", cmd_buf);
        } else {
            printf(" Failed to do %s command\n", cmd_buf);
        }

        memset(cmd_buf, 0, sizeof(cmd_buf));
    }

    return 0;
}