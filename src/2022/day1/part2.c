#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// find the elf carrying the most calories

/*
LOGIC:
1) store a list of 3 variables
2) read line by line
3) continue sum until encounter new line
4) // if last item --> then just replace last item
   // for all other cases
   // --> insert and move the rest a step
5) return max calories
*/
int _insertSorted(int arr[], int n, int key) {
    int i;
    for (i = n - 1; (i >= 0 && arr[i] < key); i--) {
        arr[i + 1] = arr[i];
    }
    arr[i + 1] = key;
    return 0;
}

int _reorderMaxArray(int calorie, int max[], int count) {
    // if calorie is less than the last, return
    if (calorie < max[count - 1]) {
        return -1;
    }

    // otherwise, insert calorie into array
    _insertSorted(max, count, calorie);
    return 0;
}

int main(int argc, char *argv[]) {
    // safe to use max 0 since calory can't be negative
    int count = atoi(argv[1]);
    if (count == 0) {
        printf("%s", "Please provide a count argument\n");
        return -1;
    }

    int max[count];
    // initialize with 0
    for (int i = 0; i < count; i++) {
        max[i] = 0;
    }

    int sum = 0;
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
            _reorderMaxArray(calories, max, count);
            calories = 0;
        }

        int currCalories = 0;
        sscanf(line, "%d", &currCalories);
        calories += currCalories;
    }

    for (int i = 0; i < count; i++) {
        sum += max[i];
    }
    printf("%s %d %s", "Sum:", sum, "\n");
    return sum;
}