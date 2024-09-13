# include <stdio.h>
# include <stdlib.h> // For strlen() and strcmp()
# include <string.h> // For malloc()

// Function that has to check if a string is a palindrome

int palindrome(char *s1) {
    int len = strlen(s1); // getting the length of the string - storing this in variable len

    // allocating memory for the reversed string.
    // size needed is len + 1, because we need space for the null terminator \0.
    char *s2 = (char *)malloc((len + 1) * sizeof(char));
        if (s2 == NULL) {
            return 0; // If memory allocation should fail, return false (0).
        }

    // now to copy characters from sa go s2, in reverse order
    for (int i = 0; i < len; i++) {
        s2[i] = s1[len - i - 1];
    }
    s2[len] = '\0'; // adding NULL charachter back at position len, the end of s2.

    // Now we compare s1 and s2, with strcmp()
    int result = strcmp(s1, s2);

    free(s2); //Freeing allocated memory to avoid memory leaks.

    if (result == 0) {
        return 1; // meaning return true, strings are equal, and it is indeed a palindrome.
    }
    else {
        return 0; //If strings are not equal, return false (0).
    }
}

int main() {
    char test[] = "racecar";
    if (palindrome(test)) {
        printf("THe string is a palindrome. \n");
    } else {
        printf("The string is not a palindrome \n");
    }
    return 0;
}