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
    // Read the character
    scanf(" %c", &caractere); // Notice the space before %c to skip whitespace characters

    // Clear the input buffer
    while (getchar() != '\n'); // Keep reading characters until encountering a newline

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
    printf("_________________________________________________\n\n");
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
       /* case 1:
            printf("  _______\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            break;*/
        /*case 1:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            break;*/
        case 8:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 7:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |     |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 6:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");           
            printf("  |     |\n");
            printf("  |     |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 5:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");             
            printf("  |    /|\n");
            printf("  |     |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 4:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |     |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 3:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |     |\n");            
            printf("  |    /\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 2:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |     |\n");            
            printf("  |    / \\\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 1:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    ---\n");
            printf("  |    /|\\\n");
            printf("  |     |\n");            
            printf("  |    / \\\n");
            printf("  |\n");
            break;
    }
}


int jeuxDePendu(TArbre trie) {
    int i, taille;
    char motCache[TAILLE_MAX];
    char carLu,cardif;
    int attempts, nb_fautes;

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
    //printf("\n \t \t ((Size: %d ))\n", taille);

    char motActuel[TAILLE_MAX];
    for (i = 0; i < taille; i++) {
        motActuel[i] = '-';
    }
    motActuel[taille] = '\0';

    printf("\n \t \tDifficulty Level (Please choose the level of difficulty)\n");
    printf("\n \t \t Hard (Tape 1)\n");
    printf("\n \t \t Medium (Tape 2)\n");
    printf("\n \t \t Easy (Tape 3)\n");
    cardif = lireCaractere();

    switch (cardif) {
        case '1':
            nb_fautes = 3 ;
            break ;
        case '2':
            nb_fautes = 5 ;
            break ;
        case '3':
            nb_fautes = 8 ;
            break ;
    }
    
    printf("\n \t \tNumber of maximum errors : %d \n", nb_fautes);
    
    //printf("\nMot secret : %s \n", motCache);
    
    printf("___________________________________________\n");
    
while (strncmp(motActuel, motCache, taille) != 0 && nb_fautes > 0) {
        printf("\n \t \t What is the secret word? %s\n", motActuel);
        printf("\t \t Remaining wrong attempts: %d\n", nb_fautes);

        do{
        printf("\n \t \t Propose a letter: (or press 0 to quit)\n");

        carLu = lireCaractere();
        //controle saisie
        if(isalpha(carLu)){
        break;
        }else 
        
          if (carLu == -1) {
            // User entered '0', exit the game
            printf("\t \t !!!! Goodbye !!!!\n");
            exit(0);
        }
        }
        while(1);
        

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
            attempts++;

            printf("____________________________________________________________________________\n");

            if (strncmp(motActuel, motCache, taille) == 0) {
	printf("\n\n \t \t ____Congratulations :)\n \tThe word to guess is __%s__ \n \t \tyou won in %d attempts!____\n\n",
		   motCache, attempts);
                printf("____________________________________________________________________________\n");
              
            }
        } else {
            // La lettre a déjà été devinée
           printf("\n \t \t Letter already guessed. You have %d Remaining wrong attempts left.\n", nb_fautes);
               printf("____________________________________________________________________________\n");
        }
    } else {
        // result == NULL or carLu != result->caractere
        
        attempts++;
        nb_fautes--;
        
        printf("\n \t \t Letter not found. You have %d Remaining wrong attempts left.\n", nb_fautes);
        
	displayHangman(nb_fautes +1);  // Display Hangman for wrong letter
        printf("____________________________________________________________________________\n");
        
    }
}
 //while

if (strncmp(motActuel, motCache, taille) != 0) {
    printf("\n\n \t \t °__° You lost! \n \t \t The word was %s\n\n", motCache);
    
}



    return 0;
}

