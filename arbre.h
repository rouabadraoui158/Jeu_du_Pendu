#ifndef DEF_ARBRE
#define DEF_ARBRE
typedef struct Noeud Noeud;
struct Noeud
{
    char caractere;
    struct Noeud *filsDroit;
    struct Noeud *filsGauche;
    int nbrOccurrence;
};

typedef  Noeud * TArbre;
typedef struct Arbre Arbre;
struct Arbre
{
    struct Noeud *racine;
};

TArbre arbreConsVide();                                                             
bool arbreEstVide(TArbre a);                                                    
TArbre arbreCons(char caractere, int entier, TArbre filsGauche, TArbre filsDroite); 
char arbreRacineLettre(TArbre a);                                                
TArbre arbreFilsGauche(TArbre a);                                               
TArbre arbreFilsDroit(TArbre a);                                                
void arbreSuppr(TArbre *arbre);
void afficherArbre(TArbre a);     
void afficherNoeuds(TArbre a, int espace);
int hauteurArbre(TArbre a);  
TArbre rechercheCaractereTrie(TArbre a, char caractere);                                        
#endif
