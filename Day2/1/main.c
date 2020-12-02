#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *f;
    int inf, sup, totalValid = 0, totalChar, i;
    char c, str[256];

    f = fopen("input.txt", "r");

    if (f == NULL) {
        printf("Error reading the file input.txt!\n");
        return 0;
    }

    while (fscanf(f, "%i-%i %c: %s", &inf, &sup, &c, str) == 4) {
        for (i = 0, totalChar = 0; i < strlen(str); i++) {
            if (str[i] == c)
                totalChar++;
        }

        if (totalChar >= inf && totalChar <= sup)
            totalValid++;
    }

    printf("Total valid: %i", totalValid);

    return 0;
}