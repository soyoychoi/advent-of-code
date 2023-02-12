#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 26
// find sequence of 4 characters that are all different
// visited hash
/*
    {
        m: 0,
        j: 1,
        q: 2
    }

    when we increment i, we reset the hash
    then when we have 4 characters, we return
*/
//     i j
// m j q j p q m g

// implementing a hash map
struct HashItem {
    char key;
    int value;
};

struct HashItem* visited[HASH_SIZE];

int hashCode(char key) {
    return ((int) key) % HASH_SIZE;
}

struct HashItem *search(char key) {
    int index = hashCode(key);
    while (visited[index] != NULL) {
        if (visited[index]->key == key) {
            return visited[index];
        }

        ++index;
        index %= HASH_SIZE;
    }

    return NULL;
}

void insert(char key, int value) {
    struct HashItem *item = (struct HashItem*) malloc(sizeof(struct HashItem));
    item->key = key;
    item->value = value;

    int index = hashCode(key);
    visited[index] = item;
}

int main() {
    char c;
    int i = 0;
    int j = 0;
    int len = 0;
    int DISTINCT_CHAR_LEN = 4;
    int threshold = 0;

    FILE *f = fopen("src/2022/inputs/day6.txt", "r");

    if (f == NULL) {
        fputs("Failed to open the file\n", stderr);
        return -1;
    }

    do {
        c = fgetc(f);
        struct HashItem *item = search(c);
        insert(c, j);
        if (item != NULL && item->value >= threshold) {
            i = item->value + 1;
            threshold = i;
            len = j - i;
        }

        j++;
        len++;

        if (len == DISTINCT_CHAR_LEN) {
            break;
        }
    } while (c != EOF);

    printf("Token appears after: %d\n", j);
    return 0;
}