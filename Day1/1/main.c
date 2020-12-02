#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YEAR 2020

int main() {
    FILE *fMain, *fSecondary;
    int main, secondary;

    fMain = fopen("input.txt", "r");

    if (fMain == NULL) {
        printf("Error reading the file input.txt!\n");
        return 0;
    }

    while (fscanf(fMain, "%i", &main) == 1) {
        fSecondary = fopen("input.txt", "r");

        if (fSecondary == NULL) {
            printf("Error reading the file input.txt!\n");
            return 0;
        }

        while (fscanf(fSecondary, "%i", &secondary) == 1)
            if ((main + secondary) == YEAR)
                break;

        if ((main + secondary) == YEAR)
                break;

        fclose(fSecondary);
    }

    printf("Main: %i\t Secondary: %i\tResult: %i\n", main, secondary, (main * secondary));

    fclose(fMain);

    if (fSecondary != NULL)
        fclose(fSecondary);

    return 0;
}