#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "include/traces.h"

#include "elt.h"
#include "avl.h"

#define TAILLE_MAX 15

int isNumber(char s[])
{
	for (int i = 0; s[i] != '\0'; i++)
	{
		if (isdigit(s[i]) == 0)
			return 0;
	}
	return 1;
}

int main(int argc, char **argv)
{
	if (argc != 3 || !isNumber(argv[2]))
	{
		printf("Veuillez entrer une commande valide.\nExemple : ./main.exe PrenomsV1.txt 10\n");
		return 1;
	}
	T_avl root = NULL;
	int N = atoi(argv[2]);

	outputPath = "output";

	FILE *pFile;
	pFile = fopen(argv[1], "r");
	if (pFile != NULL)
	{
		char chaine[TAILLE_MAX] = "";
		for (int i = 0; i < N; i++)
		{
			char nom[TAILLE_MAX] = "";
			fgets(nom, TAILLE_MAX, pFile);
			insertAVL(&root, nom);
			createDotAVL(root, chaine);
		}
	}
	else
	{
		printf("Fichier introuvable. Vérifiez le chemin relatif.\n");
	}

	printAVL(root, 0);

	return 0;
}
