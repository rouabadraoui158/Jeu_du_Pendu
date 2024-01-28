#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "arbre.h"
#include "arbre.c"
#include "dico.h"
#include "dico.c"
#include "pendu.c"
#include "pendu.h"


int main() {

    TArbre arbre;
	   arbre = arbreConsVide();
	
    afficherMotsDictionnaire(); 
      
    FILE *fichierMots = fopen("Dictionnaire.txt", "r");

    if (fichierMots == NULL) {
        fprintf(stderr, "Unable to open the file Dictionary.txt.\n");
        return 1;
    }

    char ligne[TAILLE_MAX];

    while (fgets(ligne, TAILLE_MAX, fichierMots) != NULL) {
        size_t len = strlen(ligne);
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[len - 1] = '\0';
        }

        dicoInsererMot(ligne, &arbre);
    }

    fclose(fichierMots);
    
    afficherArbre(arbre);
    
    gestionDuDico(&arbre);
    
    genererMotSecret(&arbre);
    
    jeuxDePendu(arbre);
	    
    arbreSuppr(&arbre);
    
return 0;    
}
