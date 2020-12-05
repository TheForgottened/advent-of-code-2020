#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"
#define ROWS 128 - 1
#define COLUMNS 8 - 1

char* readFile(char* fileName) {
    FILE *f;
    char *rtrnValue = NULL, *temp, line[16];
    int size;

    f = fopen(fileName, "r");

    if (f == NULL) {
        printf("Error reading the file %s!\n", fileName);
        return 0;
    }

    while (fscanf(f, "%s", line) == 1) {
        temp = (char *)realloc(rtrnValue, (rtrnValue != NULL ? strlen(rtrnValue) : 0) + strlen(line) + (sizeof(char) * 2));

        if (temp == NULL) {
            printf("Error allocating memory!\n");
            free(temp);
            rtrnValue = NULL;
            fclose(f);
            size = 0;
            return NULL;
        }

        rtrnValue = temp;
        strcat(rtrnValue, " ");
        strcat(rtrnValue, line);
    }

    fclose(f);

    return rtrnValue;
}

void printPasses(char* a) {
    int i;

    for (i = 0; i < strlen(a); i++)
        if (a[i] == ' ')
            printf("\n");
        else
            printf("%c", a[i]);

    return;
}

void printSeats(int c[][COLUMNS + 1]) {
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++)
            printf("%i ", c[i][j]);
        printf("\n");
    }
}

int mySeatID(char* passes) {
    int planeSeats[ROWS + 1][COLUMNS + 1] = {0};
    int seat, i, j, columnMin, columnMax, rowMin, rowMax, id;
    char* token;

    token = strtok(passes, " ");
    token = strtok(NULL, " ");

    while (token != NULL) {
        columnMin = 0;
        rowMin = 0;

        columnMax = COLUMNS;
        rowMax = ROWS;

        for (i = 0; i < strlen(token); i++) {
            switch (token[i]) {
                case 'F':
                    rowMax = rowMin + ((rowMax - rowMin) / 2);
                    break;

                case 'B':
                    rowMin = rowMax - ((rowMax - rowMin) / 2);
                    break;

                case 'R':
                    columnMin = columnMax - ((columnMax - columnMin) / 2);
                    break;

                case 'L':
                    columnMax = columnMin + ((columnMax - columnMin) / 2);
                    break;
            }
        }

        id = (rowMax * 8) + columnMax;

        planeSeats[rowMax][columnMax] = 1;

        token = strtok(NULL, " ");
    }

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLUMNS; j++)
            if (planeSeats[i][j] == 0 && planeSeats[i][j + 1] == 1 && planeSeats[i][j - 1] == 1)
                seat = (i * 8) + j;

    return seat;
}

int main() {
    char* bPasses = readFile(INPUT_FILE);

    printf("My Seat ID: %i", mySeatID(bPasses));

    return 0;
}