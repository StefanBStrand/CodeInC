#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>  // Include for strcmp()

pid_t child;
int status;


void sig_handler_1(int sig) {
    printf("Slutt å mase, din lille sa**n!!\n");
}

int main() {

    signal(SIGUSR1, sig_handler_1);

    child = fork();

    if (child == 0) {
        while (1) {
            char input[50];

            printf("Enter a string: ");
            scanf("%s", input);

            if (strcmp(input, "quit") == 0) {
                exit(0);
            } else {
                kill(getppid(), SIGUSR1);
                usleep(200000);
            }
        }
    } else {
        wait(&status);
    }
}
