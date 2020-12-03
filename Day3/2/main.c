#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFile(int *size, int *lineSize, int *totalLines) {
    FILE *f;
    char *rtrnValue = NULL, *temp, c, firstLine[256];

    f = fopen("input.txt", "r");

    if (f == NULL) {
        printf("Error reading the file input.txt!\n");
        return 0;
    }

    fscanf(f, "%s", firstLine);
    *lineSize = strlen(firstLine);
    rewind(f);

    while (fscanf(f, "%c", &c) == 1) {
        if (c != '\n') {
            temp = (char *)realloc(rtrnValue, sizeof(int) * (*size + 1));

            if (temp == NULL) {
                printf("Error allocating memory!\n");
                free(temp);
                free(rtrnValue);
                fclose(f);
                *size = 0;
                *lineSize = 0;
                return NULL;
            }

            rtrnValue = temp;
            rtrnValue[(*size)++] = c;
        } else
            (*totalLines)++;
    }

    fclose(f);
    (*totalLines)++;
    return rtrnValue;
}

void printPattern(char* p, int size, int lineSize) {
    int i;

    for (i = 0; i < size; i++) {
        printf("%c", p[i]);

        if ((i + 1) % lineSize == 0)
            printf("\t%i\n", i);
    }

    return;
}

int main() {
    int size = 0, lSize = 0, nrLines = 0, i, j, k, l, right = 1, down = 1, trees;
    unsigned long long int totalTrees = 1;
    char* pattern = readFile(&size, &lSize, &nrLines);
    // printPattern(pattern, size, lSize);

    for (l = 0; l < 5; l++) {
        trees = 0;

        if (pattern[0] == '#')
            trees++;

        for (i = down, j = 0; i < nrLines; i += down) {
            for (k = 0; k < right; k++) {
                if ((++j) % lSize == 0)
                    j = 0;
            }

            if (*(pattern + (i * lSize) + j) == '#')
                trees++;
        }    

        printf("Total trees encountered for right = %i and down = %i: %llu\n", right, down, trees); 
        totalTrees *= trees;

        if (right == 7) {
            right = 1;
            down++;
        } else
            right += 2; 
    }

    printf("Result of the multiplication: %llu\n", totalTrees);

    return 0;
}