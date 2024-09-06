#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    int i, r; // i for the loop index, r will store the random numbers.
    int numbers[1000]; // Declaring an array to hold the 1000 random integers.
    int min, max; // variables to hold the min and max values in the array.

    srand(time(NULL)); // random number generator, with current time to ensure randomness each time it runs.

    int length = sizeof(numbers) / sizeof(numbers[0]); // calculating the length of the array, since C does not have
    //built in function, like .length.. to check the length. To be used in the loop logic.

    for (i = 0; i < length; i++) {
        r = rand() % 100001;
        numbers[i] = r;
    }

    min = numbers[0]; // Initializing these to be the first element of the array, index 0.
    max = numbers[0];

    for (i = 0; i < length; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }

        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    printf("Minimum value in array is: %d\n", min);
    printf("Maximum value in array is: %d\n", max);

    return 0;
}
