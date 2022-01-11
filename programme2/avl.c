#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include "elt.h"
#include "avl.h"
#include "dict.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "include/traces.h"
#include "include/check.h"

char *outputPath = ".";

static T_avl newNodeAVL(T_elt e);
static T_avlNode *rotateLeftAVL(T_avlNode *A);
static T_avlNode *rotateRightAVL(T_avlNode *B);
static T_avlNode *balanceAVL(T_avlNode *A);

static T_avl newNodeAVL(T_elt e)
{
	T_avlNode *pAux;
	pAux = (T_avlNode *)malloc(sizeof(T_avlNode));
	CHECK_IF(pAux, NULL, "erreur malloc dans newNode");
	pAux->val = eltdup(e);
	pAux->bal = 0;
	pAux->l = NULL;
	pAux->r = NULL;
	return pAux;
}

int insertAVL(T_avlNode **pRoot, T_elt e)
{
	T_avl A = (*pRoot);
	if (A == NULL)
	{ // si l'arbre est vide, on y ajoute la racine
		(*pRoot) = newNodeAVL(e);
		return 1; // on renvoit 1 car la hauteur de l'arbre a augmenté
	}
	// cas général
	int deltaH = 0; // deltaH est la variation de hauteur induite par l'ajout de la feuille

	if (eltcmp(e, A->val) <= 0)
	{										   // l'élément doit aller coté gauche car plus petit ou égal
		deltaH = insertAVL(&((*pRoot)->l), e); // insertion dans la sous-arbre gauche
		A->bal += deltaH;					   // on a mis à gauche donc le facteur de déséquilibre augmente
	}

	else if (eltcmp(e, A->val) > 0)
	{ // l'élément doit aller à droite
		deltaH = insertAVL(&((*pRoot)->r), e);
		A->bal -= deltaH; //à droite donc le facteur de déséquilibre diminue
	}

	/*if ((A->bal)==2 || (A->bal)==-2){	//Si la racine est déséquilibrée, on utilise la fonction balanceAVL pour rééquilibrer
			(*pRoot)=balanceAVL(A);
	}

	if (A->bal==1 || A->bal==-1) return 1;//Si la racine de l'arbre est déséquilibré on renvoie 1

	else return 0;				//Sinon (elle est équilibrée), on renvoie 0
	*/
	if (deltaH == 0)
	{
		return 0;
	}
	else
	{
		*pRoot = balanceAVL(*pRoot);
	}
	if ((*pRoot)->bal != 0)
		return 1;
	else
		return 0;
}

static T_avlNode *rotateLeftAVL(T_avlNode *B)
{ // B est le noeud au dessus de celui qui est doublement déséquilibré
	// rotation gauche

	T_avlNode *A;
	A = B->r;
	B->r = A->l;
	A->l = B;

	B->bal = B->bal + 1 - MIN2(0, A->bal);
	A->bal = A->bal + 1 + MAX2(0, B->bal);

	return A;
}

static T_avlNode *rotateRightAVL(T_avlNode *A)
{
	// rotation droite

	T_avlNode *B;
	B = A->l;	 // on définit B comme le noeud dont est issu le sous arbre de gauche de A
	A->l = B->r; // on fait les échanges pour faire les rotations d'après le schéma de la slide 87
	B->r = A;

	A->bal = A->bal - 1 - MAX2(0, B->bal); // on utilise la formule pour mettre la nouvelle balance de A
	B->bal = B->bal - 1 + MIN2(0, A->bal); // nouvelle balance de B
	return B;
}

static T_avlNode *balanceAVL(T_avlNode *A)
{
	// rééquilibrage de A
	if (A->bal == 2)
	{ // si il y a violation de la propriété et que l'arbre issu de A penche à gauche
		if ((A->l)->bal < 0)
		{								// si le sous arbre de gauche issus de A penche à droite
			A->l = rotateLeftAVL(A->l); // on fait la première rotation
			return rotateRightAVL(A);	// on fait la 2e rotation = double rotation
		}
		else
		{ // si le sous arbre issu de A ne penche pas à droite, on fait une simple rotation
			return rotateRightAVL(A);
		}
	}

	else if (A->bal == -2)
	{ // on fait de même mais dans l'autre sens
		if ((A->r)->bal > 0)
		{ // on fait une double rotation
			A->r = rotateRightAVL(A->r);
			return rotateLeftAVL(A);
		}
		else
		{ // on fait une simple rotation
			return rotateLeftAVL(A);
		}
	}

	return A;
}

void printAVL(T_avl root, int indent)
{
	int i;
	// ordre de la récurrence : hauteur de l'arbre
	// Affiche la racine de l'arbre passé en paramètre avec un niveau d'indentation proportionnel à la profondeur du sous-arbre

	// pas de cas de base...
	if (root != NULL)
	{
		// afficher le sous-arbre droit avec indentation+1
		printAVL(root->r, indent + 1);
		// afficher le noeud racine
		for (i = 0; i < indent; i++)
			printf("\t");
		printf("%s (%d) \n ", toString(root->val), root->bal);
		// afficher le sous-arbre gauche avec indentation+1
		printAVL(root->l, indent + 1);
	}
}

int heightAVL(T_avl root)
{
	// hauteur d'un arbre
	int l, r;
	if (root == NULL)
		return -1;

	l = heightAVL(root->l);
	r = heightAVL(root->r);

	return 1 + ((l >= r) ? l : r);
}

