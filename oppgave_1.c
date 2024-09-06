#include <stdio.h>

// Note to teachers/assistants - I prefer writing all my code in english, comments as well.

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

