#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"
#define NR_FIELDS 7

int checkValidID(char** fields) {
    FILE *f;
    char curFields[NR_FIELDS + 1][256] = {"\0"}, buffer[256], *token;
    int totalValid = 0, i = 0, j, temp;

    f = fopen(INPUT_FILE, "r");

    if (f == NULL) {
        printf("Error reading the file %s!\n", INPUT_FILE);
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        if (strcmp(buffer, "\n") == 0) {
            temp = 0;

            for (i = 0; i < (NR_FIELDS + 1); i++)
                for (j = 0; j < NR_FIELDS; j++)
                    if (strcmp(curFields[i], fields[j]) == 0)
                        temp++;

            if (temp == 7)
                totalValid++;

            for (i = 0; i < (NR_FIELDS + 1); i++)
                strcpy(curFields[i], "\0");

            i = 0;
        } else {
            token = strtok(buffer, ":");

            for ( ; i < (NR_FIELDS + 1), token != NULL; i++) {
                strcpy(curFields[i], token);
                token = strtok(NULL, " ");
                token = strtok(NULL, ":");
            }
        }
    }

    return totalValid;
}

int main() {
    char* fields[NR_FIELDS] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    int nrValidID = checkValidID(fields);

    printf("Number of valid IDs: %i\n", nrValidID);

    return 0;
}