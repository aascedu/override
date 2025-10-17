void log_wrapper(FILE *log_file, char *log_prefix, char *log_message) {
    char current_char;
    size_t newline_index;
    unsigned long prefix_len = -1;
    unsigned long total_len = -1;
    char *char_ptr;
    long stack_check;
    byte dummy = 0;
    char log_buffer[264];
    long stack_guard;

    stack_guard = *(long *)(in_FS_OFFSET + 0x28);
    strcpy(log_buffer, log_prefix);

    char_ptr = log_buffer;
    do {
        if (prefix_len == 0) break;
        prefix_len--;
        current_char = *char_ptr;
        char_ptr = char_ptr + (unsigned long)dummy * -2 + 1;
    } while (current_char != '\0');

    char_ptr = log_buffer;
    do {
        if (total_len == 0) break;
        total_len--;
        current_char = *char_ptr;
        char_ptr = char_ptr + (unsigned long)dummy * -2 + 1;
    } while (current_char != '\0');

    snprintf(log_buffer + (~total_len - 1), 0xfe - (~prefix_len - 1), log_message);
    newline_index = strcspn(log_buffer, "\n");
    log_buffer[newline_index] = '\0';
    fprintf(log_file, "LOG: %s\n", log_buffer);

    if (stack_guard != *(long *)(in_FS_OFFSET + 0x28)) {
        __stack_chk_fail();
    }

    return;
}

int main(int argc, char **argv) {
    char current_char;
    int backup_fd;
    int byte_read;
    FILE *log_file;
    FILE *source_file;
    unsigned long path_len = -1;
    char *char_ptr;
    long stack_check;
    byte dummy = 0;
    char write_buffer;
    char backup_path[104];
    long stack_guard;

    stack_guard = *(long *)(in_FS_OFFSET + 0x28);
    write_buffer = -1;

    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
    }

    log_file = fopen("./backups/.log", "w");
    if (log_file == NULL) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }

    log_wrapper(log_file, "Starting back up: ", argv[1]);

    source_file = fopen(argv[1], "r");
    if (source_file == NULL) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
    }

    strncpy(backup_path, "./backups/", 11);

    char_ptr = backup_path;
    do {
        if (path_len == 0) break;
        path_len--;
        current_char = *char_ptr;
        char_ptr = char_ptr + (unsigned long)dummy * -2 + 1;
    } while (current_char != '\0');

    strncat(backup_path, argv[1], 99 - (~path_len - 1));

    backup_fd = open(backup_path, 0xc1, 0x1b0);
    if (backup_fd < 0) {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(1);
    }

    while (1) {
        byte_read = fgetc(source_file);
        write_buffer = (char)byte_read;
        if (write_buffer == -1) break;
        write(backup_fd, &write_buffer, 1);
    }

    log_wrapper(log_file, "Finished back up ", argv[1]);

    fclose(source_file);
    close(backup_fd);

    if (stack_guard != *(long *)(in_FS_OFFSET + 0x28)) {
        __stack_chk_fail();
    }

    return 0;
}
