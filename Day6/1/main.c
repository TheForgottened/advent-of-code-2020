#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int sumOfYes(char* fileName) {
    FILE *f;
    char *answersByGroup = NULL, uniqueAnswers[27] = {'\0'}, *temp, buffer[256];
    int rtrnValue = 0, i = 0, j;

    f = fopen(INPUT_FILE, "r");

    if (f == NULL) {
        printf("Error reading the file %s!\n", INPUT_FILE);
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), f) != NULL) {       
        if (strcmp(buffer, "\n") == 0) {
            uniqueAnswers[0] = answersByGroup[0];

            for (i = 1; i < strlen(answersByGroup); i++)
                for (j = 0; j < strlen(uniqueAnswers); j++)
                    if (answersByGroup[i] == uniqueAnswers[j])
                        break;
                    else if (j == strlen(uniqueAnswers) - 1) {
                        uniqueAnswers[j + 1] = answersByGroup[i];
                    }

            rtrnValue += strlen(uniqueAnswers);

            for (i = 0; i < 26; i++)
                uniqueAnswers[i] = '\0';

            free(temp);
            answersByGroup = NULL;
        } else {
            buffer[strlen(buffer) - 1] = '\0';
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