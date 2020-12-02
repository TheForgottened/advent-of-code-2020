#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YEAR 2020

int main() {
    FILE *fFirst, *fSecond, *fThird;
    int first, second, third;

    fFirst = fopen("input.txt", "r");

    if (fFirst == NULL) {
        printf("Error reading the file input.txt!\n");
        return 0;
    }

    while (fscanf(fFirst, "%i", &first) == 1) {
        fSecond = fopen("input.txt", "r");

        if (fSecond == NULL) {
            printf("Error reading the file input.txt!\n");
            return 0;
        }

        while (fscanf(fSecond, "%i", &second) == 1) {
            fThird = fopen("input.txt", "r");

            if (fThird == NULL) {
                printf("Error reading the file input.txt!\n");
                return 0;
            }

            while (fscanf(fThird, "%i", &third) == 1)
                if ((first + second + third) == YEAR)
                    break;

            fclose(fThird);

            if ((first + second + third) == YEAR)
                break;
        }

        fclose(fSecond);

        if ((first + second + third) == YEAR)
                break;
    }

    printf("First: %i\t Second: %i\tThird: %i\tResult: %i\n", first, second, third, (first * second * third));

    fclose(fFirst);

    return 0;
}