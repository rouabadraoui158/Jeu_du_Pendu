#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAILLE_MAX 255

char MotSecret[TAILLE_MAX];
char motActuel[TAILLE_MAX];

// Function to read a character from the user
char lireCaractere() {
    char caractere = 0;
    caractere = getchar();

    // On lit les autres caractères mémorisés un à un jusqu'au \n (pour les effacer)
	int c;
	while ((c = getchar()) != '\n' && c != EOF);


    return caractere;
}

void lireLigne(char* mot)
{	
	int i=0;
	
	while ((mot[i]=getchar()) != '\n')
	{
		toupper(mot[i]);
		i++;
	}
	mot[i]='\0';	
}


void genererMotSecret(TArbre *Mdico) {
    *Mdico = arbreConsVide();

    // Piocher un seul mot aléatoire
    if (piocherMot(MotSecret) == 1) {
        // Afficher le mot secret
        printf("-------- Mot secret : ---------%s\n", MotSecret);

        // Insérer le mot secret dans l'arbre (si nécessaire)
        dicoInsererMot(MotSecret, Mdico);
    } else {
        printf("Erreur lors de la récupération du mot secret.\n");
    }
}

int jeuxDePendu() {
	int  i, taille;
	char motCache[TAILLE_MAX];
	int coupsRestants, coups;
	char carLu;
	
	strcpy(motCache, MotSecret);
    
	printf("\nBienvenue dans le jeu du pendu !\n\n");
	printf("Tapez 1 pour commencer \n");
	
	carLu = lireCaractere();
	
	
	taille=strlen(motCache) -1 ;
		printf("\n****taille : %d \n\n", taille );
		
	char motActuel[TAILLE_MAX];
	for (i=0;i<taille  ;i++)
	{
		motActuel[i] = '-';
	}
	motActuel[taille]='\0';
	
	char dif[TAILLE_MAX];
	printf("\nDifficulté (tapez le nombre de coups pour trouver le mot)\n");
	lireLigne(dif);
	
	coupsRestants= strtol(dif, NULL, 10);
	coups = coupsRestants;

	printf("\n\n\nNombre de coups : %d \n\n", coupsRestants);
	
	printf("\n\n\nMot caché : %s \n\n", motCache);
	
	while ( strcmp(motActuel,motCache)!=0 )
	{
	 if(coupsRestants > 0 ){
		printf("\nQuel est le mot secret ? %s\n", motActuel);
		printf("Il vous reste %d coups a jouer\n", coupsRestants);

		printf("\nProposez une lettre : (ou appuyez sur 1 pour quitter)\n");
		
		carLu=lireCaractere();
		
		if (carLu != '1')
		{		
			for (i=0; i<strlen(motCache);i++)
			{

				if (motCache[i] == carLu)
				{
					motActuel[i] = carLu;
				}
			}				

			coupsRestants--;
			
			printf("\n ****A???%s\n",motActuel);
			
			
			printf("\n ****s???%s\n",MotSecret);
			
		/* if (strncmp(motActuel, motCache, taille) != 0)
			{
				printf("\n\ndiiiiiiiiiiiiiiiiiiifff!\n\n");			
			} else {printf("saaame");}*/
			
			if  (strncmp(motActuel, motCache, taille) == 0)
			{
				printf("\n%s\nBravo, vous avez gagné en %d coups!\n\n",motCache,coups-coupsRestants);
				coupsRestants = 0;
				//break;			
			}
			
			else if (coupsRestants==0) printf("\n\nVous avez perdu!\nLe mot était %s\n\n",motCache);
		}
		
		else coupsRestants=0;
		

		
	}}
	
    return 0;
}
