#include <stdio.h>
#include <stdlib.h>

/*
read line by line
compare scores and add to or subtract from total
Rules:
- rock > scissors
- paper > rock
- scissors > paper
return total score
*/

enum draw { Rock = 1, Paper = 2, Scissors = 3, Default = 0 };
enum score { Lose = 0, Draw = 3, Win = 6 };

enum draw _getPlayerDraw(char encryptedDraw) {
    switch (encryptedDraw) {
        case 'A':
        case 'X':
            return Rock;
        case 'B':
        case 'Y':
            return Paper;
        case 'C':
        case 'Z':
            return Scissors;
        default:
            return Default;
    }
}

int _getScore(int opponentDraw, int myDraw) {
    // edge cases
    if (opponentDraw == Scissors && myDraw == Rock) {
        // opponent has lost
        return myDraw + Win;
    }

    if (opponentDraw == Rock && myDraw == Scissors) {
        // opponent has won
        return myDraw + Lose;
    }

    // main logic
    if (opponentDraw < myDraw) {
        // opponent has lost
        return myDraw + Win;
    }

    if (opponentDraw > myDraw) {
        // opponent has won
        return myDraw + Lose;
    }

    // it's a draw!
    return myDraw + Draw;
}

int main() {
    int total = 0;
    enum draw opponentDraw;
    enum draw myDraw;
    char line[5];

    FILE *f = fopen("src/2022/inputs/day2.txt", "r");

    if (f == NULL) {
        fputs("Failed to open the file\n", stderr);
        return -1;
    }


    // read line by line
    while (fgets(line, 5, f) != NULL) {
        char draw1;
        char draw2;
        sscanf(line, "%c %c", &draw1, &draw2);

        opponentDraw = _getPlayerDraw(draw1);
        myDraw = _getPlayerDraw(draw2);

        int currScore = _getScore(opponentDraw, myDraw);
        total += currScore;
    }

    printf("%s %d%s", "Total:", total, "\n");
    return total;
}