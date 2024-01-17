//main.c
//Pour Tester les Fonctions Primitives de l'Arbre et de Dictionnaire
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

int main(){
    TArbre dico;
	dico = arbreConsVide();


int i=0;
srand(time(NULL));

	char *mot= malloc( 255 );
	

while(i<8)
{

	int x=piocherMot(mot);
	
	if(x==1){
		dicoInsererMot(mot,&dico);
		i++;
	}

}

dicoInsererMot("Yasmine",&dico);
dicoInsererMot("cas",&dico);
dicoInsererMot("Yasmine",&dico);

/*
dicoInsererMot("cas",&dico);
dicoInsererMot("ce",&dico);
dicoInsererMot("ces",&dico);
dicoInsererMot("ci",&dico);
dicoInsererMot("de",&dico);
dicoInsererMot("des",&dico);
dicoInsererMot("do",&dico);
*/

afficherArbre(dico);
dicoAfficher(dico);

printf("\n\nArbre est vide? : %i \n",arbreEstVide(dico));
printf("Racine lettre : %c \n",arbreRacineLettre(dico));
//printf("Racine Nombre Occurrence : %i \n",arbreRacineNbOcc(dico));
TArbre racineFilsDroit = noeudFilsDroit(dico);
TArbre racineFilsGauche = noeudFilsGauche(dico);
printf("Racine fils gauche lettre : %c \n",arbreRacineLettre(racineFilsGauche ));
printf("Racine fils droit lettre  : %c \n",arbreRacineLettre(racineFilsDroit));
printf("Nbr Mots Total : %i \n",dicoNbMotsTotal(dico));
printf("Nbr Mots different : %i \n",dicoNbMotsDifferents(dico));
printf("nombre de occurrence mot(parfait) : %i \n",dicoNbOccMot("cas",dico));

lettrespercentage(dico);
arbreSuppr(&dico);
printf("Arbre est vide ? : %i \n",arbreEstVide(dico));

	    genererMotSecret(&dico);
	    jeuxDePendu();
    
    
return 0;    
}
