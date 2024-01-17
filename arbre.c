#define MAX(x, y) (((x) > (y)) ? (x) : (y))

//Construire Arbre Vide
TArbre arbreConsVide()
{
    return NULL;
}

//Retourne si l'arbre est vide
bool arbreEstVide(TArbre a)
{
    if (a == NULL)
    {
        return true;
    }
    return false;
}
//Construire noeud
TArbre arbreCons(char caractere, int entier, TArbre filsGauche, TArbre filsDroit)
{
    TArbre a = (Noeud *)malloc(sizeof(Noeud));
    a->caractere = caractere;
    a->nbrOccurrence = entier;
    a->filsGauche = filsGauche;
    a->filsDroit = filsDroit;
    return a;
}
//retorune le caractere du racine
char arbreRacineLettre(TArbre a)
{
    if (!arbreEstVide(a))
    {
        return a->caractere;
    }
    return '\0';
}

//retorune le nombre d'occurence du racine
int arbreRacineNbOcc(TArbre a)
{
    if (!arbreEstVide(a))
    {
        return a->nbrOccurrence;
    }
    return 0;
}
//Retourne fils Gauche
TArbre noeudFilsGauche(TArbre a)
{
    if (a != NULL)
    {
        return a->filsGauche;
    }
    return NULL;
}
//Retourne fils Droit
TArbre noeudFilsDroit(TArbre a)
{
    if (a != NULL)
    {
        return a->filsDroit;
    }
    return NULL;
}

//Permet de supprimer l'arbre
void arbreSuppr(TArbre *noeud)
{
    if (*noeud != NULL)
    {
        arbreSuppr(&((*noeud)->filsDroit));
        arbreSuppr(&((*noeud)->filsGauche));
        free(*noeud);
        *noeud = NULL;
    }
}


//Retroune l'hauteur de l'arbre
int hauteurArbre(TArbre a)
{
    if (a != NULL)
    {
        return 1 + MAX(hauteurArbre(a->filsGauche), hauteurArbre(a->filsDroit));
    }
    return -1;
}

void afficherNoeuds(TArbre noeud, int espace)
{
    if (noeud != NULL)
    {
    	int i;
        for (i = 0; i < espace; i++)
            printf("-");

        if (noeud->caractere != '\0')
        {
            
            if(noeud->caractere == ' '){
                printf("NULL\n");
            }else{
                printf("%c\n", noeud->caractere);
            }
        }
        else
        {
            printf("\\0\n");
        }
        if (noeud->filsGauche != NULL)
            printf("(G)"); //Fils Gauche
        afficherNoeuds(noeud->filsGauche, espace + 1);
        if (noeud->filsDroit != NULL)
            printf("(D)"); //Fils Droit
        afficherNoeuds(noeud->filsDroit, espace + 1);
    }
}

//Permet d'afficher l'arbre
void afficherArbre(TArbre a)
{
    if (a != NULL)
    {
        printf("\n*******************************ARBRE*******************************\n");
        printf("\nHauteur de l'arbre : %i\n\n", hauteurArbre(a));
        printf("(R)"); //racine
        afficherNoeuds(a, 1);
        printf("\n/*******************************ARBRE*******************************/\n");
    }
}




