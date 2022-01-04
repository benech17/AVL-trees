#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *sortArr(char[]);
bool isAnagram(char *, char *);
bool isEqual(char *, char *);

bool isEqual(char *str1, char *str2)
{
    int i;
    for (i = 0; i < strlen(str1); i++)
    {
        // check string is equal or not
        if (str1[i] != str2[i])
        {
            return false;
        }
    }
    return true;
}
bool isAnagram(char *str1, char *str2)
{
    if (strlen(str1) != strlen(str2) || isEqual(str1, str2))
    {
        return false;
    }
    else
    {
        char *str1_copy = (char *)malloc(strlen(str1));
        char *str2_copy = (char *)malloc(strlen(str2));
        // call sortArr() function to sort the arrays
        strcpy(str1_copy, str1);
        sortArr(str1_copy);
        strcpy(str2_copy, str2);
        sortArr(str2_copy);

        if (!isEqual(str1_copy, str2_copy))
            return false;

        free(str1_copy);
        free(str2_copy);
        return true;
    }
}
char *sortArr(char a1[])
{
    int temp = 0, i, l;

    for (i = 0; i < strlen(a1) - 1; i++)
    {
        for (l = i + 1; l < strlen(a1); l++)
        {
            if (a1[i] > a1[l])
            {
                temp = a1[i];
                a1[i] = a1[l];
                a1[l] = temp;
            }
        }
    }
    return a1;
}



int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("veuillez entrer une commande valide ");
        printf("%s", argv[1]);
        return 0;
    }
    FILE *pFile, *pFile2;
    pFile = fopen("Dico_nn_V2/Dico_nn/Dico_03.txt", "r");
    if (pFile != NULL)
    {
        char *a = (char *)malloc(40);
        char *b = (char *)malloc(40);
        while (fscanf(pFile, "%s", a) != EOF)  // get the word of each line
        {
            printf("%s : ", a);
            pFile2 = fopen("Dico_nn_V2/Dico_nn/Dico_03.txt", "r");
            
            if (pFile2 != NULL)
            {
                while (fscanf(pFile2, "%s", b) != EOF)
                {
                    if (isAnagram(a, b))
                        printf("%s | %s - ", a, b);
                }
                printf("\n");
            }
        }
        fclose(pFile);
        fclose(pFile2);
    }
    else
    {
        printf("File does not exist.\n");
    }
}