int nbNodesAVL(T_avl root)
{
	// nb de noeuds d'un arbre (y compris les feuilles)
	if (root == NULL)
		return 0;

	return 1 + nbNodesAVL(root->l) + nbNodesAVL(root->r);
}

int minHeightAVM(int nb_nodes)
{
	return floor(log2(nb_nodes)); // propriété de cours
}

T_avlNode *searchAVL(T_avl root, T_elt e)
{
	int test;
	int profondeur=0;
	while (root != NULL)
	{
		test = eltcmp(e, root->val);
		if (test == 0){
			printf("profondeur du noeud : %d\n",profondeur);
			return root;
		}
		else if (test <= 0){
			root = root->l;
			profondeur++;
		}else{
			root = root->r;
			profondeur++;
		}
	}

	// pas trouvé (ou vide)
	return NULL;
}

static void makeDot(T_avl root, FILE *fp)
{
	fprintf(fp, "\t%s", toString(root->val));
	fprintf(fp, " [label = \"{{<c> %s | <b> %d}| { <g> | <d>} }\"];\n", toString(root->val), root->bal);

	if (root->r == NULL && root->l == NULL)
	{
		fprintf(fp, "\t%s", toString(root->val));
		fprintf(fp, " [label = \"{{<c> %s | <b> %d}| { <g> NULL | <d> NULL}}\"];\n", toString(root->val), root->bal);
	}
	else if (root->r == NULL)
	{
		fprintf(fp, "\t%s", toString(root->val));
		fprintf(fp, " [label = \"{{<c> %s | <b> %d}| { <g> | <d> NULL}}\"];\n", toString(root->val), root->bal);
	}
	else if (root->l == NULL)
	{
		fprintf(fp, "\t%s", toString(root->val));
		fprintf(fp, " [label = \"{{<c> %s | <b> %d}| { <g> NULL | <d> }}\"];\n", toString(root->val), root->bal);
	}

	// Si fils gauche existe, on appelle récursivement cette fonction avec pour racine le fils gauche
	if (root->l)
	{
		fprintf(fp, "\t%s", toString(root->val));
		fprintf(fp, ":g -> %s;\n", toString(root->l->val));
		makeDot(root->l, fp);
	}

	// Si fils droit existe, on appelle récursivement cette fonction avec pour racine le fils droit
	if (root->r)
	{
		fprintf(fp, "\t%s", toString(root->val));
		fprintf(fp, ":d -> %s;\n", toString(root->r->val));
		makeDot(root->r, fp);
	}
}

void createDotAVL(const T_avl root, const char *basename)
{
	static char oldBasename[FILENAME_MAX + 1] = "";
	static unsigned int noVersion = 0;

	char DOSSIER_DOT[FILENAME_MAX + 1];
	char DOSSIER_PNG[FILENAME_MAX + 1];
	char fnameDot[FILENAME_MAX + 1];
	char fnamePng[FILENAME_MAX + 1];
	char cmdLine[2 * FILENAME_MAX + 20];
	FILE *fp;
	struct stat sb;

	if (stat(outputPath, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
	}
	else
	{
		printf("Création du répertoire %s\n", outputPath);
		mkdir(outputPath, 0777);
	}

	// créations des répertoires output/png et output/dot
	sprintf(DOSSIER_DOT, "%s/dot/", outputPath);
	sprintf(DOSSIER_PNG, "%s/png/", outputPath);

	if (oldBasename[0] == '\0')
	{
		mkdir(DOSSIER_DOT, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		mkdir(DOSSIER_PNG, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}

	// S'il y a changement de nom de base alors recommencer à zéro la numérotation des fichiers
	if (strcmp(oldBasename, basename) != 0)
	{
		noVersion = 0;
		strcpy(oldBasename, basename);
	}

	sprintf(fnameDot, "%s%s_v%02u.dot", DOSSIER_DOT, basename, noVersion);
	sprintf(fnamePng, "%s%s_v%02u.png", DOSSIER_PNG, basename, noVersion);

	CHECK_IF(fp = fopen(fnameDot, "w"), NULL, "erreur fopen dans saveDotBST");

	noVersion++;
	fprintf(fp, "digraph %s {\n", basename);
	fprintf(fp,
			"\tnode [\n"
			"\t\tfontname  = \"Arial bold\" \n"
			"\t\tfontsize  = \"14\"\n"
			"\t\tfontcolor = \"red\"\n"
			"\t\tstyle     = \"rounded, filled\"\n"
			"\t\tshape     = \"record\"\n"
			"\t\tfillcolor = \"grey90\"\n"
			"\t\tcolor     = \"blue\"\n"
			"\t\twidth     = \"2\"\n"
			"\t]\n"
			"\n"
			"\tedge [\n"
			"\t\tcolor     = \"blue\"\n"
			"\t]\n\n");

	if (root == NULL)
		fprintf(fp, "\n");
	else
		makeDot(root, fp);

	fprintf(fp, "}\n");
	fclose(fp); // fermeture fichier

	sprintf(cmdLine, "dot -Tpng  %s -o %s", fnameDot, fnamePng);
	system(cmdLine);
	printf("'%s' et '%s' créés\n", fnameDot, fnamePng);
}
