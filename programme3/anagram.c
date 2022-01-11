#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "dict.h"

char *sortArr(char[]);
bool isAnagram(char *, char *);
bool isEqual(char *, char *);
bool isEqual(char *str1, char *str2)
{
    int i;
    for (i = 0; i < strlen(str1); i++)
    {
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

void incrementDict(dict_t **dict, char *path)
{
    FILE *pFile, *pFile2;
    pFile = fopen(path, "r");
    if (pFile != NULL)
    {
        char *a = (char *)malloc(20);
        char *b = (char *)malloc(20);
        while (fscanf(pFile, "%s", a) != EOF)
        {
            pFile2 = fopen(path, "r");
            if (pFile2 != NULL)
            {
                while (fscanf(pFile2, "%s", b) != EOF)
                {
                    if (isAnagram(a, b))
                    {
                        incrementItem(dict, a);
                    }
                }
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

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("veuillez entrer une commande valide \n");
        return 0;
    }
    dict_t **dict = dictAlloc();

    FILE *pFile, *pFile2;
    // création du dict avec 0 partout
    pFile = fopen(argv[1], "r");
    if (pFile != NULL)
    {
        char *key = (char *)malloc(20);
        while (fscanf(pFile, "%s", key) != EOF)
        {
            addItem(dict, key, 0);
        }
    }

    incrementDict(dict, argv[1]);
    
    int count =0;
    pFile = fopen(argv[1], "r");
    if (pFile != NULL)
    {
        char *a = (char *)malloc(20);
        char *b = (char *)malloc(20);
        for (int i = 25; i >= 0; i--)
        {
            pFile = fopen(argv[1], "r");
            while (fscanf(pFile, "%s", a) != EOF)
            {
                if (getItem(dict, a) == i)
                {
                    if(getItem(dict, a) >=1)
                        count ++;
                    printf("%s (%d): ", a, getItem(dict, a));
                    pFile2 = fopen(argv[1], "r");
                    if (pFile2 != NULL)
                    {
                        while (fscanf(pFile2, "%s", b) != EOF)
                        {
                            if (isAnagram(a, b))
                            {
                                printf("%s | %s ", a, b);
                            }
                        }
                        printf("\n");
                    }
                }
            }
        }
        printf("Nombre de mots dans le dictionnaire possédant au moins 1 anagramme : %d\n",count);
        fclose(pFile);
        fclose(pFile2);
    }
    else
    {
        printf("File does not exist.\n");
    }
}
