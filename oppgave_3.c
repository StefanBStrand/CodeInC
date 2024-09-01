#include <stdio.h>


long fib(int n) {
    // First, define base case, easy - this is already defined.
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else { // Now for further calculation:
        long a = 0, b = 1, tempFib; // Initialize a and b to first 2 fibpnacci numbers. tempFib is a
        //temporary variable to hold calculated Fib-numbers.
        for (int i = 2; i <= n; i++) {  // Loop starts at 2 since base cases already handled.
            tempFib = a + b; // Stores sum if last two fib.numbers - this is the next fib-number in the sequence.
            a = b; // shift - a will now hold the fib-number previously held in b.
            b = tempFib; // updating b to the fib-number just calculated.
        }
        return b;
    }
}

void beregnFn() {
    int a;  // Variable for storing the n variable entered by user
    printf("Skriv inn et heltall: ");
    scanf("%d", &a);  // Reading input from user, stored in variable a

    FILE *file = fopen("fibonacci.txt", "w"); //Open file for writing
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    printf("File 'fibonacci.txt' created successfullly \n");

    // Calculate and write the Fibonacci sequence to the file
    for (int i = 0; i <= a; i++) {
        long fib_number = fib(i);  // Call fib function to get the ith Fibonacci number
        fprintf(file, "%ld\n", fib_number);  // Write each Fibonacci number to the file
    }

    fclose(file);  // Close the file after writing is done
}

int main() {
    beregnFn();  // Call the function to calculate and write Fibonacci numbers
    return 0;
}
