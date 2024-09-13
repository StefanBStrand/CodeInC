#include <stdio.h> // For input and output, printf, scanf
#include <stdlib.h> // for dynamic memory allocation, liek malloc, free)

int main() {
    int n; // variable that will store the number of integers.

    printf("Enter how many integers you will provide: ");
    scanf("%d", &n); // Scanning input from user.

    //Now to allocate memory for n amount of integers using malloc, and a pointer.
    int *A = (int *)malloc(n * sizeof(int)); // again, type casting (int *) to convert the memory returned
    // by malloc into an int pointer.

    if (A == NULL) {
        printf("Memory allocatin failed");
        return 1; // return error code if memory allocation fails.
    }

    // Now to read the integers from user input:
    printf("Remember to enter ONE integer at a time, and press ENTER or SPACE between each of them! \n");
    // Scanf expects whitespace between inputs
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", A + i); // storing (with scanf) them in the array using pointer arithmetic.
        // A + i gives the address of the i-th element in the dynamically allocated memory.
    }

    // print integers in reverse order. again using pointer arithemtic.
    printf("The integers in reverse order are: \n");
    for (int i = n - 1; i >= 0; i--) { // getting elements from the last index.pos and backwards.
        printf("%d", *(A + i)); // Using pointer dereferencing, *(A + i) to get the actual value from the address
        // the pointer points to.
    }
    printf("\n");

    free(A);

    return 0;
}