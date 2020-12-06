#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

#define INPUT_FILE "input.txt"
#define NR_FIELDS 7

BOOL checkField(char* const fieldName, char* const fieldData) {
    if (fieldData == NULL || fieldData == NULL)
        return 0;

    if (strcmp(fieldName, "cid") == 0)
        return 1;

    int temp, i;

    if (strcmp(fieldName, "byr") == 0) {
        temp = atoi(fieldData);
        return (1920 <= temp && temp <= 2002 ? 1 : 0);
    } else if (strcmp(fieldName, "iyr") == 0) {
        temp = atoi(fieldData);
        return (2010 <= temp && temp <= 2020 ? 1 : 0);
    } else if (strcmp(fieldName, "eyr") == 0) {
        temp = atoi(fieldData);
        return (2020 <= temp && temp <= 2030 ? 1 : 0);
    } else if (strcmp(fieldName, "hgt") == 0) {
        if (strlen(fieldData) == 5 && fieldData[strlen(fieldData) - 2] == 'c' && fieldData[strlen(fieldData) - 1] == 'm') {
            temp = ((fieldData[0] - '0') * 100) + ((fieldData[1] - '0') * 10) + (fieldData[2] - '0');

            return (150 <= temp && temp <= 193 ? 1 : 0);
        } else if (strlen(fieldData) == 4 && fieldData[strlen(fieldData) - 2] == 'i' && fieldData[strlen(fieldData) - 1] == 'n') {
            temp = ((fieldData[0] - '0') * 10) + (fieldData[1] - '0');

            return (59 <= temp && temp <= 76 ? 1 : 0);
        } else
            return 0;
    } else if (strcmp(fieldName, "hcl") == 0) {
        if (fieldData[0] != '#' || strlen(fieldData) != 7)
            return 0;

        for (i = 1; i < strlen(fieldData); i++)
            if (!isxdigit(fieldData[i]))
                return 0;

        return 1;
    } else if (strcmp(fieldName, "ecl") == 0) {
        temp = (strcmp(fieldData, "amb") == 0 || strcmp(fieldData, "blu") == 0
             || strcmp(fieldData, "brn") == 0 || strcmp(fieldData, "gry") == 0
             || strcmp(fieldData, "grn") == 0 || strcmp(fieldData, "hzl") == 0
             || strcmp(fieldData, "oth") == 0);

        return temp;           
    } else if (strcmp(fieldName, "pid") == 0) 
        return (strlen(fieldData) == 9 ? 1 : 0);
    else
        return 0;
}

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
            buffer[strlen(buffer) - 1] = '\0';
            token = strtok(buffer, ":");

            for ( ; i < (NR_FIELDS + 1), token != NULL; i++) {
                strcpy(curFields[i], token);
                token = strtok(NULL, " ");

                if (!checkField(curFields[i], token)) {
                    strcpy(curFields[i], "INVALID");
                    break;
                }

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