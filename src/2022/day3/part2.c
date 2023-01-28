#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256
/*
// read line by line
// start counter at 1
// increment count at all pos in string
// if counter dividable by 3 set pos that has 3 counts as the badge
// increment total
// reset pos
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
    int counter = 1;
    char line[100];

    FILE *f = fopen("src/2022/inputs/day3.txt", "r");

    if (f == NULL) {
        fputs("Failed to open the file\n", stderr);
        return -1;
    }

    int pos[MAX_CHAR] = { 0 };
    int visited[MAX_CHAR] = { 0 };

    while (fgets(line, 100, f) != NULL) {
        int isThirdLine = counter % 3 == 0;
        for (int i = 0; i < strlen(line) - 1; i++) {
            int priority = _getPos(line[i]);

            // only increase pos if repeating across 3 lines
            if (visited[priority] != counter) {
                pos[priority]++;
                visited[priority] = counter;
            }

            if (isThirdLine && pos[priority] == 3) {
                total += priority + 1;
                break;
            }
        }

        if (isThirdLine) {
            // reset array to 0
            memset(pos, 0, MAX_CHAR);
        }

        counter++;
    }

    printf("%s %d%s", "Total: ", total, "\n");
    return total;
}