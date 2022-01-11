#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>
#include "include/traces.h"
#include <string.h>
#include "elt.h"
#include "avl.h"
#include "dict.h"
#include <time.h>

#define TAILLE_MAX 15

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

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("veuillez entrer une commande valide.\nExemple :  ./indexation.exe Dico_nn/Dico_03.txt \n ");
		return 0;
	}
	T_avl root = NULL;
	outputPath = "output";
	dict_t **dict = dictAlloc();
	FILE *pFile;
	pFile = fopen(argv[1], "r");
	int nbMots = 0;
	if (pFile != NULL)
	{
		char *signature = (char *)malloc(20);
		while (fscanf(pFile, "%s", signature) != EOF)
		{

			// on crée la signature en triant chaque mot du dictionnaire
			signature = sortArr(signature);
			if (signature[0] == '\'')
			{
				signature[0] = signature[1];
			}
			addItem(dict, signature, 0);
			nbMots++;
		}
		// printDict(dict);
		char chaine[TAILLE_MAX] = "";
		dict_t *ptr, *ptr2;
		ptr2 = *dict;
		pFile = fopen(argv[1], "r");
		if (pFile != NULL)
		{
			clock_t begin = clock();
			for (ptr = *dict; ptr != NULL; ptr = ptr->next)
			{
				insertAVL(&root, ptr->key);
			}
			clock_t end = clock();
			double time_spent = ((double)(end - begin) / CLOCKS_PER_SEC);
			createDotAVL(root, chaine);
			printf("\n|--------------------------------INFOS----------------------------------|\n");
			printf("Nombre de mots du dictionnaire : %d\n", nbMots);
			printf("Taille des mots du dictionnaire : %ld\n", strlen(ptr2->key));
			printf("Arbre AVL construit en %f secondes , soit %f millisecondes\n", time_spent, time_spent * 1000);
			printf("Hauteur de l'arbre  : %d\n", heightAVL(root));
			printf("Nb de noeuds de l'arbre: %d\n", nbNodesAVL(root));
			printf("Hauteur Minimal d'un arbre possédant %d noeuds : %d\n", nbNodesAVL(root), minHeightAVM(nbNodesAVL(root)));
			printf("|-----------------------------------------------------------------------|\n\n");

			int limit_max = strlen(ptr2->key) + 1;
			char srch[limit_max];
			T_avl pAux;
			while (true)
			{
				printf("Choisissez un mot à chercher dans l'arbre :\n");
				fgets(srch, limit_max, stdin);

				begin = clock();
				pAux = searchAVL(root, srch);
				end = clock();
				time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
				if (pAux == NULL)
				{
					printf(" sorry :(");
				}
				else
				{
					printf("recherche  du mot %s , trouvé en %f secondes , soit %f millisecondes\n\n", toString(pAux->val), time_spent, time_spent * 1000);
				}
			}
		}
		else
		{
			printf("Fichier introuvable. Vérifiez le chemin relatif.\n");
		}
	}
	else
	{
		printf("Fichier introuvable. Vérifiez le chemin relatif.\n");
	}

	/*T_elt e;
	 //insertion des signatures dans un arbre
	//dict_t *ptr;
	clock_t begin = clock();

	T_elt srch = "NAHOUM";
	begin = clock();
	T_avl pAux = searchAVL_it(root, srch);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("recherche itérative trouvé en %f secondes : %s\n", time_spent, toString(pAux->val));

	begin = clock();
	pAux = searchAVL_rec(root, srch);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("recherche récursive trouvé en %f secondes : %s\n", time_spent, toString(pAux->val));


	* /

		return 0;*/
}
