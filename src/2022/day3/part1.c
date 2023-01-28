#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256
/*
1. Read line by line
2. Split line into half
3. Compare strings if they have repeating characters
4. Find the repeating character and map it against its priority value
5. Increment sum by that value
*/

// piecewise function
// if larger than or equal to 97, - 96
// otherwise - 38
int _getPos(char k) {
    int decVal = (int) k;
    return decVal >= 97 ? decVal - 97 : decVal - 39;
}

int main() {
    int total = 0;
    char line[100];

    FILE *f = fopen("src/2022/inputs/day3.txt", "r");

    if (f == NULL) {
        fputs("Failed to open the file\n", stderr);
        return -1;
    }

    // read line by line
    while (fgets(line, 100, f) != NULL) {
        // split line into half
        int len = strlen(line);
        int len1 = len / 2;
        int len2 = len - len1;

        char *s1 = malloc(len1 + 1);
        memcpy(s1, line, len1);
        s1[len1] = '\0';

        char *s2 = malloc(len2 + 1);
        memcpy(s2, line + len1, len2);
        s2[len2] = '\0';

        // set a hash of all alphabets

        // to do this we need a hash func that will give the same output given key
        // ie. need to be able to convert 'a' to 1
        int pos[MAX_CHAR] = { 0 };

        // loop over 1 half of string and set flag on all relevant hash pos
        // loop over other half of string, if flag is set then collision!
        // once we got that char, turn pos into number + add to total
        // can do for all lines
        for (int i = 0; i < len1; i++) {
            int priority = _getPos(s1[i]);
            pos[priority] = 1;
        }

        for (int i = 0; i < len2; i++) {
            int priority = _getPos(s2[i]);
            if (pos[priority] == 1) {
                total += priority + 1;
                break;
            }
        }

        free(s1);
        free(s2);
    }

    printf("%s %d%s", "Total: ", total, "\n");
    return total;
}