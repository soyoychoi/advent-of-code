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
            return Rock;
        case 'B':
            return Paper;
        case 'C':
            return Scissors;
        default:
            return Default;
    }
}

enum score _getEndResult(char encryptedResult) {
    switch (encryptedResult) {
        case 'X':
            return Lose;
        case 'Y':
            return Draw;
        case 'Z':
            return Win;
        default:
            return Lose;
    }
}

enum draw _getMyDraw(int opponentDraw, int endResult) {
    if (endResult == Draw) {
        return opponentDraw;
    }

    if (endResult == Lose && opponentDraw == Rock) {
        return Scissors;
    }

    if (endResult == Win && opponentDraw == Scissors) {
        return Rock;
    }

    // losingDraw is always one less than opponentDraw
    // winningDraw is always one more than opponentDraw
    return endResult == Win ? opponentDraw + 1 : opponentDraw - 1;
}

int main() {
    int total = 0;
    enum draw opponentDraw;
    enum draw myDraw;
    enum score endResult;
    char line[5];

    FILE *f = fopen("src/2022/inputs/day2.txt", "r");

    if (f == NULL) {
        fputs("Failed to open the file\n", stderr);
        return -1;
    }


    // read line by line
    while (fgets(line, 5, f) != NULL) {
        char draw;
        char res;
        sscanf(line, "%c %c", &draw, &res);

        opponentDraw = _getPlayerDraw(draw);
        endResult = _getEndResult(res);
        myDraw = _getMyDraw(opponentDraw, endResult);

        int roundScore = myDraw + endResult;
        total += roundScore;
    }

    printf("%s %d%s", "Total:", total, "\n");
    return total;
}