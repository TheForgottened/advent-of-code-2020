#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int sumOfYes(char* fileName) {
    FILE *f;
    char *answersByGroup = NULL, *temp, buffer[256];
    int rtrnValue = 0, groupMembers = 0, tempAnswers, i = 0, j, lixo;

    f = fopen(INPUT_FILE, "r");

    if (f == NULL) {
        printf("Error reading the file %s!\n", INPUT_FILE);
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), f) != NULL) {       
        if (strcmp(buffer, "\n") == 0) {
            if (groupMembers == 1)
                rtrnValue += strlen(answersByGroup);
            else
                for (i = 0; i < strlen(answersByGroup); i++) {
                    tempAnswers = 1;

                    for (j = (i + 1); j < strlen(answersByGroup); j++)
                        if (answersByGroup[i] == answersByGroup[j])
                            tempAnswers++;
                        
                        if (tempAnswers == groupMembers)
                            rtrnValue++;
                }

            free(temp);
            answersByGroup = NULL;
            groupMembers = 0;
        } else {
            buffer[strlen(buffer) - 1] = '\0';
            groupMembers++;

            if (answersByGroup == NULL) {
                temp = (char *)realloc(answersByGroup, strlen(buffer) + sizeof(char));

                if (temp == NULL) {
                    printf("Error allocating memory!\n");
                    free(temp);
                    answersByGroup = NULL;
                    fclose(f);
                    return -1;
                }

                answersByGroup = temp;
                strcpy(answersByGroup, buffer);
            } else {
                temp = (char *)realloc(answersByGroup, strlen(answersByGroup) + strlen(buffer) + sizeof(char));

                if (temp == NULL) {
                    printf("Error allocating memory!\n");
                    free(temp);
                    answersByGroup = NULL;
                    fclose(f);
                    return -1;
                }

                answersByGroup = temp;
                strcat(answersByGroup, buffer);
            }
        }
    }

    return rtrnValue;
}

int main() {
    int result = sumOfYes(INPUT_FILE);

    printf("Sum of counts: %i\n", result);

    return 0;
}