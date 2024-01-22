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
    if (caractere == '0') {
        return -1;  // Return a special value to indicate exit
    }
    
    return caractere;
}

void lireLigne(char* mot) {
    int i = 0;

    while ((mot[i] = getchar()) != '\n') {
        // Utilisez isdigit pour vérifier si le caractère est un chiffre
        if (!isdigit(mot[i])) {
            printf("\t \t!!!! Please enter a number.\n");
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
        printf("\n \t \t ((Secret word: %s))\n", MotSecret);

        // Insérer le mot secret dans l'arbre (si nécessaire)
        dicoInsererMot(MotSecret, Mdico);
    } else {
        printf("Error retrieving the secret word.\n\n");
    }
}

void displayHangman(int tries) {
    switch (tries) {
        case 8:
            printf("  _______\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 7:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 6:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 5:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |     |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 4:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 3:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 2:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |    /\n");
            printf("  |\n");
            break;
        case 1:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |    / \\\n");
            printf("  |\n");
            break;
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
    printf("\n \t**************!! Welcome to the Hangman Game !!************\n");
    printf("\t______________________________________________________________\n");
    printf("\t______________________________________________________________\n\n");
   
    while (carLu != '1') {
    printf(" \t \t!! If you are ready, type 1 to start !! \n");

    carLu = lireCaractere();
    
    } 
    
       if (carLu == '1') {
        // L'utilisateur a choisi de commencer le jeu
        printf(" \t \t____The game begins____ \n");
        }

    taille = strlen(motCache) ;
    printf("\n \t \t ((Size: %d ))\n", taille);

    char motActuel[TAILLE_MAX];
    for (i = 0; i < taille; i++) {
        motActuel[i] = '-';
    }
    motActuel[taille] = '\0';

    char dif[TAILLE_MAX];
    printf("\n \t \tDifficulty Level (type the number of attempts to guess the word)\n");
   
    lireLigne(dif);

    coupsRestants = strtol(dif, NULL, 10);
    coups = coupsRestants;
    
    printf("\n \t \tNumber of attempts: %d \n", coupsRestants);
    

    //printf("\nMot secret : %s \n", motCache);
    
    printf("___________________________________________\n");
    
char lettresProposees[TAILLE_MAX];
lettresProposees[0] = '\0';


while (strncmp(motActuel, motCache, taille) != 0 && coupsRestants > 0) {
        printf("\n \t \t What is the secret word? %s\n", motActuel);
        printf("\t \t Remaining attempts: %d\n", coupsRestants);

        printf("\n \t \t Propose a letter: (or press 0 to quit)\n");

        carLu = lireCaractere();

        if (carLu == -1) {
            // User entered '0', exit the game
            printf("\t \t !!!! Goodbye !!!!\n");
            exit(0);
        }

    TArbre result = rechercheCaractereTrie(trie, carLu);

    if (result != NULL && carLu == result->caractere) {
        printf("\n \t \t Letter found: %c\n", result->caractere);

        int letterFound = 0;

        for (i = 0; i < taille; i++) {
            if (motCache[i] == result->caractere && motActuel[i] == '-') {
                motActuel[i] = carLu;
                letterFound = 1;
            }
        }

        if (letterFound) {
            coupsRestants--;

            printf("____________________________________________________________________________\n");

            if (strncmp(motActuel, motCache, taille) == 0) {
	printf("\n\n \t \t ____Congratulations :) \t The word to guess is __%s__ \n \t \tyou won in %d attempts!____\n\n",
		   motCache, coups - coupsRestants);
                printf("____________________________________________________________________________\n");
                coupsRestants = 0;
            }
        } else {
            // La lettre a déjà été devinée
           printf("\n \t \t Letter already guessed. You have %d attempts left.\n", coupsRestants);
               printf("____________________________________________________________________________\n");
        }
    } else {
        // result == NULL or carLu != result->caractere
        
        coupsRestants--;
        printf("\n \t \t Letter not found. You have %d attempts left.\n", coupsRestants);

        printf("____________________________________________________________________________\n");
    }
    displayHangman(coupsRestants);  // Display Hangman for wrong letter
}
 //while

if (strncmp(motActuel, motCache, taille) != 0) {
    printf("\n\n \t \t °__° You lost! \n \t \t The word was %s\n\n", motCache);
    coupsRestants = 0;  
}



    return 0;
}

