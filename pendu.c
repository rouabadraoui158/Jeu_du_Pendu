#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char MotSecret[TAILLE_MAX];
char motActuel[TAILLE_MAX];
TArbre trie;

// Function to read a character from the user
char lireCaractere() {
    char caractere = 0;
    caractere = getchar();

    // On lit les autres caractères mémorisés un à un jusqu'au \n (pour les effacer)
	int c;
	while ((c = getchar()) != '\n' && c != EOF);

    // Si l'utilisateur a tapé '1', retourner une valeur spéciale pour indiquer la sortie
    if (caractere == 'q') {
        return -1;  // Return a special value to indicate exit
    }
    
    return caractere;
}

void lireLigne(char* mot) {
    int i = 0;

    while ((mot[i] = getchar()) != '\n') {
        // Utilisez isdigit pour vérifier si le caractère est un chiffre
        if (!isdigit(mot[i])) {
            printf("\t \t!!!! Veuillez entrer un nombre.\n");
            // Clear the input buffer to prevent issues with subsequent inputs
            while (getchar() != '\n');
            i = 0;  // Réinitialiser l'index pour recommencer la saisie
        } else {
            // Convertir le caractère en majuscule
            mot[i] = toupper(mot[i]);
            i++;
        }
    }
    mot[i] = '\0';
}


void genererMotSecret(TArbre *Mdico) {
    *Mdico = arbreConsVide();

    // Piocher un seul mot aléatoire
    if (piocherMot(MotSecret) == 1) {
        // Afficher le mot secret
        printf("\n \t \t ((Mot secret :%s))\n", MotSecret);

        // Insérer le mot secret dans l'arbre (si nécessaire)
        dicoInsererMot(MotSecret, Mdico);
    } else {
        printf("Erreur lors de la récupération du mot secret.\n");
    }
}


int jeuxDePendu(TArbre trie) {
    int i, taille;
    char motCache[TAILLE_MAX];
    int coupsRestants, coups;
    char carLu;

    strcpy(motCache, MotSecret);

    printf("\t______________________________________________________________\n");
    printf("\t______________________________________________________________\n");
    printf("\n \t**************!! Bienvenue dans le jeu du pendu !!************\n");
    printf("\t______________________________________________________________\n");
    printf("\t______________________________________________________________\n\n");
    
    
    while (carLu != '1') {
    printf(" \t \t!! Si vous êtes prêt, tapez 1 pour commencer !! \n");

    carLu = lireCaractere();
    
    } 
    
       if (carLu == '1') {
        // L'utilisateur a choisi de commencer le jeu
        printf(" \t \t____Le jeu commence____ \n");
        }

    taille = strlen(motCache) ;
    printf("\n \t \t ((taille : %d ))\n", taille);

    char motActuel[TAILLE_MAX];
    for (i = 0; i < taille; i++) {
        motActuel[i] = '-';
    }
    motActuel[taille] = '\0';

    char dif[TAILLE_MAX];
    printf("\n \t \tNiveau De Difficulté (tapez le nombre de coups pour trouver le mot)\n");
    lireLigne(dif);

    coupsRestants = strtol(dif, NULL, 10);
    coups = coupsRestants;
    
    printf("\n \t \tNombre de coups : %d \n", coupsRestants);

    //printf("\nMot secret : %s \n", motCache);
    
    printf("___________________________________________\n");
    

while (strncmp(motActuel, motCache, taille) != 0 && coupsRestants > 0) {
    printf("\n \t \t Quel est le mot secret ? %s\n", motActuel);
    printf("\t \t Il vous reste %d coups à jouer\n", coupsRestants);


    printf("\n \t \t Proposez une lettre : (ou appuyez sur q pour quitter)\n");

    carLu = lireCaractere();

           if (carLu == -1) {
            // User entered '1', exit the game
            printf("\t \t !!!! Au revoir !!!!\n");
            exit(0); 
        }


    
    

   TArbre result = rechercheCaractereTrie(trie, carLu);
        
 if (result != NULL) {
       printf("\n \t \t Lettre trouvée : %c\n", result->caractere);
       
    int letterFound = 0;

    for (i = 0; i < strlen(motCache); i++) {
        if (motCache[i] == result->caractere && motActuel[i] == '-' ) {
            motActuel[i] = carLu;
            letterFound = 1;
        }
    }

    if (letterFound) {
        coupsRestants--;

       // printf("\n \t \t °Mot actuel : %s\n", motActuel);
        
        printf("____________________________________________________________________________\n");

        if (strncmp(motActuel, motCache, taille) == 0) {
            printf("\n\n \t \t ____Bravo :) \t Le mot à deviné est __%s__ \n \t \tvous avez gagné en %d coups!____\n\n", motCache, coups - coupsRestants);
            
        printf("____________________________________________________________________________\n");
            coupsRestants = 0;
        }
    } else {
            // La lettre a déjà été devinée
            printf("\n \t \t Lettre déjà devinée. Il vous reste %d coups.\n", coupsRestants);
            printf("____________________________________________________________________________\n");
          }
} else {
    // Traitement lorsque result est NULL (lettre non trouvée dans l'arbre)
    coupsRestants--;
    printf("\n \t \t Lettre non trouvée dans l'arbre. Il vous reste %d coups.\n", coupsRestants);
    printf("____________________________________________________________________________\n");
}

    
    
} //while

if (strncmp(motActuel, motCache, taille) != 0) {
    printf("\n\n \t \t °__° Vous avez perdu! \n \t \t Le mot était %s\n\n", motCache);
    coupsRestants = 0;  
}



    return 0;
}

