#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>  // Include for strcmp()

pid_t child;  // Global variable for the child process ID
int status;

// Signal handler for SIGUSR1
void sig_handler_1(int sig) {
    printf("Slutt å mase, din lille sa**n!!\n");
}

int main() {
    // Set up the signal handler for SIGUSR1 in the parent process
    signal(SIGUSR1, sig_handler_1);

    // Fork the process to create a child
    child = fork();

    if (child == 0) {  // Child process
        while (1) {
            char input[50];

            printf("Enter a string: ");
            scanf("%s", input);  // Get user input

            // Check if the input is "quit"
            if (strcmp(input, "quit") == 0) {  // Use strcmp() for string comparison
                exit(0);  // Exit the child process
            } else {
                // Send SIGUSR1 signal to the parent
                kill(getppid(), SIGUSR1);

                // Sleep for 200 milliseconds
                usleep(200000);
            }
        }
    } else {  // Parent process
        // Parent waits for the child to finish
        while (1) {
            wait(&status);  // Wait for signals indefinitely
        }
    }
}
