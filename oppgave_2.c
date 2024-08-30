#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    int i, r;
    int numbers[1000];
    int min, max;

    srand(time(NULL));

    int length = sizeof(numbers) / sizeof(numbers[0]);

    for (i = 0; i < length; i++) {
        r = rand() % 100001;
        numbers[i] = r;
    }

    min = numbers[0];
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
