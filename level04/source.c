#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
    pid_t child_pid;
    int wait_status;
    long traced_value;
    char buffer[128];

    child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        prctl(1, 1);
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        puts("Give me some shellcode, k");
        gets(buffer);
        return 0;
    } else {
        for (;;) {
            wait(&wait_status);
            if (WIFEXITED(wait_status) || WIFSIGNALED(wait_status)) {
                puts("child is exiting...");
                return 0;
            }
            traced_value = ptrace(PTRACE_PEEKUSER, child_pid, (void *)0x2c, NULL);
            if (traced_value == 11) {
                puts("no exec() for you");
                kill(child_pid, SIGKILL);
                return 0;
            }
        }
    }

    return 0;
}