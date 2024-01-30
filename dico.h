#ifndef DEF_DICTIONNAIRE
#define DEF_DICTIONNAIRE
#define TAILLE_MAX 255

typedef struct {
    char mot[TAILLE_MAX];
} Mot;
int piocherMot(char *motPioche);                
int nombreAleatoire(int nombreMax);       
void afficherMotsDictionnaire();        
void dicoInsererMot(char mot[], TArbre *a); 
void insererMot(char *mot, TArbre *a);
          
#endif


