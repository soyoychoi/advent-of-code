#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// find the elf carrying the most calories

/*
LOGIC:
1) store max variable
2) read line by line
3) continue sum until encounter new line
4) then compare and max variable
5) return max
*/

int main() {
    // safe to use max 0 since calory can't be negative
    int max = 0;
    int calories = 0;
    char line[10];
    FILE *f = fopen("src/2022/inputs/day1.txt", "r");

    // Checks if the file was opened successfully
    if (f == NULL) {
        fputs("Failed to open the file\n", stderr);
        return -1;
    }

    // read line by line
    while (fgets(line, 10, f) != NULL) {
        if (strcmp(line, "\n") == 0) {
            max = (calories > max) ? calories : max;
            calories = 0;
        }

        int currCalories = 0;
        sscanf(line, "%d", &currCalories);
        calories += currCalories;
    }

    printf("%s %d %s", "Max:", max, "\n");
    return max;
}