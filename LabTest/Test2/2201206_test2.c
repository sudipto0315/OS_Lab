#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <setjmp.h>

jmp_buf buf;

void alarm_handler(int signum) {
    longjmp(buf, 2);
}

int is_prime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return n > 1;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <x> <y> <z>\n", argv[0]);
        exit(1);
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    int z = atoi(argv[3]);

    int jmpval = setjmp(buf);
    if (jmpval == 0) {
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork failed\n");
            exit(1);
        } else if (pid == 0) {
            signal(SIGALRM, alarm_handler);
            alarm(z);
            for (int i = x; i <= y; i++) {
                if (is_prime(i)) {
                    printf("%d\n", i);
                }
            }
            exit(0);
        }
        wait(NULL);
        longjmp(buf, 1);
    } else if (jmpval == 1) {
        printf("All the prime numbers printed\n");
    } else if (jmpval == 2) {
        printf("Calculation is taking too much time\n");
    }
    return 0;
}
