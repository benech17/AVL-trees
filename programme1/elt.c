#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include "elt.h"
#include "include/traces.h" 

#ifdef ELT_CHAR
char * toString(T_elt e) {
	static char buffer[2]; 
	buffer[0] = e; 
	buffer[1] = '\0';
	return buffer; 
}

T_elt genElt(void) {
	static int indice = 0; 
	return 'a' + (indice++%26); 
}

T_elt eltdup(T_elt e) {
	return e; 
} 

int eltcmp(T_elt e1, T_elt e2) {
	return e1 - e2; 
}
#endif

#ifdef ELT_INT
char * toString(T_elt e) {
	static char buffer[11]; 
	sprintf(buffer, "%d",e); 
	return buffer; 
}

T_elt genElt(void) {
	static int indice = 0; 
	return indice++; 
}

T_elt eltdup(T_elt e) {
	return e; 
} 

int eltcmp(T_elt e1, T_elt e2) {
	return e1 - e2; 
}
#endif

#ifdef ELT_STRING
char * toString(T_elt e) {
	return e;  
}

T_elt genElt(void) {
	static int indice = 0; 
	// produire une chaine aléatoire... 
	// On va écrire elt_<numéro>
	char buffer[15]; // elt_+<11 chiffres>
	sprintf(buffer, "elt_%d",indice++); 
	return strdup(buffer); 
} 

T_elt eltdup(T_elt e) {
	// on renvoie une chaine dupliquée
	return strdup(e); 
} 

int eltcmp(T_elt e1, T_elt e2) {
	// on renvoie la différence de code ascii 
	return strcmp(e1,e2); 
}
#endif

#ifdef ELT_STRUCT
char * toString(T_elt e) {
	 
	static char buffer[11]; 
	sprintf(buffer, "%d",e.t[0]); 
	return buffer;
}

T_elt genElt(void) {
	T_elt aux; 
	static int indice = 0; 
	// On produit un tableau ne contenant qu'une seule case avec une valeur toujours différente 
	aux.size = 1;
	aux.t = (int *) malloc(sizeof(int)); 
	aux.t[0] = indice++;
	return aux;  
} 


T_elt eltdup(T_elt e) {
	T_elt aux;
	aux.size = e.size; 
	aux.t =   (int *) malloc(e.size * sizeof(int)); 
	memcpy(aux.t, e.t, e.size * sizeof(int));
	return aux; 
} 

int eltcmp(T_elt e1, T_elt e2) {
 	return e1.t[0] - e2.t[0]; 
}
#endif


