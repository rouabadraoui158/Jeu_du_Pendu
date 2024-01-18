
int nombreAleatoire(int nombreMax)
{
    return (rand() % nombreMax+1);
}


int piocherMot(char *motPioche)
{
    FILE *dico = fopen("Dictionnaire.txt", "r");

    if (dico == NULL) {
        printf("\nImpossible de charger le dictionnaire de mots");
        return 0;
    }

    // Count the number of words in the file
    int nombreMots = 0;
    while (fscanf(dico, "%s", motPioche) == 1) {
        nombreMots++;
    }

    // Generate a random number between 0 and (nombreMots - 1)
    srand(time(NULL));
    int numMotChoisi = rand() % nombreMots;

    // Reset the file pointer to the beginning of the file
    rewind(dico);

    // Read the file until the chosen word
    for (int i = 0; i < numMotChoisi; i++) {
        if (fscanf(dico, "%s", motPioche) != 1) {
            printf("Erreur lors de la récupération du mot secret.\n");
            fclose(dico);
            return 0;
        }
    }

    fclose(dico);
    return 1;
}


void insererMot(char *mot, TArbre *noeud)
{
    if (*noeud != NULL)
    {
        if (mot[0] != '\0') //pas fin de mot
        {
            if ((*noeud)->caractere == mot[0])
            {
                mot++; // effacer premier caractere
                insererMot(mot, &((*noeud)->filsGauche));//descendre gauche
            }
            else
            {
                if((*noeud)->caractere > mot[0]){ //ordre alphabetique
                        TArbre n = arbreCons(mot[0], 0, NULL, *noeud);
                        mot++;
                        *noeud = n;
                        insererMot(mot, &((*noeud)->filsGauche));
                }else{
                    if ((*noeud)->filsDroit != NULL)//descendre droite
                    {
                        insererMot(mot, &((*noeud)->filsDroit));
                  
                    }
                    else //caractere n'existe pas
                    {
                        (*noeud)->filsDroit = arbreCons(mot[0], 0, NULL, NULL);
                        insererMot(mot, &(*noeud)->filsDroit);
                    }
                }
            }
        }
        else if (mot[0] == '\0' && (*noeud)->caractere != '\0')//cas particulier
        {
                    TArbre n = arbreCons('\0', 1, NULL, *noeud); 
                    *noeud = n;
        }
        else if (mot[0] == '\0' && (*noeud)->caractere == '\0') //fin de mot
        {
            (*noeud)->nbrOccurrence++;
        }
    }
    else
    {
        if (mot[0] != '\0')
        {
            *noeud = arbreCons(mot[0], 0, NULL, NULL);
            mot++;
            insererMot(mot, &((*noeud)->filsGauche));
        }
        else
        {
            *noeud = arbreCons('\0', 1, NULL, NULL);
        }
    }
}

//Permet d'ajouter un mot 
void dicoInsererMot(char *mot, TArbre*arbre)
{
    if (strlen(mot) > 0)
    {
        if (*arbre == NULL)
            *arbre = arbreConsVide();

        insererMot(mot, arbre);

    }
}

// Function to display all words from the dictionary
void afficherMotsDictionnaire() {
	   
    FILE *fichierMots = fopen("Dictionnaire.txt", "r");

    if (fichierMots == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier Dictionnaire.txt.\n");
        return;
    }

    // Tableau dynamique pour stocker les mots
    Mot *mots = NULL;
    size_t tailleMots = 0;
    char ligne[TAILLE_MAX];

    // Lisez chaque ligne du fichier et stockez le mot dans le tableau
    while (fgets(ligne, TAILLE_MAX, fichierMots) != NULL) {
        size_t len = strlen(ligne);

        // Supprimez le saut de ligne à la fin du mot
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[len - 1] = '\0';
        }

        // Ajoutez le mot au tableau dynamique
        Mot nouveauMot;
        strcpy(nouveauMot.mot, ligne);

        tailleMots++;
        mots = realloc(mots, tailleMots * sizeof(Mot));
        mots[tailleMots - 1] = nouveauMot;
    }

    fclose(fichierMots);
    
    printf("\n\n______________________________________________________________________________________\n");
    printf("**************************************************************************************\n");
    printf("\n**************!! Projet Algorithmique Premiere Ingenierie ISI Ariana !!*************\n");
    printf("______________________________________________________________________________________\n");
    printf("______________________________________________________________________________________\n\n");


    // Affichez tous les mots du tableau
    printf("\n********DICTIONNAIRE********\n");
    printf("\nMots du dictionnaire :\n");
    for (size_t i = 0; i < tailleMots; i++) {
        printf("[%ld] %s\n", i + 1, mots[i].mot);
    }
  printf("\n/********DICTIONNAIRE********/\n");
    // Libérez la mémoire utilisée par le tableau
    free(mots);
}
