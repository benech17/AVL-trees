#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "avl.h"

#define TAILLE_MAX 15


int main() {
	T_avl root = NULL; 

	int N;
	printf("Nb prénoms ? ");
	scanf("%d", &N);

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







