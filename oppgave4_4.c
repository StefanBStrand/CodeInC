#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    pid_t child = fork();

    if (child == 0) {
        char *args[] = {"ping", "vg.no", NULL};

        printf("Child process: Replacing myself with ping vg.no.. Good bye!\n");

        execvp(args[0], args);

        perror("execvp failed");
        return 1;

    } else if (child > 0) {
        printf("Sleeping for 5 seconds\n");
        sleep(5);

        printf("Parent is now terminating child process (PID %d)\n", child);
        kill(child, SIGINT);

        wait(NULL);

        printf("Parent process: Hasta la vista - child is terminated.\n");

    } else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}


// Forskjell mellom SIGKILL og SIGINT i termineringsprosess: etter å ha kjørt koden med SIGINT printes
// statistikk om selve pingen ut, programmet får tid til å avslutte pent.
// Med SIGKILL skjer ikke dette, det er en mye mer abrupt termingering av prosessen. Her printes ingen statistikk ut.