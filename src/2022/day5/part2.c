#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
1. read the input & make stacks
2. read the procedure and follow through
3. read out the crate at the top of each stack
*/

char* slice(int start, int end, char* str) {
    char* result = malloc((1 + (end - start)) * sizeof(char));
    return strncpy(result, str + start, end - start);
}

int main() {
    int lineCount = 0;
    int NUM_OF_STACKS = 9;
    int STR_LEN = 50;

    char *crates[NUM_OF_STACKS];
    for (int i = 0; i < NUM_OF_STACKS; i++) {
        crates[i] = malloc((STR_LEN + 1) * sizeof(char));
    }

    char line[140];
    char *token, *tofree, *str;

    int nullCharSize = 0;
    int stackPos;
    FILE *f = fopen("src/2022/inputs/day5.txt", "r");

    if (f == NULL) {
        fputs("Failed to open the file\n", stderr);
        return -1;
    }

    while (fgets(line, 140, f) != NULL) {
        if (lineCount < NUM_OF_STACKS - 1) {
            tofree = str = strdup(line);
            stackPos = 0;
            while ((token = strsep(&str, " ")) != NULL) {
                if (strcmp(token, "") == 0) {
                    nullCharSize++;
                    if (nullCharSize % 4 == 0) {
                        stackPos++;
                    }
                } else {
                    crates[stackPos] = strncat(crates[stackPos], &token[1], 1);
                    stackPos++;
                }
            }

            free(tofree);
        } else if (lineCount > NUM_OF_STACKS) {
            int numToMove, fromStack, toStack;
            sscanf(line, "move %d from %d to %d", &numToMove, &fromStack, &toStack);
            char* substr = slice(0, numToMove, crates[fromStack - 1]);
            // remove substr from str
            crates[fromStack - 1] = slice(numToMove, STR_LEN, crates[fromStack - 1]);
            // append to str
            char* concatStr = malloc((strlen(substr) + strlen(crates[toStack - 1]) + 1) * sizeof(char));
            strcpy(concatStr, substr);
            crates[toStack - 1] = strcat(concatStr, crates[toStack - 1]);
        }

        lineCount++;
    }

    char *topCrates;
    topCrates = malloc((1 + NUM_OF_STACKS) * sizeof(char));
    for (int i = 0; i < NUM_OF_STACKS; i++) {
        topCrates = strncat(topCrates, &crates[i][0], 1);
        free(crates[i]);
    }

    printf("Top Crates: %s\n", topCrates);
    return 0;
}