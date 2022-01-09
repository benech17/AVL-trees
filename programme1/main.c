#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "avl.h"

#define TAILLE_MAX 15

int isNumber(char s[])
{
    for (int i = 0; s[i]!= '\0'; i++)
    {
        if (isdigit(s[i]) == 0)
              return 0;
    }
    return 1;
}

int main(int argc,char **argv) {
	if(argc != 3 || !isNumber(argv[2])){
		printf("Veuillez entrer une commande valide");
	}
	T_avl root = NULL; 
	int N = atoi(argv[2]);
	
	outputPath = "output";
	
	FILE* prenom;
	prenom=fopen("PrenomsV1.txt","r");
	char chaine[TAILLE_MAX] = "";
	for (int i=0;i<N;i++){
		char nom[TAILLE_MAX] = "";
		fgets(nom,TAILLE_MAX,prenom);
		insertAVL(&root, nom);
		createDotAVL(root, chaine);
	}
	
	printAVL(root, 0); 
	
	return 0;
}







