#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
returns 1 if there is a full overlap between a and b
otherwise returns 0
*/
int isFullyOverlapping(int aFirst, int aLast, int bFirst, int bLast) {
    // if first char of b <= first char of a && last char of b >= last char of a
    // if first char of a <= first char of b && last char of a <= last char of b

    return (bFirst <= aFirst && bLast >= aLast) ||
        (aFirst <= bFirst && aLast >= bLast);
}

int main() {
    int count = 0;
    char line[32];

    FILE *f = fopen("src/2022/inputs/day4.txt", "r");

    if (f == NULL) {
        fputs("Failed to open the file\n", stderr);
        return -1;
    }

    // read line by line
    while (fgets(line, 32, f) != NULL) {
        // 1. split the line by comma
        // 2. split each line by dash
        char *a = strtok(line, ",");
        char *b = strtok(NULL, ",");

        int aFirst = atoi(strtok(a, "-"));
        int aLast = atoi(strtok(NULL, "-"));

        int bFirst = atoi(strtok(b, "-"));
        int bLast = atoi(strtok(NULL, "-"));

        if (isFullyOverlapping(aFirst, aLast, bFirst, bLast)) {
            count++;
        }
    }


    printf("Total: %d\n", count);
    return count;
}