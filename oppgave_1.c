#include <stdio.h>

int main()
{
    int i;
    int sum = 0;

    for (i = 0; i < 101; i++) {
        sum += i * i;
    }

    printf("Summen er %d\n", sum);

    return 0;
}

