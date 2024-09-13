#include <stdio.h>
#include <stdlib.h>

// First, defining the struct process:

struct process {
    int number;
    char status;
    float start_time;
    float CPU_time;
};

// Now for the function itself:
struct process *kopier(struct process p) {
    //Now, to allocate memory for the new process struct.
    struct process *new_process = (struct process *) malloc(sizeof(struct process));

    //Check if memory alllocation was ok:
    if (new_process == NULL) {
        printf("Memory allocation failed \n");
        exit(1); //kill if malloc fails.
    }

    // Now we copy each field of data from the original construct into the new:
    new_process->number = p.number;
    new_process->status = p.status;
    new_process->start_time = p.start_time;
    new_process->CPU_time = p.CPU_time;

    return new_process;  // returning the pointer to the new structure created.
}